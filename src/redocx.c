#include "zipfile.h"
#include "xml.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage()
{
     printf("%s", "usage: redocx -f file [-o output]");
     exit(0);
}

int main(int argc, char *argv[])
{
     /* init some variables */
     char *filename = safe_malloc(200);
     char *txtname = safe_malloc(200);
     int opt;

     /* parse cli args */
     while((opt = getopt(argc, argv, "f:ho:")) != -1)
     {
          switch(opt)
          {
          case 'f':
               filename = optarg;
               printf(":: input file: %s\n", optarg);
               break;
          case 'o':
               txtname = optarg;
               printf(":: output file: %s\n", optarg);
               break;
          case 'h':
               usage();
               break;
          case ':':
               printf("option needs a value\n");
               break;
          }
     }

     /* write contents of file to temp.xml */
     get_contents(filename);

     /* check an error */
     if (strcmp(txtname, "") == 0) {
          printf("%s", ":: No output file given. Using default.");
          txtname = "out.txt";
     }

     /* parse the doc and write text to a file */
     parse_doc(TEMPFILE, txtname);

     /* remove our extra file */
     remove(TEMPFILE);

     /* return */
     return 0;
}
