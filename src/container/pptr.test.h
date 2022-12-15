#ifndef tr_pptr_as_pstr
# define tr_pptr_as_pstr 0
#endif

#if tr_pptr_as_pstr
# ifndef tr_base_t
#  define tr_base_t char
# endif

# ifndef tr_pptr_name
#  define tr_pptr_name I_cl_cat(pstr, tr_pptr_meta_bits)
# endif
#endif

#ifndef tr_pptr_meta_part_of_equality
# define tr_pptr_meta_part_of_equality tr_pptr_as_pstr
#endif

#ifndef tr_pptr_meta_part_of_sortability
# define tr_pptr_meta_part_of_sortability                                      \
        ((!(tr_pptr_as_pstr)) << ((tr_pptr_meta_bits)&1))
#endif


#define pptr_as_pstr                  tr_pptr_as_pstr
#define pptr_meta_bits                tr_pptr_meta_bits
#define pptr_base_t                   tr_base_t
#define pptr_meta_part_of_equality    tr_pptr_meta_part_of_equality
#define pptr_meta_part_of_sortability tr_pptr_meta_part_of_sortability
#define pptr_name                     tr_pptr_name
#include "pptr.h"


#define tr_pptr_namer(name) I_cl_namer(tr_pptr_name, name)


#define tr_K_pptr_meta_mask ((1 << (tr_pptr_meta_bits)) - 1)
#define tr_K_pstr_mlen_mask tr_K_pptr_meta_mask


#define tr_pptr_meta               tr_pptr_namer(meta)
#define tr_pptr_meta_cmp           tr_pptr_namer(meta_cmp)
#define tr_pptr_meta_clamp         tr_pptr_namer(meta_clamp)
#define tr_pptr_meta_mask          tr_pptr_namer(meta_mask)
#define tr_pptr_meta_set           tr_pptr_namer(meta_set)
#define tr_pptr_meta_sat_set       tr_pptr_namer(meta_sat_set)
#define tr_pptr_unsafe_meta_set    tr_pptr_namer(unsafe_meta_set)
#define tr_pptr_meta_plus          tr_pptr_namer(meta_plus)
#define tr_pptr_meta_minus         tr_pptr_namer(meta_minus)
#define tr_pptr_meta_sat_plus      tr_pptr_namer(meta_sat_plus)
#define tr_pptr_meta_sat_minus     tr_pptr_namer(meta_sat_minus)
#define tr_pptr_unsafe_meta_plus   tr_pptr_namer(unsafe_meta_plus)
#define tr_pptr_unsafe_meta_minus  tr_pptr_namer(unsafe_meta_minus)
#define tr_pptr_unsafe_meta_or     tr_pptr_namer(unsafe_meta_or)
#define tr_pptr_unsafe_meta_xor    tr_pptr_namer(unsafe_meta_xor)
#define tr_pptr_unsafe_meta_and    tr_pptr_namer(unsafe_meta_and)
#define tr_pptr_unsafe_meta_andn   tr_pptr_namer(unsafe_meta_andn)
#define tr_pptr_meta_or            tr_pptr_namer(meta_or)
#define tr_pptr_meta_xor           tr_pptr_namer(meta_xor)
#define tr_pptr_meta_and           tr_pptr_namer(meta_and)
#define tr_pptr_meta_andn          tr_pptr_namer(meta_andn)
#define tr_pptr_meta_lt            tr_pptr_namer(meta_lt)
#define tr_pptr_meta_gt            tr_pptr_namer(meta_gt)
#define tr_pptr_meta_eq            tr_pptr_namer(meta_eq)
#define tr_pptr_meta_ge            tr_pptr_namer(meta_ge)
#define tr_pptr_meta_le            tr_pptr_namer(meta_le)
#define tr_pptr_create             tr_pptr_namer(create)
#define tr_pptr_unsafe_create_meta tr_pptr_namer(unsafe_create_meta)
#define tr_pptr_sat_create_meta    tr_pptr_namer(sat_create_meta)
#define tr_pptr_create_meta        tr_pptr_namer(create_meta)
#define tr_pptr_ptr                tr_pptr_namer(ptr)
#define tr_pptr_ptr_set            tr_pptr_namer(ptr_set)
#define tr_pptr_is_null            tr_pptr_namer(is_null)
#define tr_pptr_agu                tr_pptr_namer(agu)
#define tr_pptr_agu_t              tr_pptr_namer(agu_t)
#define tr_pptr_lt                 tr_pptr_namer(lt)
#define tr_pptr_gt                 tr_pptr_namer(gt)
#define tr_pptr_eq                 tr_pptr_namer(eq)
#define tr_pptr_ge                 tr_pptr_namer(ge)
#define tr_pptr_le                 tr_pptr_namer(le)
#define tr_pptr_memcmpeq           tr_pptr_namer(memcmpeq)
#define tr_pptr_memcmp             tr_pptr_namer(memcmp)

