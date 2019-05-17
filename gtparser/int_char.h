#ifndef INT_CHAR_H_INCLUDED
#define INT_CHAR_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_char.h */

/* integer constant, for sizeof(char_type)/sizeof(uint_type):
  1/1: 0x01,
  1/2: 0x0101,
  1/4: 0x01010101,
  1/8: 0x0101010101010101;
  2/2: 0x0001,
  2/4: 0x00010001,
  2/8: 0x0001000100010001;
  4/4: 0x00000001,
  4/8: 0x0000000100000001;
  8/8: 0x0000000000000001. */
#define GT_ONE_ONE_CONST(char_type, uint_type) \
	(((uint_type)!!(sizeof(char_type)&0x1) << 8*(sizeof(uint_type) > 1)*(sizeof(uint_type) - 1)) | \
	 ((uint_type)!!(sizeof(char_type)&0x3) << 8*(sizeof(uint_type) > 2)*(sizeof(uint_type) - 2)) | \
	 ((uint_type)!!(sizeof(char_type)&0x1) << 8*(sizeof(uint_type) > 3)*(sizeof(uint_type) - 3)) | \
	 ((uint_type)!!(sizeof(char_type)&0x7) << 8*(sizeof(uint_type) > 4)*(sizeof(uint_type) - 4)) | \
	 ((uint_type)!!(sizeof(char_type)&0x1) << 8*(sizeof(uint_type) > 5)*(sizeof(uint_type) - 5)) | \
	 ((uint_type)!!(sizeof(char_type)&0x3) << 8*(sizeof(uint_type) > 6)*(sizeof(uint_type) - 6)) | \
	 ((uint_type)!!(sizeof(char_type)&0x1) << 8*(sizeof(uint_type) > 7)*(sizeof(uint_type) - 7)) | \
	 ((uint_type)0x01 +                                                                            \
	 /*uint_type is unsigned*/0*(uint_type)sizeof(int[1-2*((uint_type)-1 <= 0)]) +                 \
	 0*(uint_type)sizeof(int[1-2*(sizeof(char_type) > 8 || sizeof(uint_type) > 8)])))

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

/* convert character to unisgned integer,
  because char may be signed, need to mask-out sign-extended bits */
#define GT_CHAR_TO_UINT(c) ((unsigned)(c) & /*mask-out sign-extended bits*/(  \
	/*byte has 8 bits*/0*sizeof(int[1-2*(255 != (unsigned char)-1)]) +        \
	/*char type is small*/0*sizeof(int[1-2*(sizeof(c) > sizeof(unsigned))]) + \
	/*construct mask*/(((1u << (8*sizeof(c) - 1)) - 1u) | (1u << (8*sizeof(c) - 1)))))

/* check that chars read into an integer are latin letters (there are only 26 letters),
 e.g.:
  int r;
  unsigned c;
  memcpy(&c, L"string", sizeof(c));
  GT_IS_LATIN_UINT_IN_RANGE(wchar_t, unsigned, L'a', L'z', c, r);
*/
#define GT_IS_LATIN_UINT_IN_RANGE(char_type, uint_type, l, u, c, r) do {                        \
	/* assume: (u - l) < 32,                                                                    \
	  .............bbbbb.......                                                                 \
	   ^0   ^u-31  ^l  ^u                                                                       \
	 1) check that all chars of int are >= l: (c - l) should not overflow                       \
	 2) check that all chars of int are < u:  (c - (u-31)) should be < 32 */                    \
	const uint_type gt_ll_ = GT_ONE_ONE_CONST(char_type, uint_type)*GT_CHAR_TO_UINT(l);         \
	const uint_type gt_uu_ = GT_ONE_ONE_CONST(char_type, uint_type)*(GT_CHAR_TO_UINT(u) - 31u); \
	const uint_type gt_zz_ = ~(GT_ONE_ONE_CONST(char_type, uint_type)*0x1F);                    \
	const uint_type gt_cc_ = (c);                                                               \
	const uint_type gt_x_ = GT_UINT_DIFF(uint_type, gt_cc_, gt_ll_);                            \
	const uint_type gt_y_ = GT_UINT_DIFF(uint_type, gt_cc_, gt_uu_);                            \
	/*check that (u - l) < 32*/(void)sizeof(int[1-2*((u) - (l) >= 32)]);                        \
	r = !((gt_x_ | gt_y_) & gt_zz_);                                                            \
} while (0)

/* check if there is a zero char among chars read into an integer,
 e.g.:
  int r;
  unsigned c;
  memcpy(&c, L"string", sizeof(c));
  GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, c, r);
*/
#define GT_UINT_CONTAINS_ZERO(char_type, uint_type, c, r) do {  \
	const uint_type gt_cc_ = (c) +                              \
		0*sizeof(int[1-2*(sizeof(uint_type) != sizeof(c))]);    \
	r = !!((gt_cc_ - GT_ONE_ONE_CONST(char_type, uint_type)) &  \
		GT_ONE_ONE_CONST(char_type, uint_type)*0x80 & ~gt_cc_); \
} while (0)

#endif /* INT_CHAR_H_INCLUDED */
