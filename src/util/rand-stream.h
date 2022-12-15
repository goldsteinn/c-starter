#ifndef SRC_D_UTIL_D_RAND_STREAM_H_
#define SRC_D_UTIL_D_RAND_STREAM_H_

#include "util/error-util.h"
#include "util/inline-math.h"
#include "util/memory-util.h"
#include "util/types.h"

typedef struct rand_stream {
    uint8_t * rbytes_;
    uint32_t  offset_;
    uint32_t  size_;
} rand_stream_t;

static void
rand_stream_init(rand_stream_t * rstream, uint32_t sz) {
    uint8_t * rbytes;
    sz               = ROUNDUP_P2(sz, 64UL);
    rstream->offset_ = 0;
    rstream->size_   = sz;
    rbytes           = (uint8_t *)safe_aligned_alloc(64, sz);
    rstream->rbytes_ = rbytes;

    randomize_buf(rbytes, sz);
}

static void
rand_stream_deinit(rand_stream_t * rstream) {
    safe_sfree(rstream->rbytes_, rstream->size_);
}

static void
rand_stream_read(rand_stream_t * restrict rstream,
                 void *   bufv,
                 uint32_t buf_sz) {
    uint8_t *buf, *rbytes;
    uint32_t off;
    uint32_t sz;
    if (buf_sz == 0) {
        return;
    }
    buf    = (uint8_t *)bufv;
    off    = rstream->offset_;
    sz     = rstream->size_;
    rbytes = rstream->rbytes_;

    die_assert(off < sz);

    if (UNLIKELY(buf_sz >= sz)) {
        randomize_buf(buf, buf_sz);
        return;
    }
    else if (LIKELY(buf_sz <= (sz - off))) {
        memcpy_c(buf, rbytes + off, buf_sz);
        off += buf_sz;

        if (UNLIKELY(off == sz)) {
            off = 0;
            randomize_buf(rbytes, sz);
        }
    }
    else {
        memcpy_c(buf, rbytes + off, (sz - off));
        buf_sz -= (sz - off);
        buf += (sz - off);
        randomize_buf(rbytes, sz);
        memcpy_c(buf, rbytes, buf_sz);
        off = buf_sz;
        die_assert(off < sz);
    }
    rstream->offset_ = off;
    return;
}


#endif
