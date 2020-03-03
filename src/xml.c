#ifndef XML_C_
#define XML_C_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "mem.h"

static void parse_doc(char *docname, char *output)
{
     /* init variables */
     xmlDoc *doc;
     xmlNode *root, *first_child, *node1, *node2, *node3, *node4;

     /* do actual parsing of document */
     doc = xmlReadFile(docname, NULL, 0);
     if (doc == NULL ) {
          fprintf(stderr,"Document not parsed successfully. \n");
          return;
     }
     root = xmlDocGetRootElement(doc);
     if (root == NULL) {
          fprintf(stderr,"empty document\n");
          xmlFreeDoc(doc);
          return;
     }
     if (xmlStrcmp(root->name, (const xmlChar *) "document") != 0) {
          fprintf(stderr,"document of the wrong type, root node != document");
          xmlFreeDoc(doc);
          return;
     }
     xmlChar *key;

     FILE *fp;
     fp = fopen(output, "w");

     first_child = root->children;
     for (node1 = first_child; node1; node1 = node1->next) {
          if ((xmlStrcmp(node1->name, (const xmlChar *)"body")) == 0) {
               for(node2 = node1->children; node2; node2 = node2->next) {
                    if ((xmlStrcmp(node2->name, (const xmlChar *)"p")) == 0) {
                         for(node3 = node2->children; node3; node3 = node3->next) {
                              if ((xmlStrcmp(node3->name, (const xmlChar *)"r")) == 0) {
                                   for (node4 = node3->children; node4; node4 = node4->next) {
                                        if((!xmlStrcmp(node4->name, (const xmlChar *)"t"))) {
                                             key = xmlNodeListGetString(doc, node4->xmlChildrenNode, 1);
                                             fprintf(fp, "%s", key);
                                        }
                                   }
                              }
                         }
                    }
               }
          }
     }
     fclose(fp);
     xmlFree(key);
     xmlFreeDoc(doc);
}

#endif /* XML_C_ */
