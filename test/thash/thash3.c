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

static const char* g_data1[TABLE_SIZE] =
   {
   "The quick brown fox jumped over the lazy dog.",
   "The lazy dog slept fast.",
   "The slow red fox fell down.",
   "What did you expect?",
   "What did you expect?"
   };

static const char* g_data2[TABLE_SIZE] =
   {
   "First replaced data.",
   "The lazy dog slept fast.",
   "The slow red fox fell down.",
   "Second replaced data.",
   "What did you expect?"
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
   int i;
   for (i=0 ; i<TABLE_SIZE ; i++)
      {
      if ((strcmp(a_key,g_key[i]) == 0) && (strcmp(a_data,g_data1[i]) == 0))
         {
         break;
         }
      }
   if (i == TABLE_SIZE)
      {
      printf ("Key-data pair not found in data ....................................... FAIL\n");
      printf (" Key: \"%s\"\n", a_key);
      printf ("Data: \"%s\"\n", a_data);
      return SCL_NOTFOUND;
      }
   if (g_flag[i] == 1)
      {
      printf ("Duplicate key-data pair ............................................... FAIL\n");
      printf (" Key: \"%s\"\n", a_key);
      printf ("Data: \"%s\"\n", a_data);
      return SCL_NOTFOUND;
      }
   g_flag[i] = 1;
   printf ("Found key-data pair ................................................... PASS\n");
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn2 (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   int i;
   for (i=0 ; i<TABLE_SIZE ; i++)
      {
      if ((strcmp(a_key,g_key[i]) == 0) && (strcmp(a_data,g_data2[i]) == 0))
         {
         break;
         }
      }
   if (i == TABLE_SIZE)
      {
      printf ("Key-data pair not found in data ....................................... FAIL\n");
      printf (" Key: \"%s\"\n", a_key);
      printf ("Data: \"%s\"\n", a_data);
      return SCL_NOTFOUND;
      }
   if (g_flag[i] == 1)
      {
      printf ("Duplicate key-data pair ............................................... FAIL\n");
      printf (" Key: \"%s\"\n", a_key);
      printf ("Data: \"%s\"\n", a_data);
      return SCL_NOTFOUND;
      }
   g_flag[i] = 1;
   printf ("Found key-data pair ................................................... PASS\n");
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "thash3: Hash Table Update Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   SCL_hash_t   hash;

   void*   data;
   int     stat;
   int     i;

   printf ("Create hash: ", hash);
   fflush (stdout);
   hash = hash_new (NULL);
   printf ("(%p = hash_new (NULL)) != NULL .................... ", hash);
   fflush (stdout);
   printf ("%s\n", ((hash!=NULL) ? "PASS" : "FAIL"));

   printf ("Insert into hash.\n");
   for (i=0 ; i<TABLE_SIZE ; i++)
      {
      stat = hash_insert (hash, g_key[i], g_data1[i]);
      printf (
             "[%d,\"%s\"] = hash_insert (hash, key[%d], data[%d]) .................... %s\n",
             stat, scl_statstr(stat), i, i, ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf ("\"Foreach\" on hash; each key-data pair in data only once?\n");
   for (i=0 ; i<TABLE_SIZE ; i++) g_flag[i] = 0;
   hash_foreach (hash, cbfn1, NULL);

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4 ........................................... %s\n",
          hash_size(hash), ((hash_size(hash)==4) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == 5 .......................................... %s\n",
          hash_count(hash), ((hash_count(hash)==5) ? "PASS" : "FAIL")
          );

   printf ("Replace in hash using key.\n");
   stat = hash_replace (hash, g_key[3], g_data2[3]);
   printf (
          "[%d,\"%s\"] = hash_replace (hash, key[3], \"%s\") ... %s\n",
          stat, scl_statstr(stat), g_data2[3], ((stat==SCL_OK) ? "PASS" : "FAIL")
          );

   printf ("Replace in hash using key.\n");
   stat = hash_replace (hash, g_key[0], g_data2[0]);
   printf (
          "[%d,\"%s\"] = hash_replace (hash, key[0], \"%s\") .... %s\n",
          stat, scl_statstr(stat), g_data2[0], ((stat==SCL_OK) ? "PASS" : "FAIL")
          );

   printf ("Hash table size and count.\n");
   printf (
          "(%ld = hash_size (hash)) == 4 ........................................... %s\n",
          hash_size(hash), ((hash_size(hash)==4) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = hash_count (hash)) == 5 .......................................... %s\n",
          hash_count(hash), ((hash_count(hash)==5) ? "PASS" : "FAIL")
          );

   printf ("\"Foreach\" on hash; each key-data pair in data only once?\n");
   for (i=0 ; i<TABLE_SIZE ; i++) g_flag[i] = 0;
   hash_foreach (hash, cbfn2, NULL);

   printf ("Delete hash.\n");
   hash_del (hash);

   printf ("\n");

   return 0;
   }
