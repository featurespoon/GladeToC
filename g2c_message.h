#include <glib.h>

#ifdef WIN32
int g2c_common(gchar* program, 
        gchar* glade_file, 
        gchar* gen_dir, 
        gboolean gen_cmake, 
        gboolean no_parsing, 
        gchar* resource_file);
#else
int g2c_common(gchar* program, 
        gchar* glade_file, 
        gchar* gen_dir, 
        gboolean gen_cmake, 
        gboolean no_parsing);
#endif


void 
g2c_message_init(gpointer gui);

void
g2c_message_handler(const gchar *log_domain,
		    GLogLevelFlags log_level,
		    const gchar *message,
		    gpointer user_data);
