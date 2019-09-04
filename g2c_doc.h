#ifndef G2C_DOC_H
#define G2C_DOC_H

#include <gtk/gtk.h>
#include <stdio.h>

#include "g2c_project.h"
#include "g2c_file_parser.h"



/******************************************************************
 **                      Global Variables                        **
 ******************************************************************/

FILE          *CURRENT_FILE;
g2cFileParser *CURRENT_SOURCE_PARSER;
//g2cFileParser *CURRENT_PO_PARSER;
g2cFileParser *CURRENT_MAKE_PARSER;
g2cFileParser *CURRENT_MAIN_PARSER;
gchar         *DIR_PREFIX;
gchar         *MAIN_WINDOW;


/******************************************************************
 **                    Function Prototypes                       **
 ******************************************************************/

g2cDoc *g2c_doc_new( gchar *xml_file_name );
void    g2c_doc_destroy( g2cDoc *doc );

void    g2c_doc_parse( g2cDoc *doc );
void    g2c_doc_output( g2cDoc *doc );


#endif

