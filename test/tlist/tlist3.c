/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	"SCL_list.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#define	LIST_SIZE	(7)


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int g_flag[LIST_SIZE];

static unsigned long g_data[LIST_SIZE] =
   {
   /* 0 */ 0x1010,
   /* 1 */ 0xAAAAAAAA,
   /* 2 */ 0x0101,
   /* 3 */ 0xFEED,
   /* 4 */ 0x55555555,
   /* 5 */ 0xBEEF,
   /* 6 */ 0xCACAD0D0
   };


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   if (((unsigned long)a_data == g_data[a_ord]) && (g_flag[a_ord] == 0))
      {
      g_flag[a_ord] = 1;
      printf (
             "Found data [index=%2d,data=%08X] .............. PASS\n",
             a_ord, a_data
             );
      }
   else if (g_flag[a_ord] != 0)
      {
      printf (
             "Duplicate data [index=%2d,data=%08X] .......... FAIL\n",
             a_ord, a_data
             );
      }
   else
      {
      printf (
             "Data not found [index=%2d,data=%08X] .......... FAIL\n",
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
   return "tlist3: List Unordered Push Back, Push Front and Access Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   SCL_list_t   list;
   void*        data;
   int          stat;
   int          i;

   printf ("\n");
   printf ("List unordered push back, push front and access.\n");
   printf ("\n");

   printf ("Create list: ");
   fflush (stdout);
   list = list_new();
   printf ("(%p = list_new()) != NULL .... ", list);
   fflush (stdout);
   printf ("%s\n", ((list!=NULL) ? "PASS" : "FAIL"));

   stat = list_push_back (list, (void*)g_data[3]);
   printf (
          "([%d,%s] = list_push_back (list, data[3]) ..... %s\n",
          stat, scl_statstr(stat), ((stat==SCL_OK) ? "PASS" : "FAIL")
          );

   stat = list_push_back (list, (void*)g_data[4]);
   printf (
          "([%d,%s] = list_push_back (list, data[4]) ..... %s\n",
          stat, scl_statstr(stat), ((stat==SCL_OK) ? "PASS" : "FAIL")
          );

   stat = list_push_front (list, (void*)g_data[2]);
   printf (
          "([%d,%s] = list_push_front (list, data[2]) .... %s\n",
          stat, scl_statstr(stat), ((stat==SCL_OK) ? "PASS" : "FAIL")
          );

   stat = list_push_back (list, (void*)g_data[5]);
   printf (
          "([%d,%s] = list_push_back (list, data[5]) ..... %s\n",
          stat, scl_statstr(stat), ((stat==SCL_OK) ? "PASS" : "FAIL")
          );

   stat = list_push_front (list, (void*)g_data[1]);
   printf (
          "([%d,%s] = list_push_front (list, data[1]) .... %s\n",
          stat, scl_statstr(stat), ((stat==SCL_OK) ? "PASS" : "FAIL")
          );

   stat = list_push_back (list, (void*)g_data[6]);
   printf (
          "([%d,%s] = list_push_back (list, data[6]) ..... %s\n",
          stat, scl_statstr(stat), ((stat==SCL_OK) ? "PASS" : "FAIL")
          );

   stat = list_push_front (list, (void*)g_data[0]);
   printf (
          "([%d,%s] = list_push_front (list, data[0]) .... %s\n",
          stat, scl_statstr(stat), ((stat==SCL_OK) ? "PASS" : "FAIL")
          );

   printf (
          "%2ld = list_count (list) ........................... %s\n",
          list_count(list), ((list_count(list)==LIST_SIZE) ? "PASS" : "FAIL")
          );

   printf ("Foreach on list.\n");
   for (i=0 ; i<LIST_SIZE ; i++) g_flag[i] = 0;
   list_foreach (list, cbfn, NULL);

   printf ("Data in list.\n");
   data = list_front (list);
   printf (
          "(%08X = list_front (list)) == %08X ....... %s\n",
          data, g_data[0], ((data==(void*)g_data[0]) ? "PASS" : "FAIL")
          );
   i = LIST_SIZE-1;
   data = list_back (list);
   printf (
          "(%08X = list_back (list)) == %08X ........ %s\n",
          data, g_data[i], ((data==(void*)g_data[i]) ? "PASS" : "FAIL")
          );
   i = 5;
   data = list_access (list, i);
   printf (
          "(%08X = list_access (list, %d)) == %08X ... %s\n",
          data, i, g_data[i], ((data==(void*)g_data[i]) ? "PASS" : "FAIL")
          );
   i = 0;
   data = list_access (list, i);
   printf (
          "(%08X = list_access (list, %d)) == %08X ... %s\n",
          data, i, g_data[i], ((data==(void*)g_data[i]) ? "PASS" : "FAIL")
          );
   i = 2;
   data = list_access (list, i);
   printf (
          "(%08X = list_access (list, %d)) == %08X ... %s\n",
          data, i, g_data[i], ((data==(void*)g_data[i]) ? "PASS" : "FAIL")
          );
   i = LIST_SIZE-1;
   data = list_access (list, i);
   printf (
          "(%08X = list_access (list, %d)) == %08X ... %s\n",
          data, i, g_data[i], ((data==(void*)g_data[i]) ? "PASS" : "FAIL")
          );

   printf ("Erase list.\n");
   list_erase (list);

   printf (
          "%2ld = list_count (list) ........................... %s\n",
          list_count(list), ((list_count(list)==0) ? "PASS" : "FAIL")
          );

   printf ("Delete list.\n");
   list_del (list);

   printf ("\n");

   return 0;
   }
