/*
  * Project       : CMBC SAP RFC API(IRFC API)
  * Source        : rfc_malloc.h
  * Version       : AIX5.3L 64BIT Version1.2
  * Description   : The communication SAP RFC API PACK
  * Authors       : Create by RFC's ITEM hundsun INC.
  * Create date   : 2008-7-24 21:37:43             
  * Update History:
  * Date          Position    Author        Description
  * ---------------------------------------------------
  */


#ifndef __i_malloc_h
#define __i_malloc_h

#include <stddef.h>
#include <stdlib.h>

/**
 * @file malloc.h
 */

typedef void (*i_malloc_handler_t)();
extern i_malloc_handler_t i_malloc_set_handler(void (*a_handler)());
#ifndef __WP_DEBUG__
extern void *i_malloc(size_t n);
extern void *i_calloc(size_t n, size_t s);
extern void *i_realloc(void *p, size_t n);
extern char *i_strdup (const char *__str);
#else
#define i_malloc	malloc
#define i_calloc	calloc
#define i_realloc	realloc
#define i_strdup	strdup
#endif
#endif
