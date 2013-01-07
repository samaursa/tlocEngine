#include "tlocRandom.h"

#include "tlocRngWell512.inl"

namespace tloc { namespace core { namespace rng {

  // Supported RNG types instantiation
  template class RNG_T<RngWell512>;

  // Default global RNG
  rng_default   g_defaultRNG;

};};};