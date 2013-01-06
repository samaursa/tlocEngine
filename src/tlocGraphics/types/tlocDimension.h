#ifndef TLOC_GRAPHICS_TYPES_DIMENSION_H
#define TLOC_GRAPHICS_TYPES_DIMENSION_H

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

  typedef core::Variadic2i    Dimension2i;
  typedef core::Variadic2u    Dimension2u;
  typedef core::Variadic2f    Dimension2f;

  typedef core::Variadic3i    Dimension3i;
  typedef core::Variadic3u    Dimension3u;
  typedef core::Variadic3f    Dimension3f;

};};};

#endif