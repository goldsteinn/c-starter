#ifndef SRC_D_CONTAINER_D_CL_DEFS_H_
#define SRC_D_CONTAINER_D_CL_DEFS_H_

#include <assert.h>
#include <limits.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>

#include "lib/hash/hash.h"
#include "lib/string-custom.h"
#include "util/common.h"
#include "util/error-util.h"
#include "util/inline-math.h"
#include "util/memory-util.h"
#include "util/portability.h"

/********************************************************************/
/* Common info.  */
enum {
    I_cl_cache_line_size = 64,
    I_cl_page_size       = 4096,
    I_cl_CHAR_BIT        = CHAR_BIT
};

/********************************************************************/
/* Builtins.  */
#define I_cl_choose_expr(...)     I_builtin_choose_expr(__VA_ARGS__)
#define I_cl_constant_p(...)      I_builtin_constant_p(__VA_ARGS__)
#define I_cl_expect(cond, expect) I_builtin_expect(cond, expect)
#define I_cl_unreachable()        I_builtin_unreachable()
#define I_cl_memcpy(...)          I_builtin_memcpy(__VA_ARGS__)
#define I_cl_memset(...)          I_builtin_memset(__VA_ARGS__)
#define I_cl_memcmp(...)          I_builtin_memcmp(__VA_ARGS__)
#define I_cl_memcmp_eq(...)       I_builtin_memcmp_eq(__VA_ARGS__)
#define I_cl_classify_type(...)   I_builtin_classify_type(__VA_ARGS__)
#define I_cl_ptr_type             I_builtin_ptr_type
#define I_cl_ctzw(...)            I_builtin_ctz(__VA_ARGS__)
#define I_cl_ctzl(...)            I_builtin_ctzl(__VA_ARGS__)
#define I_cl_ctzll(...)           I_builtin_ctzll(__VA_ARGS__)
#define I_cl_clzw(...)            I_builtin_clz(__VA_ARGS__)
#define I_cl_clzl(...)            I_builtin_clzl(__VA_ARGS__)
#define I_cl_clzll(...)           I_builtin_clzll(__VA_ARGS__)
#define I_cl_prefetch(...)        I_builtin_prefetch(__VA_ARGS__)

/********************************************************************/
/* Platform.  */
#define I_cl_USING_LLVM USING_LLVM
#define I_cl_USING_GCC  USING_GCC

/********************************************************************/
/* Type macros.  */
#define I_cl_as_typeof(x, ...)         ((__typeof__(x))(__VA_ARGS__))
#define I_cl_as_member_type(T, member) __typeof__(((T){ 0 }).member)
#define I_cl_uint_for_bits(nbits)                                              \
    I_cl_choose_T((nbits) <= 16,                                               \
                  I_cl_choose_T((nbits) <= 8, uint8_t, uint16_t),              \
                  I_cl_choose_T((nbits) <= 32, uint32_t, uint64_t))

#define I_cl_is_ptr(x) (I_cl_classify_type(x) == I_cl_ptr_type)

#define I_cl_choose_T(cond, T0, T1) choose_T(cond, T0, T1)

/********************************************************************/
/* Common macros.  */
#define I_cl_likely(...)   I_cl_expect(__VA_ARGS__, 1)
#define I_cl_unlikely(...) I_cl_expect(__VA_ARGS__, 0)


#define I_cl_no_cmov()   __asm__ volatile("" : : :)
#define I_cl_typeof(...) __typeof__(__VA_ARGS__)

#define I_cl_const_cond(...) (I_cl_constant_p(__VA_ARGS__) && (__VA_ARGS__))
#define I_cl_sizeof_bits(x)  (sizeof(x) * I_cl_CHAR_BIT)
#define I_cl_guarantee(x)                                                      \
    if (!(x)) {                                                                \
        I_cl_unreachable();                                                    \
    }

#define I_cl_is_p2(x) (!((x) & ((x)-1)))
#define I_cl_p2_m(p, m)                                                        \
    (((p) == I_cl_sizeof_bits(unsigned long)) ? (0UL - (m))                    \
                                              : ((1UL << (p)) - (m)))
#define I_cl_agu_t(ptr, offset) ((__typeof__(ptr))(I_cl_agu(ptr, offset)))
#define I_cl_agu(ptr, offset)   (((uintptr_t)(ptr)) + (offset))

#define I_cl_ctz(x)                                                            \
    I_cl_choose_expr(                                                          \
        sizeof(x) == sizeof(long long), I_cl_builtin_ctzll(x),                 \
        I_cl_choose_expr(sizeof(x) == sizeof(long), I_cl_builtin_ctzl(x),      \
                         I_cl_builtin_ctzw(x)))
#define I_cl_clz(x)                                                            \
    I_cl_choose_expr(                                                          \
        sizeof(x) == sizeof(long long), I_cl_builtin_clzll(x),                 \
        I_cl_choose_expr(sizeof(x) == sizeof(long), I_cl_builtin_clzl(x),      \
                         I_cl_builtin_clzw(x)))

#define I_cl_lsb(x)                 ((x) & (-(x)))
#define I_cl_is_p2(x)               (!((x) & ((x)-1)))
#define I_cl_rounddown_p2(x, power) ((x) & (-(power)))

