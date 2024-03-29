/* simple argument parsing with documentation

 options can be typed as int, char, char*, bool, float, or handled by a
 special function positional parameters are always string and must be
 listed in order a special type Rest means all rest are returned as a
 pointer. */

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util/arg.h"
#include "util/error-util.h"
#include "util/memory-util.h"
#include "util/print.h"
#include "util/string-util.h"
#include "util/verbosity.h"

#include "lib/commonlib.h"

static int32_t      argp_verbosity = 0;
static char *       commandLine;
static const char * pname;

/* order is based on how enums are defined in ArgType.  */
static const char * type2fmt[] = { "",       "<int>",   "<char>", "<string>",
                                   "<bool>", "<float>", "<rest>", "",
                                   "",       "" };

enum {
    BAD_STRING  = -1,
    BAD_REST    = -2,
    BAD_FLOAT   = -3,
    BAD_INT     = -4,
    UNPARSEABLE = -5,
    OVERFLOW    = -6
};

static PURE_FUNC const char * kind2str(ArgKind k);

static void usage(arg_parser_t const * restrict ap);

static void EXIT_FUNC
FORMATF(2, 3)
    argdie(arg_parser_t const * restrict def, char const * restrict fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    fprintf_stdout("%s: Usage Error: ", pname);
    vprintf(fmt, ap); /* NOLINT */
    va_end(ap);
    fprintf_stdout("\n");
    usage(def);
    _exit(-1);
}

static char const *
concat_args(char const * const * args_begin) {
    enum { OUTBUF_LEN = 128 };
    static char buf[OUTBUF_LEN];

    uint64_t offset = 0, incr;
    char *   next;
    __builtin_memset(buf, 0, OUTBUF_LEN);
    for (; args_begin && *args_begin; ++args_begin) {

        die_assert(offset < OUTBUF_LEN,
                   "Overflow trying to concat user args.\n");

        next = stpncpy_c(buf + offset, *args_begin, OUTBUF_LEN - offset);
        die_assert(next >= (buf + offset));
        incr = CAST(uint64_t, next - (buf + offset));
        offset += incr;

        die_assert(offset < OUTBUF_LEN,
                   "Overflow trying to concat user args.\n");
        *(buf + (offset++)) = '|';
    }
    if (offset) {
        --offset;
    }

    if (buf[offset] != '\0') {
        buf[offset] = '\0';
    }
    return buf;
}


static const char *
arg2str(arg_option_t const * restrict desc) {
    enum { OUTBUF_LEN = 512 };
    static char buffer[OUTBUF_LEN];
    ssize_t     n;
    ssize_t     avail_length = OUTBUF_LEN;
    char *      p            = buffer;
    char        sep          = (desc->kind == KindPositional) ? ':' : ' ';


    if (desc->kind == (ArgKind)Help) {
        return "[-h]";
    }

    if ((desc->kind == KindPositional) && (desc->required)) {
        *p++ = '<';
        --avail_length;
        die_assert(avail_length >= 0);
    }
    else if (!desc->required) {
        *p++ = '[';
        --avail_length;
        die_assert(avail_length >= 0);
    }

    switch (desc->type) {
        case Integer:
        case Character:
        case String:
        case Boolean:
        case Float:
            die_assert(avail_length >= 0);
            n = CAST(
                int64_t,
                safe_snprintf(
                    p, CAST(uint64_t, avail_length), "%s%c%s",
                    concat_args(desc->args_begin), sep,
                    type2fmt[desc->type] /* NOLINT(*-constant-array-index) */));
            die_assert(n >= 0 && n < avail_length,
                       "Buffer overflow creating help message\n");
            avail_length -= n;
            p += strlen_c(p);
            break;
        case Rest:
            die_assert(desc->kind == KindRest);
            die_assert(avail_length >= 0);
            n = CAST(
                int64_t,
                safe_snprintf(
                    p, CAST(uint64_t, avail_length), "...%c%s ", sep,
                    type2fmt[desc->type] /* NOLINT(*-constant-array-index) */));
            die_assert(n >= 0 && n < avail_length,
                       "Buffer overflow creating help message\n");
            avail_length -= n;
            p += strlen_c(p);
            break;
        case Help:
        case Toggle:
        case Set:
        case Increment:
            die_assert(avail_length >= 0);
            n = CAST(int64_t,
                     safe_snprintf(p, CAST(uint64_t, avail_length), "%s",
                                   concat_args(desc->args_begin)));
            die_assert(n >= 0 && n < avail_length,
                       "Buffer overflow creating help message\n");
            avail_length -= n;
            p += strlen_c(p);
            break;

        case EndOptions:
            fall_through;
        default:
            /* new type that we didn't implement yet?  */
            die("Unknown type: %d\n", desc->type);
    }
    if (desc->kind == KindRest) {
        n = strlen_c("...") + 1;
        die_assert(n < avail_length, "Buffer overflow creating help message\n");
        memcpy_c(p, "...", CAST(uint64_t, n));
        p += n;
        avail_length -= n;
    }

    if ((desc->kind == KindPositional) && (desc->required)) {
        die_assert(avail_length > 1, "Buffer overflow creating help message\n");
        *p++ = '>';
        --avail_length;
    }
    else if (!desc->required) {
        die_assert(avail_length > 1, "Buffer overflow creating help message\n");
        *p++ = ']';
        --avail_length;
    }
    die_assert(avail_length > 0, "Buffer overflow creating help message\n");
    *p = 0;
    return buffer;
}

