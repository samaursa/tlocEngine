#ifndef _TLOC_GRAPHICS_GL_ATTRIBUTE_H_
#define _TLOC_GRAPHICS_GL_ATTRIBUTE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>
#include <tlocMath/types/tlocMatrix2.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

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
    derived_type& SetValueAs(core::containers::Array<T>& a_array,
                             T_Technique)
    {
      TLOC_STATIC_ASSERT(false,
        Constant_attribute_arrays_are_illegal_use_SetVertexArray_instead);
    }

    template <typename T, typename T_Technique>
    derived_type& SetVertexArray(core::containers::Array<T>& a_array,
                                 T_Technique)
    {
      m_isAttribArray = true;
      return base_type::SetValueAs(a_array, T_Technique());
    }

    TLOC_DECL_AND_DEF_GETTER(bool, IsAttribArray, m_isAttribArray);

  protected:
    template <typename T>
    void DoCheckTypeCompatibility() const
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
      using namespace core::data_structs;
      using namespace math::types;

      type_traits::AssertTypeIsSupported
        <T,
         f32,
         Vec2f32, Vec3f32, Vec4f32,
         s32,
         Tuple2s32, Tuple3s32, Tuple4s32,
         u32,
         Tuple2u32, Tuple3u32, Tuple4u32
        >();
    }

    template <typename T>
    void DoCheckVertexArrayTypes() const
    {
    }

    template <typename T>
    void DoCheckArrayTypes() const
    {
      using namespace core::data_structs;
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
         Array<Tuple4u32>
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