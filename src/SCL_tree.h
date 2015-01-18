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

	Name:     SCL_tree.h
	Revision: 1.6
	Date:     2010-04-14

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@ttylinux.org>

FILE DESCRIPTION

	Small Container Library: Tree Container Implementation

CHANGE LOG

	04apr10	drj	Added callback context pointer.

	06jun06	drj	Miscellaneous format finessing.

	11jul05	drj	Mindless rename of inclusion-control macro.

	05jul05	drj	Changed tree_update() to tree_replace().

	16nov04	drj	File generation.

***************************************************************************** */


#ifndef SCL_TREE_H
#define SCL_TREE_H 1


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

enum { SCL_PREFIX, SCL_INFIX, SCL_POSTFIX };
typedef   struct S_SCL_tree_t*   SCL_tree_t;


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

extern DECLS SCL_tree_t DECLC tree_new (void);
extern DECLS void DECLC tree_del (SCL_tree_t t);
extern DECLS void DECLC tree_erase (SCL_tree_t t, SCL_cbfn_t f, void* c);
extern DECLS size_t DECLC tree_count (SCL_tree_t t);
extern DECLS void DECLC tree_stat (
                                  SCL_tree_t t,
                                  size_t* const h,
                                  size_t* const c,
                                  size_t* const r
                                  );
extern DECLS int DECLC tree_insert (SCL_tree_t t, long k, const void* d);
extern DECLS int DECLC tree_replace (SCL_tree_t t, long k, const void* d);
extern DECLS void* DECLC tree_access (SCL_tree_t t, long k);
extern DECLS SCL_iterator_t DECLC tree_at (SCL_tree_t t, long k);
extern DECLS void DECLC tree_data_set (SCL_iterator_t i, const void* d);
extern DECLS void* DECLC tree_data_get (SCL_iterator_t i);
extern DECLS void DECLC tree_foreach (
                                     SCL_tree_t t,
                                     int o,
                                     SCL_cbfn_t f,
                                     void* c
                                     );


#ifdef	__cplusplus
}
#endif


#endif
