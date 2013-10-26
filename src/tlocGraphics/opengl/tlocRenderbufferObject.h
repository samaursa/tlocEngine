#ifndef _TLOC_GRAPHICS_GL_RENDERBUFFER_OBJECT_H_
#define _TLOC_GRAPHICS_GL_RENDERBUFFER_OBJECT_H_

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/types/tlocStrongType.h>

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
      struct StencilIndex8      { static const value_type s_glParamName; };
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

      typedef types::Dimension2s32                          dimension_type;

    public:
      Params()
        : m_formatType(p_renderbuffer_object::internal_format::RGBA4::s_glParamName)
        , m_dimensions(0, 0)
      { }

      template <typename T_InternalFormat>
      this_type&
        InternalFormat()
      {
        using namespace p_renderbuffer_object::internal_format;

        tloc::type_traits::AssertTypeIsSupported<T_InternalFormat,
          RGBA4, RGB565, RGB5_A1, DepthComponent16, StencilIndex8>();

        m_formatType = T_InternalFormat::s_glEnumValue;
        return *this;
      }

      this_type&
        Dimensions(const dimension_type& a_dim)
      { m_dimensions = a_dim; }

      TLOC_DECL_AND_DEF_GETTER(format_type, GetFormatType, m_formatType);
      TLOC_DECL_AND_DEF_GETTER(dimension_type, GetDimensions, m_dimensions);

    private:
      format_type     m_formatType;
      dimension_type  m_dimensions;
    };

  public:
    struct Bind
    {
      Bind();
      Bind(const RenderbufferObject& a_rbo);
      ~Bind();
    };

  public:
    typedef RenderbufferObject                              this_type;
    typedef Object_T<this_type, p_object::OnlyID>           base_type;
    typedef base_type::object_handle                        object_handle;
    typedef base_type::error_type                           error_type;

  public:
    RenderbufferObject(const Params& a_params = Params());
    ~RenderbufferObject();

    error_type  Initialize();

  public:

    TLOC_DECL_AND_DEF_GETTER(Params, GetParams, m_params);

  private:
    Params        m_params;

  };

};};};

#endif