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

	$RCSfile: SCL_stackbuf.h,v $
	$Revision: 1.3 $
	$Date: 2006/06/07 06:21:24 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: Stack Buffer Container Implementation

CHANGE LOG

	06jun06	drj	Miscellaneous format finessing.

	11jul05	drj	Mindless rename of inclusion-control macro.

	16nov04	drj	File generation.

***************************************************************************** */


#ifndef SCL_STACKBUF_H
#define SCL_STACKBUF_H 1


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

typedef   struct S_SCL_stackbuf_t*   SCL_stackbuf_t;


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

extern DECLS SCL_stackbuf_t DECLC stackbuf_new (
                                               SCL_getfn_t g,
                                               SCL_putfn_t p,
                                               size_t l
                                               );
extern DECLS void DECLC stackbuf_del (SCL_stackbuf_t s);
extern DECLS void DECLC stackbuf_erase (SCL_stackbuf_t s);
extern DECLS size_t DECLC stackbuf_size (SCL_stackbuf_t s);
extern DECLS size_t DECLC stackbuf_nin (SCL_stackbuf_t s);
extern DECLS size_t DECLC stackbuf_nout (SCL_stackbuf_t s);
extern DECLS int DECLC stackbuf_push (SCL_stackbuf_t s,const void* d,size_t l);
extern DECLS int DECLC stackbuf_pull (SCL_stackbuf_t s, void* d, size_t l);
extern DECLS int DECLC stackbuf_pull_alloc (
                                           SCL_stackbuf_t s,
                                           void** d,
                                           size_t l
                                           );
extern DECLS int DECLC stackbuf_flush (SCL_stackbuf_t s);


#ifdef	__cplusplus
}
#endif


#endif
