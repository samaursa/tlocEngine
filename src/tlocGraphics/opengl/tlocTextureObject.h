#ifndef _TLOC_GRAPHICS_GL_TEXTURE_OBJECT_H_
#define _TLOC_GRAPHICS_GL_TEXTURE_OBJECT_H_

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/media/tlocImage.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_texture_object {

    typedef tl_size                           size_type;

    namespace target
    {
      typedef gfx_t::gl_int             value_type;

      struct Tex1D                 { static const value_type s_glParamName; };
      struct Tex2D                 { static const value_type s_glParamName; };
      struct Tex3D                 { static const value_type s_glParamName; };

      struct TexRectangle          { static const value_type s_glParamName; };
      struct TexCubeMap            { static const value_type s_glParamName; };
      struct TexBuffer             { static const value_type s_glParamName; };
      struct Tex2DMultiSample      { static const value_type s_glParamName; };

      struct Tex1DArray            { static const value_type s_glParamName; };
      struct Tex2DArray            { static const value_type s_glParamName; };
      struct TexCubeMapArray       { static const value_type s_glParamName; };
      struct Tex2DMultiSampleArray { static const value_type s_glParamName; };

      struct Tex1DShadow           { static const value_type s_glParamName; };
      struct Tex2DShadow           { static const value_type s_glParamName; };

      struct TexRectangleShadow    { static const value_type s_glParamName; };
      struct TexCubeMapShadow      { static const value_type s_glParamName; };

      struct Tex1DArrayShadow      { static const value_type s_glParamName; };
      struct Tex2DArrayShadow      { static const value_type s_glParamName; };
      struct TexCubeMapArrayShadow { static const value_type s_glParamName; };
    };

    namespace wrap_technique
    {
      typedef gfx_t::gl_int             value_type;

      struct ClampToEdge       { static const value_type s_glParamName; };
      struct ClampToBorder     { static const value_type s_glParamName; };
      struct MirroredRepeat    { static const value_type s_glParamName; };
      struct Repeat            { static const value_type s_glParamName; };
      struct MirrorClampToEdge { static const value_type s_glParamName; };
    };

    namespace filter
    {
      typedef gfx_t::gl_int             value_type;

      struct Nearest              { static const value_type s_glParamName; };
      struct Linear               { static const value_type s_glParamName; };
      struct NearestMipmapNearest { static const value_type s_glParamName; };
      struct LinearMipmapNearest  { static const value_type s_glParamName; };
      struct NearestMipmapLinear  { static const value_type s_glParamName; };
      struct LinearMipmapLinear   { static const value_type s_glParamName; };
    };

    namespace internal_format
    {
      typedef gfx_t::gl_int             value_type;

      struct Auto            { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct Red             { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct RG              { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct RGB             { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct RGBA            { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct DepthComponent  { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct DepthStencil    { static const value_type s_glParamName; static const size_type s_glChannels; };
    };

    namespace format
    {
      typedef gfx_t::gl_int             value_type;

      struct Auto           { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct Red            { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct RG             { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct RGB            { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct BGR            { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct RGBA           { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct BGRA           { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct RedInteger     { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct RGInteger      { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct RGBInteger     { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct BGRInteger     { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct RGBAInteger    { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct BGRAInteger    { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct StencilIndex   { static const value_type s_glParamName; static const size_type s_glChannels; };
      struct DepthComponent { static const value_type s_glParamName; static const size_type s_glChannels; };
    };

    namespace type
    {
      typedef gfx_t::gl_int             value_type;

      struct Auto               { static const value_type s_glParamName; };
      struct UnsignedByte       { static const value_type s_glParamName; };
      struct Byte               { static const value_type s_glParamName; };
      struct UnsignedShort      { static const value_type s_glParamName; };
      struct Short              { static const value_type s_glParamName; };
      struct UnsignedInt        { static const value_type s_glParamName; };
      struct Int                { static const value_type s_glParamName; };
      struct Float              { static const value_type s_glParamName; };
      struct UnsignedShort565   { static const value_type s_glParamName; };
      struct UnsignedShort4444  { static const value_type s_glParamName; };
      struct UnsignedShort5551  { static const value_type s_glParamName; };
    };

    namespace alignment
    {
      typedef gfx_t::gl_int             value_type;

      struct Auto           { static const value_type s_glParamName; };
      struct OneByte        { static const value_type s_glParamName; };
      struct TwoBytes       { static const value_type s_glParamName; };
      struct FourBytes      { static const value_type s_glParamName; };
      struct EightBytes     { static const value_type s_glParamName; };
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // TextureObject

  template <typename T_Target>
  class TextureObject_T
    : public Object_T<TextureObject_T<T_Target>, p_object::OnlyID>
  {
  public:
    struct Params
    {
      template <typename U_Target> friend class TextureObject_T;

      typedef Params                                        this_type;
      typedef typename TextureObject_T<T_Target>::size_type size_type;
      typedef p_texture_object::target::value_type          texture_type;
      typedef p_texture_object::wrap_technique::value_type  wrap_value_type;
      typedef p_texture_object::filter::value_type          filter_value_type;
      typedef p_texture_object::internal_format::value_type internal_format_value_type;
      typedef p_texture_object::format::value_type          format_value_type;
      typedef p_texture_object::type::value_type            type_value_type;
      typedef p_texture_object::alignment::value_type       alignment_value_type;

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      Params();

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <typename T_WrapTechnique>
      this_type&
        Wrap_S()
      {
        using namespace p_texture_object::wrap_technique;

        tloc::type_traits::AssertTypeIsSupported<T_WrapTechnique,
          ClampToEdge, ClampToBorder, MirroredRepeat,
          Repeat, MirrorClampToEdge>();

        m_wrap_s = T_WrapTechnique::s_glParamName;
        return *this;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <typename T_WrapTechnique>
      this_type&
        Wrap_T()
      {
        using namespace p_texture_object::wrap_technique;

        tloc::type_traits::AssertTypeIsSupported<T_WrapTechnique,
          ClampToEdge, ClampToBorder, MirroredRepeat,
          Repeat, MirrorClampToEdge>();

        m_wrap_t = T_WrapTechnique::s_glParamName;
        return *this;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <typename T_Filter>
      this_type&
        MinFilter()
      {
        using namespace p_texture_object::filter;

        tloc::type_traits::AssertTypeIsSupported<T_Filter,
          Nearest, Linear, NearestMipmapNearest, LinearMipmapNearest,
          NearestMipmapLinear, LinearMipmapLinear>();

        m_minFilter = T_Filter::s_glParamName;
        return *this;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <typename T_Filter>
      this_type&
        MagFilter()
      {
        using namespace p_texture_object::filter;

        tloc::type_traits::AssertTypeIsSupported<T_Filter,
          Nearest, Linear>();

        m_magFilter = T_Filter::s_glParamName;
        return *this;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <typename T_InternalFormat>
      this_type&
        InternalFormat()
      {
        using namespace p_texture_object::internal_format;

        tloc::type_traits::AssertTypeIsSupported<T_InternalFormat,
          Auto, Red, RG, RGB, RGBA, DepthComponent, DepthStencil>();

        m_internalFormat = T_InternalFormat::s_glParamName;
        m_internalFormatChannels = T_InternalFormat::s_glChannels;
        return *this;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <typename T_Format>
      this_type&
        Format()
      {
        using namespace p_texture_object::format;

        tloc::type_traits::AssertTypeIsSupported<T_Format,
          Auto,
          Red, RG, RGB, BGR, RGBA, BGRA, RedInteger, RedInteger, RGInteger,
          RGBInteger, BGRInteger, RGBAInteger, BGRAInteger, StencilIndex,
          DepthComponent>();

        m_format = T_Format::s_glParamName;
        m_formatChannels = T_Format::s_glChannels;
        return *this;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <typename T_Type>
      this_type&
        Type()
      {
        using namespace p_texture_object::type;

        tloc::type_traits::AssertTypeIsSupported<T_Type,
          Auto,
          UnsignedByte, Byte, UnsignedShort, Short, UnsignedInt, Int, Float>();

        m_type = T_Type::s_glParamName;
        return *this;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <typename T_Alignment>
      this_type&
        Alignment()
      {
        using namespace p_texture_object::alignment;

        tloc::type_traits::AssertTypeIsSupported<T_Alignment,
          Auto, OneByte, TwoBytes, FourBytes, EightBytes>();

        m_alignment = T_Alignment::s_glParamName;
        return *this;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <typename U_Target>
      void  TextureType();

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void AutoGenerateMipMaps(bool a_autoGenMipMaps = true);

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      TLOC_DECL_AND_DEF_GETTER (wrap_value_type, GetWrap_S, m_wrap_s);
      TLOC_DECL_AND_DEF_GETTER (wrap_value_type, GetWrap_T, m_wrap_t);
      TLOC_DECL_AND_DEF_GETTER (filter_value_type, GetMinFilter, m_minFilter);
      TLOC_DECL_AND_DEF_GETTER (filter_value_type, GetMagFilter, m_magFilter);
      TLOC_DECL_AND_DEF_GETTER (internal_format_value_type, GetInternalFormat, m_internalFormat);
      TLOC_DECL_AND_DEF_GETTER (size_type, GetInternalFormatChannels, m_internalFormatChannels);
      TLOC_DECL_AND_DEF_GETTER (format_value_type, GetFormat, m_format);
      TLOC_DECL_AND_DEF_GETTER (size_type, GetFormatChannels, m_formatChannels);
      TLOC_DECL_AND_DEF_GETTER (type_value_type, GetType, m_type);
      TLOC_DECL_AND_DEF_GETTER (alignment_value_type, GetAlignment, m_alignment);
      TLOC_DECL_AND_DEF_GETTER (bool, IsAutoGenMipMaps, m_autoGenMipMaps);

    private:
      wrap_value_type             m_wrap_s;
      wrap_value_type             m_wrap_t;
      filter_value_type           m_minFilter;
      filter_value_type           m_magFilter;
      internal_format_value_type  m_internalFormat;
      size_type                   m_internalFormatChannels;
      format_value_type           m_format;
      size_type                   m_formatChannels;
      type_value_type             m_type;
      alignment_value_type        m_alignment;
      bool                        m_autoGenMipMaps;
    };

  public:
    template <typename T> friend class ObjectRefCounted;

  public:
    typedef T_Target                                      target_type;
    typedef TextureObject_T<target_type>                  this_type;
    typedef Object_T<this_type, p_object::OnlyID>         base_type;
    typedef typename base_type::object_handle             object_handle;
    typedef typename base_type::error_type                error_type;
    typedef typename base_type::size_type                 size_type;
    typedef s32                                           texture_image_unit_type;
    typedef p_texture_object::target::value_type          target_value_type;
    typedef types::Dimension2u32                          dimension_type;

  public:
    using base_type::GetHandle;
    using base_type::SetHandle;
    using base_type::IsLastRef;

  public:
    TextureObject_T(const Params& a_params = Params());
    ~TextureObject_T();

    template <typename T_ColorType, typename T_Storage>
    error_type  Initialize(const gfx_med::Image_T<T_ColorType, T_Storage>& a_image);
    template <typename T_ColorType, typename T_Storage>
    error_type  Update(const gfx_med::Image_T<T_ColorType, T_Storage>& a_image) const;

    error_type  Bind() const;

    void        UpdateParameters() const;

    error_type  ReserveTextureUnit(); 
    void        ReleaseTextureUnit();
    bool        HasReservedTextureUnit() const;

    TLOC_DECL_AND_DEF_SETTER(Params, SetParams, m_params);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(Params, GetParams, m_params);

    TLOC_DECL_AND_DEF_GETTER(dimension_type, GetDimensions, m_dim);
    TLOC_DECL_AND_DEF_GETTER(texture_image_unit_type, GetReservedTexImageUnit, 
                             m_reservedTexImageUnit);

    TLOC_DECL_AND_DEF_GETTER(target_value_type, GetTargetType, 
                             target_type::s_glParamName);

  private:
    Params                    m_params;
    dimension_type            m_dim;
    texture_image_unit_type   m_reservedTexImageUnit;
  };

  //------------------------------------------------------------------------
  // typedefs

  typedef TextureObject_T<p_texture_object::target::Tex2D>        TextureObject;
  TLOC_TYPEDEF_ALL_SMART_PTRS(TextureObject, texture_object);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(TextureObject, texture_object);

  typedef TextureObject_T<p_texture_object::target::Tex2DShadow>  TextureObjectShadow;
  TLOC_TYPEDEF_ALL_SMART_PTRS(TextureObjectShadow, texture_object_shadow);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(TextureObjectShadow, texture_object_shadow);

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(TextureObject_T<p_texture_object::target::Tex2D>);
  TLOC_EXTERN_TEMPLATE_CLASS(TextureObject_T<p_texture_object::target::Tex2DShadow>);

  TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(TextureObject);
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(TextureObject);

  TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(TextureObjectShadow);
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(TextureObjectShadow);

};};};

#endif