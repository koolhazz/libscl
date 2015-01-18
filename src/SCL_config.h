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

	$RCSfile: SCL_config.h,v $
	$Revision: 1.4 $
	$Date: 2006/06/07 06:21:19 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: SCL Configuration

CHANGE LOG

	06jun06	drj	Miscellaneous format finessing.

	11jul05	drj	Mindless rename of inclusion-control macro.

	26nov04	drj	Separated shared, static libs for the client flags.

	16nov04	drj	File generation.

***************************************************************************** */


#ifndef SCL_CONFIG_H
#define SCL_CONFIG_H 1


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

extern DECLS const char* DECLC scl_conf_credits (void);
extern DECLS const char* DECLC scl_conf_version (void);
extern DECLS const char* DECLC scl_conf_date (void);
extern DECLS const char* DECLC scl_conf_cflags (void);
extern DECLS const char* DECLC scl_conf_shared_libs (void);
extern DECLS const char* DECLC scl_conf_static_libs (void);

extern DECLS const char* DECLC scl_statstr (int stat);

extern DECLS void* DECLC scl_alloc (size_t size);
extern DECLS void  DECLC scl_free  (void* item);


#ifdef	__cplusplus
}
#endif


#endif
