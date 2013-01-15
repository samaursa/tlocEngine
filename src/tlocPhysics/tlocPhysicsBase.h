#ifndef _TLOC_PHYSICS_BASE_H_
#define _TLOC_PHYSICS_BASE_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that physics uses should go here

namespace tloc {

  //////////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace physics
  {
    namespace box2d            {};
    namespace component_system {};
    namespace error            {};
  };

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace phys_box2d = physics::box2d;
  namespace phys_cs    = physics::component_system;
  namespace phys_err   = physics::error;

};


#endif