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

static unsigned long g_data2[VECTOR_SIZE] =
   {
   0x12345678,
   0x55555555,
   0x0000BEEF,
   0xF0F0F0F0,
   0x00000101,
   0xAAAAAAAA,
   0x99999999
   };


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tvector2: Vector Replace and Access Tests";
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

   printf ("Replace some data in vector.\n");
   for (i=0 ; i<VECTOR_SIZE ; i++)
      {
      if (g_data1[i] != g_data2[i])
         {
         stat = vector_replace (vector, i, (void*)g_data2[i]);
         printf (
                "[%d,%s] = vector_replace (vector, %d, %08X) ... %s\n",
                stat, scl_statstr(stat), i, g_data2[i],
                ((stat==SCL_OK) ? "PASS" : "FAIL")
                );
         }
      }

   printf ("Access vector.\n");
   for (i=0 ; i<VECTOR_SIZE ; i++)
      {
      data = vector_access (vector, i);
      printf (
             "%08X = vector_access (vector, %d) ................ %s\n",
             data, i, (((unsigned long)data==g_data2[i]) ? "PASS" : "FAIL")
             );
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
