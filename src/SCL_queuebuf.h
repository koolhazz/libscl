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

	$RCSfile: SCL_queuebuf.h,v $
	$Revision: 1.6 $
	$Date: 2010/04/14 03:11:36 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: Queue Buffer Container Implementation

CHANGE LOG

	04apr10	drj	Added callback context pointer to queuebuf_foreach().

	06jun06	drj	Miscellaneous format finessing.

	11jul05	drj	Mindless rename of inclusion-control macro.

	05dec02	drj	Changed "push" to "put" and "pull" to "get".

	16nov04	drj	File generation.

***************************************************************************** */


#ifndef SCL_QUEUEBUF_H
#define SCL_QUEUEBUF_H 1


#ifdef	__cplusplus
extern	"C"	{
#endif


/* ************************************************************************* */
/*                                                                           */
/*      I n c l u d e d   F i l e s                                          */
/*                                                                           */
/* ************************************************************************* */

#ifdef	_unix
#   include	<unistd.h>
#endif
#include	"SCL.h"


/* ************************************************************************* */
/*                                                                           */
/*      M a n i f e s t   C o n s t a n t s                                  */
/*                                                                           */
/* ************************************************************************* */

/* (none) */


/* ************************************************************************* */
/*                                                                           */
/*      D a t a   T y p e s   a n d   S t r u c t u r e s                    */
/*                                                                           */
/* ************************************************************************* */

/* (none) */


/* ************************************************************************* */
/*                                                                           */
/*      P u b l i c   G l o b a l   V a r i a b l e s                        */
/*                                                                           */
/* ************************************************************************* */

/* (none) */


/* ************************************************************************* */
/*                                                                           */
/*      F u n c t i o n   P r o t o t y p e s                                */
/*                                                                           */
/* ************************************************************************* */

extern DECLS int DECLC queuebuf_init (void* q, size_t s, size_t n);
extern DECLS void DECLC queuebuf_erase (void* q);
extern DECLS size_t DECLC queuebuf_count (void* q);
extern DECLS size_t DECLC queuebuf_header_size (void* q);
extern DECLS size_t DECLC queuebuf_buff_size (void* q);
extern DECLS size_t DECLC queuebuf_buff_used (void* q);
extern DECLS size_t DECLC queuebuf_buff_avail (void* q);
extern DECLS int DECLC queuebuf_put (void* q, const void* d, size_t s);
extern DECLS int DECLC queuebuf_peek (void* q, void** d, size_t* s);
extern DECLS int DECLC queuebuf_get (void* q, void* d, size_t* s);
extern DECLS int DECLC queuebuf_get_alloc (void* q, void** d, size_t* s);
extern DECLS void DECLC queuebuf_foreach (void* q, SCL_cbfn_t f, void* c);


#ifdef	__cplusplus
}
#endif


#endif
