#include "g2c_accel.h"

/*******************************************************************
 **                 Accelerator Helper functions                  **
 *******************************************************************/

g2cAccel *
g2c_accel_new( void )
{
  g2cAccel *accel = g_new0( g2cAccel, 1 );

  accel->modifiers = NULL;
  accel->key       = NULL;
  accel->signal    = NULL;
  accel->focus_target = NULL;

  return accel;
}

void
g2c_accel_destroy( g2cAccel *accel )
{
  g_assert( NULL != accel );

  /* Free the strings */
  if( NULL != accel->modifiers ) g_free( accel->modifiers );
  if( NULL != accel->key )       g_free( accel->key );
  if( NULL != accel->signal )    g_free( accel->signal );
  if( NULL != accel->focus_target )    g_free( accel->focus_target );

  g_free( accel );
}

void
g2c_accel_set_modifiers( g2cAccel *accel, const gchar *modifiers )
{
  g_assert( NULL != accel );

  if( NULL != accel->modifiers ) g_free( accel->modifiers );
  accel->modifiers = g_strdup( modifiers );
}

void
g2c_accel_set_key( g2cAccel *accel, const gchar *key )
{
  g_assert( NULL != accel );

  if( NULL != accel->key ) g_free( accel->key );
  accel->key = g_strdup( key );
}

void
g2c_accel_set_signal( g2cAccel *accel, const gchar *signal )
{
  g_assert( NULL != accel );

  if( NULL != accel->signal ) g_free( accel->signal );
  accel->signal = g_strdup( signal );
  accel->signal = g_strdelimit(accel->signal, ":-", '_');
}

void
g2c_accel_set_focus_target( g2cAccel *accel, const gchar *focus_target )
{
  g_assert( NULL != accel );
  g_assert( NULL != focus_target );

  accel->focus_target = g_strdup( focus_target );
}

