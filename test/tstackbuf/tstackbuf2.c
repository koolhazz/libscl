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

static char* g_data;
static void*  g_block;
static size_t g_size;


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
   printf (
           "getfn (s=%ld => %ld) ........................................ %s\n",
           a_size, g_size, ((a_size==g_size) ? "PASS" : "FAIL")
          );
   return g_block;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int putfn (void* a_block, size_t a_size)
   {
   printf ("putfn [a=%p,s=%ld]\n", a_block, a_size);
   g_block = a_block;
   g_size  = a_size;
   return SCL_OK;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tstackbuf2: Stackbuf putfn(), getfn(), stackbuf_pull_alloc() Tests";
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
   s = stackbuf_new (getfn, putfn, size);
   printf ("%p = stackbuf_init (getfn, putfn, %ld);\n", s, size);

   printf ("stackbuf statistics.\n");
   printf (
          "(%ld = stackbuf_size (%p)) == 0 .............................. %s\n",
          stackbuf_size(s), s, ((stackbuf_size(s)==0) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = stackbuf_nin (%p)) == 0 ............................... %s\n",
          stackbuf_nin(s), s, ((stackbuf_nin(s)==0) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = stackbuf_nout (%p)) == 0 .............................. %s\n",
          stackbuf_nout(s), s, ((stackbuf_nout(s)==0) ? "PASS" : "FAIL")
          );

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
   {
   int z = strlen(g_data1[0]) +
           strlen(g_data1[1]) +
           strlen(g_data1[2]) +
           strlen(g_data1[3]);
   printf (
          "(%ld = stackbuf_size (%p)) == %d .......................... %s\n",
          stackbuf_size(s), s, z, ((stackbuf_size(s)==z) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = stackbuf_nin (%p)) == 0 ............................... %s\n",
          stackbuf_nin(s), s, ((stackbuf_nin(s)==0) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = stackbuf_nout (%p)) == 0 .............................. %s\n",
          stackbuf_nout(s), s, ((stackbuf_nout(s)==0) ? "PASS" : "FAIL")
          );
   }

   printf ("Flush data from stackbuf.\n");
   stat = stackbuf_flush (s);
   printf (
          "([%d,%s] = stackbuf_flush (%p) .............................. %s\n",
          stat, scl_statstr(stat), s, ((stat==SCL_OK) ? "PASS" : "FAIL")
          );

   printf ("stackbuf statistics.\n");
   printf (
          "(%ld = stackbuf_size (%p)) == 0 .............................. %s\n",
          stackbuf_size(s), s, ((stackbuf_size(s)==0) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = stackbuf_nin (%p)) == 0 ............................... %s\n",
          stackbuf_nin(s), s, ((stackbuf_nin(s)==0) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = stackbuf_nout (%p)) == 1 .............................. %s\n",
          stackbuf_nout(s), s, ((stackbuf_nout(s)==1) ? "PASS" : "FAIL")
          );

   printf ("Pull data from stackbuf.\n");
   g_data = NULL;
   size = stackbuf_pull_alloc (s, (void**)&g_data, strlen(g_data1[3]));
   g_data[size] = '\0';
   printf (
          "(%ld = stackbuf_pull_alloc (s, g_data, %d)) == %ld ........... %s\n",
          size, strlen(g_data1[3]), strlen(g_data1[3]),
          ((size==strlen(g_data1[3])) ? "PASS" : "FAIL")
          );
   printf ("data(%ld) = \"%s\"(%d)\n", size, g_data, strlen(g_data));
   free (g_data);

   printf ("Pull data from stackbuf.\n");
   g_data = NULL;
   size = stackbuf_pull_alloc (s, (void**)&g_data, strlen(g_data1[2]));
   g_data[size] = '\0';
   printf (
          "(%ld = stackbuf_pull_alloc (s, g_data, %d)) == %ld ........... %s\n",
          size, strlen(g_data1[2]), strlen(g_data1[2]),
          ((size==strlen(g_data1[2])) ? "PASS" : "FAIL")
          );
   printf ("data(%ld) = \"%s\"(%d)\n", size, g_data, strlen(g_data));
   free (g_data);

   printf ("Pull data from stackbuf.\n");
   g_data = NULL;
   size = stackbuf_pull_alloc (s, (void**)&g_data, strlen(g_data1[1]));
   g_data[size] = '\0';
   printf (
          "(%ld = stackbuf_pull_alloc (s, g_data, %d)) == %ld ........... %s\n",
          size, strlen(g_data1[1]), strlen(g_data1[1]),
          ((size==strlen(g_data1[1])) ? "PASS" : "FAIL")
          );
   printf ("data(%ld) = \"%s\"(%d)\n", size, g_data, strlen(g_data));
   free (g_data);

   printf ("Pull data from stackbuf.\n");
   g_data = NULL;
   size = stackbuf_pull_alloc (s, (void**)&g_data, strlen(g_data1[0]));
   g_data[size] = '\0';
   printf (
          "(%ld = stackbuf_pull_alloc (s, g_data, %d)) == %ld ........... %s\n",
          size, strlen(g_data1[0]), strlen(g_data1[0]),
          ((size==strlen(g_data1[0])) ? "PASS" : "FAIL")
          );
   printf ("data(%ld) = \"%s\"(%d)\n", size, g_data, strlen(g_data));
   free (g_data);

   printf ("stackbuf statistics.\n");
   printf (
          "(%ld = stackbuf_size (%p)) == 0 .............................. %s\n",
          stackbuf_size(s), s, ((stackbuf_size(s)==0) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = stackbuf_nin (%p)) == 1 ............................... %s\n",
          stackbuf_nin(s), s, ((stackbuf_nin(s)==1) ? "PASS" : "FAIL")
          );
   printf (
          "(%ld = stackbuf_nout (%p)) == 1 .............................. %s\n",
          stackbuf_nout(s), s, ((stackbuf_nout(s)==1) ? "PASS" : "FAIL")
          );

   printf ("Erase stackbuf.\n");
   stackbuf_erase (s);

   printf ("Delete stackbuf.\n");
   stackbuf_del (s);

   printf ("\n");

   return 0;
   }
