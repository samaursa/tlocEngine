#ifndef TLOC_IMAGE_H
#define TLOC_IMAGE_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/error/tlocError.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>

#include <tlocGraphics/types/tlocColor.h>
#include <tlocGraphics/types/tlocDimension.h>

namespace tloc { namespace graphics { namespace media {

  class Image
  {
  public:
    typedef tl_size                                       size_type;
    typedef types::Color                                  color_type;
    typedef core::containers::tl_array<color_type>::type  pixel_container_type;
    typedef core::error::Error                            error_type;
    typedef types::Dimension2                             dimension_type;
    typedef core_sptr::VirtualPtr<const uchar8>           const_uchar8_ptr;

    typedef Image                                         this_type;
    typedef core_sptr::VirtualPtr<this_type>              image_ptr;
    typedef core_conts::Array<image_ptr>                  image_ptr_cont;

  public:
    Image();

    ///-------------------------------------------------------------------------
    /// @brief Loads color buffer from memory (assuming RGBA format)
    ///-------------------------------------------------------------------------
    error_type        LoadFromMemory(const_uchar8_ptr a_buffer,
                                     dimension_type a_dim,
                                     size_type a_channels);

    error_type        LoadFromMemory(const pixel_container_type& a_buffer,
                                     dimension_type a_dim);

    template <typename T_ImageVSOContainer>
    error_type        LoadFromImages(const T_ImageVSOContainer& a_arrayOfImages);

    error_type        Create(dimension_type a_dim, const color_type& a_color);

    void              SetPixel(size_type a_X, size_type a_Y,
                               const color_type& a_color);

    error_type        AddPadding(dimension_type a_padding,
                                 const color_type& a_color);

    const color_type& GetPixel(size_type a_X, size_type a_Y) const;

    TLOC_DECL_AND_DEF_GETTER(size_type, GetWidth, m_dim[types::dimension::width]);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetHeight, m_dim[types::dimension::height]);
    TLOC_DECL_AND_DEF_GETTER(dimension_type, GetDimensions, m_dim);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(pixel_container_type,
                                          GetPixels, m_pixels);

  private:
    error_type        DoLoadFromImages(const image_ptr_cont& a_arrayOfImages);

  private:
    dimension_type          m_dim;
    pixel_container_type    m_pixels;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_ImageVSOContainer>
  Image::error_type
    Image::
    LoadFromImages(const T_ImageVSOContainer& a_arrayOfImages)
  {
    typedef typename T_ImageVSOContainer::value_type          image_vso;
    typedef typename image_vso::value_type                    image_type;

    type_traits::AssertTypeIsSupported<image_type, Image>();

    Image::image_ptr_cont imagePtrs;

    core::transform_all( a_arrayOfImages, imagePtrs,
                         core_sptr::algos::virtual_ptr::transform::ToVPtr() );

    DoLoadFromImages(imagePtrs);
  }

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Image, image);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Image, image);

};};};

#endif