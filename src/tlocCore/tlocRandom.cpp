#include "tlocRandom.h"

#include "tlocRngWell512.inl"

namespace tloc { namespace math {

  // Supported RNG types instantiation
  template      RNG<RngWell512>;

  // Default global RNG
  rng_default   g_defaultRNG;

};};