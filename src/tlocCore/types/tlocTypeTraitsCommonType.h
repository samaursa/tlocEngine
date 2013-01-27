#ifndef _TLOC_TYPES_TYPE_TRAITS_COMMON_TYPE_H_
#define _TLOC_TYPES_TYPE_TRAITS_COMMON_TYPE_H_

#include <tlocCore/types/tlocBasicTypes.h>
#include <3rdParty/loki/TypeTraits.h>

namespace tloc
{
  namespace type_traits
  {
    struct no_common_type_exists;

    ///-------------------------------------------------------------------------
    /// @brief Extracts a common type from the passed types
    ///-------------------------------------------------------------------------
    template <class T1, class T2>
    struct common_type
    {
      typedef
      typename Loki::Select
        <
          Loki::IsSameType<T1, T2>::value,
          T1,
          typename Loki::Select
          <
            // Implicit conversion from T1 to T2
            Loki::Conversion<T1, T2>::exists,
            T2,
            typename Loki::Select
            <
              Loki::Conversion<T2, T1>::exists,
              T1,
              no_common_type_exists
            >::Result
          >::Result
        >::Result                         type;
    };
  };
};

#endif