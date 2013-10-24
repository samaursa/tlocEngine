#ifndef _TLOC_GRAPHICS_GL_TEXTURE_OBJECT_H_
#define _TLOC_GRAPHICS_GL_TEXTURE_OBJECT_H_

#include <tlocCore/tloc_core.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>

#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/media/tlocImage.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_texture_object {
    namespace target
    {
      typedef s32 enum_type; // s32 because GLint is s32

      struct Tex1D                 { static const enum_type s_glParamName; };
      struct Tex2D                 { static const enum_type s_glParamName; };
      struct Tex3D                 { static const enum_type s_glParamName; };

      struct TexRectangle          { static const enum_type s_glParamName; };
      struct TexCubeMap            { static const enum_type s_glParamName; };
      struct TexBuffer             { static const enum_type s_glParamName; };
      struct Tex2DMultiSample      { static const enum_type s_glParamName; };

      struct Tex1DArray            { static const enum_type s_glParamName; };
      struct Tex2DArray            { static const enum_type s_glParamName; };
      struct TexCubeMapArray       { static const enum_type s_glParamName; };
      struct Tex2DMultiSampleArray { static const enum_type s_glParamName; };
    };
  };

  namespace p_texture_object
  {
    namespace wrap_technique
    {
      typedef s32         value_type;

      struct ClampToEdge
      { static const value_type s_glEnumValue; };
      struct ClampToBorder
      { static const value_type s_glEnumValue; };
      struct MirroredRepeat
      { static const value_type s_glEnumValue; };
      struct Repeat
      { static const value_type s_glEnumValue; };
      struct MirrorClampToEdge
      { static const value_type s_glEnumValue; };
    };

    namespace filter
    {
      typedef s32         value_type;

      struct Nearest
      { static const value_type s_glEnumValue; };
      struct Linear
      { static const value_type s_glEnumValue; };
      struct NearestMipmapNearest
      { static const value_type s_glEnumValue; };
      struct LinearMipmapNearest
      { static const value_type s_glEnumValue; };
      struct NearestMipmapLinear
      { static const value_type s_glEnumValue; };
      struct LinearMipmapLinear
      { static const value_type s_glEnumValue; };
    };
  };

  class TextureObject
    : public Object_T<TextureObject, p_object::OnlyID>
  {
  public:
    struct Params
    {
      typedef Params                                          this_type;
      typedef p_texture_object::target::enum_type             texture_type;
      typedef p_texture_object::wrap_technique::value_type    wrap_value_type;
      typedef p_texture_object::filter::value_type            filter_value_type;

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      Params()
      {
        using namespace p_texture_object::wrap_technique;
        using namespace p_texture_object::filter;

        // defaults
        Wrap_S<ClampToEdge>().Wrap_T<ClampToEdge>();
        MinFilter<Linear>().MagFilter<Linear>();
        TextureType<p_texture_object::target::Tex2D>();
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <typename T_WrapTechnique>
      this_type&
        Wrap_S()
      {
        using namespace p_texture_object::wrap_technique;

        tloc::type_traits::AssertTypeIsSupported<T_WrapTechnique,
          ClampToEdge, ClampToBorder, MirroredRepeat,
          Repeat, MirrorClampToEdge>();

        m_wrap_s = T_WrapTechnique::s_glEnumValue;
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

        m_wrap_t = T_WrapTechnique::s_glEnumValue;
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

        m_minFilter = T_Filter::s_glEnumValue;
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

        m_magFilter = T_Filter::s_glEnumValue;
        return *this;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <typename T_Target>
      void  TextureType();

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      TLOC_DECL_AND_DEF_GETTER
        (wrap_value_type, GetWrap_S, m_wrap_s);
      TLOC_DECL_AND_DEF_GETTER
        (wrap_value_type, GetWrap_T, m_wrap_t);
      TLOC_DECL_AND_DEF_GETTER
        (filter_value_type, GetMinFilter, m_minFilter);
      TLOC_DECL_AND_DEF_GETTER
        (filter_value_type, GetMagFilter, m_magFilter);
      TLOC_DECL_AND_DEF_GETTER
        (texture_type, GetTextureType, m_textureType);

    private:
      wrap_value_type       m_wrap_s;
      wrap_value_type       m_wrap_t;
      filter_value_type     m_minFilter;
      filter_value_type     m_magFilter;
      texture_type          m_textureType;
    };

  public:
    template <typename T> friend class ObjectRefCounted;

  public:
    typedef TextureObject                                 this_type;
    typedef Object_T<this_type, p_object::OnlyID>         base_type;
    typedef base_type::object_handle                      object_handle;
    typedef base_type::error_type                         error_type;
    typedef s32                                           texture_image_unit_type;
    typedef p_texture_object::target::enum_type           texture_type;
    typedef media::Image                                  image_type;

  public:
    TextureObject(const Params& a_params = Params());
    ~TextureObject();

    error_type  Initialize(const image_type& a_image);

    error_type  Bind() const;

    error_type  Activate();
    bool        IsActive() const;
    error_type  Deactivate();

    void        Update();

    TLOC_DECL_AND_DEF_SETTER(Params, SetParams, m_params);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(Params, GetParams, m_params);

    TLOC_DECL_AND_DEF_GETTER(texture_image_unit_type, GetTextureImageUnit, m_texImageUnit);

  private:

  private:
    texture_image_unit_type   m_texImageUnit;
    Params                    m_params;
  };

  //------------------------------------------------------------------------
  // Template method definitions

  template <typename T_Target>
  void
    TextureObject::Params::
    TextureType()
  {
    using namespace p_texture_object::target;

    // TODO: Support the rest of the image formats
    //type_traits::AssertTypeIsSupported
    //  <T_Target,
    //   Tex1D, Tex2D, Tex3D,
    //   TexRectangle, TexCubeMap, TexBuffer, Tex2DMultiSample,
    //   Tex1DArray, Tex2DArray, TexCubeMapArray, Tex2DMultiSampleArray>();

    tloc::type_traits::AssertTypeIsSupported
      <T_Target,
      Tex2D, TexCubeMap>();
    m_textureType = T_Target::s_glParamName;
  }

  //------------------------------------------------------------------------
  // typedefs

  typedef core::smart_ptr::SharedPtr<TextureObject>   texture_object_sptr;

};};};

#endif