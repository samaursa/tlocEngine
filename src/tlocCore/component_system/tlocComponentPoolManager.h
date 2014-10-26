#ifndef _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_H_
#define _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_H_

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/utilities/tlocType.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

namespace tloc { namespace core { namespace component_system {

  class ComponentPoolManager;

  //////////////////////////////////////////////////////////////////////////
  // ComponentPool_I

  class ComponentPool_I
    : public core_bclass::NonCopyable_I
  {
  public:
    typedef ComponentPool_I                         this_type;
    typedef tl_size                                 size_type;

  public:
    friend class ComponentPoolManager;

  public:
    virtual ~ComponentPool_I();

    template <typename T_PoolType>
    T_PoolType*         GetAs()
    { return static_cast<T_PoolType*>(this); }

    template <typename T_PoolType>
    T_PoolType const *  GetAs() const
    { return static_cast<T_PoolType const *>(this); }

    virtual size_type RecycleAllUnused() = 0;

  protected:
    ComponentPool_I();
  };

  TLOC_TYPEDEF_VIRTUAL_PTR(ComponentPool_I, component_pool);

  //////////////////////////////////////////////////////////////////////////
  // ComponentPool_TI

  template <typename T_Component>
  class ComponentPool_TI
    : public ComponentPool_I
  {
  public:
    friend class ComponentPoolManager;

  public:
    typedef ComponentPool_I                                 base_type;
    typedef T_Component                                     value_type;
    typedef core_sptr::SharedPtr<value_type>                pointer;

    typedef ComponentPool_TI<value_type>                    this_type;

    typedef core::memory::MemoryPoolIndexed
            <pointer>                                       pool_type;
    typedef typename pool_type::iterator                    iterator;
    typedef typename pool_type::final_value_type            final_value_type;
    typedef typename pool_type::const_iterator              const_iterator;
    typedef typename pool_type::size_type                   size_type;

  public:
    virtual ~ComponentPool_TI();

    iterator          GetNext();
    final_value_type& GetNextValue();

    iterator          begin();
    const_iterator    begin() const;
    iterator          end();
    const_iterator    end() const;

    ///-------------------------------------------------------------------------
    /// @brief
    /// Will recycle all the components that are not in use (i.e. their
    /// reference count is 1).
    ///-------------------------------------------------------------------------
    size_type         RecycleAllUnused();
    size_type         GetUsed() const;

  protected:
    ComponentPool_TI();

  private:
    pool_type     m_pool;
  };

#define TLOC_TYPEDEF_COMPONENT_POOL(_component_, _typedef_)\
    typedef tloc::core_cs::ComponentPool_TI<_component_>      _typedef_##_pool;\
    TLOC_TYPEDEF_VIRTUAL_PTR(_typedef_##_pool, _typedef_##_pool)

  //////////////////////////////////////////////////////////////////////////
  // ComponentPoolManager

  namespace p_component_pool_manager
  {
    template <typename T>
    struct ComponentID
    {
      enum { k_value = T::k_component_type };
    };

    template <typename T>
    struct ComponentID<core_sptr::VirtualPtr<T> >
    {
      enum { k_value = T::k_component_type };
    };
  };

  class ComponentPoolManager
    : public core_bclass::NonCopyable_I
  {
  public:
    typedef ComponentPool_I                             component_pool_type;
    typedef component_pool_vptr                         component_pool_ptr;
    typedef tl_size                                     size_type;
    typedef containers::tl_array
      <component_pool_ptr>::type                        cont_type;

    typedef cont_type::iterator                         iterator;
    typedef cont_type::const_iterator                   const_iterator;

    typedef core::component_system::components::value_type  component_type;

  public:
    ComponentPoolManager();
    ~ComponentPoolManager();

    template <typename T_Component>
    core_sptr::VirtualPtr<ComponentPool_TI<T_Component> >
                        CreateNewPool();

    template <typename T_Component>
    core_sptr::VirtualPtr<ComponentPool_TI<T_Component> >
                        GetPool();
    component_pool_ptr  GetPool(component_type a_type);

    template <typename T_Component>
    core_sptr::VirtualPtr<ComponentPool_TI<T_Component> >
                        GetOrCreatePool();

    template <typename T_Component>
    void                DestroyPool();
    void                DestroyPool(component_type a_type);

    bool                Exists(component_type a_type);

    iterator            begin();
    const_iterator      begin() const;

    iterator            end();
    const_iterator      end() const;

    // Returns the size of the pool container, not the number of 'active' pools
    size_type           size() const;

    // Returns the number of 'created pools - destroyed pools'
    size_type           GetNumActivePools() const;

    size_type           RecycleAllUnused();

  private:
    // a_index = component's ID which will be used to resize the array to the
    // appropriate size if needed
    void DoResize(size_type a_index);

  private:
    cont_type m_pools;
    size_type m_numActivePools;
  };

  //------------------------------------------------------------------------
  // template definitions
  //
  // NOTES: The following template definitions do not require the component
  //        ID because it is deduced at compile time. The methods currently
  //        work with T_Component = Component OR VirtualPtr<Component> where
  //        the component ID is deduced by the
  //        p_component_pool_manager::ComponentID<> helpers

  template <typename T_Component>
  core_sptr::VirtualPtr<ComponentPool_TI<T_Component> >
    ComponentPoolManager::
    CreateNewPool()
  {
    const tl_int compNumber =
      p_component_pool_manager::ComponentID<T_Component>::k_value;

    TLOC_ASSERT(Exists(compNumber) == false,
      "ComponentPool of type a_compNumber already exists!");

    DoResize(compNumber + 1);

    ++m_numActivePools;

    iterator itr = m_pools.begin();
    core::advance(itr, compNumber);
    itr->reset(new ComponentPool_TI<T_Component>());

    component_pool_ptr cp = GetPool(compNumber);
    return core_sptr::static_pointer_cast<ComponentPool_TI<T_Component> >(cp);
  }

  template <typename T_Component>
  core_sptr::VirtualPtr<ComponentPool_TI<T_Component> >
    ComponentPoolManager::
    GetPool()
  {
    const tl_int compNumber =
      p_component_pool_manager::ComponentID<T_Component>::k_value;

    component_pool_ptr cp = GetPool(compNumber);
    return core_sptr::static_pointer_cast<ComponentPool_TI<T_Component> >(cp);
  }

  template <typename T_Component>
  core_sptr::VirtualPtr<ComponentPool_TI<T_Component> >
    ComponentPoolManager::
    GetOrCreatePool()
  {
    const tl_int compNumber =
      p_component_pool_manager::ComponentID<T_Component>::k_value;

    core_sptr::VirtualPtr<ComponentPool_TI<T_Component> > toRet;

    if (Exists(compNumber))
    { toRet = GetPool<T_Component>(); }
    else
    { toRet = CreateNewPool<T_Component>(); }

    return toRet;
  }

  template <typename T_Component>
  void
    ComponentPoolManager::
    DestroyPool()
  {
    const tl_int compNumber =
      p_component_pool_manager::ComponentID<T_Component>::k_value;

    DestroyPool(compNumber);
  }

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(ComponentPoolManager, component_pool_mgr);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(ComponentPoolManager, component_pool_mgr);

};};};

#endif