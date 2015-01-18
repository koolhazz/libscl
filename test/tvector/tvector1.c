/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	"SCL_vector.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#define	VECTOR_SIZE	(5)


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int g_flag[VECTOR_SIZE];

static unsigned long g_data[VECTOR_SIZE] =
   {
   0x0000FEED,
   0x12345678,
   0x55555555,
   0x0000BEEF,
   0xCACAD0D0
   };

static void* g_context = &g_flag[0];


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data, void* a_context);


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   if (a_context != g_context)
      {
      printf ("Incorrect Context .................................. FAIL\n");
      return SCL_NOTFOUND;
      }
   if (((unsigned long)a_data == g_data[a_ord]) && (g_flag[a_ord] == 0))
      {
      g_flag[a_ord] = 1;
      printf ("Found data [index=%2d,data=%08X] ................... PASS\n", a_ord, a_data);
      }
   else if (g_flag[a_ord] != 0)
      {
      printf ("Duplicate data [index=%2d,data=%08X] ............... FAIL\n", a_ord, a_data);
      }
   else
      {
      printf ("Data not found [index=%2d,data=%08X] ............... FAIL\n", a_ord, a_data);
      }
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tvector1: Vector Basic, Push and Pop Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   SCL_vector_t   vector;

   void*   data;
   int     stat;
   int     i;

   printf ("Create vector: ");
   fflush (stdout);
   vector = vector_new();
   printf ("(%p = vector_new()) != NULL ..... ", vector);
   fflush (stdout);
   printf ("%s\n", ((vector!=NULL) ? "PASS" : "FAIL"));

   printf (
          "(%ld = vector_size (vector)) == 0 ....................... %s\n",
          vector_size(vector),
          ((vector_size(vector)==0) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = vector_count (vector)) == 0 ...................... %s\n",
          vector_count(vector),
          ((vector_count(vector)==0) ? "PASS" : "FAIL")
          );

   printf ("Push data in back vector.\n");
   for (i=0 ; i<VECTOR_SIZE ; i++)
      {
      stat = vector_push_back (vector, (void*)g_data[i]);
      printf (
             "[%d,%s] = vector_push_back (vector, %08X) ...... %s\n",
             stat, scl_statstr(stat), g_data[i],
             ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf (
          "(%ld = vector_size (vector)) == 16 ..................... %s\n",
          vector_size(vector),
          ((vector_size(vector)==16) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = vector_count (vector)) == 5 ...................... %s\n",
          vector_count(vector),
          ((vector_count(vector)==5) ? "PASS" : "FAIL")
          );

   printf ("Foreach on vector.\n");
   for (i=0 ; i<VECTOR_SIZE ; i++) g_flag[i] = 0;
   vector_foreach (vector, cbfn, g_context);

   printf ("REVERSE the vector.\n");
   vector_reverse (vector);

   printf ("Pop data in back vector.\n");
   for (i=0 ; i<VECTOR_SIZE ; i++)
      {
      data = vector_pop_back (vector);
      printf (
             "([%08X] = vector_pop_back (vector)) == %08X ... %s\n",
             data, g_data[i],
             (((unsigned long)data==g_data[i]) ? "PASS" : "FAIL")
             );
      }

   printf (
          "(%ld = vector_size (vector)) == 16 ..................... %s\n",
          vector_size(vector),
          ((vector_size(vector)==16) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = vector_count (vector)) == 0 ...................... %s\n",
          vector_count(vector),
          ((vector_count(vector)==0) ? "PASS" : "FAIL")
          );

   printf ("Foreach on vector (empty).\n");
   vector_foreach (vector, cbfn, g_context);

   printf ("Erase vector.\n");
   vector_erase (vector);

   printf (
          "(%ld = vector_size (vector)) == 0 ....................... %s\n",
          vector_size(vector),
          ((vector_size(vector)==0) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = vector_count (vector)) == 0 ...................... %s\n",
          vector_count(vector),
          ((vector_count(vector)==0) ? "PASS" : "FAIL")
          );

   printf ("Delete vector.\n");
   vector_del (vector);

   printf ("\n");

   return 0;
   }