#define tr_pstr_str              tr_pptr_namer(str)
#define tr_pstr_mlen             tr_pptr_namer(mlen)
#define tr_pstr_len_too_large    tr_pptr_namer(len_too_large)
#define tr_pstr_mlen_complete    tr_pptr_namer(mlen_complete)
#define tr_pstr_is_mlen_complete tr_pptr_namer(is_mlen_complete)
#define tr_pstr_mlen_set         tr_pptr_namer(mlen_set)
#define tr_pstr_mlen_plus        tr_pptr_namer(mlen_plus)
#define tr_pstr_mlen_minus       tr_pptr_namer(mlen_minus)
#define tr_pstr_mlen_cmp         tr_pptr_namer(mlen_cmp)
#define tr_pstr_mlen_lt          tr_pptr_namer(mlen_lt)
#define tr_pstr_mlen_gt          tr_pptr_namer(mlen_gt)
#define tr_pstr_mlen_eq          tr_pptr_namer(mlen_eq)
#define tr_pstr_mlen_ge          tr_pptr_namer(mlen_ge)
#define tr_pstr_mlen_le          tr_pptr_namer(mlen_le)
#define tr_pstr_len_clamp        tr_pptr_namer(len_clamp)
#define tr_pstr_len              tr_pptr_namer(len)
#define tr_pstr_create_len       tr_pptr_namer(create_len)
#define tr_pstr_create_str       tr_pptr_namer(create_str)
#define tr_pstr_refresh          tr_pptr_namer(refresh)
#define tr_pstr_strcmpeq         tr_pptr_namer(strcmpeq)
#define tr_pstr_strcmp           tr_pptr_namer(strcmp)


#define CMP_CMP(x, y)                                                          \
    ({                                                                         \
        int32_t I_tmp_x_ = (x);                                                \
        int32_t I_tmp_y_ = (y);                                                \
        !(((I_tmp_x_ < 0) == (I_tmp_y_ < 0)) &&                                \
          ((I_tmp_x_ == 0) == (I_tmp_y_ == 0)) &&                              \
          ((I_tmp_x_ > 0) == (I_tmp_y_ > 0)));                                 \
    })


