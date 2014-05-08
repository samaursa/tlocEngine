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

  typedef core::data_structs::Tuple2size   Dimension2;
  typedef core::data_structs::Tuple2s      Dimension2i;
  typedef core::data_structs::Tuple2u      Dimension2u;
  typedef core::data_structs::Tuple2f      Dimension2f;

  typedef core::data_structs::Tuple2s32    Dimension2s32;
  typedef core::data_structs::Tuple2u32    Dimension2u32;
  typedef core::data_structs::Tuple2f32    Dimension2f32;

  typedef core::data_structs::Tuple2s64    Dimension2s64;
  typedef core::data_structs::Tuple2u64    Dimension2u64;
  typedef core::data_structs::Tuple2f64    Dimension2f64;

  typedef core::data_structs::Tuple3size   Dimension3;
  typedef core::data_structs::Tuple3s      Dimension3i;
  typedef core::data_structs::Tuple3u      Dimension3u;
  typedef core::data_structs::Tuple3f      Dimension3f;

  typedef core::data_structs::Tuple3s32    Dimension3s32;
  typedef core::data_structs::Tuple3u32    Dimension3u32;
  typedef core::data_structs::Tuple3f32    Dimension3f32;

  typedef core::data_structs::Tuple3s64    Dimension3s64;
  typedef core::data_structs::Tuple3u64    Dimension3u64;
  typedef core::data_structs::Tuple3f64    Dimension3f64;

};};};

#endif