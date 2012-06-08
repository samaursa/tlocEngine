#ifndef TLOC_MEMORY_POOL_H
#define TLOC_MEMORY_POOL_H

#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>

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

  namespace memory_pool_index_wrapper
  {
    template <typename T_ParentType, typename T_Elem, typename T_SizeType>
    class type
    {
    public:
      typedef T_Elem                                    value_type;
      typedef T_SizeType                                size_type;
      typedef type<T_ParentType, value_type, size_type> this_type;

      friend T_ParentType; // here this_type is the parent class

      // Visual studio gives an incorrect warning for the friend declaration
      // below. We must therefore disable it.
#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
#pragma warning(push)
#pragma warning(disable:4517)
#endif
      friend tl_array<this_type, Array_Unordered >::type;
#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
#pragma warning(pop)
#endif

      value_type& GetElement() { return m_element; }
      size_type   GetIndex() { return m_index; }

    private:

      type() {}
      type(const this_type& a_rhs)
      {
        m_element = a_rhs.m_element;
        m_index = a_rhs.m_index;
      }

      void DoSwap(this_type& a_rhs)
      {
        tlSwap(m_element, a_rhs.m_element);
        tlSwap(m_index, a_rhs.m_index);
      }

      value_type  m_element;
      size_type   m_index;
    };
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
  public:
    //------------------------------------------------------------------------
    // typedefs

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
    typedef MemoryPoolIndex<value_type,
                            policy_allocation_type,
                            policy_used_elements_type>  this_type;
    typedef memory_pool_index_wrapper::type
                            <this_type,
                             selected_type, size_type>  wrapper_type;
    typedef typename tl_array<wrapper_type,
                              Array_Unordered>::type    container_type;
    typedef typename container_type::iterator           iterator;
    typedef typename container_type::const_iterator     const_iterator;

    //------------------------------------------------------------------------
    // Methods

    MemoryPoolIndex();
    ~MemoryPoolIndex();

    void Initialize(size_type a_maxElements);

    // Returns MemoryPoolIndex<>::npos on failure
    wrapper_type& GetNext();
    void          Recycle(const wrapper_type& a_returnedElement);
    void          Recycle(tl_int a_index);
    void          RecycleAll();

    size_type   GetTotal() const;
    size_type   GetAvail() const;
    size_type   GetUsed() const;

    // Get iterator to the elements in use
    iterator        begin();
    const_iterator  begin() const;
    iterator        end();
    const_iterator  end() const;

    bool            IsInvalid(const wrapper_type& a_element) const;

  protected:

    tl_int          DoGetAvailIndex() const;

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
    tl_int                    m_numAvail;

    static wrapper_type npos;
  };

};};

#endif