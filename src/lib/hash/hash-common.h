#ifndef SRC_D_LIB_D_HASH_D_HASH_COMMON_H_
#define SRC_D_LIB_D_HASH_D_HASH_COMMON_H_

typedef struct str_hash32_result {
    const uint32_t hv_;
    const uint32_t slen_;
} str_hash32_result_t;

typedef struct str_hash64_result {
    const uint64_t hv_;
    const uint64_t slen_;
} str_hash64_result_t;

#endif
