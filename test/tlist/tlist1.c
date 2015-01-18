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

static int g_flag[LIST_SIZE];

static unsigned long g_data[LIST_SIZE] =
   {
   0x55555555,
   0x10101010,
   0xCACAD0D0,
   0xAAAAAAAA,
   0x12345678
   };

static void* g_context = &g_flag[0];


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   if (a_context != g_context)
      {
      printf ("Invalid Context .............................. FAIL\n");
      return SCL_NOTFOUND;
      }
   if (((unsigned long)a_data == g_data[a_ord]) && (g_flag[a_ord] == 0))
      {
      g_flag[a_ord] = 1;
      printf ("Found data [index=%2d,data=%08X] ............. PASS\n", a_ord, a_data);
      }
   else if (g_flag[a_ord] != 0)
      {
      printf ("Duplicate data [index=%2d,data=%08X] ......... FAIL\n", a_ord, a_data);
      }
   else
      {
      printf ("Data not found [index=%2d,data=%08X] ......... FAIL\n", a_ord, a_data);
      }
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static void data_flag (void* a_data)
   {
   int i;
   for (i=0 ; i<LIST_SIZE ; i++)
      {
      if (((unsigned long)a_data==g_data[i]) && (g_flag[i] == 0)) break;
      }
   if (i == LIST_SIZE)
      {
      printf ("Data not found [data=%08X] .................. FAIL\n", a_data);
      return;
      }
   if (g_flag[i] == 1)
      {
      printf ("Duplicate data [index=%2d,data=%08X] ...... FAIL\n", i, a_data);
      return;
      }
   g_flag[i] = 1;
   printf ("Found data [index=%2d,data=%08X] ............. PASS\n", i, a_data);
   return;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tlist1: List Basic Tests";
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
   printf ("(%p = list_new()) != NULL ... ", list);
   fflush (stdout);
   printf ("%s\n", ((list!=NULL) ? "PASS" : "FAIL"));

   printf ("Push data in back list.\n");
   for (i=0 ; i<LIST_SIZE ; i++)
      {
      stat = list_push_back (list, (void*)g_data[i]);
      printf (
             "([%d,%s] = list_push_back (list, data[%d]) .... %s\n",
             stat, scl_statstr(stat), i, ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf (
          "%2ld = list_count (list) .......................... %s\n",
          list_count(list), ((list_count(list)==LIST_SIZE) ? "PASS" : "FAIL")
          );

   printf ("Foreach on list.\n");
   for (i=0 ; i<LIST_SIZE ; i++) g_flag[i] = 0;
   list_foreach (list, cbfn, g_context);

   printf ("REVERSE the list.\n");
   list_reverse (list);

   printf ("Iterate through the list.\n");
   iterator = list_begin (list);
   for (i=0 ; i<LIST_SIZE ; i++) g_flag[i] = 0;
   while (iterator != NULL)
      {
      data_flag (list_data_get(iterator));
      iterator = list_next (iterator);
      }

   printf ("Iterate back through the list.\n");
   iterator = list_end (list);
   for (i=0 ; i<LIST_SIZE ; i++) g_flag[i] = 0;
   while (iterator != NULL)
      {
      data_flag (list_data_get(iterator));
      iterator = list_prev (iterator);
      }

   printf ("REVERSE the list.\n");
   list_reverse (list);

   printf ("Accesses on list.\n");
   for (i=0 ; i<LIST_SIZE ; i++)
      {
      data = list_access (list, i);
      printf (
             "list_access(list,%d) == %08X ................. %s\n",
             i,
             (unsigned long)data,
             (((unsigned long)data==g_data[i]) ? "PASS" : "FAIL")
             );
      }

   printf ("Accesses on list via iterator.\n");
   for (i=0 ; i<LIST_SIZE ; i++)
      {
      iterator = list_at (list, i);
      printf (
             "list_at(list,%d) => %08X ..................... %s\n",
             i,
             (unsigned long)list_data_get(iterator),
             (((unsigned long)list_data_get(iterator)==g_data[i]) ? "PASS" : "FAIL")
             );
      }

   printf ("Erase list.\n");
   list_erase (list);

   printf (
          "%2ld = list_count (list) .......................... %s\n",
          list_count(list), ((list_count(list)==0) ? "PASS" : "FAIL")
          );

   printf ("Delete list.\n");
   list_del (list);

   printf ("\n");

   return 0;
   }
