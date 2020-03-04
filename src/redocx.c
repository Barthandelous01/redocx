#include "zipfile.h"
#include "xml.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage()
{
     printf("%s", "usage: redocx -f file [-x] [-o output]");
     exit(0);
}

int main(int argc, char *argv[])
{
     /* init some variables */
     char *filename = safe_malloc(200);
     char *txtname = safe_malloc(200);
     txtname = "";
     int opt;
     FILE *fp = NULL;
     int xmlarg = 0;

     /* parse cli args */
     while((opt = getopt(argc, argv, "f:ho:x")) != -1)
     {
          switch(opt)
          {
          case 'f':
               filename = optarg;
               break;
          case 'o':
               txtname = optarg;
               break;
          case 'h':
               usage();
               break;
          case 'x':
               xmlarg = 1;
               break;
          case ':':
               printf("option needs a value\n");
               break;
          }
     }

     /* write contents of file to temp.xml */
     get_contents(filename);

     /* do output parsing */
     if (strcmp(txtname, "") == 0) {
          fp = stdout;
     } else {
          fp = fopen(txtname, "w");
          if (fp == NULL) {
               printf("%s", "Error opening file");
               exit(-1);
          }
     }

     /* parse the doc and write text to a file */
     parse_doc(TEMPFILE, fp);

     /* check if they want to remove the temp xml or keep it */
     if (xmlarg == 0)
          remove(TEMPFILE);

     /* return */
     return 0;
}
