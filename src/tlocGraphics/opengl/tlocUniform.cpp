#include "tlocUniform.h"

#include <tlocGraphics/opengl/tlocOpenGL.h>

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

  TLOC_DECL_TL_TO_GL(Mat2f32, GL_FLOAT_MAT3);
  TLOC_DECL_TL_TO_GL(Mat3f32, GL_FLOAT_MAT3);
  TLOC_DECL_TL_TO_GL(Mat4f32, GL_FLOAT_MAT4);

#undef TLOC_DECL_TL_TO_GL

  //------------------------------------------------------------------------
  // Uniform

  Uniform::Uniform()
  { }

  Uniform::~Uniform()
  { }

  template <typename T>
  Uniform& Uniform::DoSetValueAs(const T& a_value)
  {
    TLOC_ASSERT(m_value.IsEmpty() || m_value.IsSameType(a_value),
      "Cannot change uniform TYPE after construction");
    m_type = tlToGl<T>::k_glType;
    m_value.Assign(a_value);
    return *this;
  }

  Uniform& Uniform::SetName(const string_type& a_value)
  {
    m_name = a_value;
    return *this;
  }

  //------------------------------------------------------------------------
  // Explicit instantiation

#include "tlocUniformExplicitMacros.h"
  TLOC_INSTANTIATE_DO_SET_VALUES(f32);
  TLOC_INSTANTIATE_DO_SET_VALUES(Vec2f32);
  TLOC_INSTANTIATE_DO_SET_VALUES(Vec3f32);
  TLOC_INSTANTIATE_DO_SET_VALUES(Vec4f32);
  TLOC_INSTANTIATE_DO_SET_VALUES(s32);
  TLOC_INSTANTIATE_DO_SET_VALUES(Tuple2s32);
  TLOC_INSTANTIATE_DO_SET_VALUES(Tuple3s32);
  TLOC_INSTANTIATE_DO_SET_VALUES(Tuple4s32);
  TLOC_INSTANTIATE_DO_SET_VALUES(Mat2f32);
  TLOC_INSTANTIATE_DO_SET_VALUES(Mat3f32);
  TLOC_INSTANTIATE_DO_SET_VALUES(Mat4f32);
#undef TLOC_INSTANTIATE_DO_SET_VALUES

};};};