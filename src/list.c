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

	$RCSfile: list.c,v $
	$Revision: 1.5 $
	$Date: 2010/04/14 03:08:38 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: List Container Implementation

	Many of the list functions depends upon:
	1. SCL_ALLOCATOR() setting allocated memory to binary 0,
	2. SCL_ALLOCATOR() returning NULL if memory allocation fails and
	3. NULL being equal to binary 0.

CHANGE LOG

	04apr10	drj	Added coallback context pointer to list_foreach().

	06jun06	drj	Miscellaneous format finessing.

	27nov04	drj	Added list_insert(), list_insert_before(),
			list_insert_after(), and list_remove_at().

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
#include	"SCL_list.h"


/* ************************************************************************* */
/*                                                                           */
/*      C o n s t a n t s                                                    */
/*                                                                           */
/* ************************************************************************* */

#define   PRED(x)   ((x)->pred)
#define   SUCC(x)   ((x)->succ)


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

typedef struct S_node_t     S_node_t;
typedef struct S_SCL_list_t S_SCL_list_t;

struct S_node_t
   {
   S_node_t*   succ;
   S_node_t*   pred;
   const void* data;
   };

struct S_SCL_list_t
   {
   S_node_t* head;
   S_node_t* tail;
   size_t    count;
   };


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
 * Public Function list_new
 *****************************************************************************/

SCL_list_t (list_new) (void)
   {
   return SCL_ALLOCATOR (sizeof(S_SCL_list_t));
   }


/*****************************************************************************
 * Public Function list_del
 *****************************************************************************/

void (list_del) (SCL_list_t a_list)
   {
   S_node_t* node1 = a_list->head;
   S_node_t* node2 = a_list->head;

   while (node1 != NULL)
      {
      node2 = node1->succ;
      SCL_DEALLOCATOR ((void*)node1);
      node1 = node2;
      }

   SCL_DEALLOCATOR (a_list);

   return;
   }


/*****************************************************************************
 * Public Function list_erase
 *****************************************************************************/

void (list_erase) (SCL_list_t a_list)
   {
   S_node_t* node1 = a_list->head;
   S_node_t* node2 = a_list->head;

   while (node1 != NULL)
      {
      node2 = node1->succ;
      SCL_DEALLOCATOR ((void*)node1);
      node1 = node2;
      }

   a_list->head = NULL;
   a_list->tail = NULL;
   a_list->count = 0;

   return;
   }


/*****************************************************************************
 * Public Function list_count
 *****************************************************************************/

size_t (list_count) (SCL_list_t a_list)
   {
   return a_list->count;
   }


/*****************************************************************************
 * Public Function list_insert
 *****************************************************************************/

