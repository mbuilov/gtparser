#ifndef INT_CHAR_H_INCLUDED
#define INT_CHAR_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_char.h */

/* top-most bit for a given type:
  char  -> 0x80
  short -> 0x8000, etc. */
#define GT_TYPE_TOP_BIT(uint_type, type) ((uint_type)1 << (sizeof(type)*8 - 1 +  \
	/*type <= uint_type*/0*sizeof(int[1-2*(sizeof(type) > sizeof(uint_type))]) + \
	/*byte has 8 bits*/0*sizeof(int[1-2*(255 != (unsigned char)-1)])))

/* maximum value of a type:
  char  -> 0xFF
  short -> 0xFFFF, etc. */
#define GT_TYPE_MASK(uint_type, type) \
	((GT_TYPE_TOP_BIT(uint_type, type) - (uint_type)1) | GT_TYPE_TOP_BIT(uint_type, type))

/* convert type to unsigned integer,
  because type may be signed, need to mask-out sign-extended bits */
#define GT_TYPE_TO_UINT(uint_type, type, c) \
	((uint_type)(GT_TYPE_MASK(uint_type, type) & (uint_type)(c)))

/* top-most bit for a given character type:
  char    -> 0x80
  wchar_t -> 0x8000 (windows) or 0x80000000 (unix) */
#define GT_CHAR_TOP_BIT(char_type) GT_TYPE_TOP_BIT(unsigned, char_type)

/* maximum value of a character type:
  char    -> 0xFF
  wchar_t -> 0xFFFF (windows) or 0xFFFFFFFF (unix) */
#define GT_CHAR_MASK(char_type) GT_TYPE_MASK(unsigned, char_type)

/* convert character type to unsigned integer,
  because type may be signed, need to mask-out sign-extended bits */
#define GT_CHAR_TO_UINT(char_type, c) GT_TYPE_TO_UINT(unsigned, char_type, c)

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
#define GT_ONE_ONE_CONST(char_type, uint_type) ((uint_type)-1/(uint_type)GT_CHAR_MASK(char_type))

/* get difference of two unsigned integers: a - b */
/* note: 'a' and 'b' are expanded many times */
#ifdef UBSAN_UNSIGNED_OVERFLOW
#define GT_UINT_DIFF(type, a, b)                              \
	(((a) < (b) ? (a) + ((type)-1 - (b)) + 1u : (a) - (b)) +  \
	/*type is unsigned*/0*!sizeof(int[1-2*((type)-1 <= 0)]) + \
	0*!sizeof(int[1-2*(sizeof(type) < sizeof(a))]) +          \
	0*!sizeof(int[1-2*(sizeof(type) < sizeof(b))]))
#else
#define GT_UINT_DIFF(type, a, b) ((a) - (b) +                 \
	/*type is unsigned*/0*!sizeof(int[1-2*((type)-1 <= 0)]) + \
	0*!sizeof(int[1-2*(sizeof(type) < sizeof(a))]) +          \
	0*!sizeof(int[1-2*(sizeof(type) < sizeof(b))]))
#endif

/*=============================================================== */

#define GT_IS_UINT_CHARS_IN_RANGE_(char_type, uint_type, a, b, c, r) do {                           \
	const uint_type gt_aa_ = GT_ONE_ONE_CONST(char_type, uint_type)*GT_CHAR_TO_UINT(char_type, a);  \
	const uint_type gt_bb_ = GT_ONE_ONE_CONST(char_type, uint_type)*GT_CHAR_TO_UINT(char_type, b);  \
	const uint_type gt_dd_ = GT_ONE_ONE_CONST(char_type, uint_type)*GT_CHAR_TOP_BIT(char_type) + 1; \
	const uint_type gt_cc_ = (c) + 0*sizeof(int[1-2*(sizeof(uint_type) != sizeof(c))]);             \
	const uint_type gt_x_ = GT_UINT_DIFF(uint_type, gt_cc_, gt_aa_);                                \
	const uint_type gt_y_ = GT_UINT_DIFF(uint_type, gt_cc_, gt_bb_);                                \
	const uint_type gt_z_ = GT_UINT_DIFF(uint_type, gt_y_, gt_dd_);                                 \
	r = !((gt_x_ | gt_z_) & (GT_ONE_ONE_CONST(char_type, uint_type)*GT_CHAR_TOP_BIT(char_type)));   \
} while (0)

