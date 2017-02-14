#ifndef GTPARSER_CONFIG_H_INCLUDED
#define GTPARSER_CONFIG_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* gtparser_config.h */

/* define needed external functions */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef _DEBUG
#include <assert.h>
#define ASSERT(cond) assert(cond)
#else
#define ASSERT(cond) ((void)0)
#endif

#define STRLEN(str)         strlen(str)
#define MEMMOVE(dst,src,sz) memmove(dst,src,sz)
#define MEMCPY(dst,src,sz)  memcpy(dst,src,sz)
#define SPRINTF             sprintf
#ifdef WIN32
#define VSNPRINTF(buf,sz,format,ap) _vsnprintf(buf,sz,format,ap)
#else
#define VSNPRINTF(buf,sz,format,ap) vsnprintf(buf,sz,format,ap)
#endif

#endif /* GTPARSER_CONFIG_H_INCLUDED */
