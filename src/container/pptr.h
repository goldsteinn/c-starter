#include "cl-defs.h"

#ifndef PPTR_COMMON
# define PPTR_COMMON
typedef uintptr_t pptr_t;
#endif


#ifndef pptr_meta_bits
# define pptr_meta_bits 16
#endif


#ifndef pptr_as_pstr
# define pptr_as_pstr 0
#endif


#ifndef pptr_base_t
# if pptr_as_pstr
#  define pptr_base_t char
# else
#  error "Missing 'pptr_base_t'"
# endif
#endif


#ifndef pptr_meta_bits
# define pptr_meta_bits 16
#endif

#if pptr_as_pstr
# undef pptr_meta_part_of_equality
# undef pptr_meta_part_of_sortability
# define pptr_meta_part_of_equality    1
# define pptr_meta_part_of_sortability 0
#endif

#ifndef pptr_meta_part_of_equality
# define pptr_meta_part_of_equality 0
#endif


#ifndef pptr_meta_part_of_sortability
# define pptr_meta_part_of_sortability 0
#endif


#ifndef pptr_name
# if pptr_as_pstr
#  define pptr_name I_cl_cat(pstr, pptr_meta_bits)
# else
#  define pptr_name I_cl_cat(p_, pptr_base_t)
# endif
#endif


#define pptr_namer(name) I_cl_namer(pptr_name, name)


I_cl_static_assert((pptr_meta_bits) > 0 &&
                   (pptr_meta_bits) < I_cl_sizeof_bits(void *));


enum { pptr_namer(K_meta_bits) = (pptr_meta_bits) };
#define K_pptr_meta_bits pptr_namer(K_meta_bits)
enum { pptr_namer(K_ptr_bits) = I_cl_sizeof_bits(void *) - K_pptr_meta_bits };
#define K_pptr_ptr_bits pptr_namer(K_ptr_bits)
enum { pptr_namer(K_meta_mask) = (1 << K_pptr_meta_bits) - 1 };
#define K_pptr_meta_mask pptr_namer(K_meta_mask)
/* Allow enum exceeding int capacity.  */
#if I_cl_USING_LLVM
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wpedantic"
#endif
enum {
    pptr_namer(K_ptr_mask) = ((1UL << K_pptr_ptr_bits) - 1) << K_pptr_meta_bits
};
#if I_cl_USING_LLVM
# pragma clang diagnostic pop
#endif
#define K_pptr_ptr_mask pptr_namer(K_ptr_mask)

#define pptr_meta_pass_t uintptr_t
typedef I_cl_choose_T(K_pptr_meta_bits < 32, uint32_t, pptr_meta_pass_t)
    pptr_namer(meta_cmp_t);
#define pptr_meta_cmp_t pptr_namer(meta_cmp_t)
#define pptr_meta_ret_t pptr_meta_cmp_t