/* check that all chars read into an integer are in given (small) range,
 e.g.:
  int r;
  unsigned c;
  memcpy(&c, L"string", sizeof(c));
  GT_IS_UINT_CHARS_IN_RANGE(wchar_t, unsigned, L'a', L'z', c, r);
*/
/* note: "small" - (u-l) must be less than half of the character range:
  < 128   - for 8-bit char,
  < 32768 - for 16-bit char, etc. */
#define GT_IS_UINT_CHARS_IN_RANGE(char_type, uint_type, l, u, c, r)    \
	GT_IS_UINT_CHARS_IN_RANGE_(char_type, uint_type,                   \
		(/*check that (u - l) is small enough*/(void)sizeof(int[1-2*!( \
			(u) - (l) < GT_CHAR_TOP_BIT(char_type))]),(l)), u, c, r)

/*=============================================================== */

#define GT_UINT_ALL_GE_(char_type, uint_type, b, c, r) do {                                        \
	const uint_type gt_cc_ = (c) + 0*sizeof(int[1-2*(sizeof(uint_type) != sizeof(c))]);            \
	const uint_type gt_bb_ = GT_ONE_ONE_CONST(char_type, uint_type)*GT_CHAR_TO_UINT(char_type, b); \
	const uint_type gt_x_ = GT_UINT_DIFF(uint_type, gt_cc_, gt_bb_);                               \
	r = !(gt_x_ & ~gt_cc_ & (GT_ONE_ONE_CONST(char_type, uint_type)*GT_CHAR_TOP_BIT(char_type)));  \
} while (0)

/* check that all chars read into an integer are greater or equal to some (small) char
 e.g.:
  int r;
  unsigned c;
  memcpy(&c, L"string", sizeof(c));
  GT_UINT_ALL_GE(wchar_t, unsigned, L' ', c, r);
*/
/* note: "small" - b must be not greater than half of the character range:
  <= 128   - for 8-bit char,
  <= 32768 - for 16-bit char, etc. */
#define GT_UINT_ALL_GE(char_type, uint_type, b, c, r)                                 \
	GT_UINT_ALL_GE_(char_type, uint_type,                                             \
		(/*check that b is small enough*/(void)sizeof(int[1-2*(                       \
			GT_CHAR_TO_UINT(char_type, b) > GT_CHAR_TOP_BIT(char_type))]),(b)), c, r)

/* check if there is a zero char among chars read into an integer,
 e.g.:
  int r;
  unsigned c;
  memcpy(&c, L"string", sizeof(c));
  GT_UINT_ALL_NOZERO(wchar_t, unsigned, c, r);
*/
#define GT_UINT_ALL_NOZERO(char_type, uint_type, c, r) \
	GT_UINT_ALL_GE(char_type, uint_type, 1, c, r)

/*=============================================================== */

#define GT_UINT_ALL_LE_(char_type, uint_type, a, c, r) do {                                           \
	const uint_type gt_cc_ = (c) + 0*sizeof(int[1-2*(sizeof(uint_type) != sizeof(c))]);               \
	const uint_type gt_dd_ = GT_ONE_ONE_CONST(char_type, uint_type)*(GT_CHAR_TOP_BIT(char_type) - 1); \
	const uint_type gt_aa_ = GT_ONE_ONE_CONST(char_type, uint_type)*GT_CHAR_TO_UINT(char_type, a);    \
	const uint_type gt_bb_ = GT_UINT_DIFF(uint_type, gt_dd_, gt_aa_);                                 \
	const uint_type gt_x_ = gt_cc_ + gt_bb_;                                                          \
	r = !((gt_x_ | gt_cc_) & (GT_ONE_ONE_CONST(char_type, uint_type)*GT_CHAR_TOP_BIT(char_type)));    \
} while (0)

/* check that all chars read into an integer are less or equal to some (small) char
 e.g.:
  int r;
  unsigned c;
  memcpy(&c, L"string", sizeof(c));
  GT_UINT_ALL_LE(wchar_t, unsigned, L' ', c, r);
*/
/* note: "small" - a must be less than half of the character range:
  < 128   - for 8-bit char,
  < 32768 - for 16-bit char, etc. */
#define GT_UINT_ALL_LE(char_type, uint_type, a, c, r)                                 \
	GT_UINT_ALL_LE_(char_type, uint_type,                                             \
		(/*check that a is small enough*/(void)sizeof(int[1-2*(                       \
			GT_CHAR_TO_UINT(char_type, a) >= GT_CHAR_TOP_BIT(char_type))]),(a)), c, r)

#endif /* INT_CHAR_H_INCLUDED */
