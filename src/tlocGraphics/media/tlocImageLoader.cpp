// Put this here first to avoid abs function ambiguity problems
#include <3rdParty/Graphics/lodepng/lodepng.h>
#include <3rdParty/Graphics/lodepng/lodepng.c>

#include "tlocImageLoader.h"

#include <tlocCore/io/tlocFileIO.h>

#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace media {

  using core::string::String;

  namespace
  {
    typedef ImageLoaderPng::error_type      error_type;
    typedef ImageLoaderPng::path_type       path_type;

    error_type DoLoadFromFile(const path_type& a_path, String& a_out)
    {
      core::io::FileIO_ReadB imgFile(a_path);

      error_type res = imgFile.Open();
      if (res != common_error_types::error_success)
      { return res; }

      imgFile.GetContents(a_out);
      return TLOC_ERROR(common_error_types::error_success);
    }
  };

#define IMAGE_LOADER_TEMP   typename T_DerivedClass
#define IMAGE_LOADER_PARAMS T_DerivedClass
#define IMAGE_LOADER_TYPE typename ImageLoader_TI<IMAGE_LOADER_PARAMS>

  template <IMAGE_LOADER_TEMP>
  IMAGE_LOADER_TYPE::error_type
    ImageLoader_TI<IMAGE_LOADER_PARAMS>::Load(const path_type& a_path)
  {
    return static_cast<derived_type*>(this)->DoLoad(a_path);
  }

  template <IMAGE_LOADER_TEMP>
  IMAGE_LOADER_TYPE::error_type ImageLoader_TI<IMAGE_LOADER_PARAMS>::
    DoLoadImageFromMemory(const uchar8* a_buffer, dimention_type a_dim,
                          size_type a_channels)
  {
    return m_image.LoadFromMemory(a_buffer, a_dim, a_channels);
  }

  //------------------------------------------------------------------------
  // ImageLoaderPng

  ImageLoaderPng::error_type ImageLoaderPng::DoLoad(const path_type& a_path)
  {
    String fileCont;

    error_type res = DoLoadFromFile(a_path, fileCont);

    if (res == common_error_types::error_failure)
    { return res; }

    unsigned char* image;
    unsigned int width, height;

    tl_uint lodePngErr = lodepng_decode32(&image, &width, &height,
                                          (unsigned const char*)fileCont.c_str(),
                                          (u32)fileCont.length());
    if (lodePngErr)
    {
      // LOG: Take log from lodepng_error_text(lodePngErr);
      res = TLOC_ERROR(graphics::error::error_image_decoding);
    }
    else
    {
      res = DoLoadImageFromMemory(image, dimention_type(width, height), 4);
    }

    free(image);

    return res;
  }

  //------------------------------------------------------------------------
  // Explicit instantiation for ImageLoader

  template class ImageLoader_TI<ImageLoaderPng>;

};};};