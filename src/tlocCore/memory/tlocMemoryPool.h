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



  //------------------------------------------------------------------------
  // Intrusive Memory Pool

  ///-------------------------------------------------------------------------
  /// @brief
  /// This is the simplest memory pool. It allows fast retrieval of free
  /// and used elements by caching the elements with an index. The pool
  /// assumes that the element will have a default constructor. This type
  /// of of a memory pool is useful for pools of objects such as
  /// particles.
  ///
  /// @T_Capacity specifies the size of memory pool which cannot be changed
  ///             at runtime. If you want the pool to dynamically increase in
  ///             size, then set T_Capacity to 0
  ///-------------------------------------------------------------------------
  template <class T,
            tl_uint T_Capacity = 0,
            class T_PolicyAllocation = memory_pool_policies::Allocate_On_Stack,
            class T_PolicyUsedElements = memory_pool_policies::Track_Used_Elements>
  class MemoryPoolIndex
  {
  public:

#pragma region typedefs

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

    typedef typename Loki::Int2Type<T_Capacity>       pool_size_type;

    // The value_type can be T or T* depending on the policy
    typedef T                                           value_type;
    typedef tl_int                                      index_type;
    typedef tl_size                                     size_type;

    // Select T or T* as the value_type
    typedef typename Loki::Select
      <policy_allocation_result_type::value,
       value_type, value_type*>::Result                 selected_type;

    typedef MemoryPoolIndex<value_type,
                            T_Capacity,
                            policy_allocation_type,
                            policy_used_elements_type>  this_type;

  private:
#include "tlocMemoryPoolIndexWrapper.h"
  public:

    // Declare our element wrapper
    typedef Wrapper <selected_type, index_type>  wrapper_type;

    // Select the proper array
    typedef typename tl_array<wrapper_type, Array_Unordered>::type d_array_type;
    typedef typename tl_array_fixed<wrapper_type,
                                    pool_size_type::value>::type   s_array_type;

    typedef typename
      Loki::Select<pool_size_type::value == 0,
                   d_array_type, s_array_type >::Result   container_type;

    // Declare iterator types
    typedef typename container_type::iterator             iterator;
    typedef typename container_type::const_iterator       const_iterator;

#pragma endregion typedefs

  public:

    //------------------------------------------------------------------------
    // Methods

    MemoryPoolIndex();
    ~MemoryPoolIndex();

    void Initialize(size_type a_initialSize);

    ///-------------------------------------------------------------------------
    /// @brief
    /// Gets the next available element. Returns ::npos if no more avail
    /// elements.
    ///
    /// @return The next.
    ///-------------------------------------------------------------------------
    wrapper_type& GetNext();

    ///-------------------------------------------------------------------------
    /// @brief Recycles an element. Invalidates element indexes.
    ///
    /// @param  a_returnedElement The returned element.
    ///-------------------------------------------------------------------------
    void          Recycle(const wrapper_type& a_returnedElement);

    ///-------------------------------------------------------------------------
    /// @brief
    /// Recycles an element at a particular index. Index must be smaller
    /// than # of used elements.
    ///
    /// @param  a_index Zero-based index of a.
    ///-------------------------------------------------------------------------
    void          Recycle(index_type a_index);

    ///-------------------------------------------------------------------------
    /// @brief Recycle all elements
    ///-------------------------------------------------------------------------
    void          RecycleAll();

    ///-------------------------------------------------------------------------
    /// @brief
    /// Gets an element at a particular index (must be smaller than # of
    /// used elements.
    ///
    /// @param  a_index Zero-based index of a.
    ///
    /// @return The indexed value.
    ///-------------------------------------------------------------------------
    wrapper_type& operator[](index_type a_index);
    const wrapper_type& operator[](index_type a_index) const;

    size_type   GetTotal() const;
    size_type   GetAvail() const;
    size_type   GetUsed() const;

    ///-------------------------------------------------------------------------
    /// @brief Gets the first used element iff begin() != end()
    ///
    /// @return iterator to the elements
    ///-------------------------------------------------------------------------
    iterator        begin();
    const_iterator  begin() const;

    ///-------------------------------------------------------------------------
    /// @brief Gets the iterator to the last used element + 1
    ///
    /// @return iterator to past-the-end of used elements
    ///-------------------------------------------------------------------------
    iterator        end();
    const_iterator  end() const;

    ///-------------------------------------------------------------------------
    /// @brief Query if 'a_element' is valid.
    ///
    /// @param  a_element The element.
    ///
    /// @return true if valid, false if not.
    ///-------------------------------------------------------------------------
    bool            IsValid(const wrapper_type& a_element) const;

  protected:

    typedef type_false                                 fixed_container_selected;
    typedef type_true                                  dynamic_container_selected;

    // Used for selecting functions wrt the container type
    typedef typename Loki::Select<pool_size_type::value == 0,
      type_true, type_false>::Result
                                                        container_dynamic_type;

  protected:
    void            DoResize(size_type, fixed_container_selected);
    void            DoResize(size_type a_newSize, dynamic_container_selected);

    void            DoInitializeRange(iterator a_begin, iterator a_end,
                                      index_type a_startingIndex);

    bool            DoExpand(fixed_container_selected);
    bool            DoExpand(dynamic_container_selected);

    index_type      DoGetAvailIndex() const;

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
    index_type                m_numAvail;

    static wrapper_type       npos;
    static const index_type   sm_invalidIndex;
  };

};};

#endif