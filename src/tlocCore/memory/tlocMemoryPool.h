#ifndef TLOC_MEMORY_POOL_H
#define TLOC_MEMORY_POOL_H

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/types/tlocConditionalType.h>

namespace tloc { namespace core {

  //------------------------------------------------------------------------
  // Memory pool policies

  namespace memory_pool_policies
  {
    struct TrackUsedElements
    {
      template <class T_Container, typename T_Element>
      void TrackElement(T_Container& a_container, const T_Element& a_elem)
      {
        a_container.push_back(a_elem);
      }
    };

    struct IgnoreUsedElements
    {
      template <class T_Container, typename T_Element>
      void TrackElement(T_Container&, const T_Element&)
      {
      }
    };

    // Memory pool instantiates the element on the stack
    struct AllocateOnStack {};
    // Memory pool instantiates the element on the heap. If there are many
    // elements and they are very large in size, this is the better policy to
    // use to avoid stack overflows
    struct AllocateOnHeap {};
  };

  //------------------------------------------------------------------------
  // Intrusive Memory Pool

  ///-------------------------------------------------------------------------
  /// @brief This is the simplest memory pool. It allows fast retrieval of
  /// free and used elements by caching the elements with an index. The pool
  /// assumes that the element will have a default constructor. This type of
  /// of a memory pool is useful for pools of objects such as particles
  ///-------------------------------------------------------------------------
  template <class T,
            class T_PolicyAllocation = memory_pool_policies::AllocateOnStack,
            class T_PolicyUsedElements = memory_pool_policies::TrackUsedElements>
  class MemoryPoolByIndex
  {

    //------------------------------------------------------------------------
    // Memory Pool Element Wrapper

    struct ElementWrapper
    {
      T   m_element;
      T   m_index;
    };

  public:

    // The value_type can be T or T* depending on the policy
    typedef T                                           value_type;

    typedef Loki::Select<Loki::IsSameType<T_PolicyAllocation,
                         memory_pool_policies::AllocateOnStack>::value,
                         value_type, value_type*>
                                                        selected_type;

    typedef tl_array<selected_type>::type               container_type;
    typedef container_type::iterator                    iterator;
    typedef container_type::const_iterator              const_iterator;
    typedef tl_size                                     size_type;

    MemoryPoolByIndex();
    ~MemoryPoolByIndex();

    void Initialize();
    void Allocate(size_type a_maxElements);

    value_type& GetNext();
    void        Recycle(const value_type& a_returnedElement);

    size_type   GetAvail() const;
    size_type   GetUsed() const;

    // Get iterator to the elements in use
    iterator        begin();
    const_iterator  begin() const;
    iterator        end();
    const_iterator  end() const;

  protected:

    container_type    m_allElements;
    container_type    m_usedElements;
    size_type         m_availElements;

    tl_int            m_availIndex;
  };

};};

#endif