#ifndef _TLOC_CORE_TYPES_STRONG_TYPE_H_
#define _TLOC_CORE_TYPES_STRONG_TYPE_H_

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypeTraits.h>

namespace tloc { namespace core { namespace types {

  ///-------------------------------------------------------------------------
  /// @brief
  /// Strong type structure is intended to be a replacement for function
  /// arguments where type-safety is needed. This is generally needed
  /// within a class which is why boosts STRONG_TYPEDEF macro does not
  /// work (as it cannot know what 'T' of the parent class is simply
  /// because it is a preprocessor)
  ///-------------------------------------------------------------------------
  template <typename T, tl_size T_UniqueCounter,
            typename T_Ptr = T*, typename T_Ref = T&>
  class StrongType_T
  {
  public:
    typedef T                                           value_type;
    typedef T_Ptr                                       pointer;
    typedef T_Ref                                       reference;
    typedef T const *                                   const_pointer;
    typedef T const &                                   const_reference;
    typedef StrongType_T<value_type, T_UniqueCounter>   this_type;

    // sel = selected
    typedef typename Loki::Select<
      Loki::TypeTraits<T>::isFundamental,
                   T, T_Ref>::Result                  const_sel_val_type;
    typedef typename Loki::Select<
      Loki::TypeTraits<T>::isFundamental,
      T, const_pointer>::Result                       const_sel_val_type_ptr;
    typedef typename Loki::Select<
      Loki::TypeTraits<T>::isFundamental,
      T, const_reference>::Result                     const_sel_val_type_ref;
    typedef typename Loki::Select<
      Loki::TypeTraits<T>::isFundamental,
      T, const_reference>::Result                     const_sel_return_type;

  public:

    // For complex types, const_selected_value_type is a REFERENCE but for
    // fundamental types, const_selected_value_type is passed by VALUE
    explicit StrongType_T(const_sel_val_type_ref a_value);
    StrongType_T(this_type const & a_other);

    this_type& operator= (const this_type& a_other);
    this_type& operator= (const_sel_val_type_ptr a_other);

    // Generally called operator T() or operator T&()
    operator const_sel_return_type () const;

    bool operator== (const this_type& a_other) const;
    bool operator< (const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(StrongType_T);

    enum { k_index = T_UniqueCounter };

    const_sel_val_type_ptr m_value;
  };

};};};

#define TLOC_EXTERN_TEMPLATE_STRONG_TYPE(_type_, _index_)\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_t::StrongType_T<_type_ TLOC_COMMA _index_>)

#endif