#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* bitmap.h */

/* construct bit pattern - value of a bitmap array element at the specified position:
  t - type of array elements,
  o - offset (position of array element - its index),
  c - character constant */
#define GT_SET_BIT1(t,o,c) \
	(((unsigned char)(c) < (o)*8*sizeof(t)) ? (t)0 : \
	((unsigned char)(c) >= ((o) + 1)*8*sizeof(t)) ? (t)0 : \
	((t)1 << ((unsigned char)(c) & (8*sizeof(t) - 1))))

#define GT_SET_BIT2(t,o,c)  (GT_SET_BIT1(t,o,c)|GT_SET_BIT1(t,o,(c)+1))
#define GT_SET_BIT4(t,o,c)  (GT_SET_BIT2(t,o,c)|GT_SET_BIT2(t,o,(c)+2))
#define GT_SET_BIT6(t,o,c)  (GT_SET_BIT4(t,o,c)|GT_SET_BIT2(t,o,(c)+4))
#define GT_SET_BIT10(t,o,c) (GT_SET_BIT6(t,o,c)|GT_SET_BIT4(t,o,(c)+6))
#define GT_SET_BIT20(t,o,c) (GT_SET_BIT10(t,o,c)|GT_SET_BIT10(t,o,(c)+10))
#define GT_SET_BIT26(t,o,c) (GT_SET_BIT20(t,o,c)|GT_SET_BIT6(t,o,(c)+20))

/* construct a sequence of bitmap array elements,
  bm - name of a macro that constructs a bit pattern (combination of GT_SET_BIT... macros) */
#define GT_BITMAP1(t,o,bm)  bm(t,o)
#define GT_BITMAP2(t,o,bm)  GT_BITMAP1(t,o,bm), GT_BITMAP1(t,(o)+1,bm)
#define GT_BITMAP4(t,o,bm)  GT_BITMAP2(t,o,bm), GT_BITMAP2(t,(o)+2,bm)
#define GT_BITMAP8(t,o,bm)  GT_BITMAP4(t,o,bm), GT_BITMAP4(t,(o)+4,bm)
#define GT_BITMAP16(t,o,bm) GT_BITMAP8(t,o,bm), GT_BITMAP8(t,(o)+8,bm)
#define GT_BITMAP32(t,o,bm) GT_BITMAP16(t,o,bm), GT_BITMAP16(t,(o)+16,bm)

/* check if a bit corresponding to a given character is set in the bitmap */
/* note: 'map' and 'c' are used twice in the macro */
#define GT_CHECK_BIT(map,c) \
	(!!((map)[(unsigned char)(c)/(8*sizeof((map)[0]))] & \
		((0*(map)[0] + 1) << ((unsigned char)(c) & (8*sizeof((map)[0]) - 1)))))

/* example of how to use GT_BITMAP... macros to fill bitmap array:
#define CONSTRUCT_BIT_PATTERN(t,o) (GT_SET_BIT1(t,o,'-')|GT_SET_BIT10(t,o,'0')|GT_SET_BIT26(t,o,'a'))
  static const unsigned char bit_map[32] = {GT_BITMAP32(unsigned char, 0, CONSTRUCT_BIT_PATTERN)};
  char c = 'a';
  if (GT_CHECK_BIT(bit_map, c))
    ...
*/

#endif /* BITMAP_H_INCLUDED */
