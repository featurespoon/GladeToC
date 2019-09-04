#ifndef G2C_ACCEL_H
#define G2C_ACCEL_H

#include <glib.h>

typedef struct tag_g2cAccel
  {
    gchar *modifiers;
    gchar *key;
    gchar *signal;
    gchar *focus_target;
  }
g2cAccel;

g2cAccel *g2c_accel_new( void );
void      g2c_accel_destroy( g2cAccel *accel );
void      g2c_accel_set_modifiers( g2cAccel *accel, const gchar *modifiers );
void      g2c_accel_set_key( g2cAccel *accel, const gchar *key );
void      g2c_accel_set_signal( g2cAccel *accel, const gchar *signal );
void      g2c_accel_set_focus_target( g2cAccel *accel, const gchar *focus_target );

#endif




