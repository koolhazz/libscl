/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	"SCL_map.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#define	MAP_SIZE	(5)

/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int g_flag[MAP_SIZE];

static int g_key[MAP_SIZE] =
   {
   0x1234,
   0xAAAAAAAA,
   0x0101,
   0xABCDEF,
   0x5555
   };

static const char* g_data[MAP_SIZE] =
   {
   "The quick brown fox jumped over the lazy dog.",
   "The lazy dog slept fast.",
   "The quick brown fox fell down.",
   "What did you expect?",
   "Bunko Kanazawa, Akira Watase, Maiko Yuki"
   };

static void* g_context = &g_flag[0];


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (
                const char* a_unused,
                long        a_key,
                void*       a_data,
                void*       a_context
                );


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (
                const char* a_unused,
                long        a_key,
                void*       a_data,
                void*       a_context
                )
   {
   if (a_context != g_context)
      {
      printf ("Incorrect Context .................................. FAIL\n");
      return SCL_NOTFOUND;
      }
   int i;
   for (i=0 ; i<MAP_SIZE ; i++)
      {
      if ((a_key == g_key[i]) && (strcmp(a_data,g_data[i]) == 0))
         {
         break;
         }
      }
   if (i == MAP_SIZE)
      {
      printf ("Key-data pair not found in data .................... FAIL\n");
      printf (" Key: %08X\n", a_key);
      printf ("Data: \"%s\"\n", a_data);
      return SCL_NOTFOUND;
      }
   if (g_flag[i] == 1)
      {
      printf ("Duplicate key-data pair ............................ FAIL\n");
      printf (" Key: %08X\n", a_key);
      printf ("Data: \"%s\"\n", a_data);
      return SCL_NOTFOUND;
      }
   g_flag[i] = 1;
   printf ("Found key-data pair ................................ PASS\n");
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static void data_flag (void* a_data)
   {
   int i;
   for (i=0 ; i<MAP_SIZE ; i++)
      {
      if ((strcmp(a_data,g_data[i]) == 0) && (g_flag[i] == 0)) break;
      }
   if (i == MAP_SIZE)
      {
      printf ("Data not found in data set ......................... FAIL\n");
      printf ("Data: \"%s\"\n", a_data);
      return;
      }
   if (g_flag[i] == 1)
      {
      printf ("Duplicate data ..................................... FAIL\n");
      printf ("Data: \"%s\"\n", a_data);
      return;
      }
   g_flag[i] = 1;
   printf ("Found data ......................................... PASS\n");
   return;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tmap1: Map Basic Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   SCL_map_t        map;
   SCL_iterator_t   iterator;

   void*   data;
   int     stat;
   int     i;

   printf ("Create map: ");
   fflush (stdout);
   map = map_new();
   printf (
          "(%p = map_new (NULL)) != NULL ... %s\n",
          map, ((map!=NULL) ? "PASS" : "FAIL")
          );

   printf ("Insert into map.\n");
   for (i=0 ; i<MAP_SIZE ; i++)
      {
      stat = map_insert (map, g_key[i], g_data[i]);
      printf (
             "[%d,\"%s\"] = map_insert (map, key[%d], data[%d]) ... %s\n",
             stat, scl_statstr(stat), i, i, ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf ("Iterate through the map.\n");
   iterator = map_begin (map);
   for (i=0 ; i<MAP_SIZE ; i++) g_flag[i] = 0;
   while (iterator != NULL)
      {
      data_flag (map_data_get(iterator));
      iterator = map_next (iterator);
      }

   printf ("Iterate back through the map.\n");
   iterator = map_end (map);
   for (i=0 ; i<MAP_SIZE ; i++) g_flag[i] = 0;
   while (iterator != NULL)
      {
      data_flag (map_data_get(iterator));
      iterator = map_prev (iterator);
      }

   printf ("Foreach on map.\n");
   for (i=0 ; i<MAP_SIZE ; i++) g_flag[i] = 0;
   map_foreach (map, cbfn, g_context);

   printf ("Map table size and count.\n");
   printf (
          "(%ld = map_size (map) == 4) .......................... %s\n",
          map_size(map), ((map_size(map) == 4) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = map_count (map) == 5) ......................... %s\n",
          map_count(map), ((map_count(map) == 5) ? "PASS" : "FAIL")
          );

   printf ("Erase map.\n");
   map_erase (map);

   printf ("Map table size and count.\n");
   printf (
          "(%ld = map_size (map) == 4) .......................... %s\n",
          map_size(map), ((map_size(map) == 4) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = map_count (map) == 0) ......................... %s\n",
          map_count(map), ((map_count(map) == 0) ? "PASS" : "FAIL")
          );

   printf ("Delete map.\n");
   map_del (map);

   printf ("\n");

   return 0;
   }
