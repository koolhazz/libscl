/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	"SCL_tree.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

/*
 *                   <tree>
 *                      |
 *                      V
 *              [2] "first data"
 *             /                \
 *            V                  V
 *    [1] "second data"  [4] "third data"
 *                      /
 *                     V
 *             [3] "fourth data"
 *
 * prefix: 2,1,4,3
 * infix: 1,2,3,4
 * postfix: 1,3,4,2
 */

static const char* g_data1[4] =
   {
   /* key */  /* data */      /* index */
   /*  2  */  "first data",   /* 0 */
   /*  1  */  "second data",  /* 1 */
   /*  4  */  "third data",   /* 2 */
   /*  3  */  "fourth data"   /* 3 */
   };

static const char* g_data2[4] =
   {
   /* key */  /* data */   /* index */
   /*  2  */  "1st data",  /* 0 */
   /*  1  */  "2nd data",  /* 1 */
   /*  4  */  "3rd data",  /* 2 */
   /*  3  */  "4th data"   /* 3 */
   };


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static const char* g_map[5];
static int g_key[4];
static int g_idx;
static void* g_context = &g_key[0];


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data, void* a_context);


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
/*
   printf ("\n");
   printf ("k=\"%s\", ", a_key);
   printf ("o=%ld, ",    a_ord);
   printf ("d=\"%s\"\n", (char*)a_data);
   printf ("m=\"%s\"\n", g_map[a_ord]);
*/
   if (a_context != g_context) return SCL_NOTFOUND;
   if (strcmp((char*)a_data,g_map[a_ord])==0) g_key[g_idx++] = a_ord;
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "ttree1: Tree Basic and Update, Access Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   SCL_tree_t   tree;

   void*   data;
   int     stat;
   int     i;

   size_t   height;
   size_t   compares;
   size_t   rotates;

   /* g_map[key] = data[i] */
   g_map[0] = NULL;
   g_map[1] = g_data2[1];
   g_map[2] = g_data2[0];
   g_map[3] = g_data2[3];
   g_map[4] = g_data2[2];

   printf ("Create tree:");
   fflush (stdout);
   tree = tree_new();
   printf ("(%p = tree_new()) != NULL ........ ", tree);
   fflush (stdout);
   printf ("%s\n", ((tree!=NULL) ? "PASS" : "FAIL"));

   printf (
          "%ld = tree_count (tree) ............................... %s\n",
          tree_count(tree), ((tree_count(tree)==0) ? "PASS" : "FAIL")
          );
   tree_stat (tree, &height, &compares, &rotates);
   printf (
          "tree stat: height = %ld ............................... %s\n",
          height, ((height==0) ? "PASS" : "FAIL")
          );
   printf (
          "tree stat: compares = %ld ............................. %s\n",
          compares, ((compares==0) ? "PASS" : "FAIL")
          );
   printf (
          "tree stat: rotates = %ld .............................. %s\n",
          rotates, ((rotates==0) ? "PASS" : "FAIL")
          );

   printf ("Insert into tree.\n");
   stat = tree_insert (tree, 2, g_data1[0]);
   printf (
          "[%d,%s] = tree_insert (tree, 2, \"%s\") .... %s\n",
          stat, scl_statstr(stat), g_data1[0], ((stat==SCL_OK) ? "PASS":"FAIL")
          );
   stat = tree_insert (tree, 1, g_data1[1]);
   printf (
          "[%d,%s] = tree_insert (tree, 1, \"%s\") ... %s\n",
          stat, scl_statstr(stat), g_data1[1], ((stat==SCL_OK) ? "PASS":"FAIL")
          );
   stat = tree_insert (tree, 4, g_data1[2]);
   printf (
          "[%d,%s] = tree_insert (tree, 4, \"%s\") .... %s\n",
          stat, scl_statstr(stat), g_data1[2], ((stat==SCL_OK) ? "PASS":"FAIL")
          );
   stat = tree_insert (tree, 3, g_data1[3]);
   printf (
          "[%d,%s] = tree_insert (tree, 3, \"%s\") ... %s\n",
          stat, scl_statstr(stat), g_data1[3], ((stat==SCL_OK) ? "PASS":"FAIL")
          );

   printf (
          "%ld = tree_count (tree) ............................... %s\n",
          tree_count(tree), ((tree_count(tree)==4) ? "PASS" : "FAIL")
          );
   tree_stat (tree, &height, &compares, &rotates);
   printf (
          "tree stat: height = %ld, compares = %ld, rotates = %ld\n",
          height, compares, rotates
          );
   printf (
          "tree stat: height = %ld ............................... %s\n",
          height, ((height==2) ? "PASS" : "FAIL")
          );

   printf ("Replace in tree.\n");
   stat = tree_replace (tree, 2, g_data2[0]);
   printf (
          "[%d,%s] = tree_replace (tree, 2, \"%s\") ...... %s\n",
          stat, scl_statstr(stat), g_data2[0], ((stat==SCL_OK) ? "PASS":"FAIL")
          );
   stat = tree_replace (tree, 1, g_data2[1]);
   printf (
          "[%d,%s] = tree_replace (tree, 1, \"%s\") ...... %s\n",
          stat, scl_statstr(stat), g_data2[1], ((stat==SCL_OK) ? "PASS":"FAIL")
          );
   stat = tree_replace (tree, 4, g_data2[2]);
   printf (
          "[%d,%s] = tree_replace (tree, 4, \"%s\") ...... %s\n",
          stat, scl_statstr(stat), g_data2[2], ((stat==SCL_OK) ? "PASS":"FAIL")
          );
   stat = tree_replace (tree, 3, g_data2[3]);
   printf (
          "[%d,%s] = tree_replace (tree, 3, \"%s\") ...... %s\n",
          stat, scl_statstr(stat), g_data2[3], ((stat==SCL_OK) ? "PASS":"FAIL")
          );

   for (i=0 ; i<4 ; i++) g_key[i] = 0;
   g_idx = 0;
   printf ("Foreach PREFIX on tree .............................. ");
   fflush (stdout);
   tree_foreach (tree, SCL_PREFIX, cbfn, g_context);
   if ((g_key[0]==2) && (g_key[1]==1) && (g_key[2]==4) && (g_key[3]==3))
      printf ("PASS\n");
   else
      printf ("FAIL\n");

   for (i=0 ; i<4 ; i++) g_key[i] = 0;
   g_idx = 0;
   printf ("Foreach INFIX on tree ............................... ");
   fflush (stdout);
   tree_foreach (tree, SCL_INFIX, cbfn, g_context);
   if ((g_key[0]==1) && (g_key[1]==2) && (g_key[2]==3) && (g_key[3]==4))
      printf ("PASS\n");
   else
      printf ("FAIL\n");

   for (i=0 ; i<4 ; i++) g_key[i] = 0;
   g_idx = 0;
   printf ("Foreach POSTFIX on tree ............................. ");
   tree_foreach (tree, SCL_POSTFIX, cbfn, g_context);
   fflush (stdout);
   if ((g_key[0]==1) && (g_key[1]==3) && (g_key[2]==4) && (g_key[3]==2))
      printf ("PASS\n");
   else
      printf ("FAIL\n");

   printf ("Access in tree.\n");
   data = tree_access (tree, 2);
   printf (
          "\"%s\" = tree_access (tree, 2) .................. %s\n",
          data, ((strcmp(data,g_data2[0])==SCL_OK) ? "PASS":"FAIL")
          );
   data = tree_access (tree, 1);
   printf (
          "\"%s\" = tree_access (tree, 1) .................. %s\n",
          data, ((strcmp(data,g_data2[1])==SCL_OK) ? "PASS":"FAIL")
          );
   data = tree_access (tree, 4);
   printf (
          "\"%s\" = tree_access (tree, 4) .................. %s\n",
          data, ((strcmp(data,g_data2[2])==SCL_OK) ? "PASS":"FAIL")
          );
   data = tree_access (tree, 3);
   printf (
          "\"%s\" = tree_access (tree, 3) .................. %s\n",
          data, ((strcmp(data,g_data2[3])==SCL_OK) ? "PASS":"FAIL")
          );

   printf ("Erase tree.\n");
   tree_erase (tree, NULL, NULL);

   printf (
          "%ld = tree_count (tree) ............................... %s\n",
          tree_count(tree), ((tree_count(tree)==0) ? "PASS" : "FAIL")
          );
   tree_stat (tree, &height, &compares, &rotates);
   printf (
          "tree stat: height = %ld ............................... %s\n",
          height, ((height==0) ? "PASS" : "FAIL")
          );
   printf (
          "tree stat: compares = %ld ............................. %s\n",
          compares, ((compares==0) ? "PASS" : "FAIL")
          );
   printf (
          "tree stat: rotates = %ld .............................. %s\n",
          rotates, ((rotates==0) ? "PASS" : "FAIL")
          );

   printf ("Delete tree.\n");
   tree_del (tree);

   printf ("\n");

   return 0;
   }
