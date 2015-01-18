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

	$RCSfile: symbol.c,v $
	$Revision: 1.2 $
	$Date: 2006/06/07 06:10:47 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: Symbol Container Implementation

CHANGE LOG

	06jun06	drj	Miscellaneous format finessing.

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
#include	"SCL_symbol.h"


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

typedef union U_symbol_t
   {
   long   integer;
   double real;
   void*  pointer;
   }
   U_symbol_t;

typedef struct S_SCL_symbol_t
   {
   char*      name;
   int        flag;
   U_symbol_t value;
   }
   S_SCL_symbol_t;


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
 * Public Function symbol_new
 *****************************************************************************/

SCL_symbol_t (symbol_new) (void)
   {
   return SCL_ALLOCATOR (sizeof(S_SCL_symbol_t));
   }


/*****************************************************************************
 * Public Function symbol_del
 *****************************************************************************/

void (symbol_del) (SCL_symbol_t a_symbol)
   {
   SCL_DEALLOCATOR (a_symbol);
   }


/*****************************************************************************
 * Public Function symbol_stat
 *****************************************************************************/

int (symbol_stat) (SCL_symbol_t a_symbol)
   {
   return a_symbol->flag;
   }


/*****************************************************************************
 * Public Function symbol_int_set
 *****************************************************************************/

void (symbol_int_set) (SCL_symbol_t a_symbol, long a_item)
   {
   a_symbol->flag = SCL_SYMBOL_INT;
   a_symbol->value.integer = a_item;
   }


/*****************************************************************************
 * Public Function symbol_real_set
 *****************************************************************************/

void (symbol_real_set) (SCL_symbol_t a_symbol, double a_item)
   {
   a_symbol->flag = SCL_SYMBOL_REAL;
   a_symbol->value.real = a_item;
   }


/*****************************************************************************
 * Public Function symbol_ptr_set
 *****************************************************************************/

void (symbol_ptr_set) (SCL_symbol_t a_symbol, void* a_item)
   {
   a_symbol->flag = SCL_SYMBOL_PTR;
   a_symbol->value.pointer = a_item;
   }


/*****************************************************************************
 * Public Function symbol_int_get
 *****************************************************************************/

long (symbol_int_get) (SCL_symbol_t a_symbol)
   {
   return a_symbol->value.integer;
   }


/*****************************************************************************
 * Public Function symbol_real_get
 *****************************************************************************/

double (symbol_real_get) (SCL_symbol_t a_symbol)
   {
   return a_symbol->value.real;
   }


/*****************************************************************************
 * Public Function symbol_ptr_get
 *****************************************************************************/

void* (symbol_ptr_get) (SCL_symbol_t a_symbol)
   {
   return a_symbol->value.pointer;
   }


/*****************************************************************************
 * Public Function symbol_int_set_safe
 *****************************************************************************/

int (symbol_int_set_safe) (SCL_symbol_t a_symbol, long a_item)
   {
   if (a_symbol->flag == SCL_SYMBOL_NONE)
      {
      a_symbol->flag = SCL_SYMBOL_INT;
      }
   else
      {
      if (a_symbol->flag != SCL_SYMBOL_INT) return SCL_NOSVC;
      }

   a_symbol->value.integer = a_item;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function symbol_real_set_safe
 *****************************************************************************/

int (symbol_real_set_safe) (SCL_symbol_t a_symbol, double a_item)
   {
   if (a_symbol->flag == SCL_SYMBOL_NONE)
      {
      a_symbol->flag = SCL_SYMBOL_REAL;
      }
   else
      {
      if (a_symbol->flag != SCL_SYMBOL_REAL) return SCL_NOSVC;
      }

   a_symbol->value.real = a_item;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function symbol_ptr_set_safe
 *****************************************************************************/

int (symbol_ptr_set_safe) (SCL_symbol_t a_symbol, void* a_item)
   {
   if (a_symbol->flag == SCL_SYMBOL_NONE)
      {
      a_symbol->flag = SCL_SYMBOL_PTR;
      }
   else
      {
      if (a_symbol->flag != SCL_SYMBOL_PTR) return SCL_NOSVC;
      }

   a_symbol->value.pointer = a_item;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function symbol_int_get_safe
 *****************************************************************************/

int (symbol_int_get_safe) (SCL_symbol_t a_symbol, long* const a_item)
   {
   if (a_symbol->flag != SCL_SYMBOL_INT) return SCL_NOSVC;
   *a_item = a_symbol->value.integer;
   return SCL_OK;
   }


/*****************************************************************************
 * Public Function symbol_real_get_safe
 *****************************************************************************/

int (symbol_real_get_safe) (SCL_symbol_t a_symbol, double* const a_item)
   {
   if (a_symbol->flag != SCL_SYMBOL_REAL) return SCL_NOSVC;
   *a_item = a_symbol->value.real;
   return SCL_OK;
   }


/*****************************************************************************
 * Public Function symbol_ptr_get_safe
 *****************************************************************************/

int (symbol_ptr_get_safe) (SCL_symbol_t a_symbol, void** const a_item)
   {
   if (a_symbol->flag != SCL_SYMBOL_PTR) return SCL_NOSVC;
   *a_item = a_symbol->value.pointer;
   return SCL_OK;
   }


/* end of file */
