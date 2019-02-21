/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018-2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_z_base.c */

#include "gtparser/gtparser_system.h"
#include "gtparser/parser_z_base.h"

#ifndef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
#define A_Use_decl_annotations
#endif

/* it points to checked char, likely '#' */
A_Use_decl_annotations
GTPARSER_EXPORTS void gt_skip_rest_of_line_z(struct src_iter_z *const it)
{
	const char *s = it->current;
	const unsigned tab_size = GTPARSER_TAB_SIZE(it);
	while (src_iter_z_next_(&s)) {
		src_iter_check_(&it->loc.line, &it->loc.back_column, s, tab_size);
		if ('\n' == src_iter_current_char_(s)) {
			src_iter_step_(&s);
			break;
		}
	}
	it->current = s; /* it points to char after '\n', may be to '\0' */
}

/* it points to unchecked char or to '\0' */
A_Use_decl_annotations
GTPARSER_EXPORTS char gt_read_non_space_skip_comments_z(struct src_iter_z *const it, const char comment)
{
	while (!src_iter_z_eof(it)) {
		const char c = src_iter_z_current_char(it);
		if (comment == c) {
			src_iter_z_skip_comment(it);
			continue;
		}
		if (!is_space(c))
			return c;
		src_iter_z_check(it);
		src_iter_z_step(it);
	}
	return '\0'; /* failed to read non-space, it points to eof */
}

/* it points to unchecked char or to '\0' */
A_Use_decl_annotations
GTPARSER_EXPORTS char gt_read_non_space_stop_eol_z(struct src_iter_z *const it)
{
	while (!src_iter_z_eof(it)) {
		const char c = src_iter_z_current_char(it);
		if ('\n' == c || !is_space(c))
			return c;
		src_iter_z_check_tab(it);
		src_iter_z_step(it);
	}
	return '\0'; /* failed to read non-space, it points to eof */
}
