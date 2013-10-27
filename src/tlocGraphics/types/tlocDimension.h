#ifndef TLOC_GRAPHICS_TYPES_DIMENSION_H
#define TLOC_GRAPHICS_TYPES_DIMENSION_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/data_structures/tlocVariadic.h>

namespace tloc { namespace graphics { namespace types {

  // Dimensions are always width, height, depth

  namespace dimension
  {
    enum
    {
      width = 0,
      height,
      depth
    };
  };

  typedef core::data_structs::Variadic2s    Dimension2i;
  typedef core::data_structs::Variadic2u    Dimension2u;
  typedef core::data_structs::Variadic2f    Dimension2f;

  typedef core::data_structs::Variadic2s32  Dimension2s32;
  typedef core::data_structs::Variadic2u32  Dimension2u32;
  typedef core::data_structs::Variadic2f32  Dimension2f32;

  typedef core::data_structs::Variadic2s64  Dimension2s64;
  typedef core::data_structs::Variadic2u64  Dimension2u64;
  typedef core::data_structs::Variadic2f64  Dimension2f64;

  typedef core::data_structs::Variadic3s    Dimension3i;
  typedef core::data_structs::Variadic3u    Dimension3u;
  typedef core::data_structs::Variadic3f    Dimension3f;

  typedef core::data_structs::Variadic3s32  Dimension3s32;
  typedef core::data_structs::Variadic3u32  Dimension3u32;
  typedef core::data_structs::Variadic3f32  Dimension3f32;

  typedef core::data_structs::Variadic3s64  Dimension3s64;
  typedef core::data_structs::Variadic3u64  Dimension3u64;
  typedef core::data_structs::Variadic3f64  Dimension3f64;

};};};

#endif