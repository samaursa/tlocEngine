#ifndef _TLOC_GRAPHICS_GL_UNIFORM_H_
#define _TLOC_GRAPHICS_GL_UNIFORM_H_

#include <tlocCore/smart_ptr/tlocSharedPtr.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>
#include <tlocMath/types/tlocMatrix2.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

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
      using namespace core;
      using namespace math;

      type_traits::AssertTypeIsSupported
        <T,
         f32,
         Vec2f32, Vec3f32, Vec4f32,
         s32,
         Tuple2s32, Tuple3s32, Tuple4s32,
         u32,
         Tuple2u32, Tuple3u32, Tuple4u32,
         Mat2f32, Mat3f32, Mat4f32,
         Array<f32>,
         Array<Vec2f32>,
         Array<Vec3f32>,
         Array<Vec4f32>,
         Array<s32>,
         Array<Tuple2s32>,
         Array<Tuple3s32>,
         Array<Tuple4s32>,
         Array<u32>,
         Array<Tuple2u32>,
         Array<Tuple3u32>,
         Array<Tuple4u32>
        >();
    }

    template <typename T>
    void DoCheckNonArrayTypes() const
    {
      using namespace core;
      using namespace math::types;

      type_traits::AssertTypeIsSupported
        <T,
         f32,
         Vec2f32, Vec3f32, Vec4f32,
         s32,
         Tuple2s32, Tuple3s32, Tuple4s32,
         u32,
         Tuple2u32, Tuple3u32, Tuple4u32,
         Mat2f32, Mat3f32, Mat4f32
        >();
    }

    template <typename T>
    void DoCheckArrayTypes() const
    {
      using namespace core;
      using namespace core::containers;
      using namespace math::types;

      type_traits::AssertTypeIsSupported
        <Array<T>,
         Array<f32>,
         Array<Vec2f32>,
         Array<Vec3f32>,
         Array<Vec4f32>,
         Array<s32>,
         Array<Tuple2s32>,
         Array<Tuple3s32>,
         Array<Tuple4s32>,
         Array<u32>,
         Array<Tuple2u32>,
         Array<Tuple3u32>,
         Array<Tuple4u32>,
         Array<Mat2f32>,
         Array<Mat3f32>,
         Array<Mat4f32>
        >();
    }

  };

  //------------------------------------------------------------------------
  // typedefs

  typedef tloc::core::smart_ptr::SharedPtr<Uniform>   UniformPtr;

};};};

#endif