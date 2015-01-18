/*
 * This file is part of the SCL software.
 * The license which this software falls under is as follows:
 *
 * Copyright (C) 2004-2015 Douglas Jerome <douglas@ttylinux.org>
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

	Name:     SCL_map.h
	Revision: 1.6
	Date:     2010-04-14

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@ttylinux.org>

FILE DESCRIPTION

	Small Container Library: Map Container Implementation

CHANGE LOG

	04apr10	drj	Added callback context pointer to map_foreach().

	06jun06	drj	Miscellaneous format finessing.

	11jul05	drj	Mindless rename of inclusion-control macro.

	26nov04	drj	Changed map_update() to map_replace().

	16nov04	drj	File generation.

***************************************************************************** */


#ifndef SCL_MAP_H
#define SCL_MAP_H 1


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

typedef   struct S_SCL_map_t*   SCL_map_t;


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

extern DECLS SCL_map_t DECLC map_new (void);
extern DECLS void DECLC map_del (SCL_map_t m);
extern DECLS void DECLC map_erase (SCL_map_t m);
extern DECLS size_t DECLC map_size (SCL_map_t m);
extern DECLS size_t DECLC map_count (SCL_map_t m);
extern DECLS int DECLC map_insert (SCL_map_t m, long k, const void* d);
extern DECLS int DECLC map_replace (SCL_map_t m, long k, const void* d);
extern DECLS void* DECLC map_remove (SCL_map_t m, long k);
extern DECLS void* DECLC map_access (SCL_map_t m, long k);
extern DECLS SCL_iterator_t DECLC map_at (SCL_map_t m, long k);
extern DECLS SCL_iterator_t DECLC map_begin (SCL_map_t m);
extern DECLS SCL_iterator_t DECLC map_end (SCL_map_t m);
extern DECLS SCL_iterator_t DECLC map_next (SCL_iterator_t i);
extern DECLS SCL_iterator_t DECLC map_prev (SCL_iterator_t i);
extern DECLS void DECLC map_data_set (SCL_iterator_t i, const void* d);
extern DECLS void* DECLC map_data_get (SCL_iterator_t i);
extern DECLS void DECLC map_foreach (SCL_map_t m, SCL_cbfn_t f, void* c);


#ifdef	__cplusplus
}
#endif


#endif
