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

	$RCSfile: tree.c,v $
	$Revision: 1.5 $
	$Date: 2010/04/14 03:07:09 $

PROGRAM INFORMATION

	Developed by:	SCL project
	Developer:	Douglas Jerome, drj, <douglas@backstep.org>

FILE DESCRIPTION

	Small Container Library: Tree Container Implementation

	Many of the tree functions depends upon:
	1. SCL_ALLOCATOR() setting allocated memory to binary 0,
	2. SCL_ALLOCATOR() returning NULL if memory allocation fails and
	3. NULL being equal to binary 0.

	The balanced tree insertion algorithm is directly taken from Donald E.
	Knuth, "Sorting and Searching," The Art of Computer Programming, vol. 3
	(Reading Mass.: Addison-Wesley 1973).

CHANGE LOG

	04apr10	drj	Added callback context pointer.

	06jun06	drj	Miscellaneous format finessing.

	05jul05	drj	Changed tree_update() to tree_replace().

	14nov04	drj	File generation.

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
#include	"SCL_tree.h"


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

typedef struct S_node_t     S_node_t;
typedef struct S_SCL_tree_t S_SCL_tree_t;

struct S_node_t
   {
   S_node_t*   left;
   S_node_t*   right;
   int         balance;
   long        key;
   const void* data;
   };

