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

  class Image_I
  { };

  template <typename T_ColorType = Color>
  class Image_T
    : public Image_I
  {
    TLOC_STATIC_ASSERT
      ( (Loki::Conversion<T_ColorType, gfx_t::priv::ColorType>::exists),
      Unsupported_color_type_selected);

  public:
    typedef T_ColorType                                   value_type;
    typedef Image_T<value_type>                           this_type;

    typedef value_type                                    color_type;
    typedef typename color_type::value_type               color_value_type;
    typedef typename
      core::containers::tl_array<color_type>::type        pixel_container_type;

    typedef core_sptr::VirtualPtr<color_value_type>       color_ptr;
    typedef core_sptr::VirtualPtr<const color_value_type> const_color_ptr;

    typedef tl_size                                       size_type;

    typedef core::error::Error                            error_type;
    typedef types::Dimension2                             dimension_type;

    typedef core_sptr::VirtualPtr<this_type>              image_ptr;
    typedef core_sptr::SharedPtr<this_type>               image_sptr;
    typedef core_conts::Array<image_ptr>                  image_ptr_cont;

  public:
    Image_T();

    ///-------------------------------------------------------------------------
    /// @brief Loads color buffer from memory (assuming RGBA format)
    ///-------------------------------------------------------------------------
    error_type        LoadFromMemory(const_color_ptr a_buffer,
                                     dimension_type a_dim,
                                     size_type a_channels);

    error_type        LoadFromMemory(const pixel_container_type& a_buffer,
                                     dimension_type a_dim);

    template <typename T_ImageVSOContainer>
    error_type        LoadFromImages(const T_ImageVSOContainer& a_arrayOfImages);

    error_type        Create(dimension_type a_dim, const color_type& a_color);

    void              SetPixel(size_type a_X, size_type a_Y,
                               const color_type& a_color);

    void              SetImage(size_type a_x, size_type a_y,
                               const this_type& a_image);

    error_type        AddPadding(dimension_type a_padding,
                                 const color_type& a_color);

    const color_type& GetPixel(size_type a_X, size_type a_Y) const;

    image_sptr        GetImage(size_type a_x, size_type a_y,
                               dimension_type a_dimToGet) const;

    bool              IsValid() const;

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

  template <typename T_ColorType>
  template <typename T_ImageVSOContainer>
  typename Image_T<T_ColorType>::error_type
    Image_T<T_ColorType>::
    LoadFromImages(const T_ImageVSOContainer& a_arrayOfImages)
  {
    typedef typename T_ImageVSOContainer::value_type          image_vso;
    typedef typename image_vso::value_type                    image_type;

    TLOC_STATIC_ASSERT( (Loki::Conversion<image_type, Image_I>::exists),
      Incoming_container_value_type_must_be_an_Image_T);

    this_type::image_ptr_cont imagePtrs;

    //NOTE:: Commented out temporarily since ToVPtr does not appear to be implemented yet
    //    core::transform_all( a_arrayOfImages, imagePtrs,
    //                         core_sptr::algos::virtual_ptr::transform::ToVPtr() );
    // TODO: extract VirtualPtrs from array of images, push into container, and
    //       send it to DoLoadFromImages for packing. We don't have a binpacker
    //       yet, which is needed for this operation
    TLOC_ASSERT_WIP();

    DoLoadFromImages(imagePtrs);
  }

  // -----------------------------------------------------------------------
  // typedefs

  // default image type
  typedef Image_T<gfx_t::Color>                             Image;

  typedef Image_T<gfx_t::color_rgba>                        image_rgba;
  typedef Image_T<gfx_t::color_rgb>                         image_rgb;
  typedef Image_T<gfx_t::color_rg>                          image_rg;
  typedef Image_T<gfx_t::color_r>                           image_r;

  typedef Image_T<gfx_t::color_u16_rgba>                    image_u16_rgba;
  typedef Image_T<gfx_t::color_u16_rgb>                     image_u16_rgb;
  typedef Image_T<gfx_t::color_u16_rg>                      image_u16_rg;
  typedef Image_T<gfx_t::color_u16_r>                       image_u16_r;

  typedef Image_T<gfx_t::color_f32_r>                       image_f32_r;

  TLOC_TYPEDEF_ALL_SMART_PTRS(Image, image);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Image, image);

  // ```````````````````````````````````````````````````````````````````````
  // u8 images

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_rgba, image_rgba);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_rgba, image_rgba);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_rgb, image_rgb);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_rgb, image_rgb);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_rg, image_rg);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_rg, image_rg);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_r, image_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_r, image_r);

  // ```````````````````````````````````````````````````````````````````````
  // u16 images

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_u16_rgba, image_u16_rgba);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_u16_rgba, image_u16_rgba);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_u16_rgb, image_u16_rgb);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_u16_rgb, image_u16_rgb);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_u16_rg, image_u16_rg);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_u16_rg, image_u16_rg);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_u16_r, image_u16_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_u16_r, image_u16_r);

  // ```````````````````````````````````````````````````````````````````````
  // special images

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_f32_r, image_f32_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_f32_r, image_f32_r);

};};};

#endif