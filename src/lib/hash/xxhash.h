#ifndef SRC_D_LIB_D_HASH_D_XXHASH_H_
#define SRC_D_LIB_D_HASH_D_XXHASH_H_

#include "hash-common.h"
#include "lib/string-custom.h"
#include "util/attrs.h"
#include "util/portability.h"


enum { I_xxseed = 0 };

#define xxhashT(input)             xxhashT_wseed(input, I_xxseed)
#define xxhashT_wseed(input, seed) xxhash_wseed(&(input), sizeof(input), seed)

#define XXH_INLINE_ALL
#if USING_LLVM
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wused-but-marked-unused"
# pragma clang diagnostic ignored "-Wc++17-attribute-extensions"
# pragma clang diagnostic ignored "-Wsign-conversion"
#else
# pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

#define XXH_VECTOR    XXH_SSE2
#define XXH_ACC_ALIGN 64
/* NOLINTBEGIN(portability-simd-intrinsics) */
#include "xxHash/xxhash.h"
/* NOLINTEND(portability-simd-intrinsics) */
static I_attr_pure uint64_t
xxhash_wseed(void const * input, uint64_t len, uint64_t seed) {
    return XXH3_64bits_withSeed(input, len, seed);
}

static I_attr_pure uint64_t
xxhash(void const * input, uint64_t len) {
    return xxhash_wseed(input, len, I_xxseed);
}

static I_attr_pure str_hash64_result_t
xxhash_str(char const * s) {
    uint64_t slen = strlen_c(s);
    return (str_hash64_result_t){ xxhash(s, slen), slen };
}

#if USING_LLVM
# pragma clang diagnostic pop
#else
# pragma GCC diagnostic pop
#endif

#endif
