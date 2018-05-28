#ifndef INT_PARSER_Z_H_INCLUDED
#define INT_PARSER_Z_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018 Michael M. Builov, https://github.com/mbuilov/gtparser
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
A_At(number, A_Out)
#endif
static inline int read_uint_z_(const char **current, unsigned *number/*out*/)
{
	const char *s = gt_scan_uint_z(*current, number/*out*/);
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
#endif
static inline int read_uint64_z_(const char **current, unsigned INT64_TYPE *number/*out*/)
{
	const char *s = gt_scan_uint64_z(*current, number/*out*/);
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
A_At(number, A_Out)
#endif
static inline int src_iter_z_read_uint(struct src_iter_z *it, unsigned *number/*out*/)
{
	return read_uint_z_(&it->current, number/*out*/);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(it, A_Inout)
A_At(number, A_Out)
#endif
static inline int src_iter_z_read_uint64(struct src_iter_z *it, unsigned INT64_TYPE *number/*out*/)
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
#endif
static inline int read_hex_z_(const char **current, unsigned *number/*out*/)
{
	const char *s = gt_scan_hex_z(*current, number/*out*/);
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
#endif
static inline int read_hex64_z_(const char **current, unsigned INT64_TYPE *number/*out*/)
{
	const char *s = gt_scan_hex64_z(*current, number/*out*/);
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
A_At(number, A_Out)
#endif
static inline int src_iter_z_read_hex(struct src_iter_z *it, unsigned *number/*out*/)
{
	return read_hex_z_(&it->current, number/*out*/);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(it, A_Inout)
A_At(number, A_Out)
#endif
static inline int src_iter_z_read_hex64(struct src_iter_z *it, unsigned INT64_TYPE *number/*out*/)
{
	return read_hex64_z_(&it->current, number/*out*/);
}

#ifdef __cplusplus
}
#endif

#endif /* INT_PARSER_Z_H_INCLUDED */
