#include "tlocRandom.h"

namespace tloc { namespace core { namespace rng {

  // Supported RNG types instantiation
  template class rng_t<rng_well_512>;

  // Default global RNG
  rng_default   g_defaultRNG;

};};};