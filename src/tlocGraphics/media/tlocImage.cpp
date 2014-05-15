#include "tlocImage.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/utilities/tlocContainerUtils.h>

namespace tloc { namespace graphics { namespace media {

  namespace
  {
    enum
    {
      width = types::dimension::width,
      height = types::dimension::height,
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Image_T<>

#define TLOC_IMAGE_TEMPS    typename T_ColorType
#define TLOC_IMAGE_PARAMS   T_ColorType
#define TLOC_IMAGE_TYPE     typename Image_T<TLOC_IMAGE_PARAMS>

  template <TLOC_IMAGE_TEMPS>
  Image_T<TLOC_IMAGE_PARAMS>::
    Image_T()
    : m_dim(0)
  { }

  template <TLOC_IMAGE_TEMPS>
  TLOC_IMAGE_TYPE::error_type
    Image_T<TLOC_IMAGE_PARAMS>::
    LoadFromMemory(const_color_ptr a_buffer, dimension_type a_dim,
                   size_type a_channels)
  {
    if ( (a_buffer == nullptr) || a_dim[0] == 0 || a_dim[1] == 0 ||
         (a_channels == 0) )
    { return TLOC_ERROR(common_error_types::error_no_data); }

    // Check if a_size can accommodate a whole number of Color*
    TLOC_ASSERT( ((a_channels % sizeof(color_type)) == 0),
      "The buffer has an invalid size!");

    const color_type* buffer = reinterpret_cast<const color_type*>(a_buffer.get());
    m_pixels.assign(buffer, buffer + (a_dim[0] * a_dim[1]));

    m_dim = a_dim;

    return ErrorSuccess;
  }

  template <TLOC_IMAGE_TEMPS>
  TLOC_IMAGE_TYPE::error_type
    Image_T<TLOC_IMAGE_PARAMS>::
    LoadFromMemory(const pixel_container_type& a_buffer, dimension_type a_dim)
  {
    TLOC_ASSERT( (a_dim[0] * a_dim[1]) == a_buffer.size(),
      "Invalid buffer size wrt image dimensions");
    m_pixels = a_buffer;
    m_dim = a_dim;
    return ErrorSuccess;
  }

  template <TLOC_IMAGE_TEMPS>
  TLOC_IMAGE_TYPE::error_type
    Image_T<TLOC_IMAGE_PARAMS>::
    DoLoadFromImages(const image_ptr_cont& a_arrayOfImages)
  {
    TLOC_ASSERT_WIP();
    TLOC_UNUSED(a_arrayOfImages);
    return ErrorSuccess;
  }

  template <TLOC_IMAGE_TEMPS>
  TLOC_IMAGE_TYPE::error_type
    Image_T<TLOC_IMAGE_PARAMS>::
    Create(dimension_type a_dim, const color_type& a_color)
  {
    m_dim = a_dim;

    m_pixels.clear();
    m_pixels.resize(m_dim[width] * m_dim[height] , a_color);

    return ErrorSuccess;
  }

  template <TLOC_IMAGE_TEMPS>
  void
    Image_T<TLOC_IMAGE_PARAMS>::
    SetPixel(size_type a_X, size_type a_Y, const color_type& a_color)
  {
    tl_int index = core_utils::GetIndex(m_dim, core_ds::MakeTuple(a_X, a_Y));
    m_pixels[index] = a_color;
  }

  template <TLOC_IMAGE_TEMPS>
  void
    Image_T<TLOC_IMAGE_PARAMS>::
    SetImage(size_type a_x, size_type a_y, const this_type& a_image)
  {
    const dimension_type imgDim = a_image.GetDimensions();

    TLOC_ASSERT(imgDim[0] + a_x <= m_dim[0], "Incoming image does not fit in X");
    TLOC_ASSERT(imgDim[1] + a_y <= m_dim[1], "Incoming image does not fit in Y");

    for (size_type y = 0; y < imgDim[1]; ++y)
    {
      for (size_type x = 0; x < imgDim[0]; ++x)
      {
        SetPixel(x + a_x, y + a_y, a_image.GetPixel(x, y));
      }
    }
  }

