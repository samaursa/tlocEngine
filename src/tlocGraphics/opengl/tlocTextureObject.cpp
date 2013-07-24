#include "tlocTextureObject.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/utilities/tlocType.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_texture_object {
    namespace target {

#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL

      const enum_type Tex1D::s_glParamName = GL_TEXTURE_1D;
      const enum_type Tex2D::s_glParamName = GL_TEXTURE_2D;
      const enum_type Tex3D::s_glParamName = GL_TEXTURE_3D;

      const enum_type TexRectangle::s_glParamName     = GL_TEXTURE_RECTANGLE;
      const enum_type TexCubeMap::s_glParamName       = GL_TEXTURE_CUBE_MAP;
      const enum_type TexBuffer::s_glParamName        = GL_TEXTURE_BUFFER;
      const enum_type Tex2DMultiSample::s_glParamName = GL_TEXTURE_2D_MULTISAMPLE;

      const enum_type Tex1DArray::s_glParamName = GL_TEXTURE_1D_ARRAY;
      const enum_type Tex2DArray::s_glParamName = GL_TEXTURE_2D_ARRAY;
      const enum_type TexCubeMapArray::s_glParamName = GL_TEXTURE_CUBE_MAP_ARRAY;
      const enum_type
        Tex2DMultiSampleArray::s_glParamName = GL_TEXTURE_2D_MULTISAMPLE_ARRAY;

#elif defined (TLOC_OS_IPHONE) // TODO: Change to TLOC_GFX_PLATFORM_GL_ES

      const enum_type Tex2D::s_glParamName      = GL_TEXTURE_2D;
      const enum_type TexCubeMap::s_glParamName = GL_TEXTURE_CUBE_MAP;

      const enum_type Tex1D::s_glParamName = 0;
      const enum_type Tex3D::s_glParamName = 0;

      const enum_type TexRectangle::s_glParamName     = 0;

      const enum_type TexBuffer::s_glParamName        = 0;
      const enum_type Tex2DMultiSample::s_glParamName = 0;

      const enum_type Tex1DArray::s_glParamName = 0;
      const enum_type Tex2DArray::s_glParamName = 0;
      const enum_type TexCubeMapArray::s_glParamName = 0;
      const enum_type Tex2DMultiSampleArray::s_glParamName = 0;

#else
# error "WIP"
#endif

    };
  };

  //////////////////////////////////////////////////////////////////////////
  // TextureObject

  typedef TextureObject::error_type   error_type;

  TextureObject::
    TextureObject()
    : m_texType(GL_NONE)
  {
    object_handle handle;
    glGenTextures(1, &handle);
    SetHandle(handle);
  }

  TextureObject::
    ~TextureObject()
  {
    object_handle handle = GetHandle();
    glDeleteTextures(1, &handle);
  }

  error_type TextureObject::
    DoBind(texture_type a_texType)
  {
    m_texType = a_texType;
    object_handle handle = GetHandle();
    glBindTexture(a_texType, handle);

    TLOC_ASSERT(gl::Error().Succeeded(), "Error in glBindTexture()");
    return ErrorSuccess;
  }

  error_type TextureObject::
    Initialize(const image_type& a_image)
  {
    image_type::pixel_container_type cont = a_image.GetPixels();

    Bind<p_texture_object::target::Tex2D>();
    glTexImage2D(m_texType, 0, GL_RGBA,
      core_utils::CastNumber<GLsizei, size_type>(a_image.GetWidth()),
      core_utils::CastNumber<GLsizei, size_type>(a_image.GetHeight()),
      0, GL_RGBA, GL_UNSIGNED_BYTE, &*a_image.GetPixels().begin() );

    glTexParameteri(m_texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(m_texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return ErrorSuccess;
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template class core::smart_ptr::SharedPtr<TextureObject>;

};};};