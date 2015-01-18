/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	<stdlib.h>
#include	"SCL_config.h"
#include	"SCL_map.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int g_whacker;


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data);
static long new_key (void);
static void* new_data (void);


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data)
   {
   printf ("key = \"%s\", ", a_key);
   printf ("ord = %08X, ",   a_ord);
   printf ("data = \"%s\"\n", (char*)a_data);
   return ++g_whacker < 10 ? SCL_NOTFOUND : SCL_OK;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static long new_key (void)
   {
   int i;
   long key = 0;
   for (i=0 ; i<20 ; i++)
      {
      key = 37L * (long)rand();
      }
   return key;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static void* new_data (void)
   {
   int i;
   char* data = scl_alloc (10);
   for (i=0 ; i<10 ; i++)
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
   return "tmap4: Map Memory Usage Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   SCL_map_t        map;
   SCL_iterator_t   iterator;

   long    key;
   void*   data;
   int     stat;
   long    i;

   printf ("Create map: ");
   fflush (stdout);
   map = map_new();
   printf (
          "(%p = map_new (NULL)) != NULL ... %s\n",
          map, ((map!=NULL) ? "PASS" : "FAIL")
          );

   printf ("Insert arbitrary items into map: ");
   fflush (stdout);
   for (i=0 ; i<1000000 ; i++)
      {
      key  = new_key();
      data = new_data();
      stat = map_insert (map, key, data);
      if (stat != SCL_OK) i = 1000000;
      }
   printf ("%ld.\n", map_count(map));

   printf ("Erase map.\n");
   map_erase (map);

   printf ("Insert arbitrary items into map: ");
   fflush (stdout);
   for (i=0 ; i<1000000 ; i++)
      {
      key  = new_key();
      data = new_data();
      stat = map_insert (map, key, data);
      if (stat != SCL_OK) i = 1000000;
      }
   printf ("%ld.\n", map_count(map));

   printf ("Erase map.\n");
   map_erase (map);

   printf ("Map table count.\n");
   printf (
          "(%ld = map_count (map) == 0) ......................... %s\n",
          map_count(map), ((map_count(map) == 0) ? "PASS" : "FAIL")
          );

   printf ("Delete map.\n");
   map_del (map);

   printf ("\n");

   return 0;
   }
