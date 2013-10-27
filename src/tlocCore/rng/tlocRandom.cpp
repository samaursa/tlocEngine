#include "tlocRandom.h"

namespace tloc { namespace core { namespace rng {

  // Supported RNG types instantiation
  template class RNG_T<RngWell512>;

  // Default global RNG
  rng_default   g_defaultRNG;

};};};