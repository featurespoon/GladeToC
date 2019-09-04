#include "g2c_signal.h"
#include "g2c_helpers.h"

#include "config.h"

g2cSignal *
g2c_signal_new( void )
{
  g2cSignal *signal = g_new0( g2cSignal, 1 );

  signal->name      = NULL;
  signal->handler   = NULL;
  signal->object    = NULL;
  signal->data      = NULL;
  signal->after     = FALSE;
  signal->timestamp = NULL;

  return signal;
}

void
g2c_signal_destroy( g2cSignal *signal )
{
  /* Free the strings */
  if( signal->name )      g_free( signal->name );
  if( signal->handler )   g_free( signal->handler );
  if( signal->object )    g_free( signal->object );
  if( signal->data )      g_free( signal->data );
  if( signal->timestamp ) g_free( signal->timestamp );

  g_free( signal );
}

void
g2c_signal_set_name( g2cSignal **signal, const gchar *name )
{
  if( NULL != (*signal)->name ) g_free( (*signal)->name );
  (*signal)->name = g_strdup( name );
}

void
g2c_signal_set_handler( g2cSignal **signal, const gchar *handler )
{
  if( NULL != (*signal)->handler ) g_free( (*signal)->handler );
  (*signal)->handler = g_strdelimit(g_strdup( handler ),"-",'_');
}

void
g2c_signal_set_object( g2cSignal **signal, const gchar *object )
{
  if( NULL != (*signal)->object ) g_free( (*signal)->object );
  (*signal)->object = g_strdup( object );
}

void
g2c_signal_set_data( g2cSignal **signal, const gchar *data )
{
  if( NULL != (*signal)->data ) g_free( (*signal)->data );
  (*signal)->data = g_strdup( data );
}

void
g2c_signal_set_after( g2cSignal **signal, const gchar *after )
{
  (*signal)->after = g2c_get_bool( after );
}

void
g2c_signal_set_timestamp( g2cSignal **signal, const gchar *date )
{
  if( NULL != (*signal)->timestamp ) g_free( (*signal)->timestamp );
  (*signal)->timestamp = g_strdup( date );
}

void       
g2c_signal_set_swapped( g2cSignal **signal, const gchar * swapped )
{
    (*signal)->swapped = (strcasecmp(swapped, "no") == 0) ? FALSE : TRUE;
}

