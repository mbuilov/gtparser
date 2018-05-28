#ifndef INT_PARSER_H_INCLUDED
#define INT_PARSER_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_parser.h */

#include "gtparser/int_scanner.h"
#include "gtparser/parser_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/* input:  (*current) points to [0-9] */
/* output: (*current) points to non-[0-9], may be to end */
/* returns 0 on integer overflow, (*current) - not changed */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(current, A_Inout)
A_At(*current, A_In_reads_to_ptr(end))
A_At(end, A_Notnull)
A_At(number, A_Out)
#endif
static inline int read_uint_(const char **current, const char *end, unsigned *number/*out*/)
{
	const char *s = gt_scan_uint(*current, end, number/*out*/);
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
A_At(*current, A_In_reads_to_ptr(end))
A_At(end, A_Notnull)
A_At(number, A_Out)
#endif
static inline int read_uint64_(const char **current, const char *end, unsigned INT64_TYPE *number/*out*/)
{
	const char *s = gt_scan_uint64(*current, end, number/*out*/);
	if (!s)
		return 0; /* integer overflow */
	*current = s;
	return 1;
}

/* input:  it->current points to [0-9] */
/* output: it->current points to non-[0-9], may be to end */
/* returns 0 on integer overflow, it->current - not changed */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(it, A_Inout)
A_At(number, A_Out)
#endif
static inline int src_iter_read_uint(struct src_iter *it, unsigned *number/*out*/)
{
	return read_uint_(&it->current, it->end, number/*out*/);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(it, A_Inout)
A_At(number, A_Out)
#endif
static inline int src_iter_read_uint64(struct src_iter *it, unsigned INT64_TYPE *number/*out*/)
{
	return read_uint64_(&it->current, it->end, number/*out*/);
}

/* input:  (*current) points to [0-9a-fA-F] */
/* output: (*current) points to non-[0-9a-fA-F], may be to end */
/* returns 0 on integer overflow, (*current) - not changed */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(current, A_Inout)
A_At(*current, A_In_reads_to_ptr(end))
A_At(end, A_Notnull)
A_At(number, A_Out)
#endif
static inline int read_hex_(const char **current, const char *end, unsigned *number/*out*/)
{
	const char *s = gt_scan_hex(*current, end, number/*out*/);
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
A_At(*current, A_In_reads_to_ptr(end))
A_At(end, A_Notnull)
A_At(number, A_Out)
#endif
static inline int read_hex64_(const char **current, const char *end, unsigned INT64_TYPE *number/*out*/)
{
	const char *s = gt_scan_hex64(*current, end, number/*out*/);
	if (!s)
		return 0; /* integer overflow */
	*current = s;
	return 1;
}

/* input:  it->current points to [0-9a-fA-F] */
/* output: it->current points to non-[0-9a-fA-F], may be to end */
/* returns 0 on integer overflow, it->current - not changed */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(it, A_Inout)
A_At(number, A_Out)
#endif
static inline int src_iter_read_hex(struct src_iter *it, unsigned *number/*out*/)
{
	return read_hex_(&it->current, it->end, number/*out*/);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return)
A_At(it, A_Inout)
A_At(number, A_Out)
#endif
static inline int src_iter_read_hex64(struct src_iter *it, unsigned INT64_TYPE *number/*out*/)
{
	return read_hex64_(&it->current, it->end, number/*out*/);
}

#ifdef __cplusplus
}
#endif

#endif /* INT_PARSER_H_INCLUDED */
