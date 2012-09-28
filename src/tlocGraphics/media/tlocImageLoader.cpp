#include "tlocImageLoader.h"

#include <tlocCore/io/tlocFileIO.h>

#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace media {

  namespace
  {
    typedef ImageLoaderPng::error_type   error_type;
    typedef ImageLoaderPng::path_type    path_type;

    error_type DoLoadFromFile(const path_type& a_path, core::String& a_out)
    {
      core::io::FileIO_ReadB imgFile(a_path);

      error_type res = imgFile.Open();
      if (res != common_error_types::error_success)
      { return res; }

      imgFile.GetContents(a_out);
      return common_error_types::error_success;
    }
  };

#define IMAGE_LOADER_TEMP   typename T_DerivedClass
#define IMAGE_LOADER_PARAMS T_DerivedClass
#define IMAGE_LOADER_TYPE typename ImageLoader<IMAGE_LOADER_PARAMS>

  template <IMAGE_LOADER_TEMP>
  IMAGE_LOADER_TYPE::error_type
    ImageLoader<IMAGE_LOADER_PARAMS>::Load(const path_type& a_path)
  {
    return static_cast<derived_type*>(this)->Load(a_path);
  }

  template <IMAGE_LOADER_TEMP>
  IMAGE_LOADER_TYPE::error_type ImageLoader<IMAGE_LOADER_PARAMS>::
    DoLoadImageFromMemory(const char* a_buffer, size_type a_length)
  {
    return m_image.LoadFromMemory(a_buffer, a_length);
  }

  //------------------------------------------------------------------------
  // ImageLoaderPng

#include <3rdParty/Graphics/lodepng/lodepng.h>
#include <3rdParty/Graphics/lodepng/lodepng.c>

  ImageLoaderPng::error_type ImageLoaderPng::Load(const path_type& a_path)
  {
    core::String fileCont;

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
      res = graphics::error::error_image_decoding;
      goto gt_cleanup_and_return;
    }

    res = DoLoadImageFromMemory((const char*)image, width * height * 32);

gt_cleanup_and_return:
    free(image);

    return res;
  }

  //------------------------------------------------------------------------
  // Explicit instantiation for ImageLoader

  template class ImageLoader<ImageLoaderPng>;

};};};