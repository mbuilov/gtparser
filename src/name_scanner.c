/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* name_scanner.c */

#include "gtparser/name_scanner.h"

#ifndef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
#define A_Use_decl_annotations
#endif

typedef int gt_bad_char_0_value[1-2*( 48 != '0')];
typedef int gt_bad_char_9_value[1-2*( 57 != '9')];
typedef int gt_bad_char_A_value[1-2*( 65 != 'A')];
typedef int gt_bad_char_Z_value[1-2*( 90 != 'Z')];
typedef int gt_bad_char___value[1-2*( 95 != '_')];
typedef int gt_bad_char_a_value[1-2*( 97 != 'a')];
typedef int gt_bad_char_z_value[1-2*(122 != 'z')];

const char gt_is_next_name_lookup_table[1u + (unsigned char)-1] = {
/*                      \a \b \t \n \v \f \r                                                        */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* sp  !  "  #  $  %  &  '  (  )  *  +  ,  -  .  /  0  1  2  3  4  5  6  7  8  9  :  ;  <  =  >  ?  */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,11,12,13,14,15,16,17,18,19, 0, 0, 0, 0, 0, 0,
/*  @  A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z  [  \  ]  ^  _  */
    0,20,21,22,23,24,25,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99, 0, 0, 0, 0,99,
/*  '  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  {  |  }  ~ dl  */
    0,20,21,22,23,24,25,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99, 0, 0, 0, 0, 0
};

typedef int gt_lookup_table_size[1-2*(256 != sizeof(gt_is_next_name_lookup_table))];

/* s points to [_a-zA-Z] */
A_Use_decl_annotations
GTPARSER_EXPORTS const char *gt_scan_name(const char *s, const char *const end)
{
	while (++s != end) {
		if (!is_next_name(*s))
			break;
	}
	return s; /* s points to non-[_a-zA-Z0-9], may be to end */
}

/* s points to [_a-zA-Z] */
A_Use_decl_annotations
GTPARSER_EXPORTS const char *gt_scan_name_z(const char *s)
{
	while (is_next_name(*++s));
	return s; /* s points to non-[_a-zA-Z0-9], may be to '\0' */
}
