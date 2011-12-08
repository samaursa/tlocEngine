#ifndef TLOC_RNG_WELL_512_H
#define TLOC_RNG_WELL_512_H

namespace tloc { namespace math {

  class RngWell512
  {
  public:

    typedef   u32   int_type;
    typedef   f32   real_type;

    struct Params
    {
      int_type  m_seed;

      int_type  m_index;
      int_type  m_state[16];
    };

    void            SetSeed(const Params& a_seed);
    const Params&   GetSeed() const;
    const int_type  GetRandomInteger() const;
    const real_type GetRandomFloat() const;
    const int_type  GetRandomRange(const int_type& a_min, 
                                   const int_type& a_max);
    const real_type GetRandomRange(const real_type& a_min,
                                   const real_type& a_max);
  };

};};

#endif