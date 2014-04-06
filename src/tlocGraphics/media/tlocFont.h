#ifndef _TLOC_GRAPHICS_MEDIA_FONT_H_
#define _TLOC_GRAPHICS_MEDIA_FONT_H_

#include <tlocCore/base_classes/tlocInitializeAndDestroy.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>
#include <tlocCore/string/tlocString.h>

#include <tlocGraphics/media/tlocImage.h>

namespace tloc { namespace graphics { namespace media {

  // ///////////////////////////////////////////////////////////////////////
  // FreeType forward declaration

  namespace free_type
  { class FreeType; };

  // ///////////////////////////////////////////////////////////////////////
  // Font

  class Font
    : public core_bclass::InitializeAndDestroy_TI<Font,
              core_bclass::p_initialize_and_destroy::OneParam>
  {
    TLOC_DECLARE_FRIEND_INITIALIZE_AND_DESTROY_ONE_PARAM(Font);

  public:
    typedef Font                                          this_type;
    typedef core_bclass::
      InitializeAndDestroy_TI<this_type,
      core_bclass::p_initialize_and_destroy::OneParam>    base_type;

    typedef core_sptr::VirtualPtr<free_type::FreeType>    ft_ptr;
    typedef core_str::String                              data_type;

    typedef image_sptr                                    image_ptr;

  public:
    Font();
    ~Font();

    image_ptr     GetCharImage(tl_ulong a_char);

    TLOC_USING_INITIALIZE_AND_DESTROY_METHODS();

  protected:

    error_type    DoInitialize(const data_type& a_data);
    error_type    DoDestroy();

  private:
    error_type    Destroy(); // intentionally not defined

  private:
    ft_ptr        m_ft;

  };

};};};

#endif