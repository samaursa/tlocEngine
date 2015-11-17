#ifndef TLOC_RANDOM_H
#define TLOC_RANDOM_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypes.h>

#include <tlocCore/rng/tlocRngWell512.h>

// Why include this? LLVM release complains - possible reason is that compiler
// optimizes the functioncall of RNG_T and calls RngWell512 directly and then
// is unable to locate the definition thus causing a linker error.
#include <tlocCore/rng/tlocRngWell512.inl.h>

namespace tloc { namespace core { namespace rng {

  template <typename T_Generator> class rng_t;

  //////////////////////////////////////////////////////////////////////////
  // Supported RNG Types

  // Supported RNG types
  typedef rng_t<rng_well_512> rng_well_512;

  // Default RNG type
  typedef rng_well_512      rng_default;

  // Default RNG that is used program wide
  extern rng_default        g_defaultRNG;

  ///-------------------------------------------------------------------------
  /// @brief Random number generator template class. The class requires an RNG that has the following functions at least.
  ///-------------------------------------------------------------------------
  template <typename T_Generator>
  class rng_t
  {
  public:

    typedef typename T_Generator::int_type   int_type;
    typedef typename T_Generator::real_type  real_type;
    typedef T_Generator                      rng_type;

    ///-------------------------------------------------------------------------
    /// @brief Supports multiple calls to SetSeed()
    ///
    /// @param  a_seed Template type that T_Generator must be able to accept.
    ///                It can be a single number or it can be a data structure,
    ///                as long as T_Generator supports it.
    ///-------------------------------------------------------------------------
    template <typename T_Seed>
    void set_seed(const T_Seed& a_seed) 
    { m_rng.SetSeed(a_seed); }

    ///-------------------------------------------------------------------------
    /// @brief
    /// Returns the current seed. T_Generator should return the default
    /// seed if SetSeed() was never called.
    ///
    /// @return The seed.
    ///-------------------------------------------------------------------------
    template <typename T_Seed>
    const T_Seed& get_seed() const 
    { return m_rng.GetSeed(); }

    ///-------------------------------------------------------------------------
    /// @brief The random integer is greater or equal to 0.
    ///
    /// @return The random integer.
    ///-------------------------------------------------------------------------
    const int_type get_random_int() const 
    { return m_rng.GetRandomInteger(); }

    ///-------------------------------------------------------------------------
    /// @brief The random real number with the range [0, 1).
    ///
    /// @return The random float.
    ///-------------------------------------------------------------------------
    const real_type get_random_real() const 
    { return m_rng.GetRandomFloat(); }

    ///-------------------------------------------------------------------------
    /// @brief Gets a random integer between [0, a_max)
    ///
    /// @param  a_max The maximum number (not inclusive)
    ///
    /// @return The random integer.
    ///-------------------------------------------------------------------------
    int_type get_random_int(int_type a_max) const
    { return get_random_int(0, a_max); }

    ///-------------------------------------------------------------------------
    /// @brief Gets a random float between [0, a_max)
    ///
    /// @param  a_max The maximum number (not inclusive)
    ///
    /// @return The random float.
    ///-------------------------------------------------------------------------
    real_type get_random_real(real_type a_max) const
    { return get_random_real(0, a_max); }

    ///-------------------------------------------------------------------------
    /// @brief Generates a random integer between [min, max).
    ///
    /// @param  a_min The beginning of the range (inclusive).
    /// @param  a_max The end of the range (exclusive).
    ///
    /// @return Random number between the min and max range.
    ///-------------------------------------------------------------------------
    int_type get_random_int(int_type a_min, int_type a_max) const
    { return m_rng.GetRandomInteger(a_min, a_max); }

    ///-------------------------------------------------------------------------
    /// @brief Generates a random real number between [min, max).
    ///
    /// @param  a_min The beginning of the range (inclusive).
    /// @param  a_max The end of the range (exclusive).
    ///
    /// @return Random number between min and max range.
    ///-------------------------------------------------------------------------
    const real_type get_random_real(real_type a_min, real_type a_max) const
    { return m_rng.GetRandomFloat(a_min, a_max); }

  private:

    T_Generator	        m_rng;

  };

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(rng_t<rng_well_512>);

};};};

#endif