static void
usage(arg_parser_t const * restrict ap) {
    arg_parser_node_t const * apn;
    fprintf_stdout("%s: ", pname);
    /* print out shorthand for arguments.  */
    for (apn = ap->parsers; apn; apn = apn->next) {
        arg_option_t const * args = apn->parser->args;
        int32_t              i    = 0;
        while (args[i].kind != KindEnd) {
            fprintf_stdout(" %s", arg2str(args + i));
            i++;
        }
        fprintf_stdout("\n%s\n", apn->parser->progdoc);
    }

    /* Now print individual descriptions.  */
    for (apn = ap->parsers; apn; apn = apn->next) {
        arg_option_t const * args = apn->parser->args;
        int32_t              i    = 0;
        while (args[i].kind != KindEnd) {
            fprintf_stdout(
                "   %20s\t%s\t", arg2str(args + i),
                args[i].kind == KindHelp ? "Print this message" : args[i].desc);
            switch (args[i].type) {
                case Increment:
                case Integer: {
                    uint64_t default_v = 0;

                    memcpy_c(&default_v, args[i].dest, args[i].dest_sz);

                    if (args[i].is_unsigned) {
                        fprintf_stdout("(default: %lu)", default_v);
                    }
                    else {
                        uint32_t dst_bitwidth;
                        die_assert(args[i].dest_sz <= (UINT_MAX / 8));
                        dst_bitwidth = CAST(uint32_t, 8 * args[i].dest_sz);
                        die_assert(dst_bitwidth <= sizeof_bits(uint64_t));
                        if (dst_bitwidth != sizeof_bits(uint64_t) &&
                            (default_v & (1UL << (dst_bitwidth - 1)))) {
                            uint64_t sign_extend = ~(0UL);
                            sign_extend <<= dst_bitwidth;
                            default_v |= sign_extend;
                        }

                        fprintf_stdout("(default: %ld)", default_v);
                    }
                }

                break;
                case Character:
                    fprintf_stdout("(default: %c)", *(char *)(args[i].dest));
                    break;

                case String:
                    fprintf_stdout("(default: %s)", *(char **)(args[i].dest));
                    break;

                case Toggle:
                case Set:
                case Boolean:
                    fprintf_stdout(
                        "(default: %s)",
                        *(safe_int32_t *)(args[i].dest) ? "true" : "false");
                    break;

                case Float: {
                    double default_d = 0.0;
                    switch (args[i].dest_sz) {
                        case 8:
                            default_d = *(safe_double *)(args[i].dest);
                            break;

                        case 4:
                            default_d =
                                CAST(double, *(safe_float *)(args[i].dest));
                            break;

                        default:
                            break;
                    }


                    fprintf_stdout("(default: %lf)", default_d);
                } break;
                case Rest:
                    fprintf_stdout("(default: N/A)");
                    fall_through;
                case Help:
                    break;
                case EndOptions:
                    fall_through;
                default:
                    die("Unkown Type: %d\n", args[i].type);
            }
            fprintf_stdout("\n");
            i++;
        }
    }
    freeArgumentParser(ap);
}

