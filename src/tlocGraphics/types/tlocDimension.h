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

  typedef core::data_structs::Variadic2i    Dimension2i;
  typedef core::data_structs::Variadic2u    Dimension2u;
  typedef core::data_structs::Variadic2f    Dimension2f;

  typedef core::data_structs::Variadic3i    Dimension3i;
  typedef core::data_structs::Variadic3u    Dimension3u;
  typedef core::data_structs::Variadic3f    Dimension3f;

};};};

#endif