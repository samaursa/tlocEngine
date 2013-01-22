#ifndef _TLOC_MATH_BASE_H_
#define _TLOC_MATH_BASE_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that math uses should go here

namespace tloc {

  //////////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace math
  {
    namespace component_system {};
    namespace types            {};
    namespace utils            {};
  };

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace math_cs    = math::component_system;
  namespace math_t     = math::types;
  namespace math_utils = math::utils;

};


#endif