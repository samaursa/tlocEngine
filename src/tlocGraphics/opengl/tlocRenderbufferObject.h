#ifndef _TLOC_GRAPHICS_GL_RENDERBUFFER_OBJECT_H_
#define _TLOC_GRAPHICS_GL_RENDERBUFFER_OBJECT_H_

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.h>

#include <tlocGraphics/types/tlocDimension.h>
#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_renderbuffer_object {

    namespace internal_format {

      typedef s32             value_type;

      struct RGBA4              { static const value_type s_glParamName; };
      struct RGB565             { static const value_type s_glParamName; };
      struct RGB5_A1            { static const value_type s_glParamName; };
      struct DepthComponent16   { static const value_type s_glParamName; };
      struct DepthComponent24   { static const value_type s_glParamName; };
      struct StencilIndex8      { static const value_type s_glParamName; };
      struct Depth24Stencil8    { static const value_type s_glParamName; };
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Renderbuffer Object

  class RenderbufferObject
    : public Object_T<RenderbufferObject, p_object::OnlyID>
  {
  public:
    struct Params
    {
      typedef Params                                        this_type;
      typedef p_renderbuffer_object::
              internal_format::value_type                   format_type;

      typedef types::Dimension2u32                          dimension_type;

    public:
      Params();

      template <typename T_InternalFormat>
      this_type& InternalFormat();

      this_type& Dimensions(const dimension_type& a_dim);

      TLOC_DECL_AND_DEF_GETTER(format_type, GetFormatType, m_formatType);
      TLOC_DECL_AND_DEF_GETTER(dimension_type, GetDimensions, m_dimensions);

    private:
      format_type     m_formatType;
      dimension_type  m_dimensions;
    };

  public:
    struct Bind
      : public core_bclass::NonCopyable_I
    {
      explicit Bind(const RenderbufferObject* a_rbo);
      ~Bind();
    };
    TLOC_TYPEDEF_UNIQUE_PTR(Bind, bind);

  public:
    typedef RenderbufferObject                              this_type;
    typedef Object_T<this_type, p_object::OnlyID>           base_type;
    typedef base_type::object_handle                        object_handle;
    typedef base_type::error_type                           error_type;

  public:
    RenderbufferObject(const Params& a_params = Params());
    ~RenderbufferObject();

    error_type  Initialize();
    error_type  InitializeWithoutStorage();

  public:

    TLOC_DECL_AND_DEF_GETTER(Params, GetParams, m_params);

  private:
    Params        m_params;

  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_InternalFormat>
  RenderbufferObject::Params::this_type&
    RenderbufferObject::Params::
    InternalFormat()
  {
    using namespace p_renderbuffer_object::internal_format;

    tloc::type_traits::AssertTypeIsSupported<T_InternalFormat,
      RGBA4, RGB565, RGB5_A1, DepthComponent16, DepthComponent24, StencilIndex8,
      Depth24Stencil8>();

    m_formatType = T_InternalFormat::s_glParamName;
    return *this;
  }

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(RenderbufferObject, render_buffer_object);

};};};


// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_SHARED_PTR(tloc::gfx_gl::RenderbufferObject);
TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(tloc::gfx_gl::RenderbufferObject::Bind);

#endif