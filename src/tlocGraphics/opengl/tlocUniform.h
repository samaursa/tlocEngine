#ifndef _TLOC_GRAPHICS_GL_UNIFORM_H_
#define _TLOC_GRAPHICS_GL_UNIFORM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/containers/tlocArray.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>
#include <tlocMath/types/tlocMatrix2.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

#include <tlocGraphics/opengl/tlocShaderVariable.h>
#include <tlocGraphics/opengl/tlocTextureObject.h>
#include <tlocGraphics/types/tlocVertex.h>

namespace tloc { namespace graphics { namespace gl {

  class Uniform
    : public ShaderVariable_TI<Uniform>
  {
  public:
    template <typename T_Derived> friend class ShaderVariable_TI;

    typedef Uniform                         this_type;
    typedef ShaderVariable_TI<this_type>    base_type;

  public:
    Uniform();
    Uniform(const this_type& a_other);

    this_type& operator=(this_type a_other);

    void swap(this_type& a_other);

  protected:
    template <typename T>
    void DoCheckTypeCompatibility() const
    {
      using namespace core::containers;
      using namespace core::data_structs;
      using namespace math::types;
      using namespace graphics::types;

      tloc::type_traits::AssertTypeIsSupported
        <T,
         f32,
         Vec2f32, Vec3f32, Vec4f32,
         s32,
         Tuple2s32, Tuple3s32, Tuple4s32,
         u32,
         Tuple2u32, Tuple3u32, Tuple4u32,
         Mat2f32, Mat3f32, Mat4f32,
         TextureObject,
         TextureObjectShadow,
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
         Array<Vert2fp>,
         Array<Vert2fpn>,
         Array<Vert2fpc>,
         Array<Vert2fpt>,
         Array<Vert2fpnc>,
         Array<Vert2fpnt>,
         Array<Vert2fpnct>,
         Array<Vert3fp>,
         Array<Vert3fpn>,
         Array<Vert3fpc>,
         Array<Vert3fpt>,
         Array<Vert3fpnc>,
         Array<Vert3fpnt>,
         Array<Vert3fpnct>
        >();
    }

    template <typename T>
    void DoCheckNonArrayTypes() const
    {
      using namespace core::data_structs;
      using namespace math::types;
      using namespace graphics::types;

      type_traits::AssertTypeIsSupported
        <T,
         f32,
         Vec2f32, Vec3f32, Vec4f32,
         s32,
         Tuple2s32, Tuple3s32, Tuple4s32,
         u32,
         Tuple2u32, Tuple3u32, Tuple4u32,
         Mat2f32, Mat3f32, Mat4f32,
         TextureObject,
         TextureObjectShadow
        >();
    }

    template <typename T>
    void DoCheckArrayTypes() const
    {
      using namespace core::data_structs;
      using namespace core::containers;
      using namespace math::types;
      using namespace graphics::types;

      tloc::type_traits::AssertTypeIsSupported
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

  TLOC_TYPEDEF_ALL_SMART_PTRS(Uniform, uniform);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Uniform, uniform);

  typedef core_conts::Array<uniform_sptr>         uniform_sptr_cont;

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_gl::Uniform);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_gl::Uniform);

TLOC_EXTERN_TEMPLATE_ARRAY(tloc::gfx_gl::uniform_sptr);

#endif