#define pptr_meta               pptr_namer(meta)
#define pptr_meta_clamp         pptr_namer(meta_clamp)
#define pptr_meta_mask          pptr_namer(meta_mask)
#define pptr_meta_set           pptr_namer(meta_set)
#define pptr_meta_sat_set       pptr_namer(meta_sat_set)
#define pptr_unsafe_meta_set    pptr_namer(unsafe_meta_set)
#define pptr_meta_plus          pptr_namer(meta_plus)
#define pptr_meta_minus         pptr_namer(meta_minus)
#define pptr_meta_sat_plus      pptr_namer(meta_sat_plus)
#define pptr_meta_sat_minus     pptr_namer(meta_sat_minus)
#define pptr_unsafe_meta_plus   pptr_namer(unsafe_meta_plus)
#define pptr_unsafe_meta_minus  pptr_namer(unsafe_meta_minus)
#define pptr_unsafe_meta_or     pptr_namer(unsafe_meta_or)
#define pptr_unsafe_meta_xor    pptr_namer(unsafe_meta_xor)
#define pptr_unsafe_meta_and    pptr_namer(unsafe_meta_and)
#define pptr_unsafe_meta_andn   pptr_namer(unsafe_meta_andn)
#define pptr_meta_or            pptr_namer(meta_or)
#define pptr_meta_xor           pptr_namer(meta_xor)
#define pptr_meta_and           pptr_namer(meta_and)
#define pptr_meta_andn          pptr_namer(meta_andn)
#define pptr_meta_lt            pptr_namer(meta_lt)
#define pptr_meta_gt            pptr_namer(meta_gt)
#define pptr_meta_eq            pptr_namer(meta_eq)
#define pptr_meta_ge            pptr_namer(meta_ge)
#define pptr_meta_le            pptr_namer(meta_le)
#define pptr_create             pptr_namer(create)
#define pptr_unsafe_create_meta pptr_namer(unsafe_create_meta)
#define pptr_sat_create_meta    pptr_namer(sat_create_meta)
#define pptr_create_meta        pptr_namer(create_meta)
#define pptr_ptr                pptr_namer(ptr)
#define pptr_ptr_set            pptr_namer(ptr_set)
#define pptr_is_null            pptr_namer(is_null)
#define pptr_agu                pptr_namer(agu)
#define pptr_agu_t              pptr_namer(agu_t)
#define pptr_lt                 pptr_namer(lt)
#define pptr_gt                 pptr_namer(gt)
#define pptr_eq                 pptr_namer(eq)
#define pptr_ge                 pptr_namer(ge)
#define pptr_le                 pptr_namer(le)
#define pptr_memcmpeq           pptr_namer(memcmpeq)
#define pptr_memcmp             pptr_namer(memcmp)


I_cl_cattrs pptr_meta_ret_t
pptr_meta(pptr_t pptr) {
    return pptr & K_pptr_meta_mask;
}


I_cl_cattrs pptr_meta_pass_t
pptr_meta_clamp(pptr_meta_pass_t meta) {
    return I_cl_min(meta, (pptr_meta_pass_t)K_pptr_meta_mask);
}

I_cl_cattrs pptr_meta_pass_t
pptr_meta_mask(pptr_meta_pass_t meta) {
    return meta & K_pptr_meta_mask;
}

I_cl_cattrs pptr_t
pptr_meta_set(pptr_t pptr, pptr_meta_pass_t meta) {
    return (pptr & (K_pptr_ptr_mask)) | pptr_meta_mask(meta);
}

I_cl_cattrs pptr_t
pptr_meta_sat_set(pptr_t pptr, pptr_meta_pass_t meta) {
    return (pptr & (K_pptr_ptr_mask)) | pptr_meta_clamp(meta);
}

I_cl_cattrs pptr_t
pptr_unsafe_meta_set(pptr_t pptr, pptr_meta_pass_t meta) {
    return (pptr & (K_pptr_ptr_mask)) | meta;
}


I_cl_cattrs pptr_t
pptr_meta_plus(pptr_t pptr, pptr_meta_pass_t meta) {
    meta += pptr_meta(pptr);
    return pptr_meta_set(pptr, pptr_meta_mask(meta));
}


I_cl_cattrs pptr_t
pptr_meta_minus(pptr_t pptr, pptr_meta_pass_t meta) {
    meta = pptr_meta(pptr) - meta;
    return pptr_meta_set(pptr, pptr_meta_mask(meta));
}

I_cl_cattrs pptr_t
pptr_meta_sat_plus(pptr_t pptr, pptr_meta_pass_t meta) {
    meta += pptr_meta(pptr);
    return pptr_meta_set(pptr, pptr_meta_clamp(meta));
}


I_cl_cattrs pptr_t
pptr_meta_sat_minus(pptr_t pptr, pptr_meta_pass_t meta) {
    pptr_meta_pass_t cur = pptr_meta(pptr);
    cur                  = I_cl_signbit(cur - meta) ? 0 : (cur - meta);
    return pptr_meta_set(pptr, cur);
}


I_cl_cattrs pptr_t
pptr_unsafe_meta_plus(pptr_t pptr, pptr_meta_pass_t meta) {
    return pptr + meta;
}


