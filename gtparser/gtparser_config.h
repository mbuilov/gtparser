#ifndef GTPARSER_CONFIG_H_INCLUDED
#define GTPARSER_CONFIG_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* gtparser_config.h */

/* define needed external functions */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef _DEBUG
#include <assert.h>
#endif

#define GTPARSER_STRLEN(str)         strlen(str)
#define GTPARSER_MEMMOVE(dst,src,sz) memmove(dst,src,sz)
#define GTPARSER_MEMCPY(dst,src,sz)  memcpy(dst,src,sz)
#define GTPARSER_ASSERT(cond)        assert(cond)
#define GTPARSER_SPRINTF             sprintf

#endif /* GTPARSER_CONFIG_H_INCLUDED */
