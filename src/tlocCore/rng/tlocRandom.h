#ifndef TLOC_RANDOM_H
#define TLOC_RANDOM_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypes.h>

#include <tlocCore/rng/tlocRngWell512.h>

// Why include this? LLVM release complains - possible reason is that compiler
// optimizes the functioncall of RNG_T and calls RngWell512 directly and then
// is unable to locate the definition thus causing a linker error.
#include <tlocCore/rng/tlocRngWell512.inl>

namespace tloc { namespace core { namespace rng {

  template <typename T_Generator> class RNG_T;

  //////////////////////////////////////////////////////////////////////////
  // Supported RNG Types

  // Supported RNG types
  typedef RNG_T<RngWell512> rng_well_512;

  // Default RNG type
  typedef rng_well_512      rng_default;

  // Default RNG that is used program wide
  extern rng_default        g_defaultRNG;

  ///-------------------------------------------------------------------------
  /// @brief Random number generator template class. The class requires an RNG that has the following functions at least.
  ///-------------------------------------------------------------------------
  template <typename T_Generator>
  class RNG_T
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
    void SetSeed(const T_Seed& a_seed) { m_rng.SetSeed(a_seed); }

    ///-------------------------------------------------------------------------
    /// @brief
    /// Returns the current seed. T_Generator should return the default
    /// seed if SetSeed() was never called.
    ///
    /// @return The seed.
    ///-------------------------------------------------------------------------
    template <typename T_Seed>
    const T_Seed& GetSeed() const { return m_rng.GetSeed(); }

    ///-------------------------------------------------------------------------
    /// @brief The random integer is greater or equal to 0.
    ///
    /// @return The random integer.
    ///-------------------------------------------------------------------------
    const int_type GetRandomInteger() { return m_rng.GetRandomInteger(); }

    ///-------------------------------------------------------------------------
    /// @brief The random real number with the range [0, 1).
    ///
    /// @return The random float.
    ///-------------------------------------------------------------------------
    const real_type GetRandomFloat() { return m_rng.GetRandomFloat(); }

    ///-------------------------------------------------------------------------
    /// @brief Gets a random integer between [0, a_max)
    ///
    /// @param  a_max The maximum number (not inclusive)
    ///
    /// @return The random integer.
    ///-------------------------------------------------------------------------
    const int_type GetRandomInteger(const int_type& a_max)
    { return GetRandomInteger(0, a_max); }

    ///-------------------------------------------------------------------------
    /// @brief Gets a random float between [0, a_max)
    ///
    /// @param  a_max The maximum number (not inclusive)
    ///
    /// @return The random float.
    ///-------------------------------------------------------------------------
    const real_type GetRandomFloat(const real_type& a_max)
    { return GetRandomFloat(0, a_max); }

    ///-------------------------------------------------------------------------
    /// @brief Generates a random integer between [min, max).
    ///
    /// @param  a_min The beginning of the range (inclusive).
    /// @param  a_max The end of the range (exclusive).
    ///
    /// @return Random number between the min and max range.
    ///-------------------------------------------------------------------------
    const int_type GetRandomInteger(const int_type& a_min, const int_type& a_max)
    { return m_rng.GetRandomInteger(a_min, a_max); }

    ///-------------------------------------------------------------------------
    /// @brief Generates a random real number between [min, max).
    ///
    /// @param  a_min The beginning of the range (inclusive).
    /// @param  a_max The end of the range (exclusive).
    ///
    /// @return Random number between min and max range.
    ///-------------------------------------------------------------------------
    const real_type GetRandomFloat(const real_type& a_min,
                                   const real_type& a_max)
    { return m_rng.GetRandomFloat(a_min, a_max); }

  private:

    T_Generator	        m_rng;

  };

};};};

#endif
