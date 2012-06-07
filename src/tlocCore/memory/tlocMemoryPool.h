#ifndef TLOC_MEMORY_POOL_H
#define TLOC_MEMORY_POOL_H

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/types/tlocTypeTraits.h>

namespace tloc { namespace core {

  //------------------------------------------------------------------------
  // Memory pool policies

  namespace memory_pool_policies
  {
    struct Track_Used_Elements
    {
      template <class T_Container, typename T_Element>
      void TrackElement(T_Container& a_container, const T_Element& a_elem)
      {
        a_container.push_back(a_elem);
      }
    };

    struct Ignore_Used_Elements
    {
      template <class T_Container, typename T_Element>
      void TrackElement(T_Container&, const T_Element&)
      {
      }
    };

    // Memory pool instantiates the element on the stack
    struct Allocate_On_Stack {};
    // Memory pool instantiates the element on the heap. If there are many
    // elements and they are very large in size, this is the better policy to
    // use to avoid stack overflows
    struct Allocate_On_Heap {};
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
            class T_PolicyAllocation = memory_pool_policies::Allocate_On_Stack,
            class T_PolicyUsedElements = memory_pool_policies::Track_Used_Elements>
  class MemoryPoolIndex
  {

    //------------------------------------------------------------------------
    // Memory Pool Element Wrapper
    template <typename T_Elem, typename T_SizeType>
    struct ElementWrapper
    {
      typedef T_Elem      value_type;
      typedef T_SizeType  size_type;

      ElementWrapper() {}

      value_type  m_element;
      size_type   m_index;
    };

  public:

    typedef T_PolicyAllocation                        policy_allocation_type;
    typedef T_PolicyUsedElements                      policy_used_elements_type;

    typedef typename
      Loki::Int2Type<Loki::IsSameType<policy_allocation_type,
                     memory_pool_policies::Allocate_On_Stack>::value>
                                                  policy_allocation_result_type;

    typedef typename
      Loki::Int2Type<Loki::IsSameType<policy_used_elements_type,
                     memory_pool_policies::Track_Used_Elements>::value>
                                                  policy_used_elements_result_type;

    // The value_type can be T or T* depending on the policy
    typedef T                                           value_type;
    typedef tl_size                                     size_type;
    typedef Loki::Select
      <policy_allocation_result_type::value,
       value_type, value_type*>                         selected_type;

    typedef ElementWrapper<selected_type, size_type>    element_wrapper_type;

    typedef typename tl_array<element_wrapper_type>::type        container_type;
    typedef typename container_type::iterator                    iterator;
    typedef typename container_type::const_iterator              const_iterator;

    MemoryPoolIndex();
    ~MemoryPoolIndex();

    void Initialize(size_type a_maxElements);

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

    void            DoNewElement(iterator,
                                 memory_pool_policies::Allocate_On_Stack);
    void            DoNewElement(iterator a_pos,
                                 memory_pool_policies::Allocate_On_Heap);

    template <typename T_Element>
    void            DoSetElement(T_Element& a_elem, const value_type& a_value,
                                 memory_pool_policies::Allocate_On_Stack);
    template <typename T_Element>
    void            DoSetElement(T_Element& a_elem, const value_type& a_value,
                                 memory_pool_policies::Allocate_On_Heap);

    template <typename T_Element>
    void            DoSetIndex(T_Element& a_elem, size_type a_index,
                                 memory_pool_policies::Allocate_On_Stack);
    template <typename T_Element>
    void            DoSetIndex(T_Element& a_elem, size_type a_index,
                                 memory_pool_policies::Allocate_On_Heap);

    void            DoCleanup(memory_pool_policies::Allocate_On_Stack);
    void            DoCleanup(memory_pool_policies::Allocate_On_Heap);

    bool            DoIsInitialized();

    container_type            m_allElements;
    container_type            m_usedElements;
    tl_array_size             m_availElements;

    tl_int            m_availIndex;
  };

};};

#endif