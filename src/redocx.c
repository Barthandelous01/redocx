#include "zipfile.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
     char *test = malloc(10000);
     test = get_contents("/Users/calebbrzezinski/Desktop/wc3.docx");
     printf("%s", test);
}