I_cl_cattrs pptr_t
pptr_unsafe_meta_minus(pptr_t pptr, pptr_meta_pass_t meta) {
    return pptr - meta;
}


I_cl_cattrs pptr_t
pptr_unsafe_meta_or(pptr_t pptr, pptr_meta_pass_t meta) {
    return pptr | meta;
}


I_cl_cattrs pptr_t
pptr_unsafe_meta_xor(pptr_t pptr, pptr_meta_pass_t meta) {
    return pptr ^ meta;
}


I_cl_cattrs pptr_t
pptr_unsafe_meta_and(pptr_t pptr, pptr_meta_pass_t meta) {
    return pptr & (meta | K_pptr_ptr_mask);
}


I_cl_cattrs pptr_t
pptr_unsafe_meta_andn(pptr_t pptr, pptr_meta_pass_t meta) {
    pptr_t pp_meta = meta;
    return pptr & (~pp_meta);
}

I_cl_cattrs pptr_t
pptr_meta_or(pptr_t pptr, pptr_meta_pass_t meta) {
    return pptr_unsafe_meta_or(pptr, pptr_meta_mask(meta));
}


I_cl_cattrs pptr_t
pptr_meta_xor(pptr_t pptr, pptr_meta_pass_t meta) {
    return pptr_unsafe_meta_xor(pptr, pptr_meta_mask(meta));
}


I_cl_cattrs pptr_t
pptr_meta_and(pptr_t pptr, pptr_meta_pass_t meta) {
    return pptr_unsafe_meta_and(pptr, meta);
}


I_cl_cattrs pptr_t
pptr_meta_andn(pptr_t pptr, pptr_meta_pass_t meta) {
    pptr_t pp_meta = meta;
    return pptr_unsafe_meta_andn(pptr, pptr_meta_mask(pp_meta));
}


I_cl_cattrs I_cl_bool_t
pptr_meta_lt(pptr_t lhs, pptr_t rhs) {
    return pptr_meta(lhs) < pptr_meta(rhs);
}


I_cl_cattrs I_cl_bool_t
pptr_meta_gt(pptr_t lhs, pptr_t rhs) {
    return pptr_meta(lhs) > pptr_meta(rhs);
}


I_cl_cattrs I_cl_bool_t
pptr_meta_eq(pptr_t lhs, pptr_t rhs) {
    return ((lhs - rhs) & K_pptr_meta_mask) == 0;
}


I_cl_cattrs I_cl_bool_t
pptr_meta_ge(pptr_t lhs, pptr_t rhs) {
    return !pptr_meta_lt(lhs, rhs);
}

I_cl_cattrs I_cl_bool_t
pptr_meta_le(pptr_t lhs, pptr_t rhs) {
    return !pptr_meta_gt(lhs, rhs);
}


I_cl_cattrs pptr_t
pptr_create(pptr_base_t const * ptr) {
    pptr_t pptr = (pptr_t)ptr;
    return pptr << K_pptr_meta_bits;
}

I_cl_cattrs pptr_t
pptr_unsafe_create_meta(pptr_base_t const * ptr, pptr_meta_pass_t meta) {
    return pptr_create(ptr) | meta;
}


I_cl_cattrs pptr_t
pptr_sat_create_meta(pptr_base_t const * ptr, pptr_meta_pass_t meta) {
    return pptr_unsafe_create_meta(ptr, pptr_meta_clamp(meta));
}


I_cl_cattrs pptr_t
pptr_create_meta(pptr_base_t const * ptr, pptr_meta_pass_t meta) {
    return pptr_unsafe_create_meta(ptr, pptr_meta_mask(meta));
}


I_cl_cattrs pptr_base_t *
pptr_ptr(pptr_t pptr) {
    return (pptr_base_t *)(pptr >> K_pptr_meta_bits);
}


I_cl_cattrs pptr_t
pptr_ptr_set(pptr_t pptr, pptr_base_t const * ptr) {
    return pptr_create_meta(ptr, pptr_meta(pptr));
}


I_cl_cattrs I_cl_bool_t
pptr_is_null(pptr_t pptr) {
    return pptr_ptr(pptr) == 0;
}