static void
makeCommandline(int32_t argc, char * const * argv) {
    int32_t i;
    size_t  len = 2;
    char *  p;
    for (i = 0; i < argc; i++) {
        len += (1 + strlen_c(argv[i]));
    }
    p   = (char *)safe_calloc(len, 1);
    len = 0;
    for (i = 0; i < argc; i++) {
        strcpy_c(p + len, argv[i]);
        len += strlen_c(argv[i]);
        p[len++] = ' ';
    }
    p[len - 1] = 0;
    vfprint(stderr, "[%s]\n", p);
    commandLine = p;
}


#define I_CHECK_OVERFLOW_ERROR(unsigned_T, signed_T)                           \
    if ((is_negative || (!desc->is_unsigned)) &&                               \
        (CAST(int64_t, CAST(signed_T, user_v)) != CAST(int64_t, user_v))) {    \
        storage_type =                                                         \
            desc->is_unsigned ? V_TO_STR(unsigned_T) : V_TO_STR(signed_T);     \
        err = OVERFLOW;                                                        \
    }                                                                          \
    else if (!is_negative && desc->is_unsigned &&                              \
             (CAST(uint64_t, CAST(unsigned_T, user_v)) !=                      \
              CAST(uint64_t, user_v))) {                                       \
        die_assert(desc->is_unsigned);                                         \
        storage_type = V_TO_STR(unsigned_T);                                   \
        err          = OVERFLOW;                                               \
    }

#define CHECK_OVERFLOW_ERROR(T_size)                                           \
    I_CHECK_OVERFLOW_ERROR(CAT(u, T_size, _t), CAT(T_size, _t))

/* offset is 1 for option args (argv[0] points at option, argv[1] at
 * start of data) offset is 0 for positional args (argv[0] points at
 * actual argument). */
