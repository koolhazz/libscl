/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#define	DEBUG


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	"SCL_config.h"
#include	"tmain.h"


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

const char* test_title (void)
   {
   return "tconfig0: SCL Configuration";
   }


/* ************************************************************************* */
/*                                                                           */
/* ************************************************************************* */

int  test_run (void)
   {
   void*   buff = NULL;

   printf ("\n");
   printf ("SCL Credits: \"%s\".\n", scl_conf_credits());
   printf ("\n");
   printf ("SCL Version ....... \"%s\".\n", scl_conf_version());
   printf ("SCL Date .......... \"%s\".\n", scl_conf_date());
   printf ("SCL CFLAGS ........ \"%s\".\n", scl_conf_cflags());
   printf ("SCL SHARED_LIBS ... \"%s\".\n", scl_conf_shared_libs());
   printf ("SCL STATIC_LIBS ... \"%s\".\n", scl_conf_static_libs());
   printf ("\n");
   printf ("SCL_OK ......... \"%s\".\n", scl_statstr(SCL_OK));
   printf ("SCL_ERROR ...... \"%s\".\n", scl_statstr(SCL_ERROR));
   printf ("SCL_BADARG ..... \"%s\".\n", scl_statstr(SCL_BADARG));
   printf ("SCL_CORRUPT .... \"%s\".\n", scl_statstr(SCL_CORRUPT));
   printf ("SCL_NOMEM ...... \"%s\".\n", scl_statstr(SCL_NOMEM));
   printf ("SCL_NOTFOUND ... \"%s\".\n", scl_statstr(SCL_NOTFOUND));
   printf ("SCL_NOSVC ...... \"%s\".\n", scl_statstr(SCL_NOSVC));
   printf ("SCL_DUPKEY ..... \"%s\".\n", scl_statstr(SCL_DUPKEY));

   printf ("\n");
   printf ("Trial execution of the SCL allocator, deallocator.\n");
   buff = scl_alloc (10000);
   printf ("%p = scl_alloc(10000);\n", buff);
   scl_free (buff);
   printf ("(void)scl_free(%p);\n", buff);

   printf ("\n");
   printf ("Repeated execution of the SCL allocator, deallocator.\n");
   {
   void* vbuff[100000];
   long i;
   printf ("100000 allocations ..... ");
   fflush (stdout);
   for (i=0 ; i<100000 ; i++) vbuff[i] = scl_alloc (1000);
   printf ("done\n");
   printf ("100000 deallocations ... ");
   for (i=0 ; i<100000 ; i++) scl_free (vbuff[i]);
   printf ("done\n");
   }
   printf ("\n");

   return 0;
   }
