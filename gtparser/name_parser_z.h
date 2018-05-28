#ifndef NAME_PARSER_Z_H_INCLUDED
#define NAME_PARSER_Z_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* name_parser_z.h */

#include "gtparser/name_scanner.h"
#include "gtparser/parser_z_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/* assume (*current) points to first name character,
  returns scanned name */
/* NOTE: after return (*current) points to non-[_a-zA-Z0-9], may be to '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Ret_notnull
A_Nonnull_all_args
A_At(current, A_Inout)
A_At(*current, A_In_z)
#endif
static inline const char *read_name_z_(const char **current)
{
	const char *name = *current;
	*current = gt_scan_name_z(*current, end);
	return name;
}

/* assume it->current points to first name character,
  returns scanned name */
/* NOTE: after return it->current points to non-[_a-zA-Z0-9], may be to '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Ret_notnull
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline const char *src_iter_z_read_name(struct src_iter_z *it)
{
	return read_name_z_(&it->current);
}

#ifdef __cplusplus
}
#endif

#endif /* NAME_PARSER_Z_H_INCLUDED */
