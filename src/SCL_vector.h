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

	$RCSfile: SCL_vector.h,v $
	$Revision: 1.6 $
	$Date: 2010/04/14 03:12:30 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: Vector Container Implementation

CHANGE LOG

	04apr10	drj	Added callback context pointer to vector_foreach().

	06jun06	drj	Miscellaneous format finessing.

	11jul05	drj	Mindless rename of inclusion-control macro.

	26nov04	drj	Added vector_back().  Changed vector_update() to
			vector_replace().

	16nov04	drj	File generation.

***************************************************************************** */


#ifndef SCL_VECTOR_H
#define SCL_VECTOR_H 1


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

typedef   struct S_SCL_vector_t*   SCL_vector_t;


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

extern DECLS SCL_vector_t DECLC vector_new (void);
extern DECLS void DECLC vector_del (SCL_vector_t v);
extern DECLS void DECLC vector_erase (SCL_vector_t v);
extern DECLS size_t DECLC vector_size (SCL_vector_t v);
extern DECLS size_t DECLC vector_count (SCL_vector_t v);
extern DECLS int DECLC vector_push_back (SCL_vector_t v, const void* d);
extern DECLS int DECLC vector_replace (SCL_vector_t v, size_t i, const void* d);
extern DECLS void* DECLC vector_pop_back (SCL_vector_t v);
extern DECLS void* DECLC vector_back (SCL_vector_t v);
extern DECLS void* DECLC vector_access (SCL_vector_t v, size_t i);
extern DECLS SCL_iterator_t DECLC vector_at (SCL_vector_t v, size_t i);
extern DECLS SCL_iterator_t DECLC vector_begin (SCL_vector_t v);
extern DECLS SCL_iterator_t DECLC vector_end (SCL_vector_t v);
extern DECLS SCL_iterator_t DECLC vector_next (SCL_iterator_t i);
extern DECLS SCL_iterator_t DECLC vector_prev (SCL_iterator_t i);
extern DECLS void DECLC vector_data_set (SCL_iterator_t i, const void* d);
extern DECLS void* DECLC vector_data_get (SCL_iterator_t i);
extern DECLS void DECLC vector_foreach (SCL_vector_t v, SCL_cbfn_t f, void* c);
extern DECLS void DECLC vector_reverse (SCL_vector_t v);


#ifdef	__cplusplus
}
#endif


#endif
