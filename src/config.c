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

	$RCSfile: config.c,v $
	$Revision: 1.6 $
	$Date: 2010/04/01 02:14:59 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: SCL Configuration

CHANGE LOG

	31mar10	drj	Changed __COPYRIGHT__, __TIMESTAMP__ and __REVISION__
			to LIBSCL_COPYRIGHT, LIBSCL_TIMESTAMP and
			LIBSCL_REVISION, respectively.  GCC added __TIMESTAMP__
			so all three of were changed to be similar.

	06jun06	drj	Miscellaneous format finessing.

	17jul05	drj	Fixed the scl_conf_credits() function.

	26nov04	drj	Separated shared, static libs for the client flags.

	16nov04	drj	File generation.

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
#if	defined(AUTOCONF)
#   include	"../_AUTOCONF/config.h"
#elif	defined(WIN32)
#   include	"../_MSVC6/win32_config.h"
#elif	defined(_unix)
#   include	"make_config.h"
#else
#   error  ***** Unknown build configuration.
#endif
#include	"SCL.h"
#include	"SCL_config.h"


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

/* (none) */


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
 * Public Config Functions
 *****************************************************************************/

const char* (scl_conf_credits) (void)
   {
   return LIBSCL_COPYRIGHT;
   }

const char* (scl_conf_version) (void)     { return LIBSCL_REVISION;    }
const char* (scl_conf_date) (void)        { return LIBSCL_TIMESTAMP;   }
const char* (scl_conf_cflags) (void)      { return CLIENT_CFLAGS;   }
const char* (scl_conf_shared_libs) (void) { return CLIENT_SHARLIBS; }
const char* (scl_conf_static_libs) (void) { return CLIENT_STATLIBS; }

const char* (scl_statstr) (int a_stat)
   {
   switch (a_stat)
      {
      default:  break;
      case SCL_OK:        return "all ok";
      case SCL_ERROR:     return "general error";
      case SCL_BADARG:    return "bad argument";
      case SCL_CORRUPT:   return "internal corruption";
      case SCL_NOMEM:     return "can't allocate memory";
      case SCL_NOTFOUND:  return "can't find item";
      case SCL_NOSVC:     return "service not available";
      case SCL_DUPKEY:    return "duplicate key";
      }
   return NULL;
   }

void* scl_alloc (size_t a_size) { return SCL_ALLOCATOR(a_size); }
void  scl_free  (void* a_item)  { SCL_DEALLOCATOR(a_item);      }


#ifdef	WIN32

/*****************************************************************************
 * Public Function DllMain
 *****************************************************************************/

BOOL APIENTRY DllMain (HANDLE hModule, DWORD ulReasonForCall, LPVOID lpReserved)
   {
   switch (ulReasonForCall)
      {
      default: break;
      case DLL_PROCESS_ATTACH: break;
      case DLL_PROCESS_DETACH: break;
      case DLL_THREAD_ATTACH:  break;
      case DLL_THREAD_DETACH:  break;
      }
   return TRUE;
   }

#endif


/* end of file */
