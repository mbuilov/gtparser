/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_z_base.c */

#include "gtparser/gtparser_config.h"
#include "gtparser/parser_z_base.h"

/* it points to checked char, likely '#' */
GTPARSER_EXPORTS void gt_skip_rest_of_line_z(struct src_iter_z *it)
{
	const char *s = it->current;
	while (src_iter_z_next_(&s)) {
		src_iter_check_(&it->line, &it->back_column, s, GTPARSER_TAB_SIZE(it));
		if ('\n' == src_iter_current_char_(s)) {
			src_iter_step_(&s);
			break;
		}
	}
	it->current = s; /* it points to char after '\n', may be to '\0' */
}

/* it points to unchecked char or to '\0' */
GTPARSER_EXPORTS char gt_read_non_space_skip_comments_z(struct src_iter_z *it, char comment)
{
	while (!src_iter_z_eof(it)) {
		char c = src_iter_z_current_char(it);
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
GTPARSER_EXPORTS char gt_read_non_space_stop_eol_z(struct src_iter_z *it)
{
	while (!src_iter_z_eof(it)) {
		char c = src_iter_z_current_char(it);
		if ('\n' == c || !is_space(c))
			return c;
		src_iter_z_check_tab(it);
		src_iter_z_step(it);
	}
	return '\0'; /* failed to read non-space, it points to eof */
}