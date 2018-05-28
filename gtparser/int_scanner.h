#ifndef INT_SCANNER_H_INCLUDED
#define INT_SCANNER_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_scanner.h */

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
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_reads_to_ptr(end))
A_At(end, A_Notnull)
A_At(number, A_Out)
#endif
GTPARSER_EXPORTS const char *gt_scan_uint(const char *s/*<end*/, const char *const end, unsigned *number/*out*/);

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_reads_to_ptr(end))
A_At(end, A_Notnull)
A_At(number, A_Out)
#endif
GTPARSER_EXPORTS const char *gt_scan_uint64(const char *s/*<end*/, const char *const end, unsigned INT64_TYPE *number/*out*/);

/* input:  s points to [0-9a-fA-F] */
/* return: pointer to non-[0-9a-fA-F], may be to end */
/* returns NULL on integer overflow */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_reads_to_ptr(end))
A_At(end, A_Notnull)
A_At(number, A_Out)
#endif
GTPARSER_EXPORTS const char *gt_scan_hex(const char *s/*<end*/, const char *const end, unsigned *number/*out*/);

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_reads_to_ptr(end))
A_At(end, A_Notnull)
A_At(number, A_Out)
#endif
GTPARSER_EXPORTS const char *gt_scan_hex64(const char *s/*<end*/, const char *const end, unsigned INT64_TYPE *number/*out*/);

/* input:  s points to [0-9] */
/* return: pointer to non-[0-9], may be to '\0' */
/* returns NULL on integer overflow */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_z)
A_At(number, A_Out)
#endif
GTPARSER_EXPORTS const char *gt_scan_uint_z(const char *s/*'\0'-terminated*/, unsigned *number/*out*/);

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_z)
A_At(number, A_Out)
#endif
GTPARSER_EXPORTS const char *gt_scan_uint64_z(const char *s/*'\0'-terminated*/, unsigned INT64_TYPE *number/*out*/);

/* input:  s points to [0-9a-fA-F] */
/* return: pointer to non-[0-9a-fA-F], may be to '\0' */
/* returns NULL on integer overflow */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_z)
A_At(number, A_Out)
#endif
GTPARSER_EXPORTS const char *gt_scan_hex_z(const char *s/*'\0'-terminated*/, unsigned *number/*out*/);

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_z)
A_At(number, A_Out)
#endif
GTPARSER_EXPORTS const char *gt_scan_hex64_z(const char *s/*'\0'-terminated*/, unsigned INT64_TYPE *number/*out*/);

#ifdef __cplusplus
}
#endif

#endif /* INT_SCANNER_H_INCLUDED */
