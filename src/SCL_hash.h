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

	$RCSfile: SCL_hash.h,v $
	$Revision: 1.8 $
	$Date: 2010/04/14 03:09:37 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: Hash Container Implementation

CHANGE LOG

	04apr10	drj	Added callback context pointer to hash_foreach().

	06jun06	drj	Miscellaneous format finessing.

	11jul05	drj	Mindless rename of inclusion-control macro.

	10dec04	drj	Added hash_key_get().

	26nov04	drj	Changed hash_update() to hash_replace().

	16nov04	drj	File generation.

***************************************************************************** */


#ifndef SCL_HASH_H
#define SCL_HASH_H 1


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

typedef   struct S_SCL_hash_t*   SCL_hash_t;


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

extern DECLS SCL_hash_t DECLC hash_new (SCL_mdfn_t mdfn);
extern DECLS void DECLC hash_del (SCL_hash_t h);
extern DECLS void DECLC hash_erase (SCL_hash_t h);
extern DECLS size_t DECLC hash_size (SCL_hash_t h);
extern DECLS size_t DECLC hash_count (SCL_hash_t h);
extern DECLS int DECLC hash_insert (SCL_hash_t h, const char* k, const void* d);
extern DECLS int DECLC hash_replace (SCL_hash_t h,const char* k,const void* d);
extern DECLS void* DECLC hash_remove (SCL_hash_t h, const char* k);
extern DECLS void* DECLC hash_access (SCL_hash_t h, const char* k);
extern DECLS SCL_iterator_t DECLC hash_at (SCL_hash_t h, const char* k);
extern DECLS SCL_iterator_t DECLC hash_begin (SCL_hash_t h);
extern DECLS SCL_iterator_t DECLC hash_end (SCL_hash_t h);
extern DECLS SCL_iterator_t DECLC hash_next (SCL_iterator_t i);
extern DECLS SCL_iterator_t DECLC hash_prev (SCL_iterator_t i);
extern DECLS void DECLC hash_data_set (SCL_iterator_t i, const void* d);
extern DECLS void* DECLC hash_data_get (SCL_iterator_t i);
extern DECLS const char* DECLC hash_key_get (SCL_iterator_t i);
extern DECLS void DECLC hash_foreach (SCL_hash_t h, SCL_cbfn_t f, void* c);


#ifdef	__cplusplus
}
#endif


#endif
