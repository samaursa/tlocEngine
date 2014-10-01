#include "tlocShaderVariable.h"

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocUniform.h>
#include <tlocGraphics/opengl/tlocAttribute.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>
#include <tlocMath/types/tlocMatrix2.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

namespace tloc { namespace graphics { namespace gl {

  using namespace core::data_structs;
  using namespace core::containers;
  using namespace core::smart_ptr;
  using namespace math::types;

  //------------------------------------------------------------------------
  // Supported types

  template <typename T> struct tlToGl;

#define TLOC_DECL_TL_TO_GL(_type_, _glType_)\
  template <> struct tlToGl< _type_ >\
  { enum { k_glType = _glType_ }; }

  TLOC_DECL_TL_TO_GL(s8, GL_BYTE);
  TLOC_DECL_TL_TO_GL(u8, GL_UNSIGNED_BYTE);

  TLOC_DECL_TL_TO_GL(short, GL_SHORT);
  TLOC_DECL_TL_TO_GL(ushort, GL_UNSIGNED_SHORT);

  TLOC_DECL_TL_TO_GL(f32, GL_FLOAT);

  TLOC_DECL_TL_TO_GL(Vec2f32, GL_FLOAT_VEC2);
  TLOC_DECL_TL_TO_GL(Vec3f32, GL_FLOAT_VEC3);
  TLOC_DECL_TL_TO_GL(Vec4f32, GL_FLOAT_VEC4);

  TLOC_DECL_TL_TO_GL(s32, GL_INT);

  TLOC_DECL_TL_TO_GL(Tuple2s32, GL_INT_VEC2);
  TLOC_DECL_TL_TO_GL(Tuple3s32, GL_INT_VEC3);
  TLOC_DECL_TL_TO_GL(Tuple4s32, GL_INT_VEC4);

  TLOC_DECL_TL_TO_GL(u32, GL_UNSIGNED_INT);

  TLOC_DECL_TL_TO_GL(bool, GL_BOOL);

  TLOC_DECL_TL_TO_GL(Tuple2b, GL_BOOL_VEC2);
  TLOC_DECL_TL_TO_GL(Tuple3b, GL_BOOL_VEC3);
  TLOC_DECL_TL_TO_GL(Tuple4b, GL_BOOL_VEC4);

  TLOC_DECL_TL_TO_GL(Mat2f32, GL_FLOAT_MAT2);
  TLOC_DECL_TL_TO_GL(Mat3f32, GL_FLOAT_MAT3);
  TLOC_DECL_TL_TO_GL(Mat4f32, GL_FLOAT_MAT4);

  TLOC_DECL_TL_TO_GL(Array<s8>,     GL_BYTE);
  TLOC_DECL_TL_TO_GL(Array<u8>,     GL_UNSIGNED_BYTE);
  TLOC_DECL_TL_TO_GL(Array<short>,  GL_SHORT);
  TLOC_DECL_TL_TO_GL(Array<ushort>, GL_UNSIGNED_SHORT);

  TLOC_DECL_TL_TO_GL(Array<f32>,     GL_FLOAT);
  TLOC_DECL_TL_TO_GL(Array<Vec2f32>, GL_FLOAT_VEC2);
  TLOC_DECL_TL_TO_GL(Array<Vec3f32>, GL_FLOAT_VEC3);
  TLOC_DECL_TL_TO_GL(Array<Vec4f32>, GL_FLOAT_VEC4);

  TLOC_DECL_TL_TO_GL(Array<s32>,       GL_INT);
  TLOC_DECL_TL_TO_GL(Array<Tuple2s32>, GL_INT_VEC2);
  TLOC_DECL_TL_TO_GL(Array<Tuple3s32>, GL_INT_VEC3);
  TLOC_DECL_TL_TO_GL(Array<Tuple4s32>, GL_INT_VEC4);

  TLOC_DECL_TL_TO_GL(Array<u32>,       GL_UNSIGNED_INT);

