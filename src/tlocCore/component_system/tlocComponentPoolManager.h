#ifndef _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_H_
#define _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_H_

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/utilities/tlocType.h>

namespace tloc { namespace core { namespace component_system {

  class ComponentPoolManager;

  class ComponentPool_I
  {
  public:
    typedef ComponentPool_I                   this_type;
    typedef core::tl_array<this_type*>::type  cont_type;

  public:
    friend class ComponentPoolManager;

    virtual ~ComponentPool_I()
    { }

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
    ComponentPool_I()
    { }

  };

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
    virtual ~ComponentPool_TI()
    {
      iterator itr = begin();
      iterator itrEnd = end();

      for (; itr != itrEnd; ++itr)
      {
        TLOC_ASSERT(itr->GetElement().GetRefCount() == 1,
                    "Element still in use!");
      }
    }

    iterator        GetNext()
    { return m_pool.GetNext(); }

    iterator        begin()
    { return m_pool.begin(); }

    const_iterator  begin() const
    { return m_pool.begin(); }

    iterator        end()
    { return m_pool.end(); }

    const_iterator  end() const
    { return m_pool.end(); }

    ///-------------------------------------------------------------------------
    /// @brief
    /// Will recycle all the components that are not in use (i.e. their
    /// reference count is 1). Returns the iterator to the first unused element.
    ///-------------------------------------------------------------------------
    void RecycleAllUnused()
    {
      iterator itr    = begin();
      iterator itrEnd = end();

      for (; itr != itrEnd; ++itr)
      {
        if (itr->GetElement().GetRefCount() == 1)
        {
          m_pool.RecycleElement(itr);
        }
      }
    }

    size_type       GetUsed() const
    { return m_pool.GetUsed(); }

  protected:
    ComponentPool_TI()
    {
    }

  private:
    pool_type     m_pool;
  };

  class ComponentPoolManager
  {
  public:
    typedef ComponentPool_I                             component_pool_type;
    typedef tl_size                                     size_type;
    typedef core::tl_array<component_pool_type*>::type  cont_type;

    typedef cont_type::iterator                         iterator;
    typedef cont_type::const_iterator                   const_iterator;

    typedef core::component_system::components::value_type  component_type;

  public:
    ~ComponentPoolManager()
    {
      // Cannot use this because of protected member in ComponentPool_I
      delete_ptrs(m_pools.begin(), m_pools.end());
    }

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

    void DestroyPool(component_type a_number)
    {
      const size_type index = a_number;
      TLOC_ASSERT(index < m_pools.size(),
                  "Pool not allocated for passed component type");
      TLOC_UNUSED(index);
    }

    iterator GetPool(component_type a_number)
    {
      TLOC_ASSERT( (size_type)a_number < m_pools.size(),
                  "Pool not allocated for passed component type");

      iterator itr = m_pools.begin();
      core::advance(itr, a_number);

      return itr;
    }

    bool Exists(component_type a_number)
    {
      if (core::utils::CastNumber<size_type, component_type>(a_number) >= size())
      { return false; }

      iterator itr = m_pools.begin();
      advance(itr, a_number);
      if (*itr == NULL)
      { return false; }

      return true;
    }

    size_type size()
    { return m_pools.size(); }

    // Add a function GetPool<T> where T is the pool type

  private:
    // a_index = component's ID which will be used to resize the array to the
    // appropriate size if needed
    void DoResize(size_type a_index)
    {
      if (a_index >= m_pools.size())
      { m_pools.resize(a_index, nullptr); }
    }

  private:
    cont_type m_pools;
  };

};};};

#endif