static int32_t
tr_pptr_namer(pptr)(void) {
    enum { k_test_size = (1 << (tr_pptr_meta_bits + 1)) };
    enum { k_byte_size = k_test_size * sizeof(tr_base_t) };
    uint32_t    i, j, v, v_old;
    int32_t     cmp;
    tr_base_t * mem0      = (tr_base_t *)safe_zalloc(k_byte_size);
    tr_base_t * mem2      = (tr_base_t *)safe_zalloc(k_byte_size);
    tr_base_t * mem3      = (tr_base_t *)safe_zalloc(k_byte_size);
    uint8_t *   rand_ops  = make_true_rand8_buffer(k_test_size);
    uint32_t *  rand_vals = make_true_rand32_buffer(k_test_size);

    memset(mem0, 0, k_byte_size);
    memset(mem2, 1, k_byte_size);
    memset(mem3, 0, k_byte_size / 2);
    memset(mem3 + k_test_size / 2, 1, k_byte_size / 2);

    test_assert(memcmpeq_c(mem0, mem3, k_byte_size));
    for (i = 0; i < k_test_size; ++i) {
        pptr_t   pptr0, pptr1, pptr2, pptr3;
        uint32_t len;

        pptr0 = tr_pptr_create(mem0);
        test_assert(tr_pptr_meta(pptr0) == 0);
        pptr1 = tr_pptr_create_meta(mem0, 0);
        test_assert(pptr0 == pptr1);

        pptr1 = tr_pptr_unsafe_create_meta(mem0, i & tr_K_pptr_meta_mask);
        pptr0 = tr_pptr_unsafe_meta_set(pptr0, i & tr_K_pptr_meta_mask);
        test_assert(pptr0 == pptr1);
        test_assert(tr_pptr_meta(pptr0) == (i & tr_K_pptr_meta_mask));
        pptr0 = tr_pptr_meta_set(pptr0, i);
        test_assert(pptr0 == pptr1);

        pptr2 = tr_pptr_create_meta(mem2, i);
        test_assert(tr_pptr_meta(pptr2) == (i & tr_K_pptr_meta_mask));

        pptr3 = tr_pptr_create_meta(mem3, i);
        test_assert(tr_pptr_meta(pptr3) == (i & tr_K_pptr_meta_mask));

        pptr1 = tr_pptr_sat_create_meta(mem0, i);
        test_assert(tr_pptr_meta(pptr1) == tr_pptr_meta_clamp(i));
        test_assert(tr_pptr_meta(pptr1) ==
                    (i > tr_K_pptr_meta_mask ? tr_K_pptr_meta_mask : i));
        test_assert(tr_pptr_ptr(pptr1) == mem0);


        pptr1 = tr_pptr_meta_sat_plus(pptr1, tr_K_pptr_meta_mask / 2);
        test_assert(tr_pptr_meta(pptr1) ==
                    tr_pptr_meta_clamp(i + tr_K_pptr_meta_mask / 2));
        test_assert(tr_pptr_meta(pptr1) ==
                    ((i + tr_K_pptr_meta_mask / 2) > tr_K_pptr_meta_mask
                         ? tr_K_pptr_meta_mask
                         : (i + (tr_K_pptr_meta_mask / 2))));
        test_assert(tr_pptr_ptr(pptr1) == mem0);

        pptr1 = tr_pptr_sat_create_meta(mem0, i);
        pptr1 = tr_pptr_meta_sat_minus(pptr1, tr_K_pptr_meta_mask / 2);
        if (i <= tr_K_pptr_meta_mask / 2) {
            test_assert(tr_pptr_meta(pptr1) == 0);
        }
        else if (i <= tr_K_pptr_meta_mask) {
            test_assert(tr_pptr_meta(pptr1) == (i - tr_K_pptr_meta_mask / 2));
        }
        else {
            test_assert(tr_pptr_meta(pptr1) ==
                        tr_K_pptr_meta_mask - tr_K_pptr_meta_mask / 2);
        }

        test_assert(tr_pptr_ptr(pptr1) == mem0);

        pptr1 = tr_pptr_meta_set(pptr1, i);
        test_assert(pptr1 == pptr0);

        test_assert(tr_pptr_ptr(pptr0) == mem0);
        test_assert(tr_pptr_ptr(pptr1) == mem0);
        test_assert(tr_pptr_ptr(pptr2) == mem2);
        test_assert(tr_pptr_ptr(pptr3) == mem3);

        for (j = 0; j < 2; ++j) {
            len = j ? i : (uint32_t)k_byte_size;
            if (len == 0) {
                test_assert(!tr_pptr_memcmpeq(pptr0, pptr1, len));
                test_assert(!tr_pptr_memcmpeq(pptr0, pptr2, len));
                test_assert(!tr_pptr_memcmpeq(pptr0, pptr3, len));

                test_assert(!tr_pptr_memcmp(pptr0, pptr1, len));
                test_assert(!tr_pptr_memcmp(pptr0, pptr2, len));
                test_assert(!tr_pptr_memcmp(pptr0, pptr3, len));
            }
            else {
                test_assert(!tr_pptr_memcmpeq(pptr0, pptr1, len));
                test_assert(tr_pptr_memcmpeq(pptr0, pptr2, len));


                test_assert(!tr_pptr_memcmp(pptr0, pptr1, len));
                test_assert(tr_pptr_memcmp(pptr0, pptr2, len));
                test_assert(CMP_CMP(tr_pptr_memcmp(pptr0, pptr2, len),
                                    memcmp(tr_pptr_ptr(pptr0),
                                           tr_pptr_ptr(pptr2), len)) == 0);
                test_assert(CMP_CMP(tr_pptr_memcmp(pptr2, pptr0, len),
                                    memcmp(tr_pptr_ptr(pptr2),
                                           tr_pptr_ptr(pptr0), len)) == 0);

                if (len <= k_byte_size / 2) {
                    test_assert(!tr_pptr_memcmpeq(pptr0, pptr3, len));
                    test_assert(!tr_pptr_memcmp(pptr0, pptr3, len));
                }
                else {
                    test_assert(tr_pptr_meta_eq(pptr0, pptr3));
                    test_assert(tr_pptr_memcmpeq(pptr0, pptr3, len),
                                "%d vs %d (%u)\n",
                                tr_pptr_memcmpeq(pptr0, pptr3, len),
                                memcmpeq_c(mem0, mem3, len), len);
                    test_assert(tr_pptr_memcmp(pptr0, pptr3, len));
                    test_assert(CMP_CMP(tr_pptr_memcmp(pptr0, pptr3, len),
                                        memcmp(tr_pptr_ptr(pptr0),
                                               tr_pptr_ptr(pptr3), len)) == 0);

                    test_assert(CMP_CMP(tr_pptr_memcmp(pptr3, pptr0, len),
                                        memcmp(tr_pptr_ptr(pptr3),
                                               tr_pptr_ptr(pptr0), len)) == 0);
                }
            }

            pptr0 = tr_pptr_meta_set(pptr0, i + 1);
            test_assert(tr_pptr_meta(pptr0) == ((i + 1) & tr_K_pptr_meta_mask));
            test_assert(!tr_pptr_meta_eq(pptr0, pptr1), "%u (%x vs %x)\n",
                        tr_pptr_meta_bits, tr_pptr_meta(pptr0),
                        tr_pptr_meta(pptr1));
            test_assert(!tr_pptr_meta_eq(pptr0, pptr2));
            test_assert(!tr_pptr_meta_eq(pptr0, pptr3));
#if tr_pptr_meta_part_of_equality
            test_assert(tr_pptr_memcmpeq(pptr0, pptr1, len));
            test_assert(tr_pptr_memcmpeq(pptr0, pptr2, len));
            test_assert(tr_pptr_memcmpeq(pptr0, pptr3, len));


            test_assert(CMP_CMP(tr_pptr_memcmp(pptr0, pptr2, len),
                                memcmp(tr_pptr_ptr(pptr0), tr_pptr_ptr(pptr2),
                                       len)) == 0);
            test_assert(CMP_CMP(tr_pptr_memcmp(pptr0, pptr3, len),
                                memcmp(tr_pptr_ptr(pptr0), tr_pptr_ptr(pptr3),
                                       len)) == 0);
            test_assert(CMP_CMP(tr_pptr_memcmp(pptr2, pptr0, len),
                                memcmp(tr_pptr_ptr(pptr2), tr_pptr_ptr(pptr0),
                                       len)) == 0);
            test_assert(CMP_CMP(tr_pptr_memcmp(pptr3, pptr0, len),
                                memcmp(tr_pptr_ptr(pptr3), tr_pptr_ptr(pptr0),
                                       len)) == 0);
#else
            test_assert(!tr_pptr_memcmpeq(pptr0, pptr1, len));
            test_assert((!!tr_pptr_memcmpeq(pptr0, pptr2, len)) == (len != 0));
            test_assert((!!tr_pptr_memcmpeq(pptr0, pptr3, len)) ==
                        (len > k_byte_size / 2));
#endif

#if tr_pptr_meta_part_of_sortability
            cmp = ((i & tr_K_pptr_meta_mask) == tr_K_pptr_meta_mask ? -1 : 1);
# if tr_pptr_meta_part_of_sortability != 1
            cmp = -cmp;
# endif
            test_assert(CMP_CMP(tr_pptr_memcmp(pptr0, pptr1, len), cmp) == 0, "%d vs %d\n", tr_pptr_memcmp(pptr0, pptr1, len), cmp);
            test_assert(CMP_CMP(tr_pptr_memcmp(pptr0, pptr2, len), cmp) == 0);
            test_assert(CMP_CMP(tr_pptr_memcmp(pptr0, pptr3, len), cmp) == 0);
            cmp = -cmp;
            test_assert(CMP_CMP(tr_pptr_memcmp(pptr1, pptr0, len), cmp) == 0);
            test_assert(CMP_CMP(tr_pptr_memcmp(pptr2, pptr0, len), cmp) == 0);
            test_assert(CMP_CMP(tr_pptr_memcmp(pptr3, pptr0, len), cmp) == 0);

#else
            (void)(cmp);
            test_assert(tr_pptr_memcmp(pptr0, pptr1, len) == 0);
#endif
            pptr0 = tr_pptr_meta_set(pptr0, i);
            test_assert(tr_pptr_meta(pptr0) == (i & tr_K_pptr_meta_mask));
        }


        test_assert(!tr_pptr_meta_lt(pptr0, pptr1));
        test_assert(!tr_pptr_meta_gt(pptr0, pptr1));
        test_assert(tr_pptr_meta_le(pptr0, pptr1));
        test_assert(tr_pptr_meta_ge(pptr0, pptr1));
        test_assert(tr_pptr_meta_eq(pptr0, pptr1));
        v     = i;
        v_old = i & tr_K_pptr_meta_mask;
        for (j = 0; j < 123123112; j = (j < 132 ? j : ((j * 8) / 7)) + 1) {
            pptr0 = tr_pptr_meta_plus(pptr0, j);
            v += j;
            v &= tr_K_pptr_meta_mask;
            test_assert(tr_pptr_meta(pptr0) == v);

            test_assert(tr_pptr_meta_lt(pptr0, pptr1) == (v < v_old));
            test_assert(tr_pptr_meta_gt(pptr0, pptr1) == (v > v_old));
            test_assert(tr_pptr_meta_eq(pptr0, pptr1) == (v == v_old));
            test_assert(tr_pptr_meta_ge(pptr0, pptr1) == (v >= v_old));
            test_assert(tr_pptr_meta_le(pptr0, pptr1) == (v <= v_old));

            test_assert(tr_pptr_meta_lt(pptr3, pptr0) == (v_old < v));
            test_assert(tr_pptr_meta_gt(pptr3, pptr0) == (v_old > v));
            test_assert(tr_pptr_meta_eq(pptr3, pptr0) == (v_old == v));
            test_assert(tr_pptr_meta_ge(pptr3, pptr0) == (v_old >= v));
            test_assert(tr_pptr_meta_le(pptr3, pptr0) == (v_old <= v));
        }
        for (j = 0; j < 123123112; j = (j < 132 ? j : ((j * 8) / 7)) + 1) {
            pptr0 = tr_pptr_meta_minus(pptr0, j);
            v -= j;
            v &= tr_K_pptr_meta_mask;
            test_assert(tr_pptr_meta(pptr0) == v);

            test_assert(tr_pptr_meta_lt(pptr0, pptr1) == (v < v_old));
            test_assert(tr_pptr_meta_gt(pptr0, pptr1) == (v > v_old));
            test_assert(tr_pptr_meta_eq(pptr0, pptr1) == (v == v_old));
            test_assert(tr_pptr_meta_ge(pptr0, pptr1) == (v >= v_old));
            test_assert(tr_pptr_meta_le(pptr0, pptr1) == (v <= v_old));

            test_assert(tr_pptr_meta_lt(pptr2, pptr0) == (v_old < v));
            test_assert(tr_pptr_meta_gt(pptr2, pptr0) == (v_old > v));
            test_assert(tr_pptr_meta_eq(pptr2, pptr0) == (v_old == v));
            test_assert(tr_pptr_meta_ge(pptr2, pptr0) == (v_old >= v));
            test_assert(tr_pptr_meta_le(pptr2, pptr0) == (v_old <= v));

            test_assert(pptr0 == tr_pptr_unsafe_meta_minus(
                                     tr_pptr_unsafe_meta_plus(pptr0, j), j));
            test_assert(pptr0 == tr_pptr_unsafe_meta_plus(
                                     tr_pptr_unsafe_meta_minus(pptr0, j), j));
        }
        test_assert(tr_pptr_meta(pptr0) == v);
        test_assert(tr_pptr_meta(pptr0) == (i & tr_K_pptr_meta_mask));
        test_assert(pptr0 == pptr1);

        test_assert(tr_pptr_ptr(pptr0) == mem0);
        test_assert(tr_pptr_ptr(pptr1) == mem0);
        test_assert(tr_pptr_ptr(pptr2) == mem2);
        test_assert(tr_pptr_ptr(pptr3) == mem3);
        v     = i & tr_K_pptr_meta_mask;
        v_old = i & tr_K_pptr_meta_mask;
        for (j = 0;
             (i <= 512 || i == (rand_vals[i] % k_test_size)) && j < k_test_size;
             ++j) {
            uint8_t  rop = rand_ops[j];
            uint32_t rv  = rand_vals[j];
            test_assert(tr_pptr_meta(pptr0) == v);
            switch (rop & 7) {
                case 0:
                    v &= rv;
                    if (v & 8) {
                        rv &= tr_K_pptr_meta_mask;
                        pptr0 = tr_pptr_unsafe_meta_and(pptr0, rv);
                    }
                    else {
                        pptr0 = tr_pptr_meta_and(pptr0, rv);
                    }
                    break;
                case 1:
                    v ^= rv;
                    if (v & 8) {
                        rv &= tr_K_pptr_meta_mask;
                        pptr0 = tr_pptr_unsafe_meta_xor(pptr0, rv);
                    }
                    else {
                        pptr0 = tr_pptr_meta_xor(pptr0, rv);
                    }
                    break;
                case 2:
                    v |= rv;
                    if (v & 8) {
                        rv &= tr_K_pptr_meta_mask;
                        pptr0 = tr_pptr_unsafe_meta_or(pptr0, rv);
                    }
                    else {
                        pptr0 = tr_pptr_meta_or(pptr0, rv);
                    }
                    break;
                case 3:
                    v &= (~rv);
                    if (v & 8) {
                        rv &= tr_K_pptr_meta_mask;
                        pptr0 = tr_pptr_unsafe_meta_andn(pptr0, rv);
                    }
                    else {
                        pptr0 = tr_pptr_meta_andn(pptr0, rv);
                    }
                    break;
                case 5:
                    if (v & 8) {
                        v += (rv);
                        v &= tr_K_pptr_meta_mask;
                        pptr0 = tr_pptr_meta_plus(pptr0, rv);
                    }
                    else {
                        rv &= tr_K_pptr_meta_mask;
                        v += (rv);
                        if (v > tr_K_pptr_meta_mask) {
                            v = tr_K_pptr_meta_mask;
                        }
                        pptr0 = tr_pptr_meta_sat_plus(pptr0, rv);
                    }
                    break;
                case 6:
                    if (v & 8) {
                        v -= (rv);
                        v &= tr_K_pptr_meta_mask;
                        pptr0 = tr_pptr_meta_minus(pptr0, rv);
                    }
                    else {
                        rv &= tr_K_pptr_meta_mask;
                        if (v > rv) {
                            v -= rv;
                        }
                        else {
                            v = 0;
                        }
                        pptr0 = tr_pptr_meta_sat_minus(pptr0, rv);
                    }
                    break;
                case 7:
                    v = (rv);
                    if (v & 8) {
                        rv &= tr_K_pptr_meta_mask;
                        pptr0 = tr_pptr_unsafe_meta_set(pptr0, rv);
                    }
                    else {
                        pptr0 = tr_pptr_meta_set(pptr0, rv);
                    }
                    break;
            }
            v &= tr_K_pptr_meta_mask;
            test_assert(tr_pptr_ptr(pptr0) == mem0);
            test_assert(tr_pptr_meta(pptr0) == v);
            test_assert(tr_pptr_meta(pptr1) == v_old);

            test_assert(tr_pptr_meta_lt(pptr0, pptr1) == (v < v_old),
                        "%d != %d (%x vs %x // %x vs %x)\n",
                        tr_pptr_meta_lt(pptr0, pptr1), (v < v_old),
                        tr_pptr_meta(pptr0), tr_pptr_meta(pptr1), v, v_old);
            test_assert(tr_pptr_meta_gt(pptr0, pptr1) == (v > v_old));
            test_assert(tr_pptr_meta_eq(pptr0, pptr1) == (v == v_old));
            test_assert(tr_pptr_meta_ge(pptr0, pptr1) == (v >= v_old));
            test_assert(tr_pptr_meta_le(pptr0, pptr1) == (v <= v_old));

            test_assert(tr_pptr_meta_lt(pptr1, pptr0) == (v_old < v));
            test_assert(tr_pptr_meta_gt(pptr1, pptr0) == (v_old > v));
            test_assert(tr_pptr_meta_eq(pptr1, pptr0) == (v_old == v));
            test_assert(tr_pptr_meta_ge(pptr1, pptr0) == (v_old >= v));
            test_assert(tr_pptr_meta_le(pptr1, pptr0) == (v_old <= v));
#if tr_pptr_meta_part_of_equality
            test_assert((!!tr_pptr_memcmpeq(pptr0, pptr1, i)) ==
                        (!!(v - v_old)));
            test_assert((tr_pptr_memcmp(pptr0, pptr1, i)) == 0);
#endif
#if tr_pptr_meta_part_of_sortability

            cmp = (v_old < v ? -1 : (v != v_old));
# if tr_pptr_meta_part_of_sortability == 1
            cmp = -cmp;
# endif
            test_assert(CMP_CMP(tr_pptr_memcmp(pptr0, pptr1, i), cmp) == 0);
            test_assert(CMP_CMP(tr_pptr_memcmp(pptr1, pptr0, i), -cmp) == 0);
#endif
            test_assert(tr_pptr_meta(pptr0) == v);
        }
        test_assert(tr_pptr_meta(pptr0) == v);
        pptr0 = tr_pptr_meta_set(pptr0, tr_pptr_meta(pptr1));
        test_assert(pptr0 == pptr1);

        test_assert(tr_pptr_ptr(pptr0) == mem0);
        test_assert(tr_pptr_ptr(pptr1) == mem0);
        test_assert(tr_pptr_ptr(pptr2) == mem2);
        test_assert(tr_pptr_ptr(pptr3) == mem3);
    }


    safe_sfree(mem0, k_byte_size);
    safe_sfree(mem2, k_byte_size);
    safe_sfree(mem3, k_byte_size);
    safe_sfree(rand_ops, k_test_size);
    safe_sfree(rand_vals, k_test_size);
    return 0;
}
#if tr_pptr_as_pstr
static int32_t
tr_pptr_namer(pstr)(void) {
    enum { k_test_size = (1 << (tr_pptr_meta_bits + 1)) };
    uint32_t i;
    char *   s0 = (char *)safe_zalloc(k_test_size + 1);
    char *   s2 = (char *)safe_zalloc(k_test_size + 1);
    char *   s3 = (char *)safe_zalloc(k_test_size + 1);
    for (i = 0; i < k_test_size; ++i) {
        uint32_t j;
        pstr_t   pstr0, pstr1, pstr2, pstr3;
        test_assert(strlen(s0) == (size_t)i);
        test_assert(strlen(s2) == (size_t)i);
        test_assert(strlen(s3) == (size_t)i);
        pstr0 = tr_pstr_create_str(s0);
        pstr1 = tr_pstr_create_len(s0, i);
        pstr2 = tr_pstr_create_len(s2, i);
        pstr3 = tr_pstr_create_len(s3, i);

        test_assert(pstr0 == pstr1);
        test_assert(pstr2 != pstr3);
        test_assert(pstr2 != pstr1);
        test_assert(pstr1 != pstr3);

        test_assert(tr_pstr_len(pstr0) == i);
        test_assert(tr_pstr_len(pstr1) == i);
        test_assert(tr_pstr_len(pstr2) == i);
        test_assert(tr_pstr_len(pstr3) == i);

        test_assert(!tr_pstr_strcmp(pstr0, pstr1));
        test_assert(!tr_pstr_strcmpeq(pstr0, pstr1));

        test_assert((i != 0) == (!!tr_pstr_strcmp(pstr0, pstr2)));
        test_assert(CMP_CMP(tr_pstr_strcmp(pstr0, pstr2),
                            strcmp(tr_pstr_str(pstr0), tr_pstr_str(pstr2))) ==
                    0);
        test_assert(CMP_CMP(tr_pstr_strcmp(pstr2, pstr0),
                            strcmp(tr_pstr_str(pstr2), tr_pstr_str(pstr0))) ==
                    0);

        test_assert((i != 0) == (!!tr_pstr_strcmpeq(pstr0, pstr2)));

        if (i <= (k_test_size - (k_test_size >> 2))) {
            test_assert(!tr_pstr_strcmp(pstr0, pstr3));
            test_assert(!tr_pstr_strcmpeq(pstr0, pstr3));
        }
        else {
            test_assert(tr_pstr_strcmp(pstr0, pstr3));
            test_assert(tr_pstr_strcmpeq(pstr0, pstr3));
            test_assert(
                CMP_CMP(tr_pstr_strcmp(pstr0, pstr3),
                        strcmp(tr_pstr_str(pstr0), tr_pstr_str(pstr3))) == 0);
            test_assert(
                CMP_CMP(tr_pstr_strcmp(pstr3, pstr0),
                        strcmp(tr_pstr_str(pstr3), tr_pstr_str(pstr0))) == 0);
        }


        test_assert(tr_pstr_len_too_large(i) == (i > tr_K_pstr_mlen_mask));
        test_assert((tr_pstr_mlen(pstr0) == tr_K_pstr_mlen_mask) ==
                        (!tr_pstr_is_mlen_complete(pstr0)),
                    "%u\n", i);


        test_assert(
            i == tr_pstr_mlen(pstr0) ||
            (tr_pstr_len_too_large(i) && (!tr_pstr_is_mlen_complete(pstr0))));

        test_assert(tr_pstr_str(pstr0) == tr_pstr_str(pstr1));
        test_assert(tr_pstr_str(pstr0) == s0);
        test_assert(tr_pstr_str(pstr2) == s2);
        test_assert(tr_pstr_str(pstr3) == s3);

        pstr0 = tr_pstr_mlen_set(pstr0, 0);
        test_assert(tr_pstr_mlen(pstr0) == 0);
        pstr0 = tr_pstr_mlen_set(pstr0, 12312312313211231UL);
        test_assert(tr_pstr_mlen(pstr0) == tr_K_pstr_mlen_mask);
        test_assert(!tr_pstr_is_mlen_complete(pstr0));

        pstr0 = tr_pstr_mlen_set(pstr0, i);
        test_assert(pstr0 == pstr1);

        test_assert(!tr_pstr_mlen_lt(pstr0, pstr1));
        test_assert(!tr_pstr_mlen_gt(pstr0, pstr1));
        test_assert(tr_pstr_mlen_le(pstr0, pstr1));
        test_assert(tr_pstr_mlen_ge(pstr0, pstr1));
        test_assert(tr_pstr_mlen_eq(pstr0, pstr1));

        for (j = 0; j < 123123112; j = ((j * 8) / 7) + 1) {
            uint32_t ci          = (uint32_t)tr_pstr_len_clamp(i);
            uint32_t expec_plus  = (uint32_t)tr_pstr_len_clamp(j + i);
            uint32_t expec_minus = ci > j ? (ci - j) : 0;

            test_assert(expec_plus == tr_K_pstr_mlen_mask ||
                        (i + j) < tr_K_pstr_mlen_mask);

            pstr0 = tr_pstr_mlen_plus(pstr0, j);
            test_assert(expec_plus == tr_pstr_mlen(pstr0));
            test_assert(tr_pstr_str(pstr0) == s0);
            test_assert(tr_pstr_str(pstr0) == s0);
            if (i >= tr_K_pstr_mlen_mask || j == 0) {
                test_assert(pstr0 == pstr1);
                test_assert(!tr_pstr_mlen_lt(pstr0, pstr1));
                test_assert(!tr_pstr_mlen_gt(pstr0, pstr1));
                test_assert(tr_pstr_mlen_le(pstr0, pstr1));
                test_assert(tr_pstr_mlen_ge(pstr0, pstr1));
                test_assert(tr_pstr_mlen_eq(pstr0, pstr1));

                test_assert(expec_plus == tr_K_pstr_mlen_mask || j == 0);
            }
            else {
                test_assert(pstr0 != pstr1);
                test_assert(expec_plus > i, "%u vs %u\n", expec_plus, i);
                test_assert(!tr_pstr_mlen_lt(pstr0, pstr1), "%u/%u\n", i, j);
                test_assert(tr_pstr_mlen_gt(pstr0, pstr1));
                test_assert(!tr_pstr_mlen_le(pstr0, pstr1));
                test_assert(tr_pstr_mlen_ge(pstr0, pstr1));
                test_assert(!tr_pstr_mlen_eq(pstr0, pstr1));


                pstr0 = tr_pstr_mlen_minus(pstr0, expec_plus - i);

                test_assert(pstr0 == pstr1, "(%u / %u / %u): %u vs %u\n", i, j,
                            expec_plus, tr_pstr_mlen(pstr0),
                            tr_pstr_mlen(pstr1));
            }
            test_assert(tr_pstr_str(pstr0) == s0);
            test_assert(pstr0 == pstr1);

            pstr0 = tr_pstr_mlen_minus(pstr0, j);
            test_assert(tr_pstr_str(pstr0) == s0);
            test_assert(tr_pstr_mlen(pstr0) == expec_minus,
                        "(%u / %u): %u != %u\n", i, j, tr_pstr_mlen(pstr0),
                        expec_minus);

            test_assert(tr_pstr_str(pstr0) == s0);
            if (i == 0 || j == 0) {
                test_assert(pstr0 == pstr1);
                test_assert(!tr_pstr_mlen_lt(pstr0, pstr1));
                test_assert(!tr_pstr_mlen_gt(pstr0, pstr1));
                test_assert(tr_pstr_mlen_le(pstr0, pstr1));
                test_assert(tr_pstr_mlen_ge(pstr0, pstr1));
                test_assert(tr_pstr_mlen_eq(pstr0, pstr1));
                test_assert(expec_minus == i ||
                            expec_minus == tr_K_pstr_mlen_mask);
            }
            else {
                test_assert(pstr0 != pstr1);
                test_assert(tr_pstr_mlen_lt(pstr0, pstr1));
                test_assert(!tr_pstr_mlen_gt(pstr0, pstr1));
                test_assert(tr_pstr_mlen_le(pstr0, pstr1));
                test_assert(!tr_pstr_mlen_ge(pstr0, pstr1));
                test_assert(!tr_pstr_mlen_eq(pstr0, pstr1));

                test_assert(i >= expec_minus) pstr0 =
                    tr_pstr_mlen_plus(pstr0, i - expec_minus);
            }
            test_assert(pstr0 == pstr1);
        }

        s0[i] = 'a';
        test_assert(pstr0 == pstr1);
        pstr0 = tr_pstr_refresh(pstr0);
        test_assert(pstr0 != pstr1 || (i >= tr_K_pstr_mlen_mask));
        test_assert(pstr0 != pstr2);
        test_assert(pstr0 != pstr3);

        test_assert(tr_pstr_str(pstr0) == s0);

        test_assert(tr_pstr_strcmpeq(pstr0, pstr2));
        test_assert(tr_pstr_strcmpeq(pstr0, pstr3));

        test_assert(tr_pstr_strcmp(pstr0, pstr2));
        test_assert(tr_pstr_strcmp(pstr0, pstr3));

        test_assert(CMP_CMP(tr_pstr_strcmp(pstr0, pstr3),
                            strcmp(tr_pstr_str(pstr0), tr_pstr_str(pstr3))) ==
                    0);
        test_assert(CMP_CMP(tr_pstr_strcmp(pstr3, pstr0),
                            strcmp(tr_pstr_str(pstr3), tr_pstr_str(pstr0))) ==
                    0);

        test_assert(CMP_CMP(tr_pstr_strcmp(pstr0, pstr2),
                            strcmp(tr_pstr_str(pstr0), tr_pstr_str(pstr2))) ==
                    0);
        test_assert(CMP_CMP(tr_pstr_strcmp(pstr2, pstr0),
                            strcmp(tr_pstr_str(pstr2), tr_pstr_str(pstr0))) ==
                    0);


        s2[i] = 'b';
        s3[i] = (i < (k_test_size - (k_test_size >> 2))) ? 'a' : 'b';
    }
    safe_sfree(s0, k_test_size + 1);
    safe_sfree(s2, k_test_size + 1);
    safe_sfree(s3, k_test_size + 1);
    return 0;
}
#endif

