#pragma once

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/containers/tlocContainers.h>

namespace tloc { namespace core { namespace resources {

  class ResourceFactory;

  // ///////////////////////////////////////////////////////////////////////
  // ResourcePool

  class ResourcePool_I
    : public core_bclass::NonCopyable_I
  {
  public:
    typedef ResourcePool_I                                    this_type;
    typedef containers::tl_array<this_type*>::type            cont_type;

  public:
    friend class ResourceFactory;

  public:
    virtual ~ResourcePool_I();

    template <typename T_PoolType>
    T_PoolType*   GetAs()
    {
      return static_cast<T_PoolType*>(this);
    }

    template <typename T_PoolType>
    T_PoolType* const * GetAs() const
    {
      return static_cast<T_PoolType const *>(this);
    }
  };

  // ///////////////////////////////////////////////////////////////////////
  // ResourcePool_TI

  template <typename T_Resource>
  class ResourcePool_TI
    : public ResourcePool_I
  {
  public:
    friend class ResourceFactory;

  public:
    typedef ResourcePool_I                                  base_type;
    typedef T_Resource                                      value_type;
    typedef ResourcePool_TI<value_type>                     this_type;

    typedef core_mem::MemoryPoolIndexed<value_type>         pool_type;
    typedef typename pool_type::iterator                    iterator;
    typedef typename pool_type::const_iterator              const_iterator;
    typedef typename pool_type::size_type                   size_type;

  public:
    virtual ~ResourcePool_TI();

  };

};};};