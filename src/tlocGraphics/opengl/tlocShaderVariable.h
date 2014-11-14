#ifndef _TLOC_GRAPHICS_GL_SHADER_VARIABLE_H_
#define _TLOC_GRAPHICS_GL_SHADER_VARIABLE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/tlocAssert.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/types/tlocAny.h>
#include <tlocCore/types/tlocAny.inl.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/memory/tlocBufferArg.h>

#include <tlocCore/containers/tlocContainerTraits.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>

#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/types/tlocColor.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_shader_variable_ti
  {
    struct CopyArray {};
    struct SwapArray {};
    struct Pointer {};
  };

  // ///////////////////////////////////////////////////////////////////////
  // ShaderVariableI

  class ShaderVariable_I 
  { 
  public:
    typedef ShaderVariable_I                        this_type;
    typedef core_t::Any                             value_type;
    typedef core_str::String                        string_type;
    typedef tl_size                                 size_type;
    typedef gfx_t::gl_enum                          gl_type;

  public:
    ShaderVariable_I();

    void swap(this_type& a_other);

    TLOC_DECL_AND_DEF_GETTER(gl_type, GetType, m_type);
    TLOC_DECL_AND_DEF_GETTER(bool, IsEnabled, m_enabled);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(bool, SetEnabled, m_enabled);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetName, m_name);
    TLOC_DECL_AND_DEF_SETTER_CHAIN(string_type, SetName, m_name);

    const string_type& GetName(size_type a_nameIndex) const;
    gl_type            GetInterleavedType(size_type a_typeIndex) const;

  protected:
    TLOC_DECL_AND_DEF_SETTER(gl_type, DoSetType, m_type);
    TLOC_DECL_AND_DEF_GETTER_DIRECT(value_type, DoGetValueRef, m_value);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(value_type, DoGetValueRef, m_value);

  private:
    gl_type       m_type;
    value_type    m_value;
    string_type   m_name;
    bool          m_enabled;
  };

  // ///////////////////////////////////////////////////////////////////////
  // ShaderVariable_TI<>

  template <typename T_Derived>
  class ShaderVariable_TI 
    : public ShaderVariable_I
  {
  public:
    typedef ShaderVariable_I                  base_type;
    typedef T_Derived                         derived_type;
    typedef ShaderVariable_TI<derived_type>   this_type;

    typedef p_shader_variable_ti::CopyArray   copy_array_policy;
    typedef p_shader_variable_ti::SwapArray   swap_array_policy;

  public:
    template <typename T>
    void GetValueAs(T& a_out) const;

    template <typename T>
    const T&  GetValueAs() const;

    template <typename T>
    const core::smart_ptr::VirtualPtr<T> GetValueAsArrayPtr() const;

    template <typename T>
    derived_type& SetValueAs(const T& a_value);

    template <typename T, tl_int T_Size>
    derived_type& SetValueAs(const gfx_t::Color_T<T, T_Size> a_color);

    template <typename T>
    derived_type& SetValueAs(core::smart_ptr::VirtualPtr<T> a_value);

    template <typename T, typename T_Technique>
    derived_type&
      SetValueAs(core::containers::Array<T>& a_array, T_Technique);

    template <typename T>
    derived_type&
      SetValueAs(core::smart_ptr::VirtualPtr<core::containers::Array<T> >
                 a_array, p_shader_variable_ti::Pointer);

    derived_type& SetName(const string_type& a_value);

    bool          IsValidType() const;

    void          ResetValue();
    void          Reset();

    TLOC_DECL_AND_DEF_GETTER(bool, IsArray, m_isArray);
    TLOC_DECL_AND_DEF_GETTER(bool, IsArrayPtr, m_isArrayPtr);

  protected:
    ShaderVariable_TI();
    ~ShaderVariable_TI();

    ShaderVariable_TI(const this_type& a_other);

    void swap(this_type& a_other);

  private:
    template <typename T>
    derived_type& DoSetValueAs(const T& a_value);

    template <typename T>
    derived_type& DoSetValueAs(core_sptr::VirtualPtr<T> a_value);

    template <typename T>
    derived_type& DoSetValueAs(const core_conts::Array<T>& a_array,
                               copy_array_policy);

    template <typename T>
    derived_type& DoSetValueAs(core_conts::Array<T>& a_array,
                               swap_array_policy);

    template <typename T>
    derived_type& DoSetValueAs(core_sptr::VirtualPtr
                                <core_conts::Array<T> > a_array);

  private:
    bool          m_isArray;
    bool          m_isArrayPtr;
  };

  //------------------------------------------------------------------------
  // Template methods

  template <typename T_Derived>
  template <typename T>
  void ShaderVariable_TI<T_Derived>::
    GetValueAs(T& a_out) const
  {
    static_cast<derived_type const*>(this)->template DoCheckTypeCompatibility<T>();
    a_out = DoGetValueRef().template Cast<T>();
  }

  template <typename T_Derived>
  template <typename T>
  const T& ShaderVariable_TI<T_Derived>::
    GetValueAs() const
  {
    TLOC_ASSERT(!m_isArrayPtr, "Variable is shared - use GetValueAsShared<>()");

    static_cast<derived_type const*>(this)->template DoCheckTypeCompatibility<T>();
    return DoGetValueRef().template Cast<T>();
  }

  template <typename T_Derived>
  template <typename T>
  const core::smart_ptr::VirtualPtr<T>
    ShaderVariable_TI<T_Derived>::
    GetValueAsArrayPtr() const
  {
    using core::smart_ptr::VirtualPtr;
    TLOC_ASSERT(m_isArrayPtr, "Variable is NOT shared - use GetValueAs<>()");

    static_cast<derived_type const*>(this)->template DoCheckTypeCompatibility<T>();
    return  DoGetValueRef().template Cast<VirtualPtr<T> >();
  }

  template <typename T_Derived>
  template <typename T>
  typename ShaderVariable_TI<T_Derived>::derived_type&
    ShaderVariable_TI<T_Derived>::
    SetValueAs(const T& a_value)
  {
    TLOC_STATIC_ASSERT
      ( (core_conts::type_traits::IsContainer<T>::value == false),
         Containers_require_technique_policy  );

    static_cast<derived_type*>(this)->template DoCheckNonArrayTypes<T>();
    return DoSetValueAs(a_value);
  }

  template <typename T_Derived>
  template <typename T, tl_int T_Size>
  typename ShaderVariable_TI<T_Derived>::derived_type&
    ShaderVariable_TI<T_Derived>::
    SetValueAs(const gfx_t::Color_T<T, T_Size> a_color)
  {
    return SetValueAs(a_color.template GetAs<gfx_t::p_color::format::RGBA,
                                             math_t::Vector_T<f32, T_Size> >() );
  }

  template <typename T_Derived>
  template <typename T>
  typename ShaderVariable_TI<T_Derived>::derived_type&
    ShaderVariable_TI<T_Derived>::
    SetValueAs(core::smart_ptr::VirtualPtr<T> a_value)
  {
    static_cast<derived_type*>(this)->template DoCheckNonArrayTypes<T>();
    return DoSetValueAs(a_value);
  }

  template <typename T_Derived>
  template <typename T, typename T_Technique>
  typename ShaderVariable_TI<T_Derived>::derived_type&
    ShaderVariable_TI<T_Derived>::
    SetValueAs(core::containers::Array<T>& a_array, T_Technique)
  {
    static_cast<derived_type*>(this)->template DoCheckArrayTypes<T>();
    return DoSetValueAs(a_array, T_Technique());
  }

  template <typename T_Derived>
  template <typename T>
  typename ShaderVariable_TI<T_Derived>::derived_type&
    ShaderVariable_TI<T_Derived>::
    SetValueAs(core::smart_ptr::VirtualPtr<core::containers::Array<T> >
               a_array, p_shader_variable_ti::Pointer)
  {
    static_cast<derived_type*>(this)->template DoCheckArrayTypes<T>();
    return DoSetValueAs(a_array);
  }

  // -----------------------------------------------------------------------

