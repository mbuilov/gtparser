#ifndef PARSER_BASE_H_INCLUDED
#define PARSER_BASE_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_base.h */

#include "gtparser/gtparser.h"
#include "gtparser/parser_common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct src_iter {
	const char *current;
	const char *end;
	struct src_iter_loc loc;
#ifdef __cplusplus
	inline void init(const char *const input, const size_t size);
	inline void step();
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
	inline bool eof() const;
	inline bool next();
	inline void process_tab();
	inline void check_tab();
	inline void inc_line();
	inline void check();
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
	inline char current_char() const;
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
	inline char char_or_eof() const;
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
	inline unsigned get_column() const;
	inline void get_pos(struct src_pos &pos/*out*/) const;
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
	inline struct src_pos get_pos() const;
	inline void save_pos(struct src_save_pos &save_pos_/*out*/) const;
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
	inline struct src_save_pos save_pos() const;
	inline void restore_pos(const struct src_save_pos &save_pos_);
	inline void skip_comment();
	inline char read_non_space_skip_comments(char comment/*#*/);
	inline char read_non_space_stop_eol();
#endif /* __cplusplus */
};

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Ret_range(==,it)
A_Nonnull_all_args
A_At(it, A_Out)
A_At(input, A_In)
#endif
static inline struct src_iter *src_iter_init_(struct src_iter *const it, const char *const input)
{
	it->current = input;
	it->end = input;
	src_iter_loc_init(&it->loc, input);
	return it;
}

/* allow 64-bit size type */
#define src_iter_init(it, input, size) ((void)(src_iter_init_(it, input)->end += (size)))

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to 'eof' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline void src_iter_step(struct src_iter *const it)
{
	src_iter_step_(&it->current);
}

/* returns non-zero if 'it' points to 'eof' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Pre_satisfies(current && end && current <= end)
A_When(current == end, A_Ret_range(==,1))
#endif
static inline int src_iter_eof_(const char *const current, const char *const end)
{
	return current == end;
}

/* returns non-zero if 'it' points to 'eof' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(it, A_In)
#endif
static inline int src_iter_eof(const struct src_iter *const it)
{
	return src_iter_eof_(it->current, it->end);
}

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to 'eof' */
/* returns zero if 'it' points to 'eof' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(current, A_Inout)
A_At(*current, A_In)
A_At(end, A_Notnull)
A_Pre_satisfies(*current < end)
#endif
static inline int src_iter_next_(const char **const current, const char *const end)
{
	src_iter_step_(current);
	return !src_iter_eof_(*current, end);
}

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to 'eof' */
/* returns zero if 'it' points to 'eof' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline int src_iter_next(struct src_iter *const it)
{
	return src_iter_next_(&it->current, it->end);
}

/* assume 'it->current' points to '\t' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline void src_iter_process_tab(struct src_iter *const it)
{
	src_iter_process_tab_(&it->loc.back_column, it->current, GTPARSER_TAB_SIZE(it));
}

/* check if current char is a tab:
  if current char is a tab - process it and return '\t'
  else                     - return 0 */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline int src_iter_check_tab(struct src_iter *const it)
{
	return src_iter_check_tab_(&it->loc.back_column, it->current, GTPARSER_TAB_SIZE(it));
}

/* assume 'it->current' points to '\n' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline void src_iter_inc_line(struct src_iter *const it)
{
	src_iter_inc_line_(&it->loc.line, &it->loc.back_column, it->current);
}

/* check current char:
  if current char is a tab      - process it and return '\t'
  if current char is a new line - process it and return '\n'
  else                          - return 0 */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline int src_iter_check(struct src_iter *const it)
{
	return src_iter_check_(&it->loc.line, &it->loc.back_column, it->current, GTPARSER_TAB_SIZE(it));
}

/* get current char the 'it' points to ('it' must not point to 'eof') */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(it, A_In)
#endif
static inline char src_iter_current_char(const struct src_iter *const it)
{
	return src_iter_current_char_(it->current);
}

/* get current char the 'it' points to, '\0' if 'it' points to 'eof' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Pre_satisfies(current && end && current <= end)
#endif
static inline char src_iter_char_or_eof_(const char *const current, const char *const end)
{
	return src_iter_eof_(current, end) ? '\0' : *current;
}

/* get current char the 'it' points to, '\0' if 'it' points to 'eof' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(it, A_In)
#endif
static inline char src_iter_char_or_eof(const struct src_iter *const it)
{
	return src_iter_char_or_eof_(it->current, it->end);
}

/* get column from start of the line */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(it, A_In)
#endif
static inline unsigned src_iter_get_column(const struct src_iter *const it)
{
	return src_iter_get_column_(it->current, it->loc.back_column);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_In)
