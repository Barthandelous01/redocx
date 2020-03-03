#ifndef ZIPFILE_C_
#define ZIPFILE_C_

#include <zip.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#include "mem.h"
#include "constants.h"

void get_contents(char *path)
{
     if(strcmp(path, "") == 0) {
          fprintf(stderr, "%s", "No filename specified");
          exit(-1);
     }
     /* set up some variables */
     int errp = 0;
     char full_path[200];
     strcpy(full_path, path);

     /* open ziped word document file */
     zip_t *archive = zip_open(path, ZIP_RDONLY, &errp);

     /* quick error check */
     if (errp != 0) {
          fprintf(stderr, "%s", "Error extracting from zip archive");
          exit(-1);
     }
     zip_file_t *file = zip_fopen(archive, "word/document.xml", ZIP_FL_UNCHANGED);

     /* find size of file */
     struct zip_stat st;
     zip_stat(archive, "word/document.xml", 0, &st);
     int size = st.size + 10; // add a buffer... just in case

     /* return contents of file */
     char *contents = safe_malloc(size);
     zip_fread(file, contents, size);

     /* cleanup for libzip */
     zip_fclose(file);
     zip_close(archive);

     /* put file contents into temp.xml */
     FILE *fp;
     fp = fopen(TEMPFILE, "wt");
     fputs(contents, fp);
     fclose(fp);
}

#endif /* ZIPFILE_C_ */
