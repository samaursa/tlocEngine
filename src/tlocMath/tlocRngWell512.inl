#include "tlocRngWell512.h"

#include <time.h>

namespace tloc { namespace math {

  RngWell512::RngWell512()
  {
    Params defaultParams;
    defaultParams.m_seed	= (int_type)time(NULL);
    defaultParams.m_index	= 0;

    SetSeed(defaultParams);
  }

  void RngWell512::SetSeed(const Params& a_seed)
  {
    m_params = a_seed;

    m_params.m_state[0]=m_params.m_seed ^ 0xf68a9fc1;
    for (u32 i = 1; i < 16; ++i) 
    {
      m_params.m_state[i] = (0x6c078965U * (m_params.m_state[i-1] ^ 
                            (m_params.m_state[i-1] >> 30)) + i); 
    }
  }

  const RngWell512::Params& RngWell512::GetSeed() const
  {
    return m_params;
  }

  const RngWell512::int_type RngWell512::GetRandomInteger() const
  {
    unsigned int a = m_params.m_state[m_params.m_index];
    unsigned int c = m_params.m_state[(m_params.m_index+13)&15];
    unsigned int b = a^c^(a<<16)^(c<<15);
    c = m_params.m_state[(m_params.m_index+9)&15];
    c ^= (c>>11);
    a = m_params.m_state[m_params.m_index] = b^c;
    unsigned int d = a^((a<<5)&0xda442d20U);
    m_params.m_index= (m_params.m_index+ 15)&15;
    a = m_params.m_state[m_params.m_index];
    m_params.m_state[m_params.m_index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
    return m_params.m_state[m_params.m_index];
  }

  const RngWell512::real_type RngWell512::GetRandomFloat() const
  {
    // Get a random integer, and divide by 2^32
    return (GetRandomInteger()/4294967296.0f);
  }

  const RngWell512::int_type 
    RngWell512::GetRandomRange(const RngWell512::int_type& a_min, 
                               const RngWell512::int_type& a_max)
  {
    TLOC_ASSERT_LOW_LEVEL(a_max >= a_min, "Range max is smaller than min!");

    const int_type range = a_max - a_min;
    return (range * (int_type)(GetRandomFloat()) ) + a_min;
  }

  const RngWell512::int_type
    RngWell512::GetRandomRange(const RngWell512::real_type& a_min, 
                               const RngWell512::real_type& a_max)
  {
    TLOC_ASSERT_LOW_LEVEL(a_max >= a_min, "Range max is smaller than min!");

    const real_type range = a_max - a_min;
    return (range * (real_type)(GetRandomFloat()) ) + a_min;
  }

};};