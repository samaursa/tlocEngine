#ifndef _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_H_
#define _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_H_

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/utilities/tlocType.h>

namespace tloc { namespace core { namespace component_system {

  class ComponentPoolManager;

  //////////////////////////////////////////////////////////////////////////
  // ComponentPool_I

  class ComponentPool_I
  {
  public:
    typedef ComponentPool_I                         this_type;
    typedef containers::tl_array<this_type*>::type  cont_type;

  public:
    friend class ComponentPoolManager;

  public:
    virtual ~ComponentPool_I();

    template <typename T_PoolType>
    T_PoolType* GetAs()
    {
      return static_cast<T_PoolType*>(this);
    }

    template <typename T_PoolType>
    T_PoolType const * GetAs() const
    {
      return static_cast<T_PoolType const *>(this);
    }

  protected:
    ComponentPool_I();
  };

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
    typedef core::memory::MemoryPoolIndexed<T_Component>    pool_base_type;

    typedef T_Component                                     value_type;
    typedef ComponentPool_TI<value_type>                    this_type;

    typedef core::memory::MemoryPoolIndexed
            <value_type>                                    pool_type;
    typedef typename pool_type::iterator                    iterator;
    typedef typename pool_type::const_iterator              const_iterator;
    typedef typename pool_type::size_type                   size_type;

  public:
    virtual ~ComponentPool_TI();

    iterator        GetNext();
    iterator        begin();
    const_iterator  begin() const;
    iterator        end();
    const_iterator  end() const;

    ///-------------------------------------------------------------------------
    /// @brief
    /// Will recycle all the components that are not in use (i.e. their
    /// reference count is 1). Returns the iterator to the first unused element.
    ///-------------------------------------------------------------------------
    void            RecycleAllUnused();
    size_type       GetUsed() const;

  protected:
    ComponentPool_TI();

  private:
    pool_type     m_pool;
  };

  //////////////////////////////////////////////////////////////////////////
  // ComponentPoolManager

  class ComponentPoolManager
  {
  public:
    typedef ComponentPool_I                             component_pool_type;
    typedef tl_size                                     size_type;
    typedef containers::tl_array
      <component_pool_type*>::type                      cont_type;

    typedef cont_type::iterator                         iterator;
    typedef cont_type::const_iterator                   const_iterator;

    typedef core::component_system::components::value_type  component_type;

  public:
    ~ComponentPoolManager();

    template <typename T_Component>
    iterator CreateNewPool(component_type a_compNumber)
    {
      TLOC_ASSERT(Exists(a_compNumber) == false,
                  "ComponentPool of type a_compNumber already exists!");

      DoResize(a_compNumber + 1);

      iterator itr = m_pools.begin();
      core::advance(itr, a_compNumber);
      *itr = new ComponentPool_TI<T_Component>();

      return GetPool(a_compNumber);
    }

    void      DestroyPool(component_type a_number);
    iterator  GetPool(component_type a_number);
    bool      Exists(component_type a_number);

    size_type size() const;

    // Add a function GetPool<T> where T is the pool type

  private:
    // a_index = component's ID which will be used to resize the array to the
    // appropriate size if needed
    void DoResize(size_type a_index);

  private:
    cont_type m_pools;
  };

};};};

#endif