/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_base.c */

#include "gtparser/gtparser_system.h"
#include "gtparser/parser_base.h"

#ifndef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
#define A_Use_decl_annotations
#endif

/* it points to checked char, likely '#' */
A_Use_decl_annotations
GTPARSER_EXPORTS void gt_skip_rest_of_line(struct src_iter *const it)
{
	const char *s = it->current;
	const char *const e = it->end;
	const unsigned tab_size = GTPARSER_TAB_SIZE(it);
	while (src_iter_next_(&s, e)) {
		src_iter_check_(&it->loc.line, &it->loc.back_column, s, tab_size);
		if ('\n' == src_iter_current_char_(s)) {
			src_iter_step_(&s);
			break;
		}
	}
	it->current = s; /* it points to char after '\n', may be to eof */
}

/* it points to unchecked char or to eof */
A_Use_decl_annotations
GTPARSER_EXPORTS char gt_read_non_space_skip_comments(struct src_iter *const it, const char comment)
{
	while (!src_iter_eof(it)) {
		const char c = src_iter_current_char(it);
		if (comment == c) {
			src_iter_skip_comment(it);
			continue;
		}
		if (!is_space(c))
			return c;
		src_iter_check(it);
		src_iter_step(it);
	}
	return '\0'; /* failed to read non-space, it points to eof */
}

/* it points to unchecked char or to eof */
A_Use_decl_annotations
GTPARSER_EXPORTS char gt_read_non_space_stop_eol(struct src_iter *const it)
{
	while (!src_iter_eof(it)) {
		const char c = src_iter_current_char(it);
		if ('\n' == c || !is_space(c))
			return c;
		src_iter_check_tab(it);
		src_iter_step(it);
	}
	return '\0'; /* failed to read non-space, it points to eof */
}
