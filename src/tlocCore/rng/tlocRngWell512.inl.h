#ifndef TLOC_RNG_WELL_512_INL
#define TLOC_RNG_WELL_512_INL

#include "tlocRngWell512.h"
#include <tlocCore/tlocAssert.h>

#include <time.h>
#include <stdexcept>

namespace tloc { namespace core { namespace rng {

  TL_I rng_well_512::rng_well_512()
  {
    Params defaultParams;
    defaultParams.m_seed	= (int_type)::time(nullptr);
    defaultParams.m_index	= 0;

    set_seed(defaultParams);
  }

  TL_I void rng_well_512::set_seed(const Params& a_seed)
  {
    m_params = a_seed;

    m_params.m_state[0]=m_params.m_seed ^ 0xf68a9fc1;
    for (u32 i = 1; i < 16; ++i)
    {
      m_params.m_state[i] = (0x6c078965U * (m_params.m_state[i-1] ^
                            (m_params.m_state[i-1] >> 30)) + i);
    }
  }

  TL_I const rng_well_512::Params& rng_well_512::get_seed() const
  {
    return m_params;
  }

  TL_I const rng_well_512::int_type rng_well_512::get_random_int() const
  {
    u32 a = m_params.m_state[m_params.m_index];
    u32 c = m_params.m_state[(m_params.m_index+13)&15];
    u32 b = a^c^(a<<16)^(c<<15);
    c = m_params.m_state[(m_params.m_index+9)&15];
    c ^= (c>>11);
    a = m_params.m_state[m_params.m_index] = b^c;
    u32 d = a^((a<<5)&0xda442d20U);
    m_params.m_index= (m_params.m_index+ 15)&15;
    a = m_params.m_state[m_params.m_index];
    m_params.m_state[m_params.m_index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
    return m_params.m_state[m_params.m_index];
  }

  TL_I const rng_well_512::real_type rng_well_512::get_random_real() const
  {
    // Get a random integer, and divide by 2^32
    return (get_random_int()/4294967296.0f);
  }

  TL_I const rng_well_512::int_type
    rng_well_512::get_random_int(int_type a_min, int_type a_max) const
  {
    if (a_max >= a_min) { throw std::out_of_range("Range max is smaller than min"); }

    const int_type range = a_max - a_min;
    return (int_type)((real_type)range * (real_type)(get_random_real()) ) + a_min;
  }

  TL_I const rng_well_512::real_type
    rng_well_512::get_random_real(real_type a_min, real_type a_max) const
  {
    if (a_max >= a_min) { throw std::out_of_range("Range max is smaller than min"); }

    const real_type range = a_max - a_min;
    return (range * (real_type)(get_random_real()) ) + a_min;
  }

};};};

#endif