#ifndef _TLOC_GRAPHICS_MEDIA_FONT_H_
#define _TLOC_GRAPHICS_MEDIA_FONT_H_

#include <tlocCore/base_classes/tlocInitializeAndDestroy.h>

namespace tloc { namespace graphics { namespace media {

  class Font
    : public core_bclass::InitializeAndDestroy_TI<Font, 
              core_bclass::p_initialize_and_destroy::NoParams>
  {
  public:
    typedef Font                                              this_type;
    typedef core_bclass::
      InitializeAndDestroy_TI<this_type, 
      core_bclass::p_initialize_and_destroy::NoParams>        base_type;

  public:

    Font();

    TLOC_USING_INITIALIZE_AND_DESTROY_METHODS();

  private:

  };

};};};

#endif