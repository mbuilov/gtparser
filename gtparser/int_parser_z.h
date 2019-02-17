#ifndef INT_PARSER_Z_H_INCLUDED
#define INT_PARSER_Z_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018-2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_parser_z.h */

#include "gtparser/int_scanner.h"
#include "gtparser/parser_z_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/* input:  (*current) points to [0-9] */
/* output: (*current) points to non-[0-9], may be to '\0' */
/* returns 0 on integer overflow, (*current) - not changed */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(current, A_Inout)
A_At(*current, A_In_z)
A_At(**current, A_In_range('0','9'))
A_At(number, A_Out)
A_Post_satisfies(!('0' <= **current && **current <= '9'))
A_On_failure(A_Post_satisfies(*current == A_Old(*current)))
#endif
static inline int read_uint_z_(
	const char **const current,
	unsigned *const number/*out*/)
{
	const char *const s = gt_scan_uint_z(*current, number/*out*/);
	if (!s)
		return 0; /* integer overflow */
	*current = s;
	return 1;
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(current, A_Inout)
A_At(*current, A_In_z)
A_At(**current, A_In_range('0','9'))
A_At(number, A_Out)
A_Post_satisfies(!('0' <= **current && **current <= '9'))
A_On_failure(A_Post_satisfies(*current == A_Old(*current)))
#endif
static inline int read_uint64_z_(
	const char **const current,
	unsigned INT64_TYPE *const number/*out*/)
{
	const char *const s = gt_scan_uint64_z(*current, number/*out*/);
	if (!s)
		return 0; /* integer overflow */
	*current = s;
	return 1;
}

/* input:  it->current points to [0-9] */
/* output: it->current points to non-[0-9], may be to '\0' */
/* returns 0 on integer overflow, it->current - not changed */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(it, A_Inout)
A_At(*it->current, A_In_range('0','9'))
A_At(number, A_Out)
A_Post_satisfies(!('0' <= *it->current && *it->current <= '9'))
A_On_failure(A_Post_satisfies(it->current == A_Old(it->current)))
#endif
static inline int src_iter_z_read_uint(
	struct src_iter_z *const it,
	unsigned *const number/*out*/)
{
	return read_uint_z_(&it->current, number/*out*/);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(it, A_Inout)
A_At(*it->current, A_In_range('0','9'))
A_At(number, A_Out)
A_Post_satisfies(!('0' <= *it->current && *it->current <= '9'))
A_On_failure(A_Post_satisfies(it->current == A_Old(it->current)))
#endif
static inline int src_iter_z_read_uint64(
	struct src_iter_z *const it,
	unsigned INT64_TYPE *const number/*out*/)
{
	return read_uint64_z_(&it->current, number/*out*/);
}

/* input:  (*current) points to [0-9a-fA-F] */
/* output: (*current) points to non-[0-9a-fA-F], may be to '\0' */
/* returns 0 on integer overflow, (*current) - not changed */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(current, A_Inout)
A_At(*current, A_In_z)
A_At(number, A_Out)
A_Pre_satisfies(
	('0' <= **current && **current <= '9') ||
	('a' <= **current && **current <= 'f') ||
	('A' <= **current && **current <= 'F'))
A_Post_satisfies(!(
	('0' <= **current && **current <= '9') ||
	('a' <= **current && **current <= 'f') ||
	('A' <= **current && **current <= 'F')))
A_On_failure(A_Post_satisfies(*current == A_Old(*current)))
#endif
static inline int read_hex_z_(
	const char **const current,
	unsigned *const number/*out*/)
{
	const char *const s = gt_scan_hex_z(*current, number/*out*/);
	if (!s)
		return 0; /* integer overflow */
	*current = s;
	return 1;
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(current, A_Inout)
A_At(*current, A_In_z)
A_At(number, A_Out)
A_Pre_satisfies(
	('0' <= **current && **current <= '9') ||
	('a' <= **current && **current <= 'f') ||
	('A' <= **current && **current <= 'F'))
A_Post_satisfies(!(
	('0' <= **current && **current <= '9') ||
	('a' <= **current && **current <= 'f') ||
	('A' <= **current && **current <= 'F')))
A_On_failure(A_Post_satisfies(*current == A_Old(*current)))
#endif
static inline int read_hex64_z_(
	const char **const current,
	unsigned INT64_TYPE *const number/*out*/)
{
	const char *const s = gt_scan_hex64_z(*current, number/*out*/);
	if (!s)
		return 0; /* integer overflow */
	*current = s;
	return 1;
}

/* input:  it->current points to [0-9a-fA-F] */
/* output: it->current points to non-[0-9a-fA-F], may be to '\0' */
/* returns 0 on integer overflow, it->current - not changed */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(it, A_Inout)
A_At(number, A_Out)
A_Pre_satisfies(
	('0' <= *it->current && *it->current <= '9') ||
	('a' <= *it->current && *it->current <= 'f') ||
	('A' <= *it->current && *it->current <= 'F'))
A_Post_satisfies(!(
	('0' <= *it->current && *it->current <= '9') ||
	('a' <= *it->current && *it->current <= 'f') ||
	('A' <= *it->current && *it->current <= 'F')))
A_On_failure(A_Post_satisfies(it->current == A_Old(it->current)))
#endif
static inline int src_iter_z_read_hex(
	struct src_iter_z *const it,
	unsigned *const number/*out*/)
{
	return read_hex_z_(&it->current, number/*out*/);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(it, A_Inout)
A_At(number, A_Out)
A_Pre_satisfies(
	('0' <= *it->current && *it->current <= '9') ||
	('a' <= *it->current && *it->current <= 'f') ||
	('A' <= *it->current && *it->current <= 'F'))
A_Post_satisfies(!(
	('0' <= *it->current && *it->current <= '9') ||
	('a' <= *it->current && *it->current <= 'f') ||
	('A' <= *it->current && *it->current <= 'F')))
A_On_failure(A_Post_satisfies(it->current == A_Old(it->current)))
#endif
static inline int src_iter_z_read_hex64(
	struct src_iter_z *const it,
	unsigned INT64_TYPE *const number/*out*/)
{
	return read_hex64_z_(&it->current, number/*out*/);
}

#ifdef __cplusplus
}
#endif

#endif /* INT_PARSER_Z_H_INCLUDED */