int (list_insert) (SCL_list_t a_list, size_t a_index, const void* a_data)
   {
   S_SCL_list_t* const list = a_list;
   S_node_t* ilink = list->head;
   S_node_t* node;

   if (a_index == 0) return list_push_front (a_list, a_data);
   if (a_index == a_list->count) return list_push_back (a_list, a_data);
   if (a_index > a_list->count) return SCL_NOTFOUND;

   node = SCL_ALLOCATOR (sizeof(S_node_t));
   if (node == NULL) return SCL_NOMEM;

   node->data = a_data;

   while (--a_index > 0) ilink = SUCC(ilink);

   PRED(node) = ilink;
   SUCC(node) = SUCC(ilink);
   PRED(SUCC(ilink)) = node;
   SUCC(ilink) = node;

   list->count += 1;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function list_push_front
 *****************************************************************************/

int (list_push_front) (SCL_list_t a_list, const void* a_data)
   {
   S_SCL_list_t* const list = a_list;
   S_node_t* const node = SCL_ALLOCATOR (sizeof(S_node_t));

   if (node == NULL) return SCL_NOMEM;

   node->data = a_data;
   SUCC(node) = list->head;

   if (list->head != NULL)
      PRED(list->head) = node;
   else
      list->tail = node;
   list->head = node;
   list->count += 1;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function list_push_back
 *****************************************************************************/

int (list_push_back) (SCL_list_t a_list, const void* a_data)
   {
   S_SCL_list_t* const list = a_list;
   S_node_t* const node = SCL_ALLOCATOR (sizeof(S_node_t));

   if (node == NULL) return SCL_NOMEM;

   node->data = a_data;
   PRED(node) = list->tail;

   if (list->tail != NULL)
      SUCC(list->tail) = node;
   else
      list->head = node;
   list->tail = node;
   list->count += 1;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function list_pop_front
 *****************************************************************************/

void* (list_pop_front) (SCL_list_t a_list)
   {
   const void* data;
   S_SCL_list_t* const list = a_list;
   S_node_t* node;
   S_node_t* head;

   node = list->head;
   if (node == NULL) return NULL;

   data = (void*)node->data;

   head = SUCC(node);
   if (head != NULL) PRED(head) = NULL; else list->tail = NULL;
   list->head = head;
   list->count -= 1;

   SCL_DEALLOCATOR (node);

   return (void*)data;
   }


/*****************************************************************************
 * Public Function list_pop_back
 *****************************************************************************/

void* (list_pop_back) (SCL_list_t a_list)
   {
   const void* data;
   S_SCL_list_t* const list = a_list;
   S_node_t* node;
   S_node_t* tail;

   node = list->tail;
   if (node == NULL) return NULL;

   data = (void*)node->data;

   tail = PRED(node);
   if (tail != NULL) SUCC(tail) = NULL; else list->head = NULL;
   list->tail = tail;
   list->count -= 1;

   SCL_DEALLOCATOR (node);

   return (void*)data;
   }


/*****************************************************************************
 * Public Function list_remove
 *****************************************************************************/

void* (list_remove) (SCL_list_t a_list, size_t a_index)
   {
   S_SCL_list_t* const list = a_list;
   S_node_t* node = list->head;
   const void* data;

   if (list->count <= a_index) return NULL;
   while (a_index-- > 0) node = SUCC(node);

   if (SUCC(node) != NULL) PRED(SUCC(node)) = PRED(node);
   if (PRED(node) != NULL) SUCC(PRED(node)) = SUCC(node);

   if (list->head == node) list->head = SUCC(node);
   if (list->tail == node) list->tail = PRED(node);

   data = node->data;
   list->count -= 1;

   SCL_DEALLOCATOR (node);

   return (void*)data;
   }


/*****************************************************************************
 * Public Function list_front
 *****************************************************************************/

void* (list_front) (SCL_list_t a_list)
   {
   const S_node_t* const node = a_list->head;
   if (node == NULL) return NULL;
   return (void*)node->data;
   }


/*****************************************************************************
 * Public Function list_back
 *****************************************************************************/

void* (list_back) (SCL_list_t a_list)
   {
   const S_node_t* const node = a_list->tail;
   if (node == NULL) return NULL;
   return (void*)node->data;
   }


/*****************************************************************************
 * Public Function list_access
 *****************************************************************************/

void* (list_access) (SCL_list_t a_list, size_t a_index)
   {
   const S_SCL_list_t* const list = a_list;
   const S_node_t* node = list->head;

   if (list->count <= a_index) return NULL;
   while (a_index-- > 0) node = SUCC(node);

   return (void*)node->data;
   }


/*****************************************************************************
 * Public Function list_at
 *****************************************************************************/

SCL_iterator_t (list_at) (SCL_list_t a_list, size_t a_index)
   {
   const S_SCL_list_t* const list = a_list;
   const S_node_t* node = list->head;

   if (list->count <= a_index) return NULL;
   while (a_index-- > 0) node = SUCC(node);

   return (void*)node;
   }


/*****************************************************************************
 * Public Function list_begin
 *****************************************************************************/

SCL_iterator_t (list_begin) (SCL_list_t a_list)
   {
   return a_list->head;
   }


/*****************************************************************************
 * Public Function list_end
 *****************************************************************************/

SCL_iterator_t (list_end) (SCL_list_t a_list)
   {
   return a_list->tail;
   }


/*****************************************************************************
 * Public Function list_next
 *****************************************************************************/

SCL_iterator_t (list_next) (SCL_iterator_t a_iterator)
   {
   return SUCC((S_node_t*)a_iterator);
   }


/*****************************************************************************
 * Public Function list_prev
 *****************************************************************************/

SCL_iterator_t (list_prev) (SCL_iterator_t a_iterator)
   {
   return PRED((S_node_t*)a_iterator);
   }


/*****************************************************************************
 * Public Function list_data_set
 *****************************************************************************/

void (list_data_set) (SCL_iterator_t a_iterator, const void* a_data)
   {
   ((S_node_t*)a_iterator)->data = a_data;
   }


/*****************************************************************************
 * Public Function list_data_get
 *****************************************************************************/

void* (list_data_get) (SCL_iterator_t a_iterator)
   {
   return (void*)((S_node_t*)a_iterator)->data;
   }


/*****************************************************************************
 * Public Function list_insert_before
 *****************************************************************************/

int (list_insert_before) (
                         SCL_list_t     a_list,
                         SCL_iterator_t a_iterator,
                         const void*    a_data
                         )
   {
   S_SCL_list_t* const list = a_list;
   S_node_t* ilink = (S_node_t*)a_iterator;
   S_node_t* node;

   if (ilink == list->head) return list_push_front (a_list, a_data);

   node = SCL_ALLOCATOR (sizeof(S_node_t));
   if (node == NULL) return SCL_NOMEM;

   node->data = a_data;
   PRED(node) = PRED(ilink);
   SUCC(node) = ilink;

   SUCC(PRED(ilink)) = node;
   PRED(ilink) = node;

   list->count += 1;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function list_insert_after
 *****************************************************************************/

int (list_insert_after) (
                        SCL_list_t     a_list,
                        SCL_iterator_t a_iterator,
                        const void*    a_data
                        )
   {
   S_SCL_list_t* const list = a_list;
   S_node_t* ilink = (S_node_t*)a_iterator;
   S_node_t* node;

   if (ilink == list->tail) return list_push_back (a_list, a_data);

   node = SCL_ALLOCATOR (sizeof(S_node_t));
   if (node == NULL) return SCL_NOMEM;

   node->data = a_data;
   PRED(node) = ilink;
   SUCC(node) = SUCC(ilink);

   PRED(SUCC(ilink)) = node;
   SUCC(ilink) = node;

   list->count += 1;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function list_remove_at
 *****************************************************************************/

void* (list_remove_at) (SCL_list_t a_list, SCL_iterator_t a_iterator)
   {
   S_SCL_list_t* const list = a_list;
   S_node_t* node = (S_node_t*)a_iterator;
   const void* data;

   if (SUCC(node) != NULL) PRED(SUCC(node)) = PRED(node);
   if (PRED(node) != NULL) SUCC(PRED(node)) = SUCC(node);

   if (list->head == node) list->head = SUCC(node);
   if (list->tail == node) list->tail = PRED(node);

   data = node->data;
   list->count -= 1;

   SCL_DEALLOCATOR (node);

   return (void*)data;
   }


/*****************************************************************************
 * Public Function list_foreach
 *****************************************************************************/

void (list_foreach) (SCL_list_t a_list, SCL_cbfn_t a_func, void* a_context)
   {
   const S_node_t* node = a_list->head;
   int stat = SCL_NOTFOUND;
   long ord = 0;

   while ((node != NULL) && (stat == SCL_NOTFOUND))
      {
      stat = (*a_func) (NULL, ord++, (void*)node->data, a_context);
      node = SUCC(node);
      }

   return;
   }


/*****************************************************************************
 * Public Function list_join
 *****************************************************************************/

void (list_join) (SCL_list_t a_list1, SCL_list_t a_list2)
   {
   S_SCL_list_t* const list1 = a_list1;
   S_SCL_list_t* const list2 = a_list2;
   S_node_t* const node1 = list1->tail;
   S_node_t* const node2 = list2->head;

   if (node1 != NULL) SUCC(node1) = node2; else list1->head = node2;
   if (node2 != NULL) PRED(node2) = node1; else return;

   list1->tail  = list2->tail;
   list1->count += list2->count;

   list2->head = NULL;
   list2->tail = NULL;
   list2->count = 0;

   return;
   }


/*****************************************************************************
 * Public Function list_splice
 *****************************************************************************/

void (list_splice) (SCL_list_t a_list1, size_t a_index, SCL_list_t a_list2)
   {
   S_SCL_list_t* const list1 = a_list1;
   S_SCL_list_t* const list2 = a_list2;

   if (a_index == 0)
      {
      list_join (list2, list1);
      list1->head = list2->head;
      list1->tail = list2->tail;
      list1->count = list2->count;
      list2->head = NULL;
      list2->tail = NULL;
      list2->count = 0;
      return;
      }

   if (list1->count <= a_index)
      {
      list_join (list1, list2);
      return;
      }

   {
   S_node_t* node1;
   S_node_t* node2;
   S_node_t* next;

   node1 = list1->head;
   node2 = list2->head;

   if (node2 == NULL) return;

   while (--a_index > 0) node1 = SUCC(node1);
   next = SUCC(node1);

   SUCC(node1) = node2;
   PRED(node2) = node1;

   node1 = list2->tail;
   SUCC(node1) = next;
   if (next != NULL) PRED(next) = node1;

   list1->count += list2->count;

   list2->head = NULL;
   list2->tail = NULL;
   list2->count = 0;
   }

   return;
   }


/*****************************************************************************
 * Public Function list_reverse
 *****************************************************************************/

void (list_reverse) (SCL_list_t a_list)
   {
   S_SCL_list_t* const list = a_list;
   S_node_t* t;
   S_node_t* node;

   node = list->head;
   list->head = list->tail;
   list->tail = node;

   while (node != NULL)
      {
      t = SUCC(node);
      SUCC(node) = PRED(node);
      node = PRED(node) = t;
      }

   return;
   }


/* end of file */
