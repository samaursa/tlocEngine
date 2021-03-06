#ifndef TLOC_MEMORY_POOL_H
#define TLOC_MEMORY_POOL_H

#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>

#include <tlocCore/smart_ptr/tlocVirtualPtr.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.h>

#include <tlocCore/memory/tlocMemoryPoolIndexedWrapper.h>

namespace tloc { namespace core { namespace memory {

  //------------------------------------------------------------------------
  // Memory pool index policies

  namespace p_memory_pool_index
  {
    namespace allocation
    {
      // Memory pool instantiates the element on the stack
      struct On_Stack{};
      // Memory pool instantiates the element on the heap. If there are many
      // elements and they are very large in size, this is the better policy to
      // use to avoid stack overflows
      struct On_Heap{};
    };

    namespace indexing
    {
      // Uses the built-in wrapper to store the user element
      struct Wrapper { };

      // The user element must have an m_index variable
      struct User { };
    };

    TL_I tl_int GetInvalidIndex();
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
  ///
  /// @note this memory pool MUST NOT be explicitly instantiated because
  /// some methods will not compile due to different policy types
  ///-------------------------------------------------------------------------
  template <class T,
            tl_uint T_Capacity = 0,
            class T_PolicyIndexing = p_memory_pool_index::indexing::Wrapper>
  class MemoryPoolIndexed
    : public core_bclass::NonCopyable_I
  {
  public:
    enum { k_capacity = T_Capacity };

  public:
    typedef typename Loki::Int2Type<T_Capacity>         pool_size_type;

    typedef typename
      Loki::Select<pool_size_type::value == 0,
        p_memory_pool_index::allocation::On_Heap,
        p_memory_pool_index::allocation::On_Stack>
        ::Result                                        policy_allocation_type;

    typedef T_PolicyIndexing                            policy_indexing_type;

    typedef typename
      Loki::Int2Type<Loki::IsSameType<policy_allocation_type,
      p_memory_pool_index::allocation::On_Stack>::value>
                                                  policy_allocation_result_type;

    typedef typename
      Loki::Int2Type<Loki::IsSameType<policy_indexing_type,
      p_memory_pool_index::indexing::Wrapper>::value>
                                                  policy_indexing_result_type;

    // The value_type can be T or T* depending on the policy
    typedef T                                           value_type;
    typedef core_sptr::VirtualStackObjectBase_TI
              <value_type>                              value_type_vso;
    typedef core_sptr::VirtualPtr<value_type>           pointer;
    typedef tl_int                                      index_type;
    typedef tl_size                                     size_type;

    typedef MemoryPoolIndexed<value_type,
                            T_Capacity,
                            policy_allocation_type>     this_type;

    typedef type_false                                 fixed_container_selected;
    typedef type_true                                  dynamic_container_selected;

    typedef p_memory_pool_index::allocation::On_Stack  allocation_on_stack;
    typedef p_memory_pool_index::allocation::On_Heap   allocation_on_heap;

    typedef priv::MemoryPoolIndexedWrapper<value_type>          wrapper_value_type;
    typedef core_sptr::VirtualStackObjectBase_TI
              <wrapper_value_type>                              wrapper_value_type_vso;
    typedef core_sptr::VirtualPtr<wrapper_value_type>           wrapper_pointer;

    // Select T or T* as the value_type
    typedef typename Loki::Select
      <policy_allocation_result_type::value,
       value_type_vso, pointer>::Result                   selected_user_type;

    typedef typename Loki::Select
      <policy_allocation_result_type::value,
       wrapper_value_type_vso,
       wrapper_pointer>::Result                           selected_wrapper_type;

    typedef typename Loki::Select
      <policy_indexing_result_type::value,
       wrapper_value_type, value_type>::Result            selected_value_type;

    // Declare our element wrapper
    typedef typename Loki::Select
      <
        policy_indexing_result_type::value,
        selected_wrapper_type, selected_user_type
      >::Result                                           final_value_type;

    // Select the proper array
    typedef typename
      containers::tl_array<final_value_type,
               containers::Array_Unordered>::type         d_array_type;
    typedef typename containers::tl_array_fixed
      <final_value_type, pool_size_type::value>::type     s_array_type;

    typedef typename
      Loki::Select
      <
        pool_size_type::value == 0,
        d_array_type, s_array_type
      >::Result                                           container_type;

    // Declare iterator types
    typedef typename container_type::iterator             iterator;
    typedef typename container_type::const_iterator       const_iterator;

  public:

    //------------------------------------------------------------------------
    // Methods

    MemoryPoolIndexed();
    explicit MemoryPoolIndexed(size_type a_initialSize);
    ~MemoryPoolIndexed();

    void Resize(size_type a_size);

    ///-------------------------------------------------------------------------
    /// @brief
    /// Gets the next available element. Returns ::npos if no more avail
    /// elements.
    ///
    /// @return The next.
    ///-------------------------------------------------------------------------
    iterator          GetNext();
    final_value_type& GetNextValue();

    iterator          Find(const final_value_type& a_returnedElement);

    ///-------------------------------------------------------------------------
    /// @brief Recycles an element. Invalidates element indexes.
    ///
    /// @param  a_returnedElement The returned element.
    ///-------------------------------------------------------------------------
    iterator          RecycleElement(iterator a_returnedElement);

    ///-------------------------------------------------------------------------
    /// @brief
    /// Recycles an element at a particular index. Index must be smaller
    /// than # of used elements.
    ///
    /// @param  a_index Zero-based index of a.
    ///-------------------------------------------------------------------------
    void              RecycleAtIndex(index_type a_index);

    ///-------------------------------------------------------------------------
    /// @brief Recycle all elements
    ///-------------------------------------------------------------------------
    void              RecycleAll();

    ///-------------------------------------------------------------------------
    /// @brief
    /// Gets an element at a particular index (must be smaller than # of
    /// used elements.
    ///
    /// @param  a_index Zero-based index of a.
    ///
    /// @return The indexed value.
    ///-------------------------------------------------------------------------
    final_value_type&       operator[](index_type a_index);
    final_value_type const& operator[](index_type a_index) const;

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
    bool            IsValid(const iterator a_element) const;


  public:

    // Used for selecting functions wrt the container type
    typedef typename Loki::Select<pool_size_type::value == 0,
      type_true, type_false>::Result
                                                        container_dynamic_type;

  protected:

    index_type      DoGetAvailIndex() const;
    bool            DoIsInitialized() const;

    container_type            m_allElements;
    index_type                m_numAvail;
  };

// -----------------------------------------------------------------------
// explicit instantiation macros

#define TLOC_EXTERN_TEMPLATE_MEM_POOL(_type_, _capacity_, _policyIndexing_)\
  TLOC_EXTERN_TEMPLATE_VIRTUAL_PTR(_type_);\
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(_type_);\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_mem::MemoryPoolIndexed<_type_ TLOC_COMMA _capacity_ TLOC_COMMA _policyIndexing_>)

#define TLOC_EXTERN_TEMPLATE_MEM_POOL_DYN(_type_, _policyIndexing_)\
  TLOC_EXTERN_TEMPLATE_VIRTUAL_PTR(_type_);\
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(_type_);\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_mem::MemoryPoolIndexed<_type_ TLOC_COMMA 0 TLOC_COMMA _policyIndexing_>)

// -----------------------------------------------------------------------
// fixed memory pools

#define TLOC_EXTERN_TEMPLATE_MEM_POOL_USING_WRAPPER(_type_, _capacity_)\
  TLOC_EXTERN_TEMPLATE_MEM_POOL(_type_, _capacity_, \
    tloc::core_mem::p_memory_pool_index::indexing::Wrapper);\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_mem::priv::MemoryPoolIndexedWrapper<_type_>);\
  TLOC_EXTERN_TEMPLATE_VIRTUAL_PTR(tloc::core_mem::priv::MemoryPoolIndexedWrapper<_type_>)

#define TLOC_EXTERN_TEMPLATE_MEM_POOL_ON_STACK_USER(_type_, _capacity_)\
  TLOC_EXTERN_TEMPLATE_MEM_POOL(_type_, _capacity_, \
    tloc::core_mem::p_memory_pool_index::allocation::On_Stack, \
    tloc::core_mem::p_memory_pool_index::indexing::User)

// -----------------------------------------------------------------------
// dynamic memory pools

#define TLOC_EXTERN_TEMPLATE_MEM_POOL_DYN_USING_WRAPPER(_type_)\
  TLOC_EXTERN_TEMPLATE_MEM_POOL_DYN(_type_, \
    tloc::core_mem::p_memory_pool_index::indexing::Wrapper);\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_mem::priv::MemoryPoolIndexedWrapper<_type_>);\
  TLOC_EXTERN_TEMPLATE_VIRTUAL_PTR(tloc::core_mem::priv::MemoryPoolIndexedWrapper<_type_>)

#define TLOC_EXTERN_TEMPLATE_MEM_POOL_DYN_USER(_type_)\
  TLOC_EXTERN_TEMPLATE_MEM_POOL_DYN(_type_, _capacity_, \
    tloc::core_mem::p_memory_pool_index::indexing::User)

};};};

#endif