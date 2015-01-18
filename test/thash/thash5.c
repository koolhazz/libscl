/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	<stdlib.h>
#include	"SCL_config.h"
#include	"SCL_hash.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static void* new_key (void)
   {
   int i;
   char* key = scl_alloc (771);
   for (i=0 ; i<771 ; i++)
      {
      key[i] = (char)(26.0f * (float)rand() / (float)RAND_MAX) + 'A';
      }
   return key;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static void* new_data (void)
   {
   int i;
   char* data = scl_alloc (771);
   for (i=0 ; i<771 ; i++)
      {
      data[i] = (char)(26.0f * (float)rand() / (float)RAND_MAX) + 'A';
      }
   return data;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "thash5: Hash Table Memory Usage Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   SCL_hash_t   hash;

   void*   key;
   void*   data;
   int     stat;
   long    i;

   printf ("Create hash: ", hash);
   fflush (stdout);
   hash = hash_new (NULL);
   printf ("(%p = hash_new (NULL)) != NULL ... ", hash);
   fflush (stdout);
   printf ("%s\n", ((hash!=NULL) ? "PASS" : "FAIL"));

   printf ("Insert 10000 random items into hash .................. ");
   fflush (stdout);
   stat = SCL_OK;
   for (i=0 ; i<10000 ; i++)
      {
      key  = new_key();
      data = new_data();
      stat = hash_insert (hash, key, data);
      if (stat != SCL_OK) i = 10000;
      }
   printf ("%s\n", ((stat==SCL_OK) ? "PASS" : "FAIL"));

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4096 .................... %s\n",
          hash_size(hash), ((hash_size(hash)==4096) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == 10000 ................. %s\n",
          hash_count(hash), ((hash_count(hash)==10000) ? "PASS" : "FAIL")
          );

   printf ("Erase hash.\n");
   hash_erase (hash);

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4096 .................... %s\n",
          hash_size(hash), ((hash_size(hash)==4096) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == 0 ......................... %s\n",
          hash_count(hash), ((hash_count(hash)==0) ? "PASS" : "FAIL")
          );

   printf ("Insert 10000 random items into hash .................. ");
   fflush (stdout);
   stat = SCL_OK;
   for (i=0 ; i<10000 ; i++)
      {
      key  = new_key();
      data = new_data();
      stat = hash_insert (hash, key, data);
      if (stat != SCL_OK) i = 10000;
      }
   printf ("%s\n", ((stat==SCL_OK) ? "PASS" : "FAIL"));

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4096 .................... %s\n",
          hash_size(hash), ((hash_size(hash)==4096) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == 10000 ................. %s\n",
          hash_count(hash), ((hash_count(hash)==10000) ? "PASS" : "FAIL")
          );

   printf ("Erase hash.\n");
   hash_erase (hash);

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4096 .................... %s\n",
          hash_size(hash), ((hash_size(hash)==4096) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == 0 ......................... %s\n",
          hash_count(hash), ((hash_count(hash)==0) ? "PASS" : "FAIL")
          );

   printf ("Insert 10000 random items into hash .................. ");
   fflush (stdout);
   stat = SCL_OK;
   for (i=0 ; i<10000 ; i++)
      {
      key  = new_key();
      data = new_data();
      stat = hash_insert (hash, key, data);
      if (stat != SCL_OK) i = 10000;
      }
   printf ("%s\n", ((stat==SCL_OK) ? "PASS" : "FAIL"));

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4096 .................... %s\n",
          hash_size(hash), ((hash_size(hash)==4096) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == 10000 ................. %s\n",
          hash_count(hash), ((hash_count(hash)==10000) ? "PASS" : "FAIL")
          );

   printf ("Erase hash.\n");
   hash_erase (hash);

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4096 .................... %s\n",
          hash_size(hash), ((hash_size(hash)==4096) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == 0 ......................... %s\n",
          hash_count(hash), ((hash_count(hash)==0) ? "PASS" : "FAIL")
          );

   printf ("Delete hash.\n");
   hash_del (hash);

   printf ("\n");

   return 0;
   }
