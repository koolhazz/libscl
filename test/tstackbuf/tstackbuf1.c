/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	<string.h>
#include	"SCL_stackbuf.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static const char* g_data1[4] =
   {
   ".egassem htruof eht si sihT",
   ".egassem driht eht si sihT",
   ".egassem dnoces eht si sihT",
   ".egassem tsrif eht si sihT"
   };

static const char* g_data2[4] =
   {
   "This is the first message.",
   "This is the second message.",
   "This is the third message.",
   "This is the fourth message."
   };


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static char g_dataBuff[100];


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static void* getfn (size_t a_size);
static int putfn (void* a_block, size_t a_size);


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static void* getfn (size_t a_size)
   {
   return NULL;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int putfn (void* a_block, size_t a_size)
   {
   return SCL_ERROR;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tstackbuf1: Stackbuf Push and Pull Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   SCL_stackbuf_t   s;

   int      stat;
   size_t   size;

   printf ("Create new stackbuf.\n");
   size = 200;
   s = stackbuf_new (NULL, NULL, size);
   printf ("%p = stackbuf_init (NULL, NULL, %ld);\n", s, size);

   printf ("stackbuf statistics.\n");
   printf ("%ld = stackbuf_size (%p);\n", stackbuf_size(s), s);
   printf ("%ld = stackbuf_nin (%p);\n", stackbuf_nin(s), s);
   printf ("%ld = stackbuf_nout (%p);\n", stackbuf_nout(s), s);

   printf ("Push data into stackbuf.\n");
   stat = stackbuf_push (s, g_data1[0], strlen(g_data1[0]));
   printf (
          "[%d,%s] = stackbuf_push (s, \"%s\", %d)) ... %s\n",
          stat, scl_statstr(stat), g_data1[0], strlen(g_data1[0]),
          ((stat==SCL_OK) ? "PASS" : "FAIL")
          );
   stat = stackbuf_push (s, g_data1[1], strlen(g_data1[1]));
   printf (
          "[%d,%s] = stackbuf_push (s, \"%s\", %d)) .... %s\n",
          stat, scl_statstr(stat), g_data1[1], strlen(g_data1[1]),
          ((stat==SCL_OK) ? "PASS" : "FAIL")
          );
   stat = stackbuf_push (s, g_data1[2], strlen(g_data1[2]));
   printf (
          "[%d,%s] = stackbuf_push (s, \"%s\", %d)) ... %s\n",
          stat, scl_statstr(stat), g_data1[2], strlen(g_data1[2]),
          ((stat==SCL_OK) ? "PASS" : "FAIL")
          );
   stat = stackbuf_push (s, g_data1[3], strlen(g_data1[3]));
   printf (
          "[%d,%s] = stackbuf_push (s, \"%s\", %d)) .... %s\n",
          stat, scl_statstr(stat), g_data1[3], strlen(g_data1[3]),
          ((stat==SCL_OK) ? "PASS" : "FAIL")
          );

   printf ("stackbuf statistics.\n");
   printf ("%ld = stackbuf_size (%p);\n", stackbuf_size(s), s);
   printf ("%ld = stackbuf_nin (%p);\n", stackbuf_nin(s), s);
   printf ("%ld = stackbuf_nout (%p);\n", stackbuf_nout(s), s);
   {
   int z = strlen(g_data1[0]) +
           strlen(g_data1[1]) +
           strlen(g_data1[2]) +
           strlen(g_data1[3]);
   printf (
          "(%ld = stackbuf_size (%p)) == %d ............................. %s\n",
          stackbuf_size(s), s, z, ((stackbuf_size(s)==z) ? "PASS" : "FAIL")
          );
   }

   printf ("Pull data from stackbuf.\n");
   size = stackbuf_pull (s, g_dataBuff, strlen(g_data1[3]));
   g_dataBuff[size] = '\0';
   printf (
          "(%ld = stackbuf_pull (s, g_dataBuff, %d)) == %ld ............. %s\n",
          size, strlen(g_data1[3]), strlen(g_data1[3]),
          ((size==strlen(g_data1[3])) ? "PASS" : "FAIL")
          );
   printf ("data(%ld) = \"%s\"(%d)\n", size, g_dataBuff, strlen(g_dataBuff));

   printf ("Pull data from stackbuf.\n");
   size = stackbuf_pull (s, g_dataBuff, strlen(g_data1[2]));
   g_dataBuff[size] = '\0';
   printf (
          "(%ld = stackbuf_pull (s, g_dataBuff, %d)) == %ld ............. %s\n",
          size, strlen(g_data1[2]), strlen(g_data1[2]),
          ((size==strlen(g_data1[2])) ? "PASS" : "FAIL")
          );
   printf ("data(%ld) = \"%s\"(%d)\n", size, g_dataBuff, strlen(g_dataBuff));

   printf ("Pull data from stackbuf.\n");
   size = stackbuf_pull (s, g_dataBuff, strlen(g_data1[1]));
   g_dataBuff[size] = '\0';
   printf (
          "(%ld = stackbuf_pull (s, g_dataBuff, %d)) == %ld ............. %s\n",
          size, strlen(g_data1[1]), strlen(g_data1[1]),
          ((size==strlen(g_data1[1])) ? "PASS" : "FAIL")
          );
   printf ("data(%ld) = \"%s\"(%d)\n", size, g_dataBuff, strlen(g_dataBuff));

   printf ("Pull data from stackbuf.\n");
   size = stackbuf_pull (s, g_dataBuff, strlen(g_data1[0]));
   g_dataBuff[size] = '\0';
   printf (
          "(%ld = stackbuf_pull (s, g_dataBuff, %d)) == %ld ............. %s\n",
          size, strlen(g_data1[0]), strlen(g_data1[0]),
          ((size==strlen(g_data1[0])) ? "PASS" : "FAIL")
          );
   printf ("data(%ld) = \"%s\"(%d)\n", size, g_dataBuff, strlen(g_dataBuff));

   printf ("stackbuf statistics.\n");
   printf ("%ld = stackbuf_size (%p);\n", stackbuf_size(s), s);
   printf ("%ld = stackbuf_nin (%p);\n", stackbuf_nin(s), s);
   printf ("%ld = stackbuf_nout (%p);\n", stackbuf_nout(s), s);
   printf (
          "(%ld = stackbuf_size (%p)) == 0 .............................. %s\n",
          stackbuf_size(s), s, ((stackbuf_size(s)==0) ? "PASS" : "FAIL")
          );

   printf ("Erase stackbuf.\n");
   stackbuf_erase (s);

   printf ("Delete stackbuf.\n");
   stackbuf_del (s);

   printf ("\n");

   return 0;
   }
