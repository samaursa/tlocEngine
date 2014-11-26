#ifndef TLOC_MEMORY_H
#define TLOC_MEMORY_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocCore/memory/tlocAllocators.h>

#ifndef TLOC_BASE_H
# error "Must include tlocBase.h before including tlocMemory.h"
#endif

namespace tloc { namespace core {

  namespace memory
  {
    extern bool IsValidHeapPointer(const void * a_userData);
  };

  template <typename T_InputIterator, typename T_OutputIterator>
  T_OutputIterator
    uninitialized_copy(T_InputIterator aRangeBegin,
                       T_InputIterator aRangeEnd,
                       T_OutputIterator aDestRangeBegin);

  template <typename T_InputIterator, typename T_Count, typename T_ValueType>
  void
    uninitialized_fill_n(T_InputIterator a_first,
                         T_Count a_count,
                         const T_ValueType& a_value);

  namespace detail {

    typedef type_true       IsRawItr;
    typedef type_false      IsComplexItr;
    typedef type_true       HasTrivalAssign;
    typedef type_false      HasComplexAssign;

    template <typename T_InputIterator, typename T_OutputIterator>
    T_OutputIterator
      DoUninitializedCopyWithItrType(T_InputIterator a_rangeBegin,
                                     T_InputIterator a_rangeEnd,
                                     T_OutputIterator a_destRangeBegin,
                                     IsRawItr);

    template <typename T_InputIterator, typename T_OutputIterator>
    T_OutputIterator
      DoUninitializedCopyWithItrType(T_InputIterator a_rangeBegin,
                                     T_InputIterator a_rangeEnd,
                                     T_OutputIterator a_destRangeBegin,
                                     IsComplexItr);

    template <typename T_InputIterator, typename T_OutputIterator,
              typename T_ValueType>
    T_OutputIterator
      DoUninitializedCopyWithValueType(T_InputIterator a_rangeBegin,
                                       T_InputIterator a_rangeEnd,
                                       T_OutputIterator a_destRangeBegin,
                                       T_ValueType);

    template <typename T_InputIterator, typename T_OutputIterator,
              typename T_ValueType>
    T_OutputIterator
      DoUninitializedCopy(T_InputIterator aRangeBegin,
                          T_InputIterator aRangeEnd,
                          T_OutputIterator aDestRangeBegin,
                          T_ValueType,
                          HasTrivalAssign);

    template <typename T_InputIterator, typename T_OutputIterator,
              typename T_ValueType>
    T_OutputIterator
      DoUninitializedCopy(T_InputIterator aRangeBegin,
                          T_InputIterator aRangeEnd,
                          T_OutputIterator aDestRangeBegin,
                          T_ValueType,
                          HasComplexAssign);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType>
    void
      DoUninitializedFillNWithItrType(T_InputIterator a_first,
                                      T_Count a_count,
                                      const T_ValueType& a_value,
                                      IsRawItr);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType>
    void
      DoUninitializedFillNWithItrType(T_InputIterator a_first,
                                      T_Count a_count,
                                      const T_ValueType& a_value,
                                      IsComplexItr);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    void
      DoUninitializedFillNWithValueType(T_InputIterator a_first,
                                        T_Count a_count,
                                        const T_ValueType& a_value,
                                        T_ValueTypeInputIterator);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    void
      DoUninitializedFillN(T_InputIterator a_first,
                           T_Count a_count,
                           const T_ValueType& a_value,
                           T_ValueTypeInputIterator,
                           HasTrivalAssign);

    template <typename T_InputIterator, typename T_Count, typename T_ValueType,
              typename T_ValueTypeInputIterator>
    void
      DoUninitializedFillN(T_InputIterator a_first,
                           T_Count a_count,
                           const T_ValueType& a_value,
                           T_ValueTypeInputIterator,
                           HasComplexAssign);
  };

};};

namespace tloc { namespace core { namespace memory {

  // ///////////////////////////////////////////////////////////////////////
  // Slightly safer version of memcpy where you don't have to worry about
  // complex types being copied incorrectly

  namespace priv {

