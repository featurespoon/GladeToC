#include <stdio.h>
#include <gtk/gtk.h>
#include "g2c_message.h"

static GtkTextBuffer    *textbuffer;

void 
g2c_message_init(gpointer gui)
{
	textbuffer = (GtkTextBuffer*) gui;
    return;
}

void
g2c_message_handler(const gchar *log_domain,
		    GLogLevelFlags log_level,
		    const gchar *message,
		    gpointer user_data)
{
GtkTextIter iter;
    gtk_text_buffer_get_end_iter(textbuffer, &iter);
    gtk_text_buffer_insert(textbuffer, &iter, message, -1);  
    //g_print("%s", message);
}