I_cl_cattrs pptr_t
pptr_agu(pptr_t pptr, uintptr_t offset) {
    return pptr + (offset << K_pptr_meta_bits);
}


I_cl_cattrs pptr_t
pptr_agu_t(pptr_t pptr, uintptr_t offset) {
    return pptr + sizeof(pptr_base_t) * (offset << K_pptr_meta_bits);
}


I_cl_cattrs I_cl_bool_t
pptr_lt(pptr_t lhs, pptr_t rhs) {
    return (lhs | K_pptr_meta_mask) < (rhs | K_pptr_meta_mask);
}


I_cl_cattrs I_cl_bool_t
pptr_gt(pptr_t lhs, pptr_t rhs) {
    return (lhs | K_pptr_meta_mask) > (rhs | K_pptr_meta_mask);
}


I_cl_cattrs I_cl_bool_t
pptr_eq(pptr_t lhs, pptr_t rhs) {
    return pptr_is_null(lhs ^ rhs);
}


I_cl_cattrs I_cl_bool_t
pptr_ge(pptr_t lhs, pptr_t rhs) {
    return !pptr_lt(lhs, rhs);
}


I_cl_cattrs I_cl_bool_t
pptr_le(pptr_t lhs, pptr_t rhs) {
    return !pptr_gt(lhs, rhs);
}


I_cl_pattrs I_cl_bool_t
pptr_memcmpeq(pptr_t lhs, pptr_t rhs, size_t sz) {
#if pptr_meta_part_of_equality
    pptr_meta_pass_t meta_res = (lhs - rhs) & K_pptr_meta_mask;
    if (meta_res) {
        return !!meta_res;
    }
#endif
    return !!memcmpeq_c(pptr_ptr(lhs), pptr_ptr(rhs), sz);
}


I_cl_pattrs int32_t
pptr_memcmp(pptr_t lhs, pptr_t rhs, size_t sz) {
#if pptr_meta_part_of_sortability
    pptr_meta_cmp_t lhs_meta, rhs_meta;
    lhs_meta = (pptr_meta_cmp_t)pptr_meta(lhs);
    rhs_meta = (pptr_meta_cmp_t)pptr_meta(rhs);
    if (rhs_meta - lhs_meta) {
# if pptr_meta_part_of_sortability == 1
        return I_cl_choose_expr(K_pptr_meta_bits < 32,
                                (int32_t)(lhs_meta - rhs_meta),
                                lhs_meta < rhs_meta ? (-1) : (1));
# else
        return I_cl_choose_expr(K_pptr_meta_bits < 32,
                                (int32_t)(rhs_meta - lhs_meta),
                                lhs_meta < rhs_meta ? (1) : (-1));
# endif
    }
#endif
    return memcmp_c(pptr_ptr(lhs), pptr_ptr(rhs), sz);
}

#if pptr_as_pstr

# ifndef PSTR_COMMON
#  define PSTR_COMMON
typedef pptr_t pstr_t;
# endif

# define pstr_str              pptr_namer(str)
# define pstr_mlen             pptr_namer(mlen)
# define pstr_len_too_large    pptr_namer(len_too_large)
# define pstr_mlen_complete    pptr_namer(mlen_complete)
# define pstr_is_mlen_complete pptr_namer(is_mlen_complete)
# define pstr_mlen_set         pptr_namer(mlen_set)
# define pstr_mlen_plus        pptr_namer(mlen_plus)
# define pstr_mlen_minus       pptr_namer(mlen_minus)
# define pstr_mlen_lt          pptr_namer(mlen_lt)
# define pstr_mlen_gt          pptr_namer(mlen_gt)
# define pstr_mlen_eq          pptr_namer(mlen_eq)
# define pstr_mlen_ge          pptr_namer(mlen_ge)
# define pstr_mlen_le          pptr_namer(mlen_le)
# define pstr_len_clamp        pptr_namer(len_clamp)
# define pstr_len              pptr_namer(len)
# define pstr_create_len       pptr_namer(create_len)
# define pstr_create_str       pptr_namer(create_str)
# define pstr_refresh          pptr_namer(refresh)
# define pstr_strcmpeq         pptr_namer(strcmpeq)
# define pstr_strcmp           pptr_namer(strcmp)

