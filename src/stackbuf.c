/*
 * This file is part of the SCL software.
 * The license which this software falls under is as follows:
 *
 * Copyright (C) 2004-2006 Douglas Jerome <douglas@backstep.org>
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

	$RCSfile: stackbuf.c,v $
	$Revision: 1.3 $
	$Date: 2006/06/07 06:10:46 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: Stack Buffer Container Implementation

	Many of the stack functions depends upon:
	1. SCL_ALLOCATOR() setting allocated memory to binary 0,
	2. SCL_ALLOCATOR() returning NULL if memory allocation fails and
	3. NULL being equal to binary 0.

CHANGE LOG

	06jun06	drj	Miscellaneous format finessing.

	06dec04	drj	Cast-away the results of invoking putfn.

	30oct04	drj	File generation.

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
#include	"SCL_stackbuf.h"


/* ************************************************************************* */
/*                                                                           */
/*      C o n s t a n t s                                                    */
/*                                                                           */
/* ************************************************************************* */

/* (none) */


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

typedef struct S_block_t
   {
   size_t size;
   char   data[0];
   }
   S_block_t;

typedef struct S_SCL_stackbuf_t
   {
   SCL_getfn_t getfn;
   SCL_putfn_t putfn;
   S_block_t*  block;
   size_t      blen;
   size_t      nin;
   size_t      nout;
   }
   S_SCL_stackbuf_t;


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
 * Public Function stackbuf_new
 *****************************************************************************/

SCL_stackbuf_t (stackbuf_new) (
                              SCL_getfn_t a_getfn,
                              SCL_putfn_t a_putfn,
                              size_t      a_len
                              )
   {
   S_SCL_stackbuf_t* const s = SCL_ALLOCATOR (sizeof(S_SCL_stackbuf_t));

   s->getfn = a_getfn;
   s->putfn = a_putfn;
   s->blen = sizeof(S_block_t) + a_len;

   return s;
   }


/*****************************************************************************
 * Public Function stackbuf_del
 *****************************************************************************/

void (stackbuf_del) (SCL_stackbuf_t a_stackbuf)
   {
   if (a_stackbuf->block != NULL)
      {
      (void)(*a_stackbuf->putfn) (a_stackbuf->block, a_stackbuf->blen);
      }
   SCL_DEALLOCATOR (a_stackbuf);
   }


/*****************************************************************************
 * Public Function stackbuf_erase
 *****************************************************************************/

void (stackbuf_erase) (SCL_stackbuf_t a_stackbuf)
   {
   if (a_stackbuf->block != NULL)
      {
      SCL_DEALLOCATOR (a_stackbuf->block);
      a_stackbuf->block = NULL;
      }
   }


/*****************************************************************************
 * Public Function stackbuf_size
 *****************************************************************************/

size_t (stackbuf_size) (SCL_stackbuf_t a_stackbuf)
   {
   if (a_stackbuf->block == NULL) return 0;
   return a_stackbuf->block->size;
   }


/*****************************************************************************
 * Public Function stackbuf_nin
 *****************************************************************************/

size_t (stackbuf_nin) (SCL_stackbuf_t a_stackbuf)
   {
   return a_stackbuf->nin;
   }


/*****************************************************************************
 * Public Function stackbuf_nout
 *****************************************************************************/

size_t (stackbuf_nout) (SCL_stackbuf_t a_stackbuf)
   {
   return a_stackbuf->nout;
   }


/*****************************************************************************
 * Public Function stackbuf_push
 *****************************************************************************/

int (stackbuf_push) (
                    SCL_stackbuf_t a_stackbuf,
                    const void*    a_data,
                    size_t         a_len
                    )
   {
   S_block_t* block;
   size_t size;
   size_t blen;
   char* dst;
   const char* src = (const char*)a_data;

   while (a_len > 0)
      {
      block = a_stackbuf->block;

      if (block == NULL)
         {
         block = SCL_ALLOCATOR (a_stackbuf->blen);
         if (block == NULL) return SCL_NOMEM;
         a_stackbuf->block = (S_block_t*)block;
         }

      size = block->size;
      blen = a_stackbuf->blen - sizeof(S_block_t) - size;
      dst = &block->data[size];

      while ((blen > 0) && (a_len > 0))
         {
         *dst++ = *src++;
         blen  -= 1;
         a_len -= 1;
         size  += 1;
         }
      block->size = size;

      if (blen == 0)
         {
         (void)(*a_stackbuf->putfn) ((void*)block, a_stackbuf->blen);
         a_stackbuf->block = NULL;
         a_stackbuf->nout += 1;
         }
      }

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function stackbuf_pull
 *****************************************************************************/

int (stackbuf_pull) (SCL_stackbuf_t a_stackbuf, void* a_data, size_t a_len)
   {
   int count = 0;
   S_block_t* block;
   size_t blen;
   char* dst = (char*)a_data;
   const char* src;

   while (a_len > 0)
      {
      block = a_stackbuf->block;

      if (block == NULL)
         {
         block = (*a_stackbuf->getfn) (a_stackbuf->blen);
         if (block == NULL) return count;
         a_stackbuf->block = (S_block_t*)block;
         a_stackbuf->nin += 1;
         }

      blen = block->size;
      src = &block->data[blen];

      while ((blen > 0) && (a_len > 0))
         {
         *dst++ = *--src;
         blen  -= 1;
         a_len -= 1;
         count += 1;
         }
      block->size = blen;

      if (blen == 0)
         {
         SCL_DEALLOCATOR (a_stackbuf->block);
         a_stackbuf->block = NULL;
         }
      }

   return count;
   }


/*****************************************************************************
 * Public Function stackbuf_pull_alloc
 *****************************************************************************/

int (stackbuf_pull_alloc) (
                          SCL_stackbuf_t a_stackbuf,
                          void** a_data,
                          size_t a_len
                          )
   {
   int count = 0;
   S_block_t* block;
   size_t blen;
   char* dst;
   const char* src;

   dst = SCL_ALLOCATOR (a_len);
   if (dst == NULL) return SCL_NOMEM;
   *a_data = dst;

   while (a_len > 0)
      {
      block = a_stackbuf->block;

      if (block == NULL)
         {
         block = (*a_stackbuf->getfn) (a_stackbuf->blen);
         if (block == NULL) return count;
         a_stackbuf->block = (S_block_t*)block;
         a_stackbuf->nin += 1;
         }

      blen = block->size;
      src = &block->data[blen];

      while ((blen > 0) && (a_len > 0))
         {
         *dst++ = *--src;
         blen  -= 1;
         a_len -= 1;
         count += 1;
         }
      block->size = blen;

      if (blen == 0)
         {
         SCL_DEALLOCATOR (a_stackbuf->block);
         a_stackbuf->block = NULL;
         }
      }

   return count;
   }


/*****************************************************************************
 * Public Function stackbuf_flush
 *****************************************************************************/

int (stackbuf_flush) (SCL_stackbuf_t a_stackbuf)
   {
   if (a_stackbuf->block == NULL) return SCL_NOTFOUND;

   (void)(*a_stackbuf->putfn) (a_stackbuf->block, a_stackbuf->blen);
   a_stackbuf->block = NULL;
   a_stackbuf->nout += 1;

   return SCL_OK;
   }


/* end of file */