    typedef type_true                                 simple_type;
    typedef type_false                                complex_type;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T>
    T* 
      DoMemCopy(T* a_destination, const T* a_source, tl_size a_elementsToCopy, 
                simple_type)
    { return (T*)memcpy(a_destination, a_source, a_elementsToCopy * sizeof(T)); }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T>
    T* 
      DoMemCopy(T* a_destination, const T* a_source, tl_size a_elementsToCopy, 
                complex_type)
    { 
      T* dest = a_destination;
      for (tl_size i = 0; i < a_elementsToCopy; ++i)
      {
        *dest = *a_source;
        ++dest; ++a_source;
      }

      return a_destination;
    }
  };

  template <typename T>
  T* MemCopy(T* a_destination, const T* a_source, tl_size a_elementsToCopy)
  {
    typedef Loki::Int2Type<Loki::TypeTraits<T>::isFundamental> simple_or_complex;
    return priv::DoMemCopy(a_destination, a_source, a_elementsToCopy, 
                           simple_or_complex());
  }

  // ///////////////////////////////////////////////////////////////////////
  // ObjectCreator

  // All resources require a ResourceCreator class that can construct the
  // resource properly.
  template <typename T_Object>
  class CreateObject
  {
  public:
    TLOC_STATIC_ASSERT_FALSE(T_Object,
      Object_must_have_a_specialized_ObjectCreator_class);
  };

  // -----------------------------------------------------------------------
  // macro helpers

#define TLOC_DECL_AND_DEF_CREATE_OBJECT_CTOR_DEF(_full_type_)\
namespace tloc { namespace core { namespace memory {\
  template <>\
  class CreateObject<_full_type_>\
  {\
  public:\
    typedef _full_type_                               value_type;\
    typedef core_sptr::VirtualPtr<value_type>         pointer;\
  public:\
    pointer  OnHeap()\
    {\
      return pointer(new value_type());\
    }\
    \
    value_type  OnStack()\
    {\
      return value_type();\
    }\
  };\
};};}


#define TLOC_DECL_AND_DEF_CREATE_OBJECT_CTOR_1PARAM(_full_type_, _T1_)\
namespace tloc { namespace core { namespace memory {\
  template <>\
  class CreateObject<_full_type_>\
  {\
  public:\
    typedef _full_type_                               value_type;\
    typedef core_sptr::VirtualPtr<value_type>         pointer;\
  public:\
    pointer  OnHeap(const _T1_& a)\
    {\
      return pointer(new value_type(a));\
    }\
    \
    value_type  OnStack(const _T1_& a)\
    {\
      return value_type(a);\
    }\
  };\
};};}

#define TLOC_DECL_AND_DEF_CREATE_OBJECT_CTOR_2PARAM(_full_type_, _T1_, _T2_)\
namespace tloc { namespace core { namespace memory {\
  template <>\
  class CreateObject<_full_type_>\
  {\
  public:\
    typedef _full_type_                               value_type;\
    typedef core_sptr::VirtualPtr<value_type>         pointer;\
  public:\
    pointer  OnHeap(const _T1_& a, const _T2_& b)\
    {\
      return pointer(new value_type(a, b));\
    }\
    \
    value_type  OnStack(const _T1_& a, const _T2_& b)\
    {\
      return value_type(a, b);\
    }\
  };\
};};}

#define TLOC_DECL_AND_DEF_CREATE_OBJECT_CTOR_3PARAM(_full_type_, _T1_, _T2_, _T3_)\
namespace tloc { namespace core { namespace memory {\
  template <>\
  class CreateObject<_full_type_>\
  {\
  public:\
    typedef _full_type_                               value_type;\
    typedef core_sptr::VirtualPtr<value_type>         pointer;\
  public:\
    pointer  OnHeap(const _T1_& a, const _T2_& b, const _T3_& c)\
    {\
      return pointer(new value_type(a, b, c));\
    }\
    \
    value_type  OnStack(const _T1_& a, const _T2_& b, const _T3_& c)\
    {\
      return value_type(a, b, c);\
    }\
  };\
};};}

};};};


#endif  // TLOC_MEMORY_H