  template <TLOC_IMAGE_TEMPS>
  TLOC_IMAGE_TYPE::error_type
    Image_T<TLOC_IMAGE_PARAMS>::
    AddPadding(dimension_type a_padding, const color_type& a_color)
  {
    dimension_type a_paddingTotal = core_ds::Add(a_padding, a_padding);
    dimension_type newDim = core_ds::MakeTuple
      (m_dim[0] + a_paddingTotal[0], m_dim[1] + a_paddingTotal[1]);

    pixel_container_type newImg(newDim[0] * newDim[1]);

    for (size_type y = 0; y < newDim[1]; ++y)
    {
      for (size_type x = 0; x < newDim[0]; ++x)
      {
        tl_int index = core_utils::GetIndex(newDim, core_ds::MakeTuple(x, y));

        if (x < a_padding[0] || (x >= m_dim[0] + a_padding[0]) ||
            y < a_padding[1] || (y >= m_dim[1] + a_padding[1]) )
        {
          newImg[index] = a_color;
        }
        else
        {
          tl_int currImgIndex = core_utils::GetIndex
            (m_dim, core_ds::MakeTuple(x - a_padding[0],
                                       y - a_padding[1]));

          newImg[index] = m_pixels[currImgIndex];
        }
      }
    }

    this_type temp;
    error_type err = temp.LoadFromMemory(newImg, newDim);

    if (err.Failed())
    { return err; }

    core::swap(temp, *this);
    return ErrorSuccess;
  }

  template <TLOC_IMAGE_TEMPS>
  const TLOC_IMAGE_TYPE::color_type&
    Image_T<TLOC_IMAGE_PARAMS>::
    GetPixel(size_type a_X, size_type a_Y) const
  {
    tl_int index = core_utils::GetIndex(m_dim, core_ds::MakeTuple(a_X, a_Y));
    return m_pixels[index];
  }

  template <TLOC_IMAGE_TEMPS>
  TLOC_IMAGE_TYPE::image_sptr
    Image_T<TLOC_IMAGE_PARAMS>::
    GetImage(size_type a_x, size_type a_y, dimension_type a_dimToGet) const
  {
    TLOC_ASSERT(a_x + a_dimToGet[0] <= m_dim[0], "Dimensions out of range");
    TLOC_ASSERT(a_y + a_dimToGet[1] <= m_dim[1], "Dimensions out of range");

    image_sptr img(new this_type());
    img->Create(a_dimToGet, color_type::COLOR_BLACK);

    for (size_type y = 0; y < a_dimToGet[1]; ++y)
    {
      for (size_type x = 0; x < a_dimToGet[0]; ++x)
      {
        img->SetPixel(x, y, GetPixel(x + a_x, y + a_y));
      }
    }

    return img;
  }

  template <TLOC_IMAGE_TEMPS>
  bool
    Image_T<TLOC_IMAGE_PARAMS>::
    IsValid() const
  {
    return m_dim[0] > 0 &&
           m_dim[1] > 0 &&
           (m_pixels.size() == m_dim[0] * m_dim[1]);
  }

};};};

using namespace tloc::gfx_med;
using namespace tloc::gfx_t;

// -----------------------------------------------------------------------
// explicitly instantiate Image_T<> types

template class Image_T<Color>;
template class Image_T<color_rgb>;
template class Image_T<color_rg>;
template class Image_T<color_r>;
template class Image_T<color_u16_rgba>;
template class Image_T<color_u16_rgb>;
template class Image_T<color_u16_rg>;
template class Image_T<color_u16_r>;
template class Image_T<color_f32_r>;

//------------------------------------------------------------------------
// Explicitly instantiate the container

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Image);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Color);

  // ```````````````````````````````````````````````````````````````````````
  // u8 images

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_rgb);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_rg);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_r);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_rgb);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_rg);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_r);

  // ```````````````````````````````````````````````````````````````````````
  // u16 images

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_u16_rgb);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_u16_rg);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_u16_r);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_u16_rgb);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_u16_rg);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_u16_r);

  // ```````````````````````````````````````````````````````````````````````
  // special images

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_f32_r);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_f32_r);