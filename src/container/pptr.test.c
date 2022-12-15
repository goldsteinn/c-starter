#include "test/test-common.h"

#include "util/inline-math.h"
#include "util/memory-util.h"
#include "util/rand-stream.h"
#include "util/random.h"
#include "util/types.h"

#include "lib/hash/hash.h"


#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 16
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 15
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 14
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 13
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 12
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 11
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 10
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 9
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 8
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 7
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 6
#include "pptr.test.h"


#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 5
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 4
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 3
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 2
#include "pptr.test.h"

#define tr_pptr_as_pstr   1
#define tr_pptr_meta_bits 1
#include "pptr.test.h"

#define tr_base_t         uint64_t
#define tr_pptr_name      pptr16
#define tr_pptr_meta_bits 16
#include "pptr.test.h"

#define tr_base_t         uint32_t
#define tr_pptr_name      pptr15
#define tr_pptr_meta_bits 15
#include "pptr.test.h"

#define tr_base_t         uint16_t
#define tr_pptr_name      pptr14
#define tr_pptr_meta_bits 14
#include "pptr.test.h"

#define tr_base_t         uint8_t
#define tr_pptr_name      pptr13
#define tr_pptr_meta_bits 13
#include "pptr.test.h"

#define tr_base_t         int64_t
#define tr_pptr_name      pptr12
#define tr_pptr_meta_bits 12
#include "pptr.test.h"

#define tr_base_t         int32_t
#define tr_pptr_name      pptr11
#define tr_pptr_meta_bits 11
#include "pptr.test.h"

#define tr_base_t         int16_t
#define tr_pptr_name      pptr10
#define tr_pptr_meta_bits 10
#include "pptr.test.h"

#define tr_base_t         int8_t
#define tr_pptr_name      pptr9
#define tr_pptr_meta_bits 9
#include "pptr.test.h"

#define tr_base_t         double
#define tr_pptr_name      pptr8
#define tr_pptr_meta_bits 8
#include "pptr.test.h"

#define tr_base_t         float
#define tr_pptr_name      pptr7
#define tr_pptr_meta_bits 7
#include "pptr.test.h"

#define tr_base_t         bool_t
#define tr_pptr_name      pptr6
#define tr_pptr_meta_bits 6
#include "pptr.test.h"

#define tr_base_t         wchar_t
#define tr_pptr_name      pptr5
#define tr_pptr_meta_bits 5
#include "pptr.test.h"

#define tr_base_t         long_double
#define tr_pptr_name      pptr4
#define tr_pptr_meta_bits 4
#include "pptr.test.h"

#define tr_base_t         voidp
#define tr_pptr_name      pptr3
#define tr_pptr_meta_bits 3
#include "pptr.test.h"

#define tr_base_t         uintptr_t
#define tr_pptr_name      pptr2
#define tr_pptr_meta_bits 2
#include "pptr.test.h"

#define tr_base_t         size_t
#define tr_pptr_name      pptr1
#define tr_pptr_meta_bits 1
#include "pptr.test.h"


#define make_pstr_name(sz) CAT(pstr, sz)
#define make_pptr_name(sz) CAT(pptr, sz)
#define PPTR_SIZES         1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
#define PSTR_NAMES         APPLY(make_pstr_name, COMMA, PPTR_SIZES)
#define PPTR_NAMES         APPLY(make_pptr_name, COMMA, PPTR_SIZES)


#define run_test(name) test_assert(CAT(name, _runall)() == 0)


int32_t test_pptr(void);
int32_t
test_pptr(void) {
    APPLY(run_test, ;, PPTR_NAMES);
    APPLY(run_test, ;, PSTR_NAMES);
    return 0;
}
