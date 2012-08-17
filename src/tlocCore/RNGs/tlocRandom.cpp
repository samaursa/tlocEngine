#include "tlocRandom.h"

#include "tlocRngWell512.inl"

namespace tloc { namespace core {

  // Supported RNG types instantiation
  template class RNG<RngWell512>;

  // Default global RNG
  rng_default   g_defaultRNG;

};};