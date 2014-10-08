#ifndef _TLOC_CORE_MEMORY_MEMORY_POOL_INDEXED_WRAPPER_H_
#define _TLOC_CORE_MEMORY_MEMORY_POOL_INDEXED_WRAPPER_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace core { namespace memory { namespace priv {

  template <typename T_Elem>
  class MemoryPoolIndexedWrapper
  {
  public:
    typedef T_Elem                                      value_type;
    // we assume that wrapper_value_type is a VirtualStackOBject, therefore
    // ptr_type is the VirtualPointer for this VirtualStackObject
    typedef core_sptr::
      VirtualStackObjectBase_TI<value_type>              value_type_vso;

    typedef typename
      value_type_vso::pointer                           pointer;
    typedef typename
      value_type_vso::const_pointer                     const_pointer;

    typedef tl_int                                      index_type;
    typedef MemoryPoolIndexedWrapper<value_type>        wrapper_type;

    template <class T_1, tl_uint T_2,
    class T_3, class T_4> friend class        MemoryPoolIndexed;

    MemoryPoolIndexedWrapper();
    MemoryPoolIndexedWrapper(const wrapper_type& a_rhs);

    pointer         GetValuePtr();
    const_pointer   GetValuePtr() const;
    void            SetValue(const value_type& a_value);
    void            SetValue(const_pointer a_value);

    wrapper_type&   operator=(wrapper_type a_other);
    bool            operator==(const wrapper_type& a_rhs);

    TLOC_DECL_AND_DEF_GETTER(index_type, GetIndex, m_index);
    TLOC_DECL_AND_DEF_GETTER_DIRECT(index_type, DoGetIndexRef, m_index);

    void swap(wrapper_type& a_rhs);

  private:
    value_type_vso  m_element;
    index_type      m_index;
  };

};};};};

#endif