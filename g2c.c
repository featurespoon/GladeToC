#include <glib.h>

#include <unistd.h>
#include <sys/stat.h>

#include <gtk/gtk.h>
#include "g2c_widget.h"
#include "g2c_doc.h"
#include "g2c_helpers.h"
#include "g2c_message.h"


/*  THE COMMON CODE FOR G2C  */

/* check if supplied directory exists. If not, create it.  */
void create_dir(gchar *dir)
{
struct stat s_stat;

/* Does the directory exist? */
  if( -1 == stat( dir, &s_stat ) ) {
      if( ENOENT == errno )  {
          /* Directory does not exist. Try to create it. */
          g_message("Creating directory %s\n", dir);
#ifdef WIN32
          mkdir ( dir );
#else
          mkdir( dir, 0775 );
#endif
      } else {
          g_error( "Could not create or access source directory: %s\n", dir );
      }
    }
}

#ifdef WIN32
int g2c_common(gchar* program, 
        gchar* glade_file, 
        gchar* gen_dir, 
        gboolean gen_cmake, 
        gboolean no_parsing, 
        gchar* resource_file)
#else
int g2c_common(gchar* program, 
        gchar* glade_file, 
        gchar* gen_dir, 
        gboolean gen_cmake, 
        gboolean no_parsing)
#endif
{
g2cDoc *doc        = NULL;
guint     handler_id;
int       iret = 0;

 handler_id = g_log_set_handler (NULL,
				  G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL,
				  g2c_message_handler,
				  NULL);
		     
  g_message( "Parsing %s\n", glade_file );

doc = g2c_doc_new ( glade_file );

if (doc == NULL ) return 1;

if (program == NULL) {
    doc->project->program_name = g_strdup("g2cProgram");
  } else {
    doc->project->program_name = program;
  }
  
  doc->project->source_file = glade_file;
      
  doc->project->source_directory = gen_dir;
  
  doc->project->gen_cmake = gen_cmake;
  
  doc->project->no_parsing = no_parsing;
  
#ifdef WIN32  
  doc->project->resource_file = resource_file;
#endif  
  create_dir(gen_dir);
  
  g_assert ( NULL != doc );

  /* parse the Glade xml file */
  g2c_doc_parse( doc );  
  
  /* Write out to files */
  iret = g2c_doc_output( doc );
  
  /* Free the document */
  g2c_doc_destroy ( doc );  
  
  //g_log_remove_handler (NULL, handler_id);   /*  crashes  */
  
  return iret;
}