# define K_pstr_mlen_mask K_pptr_meta_mask
# define pstr_mlen_pass_t pptr_meta_pass_t

I_cl_cattrs pptr_base_t *
pstr_str(pstr_t pstr) {
    return pptr_ptr(pstr);
}

I_cl_cattrs pptr_meta_ret_t
pstr_mlen(pstr_t pstr) {
    return pptr_meta(pstr);
}

I_cl_cattrs I_cl_bool_t
pstr_len_too_large(pstr_mlen_pass_t len) {
    return len > K_pstr_mlen_mask;
}

I_cl_cattrs I_cl_bool_t
pstr_mlen_complete(pstr_mlen_pass_t mlen) {
    return mlen != K_pstr_mlen_mask;
}

I_cl_cattrs I_cl_bool_t
pstr_is_mlen_complete(pstr_t pstr) {
    return pstr_mlen_complete(pstr_mlen(pstr));
}

I_cl_cattrs pstr_t
pstr_mlen_set(pstr_t pstr, pstr_mlen_pass_t mlen) {
    return pptr_meta_sat_set(pstr, mlen);
}

I_cl_cattrs pstr_t
pstr_mlen_plus(pstr_t pstr, pstr_mlen_pass_t len) {
    return pptr_meta_sat_plus(pstr, len);
}

I_cl_cattrs pstr_t
pstr_mlen_minus(pstr_t pstr, pstr_mlen_pass_t len) {
    return pptr_meta_sat_minus(pstr, len);
}

I_cl_cattrs I_cl_bool_t
pstr_mlen_lt(pstr_t lhs, pstr_t rhs) {
    return pptr_meta_lt(lhs, rhs);
}

I_cl_cattrs I_cl_bool_t
pstr_mlen_gt(pstr_t lhs, pstr_t rhs) {
    return pptr_meta_gt(lhs, rhs);
}


I_cl_cattrs I_cl_bool_t
pstr_mlen_eq(pstr_t lhs, pstr_t rhs) {
    return pptr_meta_eq(lhs, rhs);
}


I_cl_cattrs I_cl_bool_t
pstr_mlen_ge(pstr_t lhs, pstr_t rhs) {
    return pptr_meta_ge(lhs, rhs);
}

I_cl_cattrs I_cl_bool_t
pstr_mlen_le(pstr_t lhs, pstr_t rhs) {
    return pptr_meta_le(lhs, rhs);
}

I_cl_cattrs pstr_mlen_pass_t
pstr_len_clamp(pstr_mlen_pass_t len) {
    return pptr_meta_clamp(len);
}

I_cl_cattrs pstr_t
pstr_len(pstr_t pstr) {
    pstr_mlen_pass_t len = pstr_mlen(pstr);
    if (I_cl_unlikely(!pstr_mlen_complete(len))) {
        len += strlen_c(pstr_str(pstr) + len);
    }
    return len;
}

I_cl_cattrs pptr_t
pstr_create_len(pptr_base_t const * ptr, pstr_mlen_pass_t len) {
    return pptr_sat_create_meta(ptr, len);
}

I_cl_pattrs pstr_t
pstr_create_str(pptr_base_t const * ptr) {
    return pstr_create_len(ptr, strlen_c(ptr));
}

I_cl_pattrs pstr_t
pstr_refresh(pstr_t pstr) {
    return pstr_create_str(pstr_str(pstr));
}


I_cl_pattrs I_cl_bool_t
pstr_strcmpeq(pstr_t lhs, pstr_t rhs) {
    pstr_mlen_pass_t lhs_mlen, rhs_mlen;
    char const *     lhs_p;
    char const *     rhs_p;
    I_cl_bool_t      res;

    lhs_mlen = pstr_mlen(lhs);
    rhs_mlen = pstr_mlen(rhs);

    res = !!(lhs_mlen - rhs_mlen);
    if (res) {
        return res;
    }
    lhs_p = pstr_str(lhs);
    rhs_p = pstr_str(rhs);

    res = !!memcmpeq_c(lhs_p, rhs_p, lhs_mlen);
    if (res) {
        return res;
    }
    if (pstr_mlen_complete(lhs_mlen)) {
        return 0;
    }
    return !!strcmpeq_c(lhs_p + K_pstr_mlen_mask, rhs_p + K_pstr_mlen_mask);
}


