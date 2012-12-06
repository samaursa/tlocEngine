#ifndef _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_H_
#define _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_H_

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/component_system/tlocComponentType.h>

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

  protected:
    ComponentPool_I()
    { }

  };

  template <typename T_Component>
  class ComponentPool_TI : public ComponentPool_I
  {
  public:
    typedef ComponentPool_I                                 base_type;
    typedef T_Component                                     component_type;
    typedef ComponentPool_TI<component_type>                this_type;
    //typedef core::memory::MemoryPoolIndex<component_type>   pool_type;

  public:

  protected:
    ComponentPool_TI();

  private:
    //pool_type m_pool;
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
      DoResize(a_compNumber);

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
    }



    //iterator GetPool(component_type a_number)
    //{
    //  TLOC_ASSERT( (size_type)a_number < m_pools.size(),
    //              "Pool not allocated for passed component type");

    //  iterator itr = m_pools.begin();
    //  core::advance(itr, a_number);

    //  return itr;
    //}

  private:
    // a_index = component's ID which will be used to resize the array to the
    // appropriate size if needed
    void DoResize(size_type a_index)
    {
      if (a_index >= m_pools.size())
      { m_pools.resize(a_index, NULL); }
    }

  private:
    cont_type m_pools;
  };

};};};

#endif