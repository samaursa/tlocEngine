// Put this here first to avoid abs function ambiguity problems
#include <3rdParty/Graphics/lodepng/lodepng.h>
#include <3rdParty/Graphics/lodepng/lodepng.c>
#include <3rdParty/Graphics/nanojpeg/ujpeg.h>

#include "tlocImageLoader.h"

#include <tlocCore/io/tlocFileIO.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocGraphics/error/tlocErrorTypes.h>

TLOC_DEFINE_THIS_FILE_NAME();

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

#define IMAGE_LOADER_TEMP   typename T_DerivedClass, tl_int T_Channels
#define IMAGE_LOADER_PARAMS T_DerivedClass, T_Channels
#define IMAGE_LOADER_TYPE typename ImageLoader_TI<IMAGE_LOADER_PARAMS>

  template <IMAGE_LOADER_TEMP>
  IMAGE_LOADER_TYPE::error_type
    ImageLoader_TI<IMAGE_LOADER_PARAMS>::Load(const path_type& a_path)
  {
    return static_cast<derived_type*>(this)->DoLoad(a_path);
  }

  template <IMAGE_LOADER_TEMP>
  IMAGE_LOADER_TYPE::error_type ImageLoader_TI<IMAGE_LOADER_PARAMS>::
    DoLoadImageFromMemory(const_color_ptr a_buffer, dimention_type a_dim,
                          size_type a_channels)
  {
    m_image = core_sptr::MakeShared<image_ptr::value_type>();
    return m_image->Load(a_buffer, a_dim, a_channels);
  }

  //------------------------------------------------------------------------
  // ImageLoaderPng

  ImageLoaderPng::error_type 
    ImageLoaderPng::
    DoLoad(const path_type& a_path)
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

    core_sptr::VirtualPtr<uchar8> imgPtr(image);

    if (lodePngErr)
    {
      TLOC_LOG_GFX_ERR_FILENAME_ONLY() 
        << "lodepng_decode32 failed: " << lodepng_error_text(lodePngErr);
      res = TLOC_ERROR(graphics::error::error_image_decoding);
    }
    else
    {
      dimention_type dim = core_ds::MakeTuple(width, height);
      res = DoLoadImageFromMemory(imgPtr, dim, 4);
    }

    free(image);

    return res;
  }

  //------------------------------------------------------------------------
  // ImageLoaderPng

  ImageLoaderJpeg::error_type 
    ImageLoaderJpeg::
    DoLoad(const path_type& a_path)
  {
    String fileCont;

    error_type res = DoLoadFromFile(a_path, fileCont);

    if (res == common_error_types::error_failure)
    { return res; }

    uJPEG decoder;
    decoder.decode(fileCont.c_str(), fileCont.length());

    if (decoder.isValid() == false)
    {
      TLOC_LOG_GFX_ERR_FILENAME_ONLY() 
        << "nanojpeg decoder failed: " << decoder.getError();
      res = TLOC_ERROR(graphics::error::error_image_decoding);
    }
    else
    {
      core_sptr::VirtualPtr<const uchar8> imgPtr(decoder.getImage());

      dimension_type dim = 
        core_ds::MakeTuple(decoder.getWidth(), decoder.getHeight());

      if (decoder.isColor())
      { res = DoLoadImageFromMemory(imgPtr, dim, 3); }
      else
      { 
        TLOC_LOG_GFX_ERR_FILENAME_ONLY() << "Monochromatic JPEGs not suported";
        res = TLOC_ERROR(gfx_err::error_image_invalid_channels);
      }
    }

    return res;
  }

  //------------------------------------------------------------------------
  // Explicit instantiation for ImageLoader

  template class ImageLoader_TI<ImageLoaderPng, 4>;
  template class ImageLoader_TI<ImageLoaderJpeg, 3>;

  // -----------------------------------------------------------------------

  namespace f_image_loader {

    core_err::Error
      SaveImage(const Image& a_imgToWrite,
                const core_io::Path& a_path)
    {
      const uchar8* buffer = reinterpret_cast<const uchar8*>(a_imgToWrite.get().get());

      tl_uint outSize;
      uchar8* encodedBuffer = nullptr;

      lodepng_encode32(&encodedBuffer, &outSize, 
                       buffer, a_imgToWrite.GetWidth(), a_imgToWrite.GetHeight());

      if (buffer == nullptr)
      { 
        TLOC_LOG_GFX_ERR_FILENAME_ONLY() << "Failed to encode image to PNG32";
        return ErrorFailure;
      }

      core_io::FileIO_WriteB file(a_path);
      auto err = file.Open();
      if (err == ErrorSuccess)
      { err = file.Write((char8*)encodedBuffer, outSize); }

      return err;
    }

    core::Pair<core_t::Any, image_type>
      LoadImage(const core_io::Path& a_imagePath)
    {
      auto_cref ext = a_imagePath.GetExtension();
      if (ext.compare("jpg") == 0 || ext.compare("jpeg") == 0)
      {
        ImageLoaderJpeg il;
        auto err = il.Load(a_imagePath);
        if (err == ErrorSuccess)
        { return core::MakePair(il.GetImage(), k_image_jpeg); }

        TLOC_LOG_GFX_ERR_FILENAME_ONLY() << "Error loading JPEG image: " << err;
      }
      else if (ext.compare("png") == 0)
      {
        ImageLoaderPng il;
        auto err = il.Load(a_imagePath);
        if (err == ErrorSuccess)
        { return core::MakePair(il.GetImage(), k_image_png); }

        TLOC_LOG_GFX_ERR_FILENAME_ONLY() << "Error loading PNG image: " << err;
      }
      else
      {
        TLOC_LOG_GFX_ERR_FILENAME_ONLY() << "Unsupported image type: " <<
          a_imagePath;
      }

      return core::MakePair(core_t::Any(), k_image_unsupported);
    }

  };

};};};