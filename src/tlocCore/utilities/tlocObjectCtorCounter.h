#ifndef TLOC_OBJECT_CTOR_COUNTER_H
#define TLOC_OBJECT_CTOR_COUNTER_H

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace core { namespace utils {

  ///-------------------------------------------------------------------------
  /// @brief Counts number of all objects every created of this type
  ///-------------------------------------------------------------------------
  template <typename T>
  class ObjectCtorCounter
  {
    template <class T> friend class ObjectCounter;

  public:
    typedef tl_size     size_type;

    TL_STATIC_I TLOC_DECL_AND_DEF_GETTER_DIRECT
      (size_type, GetTotalInstantiations, m_count);

  protected:
    ObjectCtorCounter()
    {
      ++m_count;
    }
    ObjectCtorCounter(const ObjectCtorCounter&)
    {
      ++m_count;
    }

  private:
    static size_type m_count;
  };

  template <typename T>
  tl_uint  ObjectCtorCounter<T>::m_count = 0;

};};};

#endif