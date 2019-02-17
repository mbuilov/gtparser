#ifndef INT_SCANNER_W_H_INCLUDED
#define INT_SCANNER_W_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018-2019 Michael M. Builov, https://github.com/mbuilov/gtparser
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
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_reads_to_ptr(end))
A_At(*s, A_In_range(L'0',L'9'))
A_At(end, A_Notnull A_Pre_deref_invalid)
A_At(number, A_Out)
A_Pre_satisfies(s < end)
#endif
GTPARSER_EXPORTS const wchar_t *gt_scan_uint_w(
	const wchar_t *s/*<end,points to [0-9]*/,
	const wchar_t *const end/*>s*/,
	unsigned *const number/*out*/);

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_reads_to_ptr(end))
A_At(*s, A_In_range(L'0',L'9'))
A_At(end, A_Notnull A_Pre_deref_invalid)
A_At(number, A_Out)
A_Pre_satisfies(s < end)
#endif
GTPARSER_EXPORTS const wchar_t *gt_scan_uint64_w(
	const wchar_t *s/*<end,points to [0-9]*/,
	const wchar_t *const end/*>s*/,
	unsigned INT64_TYPE *const number/*out*/);

/* input:  s points to [0-9a-fA-F] */
/* return: pointer to non-[0-9a-fA-F], may be to end */
/* returns NULL on integer overflow */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_reads_to_ptr(end))
A_At(end, A_Notnull A_Pre_deref_invalid)
A_At(number, A_Out)
A_Pre_satisfies(s < end)
A_Pre_satisfies(
	(L'0' <= *s && *s <= L'9') ||
	(L'a' <= *s && *s <= L'f') ||
	(L'A' <= *s && *s <= L'F'))
#endif
GTPARSER_EXPORTS const wchar_t *gt_scan_hex_w(
	const wchar_t *s/*<end,points to [0-9a-fA-F]*/,
	const wchar_t *const end/*>s*/,
	unsigned *const number/*out*/);

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_reads_to_ptr(end))
A_At(end, A_Notnull A_Pre_deref_invalid)
A_At(number, A_Out)
A_Pre_satisfies(s < end)
A_Pre_satisfies(
	(L'0' <= *s && *s <= L'9') ||
	(L'a' <= *s && *s <= L'f') ||
	(L'A' <= *s && *s <= L'F'))
#endif
GTPARSER_EXPORTS const wchar_t *gt_scan_hex64_w(
	const wchar_t *s/*<end,points to [0-9a-fA-F]*/,
	const wchar_t *const end/*>s*/,
	unsigned INT64_TYPE *const number/*out*/);

/* input:  s points to [0-9] */
/* return: pointer to non-[0-9], may be to '\0' */
/* returns NULL on integer overflow */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_z)
A_At(*s, A_In_range(L'0',L'9'))
A_At(number, A_Out)
#endif
GTPARSER_EXPORTS const wchar_t *gt_scan_uint_w_z(
	const wchar_t *s/*'\0'-terminated,points to [0-9]*/,
	unsigned *const number/*out*/);

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_z)
A_At(*s, A_In_range(L'0',L'9'))
A_At(number, A_Out)
#endif
GTPARSER_EXPORTS const wchar_t *gt_scan_uint64_w_z(
	const wchar_t *s/*'\0'-terminated,points to [0-9]*/,
	unsigned INT64_TYPE *const number/*out*/);

/* input:  s points to [0-9a-fA-F] */
/* return: pointer to non-[0-9a-fA-F], may be to '\0' */
/* returns NULL on integer overflow */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_z)
A_At(number, A_Out)
A_Pre_satisfies(
	(L'0' <= *s && *s <= L'9') ||
	(L'a' <= *s && *s <= L'f') ||
	(L'A' <= *s && *s <= L'F'))
#endif
GTPARSER_EXPORTS const wchar_t *gt_scan_hex_w_z(
	const wchar_t *s/*'\0'-terminated,points to [0-9a-fA-F]*/,
	unsigned *const number/*out*/);

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(!!return)
A_At(s, A_In_z)
A_At(number, A_Out)
A_Pre_satisfies(
	(L'0' <= *s && *s <= L'9') ||
	(L'a' <= *s && *s <= L'f') ||
	(L'A' <= *s && *s <= L'F'))
#endif
GTPARSER_EXPORTS const wchar_t *gt_scan_hex64_w_z(
	const wchar_t *s/*'\0'-terminated,points to [0-9a-fA-F]*/,
	unsigned INT64_TYPE *const number/*out*/);

#ifdef __cplusplus
}
#endif

#endif /* INT_SCANNER_W_H_INCLUDED */