struct S_SCL_tree_t
   {
   S_node_t* root;
   size_t    count;
   size_t    height;
   size_t    compares;
   size_t    rotates;
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

static void recursive_delete (
                             S_node_t*  a_node,
                             SCL_cbfn_t a_func,
                             void*      a_context
                             );
static S_node_t* recursive_find (S_node_t* a_node, long a_key);
static int recursive_prefix (
                            S_node_t*  a_node,
                            SCL_cbfn_t a_func,
                            void*      a_context
                            );
static int recursive_infix (
                           S_node_t*  a_node,
                           SCL_cbfn_t a_func,
                           void*      a_context
                           );
static int recursive_postfix (
                             S_node_t*  a_node,
                             SCL_cbfn_t a_func,
                             void*      a_context
                             );


/*****************************************************************************
 * Private Function recursive_delete
 *****************************************************************************/

static void recursive_delete (
                             S_node_t*  a_node,
                             SCL_cbfn_t a_func,
                             void*      a_context
                             )
   {
   if (a_func != NULL) (void)(*a_func) (
                                       NULL,
                                       a_node->key,
                                       (void*)a_node->data,
                                       a_context
                                       );
   if (a_node->left  != NULL) recursive_delete (
                                               a_node->left,
                                               a_func,
                                               a_context
                                               );
   if (a_node->right != NULL) recursive_delete (
                                               a_node->right,
                                               a_func,
                                               a_context
                                               );
   SCL_DEALLOCATOR (a_node);
   }

/*****************************************************************************
 * Private Function recursive_find
 *****************************************************************************/

static S_node_t* recursive_find (S_node_t* a_node, long a_key)
   {
   S_node_t* node = NULL;

   if (a_node->left != NULL) node = recursive_find (a_node->left, a_key);
   if (node != NULL) return node;

   if (a_node->key == a_key) return a_node;

   if (a_node->right != NULL) node = recursive_find (a_node->right, a_key);
   if (node != NULL) return node;

   return NULL;
   }


/*****************************************************************************
 * Private Function recursive_prefix
 *****************************************************************************/

static int recursive_prefix (
                            S_node_t*  a_node,
                            SCL_cbfn_t a_func,
                            void*      a_context
                            )
   {
   int stat = SCL_NOTFOUND;

   if (a_func != NULL) stat = (*a_func) (
                                        NULL,
                                        a_node->key,
                                        (void*)a_node->data,
                                        a_context
                                        );
   if (stat != SCL_NOTFOUND) return stat;

   if (a_node->left != NULL) stat = recursive_prefix (
                                                     a_node->left,
                                                     a_func,
                                                     a_context
                                                     );
   if (stat != SCL_NOTFOUND) return stat;

   if (a_node->right != NULL) stat = recursive_prefix (
                                                     a_node->right,
                                                     a_func,
                                                     a_context
                                                     );
   if (stat != SCL_NOTFOUND) return stat;

   return SCL_NOTFOUND;
   }


/*****************************************************************************
 * Private Function recursive_infix
 *****************************************************************************/

static int recursive_infix (
                           S_node_t*  a_node,
                           SCL_cbfn_t a_func,
                           void*      a_context
                           )
   {
   int stat = SCL_NOTFOUND;

   if (a_node->left != NULL) stat = recursive_infix (
                                                    a_node->left,
                                                    a_func,
                                                    a_context
                                                    );
   if (stat != SCL_NOTFOUND) return stat;

   if (a_func != NULL) stat = (*a_func) (
                                        NULL,
                                        a_node->key,
                                        (void*)a_node->data,
                                        a_context
                                        );
   if (stat != SCL_NOTFOUND) return stat;

   if (a_node->right != NULL) stat = recursive_infix (
                                                     a_node->right,
                                                     a_func,
                                                     a_context
                                                     );
   if (stat != SCL_NOTFOUND) return stat;

   return SCL_NOTFOUND;
   }


/*****************************************************************************
 * Private Function recursive_postfix
 *****************************************************************************/

static int recursive_postfix (
                             S_node_t*  a_node,
                             SCL_cbfn_t a_func,
                             void*      a_context
                             )
   {
   int stat = SCL_NOTFOUND;

   if (a_node->left != NULL) stat = recursive_postfix (
                                                      a_node->left,
                                                      a_func,
                                                      a_context
                                                      );
   if (stat != SCL_NOTFOUND) return stat;

   if (a_node->right != NULL) stat = recursive_postfix (
                                                       a_node->right,
                                                       a_func,
                                                       a_context
                                                       );
   if (stat != SCL_NOTFOUND) return stat;

   if (a_func != NULL) stat = (*a_func) (
                                        NULL,
                                        a_node->key,
                                        (void*)a_node->data,
                                        a_context
                                        );
   if (stat != SCL_NOTFOUND) return stat;

   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/*****************************************************************************
 * Public Function tree_new
 *****************************************************************************/

SCL_tree_t (tree_new) (void)
   {
   return SCL_ALLOCATOR (sizeof(S_SCL_tree_t));
   }


/*****************************************************************************
 * Public Function tree_del
 *****************************************************************************/

void (tree_del) (SCL_tree_t a_tree)
   {
   if (a_tree->root != NULL) tree_erase (a_tree, NULL, NULL);
   SCL_DEALLOCATOR (a_tree);
   }


/*****************************************************************************
 * Public Function tree_erase
 *****************************************************************************/

void (tree_erase) (SCL_tree_t a_tree, SCL_cbfn_t a_func, void* a_context)
   {
   recursive_delete (a_tree->root, a_func, a_context);
   a_tree->root = NULL;
   a_tree->count = 0;
   a_tree->height = 0;
   a_tree->compares = 0;
   a_tree->rotates = 0;
   }


/*****************************************************************************
 * Public Function tree_count
 *****************************************************************************/

size_t (tree_count) (SCL_tree_t a_tree)
   {
   return a_tree->count;
   }


/*****************************************************************************
 * Public Function tree_stat
 *****************************************************************************/

void (tree_stat) (
                 SCL_tree_t a_tree,
                 size_t* const a_height,
                 size_t* const a_compares,
                 size_t* const a_rotates
                 )
   {
   if (a_height != NULL)   *a_height   = a_tree->height;
   if (a_compares != NULL) *a_compares = a_tree->compares;
   if (a_rotates != NULL)  *a_rotates  = a_tree->rotates;
   }


/*****************************************************************************
 * Public Function tree_insert
 *****************************************************************************/

int (tree_insert) (SCL_tree_t a_tree, long a_key, const void* a_data)
   {
   S_node_t* node;

   node = SCL_ALLOCATOR (sizeof(S_node_t));
   if (node == NULL) return SCL_NOMEM;

   node->key = a_key;
   node->data = a_data;

   if (a_tree->root == NULL)
      {
      a_tree->root = node;
      a_tree->count = 1;
      return SCL_OK;
      }

   {

   /*
    * The balanced tree insertion algorithm is directly taken from Donald E.
    * Knuth, "Sorting and Searching," The Art of Computer Programming, vol. 3
    * (Reading Mass.: Addison-Wesley 1973).
    *
    * I've kept the same cool variable names that Knuth used in his book: P,
    * Q, R, S, T, and a.  I added metrics to count comparisions and subtree
    * rotations.
    */

   long diff;
   int a = 0;
   S_node_t* P = NULL;
   S_node_t* Q = NULL;
   S_node_t* R = NULL;
   S_node_t* S = NULL;
   S_node_t* T = NULL;

   S = P = a_tree->root;

   /*
    * P will move down the tree; S will point to the place where rebalancing
    * may be necessary, and T always points to the parent of S.
    */

COMPARE:
   a_tree->compares += 1;
   diff = a_key - P->key;
   if (diff == 0) return SCL_DUPKEY;
   if (diff < 0)
      {
      Q = P->left;
      if (Q == NULL)
         {
         P->left = node;
         Q = node;
         goto ADJUST;
         }
      }
   if (diff > 0)
      {
      Q = P->right;
      if (Q == NULL)
         {
         P->right = node;
         Q = node;
         goto ADJUST;
         }
      }
   if (Q->balance != 0)
      {
      T = P;
      S = Q;
      }
   P = Q;
   goto COMPARE;

ADJUST:
   /*
    * Now the balance factors on nodes between S and Q need to be changed
    * from zero to +/- 1.
    */
   a_tree->compares += 1;
   diff = a_key - S->key;
   if (diff < 0)
      R = P = S->left;
   else
      R = P = S->right;
   if (P == Q) goto BALANCE;
   while (P != Q)
      {
      a_tree->compares += 1;
      diff = a_key - P->key;
      if (diff < 0)
         {
         P->balance = -1;
         P = P->left;
         }
      a_tree->compares += 1;
      diff = a_key - P->key;
      if (diff > 0)
         {
         P->balance = +1;
         P = P->right;
         }
      }

BALANCE:
   a_tree->compares += 1;
   diff = a_key - S->key;
   if (diff < 0)
      a = -1;
   else
      a = +1;
   if (S->balance == 0) /* tree has grown higher */
      {
      a_tree->height += 1;
      S->balance = a;
      goto DONE;
      }
   if (S->balance == -a) /* tree has gotten more balanced */
      {
      S->balance = 0;
      goto DONE;
      }
   if (S->balance == +a) /* tree has gotten out of balance */
      {
      if (R->balance == -a) goto DOUBLE_ROTATE;
      if (R->balance == +a) goto SINGLE_ROTATE;
      }

SINGLE_ROTATE:
   a_tree->rotates += 1;
   P = R;
   if (a == +1)
      {
      S->right = R->left;
      R->left  = S;
      }
   if (a == -1)
      {
      S->left  = R->right;
      R->right = S;
      }
   S->balance = R->balance = 0;
   goto FINISH_ROTATE;

DOUBLE_ROTATE:
   a_tree->rotates += 2;
   if (a == +1)
      {
      P = R->left;
      R->left = P->right;
      P->right = R;
      S->right = P->left;
      P->left = S;
      }
   if (a == -1)
      {
      P = R->right;
      R->right = P->left;
      P->left = R;
      S->left = P->right;
      P->right = S;
      }
   if (P->balance == +a)
      {
      S->balance = -a;
      R->balance = 0;
      }
   if (P->balance ==  0)
      {
      S->balance = 0;
      R->balance = 0;
      }
   if (P->balance == -a)
      {
      S->balance = 0;
      R->balance = a;
      }
   P->balance = 0;
   goto FINISH_ROTATE;

FINISH_ROTATE:
   if (T == NULL)
      a_tree->root = P;
   else
      {
      if (S == T->right)
         T->right = P;
      else
         T->left = P;
      }

   }

DONE:
   a_tree->count += 1;

   return SCL_OK;
   }


/*****************************************************************************
 * Public Function tree_replace
 *****************************************************************************/

int (tree_replace) (SCL_tree_t a_tree, long a_key, const void* a_data)
   {
   S_node_t* node = recursive_find (a_tree->root, a_key);
   if (node == NULL) return SCL_NOTFOUND;
   node->data = a_data;
   return SCL_OK;
   }


/*****************************************************************************
 * Public Function tree_access
 *****************************************************************************/

void* (tree_access) (SCL_tree_t a_tree, long a_key)
   {
   S_node_t* node = recursive_find (a_tree->root, a_key);
   if (node == NULL) return NULL;
   return (void*)node->data;
   }


/*****************************************************************************
 * Public Function tree_at
 *****************************************************************************/

SCL_iterator_t (tree_at) (SCL_tree_t a_tree, long a_key)
   {
   return recursive_find (a_tree->root, a_key);
   }


/*****************************************************************************
 * Public Function tree_data_set
 *****************************************************************************/

void (tree_data_set) (SCL_iterator_t a_iterator, const void* a_data)
   {
   ((S_node_t*)a_iterator)->data = a_data;
   }


/*****************************************************************************
 * Public Function tree_data_get
 *****************************************************************************/

void* (tree_data_get) (SCL_iterator_t a_iterator)
   {
   return (void*)((S_node_t*)a_iterator)->data;
   }


/*****************************************************************************
 * Public Function tree_foreach
 *****************************************************************************/

void (tree_foreach) (
                    SCL_tree_t a_tree,
                    int        a_order,
                    SCL_cbfn_t a_func,
                    void*      a_context
                    )
   {
   switch (a_order)
      {
      default: return; break;
      case SCL_PREFIX:
                      (void)recursive_prefix  (a_tree->root, a_func, a_context);
                      break;
      case SCL_INFIX:
                      (void)recursive_infix   (a_tree->root, a_func, a_context);
                       break;
      case SCL_POSTFIX:
                      (void)recursive_postfix (a_tree->root, a_func, a_context);
                       break;
      }
   }


/* end of file */
