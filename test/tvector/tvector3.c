/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	"SCL_vector.h"
#include	"tmain.h"

/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#define	VECTOR_SIZE	(7)


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static SCL_vector_t g_vector;

static int g_flag[VECTOR_SIZE];

static unsigned long g_data1[VECTOR_SIZE] =
   {
   0x0000FEED,
   0x55555555,
   0x0000BEEF,
   0xCACAD0D0,
   0x00000101,
   0xAAAAAAAA,
   0x00001010
   };


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data, void* a_context);


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   if ((a_data == vector_at(g_vector,a_ord)) && (g_flag[a_ord] == 0))
      {
      g_flag[a_ord] = 1;
      printf ("Found data [index=%2d,data=%08X] ................. PASS\n", a_ord, a_data);
      }
   else if (g_flag[a_ord] != 0)
      {
      printf ("Duplicate data [index=%2d,data=%08X] ............. FAIL\n", a_ord, a_data);
      }
   else
      {
      printf ("Data not found [index=%2d,data=%08X] ............. FAIL\n", a_ord, a_data);
      }
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tvector3: Vector Data Set and Iterator Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   SCL_vector_t     vector;
   SCL_iterator_t   iterator;

   void*   data;
   int     stat;
   int     i;

   printf ("Create vector: ");
   fflush (stdout);
   vector = vector_new();
   printf ("(%p = vector_new()) != NULL ... ", vector);
   fflush (stdout);
   printf ("%s\n", ((vector!=NULL) ? "PASS" : "FAIL"));

   printf (
          "(%ld = vector_size (vector)) == 0 ..................... %s\n",
          vector_size(vector),
          ((vector_size(vector)==0) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = vector_count (vector)) == 0 .................... %s\n",
          vector_count(vector),
          ((vector_count(vector)==0) ? "PASS" : "FAIL")
          );

   printf ("Push data in back vector.\n");
   for (i=0 ; i<VECTOR_SIZE ; i++)
      {
      stat = vector_push_back (vector, (void*)g_data1[i]);
      printf (
             "[%d,%s] = vector_push_back (vector, %08X) .... %s\n",
             stat, scl_statstr(stat), g_data1[i],
             ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf ("Iterate back through vector, changing data.\n");
   for (i=7, iterator=vector_end(vector) ; iterator!=NULL ; iterator=vector_prev(iterator))
      {
      data = vector_data_get (iterator);
      printf (
             "%08X = vector_data_get (iterator=>%p) .... %s\n",
             data, iterator,
             (((unsigned long)data==g_data1[--i]) ? "PASS" : "FAIL")
             );
      vector_data_set (iterator, iterator);
      printf ("%08X -> %08X\n", data, vector_data_get(iterator));
      }

   printf (
          "(%ld = vector_size (vector)) == 16 ................... %s\n",
          vector_size(vector),
          ((vector_size(vector)==16) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = vector_count (vector)) == 7 .................... %s\n",
          vector_count(vector),
          ((vector_count(vector)==7) ? "PASS" : "FAIL")
          );

   printf ("Foreach on vector.\n");
   for (i=0 ; i<VECTOR_SIZE ; i++) g_flag[i] = 0;
   g_vector = vector;
   vector_foreach (vector, cbfn, NULL);

   printf ("Erase vector.\n");
   vector_erase (vector);

   printf (
          "(%ld = vector_size (vector)) == 0 ..................... %s\n",
          vector_size(vector),
          ((vector_size(vector)==0) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = vector_count (vector)) == 0 .................... %s\n",
          vector_count(vector),
          ((vector_count(vector)==0) ? "PASS" : "FAIL")
          );

   printf ("Delete vector.\n");
   vector_del (vector);

   printf ("\n");

   return 0;
   }
