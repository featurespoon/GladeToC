#ifndef G2C_FILE_PARSER_H
#define G2C_FILE_PARSER_H

#include <stdio.h>
#include <glib.h>

typedef enum tag_FileType
  {
    FT_SOURCE,
    FT_PO,
    FT_MAKE,
    FT_MAIN
  } FileType;

typedef struct tag_g2cFileParser
  {
    gchar      *file_name;
    const g2cProject *project;
    FileType    file_type;
    
    /* items is a list of:
     * FT_SOURCE - function names in a source file
     * FT_PO     - source file names in po/POTFILES.in
     * FT_MAKE   - source file names in $src/Makefile.am
     * FT_MAIN   - widget creation declarations/functions in $src/main.c
     */
    GList *items; 
  }
g2cFileParser;

g2cFileParser *
g2c_file_parser_new( const gchar *file_name, const g2cProject *project, FileType file_type );

void
g2c_file_parser_add_file(g2cFileParser *parser, const gchar *file_name, FileType file_type);

void
g2c_file_parser_destroy( g2cFileParser *parser );

void
g2c_file_parser_add_item (g2cFileParser *parser,
			  gchar         *item);

gboolean
g2c_file_parser_item_exists( g2cFileParser *parser,
			     gchar         *item );

void 
g2c_file_parser_update_main_file (g2cFileParser *parser, g2cWidget *widget);


#endif

