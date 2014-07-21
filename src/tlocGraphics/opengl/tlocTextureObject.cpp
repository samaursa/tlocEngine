#include "tlocTextureObject.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_texture_object {
    namespace target {

#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL

      const value_type Auto::s_glParamName = GL_NONE;
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

#elif defined (TLOC_OS_IPHONE) // TODO: Change to TLOC_GFX_PLATFORM_GL_ES

      const value_type Auto::s_glParamName = GL_NONE;
      const value_type Tex2D::s_glParamName      = GL_TEXTURE_2D;
      const value_type TexCubeMap::s_glParamName = GL_TEXTURE_CUBE_MAP;

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

    using namespace wrap_technique;
    using namespace filter;
    using namespace format;
    using namespace internal_format;

    typedef wrap_technique::value_type  wvt;
    typedef filter::value_type          fvt;
    typedef format::value_type          formvt;
    typedef internal_format::value_type ifvt;
    typedef type::value_type            tvt;
    typedef alignment::value_type       avt;

    const wvt ClampToEdge::s_glParamName       = GL_CLAMP_TO_EDGE;
    const wvt ClampToBorder::s_glParamName     = GL_CLAMP_TO_BORDER;
    const wvt MirroredRepeat::s_glParamName    = GL_CLAMP_TO_EDGE;
    const wvt Repeat::s_glParamName            = GL_CLAMP_TO_EDGE;
    const wvt MirrorClampToEdge::s_glParamName = GL_CLAMP_TO_EDGE;

    const fvt Nearest::s_glParamName              = GL_NEAREST;
    const fvt Linear::s_glParamName               = GL_LINEAR;
    const fvt NearestMipmapNearest::s_glParamName = GL_NEAREST_MIPMAP_NEAREST;
    const fvt LinearMipmapNearest::s_glParamName  = GL_LINEAR_MIPMAP_NEAREST;
    const fvt NearestMipmapLinear::s_glParamName  = GL_NEAREST_MIPMAP_LINEAR;
    const fvt LinearMipmapLinear::s_glParamName   = GL_LINEAR_MIPMAP_LINEAR;

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

    using namespace wrap_technique;
    using namespace filter;
    using namespace format;
    using namespace internal_format;

    typedef wrap_technique::value_type  wvt;
    typedef filter::value_type          fvt;
    typedef format::value_type          formvt;
    typedef internal_format::value_type ifvt;
    typedef type::value_type            tvt;
    typedef alignment::value_type       avt;

    const wvt ClampToEdge::s_glParamName       = GL_CLAMP_TO_EDGE;
    const wvt MirroredRepeat::s_glParamName    = GL_CLAMP_TO_EDGE;
    const wvt Repeat::s_glParamName            = GL_CLAMP_TO_EDGE;
    const wvt MirrorClampToEdge::s_glParamName = GL_CLAMP_TO_EDGE;

    const fvt Nearest::s_glParamName              = GL_NEAREST;
    const fvt Linear::s_glParamName               = GL_LINEAR;
    const fvt NearestMipmapNearest::s_glParamName = GL_NEAREST_MIPMAP_NEAREST;
    const fvt LinearMipmapNearest::s_glParamName  = GL_LINEAR_MIPMAP_NEAREST;
    const fvt NearestMipmapLinear::s_glParamName  = GL_NEAREST_MIPMAP_LINEAR;
    const fvt LinearMipmapLinear::s_glParamName   = GL_LINEAR_MIPMAP_LINEAR;

    const formvt format::Auto::s_glParamName           = GL_NONE;
    const formvt format::RGB::s_glParamName            = GL_RGB;
    const formvt format::RGBA::s_glParamName           = GL_RGBA;
    const formvt format::BGRA::s_glParamName           = GL_BGRA;
    const formvt format::StencilIndex::s_glParamName   = GL_STENCIL_INDEX;
    const formvt format::DepthComponent::s_glParamName = GL_DEPTH_COMPONENT;

    const size_type format::Auto::s_glChannels           = 0;
    const size_type format::RGB::s_glChannels            = 3;
    const size_type format::RGBA::s_glChannels           = 4;
    const size_type format::BGRA::s_glChannels           = 4;
    const size_type format::StencilIndex::s_glChannels   = 1;
    const size_type format::DepthComponent::s_glChannels = 1;

    const ifvt internal_format::Auto::s_glParamName           = GL_NONE;
    const ifvt internal_format::RGB::s_glParamName            = GL_RGB;
    const ifvt internal_format::RGBA::s_glParamName           = GL_RGBA;
    const ifvt internal_format::DepthComponent::s_glParamName = GL_DEPTH_COMPONENT;

    const size_type internal_format::Auto::s_glChannels           = 0;
    const size_type internal_format::RGB::s_glChannels            = 3;
    const size_type internal_format::RGBA::s_glChannels           = 4;
    const size_type internal_format::DepthComponent::s_glChannels = 1;

    const wvt ClampToBorder::s_glParamName = 0;

    const formvt format::Red::s_glParamName           = 0;
    const formvt format::RG::s_glParamName            = 0;
    const formvt format::BGR::s_glParamName           = 0;
    const formvt format::RedInteger::s_glParamName    = 0;
    const formvt format::RGInteger::s_glParamName     = 0;
    const formvt format::RGBInteger::s_glParamName    = 0;
    const formvt format::BGRInteger::s_glParamName    = 0;
    const formvt format::RGBAInteger::s_glParamName   = 0;
    const formvt format::BGRAInteger::s_glParamName   = 0;

    const size_type format::Red::s_glChannels            = 0;
    const size_type format::RG::s_glChannels             = 0;
    const size_type format::BGR::s_glChannels            = 0;
    const size_type format::RedInteger::s_glChannels     = 0;
    const size_type format::RGInteger::s_glChannels      = 0;
    const size_type format::RGBInteger::s_glChannels     = 0;
    const size_type format::BGRInteger::s_glChannels     = 0;
    const size_type format::RGBAInteger::s_glChannels    = 0;
    const size_type format::BGRAInteger::s_glChannels    = 0;

    const ifvt internal_format::Red::s_glParamName  = 0;
    const ifvt internal_format::RG::s_glParamName   = 0;
    const ifvt internal_format::DepthStencil::s_glParamName   = 0;

    const size_type internal_format::Red::s_glChannels            = 0;
    const size_type internal_format::RG::s_glChannels             = 0;
    const size_type internal_format::DepthStencil::s_glChannels   = 0;

    const tvt  type::Auto::s_glParamName                      = GL_NONE;
    const tvt  type::UnsignedByte::s_glParamName              = GL_UNSIGNED_BYTE;
    const tvt  type::Byte::s_glParamName                      = 0;
    const tvt  type::UnsignedShort::s_glParamName             = GL_UNSIGNED_SHORT;
    const tvt  type::Short::s_glParamName                     = 0;
    const tvt  type::UnsignedInt::s_glParamName               = 0;
    const tvt  type::Int::s_glParamName                       = 0;
    const tvt  type::Float::s_glParamName                     = 0;
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

  };

  namespace {

    // -----------------------------------------------------------------------
    // Return the 'target' of image (see glTexImage2D doc)

    template <typename T_ColorType, typename T_Storage>
    gfx_t::gl_int
      DoGetTarget(const gfx_med::Image_T<T_ColorType, T_Storage>&)
    { return p_texture_object::target::Tex2D::s_glParamName; }

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

  TextureObject::Params::
    Params()
    : m_internalFormatChannels(0)
    , m_formatChannels(0)
    , m_autoGenMipMaps(true)
  {
    using namespace p_texture_object;
    using namespace p_texture_object::wrap_technique;
    using namespace p_texture_object::filter;
    using namespace p_texture_object::target;
    using namespace p_texture_object::alignment;

    // defaults
    Wrap_S<ClampToEdge>().Wrap_T<ClampToEdge>();
    MinFilter<Linear>().MagFilter<Linear>();
    TextureType<target::Auto>();
    InternalFormat<internal_format::Auto>();
    Format<format::Auto>();
    Type<type::Auto>();
    Alignment<alignment::Auto>();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TextureObject::Params::
    AutoGenerateMipMaps(bool a_autoGenMipMaps)
  { m_autoGenMipMaps = a_autoGenMipMaps; }

  //////////////////////////////////////////////////////////////////////////
  // TextureObject

  typedef TextureObject::error_type   error_type;

  TextureObject::
    TextureObject(const Params& a_params)
    : m_texImageUnit(-1)
    , m_params(a_params)
    , m_dim(0)
  {
    object_handle handle;
    glGenTextures(1, &handle);
    SetHandle(handle);
  }

  TextureObject::
    ~TextureObject()
  {
    if (IsLastRef())
    {
      object_handle handle = GetHandle();
      if (IsActive())
      { Deactivate(); }
      glDeleteTextures(1, &handle);
    }
  }

  error_type
    TextureObject::
    Bind(texture_type a_target) const
  {
    object_handle handle = GetHandle();

    glBindTexture(a_target, handle);
    TLOC_ASSERT(gl::Error().Succeeded(), "Error in glBindTexture()");
    
    return ErrorSuccess;
  }

  template <typename T_ColorType, typename T_Storage>
  error_type
    TextureObject::
    Initialize(const gfx_med::Image_T<T_ColorType, T_Storage>& a_image)
  {
    using gfx_t::gl_int;
    typedef gfx_med::Image_T<T_ColorType>                       image_type;
    typedef typename image_type::pixel_container_type           pix_cont_type;
    typedef typename image_type::color_type                     color_type;

    // We do NOT need the original image because glTexImage2D copies the image
    m_dim[0] = core_utils::CastNumber<dimension_type::value_type>(a_image.GetDimensions()[0]);
    m_dim[1] = core_utils::CastNumber<dimension_type::value_type>(a_image.GetDimensions()[1]);

    const gl_int target = m_params.GetTextureType() == 
      p_texture_object::target::Auto::s_glParamName
      ? DoGetTarget(a_image)
      : m_params.GetTextureType();

    const gl_int internalFormat = m_params.GetInternalFormat() == 
      p_texture_object::internal_format::Auto::s_glParamName
      ? DoGetInternalImageFormat(color_type())
      : m_params.GetInternalFormat();
    const size_type internalFormatChannels = m_params.GetInternalFormat() ==
      p_texture_object::format::Auto::s_glParamName
      ? DoGetImageFormatChannels(color_type()) : m_params.GetInternalFormatChannels();

    const gl_int format = m_params.GetFormat() ==
      p_texture_object::format::Auto::s_glParamName
      ? DoGetImageFormat(color_type())
      : m_params.GetFormat();
    const size_type formatChannels = m_params.GetFormat() ==
      p_texture_object::format::Auto::s_glParamName
      ? DoGetImageFormatChannels(color_type()) : m_params.GetFormatChannels();

    const gl_int type   = m_params.GetType() == 
      p_texture_object::type::Auto::s_glParamName
      ?  DoGetImageType(color_type())
      : m_params.GetType();
    const gl_int alignment = m_params.GetAlignment() ==
      p_texture_object::alignment::Auto::s_glParamName
      ? DoGetAlignment(color_type())
      : m_params.GetAlignment();

    m_params.m_textureType = target;
    m_params.m_internalFormat = internalFormat;
    m_params.m_internalFormatChannels = internalFormatChannels;
    m_params.m_format = format;
    m_params.m_formatChannels = formatChannels;
    m_params.m_type = type;
    m_params.m_alignment = alignment;

    return Update(a_image);
  }

  template <typename T_ColorType, typename T_Storage>
  error_type
    TextureObject::
    Update(const gfx_med::Image_T<T_ColorType, T_Storage>& a_image) const
  {
    TLOC_ASSERT(a_image.GetWidth() == m_dim[0] && 
                a_image.GetHeight() == m_dim[1], "Image dimensions do not match."
                " Use Initialize() for a different image.");

    using gfx_t::gl_int;
    typedef gfx_med::Image_T<T_ColorType>                       image_type;
    typedef typename image_type::pixel_container_type           pix_cont_type;
    typedef typename image_type::color_type                     color_type;

    const gl_int target = m_params.GetTextureType();
    const gl_int internalFormat = m_params.GetInternalFormat();
    const gl_int format = m_params.GetFormat();
    const gl_int type   = m_params.GetType();
    const gl_int alignment = m_params.GetAlignment();

    // -----------------------------------------------------------------------
    // issue warnings for inconsistencies in image type

    TLOC_LOG_GFX_WARN_IF(DoGetTarget(a_image) != target) 
      << "TextureObject initialized with different TARGET than "
      << "incoming image. Use Initialize() for a different image type.";

    // NOTE: no need to warn against 'internal format' as it is frequently 
    // different

    TLOC_LOG_GFX_WARN_IF(DoGetImageFormatChannels(color_type()) != 
                         m_params.GetFormatChannels()) 
      << "TextureObject initialized with different FORMAT than "
      << "incoming image. Use Initialize() for a different image type.";

    TLOC_LOG_GFX_WARN_IF(DoGetImageType(color_type()) != type) 
      << "TextureObject initialized with different IMAGE TYPE than "
      << "incoming image. Use Initialize() for a different image type.";
    
    TLOC_LOG_GFX_WARN_IF(DoGetAlignment(color_type()) != alignment) 
      << "TextureObject initialized with different ALIGNMENT than "
      << "incoming image. Use Initialize() for a different image type.";

    // -----------------------------------------------------------------------
    // update the image

    glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
    TLOC_ASSERT(gl::Error().Succeeded(), "Error in glPixelStorei()");

    Bind(target);
    glTexImage2D(target, 0, internalFormat,
                 core_utils::CastNumber<GLsizei>(m_dim[0]),
                 core_utils::CastNumber<GLsizei>(m_dim[1]),
                 0, format, type, a_image.get().get() );
    TLOC_ASSERT(gl::Error().Succeeded(), "Error in glTexImage2D()");

    if (m_params.IsAutoGenMipMaps())
    {
      glGenerateMipmap(m_params.GetTextureType());
      TLOC_LOG_GFX_WARN_IF(gl::Error().Failed())
        << "Error in glGenerateMipmap() for Texture with handle(" << GetHandle()
        << ") - Is texture valid and power of two?";
    }

    UpdateParameters();

    return ErrorSuccess;
  }

  error_type
    TextureObject::
    Activate()
  {
    if (IsActive())
    { return TLOC_ERROR(gfx_err::error_texture_object_already_activated); }

    texture_image_unit_type tUnit;
    error_type err = GetNextAvailableTextureImageUnit(tUnit);
    if (err == ErrorSuccess)
    {
      m_texImageUnit = tUnit;
      return ErrorSuccess;
    }

    return TLOC_ERROR(gfx_err::error_no_texture_units_available);
  }

  bool
    TextureObject::
    IsActive() const
  { return m_texImageUnit != -1; }

  error_type
    TextureObject::
    Deactivate()
  {
    if (IsActive())
    {
      RecycleTextureImageUnit(m_texImageUnit);
      m_texImageUnit = -1;

      return ErrorSuccess;
    }

    return TLOC_ERROR(error::error_texture_object_never_activated);
  }

  void
    TextureObject::
    UpdateParameters() const
  {
    texture_type texType = m_params.GetTextureType();

    TLOC_ASSERT(texType != GL_NONE, "Update parameters on a GL_NONE texture");
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, m_params.GetWrap_S());
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, m_params.GetWrap_T());
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, m_params.GetMagFilter());
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, m_params.GetMinFilter());
    TLOC_ASSERT(gl::Error().Succeeded(), "Error in glTexParameteri()");
  }

};};};

// -----------------------------------------------------------------------
// explicit instantiations for

using namespace tloc::gfx_gl;
using namespace tloc::gfx_med;

#define TLOC_EXPLICITLY_INSTANTIATE_IMAGE(_imageType_)\
template TextureObject::error_type TextureObject::Initialize(const _imageType_&);\
template TextureObject::error_type TextureObject::Update(const _imageType_&) const

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

//------------------------------------------------------------------------
// Explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_gl;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(TextureObject);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(TextureObject);