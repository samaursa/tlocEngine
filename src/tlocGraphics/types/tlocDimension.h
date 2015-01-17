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

  namespace f_dimension {

    template <typename T, typename T2>
    core_ds::Tuple<T, 2>
      ModifyAndKeepRatioX(const core_ds::Tuple<T, 2>& a_dim,
                          T2 a_newX)
    {
      const auto newXDim  = core_utils::CastNumber<tl_float>(a_newX);
      const auto oldXDim  = core_utils::CastNumber<tl_float>(a_dim[0]);
      const auto ratio    = newXDim / oldXDim;
      const auto newYDim  = core_utils::CastNumber<T>(a_dim[1] * ratio);

      return core_ds::MakeTuple(core_utils::CastNumber<T>(a_newX), newYDim);
    }

    template <typename T, typename T2>
    core_ds::Tuple<T, 2>
      ModifyAndKeepRatioY(const core_ds::Tuple<T, 2>& a_dim,
                          T2 a_newY)
    {
      const auto newYDim  = core_utils::CastNumber<tl_float>(a_newY);
      const auto oldYDim  = core_utils::CastNumber<tl_float>(a_dim[1]);
      const auto ratio    = newYDim / oldYDim;
      const auto newXDim  = core_utils::CastNumber<T>(a_dim[0] * ratio);

      return core_ds::MakeTuple(newXDim, core_utils::CastNumber<T>(a_newY));
    }

  };

};};};

#endif