#ifndef PARSER_Z_BASE_H_INCLUDED
#define PARSER_Z_BASE_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_z_base.h */

#include "gtparser/gtparser.h"
#include "gtparser/parser_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* for parsing '\0'-terminated text */
struct src_iter_z {
	const char *current;
	unsigned back_column;
	unsigned line;
#ifdef __cplusplus
	inline void init(const char *input/*'\0'-terminated*/);
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
A_Nonnull_all_args
A_At(it, A_Out)
A_At(input, A_In_z)
#endif
static inline void src_iter_z_init(struct src_iter_z *it, const char *input/*'\0'-terminated*/)
{
	it->current = input;
	src_iter_get_back_column_(input, &it->back_column);
	it->line = 1;
}

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline void src_iter_z_step(struct src_iter_z *it)
{
	src_iter_step_(&it->current);
}

/* returns non-zero if 'it' points to '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(current, A_In_z)
#endif
static inline int src_iter_z_eof_(const char *current)
{
	return !*current;
}

/* returns non-zero if 'it' points to '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(it, A_In)
#endif
static inline int src_iter_z_eof(const struct src_iter_z *it)
{
	return src_iter_z_eof_(it->current);
}

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to '\0' */
/* returns zero if 'it' points to '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(current, A_Inout)
A_At(*current, A_In_z)
#endif
static inline int src_iter_z_next_(const char **current)
{
	src_iter_step_(current);
	return !src_iter_z_eof_(*current);
}

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to '\0' */
/* returns zero if 'it' points to '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline int src_iter_z_next(struct src_iter_z *it)
{
	return src_iter_z_next_(&it->current);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline void src_iter_z_process_tab(struct src_iter_z *it)
{
	src_iter_process_tab_(&it->back_column, it->current, GTPARSER_TAB_SIZE(it));
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline void src_iter_z_check_tab(struct src_iter_z *it)
{
	src_iter_check_tab_(&it->back_column, it->current, GTPARSER_TAB_SIZE(it));
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline void src_iter_z_inc_line(struct src_iter_z *it)
{
	src_iter_inc_line_(&it->line, &it->back_column, it->current);
}

/* check current char - adjust iterator */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
static inline void src_iter_z_check(struct src_iter_z *it)
{
	src_iter_check_(&it->line, &it->back_column, it->current, GTPARSER_TAB_SIZE(it));
}

/* get current char the 'it' points to ('it' _may_ point to '\0') */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(it, A_In)
#endif
static inline char src_iter_z_current_char(const struct src_iter_z *it)
{
	return src_iter_current_char_(it->current);
}

/* get current char the 'it' points to, '\0' if 'it' points to '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(current, A_In_z)
#endif
static inline char src_iter_z_char_or_eof_(const char *current)
{
	return *current;
}

/* get current char the 'it' points to, '\0' if 'it' points to '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(it, A_In)
#endif
static inline char src_iter_z_char_or_eof(const struct src_iter_z *it)
{
	return src_iter_z_char_or_eof_(it->current);
}

/* get column from start of the line */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(it, A_In)
#endif
static inline unsigned src_iter_z_get_column(const struct src_iter_z *it)
{
	return src_iter_get_column_(it->current, it->back_column);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_In)
A_At(pos, A_Out)
#endif
static inline void src_iter_z_get_pos(const struct src_iter_z *it, struct src_pos *pos/*out*/)
{
	src_iter_get_pos_(it->line, it->current, it->back_column, pos);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(it, A_In)
#endif
static inline struct src_pos src_iter_z_return_pos(const struct src_iter_z *it)
{
	return src_iter_return_pos_(it->line, it->current, it->back_column);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_In)
A_At(save_pos, A_Out)
#endif
static inline void src_iter_z_save_pos(const struct src_iter_z *it, struct src_save_pos *save_pos/*out*/)
{
	src_iter_save_pos_(it->line, it->current, it->back_column, save_pos);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_At(it, A_In)
#endif
static inline struct src_save_pos src_iter_z_return_save_pos(const struct src_iter_z *it)
{
	return src_iter_return_save_pos_(it->line, it->current, it->back_column);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
A_At(save_pos, A_In)
#endif
static inline void src_iter_z_restore_pos(struct src_iter_z *it, const struct src_save_pos *save_pos/*in*/)
{
	src_iter_restore_pos_(&it->line, &it->current, &it->back_column, save_pos);
}

/* input:  'it' points to checked char (like comment beginning) */
/* output: 'it' points to next unchecked char after new line, may be to '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
GTPARSER_EXPORTS void gt_skip_rest_of_line_z(struct src_iter_z *it);
#define src_iter_z_skip_comment(it) gt_skip_rest_of_line_z(it)

/* input:  'it' points to unchecked char or to '\0' */
/* output: if returns != '\0', 'it' points to non-space and non-'\0' */
/* returns current char or '\0' on '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
GTPARSER_EXPORTS char gt_read_non_space_skip_comments_z(struct src_iter_z *it, char comment/*'#'*/);
#define src_iter_z_read_non_space_skip_comments(it, comment) gt_read_non_space_skip_comments_z(it, comment)

/* input:  'it' points to unchecked char or to '\0' */
/* output: if returns != '\0', 'it' points to '\n' or to non-space and non-'\0' */
/* returns current char or '\0' on '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(it, A_Inout)
#endif
GTPARSER_EXPORTS char gt_read_non_space_stop_eol_z(struct src_iter_z *it);
#define src_iter_z_read_non_space_stop_eol(it) gt_read_non_space_stop_eol_z(it)

#ifdef __cplusplus

inline void src_iter_z::init(const char *input/*'\0'-terminated*/)
{
	src_iter_z_init(this, input);
}

inline void src_iter_z::step()
{
	src_iter_z_step(this);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
inline bool src_iter_z::eof() const
{
	return 0 != src_iter_z_eof(this);
}

inline bool src_iter_z::next()
{
	return 0 != src_iter_z_next(this);
}

inline void src_iter_z::process_tab()
{
	src_iter_z_process_tab(this);
}

inline void src_iter_z::check_tab()
{
	src_iter_z_check_tab(this);
}

inline void src_iter_z::inc_line()
{
	src_iter_z_inc_line(this);
}

inline void src_iter_z::check()
{
	src_iter_z_check(this);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
inline char src_iter_z::current_char() const
{
	return src_iter_z_current_char(this);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
inline char src_iter_z::char_or_eof() const
{
	return src_iter_z_char_or_eof(this);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
inline unsigned src_iter_z::get_column() const
{
	return src_iter_z_get_column(this);
}

inline void src_iter_z::get_pos(struct src_pos &pos/*out*/) const
{
	src_iter_z_get_pos(this, &pos/*out*/);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
inline struct src_pos src_iter_z::get_pos() const
{
	return src_iter_z_return_pos(this);
}

inline void src_iter_z::save_pos(struct src_save_pos &save_pos_/*out*/) const
{
	src_iter_z_save_pos(this, &save_pos_/*out*/);
}

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
#endif
inline struct src_save_pos src_iter_z::save_pos() const
{
	return src_iter_z_return_save_pos(this);
}

inline void src_iter_z::restore_pos(const struct src_save_pos &save_pos_)
{
	src_iter_z_restore_pos(this, &save_pos_/*in*/);
}

inline void src_iter_z::skip_comment()
{
	src_iter_z_skip_comment(this);
}

inline char src_iter_z::read_non_space_skip_comments(char comment/*#*/)
{
	return src_iter_z_read_non_space_skip_comments(this, comment);
}

inline char src_iter_z::read_non_space_stop_eol()
{
	return src_iter_z_read_non_space_stop_eol(this);
}

#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif

#endif /* PARSER_Z_BASE_H_INCLUDED */
