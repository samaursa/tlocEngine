#include "tlocShaderVariable.h"

#include <tlocCore/containers/tlocContainers.inl>

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocUniform.h>
#include <tlocGraphics/opengl/tlocAttribute.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>
#include <tlocMath/types/tlocMatrix2.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

namespace tloc { namespace graphics { namespace gl {

  using namespace tloc::core;
  using namespace tloc::core::containers;
  using namespace tloc::math::types;

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

  TLOC_DECL_TL_TO_GL(Tuple2u32, GL_UNSIGNED_INT_VEC2);
  TLOC_DECL_TL_TO_GL(Tuple3u32, GL_UNSIGNED_INT_VEC3);
  TLOC_DECL_TL_TO_GL(Tuple4u32, GL_UNSIGNED_INT_VEC4);

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
  TLOC_DECL_TL_TO_GL(Array<Tuple2u32>, GL_UNSIGNED_INT_VEC2);
  TLOC_DECL_TL_TO_GL(Array<Tuple3u32>, GL_UNSIGNED_INT_VEC3);
  TLOC_DECL_TL_TO_GL(Array<Tuple4u32>, GL_UNSIGNED_INT_VEC4);

  TLOC_DECL_TL_TO_GL(Array<bool>,    GL_BOOL);
  TLOC_DECL_TL_TO_GL(Array<Tuple2b>, GL_BOOL_VEC2);
  TLOC_DECL_TL_TO_GL(Array<Tuple3b>, GL_BOOL_VEC3);
  TLOC_DECL_TL_TO_GL(Array<Tuple4b>, GL_BOOL_VEC4);

#undef TLOC_DECL_TL_TO_GL

  //------------------------------------------------------------------------
  // ShaderVariable

#define SHADER_VARIABLE_TEMP    typename T_Derived
#define SHADER_VARIABLE_PARAMS  T_Derived
#define SHADER_VARIABLE_TYPE    typename ShaderVariable_TI<SHADER_VARIABLE_PARAMS>

  template <SHADER_VARIABLE_TEMP>
  ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::ShaderVariable_TI()
  { }

  template <SHADER_VARIABLE_TEMP>
  ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::~ShaderVariable_TI()
  { }

  template <SHADER_VARIABLE_TEMP>
  template <typename T>
  SHADER_VARIABLE_TYPE::derived_type&
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::DoSetValueAs(const T& a_value)
  {
    TLOC_ASSERT(m_value.IsEmpty() || m_value.IsSameType(a_value),
      "Cannot change uniform TYPE after construction");
    m_type = tlToGl<T>::k_glType;
    m_isArray = false;
    m_value.Assign(a_value);
    return *(static_cast<derived_type*>(this));
  }

  template <SHADER_VARIABLE_TEMP>
  template <typename T>
  SHADER_VARIABLE_TYPE::derived_type&
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::
    DoSetValueAs(const Array<T>& a_array, copy_array_policy)
  {
    TLOC_ASSERT(m_value.IsEmpty() || m_value.IsSameType(a_array),
      "Cannot change uniform TYPE after construction");
    m_type = tlToGl<T>::k_glType;
    m_isArray = true;
    m_value.Assign(a_array);
    return *(static_cast<derived_type*>(this));
  }

  template <SHADER_VARIABLE_TEMP>
  template <typename T>
  SHADER_VARIABLE_TYPE::derived_type&
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::
    DoSetValueAs(Array<T>& a_array, swap_array_policy)
  {
    TLOC_ASSERT(m_value.IsEmpty() || m_value.IsSameType(a_array),
      "Cannot change uniform TYPE after construction");
    m_type = tlToGl<T>::k_glType;
    m_isArray = true;
    m_value.Assign(Array<T>());
    m_value.Cast<Array<T> >().swap(a_array);
    return *(static_cast<derived_type*>(this));
  }

  template <SHADER_VARIABLE_TEMP>
  SHADER_VARIABLE_TYPE::derived_type&
    ShaderVariable_TI<SHADER_VARIABLE_PARAMS>::SetName(const string_type& a_value)
  {
    m_name = a_value;
    return *(static_cast<derived_type*>(this));
  }

  //------------------------------------------------------------------------
  // Explicit instantiation

#include "tlocShaderVariableExplicitMacros.h"

  //````````````````````````````````````````````````````````````````````````
  // Uniform
  TLOC_SHADER_VARIABLE_EXPLICIT(Uniform);

  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(f32,              Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec2f32,          Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec3f32,          Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec4f32,          Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(s32,              Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple2s32,        Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple3s32,        Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple4s32,        Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(u32,              Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple2u32,        Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple3u32,        Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple4u32,        Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(bool,             Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple2b,          Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple3b,          Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple4b,          Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Mat2f32,          Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Mat3f32,          Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Mat4f32,          Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<f32>,       Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Vec2f32>,   Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Vec3f32>,   Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Vec4f32>,   Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<s32>,       Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Tuple2s32>, Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Tuple3s32>, Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Tuple4s32>, Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<u32>,       Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Tuple2u32>, Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Tuple3u32>, Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Tuple4u32>, Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<bool>,      Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Tuple2b>,   Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Tuple3b>,   Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Tuple4b>,   Uniform);

  //````````````````````````````````````````````````````````````````````````
  // Attribute
  TLOC_SHADER_VARIABLE_EXPLICIT(Attribute);

  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(f32,                   Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec2f32,               Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec3f32,               Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec4f32,               Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(s32,                   Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple2s32,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple3s32,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple4s32,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(u32,                   Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple2u32,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple3u32,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple4u32,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<s8>,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<u8>,             Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<short>,          Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<ushort>,         Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<f32>,            Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Vec2f32>,        Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Vec3f32>,        Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Array<Vec4f32>,        Attribute);
#undef TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS

};};};