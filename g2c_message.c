#include <stdio.h>
#include "g2c_message.h"

void 
g2c_message_init(gpointer gui)
{
   return;
}

void
g2c_message_handler(const gchar *log_domain,
		    GLogLevelFlags log_level,
		    const gchar *message,
		    gpointer user_data)
{
  g_print( "%s", message );
}

