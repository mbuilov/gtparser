#ifndef PARSER_COMMON_H_INCLUDED
#define PARSER_COMMON_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018-2019 Michael M. Builov, https://github.com/mbuilov/gtparser
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

struct src_iter_loc {
	unsigned back_column;
	unsigned line;
};

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
static inline unsigned gtparser_ptr_to_uint(const char *const p)
{
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4826) /* Conversion from 'const char *' to 'unsigned __int64' is sign-extended */
#elif !defined __cplusplus && defined __GNUC__ && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast" /* warning: cast from pointer to integer of different size */
#endif
	return (unsigned)((unsigned)-1 & (unsigned long long)p) +
		0*sizeof(int[1-2*(sizeof(const char*) > sizeof(unsigned long long))]);
#ifdef _MSC_VER
#pragma warning(pop)
#elif !defined __cplusplus && defined __GNUC__ && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#pragma GCC diagnostic pop
#endif
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
static inline int is_space(const char c)
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
	const char *const input/*in*/,
	unsigned *const back_column/*out*/)
{
	const unsigned i = gtparser_ptr_to_uint(input);
#ifdef UBSAN_UNSIGNED_OVERFLOW
	*back_column = i ? i - 1u : (unsigned)-1;
#else
	*back_column = i - 1u;
#endif
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(line, A_Out)
A_At(back_column, A_Out)
A_At(input, A_In)
#endif
static inline void src_iter_loc_init_(
	unsigned *const line/*out*/,
	unsigned *const back_column/*out*/,
	const char *const input/*in*/)
{
	*line = 1;
	src_iter_get_back_column_(input, back_column);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(loc, A_Out)
A_At(input, A_In)
#endif
static inline void src_iter_loc_init(
	struct src_iter_loc *const loc,
	const char *const input)
{
	src_iter_loc_init_(&loc->line, &loc->back_column, input);
}

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to 'eof' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(current, A_Inout)
#endif
static inline void src_iter_step_(const char **const current/*in,out*/)
{
	(*current)++;
}

/* assume 'current' points to '\t' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(back_column, A_Inout)
A_At(current, A_In)
A_At(tab_size, A_In_range(>,0))
#endif
static inline void src_iter_process_tab_(
	unsigned *const back_column/*in,out*/,
	const char *const current/*in*/,
	const unsigned tab_size/*>0*/)
{
	const unsigned c = *back_column;
	unsigned d = gtparser_ptr_to_uint(current);
#ifdef UBSAN_UNSIGNED_OVERFLOW
	d = (c >= d) ? c - d : ((unsigned)-1 - (d - c)) + 1u;
#else
	d = c - d;
#endif
	d %= tab_size;
#ifdef UBSAN_UNSIGNED_OVERFLOW
	*back_column = (c >= d) ? c - d : ((unsigned)-1 - (d - c)) + 1u;
#else
	*back_column = c - d;
#endif
}

/* check if current char is a tab:
  if current char is a tab - process it and return '\t'
  else                     - return 0 */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(back_column, A_Inout)
A_At(current, A_In)
A_At(tab_size, A_In_range(>,0))
#endif
static inline int src_iter_check_tab_(
	unsigned *const back_column/*in,out*/,
	const char *const current/*in*/,
	const unsigned tab_size/*>0*/)
{
	if ('\t' == *current) {
		src_iter_process_tab_(back_column, current, tab_size);
		return '\t';
	}
	return 0;
}

/* assume 'current' points to '\n' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(line, A_Inout)
A_At(back_column, A_Out)
A_At(current, A_In)
#endif
static inline void src_iter_inc_line_(
	unsigned *const line/*in,out*/,
	unsigned *const back_column/*out*/,
	const char *const current/*in*/)
{
	(*line)++;
	*back_column = gtparser_ptr_to_uint(current);
}

/* check current char:
  if current char is a tab      - process it and return '\t'
  if current char is a new line - process it and return '\n'
  else                          - return 0 */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(line, A_Inout)
A_At(back_column, A_Inout)
A_At(current, A_In)
A_At(tab_size, A_In_range(>,0))
#endif
static inline int src_iter_check_(
	unsigned *const line/*in,out*/,
	unsigned *const back_column/*in,out*/,
	const char *const current/*in*/,
	const unsigned tab_size/*>0*/)
{
	if ('\n' == *current) {
		src_iter_inc_line_(line, back_column, current);
		return '\n';
	}
	return src_iter_check_tab_(back_column, current, tab_size);
}

/* get current char the 'it' points to ('it' must not point to 'eof') */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(current, A_In)
#endif
static inline char src_iter_current_char_(const char *const current)
{
	return *current;
}

/* get column from start of the line */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(current, A_Notnull)
#endif
static inline unsigned src_iter_get_column_(
	const char *const current,
	const unsigned back_column)
{
	const unsigned c = gtparser_ptr_to_uint(current);
#ifdef UBSAN_UNSIGNED_OVERFLOW
	return (c >= back_column) ? c - back_column : ((unsigned)-1 - (back_column - c)) + 1u;
#else
	return c - back_column;
#endif
}

/* convert back-column <-> column */
/* note: assume 'current' is not changed between conversions */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(current, A_Notnull)
A_At(xcolumn, A_Inout)
#endif
static inline void src_iter_convert_column_(
	const char *const current,
	unsigned *const xcolumn)
{
	/* 1) first call - get column from back-column:
	  column = (unsigned)current1 - back_column;
	   2) next call - convert column back to back-column:
	  back_column = (unsigned)current2 - column =
	   (unsigned)current2 - ((unsigned)current1 - back_column) =
	   (unsigned)current2 - (unsigned)current1 + back_column */
	*xcolumn = src_iter_get_column_(current, *xcolumn);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(current, A_Notnull)
A_At(pos, A_Out)
#endif
static inline void src_iter_get_pos_(
	const unsigned line,
	const char *const current,
	const unsigned back_column,
	struct src_pos *const pos/*out*/)
{
	pos->line = line;
	pos->column = src_iter_get_column_(current, back_column);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(current, A_Notnull)
#endif
static inline struct src_pos src_iter_return_pos_(
	const unsigned line,
	const char *const current,
	const unsigned back_column)
{
	struct src_pos pos;
	src_iter_get_pos_(line, current, back_column, &pos);
	return pos;
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(current, A_Notnull)
A_At(save_pos, A_Out)
#endif
static inline void src_iter_save_pos_(
	const unsigned line,
	const char *const current,
	const unsigned back_column,
	struct src_save_pos *const save_pos/*out*/)
{
	save_pos->line = line;
	save_pos->current = current;
	save_pos->back_column = back_column;
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(current, A_Notnull)
#endif
static inline struct src_save_pos src_iter_return_save_pos_(
	const unsigned line,
	const char *const current,
	const unsigned back_column)
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
static inline void src_iter_restore_pos_(
	unsigned *const line/*out*/,
	const char **const current/*out*/,
	unsigned *const back_column/*out*/,
	const struct src_save_pos *const save_pos/*in*/)
{
	*line = save_pos->line;
	*current = save_pos->current;
	*back_column = save_pos->back_column;
}

#ifdef __cplusplus
}
#endif

#endif /* PARSER_COMMON_H_INCLUDED */
