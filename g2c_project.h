#ifndef G2C_PROJECT_H
#define G2C_PROJECT_H

#include <glib.h>



g2cProject *CURRENT_PROJECT;

g2cProject *
g2c_project_new( void );

void
g2c_project_destroy( g2cProject *project );

void
g2c_project_set_property( g2cProject *project,
                          const gchar *name,
                          const gchar *value );

//const gchar *
//g2c_project_get_property( g2cProject *project,
//                          const gchar *name );

void
g2c_project_add_top_level_widget( g2cProject *project,
                                  g2cWidget  *widget );


#endif

