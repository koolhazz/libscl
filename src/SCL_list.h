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

	$RCSfile: SCL_list.h,v $
	$Revision: 1.7 $
	$Date: 2010/04/14 03:10:07 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: List Container Implementation

CHANGE LOG

	04apr10	drj	Added callback context pointer to list_foreach().

	06jun06	drj	Miscellaneous format finessing.

	11jul05	drj	Mindless rename of inclusion-control macro.

	20jun05	drj	Removed prototype for the non-existing list_replace().

	27nov04	drj	Added list_insert(), list_insert_before(),
			list_insert_after(), and list_remove_at().

	16nov04	drj	File generation.

***************************************************************************** */


#ifndef SCL_LIST_H
#define SCL_LIST_H 1


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

typedef   struct S_SCL_list_t*   SCL_list_t;


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

extern DECLS SCL_list_t DECLC list_new (void);
extern DECLS void DECLC list_del (SCL_list_t l);
extern DECLS void DECLC list_erase (SCL_list_t l);
extern DECLS size_t DECLC list_count (SCL_list_t l);
extern DECLS int DECLC list_insert (SCL_list_t l, size_t i, const void* d);
extern DECLS int DECLC list_push_front (SCL_list_t l, const void* d);
extern DECLS int DECLC list_push_back (SCL_list_t l, const void* d);
extern DECLS void* DECLC list_pop_front (SCL_list_t l);
extern DECLS void* DECLC list_pop_back (SCL_list_t l);
extern DECLS void* DECLC list_remove (SCL_list_t l, size_t i);
extern DECLS void* DECLC list_front (SCL_list_t l);
extern DECLS void* DECLC list_back (SCL_list_t l);
extern DECLS void* DECLC list_access (SCL_list_t l, size_t i);
extern DECLS SCL_iterator_t DECLC list_at (SCL_list_t l, size_t i);
extern DECLS SCL_iterator_t DECLC list_begin (SCL_list_t l);
extern DECLS SCL_iterator_t DECLC list_end (SCL_list_t l);
extern DECLS SCL_iterator_t DECLC list_next (SCL_iterator_t i);
extern DECLS SCL_iterator_t DECLC list_prev (SCL_iterator_t i);
extern DECLS void DECLC list_data_set (SCL_iterator_t i, const void* d);
extern DECLS void* DECLC list_data_get (SCL_iterator_t i);
extern DECLS int DECLC list_insert_before (
                                          SCL_list_t l,
                                          SCL_iterator_t i,
                                          const void* d
                                          );
extern DECLS int DECLC list_insert_after (
                                         SCL_list_t l,
                                         SCL_iterator_t i,
                                         const void* d
                                         );
extern DECLS void* DECLC list_remove_at (SCL_list_t l, SCL_iterator_t i);
extern DECLS void DECLC list_foreach (SCL_list_t l, SCL_cbfn_t f, void* c);
extern DECLS void DECLC list_join (SCL_list_t l1, SCL_list_t l2);
extern DECLS void DECLC list_splice (SCL_list_t l1, size_t i, SCL_list_t l2);
extern DECLS void DECLC list_reverse (SCL_list_t l);


#ifdef	__cplusplus
}
#endif


#endif
