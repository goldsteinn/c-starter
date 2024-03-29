#ifndef SRC_LIB_STRING_CUSTOM_H_
#define SRC_LIB_STRING_CUSTOM_H_

#include <stdint.h>
#include <string.h>

#include "util/attrs.h"
#include "util/common.h"
#include "util/types.h"

#define bcopy_c      bcopy
#define bzero_c      bzero
#define memccpy_c    memccpy
#define memchr_c     memchr
#define memcmp_c     memcmp
#define memcpy_c     memcpy
#define memmem_c     memmem
#define memmove_c    memmove
#define mempcpy_c    mempcpy
#define memset_c     memset
#define rawmemchr_c  rawmemchr
#define stpcpy_c     stpcpy
#define stpncpy_c    stpncpy
#define strcasecmp_c strcasecmp
#define strcasestr_c strcasestr
#define strcat_c     strcat
#define strchr_c     strchr
#define strchrnul_c  strchrnul
#define strcmp_c     strcmp
#define strcoll_c    strcoll
#define strcpy_c     strcpy
#define strcspn_c    strcspn
#define strdup_c     strdup
#define strerror_c   strerror
#define strlen_c     strlen
#define strncat_c    strncat
#define strncmp_c    strncmp
#define strncpy_c    strncpy
#define strndup_c    strndup
#define strnlen_c    strnlen
#define strpbrk_c    strpbrk
#define strrchr_c    strrchr
#define strsep_c     strsep
#define strspn_c     strspn
#define strstr_c     strstr
#define strtok_c     strtok
#define strtok_r_c   strtok_r
#define strverscmp_c strverscmp
#define strxfrm_c    strxfrm
#define wcpcpy_c     wcpcpy
#define wcpncpy_c    wcpncpy
#define wcscasecmp_c wcscasecmp
#define wcscat_c     wcscat
#define wcschr_c     wcschr
#define wcscmp_c     wcscmp
#define wcscpy_c     wcscpy
#define wcscspn_c    wcscspn
#define wcsdup_c     wcsdup
#define wcslen_c     wcslen
#define wcsncat_c    wcsncat
#define wcsncmp_c    wcsncmp
#define wcsncpy_c    wcsncpy
#define wcsnlen_c    wcsnlen
#define wcspbrk_c    wcspbrk
#define wcsrchr_c    wcsrchr
#define wcsspn_c     wcsspn
#define wcsstr_c     wcsstr
#define wcstok_c     wcstok
#define wmemchr_c    wmemchr
#define wmemcmp_c    wmemcmp
#define wmemcpy_c    wmemcpy
#define wmemmove_c   wmemmove
#define wmempcpy_c   wmempcpy
#define wmemset_c    wmemset

static ALWAYS_INLINE bool_t
memcmpeq_c(void const * s1, void const * s2, size_t n) {
#if I_glibc_version_ge(2, 35)
    if (const_condition(n <= 64)) {
        return !!memcmp(s1, s2, n);
    }
    return !!__memcmpeq(s1, s2, n);
#else
    return !!memcmp(s1, s2, n);
#endif
}

static ALWAYS_INLINE bool_t
strcmpeq_c(char const * s1, char const * s2) {
    return !!strcmp(s1, s2);
}

static ALWAYS_INLINE bool_t
strncmpeq_c(char const * s1, char const * s2, size_t n) {
    return !!strncmp(s1, s2, n);
}


#endif
