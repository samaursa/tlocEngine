#ifndef _TLOC_GRAPHICS_GL_ATTRIBUTE_H_
#define _TLOC_GRAPHICS_GL_ATTRIBUTE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>
#include <tlocMath/types/tlocMatrix2.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

#include <tlocGraphics/types/tlocVertex.h>
#include <tlocGraphics/opengl/tlocShaderVariable.h>

namespace tloc { namespace graphics { namespace gl {

  class Attribute
    : public ShaderVariable_TI<Attribute>
  {
  public:
    template <typename T_Derived> friend class ShaderVariable_TI;

    typedef Attribute                               this_type;
    typedef ShaderVariable_TI<this_type>            base_type;

  public:
    Attribute();
    Attribute(const this_type& a_other);

    this_type& operator=(this_type a_other);

    void swap(this_type& a_other);

    template <typename T>
    derived_type& SetValueAs(const T& a_value);

    template <typename T, typename T_Technique>
    derived_type& SetValueAs(core_conts::Array<T>& a_array, T_Technique);

    template <typename T, typename T_Technique>
    derived_type& SetVertexArray(core_conts::Array<T>& a_array, T_Technique);

    template <typename T>
    derived_type& SetVertexArray 
      (core_sptr::VirtualPtr<core_conts::Array<T> > a_array, 
       p_shader_variable_ti::Pointer);

    void Reset();

    TLOC_DECL_AND_DEF_GETTER(bool, IsAttribArray, m_isAttribArray);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetSecondName, m_name2);
    TLOC_DECL_AND_DEF_SETTER_CHAIN(string_type, SetSecondName, m_name2);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetThirdName, m_name3);
    TLOC_DECL_AND_DEF_SETTER_CHAIN(string_type, SetThirdName, m_name3);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetFourthName, m_name4);
    TLOC_DECL_AND_DEF_SETTER_CHAIN(string_type, SetFourthName, m_name4);

    using base_type::GetName;
    const string_type& GetName(tl_int a_nameIndex) const;

  protected:
    template <typename T>
    void DoCheckTypeCompatibility() const;

    template <typename T>
    void DoCheckNonArrayTypes() const;

    template <typename T>
    void DoCheckVertexArrayTypes() const;

    template <typename T>
    void DoCheckArrayTypes() const;

  private:
    bool          m_isAttribArray;
    string_type   m_name2;
    string_type   m_name3;
    string_type   m_name4;

  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T>
  Attribute::derived_type& 
    Attribute::
    SetValueAs(const T& a_value)
  { return base_type::SetValueAs(a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, typename T_Technique>
  Attribute::derived_type& 
    Attribute::
    SetValueAs(core::containers::Array<T>& a_array, T_Technique)
  {
    // Constant = GLSL's view of a constant attribute
    TLOC_STATIC_ASSERT((Loki::IsSameType<T, DummyStruct>::value),
      Constant_attribute_arrays_are_illegal_use_SetVertexArray_instead);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, typename T_Technique>
  Attribute::derived_type&
    Attribute::
    SetVertexArray(core::containers::Array<T>& a_array, T_Technique)
  {
    m_isAttribArray = true;
    return base_type::SetValueAs(a_array, T_Technique());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  Attribute::derived_type&
    Attribute::
    SetVertexArray(core_sptr::VirtualPtr<core_conts::Array<T> > a_array, 
                   p_shader_variable_ti::Pointer)
  {
    m_isAttribArray = true;
    return base_type::SetValueAs(a_array, p_shader_variable_ti::Pointer());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  void 
    Attribute::
    DoCheckTypeCompatibility() const
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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  void 
    Attribute::
    DoCheckNonArrayTypes() const
  {
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
       Tuple2u32, Tuple3u32, Tuple4u32
      >();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  void 
    Attribute::
    DoCheckVertexArrayTypes() const
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  void 
    Attribute::
    DoCheckArrayTypes() const
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

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Attribute, attribute);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Attribute, attribute);

  typedef core_conts::Array<attribute_sptr>         attribute_sptr_cont;

};};};

#endif