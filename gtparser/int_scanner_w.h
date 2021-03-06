#ifndef INT_SCANNER_W_H_INCLUDED
#define INT_SCANNER_W_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_scanner_w.h */

#include "gtparser/gtparser.h"

#ifndef INT64_TYPE
#define INT64_TYPE long long
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* input:  s points to [0-9] */
/* return: pointer to non-[0-9], may be to end */
/* returns NULL on integer overflow */
GTPARSER_EXPORTS const wchar_t *gt_scan_uint_w(const wchar_t *s/*<end*/, const wchar_t *const end, unsigned *number/*out*/);
GTPARSER_EXPORTS const wchar_t *gt_scan_uint64_w(const wchar_t *s/*<end*/, const wchar_t *const end, unsigned INT64_TYPE *number/*out*/);

/* input:  s points to [0-9a-fA-F] */
/* return: pointer to non-[0-9a-fA-F], may be to end */
/* returns NULL on integer overflow */
GTPARSER_EXPORTS const wchar_t *gt_scan_hex_w(const wchar_t *s/*<end*/, const wchar_t *const end, unsigned *number/*out*/);
GTPARSER_EXPORTS const wchar_t *gt_scan_hex64_w(const wchar_t *s/*<end*/, const wchar_t *const end, unsigned INT64_TYPE *number/*out*/);

/* input:  s points to [0-9] */
/* return: pointer to non-[0-9], may be to '\0' */
/* returns NULL on integer overflow */
GTPARSER_EXPORTS const wchar_t *gt_scan_uint_w_z(const wchar_t *s/*'\0'-terminated*/, unsigned *number/*out*/);
GTPARSER_EXPORTS const wchar_t *gt_scan_uint64_w_z(const wchar_t *s/*'\0'-terminated*/, unsigned INT64_TYPE *number/*out*/);

/* input:  s points to [0-9a-fA-F] */
/* return: pointer to non-[0-9a-fA-F], may be to '\0' */
/* returns NULL on integer overflow */
GTPARSER_EXPORTS const wchar_t *gt_scan_hex_w_z(const wchar_t *s/*'\0'-terminated*/, unsigned *number/*out*/);
GTPARSER_EXPORTS const wchar_t *gt_scan_hex64_w_z(const wchar_t *s/*'\0'-terminated*/, unsigned INT64_TYPE *number/*out*/);

#ifdef __cplusplus
}
#endif

#endif /* INT_SCANNER_W_H_INCLUDED */
