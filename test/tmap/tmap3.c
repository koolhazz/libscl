/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	"SCL_map.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#define	MAP_SIZE1	(5)
#define	MAP_SIZE2	(7)


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int g_flag1[MAP_SIZE1];
static int g_flag2[MAP_SIZE2];

static int g_key1[MAP_SIZE1] =
   {
   0x1234,
   0xAAAAAAAA,
   0x0101,
   0xABCDEF,
   0x5555
   };

static int g_key2[MAP_SIZE2] =
   {
   0x10101010,
   0xCCCCCCCC,
   0xCACAD0D0,
   0xF1F0F1F0,
   0x33333333,
   0x00000002,
   0x00000001
   };

static const char* g_data1[MAP_SIZE1] =
   {
   "The quick brown fox jumped over the lazy dog.",
   "The lazy dog slept fast.",
   "The quick brown fox fell down.",
   "What did you expect?",
   "Bunko Kanazawa, Akira Watase, Maiko Yuki"
   };

static const char* g_data2[MAP_SIZE1] =
   {
   "replaced one",
   "replaced two",
   "replaced three",
   "replaced four",
   "replaced five"
   };

static const char* g_data3[MAP_SIZE2] =
   {
   "big new one",
   "big new two",
   "big new three",
   "big new four",
   "big new five",
   "big new six",
   "big new seven"
   };


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn1 (const char* a_key, long a_ord, void* a_data, void* a_context);
static int cbfn2 (const char* a_key, long a_ord, void* a_data, void* a_context);


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn1 (
                 const char* a_unused,
                 long        a_key,
                 void*       a_data,
                 void*       a_context
                 )
   {
   int i;
   printf ("k=%08X,", a_key);
   printf ("d=\"%s\"\n", (char*)a_data);
   for (i=0 ; i<MAP_SIZE1 ; i++)
      {
      if ((a_key == g_key1[i]) && (strcmp(a_data,g_data1[i]) == 0))
         {
         break;
         }
      }
   if (i == MAP_SIZE1) return SCL_NOTFOUND;
   if (g_flag1[i] == 1) return SCL_NOTFOUND;
   g_flag1[i] = 1;
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn2 (
                 const char* a_unused,
                 long        a_key,
                 void*       a_data,
                 void*       a_context
                 )
   {
   int i;
   printf ("k=%08X,", a_key);
   printf ("d=\"%s\"\n", (char*)a_data);
   for (i=0 ; i<MAP_SIZE1 ; i++)
      {
      if ((a_key == g_key1[i]) && (strcmp(a_data,g_data2[i]) == 0))
         {
         break;
         }
      }
   if (i == MAP_SIZE1) return SCL_NOTFOUND;
   if (g_flag1[i] == 1) return SCL_NOTFOUND;
   g_flag1[i] = 1;
   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tmap3: Map Insert, Replace, Remove and Access Tests";
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
          "(%p = map_new (NULL)) != NULL ..... %s\n",
          map, ((map!=NULL) ? "PASS" : "FAIL")
          );

   printf ("Insert into map.\n");
   for (i=0 ; i<MAP_SIZE1 ; i++)
      {
      stat = map_insert (map, g_key1[i], g_data1[i]);
      printf (
             "[%d,\"%s\"] = map_insert (map, key[%d], data1[%d]) .... %s\n",
             stat, scl_statstr(stat), i, i, ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf ("Foreach on map.\n");
   for (i=0 ; i<MAP_SIZE1 ; i++) g_flag1[i] = 0;
   map_foreach (map, cbfn1, NULL);
   stat = 0;
   for (i=0 ; i<MAP_SIZE1 ; i++) if (g_flag1[i] == 0) stat = 1;
   printf (
          "foreach() ............................................ %s\n",
          ((stat==0) ? "PASS" : "FAIL")
          );

   printf ("Replace in map.\n");
   for (i=0 ; i<MAP_SIZE1 ; i++)
      {
      stat = map_replace (map, g_key1[i], g_data2[i]);
      printf (
             "[%d,\"%s\"] = map_replace (map, key[%d], data2[%d]) ... %s\n",
             stat, scl_statstr(stat), i, i, ((stat==SCL_OK) ? "PASS" : "FAIL")
             );
      }

   printf ("Foreach on map.\n");
   for (i=0 ; i<MAP_SIZE1 ; i++) g_flag1[i] = 0;
   map_foreach (map, cbfn2, NULL);
   stat = 0;
   for (i=0 ; i<MAP_SIZE1 ; i++) if (g_flag1[i] == 0) stat = 1;
   printf (
          "foreach() ............................................ %s\n",
          ((stat==0) ? "PASS" : "FAIL")
          );

   printf ("Access the map.\n");
   for (i=0 ; i<MAP_SIZE1 ; i++)
      {
      data = map_access (map, g_key1[i]);
      printf (
             "%08p = map_access (map, key[%d]) ................. %s\n",
             data, i, ((strcmp(data,g_data2[i])==0) ? "PASS" : "FAIL")
             );
      }

   printf ("Remove from map.\n");
   for (i=0 ; i<MAP_SIZE1 ; i++)
      {
      data = map_remove (map, g_key1[i]);
      printf (
             "%08p = map_remove (map, key[%d]) ................. %s\n",
             data, i, ((strcmp(data,g_data2[i])==0) ? "PASS" : "FAIL")
             );
      }

   printf ("Foreach on map (empty).\n");
   for (i=0 ; i<MAP_SIZE1 ; i++) g_flag1[i] = 0;
   map_foreach (map, cbfn1, NULL);

   printf ("Erase map.\n");
   map_erase (map);

   printf ("Map table size and count.\n");
   printf (
          "(%ld = map_size (map) == 4) ............................ %s\n",
          map_size(map), ((map_size(map) == 4) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = map_count (map) == 0) ........................... %s\n",
          map_count(map), ((map_count(map) == 0) ? "PASS" : "FAIL")
          );

   printf ("Delete map.\n");
   map_del (map);

   printf ("\n");

   return 0;
   }
