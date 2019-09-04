#include <glib.h>

#ifdef WIN32
int g2c_common(gchar* program, gchar* glade_file, gchar* gen_dir, gchar* resource_file);
#else
int g2c_common(gchar* program, gchar* glade_file, gchar* gen_dir);
#endif


void 
g2c_message_init(gpointer gui);

void
g2c_message_handler(const gchar *log_domain,
		    GLogLevelFlags log_level,
		    const gchar *message,
		    gpointer user_data);
