#ifndef TLOC_IMAGE_LOADER_H
#define TLOC_IMAGE_LOADER_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/error/tlocError.h>
#include <tlocCore/io/tlocPath.h>

#include <tlocGraphics/media/tlocImage.h>

namespace tloc { namespace graphics { namespace media {

  // ///////////////////////////////////////////////////////////////////////
  // ImageLoader_TI

  template <typename T_DerivedClass, tl_int T_Channels>
  class ImageLoader_TI
  {
    TLOC_STATIC_ASSERT(T_Channels == 3 || T_Channels == 4,
      Only_3_or_4_channel_images_are_supported_by_the_loaders);

  public:
    typedef T_DerivedClass            derived_type;
    typedef core::error::Error        error_type;
    typedef core::io::Path            path_type;
    typedef tl_size                   size_type;

    typedef typename Loki::Select<T_Channels == 4, 
      image_sptr, image_rgb_sptr>::Result             image_ptr;
    typedef typename image_ptr::value_type            image_type;

    typedef typename image_type::dimension_type       dimention_type;
    typedef typename image_type::const_color_ptr      const_color_ptr;

  public:
    error_type Load(const path_type& a_path);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(image_ptr, GetImage, m_image);

  protected:

    error_type DoLoadImageFromMemory(const_color_ptr a_buffer,
                                     dimention_type a_dim,
                                     size_type a_channels);
  private:
    image_ptr m_image;
  };

  // ///////////////////////////////////////////////////////////////////////
  // ImageLoaderPng

  class ImageLoaderPng 
    : public ImageLoader_TI<ImageLoaderPng, 4>
  {
  public:
    typedef ImageLoader_TI<ImageLoaderPng, 4>   base_type;

    friend base_type;
    typedef base_type::error_type           error_type;
    typedef base_type::path_type            path_type;
    typedef base_type::size_type            size_type;
    typedef base_type::dimention_type       dimension_type;

  protected:
    error_type  DoLoad(const path_type& a_path);

  };

  // ///////////////////////////////////////////////////////////////////////
  // ImageLoaderJpeg

  class ImageLoaderJpeg : public ImageLoader_TI<ImageLoaderJpeg, 3>
  {
  public:
    typedef ImageLoader_TI<ImageLoaderJpeg, 3>   base_type;

    friend base_type;
    typedef base_type::error_type           error_type;
    typedef base_type::path_type            path_type;
    typedef base_type::size_type            size_type;
    typedef base_type::dimention_type       dimension_type;

  protected:
    error_type  DoLoad(const path_type& a_path);

  };

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(ImageLoader_TI<ImageLoaderPng TLOC_COMMA 4>);
  TLOC_EXTERN_TEMPLATE_CLASS(ImageLoader_TI<ImageLoaderJpeg TLOC_COMMA 3>);

  // -----------------------------------------------------------------------

  namespace f_image_loader {

    core_err::Error
      SaveImage(const Image& a_imgToWrite, 
                const core_io::Path& a_path);

  };

};};};

#endif