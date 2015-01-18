/*
 * This file is part of the SCL software.
 * The license which this software falls under is as follows:
 *
 * Copyright (C) 2004-2010 Douglas Jerome <douglas@backstep.org>
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


/* *****************************************************************************

FILE NAME

	$RCSfile: vector.c,v $
	$Revision: 1.5 $
	$Date: 2010/04/05 02:28:55 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: Vector Container Implementation

	Many of the vector functions depends upon:
	1. SCL_ALLOCATOR() setting allocated memory to binary 0,
	2. SCL_ALLOCATOR() returning NULL if memory allocation fails and
	3. NULL being equal to binary 0.

CHANGE LOG

	04apr10	drj	Added callback context pointer to vector_foreach().

	31mar10	drj	Fixed bug in vector_back() reported via sf.net project
			bug tracker and via email.

	06jun06	drj	Miscellaneous format finessing.

	26nov04	drj	Added vector_back().  Changed vector_update() to
			vector_replace().

	15nov04	drj	File generation.

***************************************************************************** */


/* ************************************************************************* */
/*                                                                           */
/*      F e a t u r e   S w i t c h e s                                      */
/*                                                                           */
/* ************************************************************************* */

/*
 * Select these feature by moving them from the `if UNDEF' into the `else'
 * section.
 */
#ifdef	UNDEF
#   define	_BSD_SOURCE	1	/* 4.3+bsd subsystems           */
#   define	_POSIX_SOURCE	1	/* posix.1                      */
#   define	_POSIX_C_SOURCE	199309L	/* posix.1 and posix.4          */
#   define	_POSIX_C_SOURCE	199506L	/* posix.1 and posix.4 and MORE */
#else
#   define	_POSIX_C_SOURCE	200112L	/* posix.1 and posix.4 and MORE */
#   undef	_REENTRANT
#   define	_REENTRANT		/* thread-safe for glibc        */
#endif


/* ************************************************************************* */
/*                                                                           */
/*      I n c l u d e d   F i l e s                                          */
/*                                                                           */
/* ************************************************************************* */

/*
 * OS Specific Header Files
 */
#ifdef	WIN32
#   include	"stdafx.h"
#endif

/*
 * Standard C (ANSI) Header Files
 */
/* (none) */

/*
 * Posix Header Files
 */
#ifdef	_unix
#   include	<unistd.h> /* always first amongst POSIX header files */
#endif

/*
 * Project Specific Header Files
 */
#include	"SCL_vector.h"


/* ************************************************************************* */
/*                                                                           */
/*      C o n s t a n t s                                                    */
/*                                                                           */
/* ************************************************************************* */

/*
 * This should have only one bit set.
 */
#define	INITIAL_SIZE	(0x0010)


/* ************************************************************************* */
/*                                                                           */
/*      E x t e r n a l   R e f e r e n c e s                                */
/*                                                                           */
/* ************************************************************************* */

/* (none) */


/* ************************************************************************* */
/*                                                                           */
/*      D a t a   T y p e s   a n d   S t r u c t u r e s                    */
/*                                                                           */
/* ************************************************************************* */

typedef struct S_node_t
   {
   SCL_vector_t vector;
   const void*  data;
   }
   S_node_t;

typedef struct S_SCL_vector_t
   {
   S_node_t* array;
   size_t    count;
   size_t    size;
   size_t    next;
   }
   S_SCL_vector_t;


/* ************************************************************************* */
/*                                                                           */
/*      P u b l i c   G l o b a l   V a r i a b l e s                        */
/*                                                                           */
/* ************************************************************************* */

/* (none) */


/* ************************************************************************* */
/*                                                                           */
/*      P r i v a t e   G l o b a l   V a r i a b l e s                      */
/*                                                                           */
/* ************************************************************************* */

/* (none) */


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (Locally Used Functions)             */
/*                                                                           */
/* ************************************************************************* */


/*****************************************************************************
 * Private Function Prototypes
 *****************************************************************************/

/* (none) */


/*****************************************************************************
 * Private Function
 *****************************************************************************/

/* (none) */


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/*****************************************************************************
 * Public Function vector_new
 *****************************************************************************/

SCL_vector_t (vector_new) (void)
   {
   S_SCL_vector_t* const vector = SCL_ALLOCATOR (sizeof(S_SCL_vector_t));
   if (vector == NULL) return NULL;
   vector->next = INITIAL_SIZE;
   return vector;
   }


/*****************************************************************************
 * Public Function vector_del
 *****************************************************************************/

void (vector_del) (SCL_vector_t a_vector)
   {
   if (a_vector->array != NULL) SCL_DEALLOCATOR (a_vector->array);
   SCL_DEALLOCATOR (a_vector);
   }


/*****************************************************************************
 * Public Function vector_erase
 *****************************************************************************/

void (vector_erase) (SCL_vector_t a_vector)
   {
   if (a_vector->array != NULL) SCL_DEALLOCATOR (a_vector->array);
   a_vector->array = NULL;
   a_vector->count = 0;
   a_vector->size = 0;
   a_vector->next = INITIAL_SIZE;
   }


/*****************************************************************************
 * Public Function vector_size
 *****************************************************************************/

size_t (vector_size) (SCL_vector_t a_vector)
   {
   return a_vector->size;
   }


/*****************************************************************************
 * Public Function vector_count
 *****************************************************************************/

size_t (vector_count) (SCL_vector_t a_vector)
   {
   return a_vector->count;
   }


/*****************************************************************************
 * Public Function vector_push_back
 *****************************************************************************/

