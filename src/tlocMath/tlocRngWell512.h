#ifndef TLOC_RNG_WELL_512_H
#define TLOC_RNG_WELL_512_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTypes.h"

#include "tlocRandom.h"

namespace tloc { namespace math {

  // The basis of this class has been taken from a forum post of gamedev.net
  // The class had to be `adjusted` to fit with our interface but the actual
  // functionality has been copied directly.

  class RngWell512
  {
    template <typename T_Generator> friend class RNG;

  private:

    typedef   u32   int_type;
    typedef   f32   real_type;

    struct Params
    {
      int_type  m_seed;

      int_type  m_index;
      int_type  m_state[16];
    };

    RngWell512();

    ///-------------------------------------------------------------------------
    /// @brief
    /// Params must a seed and an index. The states are calculated by the
    /// function.
    ///
    /// @param  a_seed POD containing a seed, index and states
    ///-------------------------------------------------------------------------
    void            SetSeed(const Params& a_seed);

    ///-------------------------------------------------------------------------
    /// @brief Gets the seed POD.
    ///
    /// @return The seed POD.
    ///-------------------------------------------------------------------------
    const Params&   GetSeed() const;

    const int_type  GetRandomInteger() ;
    const real_type GetRandomFloat() ;
    const int_type  GetRandomInteger(const int_type& a_min,
                                     const int_type& a_max);
    const real_type GetRandomFloat(const real_type& a_min,
                                   const real_type& a_max);

    Params          m_params;
  };

  typedef RNG<RngWell512> rng_well_512;

};};

#endif