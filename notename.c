/*
 * notename - Pd external: MIDI note number (0-127) to English note + octave label.
 * White keys: "C-3", black keys: "C#3" (sharp, no hyphen before octave).
 */

#include "m_pd.h"

#include <stdio.h>

static t_class *notename_class;

typedef struct _notename {
  t_object x_obj;
  t_outlet *x_out;
  t_float x_last;
} t_notename;

static void notename_format(int n, char *buf, size_t buflen)
{
  int pc;
  int oct;

  if (n < 0) {
    n = 0;
  }
  if (n > 127) {
    n = 127;
  }
  pc = n % 12;
  oct = n / 12 - 1;

  switch (pc) {
    case 0:
      snprintf(buf, buflen, "C-%d", oct);
      break;
    case 1:
      snprintf(buf, buflen, "C#%d", oct);
      break;
    case 2:
      snprintf(buf, buflen, "D-%d", oct);
      break;
    case 3:
      snprintf(buf, buflen, "D#%d", oct);
      break;
    case 4:
      snprintf(buf, buflen, "E-%d", oct);
      break;
    case 5:
      snprintf(buf, buflen, "F-%d", oct);
      break;
    case 6:
      snprintf(buf, buflen, "F#%d", oct);
      break;
    case 7:
      snprintf(buf, buflen, "G-%d", oct);
      break;
    case 8:
      snprintf(buf, buflen, "G#%d", oct);
      break;
    case 9:
      snprintf(buf, buflen, "A-%d", oct);
      break;
    case 10:
      snprintf(buf, buflen, "A#%d", oct);
      break;
    default:
      snprintf(buf, buflen, "B-%d", oct);
      break;
  }
}

static void notename_output(t_notename *x, t_float f)
{
  char buf[32];

  x->x_last = f;
  notename_format((int)f, buf, sizeof(buf));
  outlet_symbol(x->x_out, gensym(buf));
}

static void notename_float(t_notename *x, t_floatarg f)
{
  notename_output(x, (t_float)f);
}

static void notename_bang(t_notename *x)
{
  notename_output(x, x->x_last);
}

static void *notename_new(t_symbol *s, int argc, t_atom *argv)
{
  t_notename *x = (t_notename *)pd_new(notename_class);
  t_float init = 0;

  (void)s;
  if (argc > 0) {
    init = atom_getfloat(argv);
  }
  x->x_last = init;
  x->x_out = outlet_new(&x->x_obj, &s_symbol);
  return (void *)x;
}

void notename_setup(void)
{
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-function-type-mismatch"
#endif
  notename_class = class_new(
      gensym("notename"),
      (t_newmethod)notename_new,
      0,
      sizeof(t_notename),
      CLASS_DEFAULT,
      A_GIMME,
      0);
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
  class_addfloat(notename_class, (t_method)notename_float);
  class_addbang(notename_class, (t_method)notename_bang);
}
