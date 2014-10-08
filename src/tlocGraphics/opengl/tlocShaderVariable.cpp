#include "tlocShaderVariable.h"

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocUniform.h>
#include <tlocGraphics/opengl/tlocAttribute.h>
#include <tlocGraphics/types/tlocVertex.h>
#include <tlocGraphics/opengl/tlocGLTypes.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>
#include <tlocMath/types/tlocMatrix2.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

namespace tloc { namespace graphics { namespace gl {

  using namespace core_ds;
  using namespace core_conts;
  using namespace core_sptr;
  using namespace math_t;
  using namespace gfx_t;

  // ///////////////////////////////////////////////////////////////////////
  // ShaderVariable_I

  ShaderVariable_I::
    ShaderVariable_I()
    : m_type(GL_NONE)
    , m_enabled(true)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ShaderVariable_I::
    swap(this_type& a_other)
  {
    using core::swap;

    swap(m_type, a_other.m_type);
    swap(m_value, a_other.m_value);
    swap(m_name, a_other.m_name);
    swap(m_enabled, a_other.m_enabled);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const ShaderVariable_I::string_type&
    ShaderVariable_I::GetName(tl_int a_nameIndex) const
  {
    TLOC_ASSERT(a_nameIndex == 0, "ShaderVariable only has one name");
    return m_name;
  }

  // ///////////////////////////////////////////////////////////////////////
  // ShaderVariable_TI

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
    DoSetType(type_to_gl::Get<T>());
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
    DoSetType(type_to_gl::Get<T>());
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
    DoSetType(type_to_gl::Get<T>());
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
    DoSetType(type_to_gl::Get<T>());
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
    DoSetType(type_to_gl::Get<T>());
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

#undef TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS

};};};