#ifndef _TLOC_ANIMATION_BASE_H_
#define _TLOC_ANIMATION_BASE_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that animation uses should go here

namespace tloc {

  //////////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace animation
  {
    namespace component_system {};
    namespace error            {};
    namespace types            {};
  };

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace anim          = animation;
  namespace anim_cs       = animation::component_system;
  namespace anim_err      = animation::error;
  namespace anim_t        = animation::types;

};


#endif