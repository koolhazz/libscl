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
   "this is the really double-plus extra longer key two",
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

static void* g_context = &g_flag[0];


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
   if (a_context != g_context)
      {
      printf ("Incorrect Context .................................... FAIL\n");
      return SCL_NOTFOUND;
      }
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
   return "thash1: Hash Table Basic Tests";
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

   printf ("Iterate through the hash.\n");
   iterator = hash_begin (hash);
   for (i=0 ; i<TABLE_SIZE ; i++) g_flag[i] = 0;
   while (iterator != NULL)
      {
      data_flag (hash_data_get(iterator));
      iterator = hash_next (iterator);
      }

   printf ("Iterate back through the hash.\n");
   iterator = hash_end (hash);
   for (i=0 ; i<TABLE_SIZE ; i++) g_flag[i] = 0;
   while (iterator != NULL)
      {
      data_flag (hash_data_get(iterator));
      iterator = hash_prev (iterator);
      }

   printf ("Foreach on hash; each key-data pair in data only once?\n");
   for (i=0 ; i<TABLE_SIZE ; i++) g_flag[i] = 0;
   hash_foreach (hash, cbfn, g_context);

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4 .......................... %s\n",
          hash_size(hash), ((hash_size(hash)==4) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == %d ......................... %s\n",
          hash_count(hash),
          TABLE_SIZE,
          ((hash_count(hash)==TABLE_SIZE) ? "PASS" : "FAIL")
          );

   printf ("Accesses on hash.\n");
   for (i=0 ; i<TABLE_SIZE ; i++)
      {
      data = hash_access (hash, g_key[i]);
      printf (
             "hash_access(hash,key[%d]) == data[%d] .................. %s\n",
             i, i, ((strcmp(data,g_data[i])==0) ? "PASS" : "FAIL")
             );
      }

   printf ("Accesses on hash via iterator.\n");
   for (i=0 ; i<TABLE_SIZE ; i++)
      {
      iterator = hash_at (hash, g_key[i]);
      printf (
             "hash_at(hash,key[%d]) => data[%d] ...................... %s\n",
             i,
             i,
             ((strcmp(hash_data_get(iterator),g_data[i])==0) ? "PASS" : "FAIL")
             );
      }

   printf ("Erase hash.\n");
   hash_erase (hash);

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4 .......................... %s\n",
          hash_size(hash), ((hash_size(hash)==4) ? "PASS" : "FAIL")
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
