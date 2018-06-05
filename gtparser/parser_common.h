#ifndef PARSER_COMMON_H_INCLUDED
#define PARSER_COMMON_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_common.h */

/* GTPARSER_TAB_SIZE may be defined as a function, e.g.:
extern unsigned source_tab_size(const struct src_iter *iter);
#define GTPARSER_TAB_SIZE(iter) source_tab_size(iter)
*/
#ifndef GTPARSER_TAB_SIZE
#define GTPARSER_TAB_SIZE(iter) 4 /* used to determine parsing error column in error messages */
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct src_pos {
	unsigned column;
	unsigned line;
};

struct src_save_pos {
	const char *current;
	unsigned back_column;
	unsigned line;
};

/* convert pointer to unsigned integer */
static inline unsigned gtparser_ptr_to_uint(const char *p)
{
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4826) /* Conversion from 'const char *' to 'unsigned __int64' is sign-extended */
#endif
	return (unsigned)(unsigned long long)p;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
static inline int is_space(char c)
{
	return (unsigned char)c <= ' ';
}

/* get initial value of 'back_column' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(input, A_In)
A_At(back_column, A_Out)
#endif
static inline void src_iter_get_back_column_(
	const char *input/*in*/,
	unsigned *back_column/*out*/)
{
	unsigned i = gtparser_ptr_to_uint(input);
#ifdef UBSAN_UNSIGNED_OVERFLOW
	*back_column = i ? i - 1u : (unsigned)-1;
#else
	*back_column = i - 1u;
#endif
}

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to 'eof' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(current, A_Inout)
#endif
static inline void src_iter_step_(const char **current/*in,out*/)
{
	(*current)++;
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(back_column, A_Inout)
A_At(current, A_In)
A_At(tab_size, A_In_range(>,0))
#endif
static inline void src_iter_process_tab_(
	unsigned *back_column/*in,out*/,
	const char *current/*in*/,
	unsigned tab_size/*>0*/)
{
	unsigned c = *back_column;
	unsigned d = gtparser_ptr_to_uint(current);
#ifdef UBSAN_UNSIGNED_OVERFLOW
	d = (c >= d) ? c - d : ~0u - (d - c) + 1u;
#else
	d = c - d;
#endif
	d %= tab_size;
#ifdef UBSAN_UNSIGNED_OVERFLOW
	*back_column = (c >= d) ? c - d : ~0u - (d - c) + 1u;
#else
	*back_column = c - d;
#endif
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(back_column, A_Inout)
A_At(current, A_In)
A_At(tab_size, A_In_range(>,0))
#endif
static inline void src_iter_check_tab_(
	unsigned *back_column/*in,out*/,
	const char *current/*in*/,
	unsigned tab_size/*>0*/)
{
	if ('\t' == *current)
		src_iter_process_tab_(back_column, current, tab_size);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(line, A_Inout)
A_At(back_column, A_Out)
A_At(current, A_In)
#endif
static inline void src_iter_inc_line_(
	unsigned *line/*in,out*/,
	unsigned *back_column/*out*/,
	const char *current/*in*/)
{
	(*line)++;
	*back_column = gtparser_ptr_to_uint(current);
}

/* check current char */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(line, A_Inout)
A_At(back_column, A_Inout)
A_At(current, A_In)
A_At(tab_size, A_In_range(>,0))
#endif
static inline void src_iter_check_(
	unsigned *line/*in,out*/,
	unsigned *back_column/*in,out*/,
	const char *current/*in*/,
	unsigned tab_size/*>0*/)
{
	if ('\n' == *current)
		src_iter_inc_line_(line, back_column, current);
	else
		src_iter_check_tab_(back_column, current, tab_size);
}

/* get current char the 'it' points to ('it' must not point to 'eof') */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(current, A_In)
#endif
static inline char src_iter_current_char_(const char *current)
{
	return *current;
}

/* get column from start of the line */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(current, A_In)
#endif
static inline unsigned src_iter_get_column_(
	const char *current, unsigned back_column)
{
	unsigned c = gtparser_ptr_to_uint(current);
#ifdef UBSAN_UNSIGNED_OVERFLOW
	return (c >= back_column) ? c - back_column : ~0u - (back_column - c) + 1u;
#else
	return c - back_column;
#endif
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(current, A_In)
A_At(pos, A_Out)
#endif
static inline void src_iter_get_pos_(unsigned line, const char *current,
	unsigned back_column, struct src_pos *pos/*out*/)
{
	pos->line = line;
	pos->column = src_iter_get_column_(current, back_column);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(current, A_In)
#endif
static inline struct src_pos src_iter_return_pos_(
	unsigned line, const char *current, unsigned back_column)
{
	struct src_pos pos;
	src_iter_get_pos_(line, current, back_column, &pos);
	return pos;
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(current, A_In)
A_At(save_pos, A_Out)
#endif
static inline void src_iter_save_pos_(unsigned line, const char *current,
	unsigned back_column, struct src_save_pos *save_pos/*out*/)
{
	save_pos->line = line;
	save_pos->current = current;
	save_pos->back_column = back_column;
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(current, A_In)
#endif
static inline struct src_save_pos src_iter_return_save_pos_(
	unsigned line, const char *current, unsigned back_column)
{
	struct src_save_pos save_pos;
	src_iter_save_pos_(line, current, back_column, &save_pos);
	return save_pos;
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(line, A_Out)
A_At(current, A_Out)
A_At(back_column, A_Out)
A_At(save_pos, A_In)
#endif
static inline void src_iter_restore_pos_(unsigned *line/*out*/, const char **current/*out*/,
	unsigned *back_column/*out*/, const struct src_save_pos *save_pos/*in*/)
{
	*line = save_pos->line;
	*current = save_pos->current;
	*back_column = save_pos->back_column;
}

#ifdef __cplusplus
}
#endif

#endif /* PARSER_COMMON_H_INCLUDED */
