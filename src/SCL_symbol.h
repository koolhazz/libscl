/*
 * This file is part of the SCL software.
 * The license which this software falls under is as follows:
 *
 * Copyright (C) 2004-2206 Douglas Jerome <douglas@backstep.org>
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

	$RCSfile: SCL_symbol.h,v $
	$Revision: 1.3 $
	$Date: 2006/06/07 06:21:25 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: Symbol Container Implementation

CHANGE LOG

	06jun06	drj	Miscellaneous format finessing.

	11jul05	drj	Mindless rename of inclusion-control macro.

	16nov04	drj	File generation.

***************************************************************************** */


#ifndef SCL_SYMBOL_H
#define SCL_SYMBOL_H 1


#ifdef	__cplusplus
extern	"C"	{
#endif


/* ************************************************************************* */
/*                                                                           */
/*      I n c l u d e d   F i l e s                                          */
/*                                                                           */
/* ************************************************************************* */

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

enum
   {
   SCL_SYMBOL_NONE = 0,
   SCL_SYMBOL_INT  = 1,
   SCL_SYMBOL_REAL = 2,
   SCL_SYMBOL_PTR  = 3
   };

typedef   struct S_SCL_symbol_t*   SCL_symbol_t;


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

extern DECLS SCL_symbol_t DECLC symbol_new (void);
extern DECLS void         DECLC symbol_del (SCL_symbol_t s);

extern DECLS int  DECLC symbol_stat (SCL_symbol_t s);

extern DECLS void DECLC symbol_int_set (SCL_symbol_t s, long i);
extern DECLS void DECLC symbol_real_set (SCL_symbol_t s, double i);
extern DECLS void DECLC symbol_ptr_set (SCL_symbol_t s, void* i);

extern DECLS long   DECLC symbol_int_get (SCL_symbol_t s);
extern DECLS double DECLC symbol_real_get (SCL_symbol_t s);
extern DECLS void*  DECLC symbol_ptr_get (SCL_symbol_t s);

extern DECLS int DECLC symbol_int_set_safe (SCL_symbol_t s, long i);
extern DECLS int DECLC symbol_real_set_safe (SCL_symbol_t s, double i);
extern DECLS int DECLC symbol_ptr_set_safe (SCL_symbol_t s, void* i);

extern DECLS int DECLC symbol_int_get_safe (SCL_symbol_t s, long* const i);
extern DECLS int DECLC symbol_real_get_safe (SCL_symbol_t s, double* const i);
extern DECLS int DECLC symbol_ptr_get_safe (SCL_symbol_t s, void** const i);


#ifdef	__cplusplus
}
#endif


#endif
