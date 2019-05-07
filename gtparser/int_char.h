#ifndef INT_CHAR_H_INCLUDED
#define INT_CHAR_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_char.h */

/* integer constant, for sizeof(char_type) - sizeof(int_type):
  1-1: 0x01,
  1-2: 0x0101,
  1-4: 0x01010101,
  1-8: 0x0101010101010101;
  2-2: 0x0001,
  2-4: 0x00010001,
  2-8: 0x0001000100010001;
  4-4: 0x00000001,
  4-8: 0x0000000100000001;
  8-8: 0x0000000000000001. */
#define GT_ONE_ONE_CONST(char_type, int_type) \
	(((int_type)!!(sizeof(char_type)&0x1) << 8*(sizeof(int_type) > 1)*(sizeof(int_type) - 1)) | \
	 ((int_type)!!(sizeof(char_type)&0x3) << 8*(sizeof(int_type) > 2)*(sizeof(int_type) - 2)) | \
	 ((int_type)!!(sizeof(char_type)&0x1) << 8*(sizeof(int_type) > 3)*(sizeof(int_type) - 3)) | \
	 ((int_type)!!(sizeof(char_type)&0x7) << 8*(sizeof(int_type) > 4)*(sizeof(int_type) - 4)) | \
	 ((int_type)!!(sizeof(char_type)&0x1) << 8*(sizeof(int_type) > 5)*(sizeof(int_type) - 5)) | \
	 ((int_type)!!(sizeof(char_type)&0x3) << 8*(sizeof(int_type) > 6)*(sizeof(int_type) - 6)) | \
	 ((int_type)!!(sizeof(char_type)&0x1) << 8*(sizeof(int_type) > 7)*(sizeof(int_type) - 7)) | \
	 ((int_type)0x01 + 0*sizeof(int[1-2*(sizeof(char_type) > 8 || sizeof(int_type) > 8)])))

/* get difference of two unsigned integers: a - b */
#ifdef UBSAN_UNSIGNED_OVERFLOW
#define GT_UINT_DIFF(type, a, b) ((a) < (b) ? (a) + ((type)-1 - (b)) + 1u : (a) - (b))
#else
#define GT_UINT_DIFF(type, a, b) ((a) - (b))
#endif

/* check that chars read into the integer are latin letters (there are only 26 letters) */
#define GT_IS_LATIN_UINT_IN_RANGE(char_type, int_type, l, u, c, r) do {                  \
	/* assume: (u - l) < 32,                                                             \
	  .............bbbbb.......                                                          \
	   ^0   ^u-31  ^l  ^u                                                                \
	 1) check that all chars of int are >= l: (c - l) should not overflow                \
	 2) check that all chars of int are < u:  (c - (u-31)) should be < 32 */             \
	const int_type gt_ll_ = GT_ONE_ONE_CONST(char_type, int_type)*(unsigned)(l);         \
	const int_type gt_uu_ = GT_ONE_ONE_CONST(char_type, int_type)*((unsigned)(u) - 31u); \
	const int_type gt_zz_ = ~(GT_ONE_ONE_CONST(char_type, int_type)*0x1F);               \
	const int_type gt_x_ = GT_UINT_DIFF(int_type, c, gt_ll_);                            \
	const int_type gt_y_ = GT_UINT_DIFF(int_type, c, gt_uu_);                            \
	r = !((gt_x_ | gt_y_) & gt_zz_);                                                     \
} while (0)

#endif /* INT_CHAR_H_INCLUDED */
