#ifndef INT_CHAR_H_INCLUDED
#define INT_CHAR_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_char.h */

/* top-most bit for a given character type:
  char    -> 0x80
  wchar_t -> 0x8000 (windows) or 0x80000000 (unix) */
#define GT_CHAR_TYPE_TOP_BIT(char_type) (1u << (sizeof(char_type)*8 - 1 +             \
	/*char type is small*/0*sizeof(int[1-2*(sizeof(char_type) > sizeof(unsigned))]) + \
	/*byte has 8 bits*/0*sizeof(int[1-2*(255 != (unsigned char)-1)])))

/* maximum value of a character type:
  char    -> 0xFF
  wchar_t -> 0xFFFF (windows) or 0xFFFFFFFF (unix) */
#define GT_CHAR_TYPE_MASK(char_type) \
	((GT_CHAR_TYPE_TOP_BIT(char_type) - 1u) | GT_CHAR_TYPE_TOP_BIT(char_type))

/* convert character to unsigned integer,
  because char may be signed, need to mask-out sign-extended bits */
#define GT_CHAR_TO_UINT(char_type, c) (GT_CHAR_TYPE_MASK(char_type) & (unsigned)(c))

/* integer constant, for (uint_type)-1/(char_type)-1
  1/1: 0x01,
  2/1: 0x0101,
  4/1: 0x01010101,
  8/1: 0x0101010101010101;
  2/2: 0x0001,
  4/2: 0x00010001,
  8/2: 0x0001000100010001;
  4/4: 0x00000001,
  8/4: 0x0000000100000001;
  8/8: 0x0000000000000001. */
#define GT_ONE_ONE_CONST(char_type, uint_type) ((uint_type)-1/GT_CHAR_TYPE_MASK(char_type))

/* get difference of two unsigned integers: a - b */
/* note: 'a' and 'b' are expanded many times */
#ifdef UBSAN_UNSIGNED_OVERFLOW
#define GT_UINT_DIFF(type, a, b)                             \
	(((a) < (b) ? (a) + ((type)-1 - (b)) + 1u : (a) - (b)) + \
	/*type is unsigned*/0*sizeof(int[1-2*((type)-1 <= 0)]) + \
	0*sizeof(int[1-2*(sizeof(type) < sizeof(a))]) +          \
	0*sizeof(int[1-2*(sizeof(type) < sizeof(b))]))
#else
#define GT_UINT_DIFF(type, a, b) ((a) - (b) +                \
	/*type is unsigned*/0*sizeof(int[1-2*((type)-1 <= 0)]) + \
	0*sizeof(int[1-2*(sizeof(type) < sizeof(a))]) +          \
	0*sizeof(int[1-2*(sizeof(type) < sizeof(b))]))
#endif

#define GT_IS_LATIN_UINT_IN_RANGE_(char_type, uint_type, l, u, c, r) do {                                  \
	/* assume: (u - l) < 32,                                                                               \
	  .............bbbbb.......                                                                            \
	   ^0   ^u-31  ^l  ^u                                                                                  \
	 1) check that all chars of int are >= l: (c - l) should not overflow                                  \
	 2) check that all chars of int are < u:  (c - (u-31)) should be < 32 */                               \
	const uint_type gt_ll_ = GT_ONE_ONE_CONST(char_type, uint_type)*GT_CHAR_TO_UINT(char_type, l);         \
	const uint_type gt_uu_ = GT_ONE_ONE_CONST(char_type, uint_type)*(GT_CHAR_TO_UINT(char_type, u) - 31u); \
	const uint_type gt_zz_ = ~(GT_ONE_ONE_CONST(char_type, uint_type)*0x1F);                               \
	const uint_type gt_cc_ = (c);                                                                          \
	const uint_type gt_x_ = GT_UINT_DIFF(uint_type, gt_cc_, gt_ll_);                                       \
	const uint_type gt_y_ = GT_UINT_DIFF(uint_type, gt_cc_, gt_uu_);                                       \
	r = !((gt_x_ | gt_y_) & gt_zz_);                                                                       \
} while (0)

#define GT_UINT_ALL_GE_(char_type, uint_type, b, c, r) do {                                          \
	const uint_type gt_cc_ = (c) + 0*sizeof(int[1-2*(sizeof(uint_type) != sizeof(c))]);              \
	const uint_type gt_bb_ = GT_ONE_ONE_CONST(char_type, uint_type)*GT_CHAR_TO_UINT(char_type, b);   \
	const uint_type gt_x_ = GT_UINT_DIFF(uint_type, gt_cc_, gt_bb_);                                 \
	r = !(gt_x_ & ~gt_cc_ & GT_ONE_ONE_CONST(char_type, uint_type)*GT_CHAR_TYPE_TOP_BIT(char_type)); \
} while (0)

/* check that all chars read into an integer are latin letters (there are only 26 letters),
 e.g.:
  int r;
  unsigned c;
  memcpy(&c, L"string", sizeof(c));
  GT_IS_LATIN_UINT_IN_RANGE(wchar_t, unsigned, L'a', L'z', c, r);
*/
#define GT_IS_LATIN_UINT_IN_RANGE(char_type, uint_type, l, u, c, r)                         \
	GT_IS_LATIN_UINT_IN_RANGE_(char_type, uint_type,                                        \
		(/*check that (u - l) < 32*/(void)sizeof(int[1-2*((u) - (l) >= 32)]),(l)), u, c, r)

/* check that all chars read into an integer are greater or equal to some (small) char
 e.g.:
  int r;
  unsigned c;
  memcpy(&c, L"string", sizeof(c));
  GT_UINT_ALL_GE(wchar_t, unsigned, L' ', c, r);
*/
#define GT_UINT_ALL_GE(char_type, uint_type, b, c, r)                                      \
	GT_UINT_ALL_GE_(char_type, uint_type,                                                  \
		(/*check that b is small enough*/(void)sizeof(int[1-2*(                            \
			GT_CHAR_TYPE_TOP_BIT(char_type) & GT_CHAR_TO_UINT(char_type, b))]),(b)), c, r)

/* check if there is a zero char among chars read into an integer,
 e.g.:
  int r;
  unsigned c;
  memcpy(&c, L"string", sizeof(c));
  GT_UINT_ALL_NOZERO(wchar_t, unsigned, c, r);
*/
#define GT_UINT_ALL_NOZERO(char_type, uint_type, c, r) \
	GT_UINT_ALL_GE(char_type, uint_type, 1, c, r)

#endif /* INT_CHAR_H_INCLUDED */
