#ifndef _TLOC_GRAPHICS_GL_ATTRIBUTE_H_
#define _TLOC_GRAPHICS_GL_ATTRIBUTE_H_

#include <tlocCore/smart_ptr/tlocSmartPtr.h>

#include <tlocMath/vector/tlocVector2.h>
#include <tlocMath/vector/tlocVector3.h>
#include <tlocMath/vector/tlocVector4.h>
#include <tlocMath/matrix/tlocMatrix2.h>
#include <tlocMath/matrix/tlocMatrix3.h>
#include <tlocMath/matrix/tlocMatrix4.h>

#include <tlocGraphics/opengl/tlocShaderVariable.h>

namespace tloc { namespace graphics { namespace gl {

  class Attribute : public ShaderVariable_TI<Attribute>
  {
  public:
    template <typename T_Derived> friend class ShaderVariable_TI;

    typedef Attribute                     this_type;
    typedef ShaderVariable_TI<this_type>  base_type;

  public:
    Attribute() : m_isAttribArray(false)
    { }

    template <typename T>
    derived_type& SetValueAs(const T& a_value)
    {
      return base_type::SetValueAs(a_value);
    }

    template <typename T, typename T_Technique>
    derived_type& SetValueAs(core::Array<T>& a_array, T_Technique)
    {
      TLOC_STATIC_ASSERT(false,
        Constant_attribute_arrays_are_illegal_use_SetVertexArray_instead);
    }

    template <typename T, typename T_Technique>
    derived_type& SetVertexArray(core::Array<T>& a_array, T_Technique)
    {
      m_isAttribArray = true;
      return base_type::SetValueAs(a_array, T_Technique());
    }

    TLOC_DECL_AND_DEF_GETTER(bool, IsAttribArray, m_isAttribArray);

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
         math::Vec2s32,
         math::Vec3s32,
         math::Vec4s32,
         u32,
         math::Vec2u32,
         math::Vec3u32,
         math::Vec4u32,
         core::Array<f32>,
         core::Array<math::Vec2f32>,
         core::Array<math::Vec3f32>,
         core::Array<math::Vec4f32>,
         core::Array<s32>,
         core::Array<math::Vec2s32>,
         core::Array<math::Vec3s32>,
         core::Array<math::Vec4s32>,
         core::Array<u32>,
         core::Array<math::Vec2u32>,
         core::Array<math::Vec3u32>,
         core::Array<math::Vec4u32>
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
         math::Vec2s32,
         math::Vec3s32,
         math::Vec4s32,
         u32,
         math::Vec2u32,
         math::Vec3u32,
         math::Vec4u32
        >();
    }

    template <typename T>
    void DoCheckVertexArrayTypes() const
    {
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
         core::Array<math::Vec2s32>,
         core::Array<math::Vec3s32>,
         core::Array<math::Vec4s32>,
         core::Array<u32>,
         core::Array<math::Vec2u32>,
         core::Array<math::Vec3u32>,
         core::Array<math::Vec4u32>
        >();
    }

  private:
    bool    m_isAttribArray;

  };

  //------------------------------------------------------------------------
  // typedefs

  typedef tloc::core::smart_ptr::SharedPtr<Attribute>   AttributePtr;

};};};

#endif