#define I_cl_roundup_p2(x, power) I_cl_rounddown_p2(((x) + ((power)-1)), power)

#define I_cl_unsafe_next_p2(x)                                                 \
    (I_cl_as_typeof(x, 2) << ((I_cl_sizeof_bits(x) - 1) - I_cl_clz((x)-1)))

#define I_cl_max(...) CMAX(__VA_ARGS__)
#define I_cl_min(...) CMIN(__VA_ARGS__)

#define I_cl_next_p2(x)            next_p2(x)
#define I_cl_const_eval_next_p2(x) const_eval_next_p2(x)

#define I_cl_log2_p2(x) I_cl_ctz(x)

#define I_cl_scale_sz_to(from_obj_size, to_obj_size, val)                      \
    I_cl_choose_expr(                                                          \
        ((to_obj_size) >= (from_obj_size)) &&                                  \
            (((to_obj_size) % (from_obj_size)) == 0),                          \
        (val) * ((to_obj_size) / (from_obj_size)),                             \
        I_cl_choose_expr(((from_obj_size) >= (to_obj_size)) &&                 \
                             (((from_obj_size) % (to_obj_size)) == 0),         \
                         (val) / ((from_obj_size) / (to_obj_size)),            \
                         ((val) / (from_obj_size)) * (to_obj_size)))

#define I_cl_CAST(T, ...)        CAST(T, __VA_ARGS__)
#define I_cl_cat(...)            CAT(__VA_ARGS__)
#define I_cl_namer(prefix, name) I_cl_cat(prefix, _, name)

#define I_cl_signbit(x)                                                        \
    ((((__typeof__(x))1) << (I_cl_sizeof_bits(x) - 1)) & (x))

#define I_cl_load_T(T, p)                                                      \
    ({                                                                         \
        T I_tmp_load_var_;                                                     \
        if (sizeof(T) <= 24) {                                                 \
            I_tmp_load_var_ = *((T const *)(p));                               \
        }                                                                      \
        else {                                                                 \
            I_cl_memcpy(&I_tmp_load_var_, (T const *)(p), sizeof(T));          \
        }                                                                      \
        I_tmp_load_var_;                                                       \
    })

#define I_cl_store_T(T, p, v)                                                  \
    ({                                                                         \
        if (sizeof(T) <= 24) {                                                 \
            *((T *)(p)) = (v);                                                 \
        }                                                                      \
        else {                                                                 \
            T I_tmp_store_var_ = (v);                                          \
            I_cl_memcpy((T *)(p), &I_tmp_store_var_, sizeof(T));               \
        }                                                                      \
    })


/********************************************************************/
/* Asserts.  */
#define I_cl_static_assert(...) const_assert(__VA_ARGS__)
#define I_cl_assert_constant(expr)                                             \
    if (!I_cl_constant_p(expr)) {                                              \
        I_cl_make_error();                                                     \
    }


#define I_cl_assert_const_eval(expr)                                           \
    enum {                                                                     \
        I_cl_cat(I_cl_checking_constant_eval, __LINE__, _, __COUNTER__) =      \
            (expr)                                                             \
    };

#define I_cl_err_check(x, err_code)                                            \
    if (I_cl_unlikely(!(x))) {                                                 \
        return err_code;                                                       \
    }

#define I_cl_compile_assert(expr)                                              \
    if (!(expr)) {                                                             \
        I_cl_make_error();                                                     \
    }

extern void I_attr_error("Should be unreachable") I_cl_make_error_f(void);
#define I_cl_make_error(...) I_cl_make_error_f()


/********************************************************************/
/* Attributes.  */
#if defined(__cplusplus) && I_STDCPP_VERSION >= 2014
# define I_cl_constexpr constexpr
#else
# define I_cl_constexpr
#endif

#define I_cl_noinline NEVER_INLINE
#define I_cl_pure     I_attr_pure
#define I_cl_const    I_attr_const
#define I_cl_unused   I_attr_unused

#define I_cl_attrs  static I_cl_constexpr ALWAYS_INLINE
#define I_cl_cattrs I_cl_attrs I_cl_const
#define I_cl_pattrs I_cl_attrs I_cl_pure

/********************************************************************/
/* Types.  */
typedef struct I_cl_byte {
    uint8_t val_;
} I_cl_byte_t;

typedef struct I_cl_word {
    uint16_t val_;
} I_cl_word_t;

typedef struct I_cl_long {
    uint32_t val_;
} I_cl_long_t;

typedef struct I_cl_quad {
    uint64_t val_;
} I_cl_quad_t;

typedef bool_t I_cl_bool_t;
#if (defined __cplusplus) && I_cl_USING_GCC
# define I_cl_dconst
#else
# define I_cl_dconst const
#endif

typedef size_t    I_cl_obj_size_t;
typedef uintptr_t I_cl_uptr_t;


/********************************************************************/
/* Returns.  */

#define I_cl_die(...) msg_die(__VA_ARGS__)

#define cl_operation_success ((I_cl_bool_t)0)
#define cl_operation_failure ((I_cl_bool_t)1)

#endif