  TLOC_DECL_TL_TO_GL(Array<bool>,    GL_BOOL);
  TLOC_DECL_TL_TO_GL(Array<Tuple2b>, GL_BOOL_VEC2);
  TLOC_DECL_TL_TO_GL(Array<Tuple3b>, GL_BOOL_VEC3);
  TLOC_DECL_TL_TO_GL(Array<Tuple4b>, GL_BOOL_VEC4);

  TLOC_DECL_TL_TO_GL(TextureObject, GL_SAMPLER_2D);
  TLOC_DECL_TL_TO_GL(TextureObjectShadow, GL_SAMPLER_2D_SHADOW);

#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL
  TLOC_DECL_TL_TO_GL(Tuple2u32, GL_UNSIGNED_INT_VEC2);
  TLOC_DECL_TL_TO_GL(Tuple3u32, GL_UNSIGNED_INT_VEC3);
  TLOC_DECL_TL_TO_GL(Tuple4u32, GL_UNSIGNED_INT_VEC4);

  TLOC_DECL_TL_TO_GL(Array<Tuple2u32>, GL_UNSIGNED_INT_VEC2);
  TLOC_DECL_TL_TO_GL(Array<Tuple3u32>, GL_UNSIGNED_INT_VEC3);
  TLOC_DECL_TL_TO_GL(Array<Tuple4u32>, GL_UNSIGNED_INT_VEC4);
#endif

#undef TLOC_DECL_TL_TO_GL

  // ///////////////////////////////////////////////////////////////////////
  // ShaderVariableBase

  ShaderVariableBase::
    ShaderVariableBase()
    : m_type(GL_NONE)
    , m_enabled(true)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ShaderVariableBase::
    swap(this_type& a_other)
  {
    using core::swap;

    swap(m_type, a_other.m_type);
    swap(m_value, a_other.m_value);
    swap(m_name, a_other.m_name);
    swap(m_enabled, a_other.m_enabled);
  }

  // ///////////////////////////////////////////////////////////////////////
  // ShaderVariable

#define SHADER_VARIABLE_TEMP    typename T_Derived
#define SHADER_VARIABLE_PARAMS  T_Derived
#define SHADER_VARIABLE_TYPE    typename ShaderVariable_TI<SHADER_VARIABLE_PARAMS>