static int32_t
tr_pptr_namer(runall)(void) {
    vprint("Running: %s\n", V_TO_STR(tr_pptr_name));
    test_assert(tr_pptr_namer(pptr)() == 0);
#if tr_pptr_as_pstr
    test_assert(tr_pptr_namer(pstr)() == 0);
#endif
    return 0;
}

#undef tr_pptr_as_pstr
#undef tr_pptr_meta_bits
#undef tr_pptr_meta_part_of_equality
#undef tr_pptr_meta_part_of_sortability
#undef tr_base_t
#undef tr_pptr_name
#undef pptr_as_pstr
#undef pptr_meta_bits
#undef pptr_base_t
#undef pptr_meta_part_of_equality
#undef pptr_meta_part_of_sortability
#undef pptr_name
#undef tr_pptr_namer
#undef tr_K_pptr_meta_mask
#undef tr_K_pstr_mlen_mask
#undef tr_pptr_meta
#undef tr_pptr_meta_cmp
#undef tr_pptr_meta_clamp
#undef tr_pptr_meta_mask
#undef tr_pptr_meta_set
#undef tr_pptr_meta_sat_set
#undef tr_pptr_unsafe_meta_set
#undef tr_pptr_meta_plus
#undef tr_pptr_meta_minus
#undef tr_pptr_meta_sat_plus
#undef tr_pptr_meta_sat_minus
#undef tr_pptr_unsafe_meta_plus
#undef tr_pptr_unsafe_meta_minus
#undef tr_pptr_unsafe_meta_or
#undef tr_pptr_unsafe_meta_xor
#undef tr_pptr_unsafe_meta_and
#undef tr_pptr_unsafe_meta_andn
#undef tr_pptr_meta_or
#undef tr_pptr_meta_xor
#undef tr_pptr_meta_and
#undef tr_pptr_meta_andn
#undef tr_pptr_meta_lt
#undef tr_pptr_meta_gt
#undef tr_pptr_meta_eq
#undef tr_pptr_meta_ge
#undef tr_pptr_meta_le
#undef tr_pptr_create
#undef tr_pptr_unsafe_create_meta
#undef tr_pptr_sat_create_meta
#undef tr_pptr_create_meta
#undef tr_pptr_ptr
#undef tr_pptr_ptr_set
#undef tr_pptr_is_null
#undef tr_pptr_agu
#undef tr_pptr_agu_t
#undef tr_pptr_lt
#undef tr_pptr_gt
#undef tr_pptr_eq
#undef tr_pptr_ge
#undef tr_pptr_le
#undef tr_pptr_memcmpeq
#undef tr_pptr_memcmp
#undef tr_pstr_str
#undef tr_pstr_mlen
#undef tr_pstr_len_too_large
#undef tr_pstr_mlen_complete
#undef tr_pstr_is_mlen_complete
#undef tr_pstr_mlen_set
#undef tr_pstr_mlen_plus
#undef tr_pstr_mlen_minus
#undef tr_pstr_mlen_cmp
#undef tr_pstr_mlen_lt
#undef tr_pstr_mlen_gt
#undef tr_pstr_mlen_eq
#undef tr_pstr_mlen_ge
#undef tr_pstr_mlen_le
#undef tr_pstr_len_clamp
#undef tr_pstr_len
#undef tr_pstr_create_len
#undef tr_pstr_create_str
#undef tr_pstr_refresh
#undef tr_pstr_strcmpeq
#undef tr_pstr_strcmp
#undef CMP_CMP