static int32_t
assignArg(arg_option_t * restrict desc,
          char * const * argv,
          arg_parser_t * restrict ap,
          int32_t        offset,
          char * const * argv_end) {

    vvprint("[%-12s][%-8s][%-20s][%-1d][%p][%-2lu][%-1d][%-20s]\n",
            kind2str(desc->kind), type2fmt[desc->type],
            concat_args(desc->args_begin), desc->required, desc->dest,
            desc->dest_sz, desc->is_unsigned, desc->desc);


    switch (desc->type) {
        case Increment: {
            vprint("incremement %s\n", concat_args(desc->args_begin));
            {
                uint64_t next_v, prev_v = 0;
                memcpy_c(&prev_v, desc->dest, desc->dest_sz);
                next_v = prev_v + 1;
                /* TODO: Add overflow check here. */
                memcpy_c(desc->dest, &next_v, desc->dest_sz);
            }
        } break;

        case String: {
            if (!argv[offset]) {
                return BAD_STRING;
            }
            vprint("Saving %s to %s\n", argv[offset],
                   concat_args(desc->args_begin));
            {
                char const ** p = (char const **)desc->dest;
                *p              = argv[offset];
                return 1;
            }
        } break;

        case Rest: {
            if (!argv[offset]) {
                return BAD_REST;
            }
            die_assert(desc->kind == KindRest);
            vprint("Saving %s to Rest\n", argv[offset]);
            {
                arg_rest_t * p;
                uint64_t     n;
                die_assert(argv_end >= (argv + offset));
                p       = (arg_rest_t *)desc->dest;
                n       = CAST(uint64_t, (argv_end) - (argv + offset));
                p->ptrs = argv + offset;
                p->n    = n;
                return 1;
            }
        } break;

        case Set: {
            vprint("Setting %s to 1\n", concat_args(desc->args_begin));
            {
                memset_c(desc->dest, 0, desc->dest_sz);
                __builtin_memset(desc->dest, 1, 1);
            }
        } break;

        case Toggle: {
            vprint("toggeling %s\n", concat_args(desc->args_begin));
            {
                uint64_t prev_v = 0;
                memcpy_c(&prev_v, desc->dest, desc->dest_sz);
                prev_v = !prev_v;
                memcpy_c(desc->dest, &prev_v, desc->dest_sz);
            }
        } break;

        case Float: {
            char * end;
            double user_v;
            if (!argv[offset]) {
                return BAD_FLOAT;
            }

            user_v = strtod(argv[offset], &end);
            warn_assert(argv[offset] != end, "Float -> [%s] unparseable (%s)\n",
                        concat_args(desc->args_begin), argv[offset]);
            if (argv[offset] != end) {
                switch (desc->dest_sz) {
                    case 8: {
                        vprint("float -> [%s] = %lf\n",
                               concat_args(desc->args_begin), user_v);
                        __builtin_memcpy(desc->dest, &user_v, 8);
                    } break;
                    case 4: {
                        /* Case to float. */
                        float user_f = CAST(float, user_v);
                        vprint("float -> [%s] = %f\n",
                               concat_args(desc->args_begin), user_f);
                        __builtin_memcpy(desc->dest, &user_f, 4);
                    } break;
                    default:
                        return BAD_FLOAT;
                }
            }
            return 1;
        } break;

        case Integer: {
            char *       end;
            uint64_t     user_v       = 0;
            int32_t      err          = 0;
            char const * storage_type = NULL;
            int32_t      base         = 10;
            int32_t      is_negative  = 0;
            if (!argv[offset]) {
                return BAD_INT;
            }

            if (argv[offset][0] == '0' && argv[offset][1] == 'x') {
                base = 16;
            }
            else if (argv[offset][0] == '-') {
                is_negative = 1;
            }

            user_v = desc->is_unsigned
                         ? CAST(uint64_t, strtoull(argv[offset], &end, base))
                         : CAST(uint64_t, strtoll(argv[offset], &end, base));

            warn_assert(argv[offset] != end, "int -> [%s] unparseable (%s)\n",
                        concat_args(desc->args_begin), argv[offset]);
            vprint("int -> [%s] = %lu\n", concat_args(desc->args_begin),
                   user_v);
            if (argv[offset] != end) {
                switch (desc->dest_sz) {
                    case 8:
                        __builtin_memcpy(desc->dest, &user_v, 8);
                        break;
                    case 4:
                        CHECK_OVERFLOW_ERROR(int32);
                        __builtin_memcpy(desc->dest, &user_v, 4);
                        break;
                    case 2:
                        CHECK_OVERFLOW_ERROR(int16);
                        __builtin_memcpy(desc->dest, &user_v, 2);
                        break;
                    case 1:
                        CHECK_OVERFLOW_ERROR(int8);
                        __builtin_memcpy(desc->dest, &user_v, 1);
                        break;
                    default:
                        return BAD_INT;
                }
                warn_assert(
                    err == 0, "int -> [%s] overflow converting (%s) to %s\n",
                    concat_args(desc->args_begin), argv[offset], storage_type);
            }
            return 1;
        } break;

        case Help: {
            usage(ap);
            _exit(-1);
        }
        case Character:
        case Boolean:
        case EndOptions:
        default:
            die("NIY: type\n");
    }
    return 0;
}

static PURE_FUNC const char *
kind2str(ArgKind k) {
    switch (k) {
        case KindEnd:
            return "End";
        case KindHelp:
            return "Help";
        case KindPositional:
            return "Positional";
        case KindOption:
            return "Option";
        case KindRest:
            return "Rest";
        default:
            assert(0);
    }
    return "Unknown";
}

/* return true if has help.  */
static PURE_FUNC bool_t
checkArgDef(arg_parser_t const * restrict ap,
            arg_defs_t const * restrict def,
            bool_t main) {
    /* optional/help come before postional before rest.  */
    uint32_t             state   = KindOption;
    arg_option_t const * desc    = def->args;
    int32_t              hashelp = false;
    int32_t              i;
    for (i = 0; desc[i].kind != KindEnd; i++) {
        if (desc[i].kind > KindEnd) {
            argdie(ap, "Bad kind - no KindEnd?");
        }
        if (desc[i].kind != state) {
            if ((state == KindOption) && (desc[i].kind == KindHelp)) {
                hashelp = true;
                continue;
            }
            if (desc[i].kind < state) {
                argdie(ap,
                       "Bad order of arg defs: %s comes before "
                       "last of %s",
                       kind2str((ArgKind)state), kind2str(desc[i].kind));
            }
            state = desc[i].kind;
        }
        if (((state == KindPositional) || (state == KindRest)) && !main) {
            argdie(ap, "positional args but not main");
        }
    }
    return hashelp;
}