A_At(pos, A_Out)
#endif
static inline void src_iter_get_pos(const struct src_iter *const it, struct src_pos *const pos/*out*/)
{
	src_iter_get_pos_(it->loc.line, it->current, it->loc.back_column, pos);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(it, A_In)
#endif
static inline struct src_pos src_iter_return_pos(const struct src_iter *const it)
{
	return src_iter_return_pos_(it->loc.line, it->current, it->loc.back_column);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_In)
A_At(save_pos, A_Out)
#endif
static inline void src_iter_save_pos(const struct src_iter *const it, struct src_save_pos *const save_pos/*out*/)
{
	src_iter_save_pos_(it->loc.line, it->current, it->loc.back_column, save_pos);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(it, A_In)
#endif
static inline struct src_save_pos src_iter_return_save_pos(const struct src_iter *const it)
{
	return src_iter_return_save_pos_(it->loc.line, it->current, it->loc.back_column);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
A_At(save_pos, A_In)
#endif
static inline void src_iter_restore_pos(struct src_iter *const it, const struct src_save_pos *const save_pos/*in*/)
{
	src_iter_restore_pos_(&it->loc.line, &it->current, &it->loc.back_column, save_pos);
}

/* input:  'it' points to checked char (like comment beginning) */
/* output: 'it' points to next unchecked char after new line, may be to 'eof' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
GTPARSER_EXPORTS void gt_skip_rest_of_line(struct src_iter *const it);
#define src_iter_skip_comment(it) gt_skip_rest_of_line(it)

/* input:  'it' points to unchecked char or to 'eof' */
/* output: if returns != '\0', 'it' points to non-space and non-'eof' */
/* returns current char or '\0' on 'eof' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
GTPARSER_EXPORTS char gt_read_non_space_skip_comments(struct src_iter *const it, const char comment/*'#'*/);
#define src_iter_read_non_space_skip_comments(it, comment) gt_read_non_space_skip_comments(it, comment)

/* input:  'it' points to unchecked char or to eof */
/* output: if returns != '\0', 'it' points to '\n' or to non-space and non-'eof' */
/* returns current char or '\0' on 'eof' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
GTPARSER_EXPORTS char gt_read_non_space_stop_eol(struct src_iter *const it);
#define src_iter_read_non_space_stop_eol(it) gt_read_non_space_stop_eol(it)

#ifdef __cplusplus

inline void src_iter::init(const char *const input, const size_t size)
{
	src_iter_init(this, input, size);
}

inline void src_iter::step()
{
	src_iter_step(this);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
inline bool src_iter::eof() const
{
	return 0 != src_iter_eof(this);
}

inline bool src_iter::next()
{
	return 0 != src_iter_next(this);
}

inline void src_iter::process_tab()
{
	src_iter_process_tab(this);
}

inline void src_iter::check_tab()
{
	src_iter_check_tab(this);
}

inline void src_iter::inc_line()
{
	src_iter_inc_line(this);
}

inline void src_iter::check()
{
	src_iter_check(this);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
inline char src_iter::current_char() const
{
	return src_iter_current_char(this);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
inline char src_iter::char_or_eof() const
{
	return src_iter_char_or_eof(this);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
inline unsigned src_iter::get_column() const
{
	return src_iter_get_column(this);
}

inline void src_iter::get_pos(struct src_pos &pos/*out*/) const
{
	src_iter_get_pos(this, &pos/*out*/);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
inline struct src_pos src_iter::get_pos() const
{
	return src_iter_return_pos(this);
}

inline void src_iter::save_pos(struct src_save_pos &save_pos_/*out*/) const
{
	src_iter_save_pos(this, &save_pos_/*out*/);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
inline struct src_save_pos src_iter::save_pos() const
{
	return src_iter_return_save_pos(this);
}

inline void src_iter::restore_pos(const struct src_save_pos &save_pos_)
{
	src_iter_restore_pos(this, &save_pos_/*in*/);
}

inline void src_iter::skip_comment()
{
	src_iter_skip_comment(this);
}

inline char src_iter::read_non_space_skip_comments(char comment/*#*/)
{
	return src_iter_read_non_space_skip_comments(this, comment);
}

inline char src_iter::read_non_space_stop_eol()
{
	return src_iter_read_non_space_stop_eol(this);
}

#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif

#endif /* PARSER_BASE_H_INCLUDED */
