#ifndef TLOC_OPENGL_TYPES_H
#define TLOC_OPENGL_TYPES_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocTypes.h>

namespace tloc { namespace graphics { namespace types {

  typedef s32                     gl_int;
  typedef u32                     gl_uint;
  typedef u32                     gl_enum;
  typedef s32                     gl_sizei;
  typedef f32                     gl_float;
  typedef f64                     gl_double;
  typedef gl_uint                 gl_handle;

  // -----------------------------------------------------------------------
  
  namespace type_to_gl {

    template <typename T>
    gl_enum Get();

  };

};};};

#endif