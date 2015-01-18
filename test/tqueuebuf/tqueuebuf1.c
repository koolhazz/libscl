/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"SCL_queuebuf.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static const char* const g_data [4] =
   {
   "This is the first message.",
   "This is the second message.",
   "This is the third message.",
   "This is the fourth message."
   };


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int  g_flag[4];
static char g_dataBuff[100];
static void* g_context = &g_flag[0];


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data, void* a_context);


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

static int cbfn (const char* a_key, long a_ord, void* a_data, void* a_context)
   {
   int i = 0;
   int j = -1;

   if (a_context != g_context)
      {
      printf ("Incorrect Context ..................................... FAIL\n");
      return SCL_NOTFOUND;
      }

   for (i=0 ; i<4 ; i++)
      {
      if (strcmp((char*)a_data,g_data[i]) == 0) j = i;
      }

   if ((j > -1) && (g_flag[j] == 0))
      {
      g_flag[j] = 1;
      printf ("Found data ............................................ PASS\n");
      }
   else if (g_flag[j] == 1)
      {
      printf ("Duplicate data ........................................ FAIL\n");
      }
   else
      {
      printf ("Data not found ........................................ FAIL\n");
      }

   return SCL_NOTFOUND;
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tqueuebuf1: Queuebuf Put, Get Tests";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int test_run (void)
   {
   void*    q;
   int      stat;
   size_t   size;
   int      i;

   printf ("Create new queuebuf.\n");
   q = (void*)malloc (1000);
   printf ("%p = malloc (1000);\n", q);
   stat = queuebuf_init (q, 1000, 5);
   printf ("%d = queuebuf_init (q, 1000, 5);\n", stat);

   printf ("queuebuf statistics.\n");
   printf ("%3ld = queuebuf_count (%p);\n",queuebuf_count(q), q);
   printf ("%3ld = queuebuf_header_size (%p);\n",queuebuf_header_size(q), q);
   printf ("%3ld = queuebuf_buff_size (%p);\n",queuebuf_buff_size(q), q);
   printf ("%3ld = queuebuf_buff_used (%p);\n",queuebuf_buff_used(q), q);
   printf ("%3ld = queuebuf_buff_avail (%p);\n",queuebuf_buff_avail(q), q);

   printf ("Push data into queuebuf.\n");
   stat = queuebuf_put (q, g_data[0], strlen(g_data[0])+1);
   printf (
          "([%d,%s] = queuebuf_put (q, \"%s\", %d)) .... %s\n",
          stat, scl_statstr(stat), g_data[0], strlen(g_data[0])+1,
          ((stat==SCL_OK) ? "PASS" : "FAIL")
          );
   stat = queuebuf_put (q, g_data[1], strlen(g_data[1])+1);
   printf (
          "([%d,%s] = queuebuf_put (q, \"%s\", %d)) ... %s\n",
          stat, scl_statstr(stat), g_data[1], strlen(g_data[1])+1,
          ((stat==SCL_OK) ? "PASS" : "FAIL")
          );
   stat = queuebuf_put (q, g_data[2], strlen(g_data[2])+1);
   printf (
          "([%d,%s] = queuebuf_put (q, \"%s\", %d)) .... %s\n",
          stat, scl_statstr(stat), g_data[2], strlen(g_data[2])+1,
          ((stat==SCL_OK) ? "PASS" : "FAIL")
          );
   stat = queuebuf_put (q, g_data[3], strlen(g_data[3])+1);
   printf (
          "([%d,%s] = queuebuf_put (q, \"%s\", %d)) ... %s\n",
          stat, scl_statstr(stat), g_data[3], strlen(g_data[3])+1,
          ((stat==SCL_OK) ? "PASS" : "FAIL")
          );

   printf ("foreach on queuebuf:\n");
   for (i=0 ; i<4 ; i++) g_flag[i] = 0;
   queuebuf_foreach (q, cbfn, g_context);

   printf ("queuebuf statistics.\n");
   printf ("%3ld = queuebuf_count (%p);\n", queuebuf_count(q), q);
   printf ("%3ld = queuebuf_header_size (%p);\n", queuebuf_header_size(q), q);
   printf ("%3ld = queuebuf_buff_size (%p);\n", queuebuf_buff_size(q), q);
   printf ("%3ld = queuebuf_buff_used (%p);\n", queuebuf_buff_used(q), q);
   printf ("%3ld = queuebuf_buff_avail (%p);\n", queuebuf_buff_avail(q), q);
   {
   int s = strlen(g_data[0]) + 1 +
           strlen(g_data[1]) + 1 +
           strlen(g_data[2]) + 1 +
           strlen(g_data[3]) + 1;
   printf (
          "queuebuf_count (%p) == 4 ..................................... %s\n",
          q, ((queuebuf_count(q)==4) ? "PASS" : "FAIL")
          );
   printf (
          "queuebuf_buff_used (%p) == %d ............................... %s\n",
          q, s, ((queuebuf_buff_used(q)==s) ? "PASS" : "FAIL")
          );
   }

   for (i=0 ; i<4 ; i++) g_flag[i] = 0;

   printf ("Pull data from queuebuf.\n");
   stat = queuebuf_get (q, g_dataBuff, &size);
   printf (
          "[%d,%s] = queuebuf_get (q, g_dataBuff, &size);\n",
          stat, scl_statstr(stat)
          );
   printf ("data(%ld) = \"%s\"(%d)\n", size, g_dataBuff, strlen(g_dataBuff)+1);
   (void)cbfn (NULL, size, g_dataBuff, g_context);

   printf ("Pull data from queuebuf.\n");
   stat = queuebuf_get (q, g_dataBuff, &size);
   printf (
          "[%d,%s] = queuebuf_get (q, g_dataBuff, &size);\n",
          stat, scl_statstr(stat)
          );
   printf ("data(%ld) = \"%s\"(%d)\n", size, g_dataBuff, strlen(g_dataBuff)+1);
   (void)cbfn (NULL, size, g_dataBuff, g_context);

   printf ("Pull data from queuebuf.\n");
   stat = queuebuf_get (q, g_dataBuff, &size);
   printf (
          "[%d,%s] = queuebuf_get (q, g_dataBuff, &size);\n",
          stat, scl_statstr(stat)
          );
   printf ("data(%ld) = \"%s\"(%d)\n", size, g_dataBuff, strlen(g_dataBuff)+1);
   (void)cbfn (NULL, size, g_dataBuff, g_context);

   printf ("Pull data from queuebuf.\n");
   stat = queuebuf_get (q, g_dataBuff, &size);
   printf (
          "[%d,%s] = queuebuf_get (q, g_dataBuff, &size);\n",
          stat, scl_statstr(stat)
          );
   printf ("data(%ld) = \"%s\"(%d)\n", size, g_dataBuff, strlen(g_dataBuff)+1);
   (void)cbfn (NULL, size, g_dataBuff, g_context);

   printf ("queuebuf statistics.\n");
   printf ("%3ld = queuebuf_count (%p);\n", queuebuf_count(q));
   printf ("%3ld = queuebuf_header_size (%p);\n", queuebuf_header_size(q));
   printf ("%3ld = queuebuf_buff_size (%p);\n", queuebuf_buff_size(q));
   printf ("%3ld = queuebuf_buff_used (%p);\n", queuebuf_buff_used(q));
   printf ("%3ld = queuebuf_buff_avail (%p);\n", queuebuf_buff_avail(q));
   printf (
          "queuebuf_count (%p) == 0 ..................................... %s\n",
          q, ((queuebuf_count(q)==0) ? "PASS" : "FAIL")
          );
   printf (
          "queuebuf_buff_used (%p) == 0 ................................. %s\n",
          q, ((queuebuf_buff_used(q)==0) ? "PASS" : "FAIL")
          );

   printf ("Foreach on queuebuf (empty).\n");
   queuebuf_foreach (q, cbfn, g_context);

   printf ("Erase queuebuf.\n");
   queuebuf_erase (q);

   printf ("Delete queuebuf.\n");
   printf ("free (q);\n");
   free (q);

   printf ("\n");

   return 0;
   }