  template <SHADER_VARIABLE_TEMP>
  ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::ShaderVariable_TI()
    : base_type()
    , m_isArray(false)
    , m_isArrayPtr(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SHADER_VARIABLE_TEMP>
  ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::
    ShaderVariable_TI(const this_type& a_other)
    : base_type(a_other)
    , m_isArray(a_other.m_isArray)
    , m_isArrayPtr(a_other.m_isArrayPtr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SHADER_VARIABLE_TEMP>
  ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::~ShaderVariable_TI()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SHADER_VARIABLE_TEMP>
  void
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::
    swap(this_type& a_other)
  {
    using core::swap;

    base_type::swap(a_other);
    swap(m_isArray, a_other.m_isArray);
    swap(m_isArrayPtr, a_other.m_isArrayPtr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SHADER_VARIABLE_TEMP>
  template <typename T>
  SHADER_VARIABLE_TYPE::derived_type&
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::DoSetValueAs(const T& a_value)
  {
    TLOC_ASSERT(DoGetValueRef().IsEmpty() || DoGetValueRef().IsSameType(a_value),
      "Cannot change uniform TYPE after construction");
    DoSetType(tlToGl<T>::k_glType);
    DoGetValueRef().Assign(a_value);
    return *(static_cast<derived_type*>(this));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SHADER_VARIABLE_TEMP>
  template <typename T>
  SHADER_VARIABLE_TYPE::derived_type&
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::
    DoSetValueAs(VirtualPtr<T> a_value)
  {
    TLOC_ASSERT(DoGetValueRef().IsEmpty() || DoGetValueRef().IsSameType(a_value),
      "Cannot change uniform TYPE after construction");
    DoSetType(tlToGl<T>::k_glType);
    DoGetValueRef().Assign(a_value);
    m_isArrayPtr = true;
    return *(static_cast<derived_type*>(this));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SHADER_VARIABLE_TEMP>
  template <typename T>
  SHADER_VARIABLE_TYPE::derived_type&
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::
    DoSetValueAs(const Array<T>& a_array, copy_array_policy)
  {
    TLOC_ASSERT(DoGetValueRef().IsEmpty() || DoGetValueRef().IsSameType(a_array),
      "Cannot change uniform TYPE after construction");
    DoSetType(tlToGl<T>::k_glType);
    m_isArray = true;
    DoGetValueRef().Assign(a_array);
    return *(static_cast<derived_type*>(this));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SHADER_VARIABLE_TEMP>
  template <typename T>
  SHADER_VARIABLE_TYPE::derived_type&
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::
    DoSetValueAs(Array<T>& a_array, swap_array_policy)
  {
    TLOC_ASSERT(DoGetValueRef().IsEmpty() || DoGetValueRef().IsSameType(a_array),
      "Cannot change uniform TYPE after construction");
    DoSetType(tlToGl<T>::k_glType);
    m_isArray = true;
    DoGetValueRef().Assign(Array<T>());
    DoGetValueRef().Cast<Array<T> >().swap(a_array);
    return *(static_cast<derived_type*>(this));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SHADER_VARIABLE_TEMP>
  template <typename T>
  SHADER_VARIABLE_TYPE::derived_type&
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::
    DoSetValueAs(VirtualPtr<Array<T> > a_array)
  {
    TLOC_ASSERT(DoGetValueRef().IsEmpty() || DoGetValueRef().IsSameType(a_array),
      "Cannot change uniform TYPE after construction");
    DoSetType(tlToGl<T>::k_glType);
    m_isArray = true;
    m_isArrayPtr = true;
    DoGetValueRef().Assign(a_array);
    return *(static_cast<derived_type*>(this));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SHADER_VARIABLE_TEMP>
  SHADER_VARIABLE_TYPE::derived_type&
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::SetName(const string_type& a_value)
  {
    base_type::SetName(a_value);
    return *(static_cast<derived_type*>(this));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SHADER_VARIABLE_TEMP>
  bool
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::
    IsValidType() const
  {
    return GetType() != GL_NONE;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SHADER_VARIABLE_TEMP>
  void
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::
    ResetValue()
  { DoGetValueRef().Reset(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <SHADER_VARIABLE_TEMP>
  void
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::
    Reset()
  {
    DoSetType(GL_NONE);
    m_isArray     = false;
    m_isArrayPtr  = false;

    DoGetValueRef().Reset();
    SetName("");
  }

  //------------------------------------------------------------------------
  // Explicit instantiation

#include "tlocShaderVariableExplicitMacros.h"

  //````````````````````````````````````````````````````````````````````````
  // Uniform
  TLOC_SHADER_VARIABLE_EXPLICIT(Uniform);

  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(f32,                 Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec2f32,             Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec3f32,             Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec4f32,             Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(s32,                 Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple2s32,           Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple3s32,           Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple4s32,           Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(bool,                Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple2b,             Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple3b,             Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple4b,             Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Mat2f32,             Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Mat3f32,             Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Mat4f32,             Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(TextureObject,       Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(TextureObjectShadow, Uniform);

#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(u32,              Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple2u32,        Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple3u32,        Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple4u32,        Uniform);
#endif

  //````````````````````````````````````````````````````````````````````````
  // Attribute
  TLOC_SHADER_VARIABLE_EXPLICIT(Attribute);

  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(f32,                   Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec2f32,               Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec3f32,               Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec4f32,               Attribute);


#if defined (TLOC_OS_WIN)
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(s32,                   Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple2s32,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple3s32,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple4s32,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(u32,                   Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple2u32,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple3u32,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple4u32,             Attribute);
#endif

#undef TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS

};};};