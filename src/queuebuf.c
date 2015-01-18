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

	$RCSfile: queuebuf.c,v $
	$Revision: 1.5 $
	$Date: 2010/04/14 03:07:44 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: Queue Buffer Container Implementation

	Many of the queue functions depends upon:
	1. SCL_ALLOCATOR() setting allocated memory to binary 0,
	2. SCL_ALLOCATOR() returning NULL if memory allocation fails and
	3. NULL being equal to binary 0.

CHANGE LOG

	04apr10	drj	Added callback context pointer to queuebuf_foreach().

	06jun06	drj	Miscellaneous format finessing.

	05dec02	drj	Changed "push" to "put" and "pull" to "get".

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
#include	<string.h>

/*
 * Posix Header Files
 */
#ifdef	_unix
#   include	<unistd.h> /* always first amongst POSIX header files */
#endif

/*
 * Project Specific Header Files
 */
#include	"SCL_queuebuf.h"


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

typedef struct S_node_t
   {
   size_t head;
   size_t tail;
   size_t size;
   }
   S_node_t;

typedef struct S_queuebuf_t
   {
   size_t   head;
   size_t   tail;
   size_t   count;
   size_t   headerCount;
   size_t   bufferAvail;
   size_t   bufferSize;
   S_node_t header[0];
   }
   S_queuebuf_t;


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

static __inline__ int put_empty_queue (S_queuebuf_t*, const void*, size_t);
static __inline__ int put_nonempty_queue (S_queuebuf_t*, const void*, size_t);


/*****************************************************************************
 * Private Function put_empty_queue
 *****************************************************************************/

static __inline__ int put_empty_queue (
                                      S_queuebuf_t* a_qbuf,
                                      const void*   a_data,
                                      size_t        a_size
                                      )
   {
   char* const data = (char* const)&a_qbuf->header[ a_qbuf->headerCount ];

   /* add the message */
   (void)memcpy (data, a_data, a_size);

   /* update the header array */
   a_qbuf->header[0].head = 0;
   a_qbuf->header[0].tail = a_size-1;
   a_qbuf->header[0].size = a_size;

   /* update the head, tail */
   a_qbuf->head = 0;
   a_qbuf->tail = 0;

   /* update the count */
   a_qbuf->count = 1;

   /* update the available buffer size */
   a_qbuf->bufferAvail -= a_size;

   return SCL_OK;
   }


/*****************************************************************************
 * Private Function put_nonempty_queue
 *****************************************************************************/

static __inline__ int put_nonempty_queue (
                                         S_queuebuf_t* a_qbuf,
                                         const void*   a_data,
                                         size_t        a_size
                                         )
   {
   char* const data = (char* const)&a_qbuf->header[ a_qbuf->headerCount ];
   size_t h; /* head */
   size_t d; /* Destination index: decreasing index in data. */
   size_t c; /* Source count: decreasing index in the new message. */

   S_node_t*   node;

   h = a_qbuf->header[ a_qbuf->head ].head;
   d = h;
   c = a_size;

   /*
    * Add the new message to the buffer, backwards with a possible wrap to
    * the end of the buffer;
    */
   while (c > 0)
      {
      d = d == 0 ? a_qbuf->bufferSize - 1 : d - 1;
      data[d] = ((char*)a_data)[--c];
      }

   /* update the head */
   if (a_qbuf->head == 0)
      a_qbuf->head = a_qbuf->headerCount - 1;
   else
      a_qbuf->head = a_qbuf->head - 1;

   /* update the header array */
   node = &a_qbuf->header[a_qbuf->head];
   node->head = d;
   node->tail = h == 0 ? a_qbuf->bufferSize - 1 : h - 1;
   node->size = a_size;

   /* update the count */
   a_qbuf->count += 1;

   /* update the available buffer size */
   a_qbuf->bufferAvail -= a_size;

   return SCL_OK;
   }


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/*****************************************************************************
 * Public Function queuebuf_init
 *****************************************************************************/

int (queuebuf_init) (void* a_qbuf, size_t a_qbufSize, size_t a_count)
   {
   const size_t s = sizeof(S_queuebuf_t) + (sizeof(S_node_t) * a_count);
   S_queuebuf_t* const buff = (S_queuebuf_t*)a_qbuf;

   if (s > a_qbufSize) return -(int)(s - a_qbufSize);

   buff->head = buff->tail = -1;
   buff->count = 0;
   buff->headerCount = a_count;
   buff->bufferSize = a_qbufSize - s;
   buff->bufferAvail = a_qbufSize - s;

   return (int)(a_qbufSize - s);
   }


/*****************************************************************************
 * Public Function queuebuf_erase
 *****************************************************************************/

void (queuebuf_erase) (void* a_qbuf)
   {
   S_queuebuf_t* const buff = (S_queuebuf_t*)a_qbuf;
   buff->head = buff->tail = -1;
   buff->count = 0;
   buff->bufferAvail = buff->bufferSize;
   }


/*****************************************************************************
 * Public Function queuebuf_count
 *****************************************************************************/

size_t (queuebuf_count) (void* a_qbuf)
   {
   S_queuebuf_t* const buff = (S_queuebuf_t*)a_qbuf;
   return buff->count;
   }


/*****************************************************************************
 * Public Function queuebuf_header_size
 *****************************************************************************/

