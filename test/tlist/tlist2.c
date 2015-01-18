/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	"SCL_list.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#define	LIST1_SIZE	(7)
#define	LIST2_SIZE	(2)


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int g_flag1[LIST1_SIZE];
static int g_flag2[LIST2_SIZE];

static unsigned long g_data1[LIST1_SIZE] =
   {
   /* 0 */ 0xAAAAAAAA,
   /* 1 */ 0xFEED,
   /* 2 */ 0x55555555,
   /* 3 */ 0x0101,
   /* 4 */ 0xBEEF,
   /* 5 */ 0xCACAD0D0,
   /* 6 */ 0x1010
   };

static unsigned long g_data2[LIST2_SIZE] =
   {
   /* 0 */ 0x55555555,
   /* 1 */ 0xBEEF
   };


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn1 (const char* a_key, long a_ord, void* a_data, void* a_context);
static int cbfn2 (const char* a_key, long a_ord, void* a_data, void* a_context);


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn1 (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   if (((unsigned long)a_data == g_data1[a_ord]) && (g_flag1[a_ord] == 0))
      {
      g_flag1[a_ord] = 1;
      printf (
             "Found data [index=%2d,data=%08X] ....................... PASS\n",
             a_ord, a_data
             );
      }
   else if (g_flag1[a_ord] != 0)
      {
      printf (
             "Duplicate data [index=%2d,data=%08X] ................... FAIL\n",
             a_ord, a_data
             );
      }
   else
      {
      printf (
             "Data not found [index=%2d,data=%08X] ................... FAIL\n",
             a_ord, a_data
             );
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
      printf (
             "Found data [index=%2d,data=%08X] ....................... PASS\n",
             a_ord, a_data
             );
      }
   else if (g_flag2[a_ord] != 0)
      {
      printf (
             "Duplicate data [index=%2d,data=%08X] ................... FAIL\n",
             a_ord, a_data
             );
      }
   else
      {
      printf (
             "Data not found [index=%2d,data=%08X] ................... FAIL\n",
             a_ord, a_data
             );
      }
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tlist2: List Insert and Remove Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   SCL_list_t       list;
   SCL_iterator_t   iterator;

   void*   data;
   int     stat;
   int     i;

   printf ("Create list: ");
   fflush (stdout);
   list = list_new();
   printf ("(%p = list_new()) != NULL ............. ", list);
   fflush (stdout);
   printf ("%s\n", ((list!=NULL) ? "PASS" : "FAIL"));

   printf ("Push data into list.\n");
   for (i=0 ; i<LIST1_SIZE ; i++)
      {
      stat = list_push_back (list, (void*)g_data1[i]);
      printf (
             "([%d,%s] = list_push_back (list, data[%d]) .............. %s\n",
             stat, scl_statstr(stat), i, ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf (
          "%2ld = list_count (list) .................................... %s\n",
          list_count(list), ((list_count(list)==LIST1_SIZE) ? "PASS" : "FAIL")
          );

   printf ("Foreach on list.\n");
   for (i=0 ; i<LIST1_SIZE ; i++) g_flag1[i] = 0;
   list_foreach (list, cbfn1, NULL);

   printf ("Remove data in list at 3 (using iterator).\n");
   iterator = list_at (list, 3);
   printf ("%p = list_at (list, 3);\n", iterator);
   data = list_remove_at (list, iterator);
   printf ("[%08X] = list_remove_at (list, iterator=>%p) ... ", data, iterator);
   fflush (stdout);
   printf ("%s\n", (data == (void*)g_data1[3]) ? "PASS" : "FAIL");

   printf ("Remove data in list at 0 (using iterator).\n");
   iterator = list_at (list, 0);
   printf ("%p = list_at (list, 0);\n", iterator);
   data = list_remove_at (list, iterator);
   printf (
          "[%08X] = list_remove_at (list, iterator=>%p) ... ", data, iterator);
   fflush (stdout);
   printf ("%s\n", (data == (void*)g_data1[0]) ? "PASS" : "FAIL");

   printf ("Remove data in list at 4 (using iterator).\n");
   iterator = list_at (list, 4);
   printf ("%p = list_at (list, 4);\n", iterator);
   data = list_remove_at (list, iterator);
   printf ("[%08X] = list_remove_at (list, iterator=>%p) ... ", data, iterator);
   fflush (stdout);
   printf ("%s\n", (data == (void*)g_data1[6]) ? "PASS" : "FAIL");

   printf ("Remove data in list via list_pop_front() .................. ");
   fflush (stdout);
   data = list_pop_front (list);
   printf ("%s\n", (data == (void*)g_data1[1]) ? "PASS" : "FAIL");

   printf ("Remove data in list via list_pop_back() ................... ");
   fflush (stdout);
   data = list_pop_back (list);
   printf ("%s\n", (data == (void*)g_data1[5]) ? "PASS" : "FAIL");

   printf (
          "%2ld = list_count (list) .................................... %s\n",
          list_count(list), ((list_count(list)==LIST2_SIZE) ? "PASS" : "FAIL")
          );

   printf ("Foreach on list.\n");
   for (i=0 ; i<LIST2_SIZE ; i++) g_flag2[i] = 0;
   list_foreach (list, cbfn2, NULL);

   printf ("Remove data in list via list_pop_front() .................. ");
   fflush (stdout);
   data = list_pop_front (list);
   printf ("%s\n", (data == (void*)g_data2[0]) ? "PASS" : "FAIL");

   printf ("Remove data in list via list_pop_back() ................... ");
   fflush (stdout);
   data = list_pop_back (list);
   printf ("%s\n", (data == (void*)g_data2[1]) ? "PASS" : "FAIL");

   printf (
          "%2ld = list_count (list) .................................... %s\n",
          list_count(list), ((list_count(list)==0) ? "PASS" : "FAIL")
          );

   printf ("Foreach on list (empty).\n");
   list_foreach (list, cbfn1, NULL);

   printf ("Erase list.\n");
   list_erase (list);

   printf (
          "%2ld = list_count (list) .................................... %s\n",
          list_count(list), ((list_count(list)==0) ? "PASS" : "FAIL")
          );

   printf ("Delete list.\n");
   list_del (list);

   printf ("\n");

   return 0;
   }


/* end of file */
