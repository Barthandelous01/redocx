#include "zipfile.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
     /* init some variables */
     char *filename = safe_malloc(200);
     char *txtname = safe_malloc(200);
     int opt;

     /* parse cli args */
     while((opt = getopt(argc, argv, ":f:")) != -1)
     {
          switch(opt)
          {
          case 'f':
               filename = optarg;
               printf("filename: %s\n", optarg);
               break;
          case 'o':
               txtname = optarg;
               printf("output file: %s\n", optarg);
               break;
          case ':':
               printf("option needs a value\n");
               break;
          case '?':
               printf("unknown option: %c\n", optopt);
          break;
          }
     }
     /* write contents of file to temp.xml */
     get_contents(filename);

     /* return */
     return 0;
}
