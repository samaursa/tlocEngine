#ifndef TLOC_INPUT_TYPES_H
#define TLOC_INPUT_TYPES_H

namespace tloc { namespace input {

  namespace hid
  {
    enum Type
    {
      keyboard = 0,
      mouse,
      joystick,

      total_input_types
    };
  }

  namespace parameter_options
  {
    enum Type
    {
      TL_DEFAULT = 0,

      // Useful only for windows
      TL_WIN_DISCL_BACKGROUND   = 1 << 0,
      TL_WIN_DISCL_EXCLUSIVE    = 1 << 1,
      TL_WIN_DISCL_FOREGROUND   = 1 << 2,
      TL_WIN_DISCL_NONEXCLUSIVE = 1 << 3,
      TL_WIN_DISCL_NOWINKEY     = 1 << 4,
    };
  }

};};

#endif