#ifndef TLOC_RANDOM_H
#define TLOC_RANDOM_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTypes.h"

namespace tloc { namespace math {

  template <typename T_Generator>
  class RNG
  {
  public:

    typedef typename T_Generator::int_type   int_type;
    typedef typename T_Generator::real_type  real_type;

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

    T_Generator m_rng;

  };

};};

#endif

/**
* \class	Random
*
* \ingroup	core
* \brief
* \author	Mattias Gustavsson
*
* Random number generation, using the WELL algorithm by F. Panneton, P. L'Ecuyer and M. Matsumoto.
* The creators of the algorithm describes it like this:
*
*      Fast uniform random number generators with extremely long periods have been defined and implemented based on
*      linear recurrences modulo 2. The twisted GFSR and the Mersenne twister are famous recent examples. Besides the
*      period length, the statistical quality of these generators is usually assessed via their equidistribution
*      properties. The huge-period generators proposed so far are not quite optimal in that respect. In this paper,
*      we propose new generators, with better equidistribution and "bit-mixing" properties for equivalent period length
*      and speed. Approximately half of the coefficients of the characteristic polynomial of these generators are
*      nonzero. The state of our new generators evolves in a more chaotic way than for the Mersenne twister. We
*      illustrate how this can reduce the impact of persistent dependencies among successive output values, which can
*      be observed in certain parts of the period of gigantic generators such as the Mersenne twister.
*
* More information in the original paper: http://www.iro.umontreal.ca/~panneton/WELLRNG.html
*
* This code is originally based on WELL512 C/C++ code written by Chris Lomont (published in Game Programming Gems 7)
* and placed in the public domain. There's also an article about it on Lomont's site:
*
*      http://lomont.org/Math/Papers/2008/Lomont_PRNG_2008.pdf
*/

//#ifndef __Random_H__
//#define __Random_H__
//
//class Random
//{
//public:
//  Random();
//
//  void Seed(unsigned int seed);
//  void SetState(const unsigned int state[16], int index);
//  void GetState(unsigned int state[16], int& index);
//
//  /**
//  * Generates a random number on [0,0xffffffff] interval
//  */
//  unsigned int RandomInteger();
//
//  /**
//  * Generates a random number on [0,0.99999999999...] interval
//  */
//  float RandomFloat();
//
//  /**
//  * Generates a random number on [min,max] interval
//  */
//  int RandomRanged(int min, int max);
//
//private:
//  unsigned int state_[16];
//  unsigned int index_;
//
//};
//
//#endif /* __Random_H__ */