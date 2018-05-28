#ifndef NAME_PARSER_H_INCLUDED
#define NAME_PARSER_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* name_parser.h */

#include "gtparser/name_scanner.h"
#include "gtparser/parser_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/* assume (*current) points to first name character,
  returns scanned name */
/* NOTE: after return (*current) points to non-[_a-zA-Z0-9], may be to end */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Ret_notnull
A_Nonnull_all_args
A_At(current, A_Inout)
A_At(*current, A_In_reads_to_ptr(end))
A_At(end, A_Notnull)
#endif
static inline const char *read_name_(const char **current, const char *end)
{
	const char *name = *current;
	*current = gt_scan_name(*current, end);
	return name;
}

/* assume it->current points to first name character,
  returns scanned name */
/* NOTE: after return it->current points to non-[_a-zA-Z0-9], may be to end */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Ret_notnull
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline const char *src_iter_read_name(struct src_iter *it)
{
	return read_name_(&it->current, it->end);
}

#ifdef __cplusplus
}
#endif

#endif /* NAME_PARSER_H_INCLUDED */
