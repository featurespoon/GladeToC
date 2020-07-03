#include "g2c_widget.h"
#include "g2c_project.h"
#include "g2c_helpers.h"
#include <string.h>


/* Helpers */

static void
g2c_project_free_children_cb( gpointer data,
               gpointer user_data )
{
g2cWidget *widget = NULL;

  if (NULL != data)
    {
      widget = (g2cWidget *) data;      
      g2c_widget_destroy( widget );
    }
  else
    g_message ("Memory deallocation failure in free_children\n");
}


/* Class functions */

g2cProject *
g2c_project_new( void )
{
  g2cProject *project = g_new0( g2cProject, 1 );

  allocs = 0;

  //project->properties = NULL;

  project->top_level_widgets    = NULL;
  project->dialogue_widgets     = NULL;
  project->main_widget          = NULL;
  project->name                 = NULL;
  project->program_name         = NULL;
  project->directory            = NULL;
  project->source_directory     = NULL;
  project->source_file          = NULL;
  project->pixmaps_directory    = NULL;
  project->gettext_support      = FALSE;
  project->output_main_file     = TRUE;
  project->output_support_files = TRUE;
  project->output_build_files   = TRUE;
  project->resource_file        = NULL;
  project->resource_list        = NULL;


  return project;
}

void
g2c_project_destroy( g2cProject *project )
{
 
  /* Free the top level widgets */
  g_list_foreach( project->top_level_widgets,
                  g2c_project_free_children_cb,
                  NULL );
  
  g_list_free( project->top_level_widgets );
  
  g_list_free( project->dialogue_widgets );
  
  g_list_free( project->resource_list );
  
  if( NULL != project->name              ) g_free( project->name );
  if( NULL != project->program_name      ) g_free( project->program_name );
  if( NULL != project->directory         ) g_free( project->directory );  
  if( NULL != project->source_directory  ) g_free( project->source_directory );
  if( NULL != project->source_file       ) g_free( project->source_file );
  if( NULL != project->pixmaps_directory ) g_free( project->pixmaps_directory );
  if( NULL != project->resource_file     ) g_free( project->resource_file );
 
  g_free( project );
  
  if (allocs != 0)
    g_message ("%d widgets were not freed\n", allocs);
}

void
g2c_project_set_property( g2cProject *project,
                          const gchar *name,
                          const gchar *value )
{
  if( strcmp( name, "gettext_support" ) == 0 )
    {
      project->gettext_support = g2c_get_bool( value );
    }
  else if( strcmp( name, "name" ) == 0 )
    {
      project->name = g_strdup( value );
    }
  else if( strcmp( name, "program_name" ) == 0 )
    {
      project->program_name = g_strdup( value );
    }
  else if( strcmp( name, "directory" ) == 0 )
    {
      project->directory = g_strdup( value );
    }
  else if( strcmp( name, "source_directory" ) == 0 )
    {
      project->source_directory = g_strdup( value );
    }
  else if( strcmp( name, "pixmaps_directory" ) == 0 )
    {
      project->pixmaps_directory = g_strdup( value );
    }
  else if( strcmp( name, "output_main_file" ) == 0 )
    {
      project->output_main_file = g2c_get_bool( value );
    }
  else if( strcmp( name, "output_support_files" ) == 0 )
    {
      project->output_support_files = g2c_get_bool( value );
    }
  else if( strcmp( name, "output_build_files" ) == 0 )
    {
      project->output_build_files = g2c_get_bool( value );
    }
}

void
g2c_project_add_top_level_widget( g2cProject *project,
                                  g2cWidget  *widget )
{
  g_assert( NULL != project );
  g_assert( NULL != widget );

  project->top_level_widgets = g_list_append( project->top_level_widgets,
                               widget );
}


