#ifndef CSTRING_PARSER_H_INCLUDED
#define CSTRING_PARSER_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* cstring_parser.h */

#include "gtparser/gtparser.h"

#ifdef __cplusplus
extern "C" {
#endif

struct src_iter;
struct src_iter_z;

enum GT_PARSE_CSTRING_ERR {
	GT_PARSE_CSTRING_OK = 0,              /* C-string successfully parsed                                             */
	GT_PARSE_CSTRING_UNESCAPED_NEWLINE,   /* unescaped line-feed '\n' or carriage-return '\r'                         */
	GT_PARSE_CSTRING_EXPECTING_LINE_FEED, /* expecting line-feed '\n' after carriage-return '\r'                      */
	GT_PARSE_CSTRING_EXPECTING_HEX_DIGIT, /* expecting hexadecimal digit in hex escape sequence after '\x'            */
	GT_PARSE_CSTRING_TOO_BIG_OCTAL,       /* too big octal character value > 255 in string, maximum allowed is '\377' */
	GT_PARSE_CSTRING_NULL_INSIDE_CSTRING, /* null character '\0' inside C-string is not allowed                       */
	GT_PARSE_CSTRING_UNTERMINATED         /* unterminated string                                                      */
};

/* input:  'it' points to first (opening) quote */
/* output: 'it' points to last (closing) quote */
/* removed - number of removed meta-characters:
  - each '\' is removed and next char after it is unescaped (likely converted to some to non-printable char),
  - each line continuation-split (two chars: \<newline>) is removed,
  - encoded characters in octadecimal (\377) or hexadecimal (\xff) encoding are unencoded */
/* list of recognized escape sequences (a character after '\' will be replaced with byte value in {}):
  \a{0x07} \b{0x08} \t{0x09} \n{0x0a} \v{0x0b} \f{0x0c} \r{0x0d}
  octadecimal-encoded chars (max 3 octadecimal digits after '\'):
  \0..\7, \00..\77, \000..\377
  hexadecimal-encoded chars (max 2 hexadecimal digits after '\x'):
  \x0..\xf, \x00..\xff */
/* NOTE: '\0' (null) character is not allowed inside the string, because C-string is '\0'-terminated */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return == GT_PARSE_CSTRING_OK)
A_At(it, A_Inout)
A_At(removed, A_Out)
#endif
GTPARSER_EXPORTS enum GT_PARSE_CSTRING_ERR gt_parse_cstring(struct src_iter *it, size_t *removed/*out*/);

#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Nonnull_all_args
A_Success(return == GT_PARSE_CSTRING_OK)
A_At(it, A_Inout)
A_At(removed, A_Out)
#endif
GTPARSER_EXPORTS enum GT_PARSE_CSTRING_ERR gt_parse_cstring_z(struct src_iter_z *it, size_t *removed/*out*/);

#ifndef SAL_DEFS_H_INCLUDED
#define A_Restrict
#endif

/* copy previously parsed by gt_parse_cstring() string into supplied
  'dst' buffer (which must be large enough) unescaping escape sequences */
/* begin   - points to next char after the first (opening) quote in the source C-string */
/* end     - points to the last (closing) quote in the source C-string */
/* removed - number of meta-characters, value determined by gt_parse_cstring() */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(dst, A_Out_writes(end - begin - removed))
A_At(begin, A_In_reads_to_ptr(end))
A_At(end, A_Notnull)
A_At(removed, A_Pre_satisfies(removed <= end - begin))
#endif
GTPARSER_EXPORTS void gt_copy_cstring(char A_Restrict dst[]/*out*/, const char *A_Restrict begin, const char *end, size_t removed);

#ifndef SAL_DEFS_H_INCLUDED
#undef A_Restrict
#endif

#ifdef __cplusplus
}
#endif

#endif /* CSTRING_PARSER_H_INCLUDED */
