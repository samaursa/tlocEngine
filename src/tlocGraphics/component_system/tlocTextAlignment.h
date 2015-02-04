#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXT_ALIGNMENT_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXT_ALIGNMENT_H_

#include <tlocGraphics/tlocGraphicsBase.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace alignment {

    enum 
    {
      k_align_left = 0,
      k_align_center,
      k_align_right,

      k_align_count
    }; typedef tl_int                                       align_type;

  };

  namespace horizontal_alignment {

    enum 
    {
      k_none = 0,
      k_align_middle,

      k_align_count
    }; typedef tl_int                                       align_type;

  };

  namespace vertical_alignment {

    enum 
    {
      k_align_left = 0,
      k_align_center,
      k_align_right,

      k_align_count
    }; typedef tl_int                                       align_type;

  };

};};};

#endif