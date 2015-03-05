#include "tlocTextureObject.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace graphics { namespace gl {

  namespace p_texture_object {
    namespace target {

#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL

      const value_type Tex1D::s_glParamName = GL_TEXTURE_1D;
      const value_type Tex2D::s_glParamName = GL_TEXTURE_2D;
      const value_type Tex3D::s_glParamName = GL_TEXTURE_3D;

      const value_type TexRectangle::s_glParamName     = GL_TEXTURE_RECTANGLE;
      const value_type TexCubeMap::s_glParamName       = GL_TEXTURE_CUBE_MAP;
      const value_type TexBuffer::s_glParamName        = GL_TEXTURE_BUFFER;
      const value_type Tex2DMultiSample::s_glParamName = GL_TEXTURE_2D_MULTISAMPLE;

      const value_type Tex1DArray::s_glParamName = GL_TEXTURE_1D_ARRAY;
      const value_type Tex2DArray::s_glParamName = GL_TEXTURE_2D_ARRAY;
      const value_type TexCubeMapArray::s_glParamName = GL_TEXTURE_CUBE_MAP_ARRAY;
      const value_type
        Tex2DMultiSampleArray::s_glParamName = GL_TEXTURE_2D_MULTISAMPLE_ARRAY;

      const value_type Tex1DShadow::s_glParamName = GL_TEXTURE_1D;
      const value_type Tex2DShadow::s_glParamName = GL_TEXTURE_2D;

      const value_type TexRectangleShadow::s_glParamName     = GL_TEXTURE_RECTANGLE;
      const value_type TexCubeMapShadow::s_glParamName       = GL_TEXTURE_CUBE_MAP;

      const value_type Tex1DArrayShadow::s_glParamName = GL_TEXTURE_1D_ARRAY;
      const value_type Tex2DArrayShadow::s_glParamName = GL_TEXTURE_2D_ARRAY;
      const value_type TexCubeMapArrayShadow::s_glParamName = GL_TEXTURE_CUBE_MAP_ARRAY;

#elif defined (TLOC_OS_IPHONE) // TODO: Change to TLOC_GFX_PLATFORM_GL_ES

      const value_type Tex2D::s_glParamName       = GL_TEXTURE_2D;
      const value_type Tex2DShadow::s_glParamName = GL_TEXTURE_2D;
      const value_type TexCubeMap::s_glParamName  = GL_TEXTURE_CUBE_MAP;

      const value_type Tex1D::s_glParamName = 0;
      const value_type Tex3D::s_glParamName = 0;

      const value_type TexRectangle::s_glParamName     = 0;

      const value_type TexBuffer::s_glParamName        = 0;
      const value_type Tex2DMultiSample::s_glParamName = 0;

      const value_type Tex1DArray::s_glParamName = 0;
      const value_type Tex2DArray::s_glParamName = 0;
      const value_type TexCubeMapArray::s_glParamName = 0;
      const value_type Tex2DMultiSampleArray::s_glParamName = 0;

#else
# error "WIP"
#endif

    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // static variables initialization

  namespace p_texture_object {

#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL

    typedef wrap_technique::value_type  wvt;
    typedef filter::value_type          fvt;
    typedef format::value_type          formvt;
    typedef internal_format::value_type ifvt;
    typedef type::value_type            tvt;
    typedef alignment::value_type       avt;

    const wvt wrap_technique::ClampToEdge::s_glParamName       = GL_CLAMP_TO_EDGE;
    const wvt wrap_technique::ClampToBorder::s_glParamName     = GL_CLAMP_TO_BORDER;
    const wvt wrap_technique::MirroredRepeat::s_glParamName    = GL_MIRRORED_REPEAT;
    const wvt wrap_technique::Repeat::s_glParamName            = GL_REPEAT;
    const wvt wrap_technique::MirrorClampToEdge::s_glParamName = GL_MIRROR_CLAMP_TO_EDGE_EXT;

    const fvt filter::Nearest::s_glParamName              = GL_NEAREST;
    const fvt filter::Linear::s_glParamName               = GL_LINEAR;
    const fvt filter::NearestMipmapNearest::s_glParamName = GL_NEAREST_MIPMAP_NEAREST;
    const fvt filter::LinearMipmapNearest::s_glParamName  = GL_LINEAR_MIPMAP_NEAREST;
    const fvt filter::NearestMipmapLinear::s_glParamName  = GL_NEAREST_MIPMAP_LINEAR;
    const fvt filter::LinearMipmapLinear::s_glParamName   = GL_LINEAR_MIPMAP_LINEAR;

    const formvt format::Auto::s_glParamName           = GL_NONE;
    const formvt format::Red::s_glParamName            = GL_RED;
    const formvt format::RG::s_glParamName             = GL_RG;
    const formvt format::RGB::s_glParamName            = GL_RGB;
    const formvt format::BGR::s_glParamName            = GL_BGR;
    const formvt format::RGBA::s_glParamName           = GL_RGBA;
    const formvt format::BGRA::s_glParamName           = GL_BGRA;
    const formvt format::RedInteger::s_glParamName     = GL_RED_INTEGER;
    const formvt format::RGInteger::s_glParamName      = GL_RG_INTEGER;
    const formvt format::RGBInteger::s_glParamName     = GL_RGB_INTEGER;
    const formvt format::BGRInteger::s_glParamName     = GL_BGR_INTEGER;
    const formvt format::RGBAInteger::s_glParamName    = GL_RGBA_INTEGER;
    const formvt format::BGRAInteger::s_glParamName    = GL_BGRA_INTEGER;
    const formvt format::StencilIndex::s_glParamName   = GL_STENCIL_INDEX;
    const formvt format::DepthComponent::s_glParamName = GL_DEPTH_COMPONENT;

    const size_type format::Auto::s_glChannels           = 0;
    const size_type format::Red::s_glChannels            = 1;
    const size_type format::RG::s_glChannels             = 2;
    const size_type format::RGB::s_glChannels            = 3;
    const size_type format::BGR::s_glChannels            = 3;
    const size_type format::RGBA::s_glChannels           = 4;
    const size_type format::BGRA::s_glChannels           = 4;
    const size_type format::RedInteger::s_glChannels     = 1;
    const size_type format::RGInteger::s_glChannels      = 2;
    const size_type format::RGBInteger::s_glChannels     = 3;
    const size_type format::BGRInteger::s_glChannels     = 3;
    const size_type format::RGBAInteger::s_glChannels    = 4;
    const size_type format::BGRAInteger::s_glChannels    = 4;
    const size_type format::StencilIndex::s_glChannels   = 1;
    const size_type format::DepthComponent::s_glChannels = 1;

    const ifvt internal_format::Auto::s_glParamName           = GL_NONE;
    const ifvt internal_format::Red::s_glParamName            = GL_RED;
    const ifvt internal_format::RG::s_glParamName             = GL_RG;
    const ifvt internal_format::RGB::s_glParamName            = GL_RGB;
    const ifvt internal_format::RGBA::s_glParamName           = GL_RGBA;
    const ifvt internal_format::DepthComponent::s_glParamName = GL_DEPTH_COMPONENT;
    const ifvt internal_format::DepthStencil::s_glParamName   = GL_DEPTH_STENCIL;

    const size_type internal_format::Auto::s_glChannels           = 0;
    const size_type internal_format::Red::s_glChannels            = 1;
    const size_type internal_format::RG::s_glChannels             = 2;
    const size_type internal_format::RGB::s_glChannels            = 3;
    const size_type internal_format::RGBA::s_glChannels           = 4;
    const size_type internal_format::DepthComponent::s_glChannels = 1;
    const size_type internal_format::DepthStencil::s_glChannels   = 1;

    const tvt  type::Auto::s_glParamName                      = GL_NONE;
    const tvt  type::UnsignedByte::s_glParamName              = GL_UNSIGNED_BYTE;
    const tvt  type::Byte::s_glParamName                      = GL_BYTE;
    const tvt  type::UnsignedShort::s_glParamName             = GL_UNSIGNED_SHORT;
    const tvt  type::Short::s_glParamName                     = GL_SHORT;
    const tvt  type::UnsignedInt::s_glParamName               = GL_UNSIGNED_INT;
    const tvt  type::Int::s_glParamName                       = GL_INT;
    const tvt  type::Float::s_glParamName                     = GL_FLOAT;
    const tvt  type::UnsignedShort565::s_glParamName          = GL_UNSIGNED_SHORT_5_6_5;
    const tvt  type::UnsignedShort4444::s_glParamName         = GL_UNSIGNED_SHORT_4_4_4_4;
    const tvt  type::UnsignedShort5551::s_glParamName         = GL_UNSIGNED_SHORT_5_5_5_1;

    const avt  alignment::Auto::s_glParamName                 = GL_NONE;
    const avt  alignment::OneByte::s_glParamName              = 1;
    const avt  alignment::TwoBytes::s_glParamName             = 2;
    const avt  alignment::FourBytes::s_glParamName            = 4;
    const avt  alignment::EightBytes::s_glParamName           = 8;

#elif defined (TLOC_OS_IPHONE) // TODO: Change to TLOC_GFX_PLATFORM_GL_ES

    // GL_STENCIL_INDEX is no longer defined in iOS 7 framework
#if !defined(GL_STENCIL_INDEX) && defined(GL_STENCIL_INDEX8_OES)
#define GL_STENCIL_INDEX                            GL_STENCIL_INDEX8_OES
#endif
#if !defined(GL_STENCIL_INDEX) && defined(GL_STENCIL_INDEX8)
#define GL_STENCIL_INDEX                            GL_STENCIL_INDEX8
#endif

    typedef wrap_technique::value_type  wvt;
    typedef filter::value_type          fvt;
    typedef format::value_type          formvt;
    typedef internal_format::value_type ifvt;
    typedef type::value_type            tvt;
    typedef alignment::value_type       avt;

    const wvt wrap_technique::ClampToEdge::s_glParamName       = GL_CLAMP_TO_EDGE;
    const wvt wrap_technique::ClampToBorder::s_glParamName     = TLOC_GL_UNSUPPORTED;
    const wvt wrap_technique::MirroredRepeat::s_glParamName    = GL_CLAMP_TO_EDGE;
    const wvt wrap_technique::Repeat::s_glParamName            = GL_CLAMP_TO_EDGE;
    const wvt wrap_technique::MirrorClampToEdge::s_glParamName = GL_CLAMP_TO_EDGE;

    const fvt filter::Nearest::s_glParamName              = GL_NEAREST;
    const fvt filter::Linear::s_glParamName               = GL_LINEAR;
    const fvt filter::NearestMipmapNearest::s_glParamName = GL_NEAREST_MIPMAP_NEAREST;
    const fvt filter::LinearMipmapNearest::s_glParamName  = GL_LINEAR_MIPMAP_NEAREST;
    const fvt filter::NearestMipmapLinear::s_glParamName  = GL_NEAREST_MIPMAP_LINEAR;
    const fvt filter::LinearMipmapLinear::s_glParamName   = GL_LINEAR_MIPMAP_LINEAR;

    const formvt format::Auto::s_glParamName           = GL_NONE;
    const formvt format::Red::s_glParamName            = GL_RED_EXT;
    const formvt format::RG::s_glParamName             = GL_RG_EXT;
    const formvt format::RGB::s_glParamName            = GL_RGB;
    const formvt format::BGR::s_glParamName            = TLOC_GL_UNSUPPORTED;
    const formvt format::RGBA::s_glParamName           = GL_RGBA;
    const formvt format::BGRA::s_glParamName           = GL_BGRA;
    const formvt format::RedInteger::s_glParamName     = TLOC_GL_UNSUPPORTED;
    const formvt format::RGInteger::s_glParamName      = TLOC_GL_UNSUPPORTED;
    const formvt format::RGBInteger::s_glParamName     = TLOC_GL_UNSUPPORTED;
    const formvt format::BGRInteger::s_glParamName     = TLOC_GL_UNSUPPORTED;
    const formvt format::RGBAInteger::s_glParamName    = TLOC_GL_UNSUPPORTED;
    const formvt format::BGRAInteger::s_glParamName    = TLOC_GL_UNSUPPORTED;
    const formvt format::StencilIndex::s_glParamName   = GL_STENCIL_INDEX;
    const formvt format::DepthComponent::s_glParamName = GL_DEPTH_COMPONENT;

    const size_type format::Auto::s_glChannels           = 0;
    const size_type format::Red::s_glChannels            = 1;
    const size_type format::RG::s_glChannels             = 2;
    const size_type format::RGB::s_glChannels            = 3;
    const size_type format::BGR::s_glChannels            = 3;
    const size_type format::RGBA::s_glChannels           = 4;
    const size_type format::BGRA::s_glChannels           = 4;
    const size_type format::RedInteger::s_glChannels     = 1;
    const size_type format::RGInteger::s_glChannels      = 2;
    const size_type format::RGBInteger::s_glChannels     = 3;
    const size_type format::BGRInteger::s_glChannels     = 3;
    const size_type format::RGBAInteger::s_glChannels    = 4;
    const size_type format::BGRAInteger::s_glChannels    = 4;
    const size_type format::StencilIndex::s_glChannels   = 1;
    const size_type format::DepthComponent::s_glChannels = 1;

    const ifvt internal_format::Auto::s_glParamName           = GL_NONE;
    const ifvt internal_format::Red::s_glParamName            = GL_RED_EXT;
    const ifvt internal_format::RG::s_glParamName             = GL_RG_EXT;
    const ifvt internal_format::RGB::s_glParamName            = GL_RGB;
    const ifvt internal_format::RGBA::s_glParamName           = GL_RGBA;
    const ifvt internal_format::DepthComponent::s_glParamName = GL_DEPTH_COMPONENT;
    const ifvt internal_format::DepthStencil::s_glParamName   = GL_DEPTH_STENCIL_OES;

    const size_type internal_format::Auto::s_glChannels           = 0;
    const size_type internal_format::Red::s_glChannels            = 1;
    const size_type internal_format::RG::s_glChannels             = 2;
    const size_type internal_format::RGB::s_glChannels            = 3;
    const size_type internal_format::RGBA::s_glChannels           = 4;
    const size_type internal_format::DepthComponent::s_glChannels = 1;
    const size_type internal_format::DepthStencil::s_glChannels   = 1;

    const tvt  type::Auto::s_glParamName                      = GL_NONE;
    const tvt  type::UnsignedByte::s_glParamName              = GL_UNSIGNED_BYTE;
    const tvt  type::Byte::s_glParamName                      = GL_BYTE;
    const tvt  type::UnsignedShort::s_glParamName             = GL_UNSIGNED_SHORT;
    const tvt  type::Short::s_glParamName                     = GL_SHORT;
    const tvt  type::UnsignedInt::s_glParamName               = GL_UNSIGNED_INT;
    const tvt  type::Int::s_glParamName                       = GL_INT;
    const tvt  type::Float::s_glParamName                     = GL_FLOAT;
    const tvt  type::UnsignedShort565::s_glParamName          = GL_UNSIGNED_SHORT_5_6_5;
    const tvt  type::UnsignedShort4444::s_glParamName         = GL_UNSIGNED_SHORT_4_4_4_4;
    const tvt  type::UnsignedShort5551::s_glParamName         = GL_UNSIGNED_SHORT_5_5_5_1;

    const avt  alignment::Auto::s_glParamName                 = GL_NONE;
    const avt  alignment::OneByte::s_glParamName              = 1;
    const avt  alignment::TwoBytes::s_glParamName             = 2;
    const avt  alignment::FourBytes::s_glParamName            = 4;
    const avt  alignment::EightBytes::s_glParamName           = 8;

#else
# error "WIP"
#endif

    // ///////////////////////////////////////////////////////////////////////
    // Params

    Params::
      Params()
      : m_internalFormatChannels(0)
      , m_formatChannels(0)
      , m_autoGenMipMaps(true)
    {
      using namespace p_texture_object::wrap_technique;
      using namespace p_texture_object::filter;
      using namespace p_texture_object::target;
      using namespace p_texture_object::alignment;

      // defaults
      Wrap_S<ClampToEdge>(); Wrap_T<ClampToEdge>(); Wrap_R<ClampToEdge>();
      MinFilter<Linear>(); MagFilter<Linear>();
      InternalFormat<internal_format::Auto>();
      Format<format::Auto>();
      Type<type::Auto>();
      Alignment<alignment::Auto>();
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      Params::
      AutoGenerateMipMaps(bool a_autoGenMipMaps)
    { m_autoGenMipMaps = a_autoGenMipMaps; }

  };

  namespace {

    // -----------------------------------------------------------------------
    // 

    // -----------------------------------------------------------------------
    // Return the 'target' of image (see glTexImage2D doc)

    template <typename T_ColorType, typename T_Storage>
    gfx_t::gl_int
      DoGetTarget(const gfx_med::Image_T<gfx_med::p_image::dim_2d, 
                                         T_ColorType, T_Storage>&)
    { return p_texture_object::target::Tex2D::s_glParamName; }

    template <typename T_ColorType, typename T_Storage>
    gfx_t::gl_int
      DoGetTarget(const gfx_med::Image_T<gfx_med::p_image::dim_3d, 
                                         T_ColorType, T_Storage>&)
    { return p_texture_object::target::Tex3D::s_glParamName; }

    // -----------------------------------------------------------------------
    // Return the 'internal format' of image (see glTexImage2D doc)

    gfx_t::gl_int
      DoGetInternalImageFormat(gfx_t::Color)
    { return p_texture_object::internal_format::RGBA::s_glParamName; }

    gfx_t::gl_int
      DoGetInternalImageFormat(gfx_t::color_rgb)
    { return p_texture_object::internal_format::RGB::s_glParamName; }

    gfx_t::gl_int
      DoGetInternalImageFormat(gfx_t::color_rg)
    { return p_texture_object::internal_format::RG::s_glParamName; }

    gfx_t::gl_int
      DoGetInternalImageFormat(gfx_t::color_r)
    { return p_texture_object::internal_format::Red::s_glParamName; }


    gfx_t::gl_int
      DoGetInternalImageFormat(gfx_t::color_u16_rgba)
    { return p_texture_object::internal_format::RGBA::s_glParamName; }

    gfx_t::gl_int
      DoGetInternalImageFormat(gfx_t::color_u16_rgb)
    { return p_texture_object::internal_format::RGB::s_glParamName; }

    gfx_t::gl_int
      DoGetInternalImageFormat(gfx_t::color_u16_rg)
    { return p_texture_object::internal_format::RG::s_glParamName; }

    gfx_t::gl_int
      DoGetInternalImageFormat(gfx_t::color_u16_r)
    { return p_texture_object::internal_format::Red::s_glParamName; }

    gfx_t::gl_int
      DoGetInternalImageFormat(gfx_t::color_f32_r)
    { return p_texture_object::internal_format::DepthComponent::s_glParamName; }

    // -----------------------------------------------------------------------
    // Return the 'format' of image (see glTexImage2D doc)

    gfx_t::gl_int
      DoGetImageFormat(gfx_t::Color)
    { return p_texture_object::format::RGBA::s_glParamName; }

    gfx_t::gl_int
      DoGetImageFormat(gfx_t::color_rgb)
    { return p_texture_object::format::RGB::s_glParamName; }

    gfx_t::gl_int
      DoGetImageFormat(gfx_t::color_rg)
    { return p_texture_object::format::RG::s_glParamName; }

    gfx_t::gl_int
      DoGetImageFormat(gfx_t::color_r)
    { return p_texture_object::format::Red::s_glParamName; }

    gfx_t::gl_int
      DoGetImageFormat(gfx_t::color_u16_rgba)
    { return p_texture_object::format::RGBA::s_glParamName; }

    gfx_t::gl_int
      DoGetImageFormat(gfx_t::color_u16_rgb)
    { return p_texture_object::format::RGB::s_glParamName; }

    gfx_t::gl_int
      DoGetImageFormat(gfx_t::color_u16_rg)
    { return p_texture_object::format::RG::s_glParamName; }

    gfx_t::gl_int
      DoGetImageFormat(gfx_t::color_u16_r)
    { return p_texture_object::format::Red::s_glParamName; }

    gfx_t::gl_int
      DoGetImageFormat(gfx_t::color_f32_r)
    { return p_texture_object::format::DepthComponent::s_glParamName; }

    // -----------------------------------------------------------------------
    // Return the number of channels of an image format

    tl_size
      DoGetImageFormatChannels(gfx_t::Color) { return 4; }

    tl_size
      DoGetImageFormatChannels(gfx_t::color_rgb) { return 3; }

    tl_size
      DoGetImageFormatChannels(gfx_t::color_rg) { return 2; }

    tl_size
      DoGetImageFormatChannels(gfx_t::color_r) { return 1; }

    tl_size
      DoGetImageFormatChannels(gfx_t::color_u16_rgba) { return 4; }

    tl_size
      DoGetImageFormatChannels(gfx_t::color_u16_rgb) { return 3; }

    tl_size
      DoGetImageFormatChannels(gfx_t::color_u16_rg) { return 2; }

    tl_size
      DoGetImageFormatChannels(gfx_t::color_u16_r) { return 1; }

    tl_size
      DoGetImageFormatChannels(gfx_t::color_f32_r) { return 1; }

    // -----------------------------------------------------------------------
    // Return the 'type' of image (see glTexImage2D doc)

    gfx_t::gl_int
      DoGetImageType(gfx_t::Color)
    { return p_texture_object::type::UnsignedByte::s_glParamName; }

    gfx_t::gl_int
      DoGetImageType(gfx_t::color_rgb)
    { return p_texture_object::type::UnsignedByte::s_glParamName; }

    gfx_t::gl_int
      DoGetImageType(gfx_t::color_rg)
    { return p_texture_object::type::UnsignedByte::s_glParamName; }

    gfx_t::gl_int
      DoGetImageType(gfx_t::color_r)
    { return p_texture_object::type::UnsignedByte::s_glParamName; }

    gfx_t::gl_int
      DoGetImageType(gfx_t::color_u16_rgba)
    { return p_texture_object::type::UnsignedShort::s_glParamName; }

    gfx_t::gl_int
      DoGetImageType(gfx_t::color_u16_rgb)
    { return p_texture_object::type::UnsignedShort::s_glParamName; }

    gfx_t::gl_int
      DoGetImageType(gfx_t::color_u16_rg)
    { return p_texture_object::type::UnsignedShort::s_glParamName; }

    gfx_t::gl_int
      DoGetImageType(gfx_t::color_u16_r)
    { return p_texture_object::type::UnsignedShort::s_glParamName; }

    gfx_t::gl_int
      DoGetImageType(gfx_t::color_f32_r)
    { return p_texture_object::type::Float::s_glParamName; }

    // -----------------------------------------------------------------------
    // Return the 'alignment' of image (see glPixelStorei doc)

    gfx_t::gl_int
      DoGetAlignment(gfx_t::Color)
    { return p_texture_object::alignment::FourBytes::s_glParamName; }

    gfx_t::gl_int
      DoGetAlignment(gfx_t::color_rgb)
    { return p_texture_object::alignment::OneByte::s_glParamName; }

    gfx_t::gl_int
      DoGetAlignment(gfx_t::color_rg)
    { return p_texture_object::alignment::OneByte::s_glParamName; }

    gfx_t::gl_int
      DoGetAlignment(gfx_t::color_r)
    { return p_texture_object::alignment::OneByte::s_glParamName; }

    gfx_t::gl_int
      DoGetAlignment(gfx_t::color_u16_rgba)
    { return p_texture_object::alignment::EightBytes::s_glParamName; }

    gfx_t::gl_int
      DoGetAlignment(gfx_t::color_u16_rgb)
    { return p_texture_object::alignment::TwoBytes::s_glParamName; }

    gfx_t::gl_int
      DoGetAlignment(gfx_t::color_u16_rg)
    { return p_texture_object::alignment::TwoBytes::s_glParamName; }

    gfx_t::gl_int
      DoGetAlignment(gfx_t::color_u16_r)
    { return p_texture_object::alignment::TwoBytes::s_glParamName; }

    gfx_t::gl_int
      DoGetAlignment(gfx_t::color_f32_r)
    { return p_texture_object::alignment::FourBytes::s_glParamName; }
  };

  // ///////////////////////////////////////////////////////////////////////
  // TextureObject::Params

#define TEXTURE_OBJECT_TEMPS  typename T_Target
#define TEXTURE_OBJECT_PARAMS T_Target
#define TEXTURE_OBJECT_TYPE   typename TextureObject_T<TEXTURE_OBJECT_PARAMS>

  //////////////////////////////////////////////////////////////////////////
  // TextureObject

  template <TEXTURE_OBJECT_TEMPS>
  TextureObject_T<TEXTURE_OBJECT_PARAMS>::
    TextureObject_T(const Params& a_params)
    : m_params(a_params)
    , m_dim(0)
    , m_reservedTexImageUnit(-1)
  {
    object_handle handle;
    glGenTextures(1, &handle);
    SetHandle(handle);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TEXTURE_OBJECT_TEMPS>
  TextureObject_T<TEXTURE_OBJECT_PARAMS>::
    ~TextureObject_T()
  {
    if (IsLastRef())
    {
      ReleaseTextureUnit();
      object_handle handle = GetHandle();
      glDeleteTextures(1, &handle);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TEXTURE_OBJECT_TEMPS>
  TEXTURE_OBJECT_TYPE::error_type
    TextureObject_T<TEXTURE_OBJECT_PARAMS>::
    Bind() const
  {
    object_handle handle = GetHandle();

    glBindTexture(GetTargetType(), handle);
    TLOC_ASSERT(gl::Error().Succeeded(), "Error in glBindTexture()");
    
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TEXTURE_OBJECT_TEMPS>
  template <typename T_Dim, typename T_ColorType, typename T_Storage>
  TEXTURE_OBJECT_TYPE::error_type
    TextureObject_T<TEXTURE_OBJECT_PARAMS>::
    Initialize(const gfx_med::Image_T<T_Dim, T_ColorType, T_Storage>& a_image)
  {
    using gfx_t::gl_int; using namespace p_texture_object;
    typedef gfx_med::Image_T<T_Dim, T_ColorType, T_Storage>     image_type;
    typedef typename image_type::pixel_container_type           pix_cont_type;
    typedef typename image_type::color_type                     color_type;

    // We do NOT need the original image because glTexImage2D copies the image
    m_dim[0] = core_utils::CastNumber<dimension_type::value_type>(a_image.GetDimensions()[0]);
    m_dim[1] = core_utils::CastNumber<dimension_type::value_type>(a_image.GetDimensions()[1]);

    const gl_int target = GetTargetType();
    TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(target != DoGetTarget(a_image)) <<
      "TextureObject_T<>::target_type is different than incoming image";

    const gl_int internalFormat = 
      m_params.GetInternalFormat() == internal_format::Auto::s_glParamName ? 
      DoGetInternalImageFormat(color_type()) : m_params.GetInternalFormat();

    const size_type internalFormatChannels = 
      m_params.GetInternalFormat() == format::Auto::s_glParamName ? 
      DoGetImageFormatChannels(color_type()) : m_params.GetInternalFormatChannels();

    const gl_int format = 
      m_params.GetFormat() == format::Auto::s_glParamName ? 
      DoGetImageFormat(color_type()) : m_params.GetFormat();

    const size_type formatChannels = 
      m_params.GetFormat() == format::Auto::s_glParamName ? 
      DoGetImageFormatChannels(color_type()) : m_params.GetFormatChannels();

    const gl_int type = 
      m_params.GetType() == type::Auto::s_glParamName ?  
      DoGetImageType(color_type()) : m_params.GetType();

    const gl_int alignment = 
      m_params.GetAlignment() == alignment::Auto::s_glParamName ? 
      DoGetAlignment(color_type()) : m_params.GetAlignment();

    m_params.m_internalFormat         = internalFormat;
    m_params.m_internalFormatChannels = internalFormatChannels;
    m_params.m_format                 = format;
    m_params.m_formatChannels         = formatChannels;
    m_params.m_type                   = type;
    m_params.m_alignment              = alignment;

    return Update(a_image);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TEXTURE_OBJECT_TEMPS>
  template <typename T_Dim, typename T_ColorType, typename T_Storage>
  TEXTURE_OBJECT_TYPE::error_type
    TextureObject_T<TEXTURE_OBJECT_PARAMS>::
    Update(const gfx_med::Image_T<T_Dim, T_ColorType, T_Storage>& a_image) const
  {
    TLOC_ASSERT(a_image.GetWidth() == m_dim[0] && 
                a_image.GetHeight() == m_dim[1], "Image dimensions do not match."
                " Use Initialize() for a different image.");

    using gfx_t::gl_int;
    typedef gfx_med::Image_T<T_Dim, T_ColorType, T_Storage>     image_type;
    typedef typename image_type::pixel_container_type           pix_cont_type;
    typedef typename image_type::color_type                     color_type;

    const gl_int target         = GetTargetType();
    const gl_int internalFormat = m_params.GetInternalFormat();
    const gl_int format         = m_params.GetFormat();
    const gl_int type           = m_params.GetType();
    const gl_int alignment      = m_params.GetAlignment();

    // -----------------------------------------------------------------------
    // issue warnings for inconsistencies in image type

    TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(DoGetTarget(a_image) != target)
      << "TextureObject initialized with different TARGET than "
      << "incoming image. Use Initialize() for a different image type.";

    // NOTE: no need to warn against 'internal format' as it is frequently 
    // different

    TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF
      (DoGetImageFormatChannels(color_type()) != m_params.GetFormatChannels())
      << "TextureObject initialized with different FORMAT than "
      << "incoming image. Use Initialize() for a different image type.";

    TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(DoGetImageType(color_type()) != type)
      << "TextureObject initialized with different IMAGE TYPE than "
      << "incoming image. Use Initialize() for a different image type.";
    
    TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(DoGetAlignment(color_type()) != alignment)
      << "TextureObject initialized with different ALIGNMENT than "
      << "incoming image. Use Initialize() for a different image type.";

    // -----------------------------------------------------------------------
    // update the image

    glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
    TLOC_ASSERT(gl::Error().Succeeded(), "Error in glPixelStorei()");

    Bind();
    auto res = f_texture_object::
      GL_TexImage(target, internalFormat, a_image.GetDimensions(), 
                  format, type, (void*)a_image.get().get());
    TLOC_LOG_GFX_ERR_NO_FILENAME_IF(res == false) << "Error with glTexImage2D()";

    if (res == false) { return ErrorFailure; }

    if (m_params.IsAutoGenMipMaps())
    {
      glGenerateMipmap(target);
      TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(gl::Error().Failed())
        << "Error in glGenerateMipmap() for Texture with handle(" << GetHandle()
        << ") - Is texture valid and power of two?";
    }

    UpdateParameters();

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TEXTURE_OBJECT_TEMPS>
  void
    TextureObject_T<TEXTURE_OBJECT_PARAMS>::
    UpdateParameters() const
  {
    const p_texture_object::target::value_type 
      texType = GetTargetType();

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, m_params.GetWrap_S());
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, m_params.GetWrap_T());

    if (texType == p_texture_object::target::Tex3D::s_glParamName)
    { glTexParameteri(texType, GL_TEXTURE_WRAP_R, m_params.GetWrap_R()); }

    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, m_params.GetMagFilter());
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, m_params.GetMinFilter());
    TLOC_ASSERT(gl::Error().Succeeded(), "Error in glTexParameteri()");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TEXTURE_OBJECT_TEMPS>
  TEXTURE_OBJECT_TYPE::error_type
    TextureObject_T<TEXTURE_OBJECT_PARAMS>::
    ReserveTextureUnit()
  {
    using namespace gl::texture_units;
    return image_units::Reserve(m_reservedTexImageUnit);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TEXTURE_OBJECT_TEMPS>
  void
    TextureObject_T<TEXTURE_OBJECT_PARAMS>::
    ReleaseTextureUnit()
  {
    if (HasReservedTextureUnit())
    {
      using namespace gl::texture_units;
      image_units::Release(m_reservedTexImageUnit);
      m_reservedTexImageUnit = -1;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TEXTURE_OBJECT_TEMPS>
  bool
    TextureObject_T<TEXTURE_OBJECT_PARAMS>::
    HasReservedTextureUnit() const
  {
    return m_reservedTexImageUnit != -1;
  }

  // -----------------------------------------------------------------------

  namespace f_texture_object {

    using namespace p_texture_object;

    template <typename T_Dim, typename T_ColorType, typename T_Storage>
    bool GL_TexImage(const gfx_med::Image_T<T_Dim, T_ColorType, T_Storage>& a_image)
    {
      using gfx_t::gl_int;
      typedef gfx_med::Image_T<T_Dim, T_ColorType, T_Storage>     image_type;
      typedef typename image_type::pixel_container_type           pix_cont_type;
      typedef typename image_type::color_type                     color_type;

      const gl_int target                    = DoGetTarget(a_image);
      const gl_int internalFormat            = DoGetInternalImageFormat(color_type());
      const size_type internalFormatChannels = DoGetImageFormatChannels(color_type());
      const gl_int format                    = DoGetImageFormat(color_type());
      const size_type formatChannels         = DoGetImageFormatChannels(color_type());
      const gl_int type                      = DoGetImageType(color_type());

      return GL_TexImage(target, internal_format, a_image.GetDimensions(), 
                         format, type, a_image.get().get());
    }

    bool GL_TexImage(target::value_type           a_target,
                     internal_format::value_type  a_internalFormat,
                     gfx_t::Dimension2            a_dim,
                     format::value_type           a_format,
                     type::value_type             a_type,
                     void*                        a_data)
    {
      using core_utils::CastNumber;

      glTexImage2D(a_target, 0, a_internalFormat,
                   CastNumber<GLsizei>(a_dim[0]), 
                   CastNumber<GLsizei>(a_dim[1]),
                   0, a_format, a_type, a_data);
      return gl::Error().Succeeded();
    }

    bool GL_TexImage(target::value_type           a_target,
                     internal_format::value_type  a_internalFormat,
                     gfx_t::Dimension3            a_dim,
                     format::value_type           a_format,
                     type::value_type             a_type,
                     void*                        a_data)
    {
      using core_utils::CastNumber;

      glTexImage3D(a_target, 0, a_internalFormat,
                   CastNumber<GLsizei>(a_dim[0]), 
                   CastNumber<GLsizei>(a_dim[1]),
                   CastNumber<GLsizei>(a_dim[2]),
                   0, a_format, a_type, a_data);
      return gl::Error().Succeeded();
    }
  };

  // ///////////////////////////////////////////////////////////////////////
  // explicit instantiations

  using namespace p_texture_object::target;

  template class TextureObject_T<Tex2D>;
  template class TextureObject_T<Tex3D>;
  template class TextureObject_T<Tex2DShadow>;

};};};

// -----------------------------------------------------------------------
// explicit instantiations for

using namespace tloc::gfx_gl;
using namespace tloc::gfx_med;
using namespace tloc::gfx_gl::f_texture_object;

#define TLOC_EXPLICITLY_INSTANTIATE_IMAGE(_imageType_)\
template TextureObject::error_type TextureObject::Initialize(const _imageType_&);\
template TextureObject::error_type TextureObject::Update(const _imageType_&) const;\
\
template TextureObject3D::error_type TextureObject3D::Initialize(const _imageType_&);\
template TextureObject3D::error_type TextureObject3D::Update(const _imageType_&) const;\
\
template TextureObjectShadow::error_type TextureObjectShadow::Initialize(const _imageType_&);\
template TextureObjectShadow::error_type TextureObjectShadow::Update(const _imageType_&) const;\
\
bool GL_TexImage(const _imageType_&)

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(Image);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_rgb);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_rg);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_r);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_u16_rgba);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_u16_rgb);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_u16_rg);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_u16_r);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_f32_r);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_stream_rgba);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_stream_rgb);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_stream_rg);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_stream_r);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_stream_u16_rgba);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_stream_u16_rgb);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_stream_u16_rg);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_stream_u16_r);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_stream_f32_r);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(Image3D);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_rgb);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_rg);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_r);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_u16_rgba);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_u16_rgb);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_u16_rg);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_u16_r);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_f32_r);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_stream_rgba);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_stream_rgb);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_stream_rg);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_stream_r);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_stream_u16_rgba);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_stream_u16_rgb);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_stream_u16_rg);
TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_stream_u16_r);

TLOC_EXPLICITLY_INSTANTIATE_IMAGE(image_3d_stream_f32_r);

//------------------------------------------------------------------------
// Explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_gl;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(TextureObject);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(TextureObject);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(TextureObject3D);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(TextureObject3D);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(TextureObjectShadow);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(TextureObjectShadow);