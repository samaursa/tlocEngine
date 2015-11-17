#ifndef TLOC_RNG_WELL_512_H
#define TLOC_RNG_WELL_512_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypes.h>

namespace tloc { namespace core { namespace rng {

  // The basis of this class has been taken from a forum post of gamedev.net
  // The class had to be `adjusted` to fit with our interface but the actual
  // functionality has been copied directly. The original class was written
  // by Mattias Gustavsson with the algorithm Well512 taken from
  // http://www.iro.umontreal.ca/~panneton/WELLRNG.html

  class rng_well_512
  {
    template <typename T_Generator> friend class rng_t;

  private:

    typedef   u32           int_type;
    typedef   f32           real_type;
    typedef   rng_well_512    rng_type;

    struct Params
    {
      int_type  m_seed;

      int_type  m_index;
      int_type  m_state[16];
    };

    rng_well_512();

    ///-------------------------------------------------------------------------
    /// @brief
    /// Params must a seed and an index. The states are calculated by the
    /// function.
    ///
    /// @param  a_seed POD containing a seed, index and states
    ///-------------------------------------------------------------------------
    void            set_seed(const Params& a_seed);

    ///-------------------------------------------------------------------------
    /// @brief Gets the seed POD.
    ///
    /// @return The seed POD.
    ///-------------------------------------------------------------------------
    const Params&   get_seed() const;

    const int_type  get_random_int() const;
    const real_type get_random_real() const;
    const int_type  get_random_int(int_type a_min, int_type a_max) const;
    const real_type get_random_real(real_type a_min, real_type a_max) const;

    mutable Params          m_params;
  };

};};};

#endif