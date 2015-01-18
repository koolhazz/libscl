/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	"SCL_hash.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#define	TABLE_SIZE	(5)


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int g_flag[TABLE_SIZE];

static const char* g_key[TABLE_SIZE] =
   {
   "key one",
   "this is the longer key two",
   "key three",
   "!%^&#$\"(%&)<:",
   "key five"
   };

static const char* g_data[TABLE_SIZE] =
   {
   "The quick brown fox jumped over the lazy dog.",
   "The lazy dog slept fast.",
   "The slow red fox fell down.",
   "What did you expect?",
   "What did you expect?"
   };


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data, void* a_context);
static void data_flag (void* a_data);


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   int i;
   for (i=0 ; i<TABLE_SIZE ; i++)
      {
      if ((strcmp(a_key,g_key[i]) == 0) && (strcmp(a_data,g_data[i]) == 0))
         {
         break;
         }
      }
   if (i == TABLE_SIZE)
      {
      printf ("Key-data pair not found in data ...................... FAIL\n");
      printf (" Key: \"%s\"\n", a_key);
      printf ("Data: \"%s\"\n", a_data);
      return SCL_NOTFOUND;
      }
   if (g_flag[i] == 1)
      {
      printf ("Duplicate key-data pair .............................. FAIL\n");
      printf (" Key: \"%s\"\n", a_key);
      printf ("Data: \"%s\"\n", a_data);
      return SCL_NOTFOUND;
      }
   g_flag[i] = 1;
   printf ("Found key-data pair .................................. PASS\n");
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static void data_flag (void* a_data)
   {
   int i;
   for (i=0 ; i<TABLE_SIZE ; i++)
      {
      if ((strcmp(a_data,g_data[i]) == 0) && (g_flag[i] == 0)) break;
      }
   if (i == TABLE_SIZE)
      {
      printf ("Data not found in data set ........................... FAIL\n");
      printf ("Data: \"%s\"\n", a_data);
      return;
      }
   if (g_flag[i] == 1)
      {
      printf ("Duplicate data ....................................... FAIL\n");
      printf ("Data: \"%s\"\n", a_data);
      return;
      }
   g_flag[i] = 1;
   printf ("Found data ........................................... PASS\n");
   return;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "thash2: Hash Table Insert and Remove Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   SCL_hash_t       hash;
   SCL_iterator_t   iterator;

   void*   data;
   int     stat;
   int     i;

   printf ("Create hash: ", hash);
   fflush (stdout);
   hash = hash_new (NULL);
   printf ("(%p = hash_new (NULL)) != NULL ... ", hash);
   fflush (stdout);
   printf ("%s\n", ((hash!=NULL) ? "PASS" : "FAIL"));

   printf ("Insert into hash.\n");
   for (i=0 ; i<TABLE_SIZE ; i++)
      {
      stat = hash_insert (hash, g_key[i], g_data[i]);
      printf (
             "[%d,\"%s\"] = hash_insert (hash, key[%d], data[%d]) ... %s\n",
             stat, scl_statstr(stat), i, i, ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf ("\"Foreach\" on hash; each key-data pair in data only once?\n");
   for (i=0 ; i<TABLE_SIZE ; i++) g_flag[i] = 0;
   hash_foreach (hash, cbfn, NULL);

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4 .......................... %s\n",
          hash_size(hash), ((hash_size(hash)==4) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == 5 ......................... %s\n",
          hash_count(hash), ((hash_count(hash)==5) ? "PASS" : "FAIL")
          );

   printf ("Remove from hash.\n");
   for (i=TABLE_SIZE-1 ; i>=0 ; i--)
      {
      data = hash_remove (hash, g_key[i]);
      printf (
             "%p = hash_remove (hash, key[%d]) ............... %s\n",
             data,
             i,
             ((strcmp(data,g_data[i])==0) ? "PASS" : "FAIL")
             );
      }

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4 .......................... %s\n",
          hash_size(hash), ((hash_size(hash)==4) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == 0 ......................... %s\n",
          hash_count(hash), ((hash_count(hash)==0) ? "PASS" : "FAIL")
          );

   printf ("Insert into hash.\n");
   for (i=TABLE_SIZE-1 ; i>=0 ; i--)
      {
      stat = hash_insert (hash, g_key[i], g_data[i]);
      printf (
             "[%d,\"%s\"] = hash_insert (hash, key[%d], data[%d]) ... %s\n",
             stat, scl_statstr(stat), i, i, ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4 .......................... %s\n",
          hash_size(hash), ((hash_size(hash)==4) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == 5 ......................... %s\n",
          hash_count(hash), ((hash_count(hash)==5) ? "PASS" : "FAIL")
          );

   printf ("Iterate back through the hash.\n");
   iterator = hash_end (hash);
   for (i=0 ; i<TABLE_SIZE ; i++) g_flag[i] = 0;
   while (iterator != NULL)
      {
      data_flag (hash_data_get(iterator));
      iterator = hash_prev (iterator);
      }

   data = hash_remove (hash, g_key[3]);
   printf (
          "%p = hash_remove (hash, key[%d]) ............... %s\n",
          data,
          3,
          ((strcmp(data,g_data[3])==0) ? "PASS" : "FAIL")
          );
   data = hash_remove (hash, g_key[1]);
   printf (
          "%p = hash_remove (hash, key[%d]) ............... %s\n",
          data,
          1,
          ((strcmp(data,g_data[1])==0) ? "PASS" : "FAIL")
          );
   data = hash_remove (hash, g_key[4]);
   printf (
          "%p = hash_remove (hash, key[%d]) ............... %s\n",
          data,
          4,
          ((strcmp(data,g_data[4])==0) ? "PASS" : "FAIL")
          );
   data = hash_remove (hash, g_key[2]);
   printf (
          "%p = hash_remove (hash, key[%d]) ............... %s\n",
          data,
          2,
          ((strcmp(data,g_data[2])==0) ? "PASS" : "FAIL")
          );
   data = hash_remove (hash, g_key[0]);
   printf (
          "%p = hash_remove (hash, key[%d]) ............... %s\n",
          data,
          0,
          ((strcmp(data,g_data[0])==0) ? "PASS" : "FAIL")
          );

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4 .......................... %s\n",
          hash_size(hash), ((hash_size(hash)==4) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == 0 ......................... %s\n",
          hash_count(hash), ((hash_count(hash)==0) ? "PASS" : "FAIL")
          );

   printf ("\"Foreach\" on hash; each key-data pair in data only once?\n");
   for (i=0 ; i<TABLE_SIZE ; i++) g_flag[i] = 0;
   hash_foreach (hash, cbfn, NULL);

   printf ("Delete hash.\n");
   hash_del (hash);

   printf ("\n");

   return 0;
   }
