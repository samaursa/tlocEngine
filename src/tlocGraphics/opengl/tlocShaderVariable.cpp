#include "tlocShaderVariable.h"

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocUniform.h>
#include <tlocGraphics/opengl/tlocAttribute.h>

#include "tlocShaderVariable.h"
#include <tlocMath/vector/tlocVector2.h>
#include <tlocMath/vector/tlocVector3.h>
#include <tlocMath/vector/tlocVector4.h>
#include <tlocMath/matrix/tlocMatrix2.h>
#include <tlocMath/matrix/tlocMatrix3.h>
#include <tlocMath/matrix/tlocMatrix4.h>

namespace tloc { namespace graphics { namespace gl {

  using namespace tloc::core;
  using namespace tloc::math;

  //------------------------------------------------------------------------
  // Supported types

  template <typename T> struct tlToGl;

#define TLOC_DECL_TL_TO_GL(_type_, _glType_)\
  template <> struct tlToGl<_type_>\
  { enum { k_glType = _glType_ }; }

  TLOC_DECL_TL_TO_GL(f32, GL_FLOAT);

  TLOC_DECL_TL_TO_GL(Vec2f32, GL_FLOAT_VEC2);
  TLOC_DECL_TL_TO_GL(Vec3f32, GL_FLOAT_VEC3);
  TLOC_DECL_TL_TO_GL(Vec4f32, GL_FLOAT_VEC4);

  TLOC_DECL_TL_TO_GL(s32, GL_INT);

  TLOC_DECL_TL_TO_GL(Tuple2s32, GL_INT_VEC2);
  TLOC_DECL_TL_TO_GL(Tuple3s32, GL_INT_VEC3);
  TLOC_DECL_TL_TO_GL(Tuple4s32, GL_INT_VEC4);

  TLOC_DECL_TL_TO_GL(Mat2f32, GL_FLOAT_MAT2);
  TLOC_DECL_TL_TO_GL(Mat3f32, GL_FLOAT_MAT3);
  TLOC_DECL_TL_TO_GL(Mat4f32, GL_FLOAT_MAT4);

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
    m_value.Assign(a_value);
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

  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(f32,       Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec2f32,   Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec3f32,   Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec4f32,   Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(s32,       Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple2s32, Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple3s32, Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple4s32, Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Mat2f32,   Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Mat3f32,   Uniform);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Mat4f32,   Uniform);

  //````````````````````````````````````````````````````````````````````````
  // Attribute
  TLOC_SHADER_VARIABLE_EXPLICIT(Attribute);

  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(f32,       Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec2f32,   Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec3f32,   Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Vec4f32,   Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(s32,       Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple2s32, Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple3s32, Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Tuple4s32, Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Mat2f32,   Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Mat3f32,   Attribute);
  TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(Mat4f32,   Attribute);
#undef TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS

};};};