int (vector_push_back) (SCL_vector_t a_vector, const void* a_data)
   {
   size_t count = a_vector->count;
   S_node_t* dst = &a_vector->array[count];

   if (a_vector->count == a_vector->size)
      {
      size_t newsize = a_vector->size + a_vector->next;
      size_t i = 0;
      S_node_t* array = SCL_ALLOCATOR (newsize*sizeof(S_node_t));
      const S_node_t* src = a_vector->array;

      if ((dst=array) == NULL) return SCL_NOMEM;

      while (i++ < count) *dst++ = *src++;

      SCL_DEALLOCATOR (a_vector->array);

      a_vector->array = array;
      a_vector->size = newsize;
      a_vector->next <<= 1;
      }

   dst->data = (void*)a_data;
   dst->vector = a_vector;
   a_vector->count = count+1;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function vector_replace
 *****************************************************************************/

int (vector_replace) (SCL_vector_t a_vector, size_t a_index, const void* a_data)
   {
   size_t count = a_vector->count;
   S_node_t* dst = &a_vector->array[a_index];

   if (a_index >= a_vector->size)
      {
      size_t newsize = a_vector->size;
      size_t newnext = a_vector->next;
      size_t i = 0;
      S_node_t* array;
      const S_node_t* src = a_vector->array;

      do
         {
         newsize = newsize + newnext;
         newnext <<= 1;
         }
      while (a_index >= newsize);

      array = SCL_ALLOCATOR (newsize*sizeof(S_node_t));
      if ((dst=array) == NULL) return SCL_NOMEM;

      while (i++ < count) *dst++ = *src++;
      dst->data = (void*)a_data;
      dst->vector = a_vector;
      while (count++ < a_index) dst++->vector = a_vector;

      SCL_DEALLOCATOR (a_vector->array);

      a_vector->array = array;
      a_vector->size  = newsize;
      a_vector->next  = newnext;
      a_vector->count = count+1;

      return SCL_OK;
      }

   dst->data = (void*)a_data;
   dst->vector = a_vector;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function vector_pop_back
 *****************************************************************************/

void* (vector_pop_back) (SCL_vector_t a_vector)
   {
   return (void*)a_vector->array[--(a_vector->count)].data;
   }


/*****************************************************************************
 * Public Function vector_back
 *****************************************************************************/

void* (vector_back) (SCL_vector_t a_vector)
   {
   return (void*)a_vector->array[a_vector->count-1].data;
   }


/*****************************************************************************
 * Public Function vector_access
 *****************************************************************************/

void* (vector_access) (SCL_vector_t a_vector, size_t a_index)
   {
   if (a_index >= a_vector->count) return NULL;
   return (void*)a_vector->array[a_index].data;
   }


/*****************************************************************************
 * Public Function vector_at
 *****************************************************************************/

SCL_iterator_t (vector_at) (SCL_vector_t a_vector, size_t a_index)
   {
   if (a_index >= a_vector->count) return NULL;
   return &a_vector->array[a_index];
   }


/*****************************************************************************
 * Public Function vector_begin
 *****************************************************************************/

SCL_iterator_t (vector_begin) (SCL_vector_t a_vector)
   {
   return &a_vector->array[0];
   }


/*****************************************************************************
 * Public Function vector_end
 *****************************************************************************/

SCL_iterator_t (vector_end) (SCL_vector_t a_vector)
   {
   return &a_vector->array[a_vector->count-1];
   }


/*****************************************************************************
 * Public Function vector_next
 *****************************************************************************/

SCL_iterator_t (vector_next) (SCL_iterator_t a_iterator)
   {
   const S_node_t* node = a_iterator;
   const S_SCL_vector_t* const vector = (S_SCL_vector_t*)node->vector;
   return (void*)(node == &vector->array[vector->count-1] ? NULL : ++node);
   }


/*****************************************************************************
 * Public Function vector_prev
 *****************************************************************************/

SCL_iterator_t (vector_prev) (SCL_iterator_t a_iterator)
   {
   const S_node_t* node = a_iterator;
   const S_SCL_vector_t* const vector = (S_SCL_vector_t*)node->vector;
   return (void*)(node == vector->array ? NULL : --node);
   }


/*****************************************************************************
 * Public Function vector_data_set
 *****************************************************************************/

void (vector_data_set) (SCL_iterator_t a_iterator, const void* a_data)
   {
   ((S_node_t*)a_iterator)->data = (void*)a_data;
   }


/*****************************************************************************
 * Public Function vector_data_get
 *****************************************************************************/

void* (vector_data_get) (SCL_iterator_t a_iterator)
   {
   return (void*)((S_node_t*)a_iterator)->data;
   }


/*****************************************************************************
 * Public Function vector_foreach
 *****************************************************************************/

void (vector_foreach) (
                      SCL_vector_t a_vector,
                      SCL_cbfn_t   a_func,
                      void*        a_context
                      )
   {
   size_t count = a_vector->count;
   const S_node_t* src = a_vector->array;
   int stat = SCL_NOTFOUND;
   long ord = 0;

   while ((count-- > 0) && (stat == SCL_NOTFOUND))
      {
      stat = (*a_func) (NULL, ord++, (void*)src++->data, a_context);
      }
   }


/*****************************************************************************
 * Public Function vector_reverse
 *****************************************************************************/

void (vector_reverse) (SCL_vector_t a_vector)
   {
   S_node_t* head = &a_vector->array[0];
   S_node_t* tail = &a_vector->array[a_vector->count-1];
   const void* t;

   while (head < tail)
      {
      t = head->data;
      head->data = tail->data;
      tail->data = t;
      head += 1;
      tail -= 1;
      }
   }


/* end of file */
