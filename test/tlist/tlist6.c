/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	"SCL_list.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#define	LIST_SIZE	(5)


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int g_flag1[LIST_SIZE];
static int g_flag2[LIST_SIZE];
static int g_flag3[2*LIST_SIZE];

static unsigned long g_data1[LIST_SIZE] =
   {
   0x1234,
   0xFEED,
   0xBEEF,
   0xCACAD0D0,
   0x10101010
   };

static unsigned long g_data2[LIST_SIZE] =
   {
   0xABCD,
   0x01010101,
   0xAAAAAAAA,
   0x5555,
   0x89ABCDEF
   };

static unsigned long g_data3[2*LIST_SIZE] =
   {
   0x1234,
   0xABCD,
   0x01010101,
   0xAAAAAAAA,
   0x5555,
   0x89ABCDEF,
   0xFEED,
   0xBEEF,
   0xCACAD0D0,
   0x10101010
   };


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn1 (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   if (((unsigned long)a_data == g_data1[a_ord]) && (g_flag1[a_ord] == 0))
      {
      g_flag1[a_ord] = 1;
      printf ("Found data [index=%2d,data=%08X] ............... PASS\n", a_ord, a_data);
      }
   else if (g_flag1[a_ord] != 0)
      {
      printf ("Duplicate data [index=%2d,data=%08X] ........... FAIL\n", a_ord, a_data);
      }
   else
      {
      printf ("Data not found [index=%2d,data=%08X] ........... FAIL\n", a_ord, a_data);
      }
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn2 (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   if (((unsigned long)a_data == g_data2[a_ord]) && (g_flag2[a_ord] == 0))
      {
      g_flag2[a_ord] = 1;
      printf ("Found data [index=%2d,data=%08X] ............... PASS\n", a_ord, a_data);
      }
   else if (g_flag2[a_ord] != 0)
      {
      printf ("Duplicate data [index=%2d,data=%08X] ........... FAIL\n", a_ord, a_data);
      }
   else
      {
      printf ("Data not found [index=%2d,data=%08X] ........... FAIL\n", a_ord, a_data);
      }
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn3 (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   if (((unsigned long)a_data == g_data3[a_ord]) && (g_flag3[a_ord] == 0))
      {
      g_flag3[a_ord] = 1;
      printf ("Found data [index=%2d,data=%08X] ............... PASS\n", a_ord, a_data);
      }
   else if (g_flag3[a_ord] != 0)
      {
      printf ("Duplicate data [index=%2d,data=%08X] ........... FAIL\n", a_ord, a_data);
      }
   else
      {
      printf ("Data not found [index=%2d,data=%08X] ........... FAIL\n", a_ord, a_data);
      }
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tlist6: List Splice Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   SCL_list_t   list1;
   SCL_list_t   list2;

   int   stat;
   int   i;

   printf ("\n");
   printf ("List splice tests.\n");
   printf ("\n");

   printf ("Create two lists.\n");
   list1 = list_new();
   printf ("(%p = list_new()) != NULL .................. ", list1);
   fflush (stdout);
   printf ("%s\n", ((list1!=NULL) ? "PASS" : "FAIL"));
   list2 = list_new();
   printf ("(%p = list_new()) != NULL .................. ", list2);
   fflush (stdout);
   printf ("%s\n", ((list2!=NULL) ? "PASS" : "FAIL"));

   printf ("Push data in back list1.\n");
   for (i=0 ; i<LIST_SIZE ; i++)
      {
      stat = list_push_back (list1, (void*)g_data1[i]);
      printf (
             "([%d,%s] = list_push_back (list1, data1[%d]) .... %s\n",
             stat, scl_statstr(stat), i, ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf ("Push data in front list2.\n");
   for (i=0 ; i<LIST_SIZE ; i++)
      {
      stat = list_push_front (list2, (void*)g_data2[i]);
      printf (
             "([%d,%s] = list_push_front (list2, data2[%d]) ... %s\n",
             stat, scl_statstr(stat), i, ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf ("REVERSE list2\n");
   list_reverse (list2);

   printf ("foreach on list1.\n");
   for (i=0 ; i<LIST_SIZE ; i++) g_flag1[i] = 0;
   list_foreach (list1, cbfn1, NULL);

   printf ("foreach on list2.\n");
   for (i=0 ; i<LIST_SIZE ; i++) g_flag2[i] = 0;
   list_foreach (list2, cbfn2, NULL);

   printf ("list_splice list2 into second position (offset 1) in list1.\n");
   list_splice (list1, 1, list2);

   printf (
          "%2ld = list_count (list1) ........................... %s\n",
          list_count(list1), ((list_count(list1)==10) ? "PASS" : "FAIL")
          );

   printf (
          "%2ld = list_count (list2) ........................... %s\n",
          list_count(list2), ((list_count(list2)==0) ? "PASS" : "FAIL")
          );

   printf ("foreach on list1.\n");
   for (i=0 ; i<2*LIST_SIZE ; i++) g_flag3[i] = 0;
   list_foreach (list1, cbfn3, NULL);

   printf ("foreach on list2 (empty).\n");
   list_foreach (list2, cbfn2, NULL);

   printf ("list_splice list1 into first position (offset 0) in list2 several times.\n");
   list_splice (list2, 0, list1); printf ("list_splice (list2, 0, list1);\n");
   list_splice (list2, 0, list1); printf ("list_splice (list2, 0, list1);\n");
   list_splice (list2, 0, list1); printf ("list_splice (list2, 0, list1);\n");

   printf (
          "%2ld = list_count (list1) ........................... %s\n",
          list_count(list1), ((list_count(list1)==0) ? "PASS" : "FAIL")
          );

   printf (
          "%2ld = list_count (list2) ........................... %s\n",
          list_count(list2), ((list_count(list2)==10) ? "PASS" : "FAIL")
          );

   printf ("foreach on list2.\n");
   for (i=0 ; i<2*LIST_SIZE ; i++) g_flag3[i] = 0;
   list_foreach (list2, cbfn3, NULL);

   printf ("foreach on list1 (empty).\n");
   list_foreach (list1, cbfn1, NULL);

   printf ("Erase list1 and list2.\n");
   list_erase (list1);
   list_erase (list2);

   printf (
          "%2ld = list_count (list1) ........................... %s\n",
          list_count(list1), ((list_count(list1)==0) ? "PASS" : "FAIL")
          );

   printf (
          "%2ld = list_count (list2) ........................... %s\n",
          list_count(list2), ((list_count(list2)==0) ? "PASS" : "FAIL")
          );

   printf ("Delete list1 and list2.\n");
   list_del (list1);
   list_del (list2);

   printf ("\n");

   return 0;
   }