#define TLOC_EXTERN_TEMPLATE_SHADER_VARIABLE(_dt_)\
  TLOC_EXTERN_TEMPLATE_CLASS(ShaderVariable_TI<_dt_>)

  // -----------------------------------------------------------------------

  namespace algos { namespace shader_variable {

    namespace transform {

      struct Enable
      {
        template <typename T>
        void operator()(ShaderVariable_TI<T>& a_sv) const
        { a_sv.SetEnabled(true); }
      };

      struct Disable
      {
        template <typename T>
        void operator()(ShaderVariable_TI<T>& a_sv) const
        { a_sv.SetEnabled(false); }
      };

    };

    namespace compare {

      struct Name
      {
        typedef BufferArg                       value_type;

        Name(value_type a_nameToCompare)
          : m_name(a_nameToCompare)
        { }

        template <typename T>
        bool operator()(const ShaderVariable_TI<T>& a_sv) const
        {
          return a_sv.GetName().compare(m_name) == 0;
        }

        value_type m_name;
      };

      struct Type
      {
        // typedefing gl_type just to show where the type comes from
        typedef u32                             gl_type;
        typedef gl_type                         value_type;

        Type(value_type a_typeToCheck)
          : m_type(a_typeToCheck)
        { }

        template <typename T>
        bool operator()(const ShaderVariable_TI<T>& a_sv) const
        { return m_type == a_sv.GetType(); }

        value_type m_type;
      };
    };

  };};

};};};

#endif
