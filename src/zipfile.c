#ifndef ZIPFILE_C_
#define ZIPFILE_C_

#include <zip.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "mem.h"

char *get_contents(char *path)
{
     /* set up some variables */
     int errp;
     char full_path[200];
     strcpy(full_path, path);

     /* open ziped word document file */
     zip_t *archive = zip_open(path, ZIP_RDONLY, &errp);
     zip_file_t *file = zip_fopen(archive, "word/document.xml", ZIP_FL_UNCHANGED);

     /* find size of file */
     struct stat st;
     stat(strcat(full_path, "/word/document.xml"), &st);
     int size = st.st_size + 10; // add a buffer... just in case

     /* return contents of file */
     char *contents = safe_malloc(size);
     zip_fread(file, contents, size);
     return contents;
}

#endif /* ZIPFILE_C_ */