I_cl_pattrs int32_t
pstr_strcmp(pstr_t lhs, pstr_t rhs) {
    pstr_mlen_pass_t lhs_mlen, rhs_mlen;
    char const *     lhs_p;
    char const *     rhs_p;
    int32_t          res;

    lhs_mlen = pstr_mlen(lhs);
    rhs_mlen = pstr_mlen(rhs);

    lhs_p = pstr_str(lhs);
    rhs_p = pstr_str(rhs);

    if (lhs_mlen == rhs_mlen) {
        res = memcmp_c(lhs_p, rhs_p, lhs_mlen);
        if (res) {
            return res;
        }
        if (pstr_mlen_complete(lhs_mlen)) {
            return 0;
        }
        return strcmp_c(lhs_p + K_pstr_mlen_mask, rhs_p + K_pstr_mlen_mask);
    }
    return memcmp_c(lhs_p, rhs_p, I_cl_min(lhs_mlen, rhs_mlen) + 1);
}

# undef pstr_str
# undef pstr_mlen
# undef pstr_len_too_large
# undef pstr_mlen_complete
# undef pstr_is_mlen_complete
# undef pstr_mlen_set
# undef pstr_mlen_plus
# undef pstr_mlen_minus
# undef pstr_mlen_lt
# undef pstr_mlen_gt
# undef pstr_mlen_eq
# undef pstr_mlen_ge
# undef pstr_mlen_le
# undef pstr_len_clamp
# undef pstr_len
# undef pstr_create_len
# undef pstr_create_str
# undef pstr_refresh
# undef pstr_strcmpeq
# undef pstr_strcmp
# undef K_pstr_mlen_mask
# undef pstr_mlen_pass_t

#endif

#undef pptr_meta_bits
#undef pptr_as_pstr
#undef pptr_base_t
#undef pptr_meta_bits
#undef pptr_meta_part_of_equality
#undef pptr_meta_part_of_sortability
#undef pptr_name
#undef pptr_name
#undef pptr_namer
#undef K_pptr_meta_bits
#undef K_pptr_ptr_bits
#undef K_pptr_meta_mask
#undef K_pptr_ptr_mask
#undef pptr_meta_pass_t
#undef pptr_meta_cmp_t
#undef pptr_meta_ret_t

#undef pptr_meta
#undef pptr_meta_clamp
#undef pptr_meta_mask
#undef pptr_meta_set
#undef pptr_meta_sat_set
#undef pptr_unsafe_meta_set
#undef pptr_meta_plus
#undef pptr_meta_minus
#undef pptr_meta_sat_plus
#undef pptr_meta_sat_minus
#undef pptr_unsafe_meta_plus
#undef pptr_unsafe_meta_minus
#undef pptr_unsafe_meta_or
#undef pptr_unsafe_meta_xor
#undef pptr_unsafe_meta_and
#undef pptr_unsafe_meta_andn
#undef pptr_meta_or
#undef pptr_meta_xor
#undef pptr_meta_and
#undef pptr_meta_andn
#undef pptr_meta_lt
#undef pptr_meta_gt
#undef pptr_meta_eq
#undef pptr_meta_ge
#undef pptr_meta_le
#undef pptr_create
#undef pptr_unsafe_create_meta
#undef pptr_sat_create_meta
#undef pptr_create_meta
#undef pptr_ptr
#undef pptr_ptr_set
#undef pptr_is_null
#undef pptr_agu
#undef pptr_agu_t
#undef pptr_lt
#undef pptr_gt
#undef pptr_eq
#undef pptr_ge
#undef pptr_le
#undef pptr_memcmpeq
#undef pptr_memcmp
