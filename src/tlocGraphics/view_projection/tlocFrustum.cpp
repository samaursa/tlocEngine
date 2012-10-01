#include "tlocFrustum.h"
#include <tlocCore/data_structures/tlocTuple.inl>

namespace tloc { namespace graphics { namespace view_projection {

  Frustum::Frustum()
  { }

  Frustum::~Frustum()
  { }

  //------------------------------------------------------------------------
  // Instantiate tuple for the number of planes we have

  template class core::Tuple<Frustum::real_type, Frustum::Planes::k_count>;

};};};