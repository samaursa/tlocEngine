#ifndef _TLOC_GRAPHICS_GL_UNIFORM_H_
#define _TLOC_GRAPHICS_GL_UNIFORM_H_

#include <tlocMath/vector/tlocVector2.h>
#include <tlocMath/vector/tlocVector3.h>
#include <tlocMath/vector/tlocVector4.h>
#include <tlocMath/matrix/tlocMatrix2.h>
#include <tlocMath/matrix/tlocMatrix3.h>
#include <tlocMath/matrix/tlocMatrix4.h>

#include <tlocGraphics/opengl/tlocShaderVariable.h>

namespace tloc { namespace graphics { namespace gl {

  class Uniform : public ShaderVariable_TI<Uniform>
  {
  public:
    template <typename T_Derived> friend class ShaderVariable_TI;

    typedef Uniform                         this_type;
    typedef ShaderVariable_TI<this_type>    base_type;

  protected:
    template <typename T>
    void DoCheckTypeCompatibility() const
    {
      type_traits::AssertTypeIsSupported
        <T,
         f32,
         math::Vec2f32,
         math::Vec3f32,
         math::Vec4f32,
         s32,
         core::Tuple2s32,
         core::Tuple3s32,
         core::Tuple4s32,
         math::Mat2f32,
         math::Mat3f32,
         math::Mat4f32,

         core::Array<f32>,
         core::Array<math::Vec2f32>,
         core::Array<math::Vec3f32>,
         core::Array<math::Vec4f32>,
         core::Array<s32>,
         core::Array<core::Tuple2s32>,
         core::Array<core::Tuple3s32>,
         core::Array<core::Tuple4s32>
        >();
    }

    template <typename T>
    void DoCheckNonArrayTypes() const
    {
      type_traits::AssertTypeIsSupported
        <T,
         f32,
         math::Vec2f32,
         math::Vec3f32,
         math::Vec4f32,
         s32,
         core::Tuple2s32,
         core::Tuple3s32,
         core::Tuple4s32,
         math::Mat2f32,
         math::Mat3f32,
         math::Mat4f32
        >();
    }

    template <typename T>
    void DoCheckArrayTypes() const
    {
      type_traits::AssertTypeIsSupported
        <core::Array<T>,
         core::Array<f32>,
         core::Array<math::Vec2f32>,
         core::Array<math::Vec3f32>,
         core::Array<math::Vec4f32>,
         core::Array<s32>,
         core::Array<core::Tuple2s32>,
         core::Array<core::Tuple3s32>,
         core::Array<core::Tuple4s32>
        >();
    }

  };

};};};

#endif