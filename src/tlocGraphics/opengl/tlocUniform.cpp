#include "tlocUniform.h"

#include <tlocMath/vector/tlocVector3.h>
#include <tlocMath/vector/tlocVector4.h>
#include <tlocMath/matrix/tlocMatrix3.h>
#include <tlocMath/matrix/tlocMatrix4.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace gl {

  using namespace tloc::math;

  template <typename T> struct tlToGl;

  template <> struct tlToGl<Mat3f>
  { enum { k_glType = GL_FLOAT_MAT3 }; };

  template <> struct tlToGl<Mat4f>
  { enum { k_glType = GL_FLOAT_MAT4 }; };

  template <> struct tlToGl<Vec3f>
  { enum { k_glType = GL_FLOAT_VEC3 }; };

  template <> struct tlToGl<Vec4f>
  { enum { k_glType = GL_FLOAT_VEC4 }; };

  Uniform::Uniform()
  { }

  Uniform::~Uniform()
  { }

  template <typename T>
  Uniform& Uniform::SetValueAs(const T& a_value)
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

  template Uniform& Uniform::SetValueAs(const Mat3f&);
  template Uniform& Uniform::SetValueAs(const Mat4f&);
  template Uniform& Uniform::SetValueAs(const Vec3f&);
  template Uniform& Uniform::SetValueAs(const Vec4f&);

};};};