static void
checkarg_parser_t(arg_parser_t const * ap) {
    bool_t                    hashelp = false;
    arg_parser_node_t const * apn;
    for (apn = ap->parsers; apn; apn = apn->next) {
        hashelp |= checkArgDef(ap, apn->parser, apn->main);
    }
    if (!hashelp) {
        argdie(ap, "No help string");
    }
}

int32_t
parseArgs(int32_t argc, char * const * argv, arg_defs_t const * restrict def) {
    arg_parser_node_t n  = { 1, def, NULL };
    arg_parser_t      ap = { &n, def };
    return parseArguments(&ap, argc, argv);
}

/**************************************************************************/
/* multiple argument parsers. */

arg_parser_t *
createArgumentParser(arg_defs_t const * restrict def) {
    arg_parser_t * ap = (arg_parser_t *)safe_calloc(1, sizeof(arg_parser_t));
    ap->parsers =
        (arg_parser_node_t *)safe_calloc(1, sizeof(arg_parser_node_t));
    ap->parsers->parser = def;
    ap->parsers->main   = 1;
    ap->mainProg        = def;
    return ap;
}

void
freeCommandLine(void) {
    safe_free(commandLine);
}

void
freeArgumentParser(arg_parser_t const * ap) {
    arg_parser_node_t * next;
    arg_parser_node_t * p;
    for (p = ap->parsers; p; p = next) {
        next = p->next;
        safe_free(p);
    }
    safe_free((void *)(uintptr_t)ap); /* NOLINT(performance-no-int-to-ptr) */
    freeCommandLine();
}


void
addArgumentParser(arg_parser_t * restrict ap,
                  arg_defs_t const * restrict def,
                  int32_t order) {
    arg_parser_node_t * p =
        (arg_parser_node_t *)safe_calloc(1, sizeof(arg_parser_node_t));
    p->parser = def;
    p->next   = NULL;
    p->main   = 0;

    if (order > 0) {
        arg_parser_node_t * nextp;
        for (nextp = ap->parsers; nextp->next; nextp = nextp->next) {
            ;
        }
        nextp->next = p;
    }
    else {
        p->next     = ap->parsers;
        ap->parsers = p;
    }
}

static int32_t
user_args_match(char const * const * args_begin, char const * arg) {
    for (; args_begin && *args_begin; ++args_begin) {
        if (strcmp_c(*args_begin, arg) == 0) {
            return 1;
        }
    }
    return 0;
}

