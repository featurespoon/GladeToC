#ifndef G2C_SIGNAL_H
#define G2C_SIGNAL_H

#include <glib.h>

typedef struct tag_g2cSignal
  {
    gchar    *name;
    gchar    *handler;
    gchar    *object;
    gchar    *data;
    gboolean after;
    gboolean swapped;
    gchar    *timestamp;
  }
g2cSignal;

g2cSignal *g2c_signal_new( void );
void       g2c_signal_destroy( g2cSignal *signal );
void       g2c_signal_set_name( g2cSignal **signal, const gchar *name );
void       g2c_signal_set_handler( g2cSignal **signal, const gchar *handler );
void       g2c_signal_set_object( g2cSignal **signal, const gchar *object );
void       g2c_signal_set_data( g2cSignal **signal, const gchar *data );
void       g2c_signal_set_after( g2cSignal **signal, const gchar * after );
void       g2c_signal_set_timestamp( g2cSignal **signal, const gchar *date );
void       g2c_signal_set_swapped( g2cSignal **signal, const gchar * swapped );

#endif
