#include "zipfile.h"
#include "xml.h"
#include "mem.h"
#include "constants.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <config.h>

void usage()
{
     printf("%s", "A blazing-fast .docx decoder\n"
            "\n"
            "USAGE:\n"
            "    redocx -f file [-o outfile] [-x]\n"
            "\n"
            "OPTIONS:\n"
            "-V, --version           Print version info and exit\n"
            "-h, --help              Print tis message and exit\n"
            "-x, --xml               Leave temporary XML file\n"
            "-f, --filename          The filename of the docx file\n"
            "-o, --outfile           The output text file\n");
     exit(0);
}

void version()
{
     printf("%s", PACKAGE_STRING "\nCopyright (C) 2020-2021 Barthandelous01\n\
License RBSD 3-Clause License.\n\
This is free software; you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n");
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
     static struct option longopts[] = {
         {"filename", required_argument, NULL, 'f'},
         {"outfile",  required_argument, NULL, 'o'},
         {"xml",      no_argument,       NULL, 'x'},
         {"help",     no_argument,       NULL, 'h'},
         {"version",  no_argument,       NULL, 'V'}
     };
     while((opt = getopt_long(argc, argv, "f:ho:xV", longopts, NULL)) != -1)
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
          case 'V':
               version();
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
