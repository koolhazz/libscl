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

static const char* g_data1[MAP_SIZE] =
   {
   "The quick brown fox jumped over the lazy dog.",
   "The lazy dog slept fast.",
   "The quick brown fox fell down.",
   "What did you expect?",
   "Bunko Kanazawa, Akira Watase, Maiko Yuki"
   };

static const char* g_data2[MAP_SIZE] =
   {
   "The quick brown fox jumped over the lazy dog.",
   "This is the NEW data.",
   "The quick brown fox fell down.",
   "What did you expect?",
   "Kid Palooka"
   };


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static void data_flag (void* a_data, const char* a_table[]);


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static void data_flag (void* a_data, const char* a_table[])
   {
   int i;
   for (i=0 ; i<MAP_SIZE ; i++)
      {
      if ((strcmp(a_data,a_table[i]) == 0) && (g_flag[i] == 0)) break;
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
   printf ("Data: \"%s\"\n", a_data);
   return;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tmap2: Map Iterator-based Function Tests";
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
      stat = map_insert (map, g_key[i], g_data1[i]);
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
      data_flag (map_data_get(iterator), g_data1);
      iterator = map_next (iterator);
      }

   printf ("Map table size and count.\n");
   printf (
          "(%ld = map_size (map) == 4) .......................... %s\n",
          map_size(map), ((map_size(map) == 4) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = map_count (map) == 4) ......................... %s\n",
          map_count(map), ((map_size(map) == 4) ? "PASS" : "FAIL")
          );

   printf ("Get something from the map; key=0xAAAAAAAA.\n");
   iterator = map_at (map, 0xAAAAAAAA);
   data = map_data_get (iterator);
   printf ("map[0xAAAAAAAA] => \"%s\"\n", (char*)data);
   printf (
          "(map[0xAAAAAAAA] == g_data1[1]) .................... %s\n",
          ((strcmp(data,g_data1[1])==0) ? "PASS" : "FAIL")
          );

   printf ("Set something from the map; key=0xAAAAAAAA.\n");
   iterator = map_at (map, 0xAAAAAAAA);
   map_data_set (iterator, g_data2[1]);
   printf ("set map[0xAAAAAAAA] = \"%s\"\n", g_data2[1]);

   printf ("Get something from the map; key=0xAAAAAAAA.\n");
   iterator = map_at (map, 0xAAAAAAAA);
   data = map_data_get (iterator);
   printf ("map[0xAAAAAAAA] => \"%s\"\n", (char*)data);
   printf (
          "(map[0xAAAAAAAA] == g_data2[1]) .................... %s\n",
          ((strcmp(data,g_data2[1])==0) ? "PASS" : "FAIL")
          );

   printf ("Get something from the map; key=0x5555.\n");
   iterator = map_at (map, 0x5555);
   data = map_data_get (iterator);
   printf ("map[0x5555] => \"%s\"\n", (char*)data);
   printf (
          "(map[0x5555] == g_data1[4]) ........................ %s\n",
          ((strcmp(data,g_data1[4])==0) ? "PASS" : "FAIL")
          );

   printf ("Set something from the map; key=0x5555.\n");
   iterator = map_at (map, 0x5555);
   map_data_set (iterator, g_data2[4]);
   printf ("set map[0x5555] = \"%s\"\n", g_data2[4]);

   printf ("Get something from the map; key=0x5555.\n");
   iterator = map_at (map, 0x5555);
   data = map_data_get (iterator);
   printf ("map[0x5555] => \"%s\"\n", (char*)data);
   printf (
          "(map[0x5555] == g_data2[4]) ........................ %s\n",
          ((strcmp(data,g_data2[4])==0) ? "PASS" : "FAIL")
          );

   printf ("Iterate back through the map.\n");
   iterator = map_end (map);
   for (i=0 ; i<MAP_SIZE ; i++) g_flag[i] = 0;
   while (iterator != NULL)
      {
      data_flag (map_data_get(iterator), g_data2);
      iterator = map_prev (iterator);
      }

   printf ("Map table size and count.\n");
   printf (
          "(%ld = map_size (map) == 4) .......................... %s\n",
          map_size(map), ((map_size(map) == 4) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = map_count (map) == 4) ......................... %s\n",
          map_count(map), ((map_size(map) == 4) ? "PASS" : "FAIL")
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