int32_t
parseArguments(arg_parser_t * restrict ap, int32_t argc, char * const * argv) {
    char * const *            argv_end = argv + argc;
    arg_parser_node_t const * apn;
    int32_t                   i, j, base_arg, base_dest_offset;
    bool_t                    opts_possible;
    arg_option_t *            desc;
    /* get program name and commandline as a string.  */
    pname = argv[0];
    makeCommandline(argc, argv);
    argv++;
    argc--;

    checkarg_parser_t(ap);

    /* process args.  */
    vprint("Processing args for %s: %d\n", pname, argc);

    for (apn = ap->parsers; apn; apn = apn->next) {
        desc = apn->parser->args;


        for (i = 0; (desc[i].kind != KindEnd); ++i) {
            if (desc[i].required && desc[i].required != 1) {
                desc[i].required = 1;
            }
        }
    }


    opts_possible = true;
    for (i = 0; (i < argc) && opts_possible; i++) {
        char const * arg = argv[i];
        vprint("%d -> [%s]\n", i, arg);
        if (arg[0] == '-') {
            /* Handle options.  */
            bool_t ok       = false;
            bool_t notfound = true;
            for (apn = ap->parsers; notfound && apn; apn = apn->next) {
                desc = apn->parser->args;
                for (j = 0; notfound && (desc[j].kind != KindEnd); j++) {
                    if (user_args_match(desc[j].args_begin, arg)) {
                        int32_t consumed;
                        ok       = true;
                        notfound = false;
                        /* see if it is special.  */
                        if (desc[j].type == EndOptions) {
                            opts_possible = false;
                            break;
                        }
                        /* process it.  */
                        consumed =
                            assignArg(desc + j, argv + i, ap, 1, argv_end);
                        if (consumed < 0) {
                            argdie(ap,
                                   "Missing expected argument value for [%s]\n",
                                   argv[i]);
                        }
                        i += consumed;
                        desc[j].required |= (desc[j].required << 1);
                    }
                }
            }
            if (!ok) {
                argdie(ap, "Do not understand the flag [%s]\n", arg);
            }
        }

        else {
            /* No more options.  */
            break;
        }
    }

    /* ok, now we handle positional args, we handle them in the order
     * they are declared only the main parser can define positional
     * args.  */
    desc = NULL;
    for (apn = ap->parsers; apn; apn = apn->next) {
        if (apn->main) {
            desc = apn->parser->args;
            break;
        }
    }
    die_assert(desc != NULL);
    base_arg = i;

    for (base_dest_offset = 0; desc[base_dest_offset].kind != KindEnd;
         base_dest_offset++) {
        if ((desc[base_dest_offset].kind == KindPositional) ||
            (desc[base_dest_offset].kind == KindRest)) {
            break;
        }
    }
    /* base is first positional arg we are passed, j is first descriptor
     * for positional arg.  */
    vprint("start pos: j=%d %s kind=%d basearg=%d\n", base_dest_offset,
           concat_args(desc[base_dest_offset].args_begin),
           desc[base_dest_offset].type, base_arg);

    j = 0;
    while ((desc[base_dest_offset + j].kind == KindPositional) &&
           ((base_arg + j) < argc)) {
        int32_t consumed = assignArg(desc + base_dest_offset + j,
                                     argv + base_arg + j, ap, 0, argv_end);
        vprint("%d: %s\n", j,
               base_arg + concat_args(desc[base_dest_offset + j].args_begin));

        j += consumed;
        desc[base_dest_offset + j].required |=
            (desc[base_dest_offset + j].required << 1);
    }
    /* check that we used all the arguments and don't have any extra. */
    if (desc[base_dest_offset + j].type == (ArgType)KindPositional) {
        argdie(ap, "Expected more arguments, only given %d", j);
    }
    else if ((desc[base_dest_offset + j].type == (ArgType)KindEnd) &&
             ((base_arg + j) < argc)) {
        argdie(ap, "Too many arguments, given %d", j);
    }
    /* see if we have a variable number of args at end.  */
    if (desc[base_dest_offset + j].type == Rest && ((base_arg + j) < argc)) {
        int32_t consumed = assignArg(desc + base_dest_offset + j,
                                     argv + base_arg + j, ap, 0, argv_end);
        j += consumed;
        desc[base_dest_offset + j].required |=
            (desc[base_dest_offset + j].required << 1);
    }

    /* if user defined a post parsing function, call it - main prog
     * called last.
     */
    for (apn = ap->parsers; apn; apn = apn->next) {
        if ((apn->main != 1) && (apn->parser->doneParsing != NULL)) {
            (*(apn->parser->doneParsing))();
        }
    }
    if (ap->mainProg->doneParsing) {
        (*(ap->mainProg->doneParsing))();
    }

    for (apn = ap->parsers; apn; apn = apn->next) {
        desc = apn->parser->args;
        for (j = 0; (desc[j].kind != KindEnd); ++j) {
            if (desc[j].required == 1) {
                argdie(ap, "Missing required argument\n\t%s\n",
                       arg2str(desc + j));
            }
        }
    }
    return 0;
}

int32_t
doParse(arg_defs_t const * restrict argp, int argc, char * const * argv) {
    arg_parser_t * ap;
    int32_t        ret, orig_verbosity;

    orig_verbosity = get_verbosity();
    set_verbosity(argp_verbosity);

    ap  = createArgumentParser(argp);
    ret = parseArguments(ap, argc, argv);
    if (ret) {
        argdie(ap, "Missing required argument\n");
    }
    freeArgumentParser(ap);

    set_verbosity(orig_verbosity); /* NOLINT(clang-analyzer-unix.Malloc) */
    return ret;
}
