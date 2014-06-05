#include "tlocImage.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/logging/tlocLogger.h>

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
  // Image_I

  Image_I::
    Image_I()
    : m_dim(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Image_I::
    ~Image_I()
  { }

  // ///////////////////////////////////////////////////////////////////////
  // Image_TI<>

#define TLOC_IMAGE_INTERNAL_TEMPS   typename T_ColorType
#define TLOC_IMAGE_INTERNAL_PARAMS  T_ColorType, p_image::storage::Internal
#define TLOC_IMAGE_INTERNAL_TYPE    typename Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    Image_TI()
    : base_type()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    ~Image_TI()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  TLOC_IMAGE_INTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    Load(const_color_ptr a_buffer, dimension_type a_dim, size_type a_channels)
  {
    if ( (a_buffer == nullptr) || a_dim[0] == 0 || a_dim[1] == 0 ||
         (a_channels == 0) )
    { return TLOC_ERROR(common_error_types::error_no_data); }

    // Check if a_size can accommodate a whole number of Color*
    TLOC_ASSERT( (a_channels == color_type::k_size),
      "The buffer has an invalid size!");

    const color_type* buffer = reinterpret_cast<const color_type*>(a_buffer.get());
    m_pixels.assign(buffer, buffer + (a_dim[0] * a_dim[1]));

    m_dim = a_dim;

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  TLOC_IMAGE_INTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    Load(const pixel_container_type& a_buffer, dimension_type a_dim)
  {
    TLOC_ASSERT( (a_dim[0] * a_dim[1]) == a_buffer.size(),
      "Invalid buffer size wrt image dimensions");
    m_pixels = a_buffer;
    m_dim = a_dim;
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  TLOC_IMAGE_INTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    Create(dimension_type a_dim, const color_type& a_color)
  {
    m_dim = a_dim;

    m_pixels.clear();
    m_pixels.resize(m_dim[width] * m_dim[height] , a_color);

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  TLOC_IMAGE_INTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
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
    error_type err = Load(newImg, newDim);

    return err;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  bool
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    IsValid() const
  {
    return GetDimensions()[0] > 0 &&
           GetDimensions()[1] > 0 &&
           (m_pixels.size() == m_dim[0] * m_dim[1]);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  TLOC_IMAGE_INTERNAL_TYPE::const_color_type_ptr
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    get() const
  {
    return const_color_type_ptr(&*m_pixels.begin());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  void
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    DoSet(tl_int a_index, const color_type& a_color)
  { m_pixels[a_index] = a_color; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  const TLOC_IMAGE_INTERNAL_TYPE::color_type&
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    DoGet(tl_int a_index) const
  { return m_pixels[a_index]; }

  // ///////////////////////////////////////////////////////////////////////
  // Image_TI<External>

#define TLOC_IMAGE_EXTERNAL_TEMPS   typename T_ColorType
#define TLOC_IMAGE_EXTERNAL_PARAMS  T_ColorType, p_image::storage::External
#define TLOC_IMAGE_EXTERNAL_TYPE    typename Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    Image_TI()
    : base_type()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    ~Image_TI()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  TLOC_IMAGE_EXTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    Load(color_ptr a_buffer, dimension_type a_dim, size_type a_channels)
  {
    if ( (a_buffer == nullptr) || a_dim[0] == 0 || a_dim[1] == 0 ||
         (a_channels == 0) )
    { return TLOC_ERROR(common_error_types::error_no_data); }

    // Check if a_size can accommodate a whole number of Color*
    TLOC_ASSERT( (a_channels == color_type::k_size),
      "The buffer has an invalid size!");

    m_pixels.reset( reinterpret_cast<color_type*>(a_buffer.get()) );
    m_dim = a_dim;

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  TLOC_IMAGE_EXTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    Create(dimension_type , const color_type& )
  {
    TLOC_LOG_GFX_WARN() << 
      "Create() has no effect in Image_T<> with external storage";
    return ErrorFailure;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  TLOC_IMAGE_EXTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    AddPadding(dimension_type , const color_type& )
  {
    TLOC_LOG_GFX_WARN() << 
      "Cannot add padding to Image_T<> with external storage";
    return ErrorFailure;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  bool
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    IsValid() const
  {
    return GetDimensions()[0] > 0 &&
           GetDimensions()[1] > 0 &&
           m_pixels != nullptr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  TLOC_IMAGE_EXTERNAL_TYPE::const_color_type_ptr
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    get() const
  {
    return m_pixels;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  void
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    DoSet(tl_int a_index, const color_type& a_color)
  { m_pixels.get()[a_index] = a_color; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  const TLOC_IMAGE_EXTERNAL_TYPE::color_type&
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    DoGet(tl_int a_index) const
  { return m_pixels.get()[a_index]; }

  // ///////////////////////////////////////////////////////////////////////
  // Image_T<>

#define TLOC_IMAGE_TEMPS    typename T_ColorType, typename T_StorageType
#define TLOC_IMAGE_PARAMS   T_ColorType, T_StorageType
#define TLOC_IMAGE_TYPE     typename Image_T<TLOC_IMAGE_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_TEMPS>
  Image_T<TLOC_IMAGE_PARAMS>::
    Image_T()
    : base_type()
  { }


  template <TLOC_IMAGE_TEMPS>
  void
    Image_T<TLOC_IMAGE_PARAMS>::
    SetPixel(size_type a_X, size_type a_Y, const color_type& a_color)
  {
    tl_int index = core_utils::GetIndex(this->GetDimensions(), 
                                        core_ds::MakeTuple(a_X, a_Y));
    this->DoSet(index, a_color);
  }

  template <TLOC_IMAGE_TEMPS>
  void
    Image_T<TLOC_IMAGE_PARAMS>::
    SetImage(size_type a_x, size_type a_y, const this_type& a_image)
  {
    const dimension_type imgDim = a_image.GetDimensions();

    TLOC_ASSERT(imgDim[0] + a_x <= this->GetDimensions()[0], 
                "Incoming image does not fit in X");
    TLOC_ASSERT(imgDim[1] + a_y <= this->GetDimensions()[1], 
                "Incoming image does not fit in Y");

    for (size_type y = 0; y < imgDim[1]; ++y)
    {
      for (size_type x = 0; x < imgDim[0]; ++x)
      {
        SetPixel(x + a_x, y + a_y, a_image.GetPixel(x, y));
      }
    }
  }

  template <TLOC_IMAGE_TEMPS>
  const TLOC_IMAGE_TYPE::color_type&
    Image_T<TLOC_IMAGE_PARAMS>::
    GetPixel(size_type a_X, size_type a_Y) const
  {
    tl_int index = core_utils::GetIndex(this->GetDimensions(), 
                                        core_ds::MakeTuple(a_X, a_Y));
    return this->DoGet(index);
  }

  template <TLOC_IMAGE_TEMPS>
  TLOC_IMAGE_TYPE::image_sptr
    Image_T<TLOC_IMAGE_PARAMS>::
    GetImage(size_type a_x, size_type a_y, dimension_type a_dimToGet) const
  {
    TLOC_ASSERT(a_x + a_dimToGet[0] <= this->GetDimensions()[0], 
                "Dimensions out of range");
    TLOC_ASSERT(a_y + a_dimToGet[1] <= this->GetDimensions()[1], 
                "Dimensions out of range");

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
  
  // -----------------------------------------------------------------------
  // explicitly instantiate Image_T<> types
  
  using namespace gfx_t;

  typedef p_image::storage::Internal          internal_store;
  typedef p_image::storage::External          external_store;

#define TLOC_EXPLICITLY_INSTANTIATE_IMAGE(_colorType_)\
  template class Image_TI<_colorType_, internal_store>;\
  template class Image_TI<_colorType_, external_store>;\
  template class Image_T<_colorType_, internal_store>;\
  template class Image_T<_colorType_, external_store>

  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(Color);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(color_rgb);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(color_rg);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(color_r);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(color_u16_rgba);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(color_u16_rgb);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(color_u16_rg);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(color_u16_r);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(color_f32_r);

};};};

//------------------------------------------------------------------------
// Explicitly instantiate the container

using namespace tloc::gfx_med;
using namespace tloc::gfx_t;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

// ```````````````````````````````````````````````````````````````````````
// Instantiate all color VirtualPtrs

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_rgba::color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_rgb::color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_rg::color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_r::color_type_ptr);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_rgba::color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_rgb::color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_rg::color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_r::color_type_ptr);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_f32_r::color_type_ptr);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_rgba::const_color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_rgb::const_color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_rg::const_color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_r::const_color_type_ptr);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_rgba::const_color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_rgb::const_color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_rg::const_color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_r::const_color_type_ptr);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_f32_r::const_color_type_ptr);

// ```````````````````````````````````````````````````````````````````````
// Defaults

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