#ifndef TLOC_OBJECT_COUNTER_H
#define TLOC_OBJECT_COUNTER_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/utilities/tlocObjectCtorCounter.h>

namespace tloc { namespace core { namespace utils {

  ///-------------------------------------------------------------------------
  /// @brief Counter number of objects that have not yet been destroyed
  ///-------------------------------------------------------------------------
  template <typename T>
  class ObjectCounter : ObjectCtorCounter<T>
  {
  public:
    typedef ObjectCtorCounter<T>        base_type;
    typedef ObjectCounter<T>              this_type;

    typedef typename base_type::size_type size_type;

    using base_type::m_count;

    TL_STATIC_I TLOC_DECL_AND_DEF_GETTER_DIRECT
      (size_type, GetCurrentObjectCount, base_type::GetTotalInstantiations() );

  protected:
    ~ObjectCounter()                      { --m_count; }
  };

};};};

#endif