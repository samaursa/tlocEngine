#ifndef _TLOC_CORE_TYPES_STRONG_TYPE_H_
#define _TLOC_CORE_TYPES_STRONG_TYPE_H_

#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace core { namespace types {

  ///-------------------------------------------------------------------------
  /// @brief
  /// Strong type structure is intended to be a replacement for function
  /// arguments where type-safety is needed. This is generally needed
  /// within a class which is why boosts STRONG_TYPEDEF macro does not
  /// work (as it cannot know what 'T' of the parent class is simply
  /// because it is a preprocessor)
  ///-------------------------------------------------------------------------
  template <typename T, tl_size T_UniqueCounter>
  struct StrongType_T
  {
    typedef T                                           value_type;
    typedef StrongType_T<value_type, T_UniqueCounter>   this_type;

    explicit StrongType_T(const T a_value);
    StrongType_T(const StrongType_T& a_other);

    this_type& operator= (const StrongType_T& a_other);
    this_type& operator= (value_type a_other);

    operator value_type& ();
    operator const value_type& () const;

    bool operator== (const this_type& a_other) const;
    bool operator< (const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(StrongType_T);

    value_type m_value;
  };

};};};

#endif