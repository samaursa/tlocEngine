#include "tlocTextureObject.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/utilities/tlocType.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

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

#elif defined (TLOC_OS_IPHONE) // TODO: Change to TLOC_GFX_PLATFORM_GL_ES

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

    const ifvt internal_format::Red::s_glParamName            = GL_RED;
    const ifvt internal_format::RG::s_glParamName             = GL_RG;
    const ifvt internal_format::RGB::s_glParamName            = GL_RGB;
    const ifvt internal_format::RGBA::s_glParamName           = GL_RGBA;
    const ifvt internal_format::DepthComponent::s_glParamName = GL_DEPTH_COMPONENT;
    const ifvt internal_format::DepthStencil::s_glParamName   = GL_DEPTH_STENCIL;

#elif defined (TLOC_OS_IPHONE) // TODO: Change to TLOC_GFX_PLATFORM_GL_ES

    using namespace wrap_technique;
    using namespace filter;

    typedef wrap_technique::value_type  wvt;
    typedef filter::value_type          fvt;

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

    const ifvt internal_format::Red::s_glParamName            = GL_RED;
    const ifvt internal_format::RG::s_glParamName             = GL_RG;
    const ifvt internal_format::RGB::s_glParamName            = GL_RGB;
    const ifvt internal_format::RGBA::s_glParamName           = GL_RGBA;
    const ifvt internal_format::DepthComponent::s_glParamName = GL_DEPTH_COMPONENT;
    const ifvt internal_format::DepthStencil::s_glParamName   = GL_DEPTH_STENCIL;

    const wvt ClampToBorder::s_glParamName = 0;

#else
# error "WIP"
#endif

  };

  // ///////////////////////////////////////////////////////////////////////
  // TextureObject::Params

  TextureObject::Params::
    Params()
  {
    using namespace p_texture_object;
    using namespace p_texture_object::wrap_technique;
    using namespace p_texture_object::filter;
    using namespace p_texture_object::target;

    // defaults
    Wrap_S<ClampToEdge>().Wrap_T<ClampToEdge>();
    MinFilter<Linear>().MagFilter<Linear>();
    TextureType<Tex2D>();
    InternalFormat<internal_format::RGBA>();
    Format<format::RGBA>();
  }

  //////////////////////////////////////////////////////////////////////////
  // TextureObject

  typedef TextureObject::error_type   error_type;

  TextureObject::
    TextureObject(const Params& a_params)
    : m_texImageUnit(-1)
    , m_params(a_params)
    , m_dim(0, 0)
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
    Bind() const
  {
    object_handle handle = GetHandle();
    glBindTexture(m_params.GetTextureType(), handle);

    TLOC_ASSERT(gl::Error().Succeeded(), "Error in glBindTexture()");
    return ErrorSuccess;
  }

  error_type
    TextureObject::
    Initialize(const image_type& a_image)
  {
    image_type::pixel_container_type cont = a_image.GetPixels();

    // We do NOT need the original image because glTexImage2D copies the image
    m_dim = a_image.GetDimensions();

    Bind();
    glTexImage2D(m_params.GetTextureType(), 0, m_params.GetInternalFormat(),
      core_utils::CastNumber<GLsizei>(m_dim[0]),
      core_utils::CastNumber<GLsizei>(m_dim[1]),
      0, m_params.GetFormat(), GL_UNSIGNED_BYTE, &*a_image.GetPixels().begin() );
    TLOC_ASSERT(gl::Error().Succeeded(), "Error in glBindTexture()");

    Update();

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
    Update()
  {
    texture_type texType = m_params.GetTextureType();

    TLOC_ASSERT(texType != GL_NONE, "Update parameters on a GL_NONE texture");
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, m_params.GetWrap_S());
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, m_params.GetWrap_T());
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, m_params.GetMagFilter());
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, m_params.GetMinFilter());
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template class core::smart_ptr::SharedPtr<TextureObject>;

};};};