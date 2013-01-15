#ifndef _TLOC_PREFAB_BASE_H_
#define _TLOC_PREFAB_BASE_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that prefab uses should go here

namespace tloc {

  //////////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace prefab
  {
    namespace core      {};
    namespace graphics  {};
    namespace input     {};
    namespace math      {};
    namespace physics   {};
  };

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace prefab_core   = prefab::core;
  namespace prefab_gfx    = prefab::graphics;
  namespace prefab_input  = prefab::input;
  namespace prefab_phys   = prefab::physics;

};


#endif