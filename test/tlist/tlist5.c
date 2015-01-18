/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	"SCL_list.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#define LIST1_SIZE       (5)
#define LIST2_SIZE       (7)
#define LIST3_SIZE       (7)


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int g_flag1[LIST1_SIZE];
static int g_flag2[LIST2_SIZE];
static int g_flag3[LIST3_SIZE];

static unsigned long g_data1[LIST1_SIZE] =
   {
   0xFEED,
   0x55555555,
   0xBEEF,
   0xCACAD0D0,
   0x12345678
   };

static unsigned long g_data2[LIST2_SIZE] =
   {
   0xFEED,
   0x55555555,
   0x0101,
   0xBEEF,
   0xAAAAAAAA,
   0xCACAD0D0,
   0x12345678
   };

static unsigned long g_data3[LIST3_SIZE] =
   {
   0x12345678,
   0xCACAD0D0,
   0xAAAAAAAA,
   0xBEEF,
   0x0101,
   0x55555555,
   0xFEED
   };


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn1 (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   if (((unsigned long)a_data == g_data1[a_ord]) && (g_flag1[a_ord] == 0))
      {
      g_flag1[a_ord] = 1;
      printf ("Found data [index=%2d,data=%08X] ............. PASS\n", a_ord, a_data);
      }
   else if (g_flag1[a_ord] != 0)
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

static int cbfn2 (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   if (((unsigned long)a_data == g_data2[a_ord]) && (g_flag2[a_ord] == 0))
      {
      g_flag2[a_ord] = 1;
      printf ("Found data [index=%2d,data=%08X] ............. PASS\n", a_ord, a_data);
      }
   else if (g_flag2[a_ord] != 0)
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

static int cbfn3 (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   if (((unsigned long)a_data == g_data3[a_ord]) && (g_flag3[a_ord] == 0))
      {
      g_flag3[a_ord] = 1;
      printf ("Found data [index=%2d,data=%08X] ............. PASS\n", a_ord, a_data);
      }
   else if (g_flag3[a_ord] != 0)
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

const char* test_title (void)
   {
   return "tlist5: List Insertion Tests";
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
   printf ("(%p = list_new()) != NULL ....... ", list);
   fflush (stdout);
   printf ("%s\n", ((list!=NULL) ? "PASS" : "FAIL"));

   printf ("Push data in back list.\n");
   for (i=0 ; i<LIST1_SIZE ; i++)
      {
      stat = list_push_back (list, (void*)g_data1[i]);
      printf (
             "([%d,%s] = list_push_back (list, data[%d]) .... %s\n",
             stat, scl_statstr(stat), i, ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf (
          "%2ld = list_count (list) .......................... %s\n",
          list_count(list), ((list_count(list)==LIST1_SIZE) ? "PASS" : "FAIL")
          );

   printf ("Foreach on list.\n");
   for (i=0 ; i<LIST1_SIZE ; i++) g_flag1[i] = 0;
   list_foreach (list, cbfn1, NULL);

   printf ("Insert data in list before 2 using iterator.\n");
   iterator = list_at (list, 2);
   printf ("%p = list_at (list, 2);\n", iterator);
   stat = list_insert_before (list, iterator, (void*)0x0101);
   printf (
          "[%d,%s] = list_insert_before (list, iterator=>%p, %08X);\n",
          stat, scl_statstr(stat), iterator, 0x0101
          );

   printf ("Insert data in list after 3 using iterator.\n");
   iterator = list_at (list, 3);
   printf ("%p = list_at (list, 3);\n", iterator);
   stat = list_insert_after (list, iterator, (void*)0xAAAAAAAA);
   printf (
          "[%d,%s] = list_insert_after (list, iterator=>%p, %08X);\n",
          stat, scl_statstr(stat), iterator, 0xAAAAAAAA
          );

   printf (
          "%2ld = list_count (list) .......................... %s\n",
          list_count(list), ((list_count(list)==LIST2_SIZE) ? "PASS" : "FAIL")
          );

   printf ("Foreach on list.\n");
   for (i=0 ; i<LIST2_SIZE ; i++) g_flag2[i] = 0;
   list_foreach (list, cbfn2, NULL);

   printf ("REVERSE the list.\n");
   list_reverse (list);

   printf (
          "%2ld = list_count (list) .......................... %s\n",
          list_count(list), ((list_count(list)==LIST3_SIZE) ? "PASS" : "FAIL")
          );

   printf ("Foreach on list.\n");
   for (i=0 ; i<LIST3_SIZE ; i++) g_flag3[i] = 0;
   list_foreach (list, cbfn3, NULL);

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