size_t (queuebuf_header_size) (void* a_qbuf)
   {
   S_queuebuf_t* const buff = (S_queuebuf_t*)a_qbuf;
   return sizeof(S_queuebuf_t) + (sizeof(S_node_t) * buff->headerCount);
   }


/*****************************************************************************
 * Public Function queuebuf_buff_size
 *****************************************************************************/

size_t (queuebuf_buff_size) (void* a_qbuf)
   {
   S_queuebuf_t* const buff = (S_queuebuf_t*)a_qbuf;
   return buff->bufferSize;
   }


/*****************************************************************************
 * Public Function queuebuf_buff_used
 *****************************************************************************/

size_t (queuebuf_buff_used) (void* a_qbuf)
   {
   S_queuebuf_t* const buff = (S_queuebuf_t*)a_qbuf;
   return buff->bufferSize - buff->bufferAvail;
   }


/*****************************************************************************
 * Public Function queuebuf_buff_avail
 *****************************************************************************/

size_t (queuebuf_buff_avail) (void* a_qbuf)
   {
   S_queuebuf_t* const buff = (S_queuebuf_t*)a_qbuf;
   return buff->bufferAvail;
   }


/*****************************************************************************
 * Public Function queuebuf_put
 *****************************************************************************/

int (queuebuf_put) (void* a_qbuf, const void* a_data, size_t a_size)
   {
   int stat;

   S_queuebuf_t* const buff = (S_queuebuf_t*)a_qbuf;

   if (buff->count == buff->headerCount) return SCL_NOSVC;
   if (buff->bufferAvail < a_size) return SCL_NOSVC;

   if (buff->count == 0)
      stat = put_empty_queue (buff, a_data, a_size);
   else
      stat = put_nonempty_queue (buff, a_data, a_size);

   return stat;
   }


/*****************************************************************************
 * Public Function queuebuf_peek
 *****************************************************************************/

int (queuebuf_peek) (void* a_qbuf, void** a_data, size_t* a_size)
   {
   S_queuebuf_t* const buff = (S_queuebuf_t*)a_qbuf;
   const S_node_t* node;
   const char* data;

   if (buff->count == 0) return SCL_NOTFOUND;

   node = &buff->header[ buff->tail ];
   data = (char*)&buff->header[buff->headerCount];

   if (a_data != NULL) *a_data = (void*)&data[ node->head ];
   if (a_size != NULL) *a_size = node->size;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function queuebuf_get
 *****************************************************************************/

int (queuebuf_get) (void* a_qbuf, void* a_data, size_t* a_size)
   {
   S_queuebuf_t* const buff = (S_queuebuf_t*)a_qbuf;
   const S_node_t* node;
   const char* data;
   char* dst;
   size_t d;
   size_t c;

   if (buff->count == 0) return SCL_NOSVC;

   node = &buff->header[ buff->tail ];
   data = (char*)&buff->header[buff->headerCount];
   dst = (char*)a_data;

   d = node->head;
   c = node->size;
   while (c-- > 0)
      {
      *dst++ = data[d++];
      if (d == buff->bufferSize) d = 0;
      }
   *a_size = node->size;

   buff->count -= 1;
   buff->bufferAvail += node->size;

   if (buff->count == 0)
      buff->head = buff->tail = -1;
   else
      buff->tail = buff->tail > 0 ? buff->tail - 1 : buff->headerCount - 1;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function queuebuf_get_alloc
 *****************************************************************************/

int (queuebuf_get_alloc) (void* a_qbuf, void** a_data, size_t* a_size)
   {
   S_queuebuf_t* const buff = (S_queuebuf_t*)a_qbuf;
   const S_node_t* node;
   const char* data;
   char* dst;
   size_t d;
   size_t c;

   if (buff->count == 0) return SCL_NOSVC;

   node = &buff->header[ buff->tail ];
   data = (char*)&buff->header[buff->headerCount];

   dst = SCL_ALLOCATOR (node->size);
   if (dst == NULL) return SCL_NOMEM;
   *a_data = dst;

   d = node->head;
   c = node->size;
   while (c-- > 0)
      {
      *dst++ = data[d++];
      if (d == buff->bufferSize) d = 0;
      }
   *a_size = node->size;

   buff->count -= 1;
   buff->bufferAvail += node->size;

   if (buff->count == 0)
      buff->head = buff->tail = -1;
   else
      buff->tail = buff->tail > 0 ? buff->tail - 1 : buff->headerCount - 1;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function queuebuf_foreach
 *****************************************************************************/

void (queuebuf_foreach) (void* a_qbuf, SCL_cbfn_t a_func, void* a_context)
   {
   const S_queuebuf_t* const buff = (S_queuebuf_t*)a_qbuf;
   const char* const data = (const char* const)&buff->header[buff->headerCount];
   size_t c = buff->count;
   size_t i = buff->head;

   const S_node_t* node;
   int stat;

   while (c-- > 0)
      {
      node = &buff->header[i];
      stat = (*a_func) (
                       NULL,
                       (long)node->size,
                       (void*)&data[node->head],
                       a_context
                       );
      if (stat != SCL_NOTFOUND) return;
      if (++i == buff->headerCount) i = 0;
      }

   return;
   }


/* end of file */
