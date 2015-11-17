#ifndef _TLOC_COMPONENT_MAPPER_H_
#define _TLOC_COMPONENT_MAPPER_H_

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>

namespace tloc { namespace core { namespace component_system {

  typedef core_cs::EntityManager  entMgr;

  ///-------------------------------------------------------------------------
  /// @brief Component mapper allows easy access to a component from a list
  ///-------------------------------------------------------------------------
  template <typename T, typename T_ItrType = Entity::const_component_iterator>
  class ComponentMapper
    : core_bclass::non_copyable_i
  {
  public:
    typedef T_ItrType                                   itr_type;
    typedef T                                           value_type;
    typedef tl_size                                     size_type;

    ComponentMapper(itr_type a_begin, itr_type a_end) 
      : m_begin(a_begin)
      , m_end(a_end)
    { }

    size_type size() const { return core::distance(m_begin, m_end); }

    core_sptr::SharedPtr<value_type>
      operator[](size_type a_index) const
    {
      TLOC_ASSERT(a_index < size(), "Index out of bounds");
      itr_type itr = m_begin;
      advance(itr, a_index);
      return core_sptr::static_pointer_cast<value_type>(*itr);
    }

  private:
    itr_type m_begin, m_end;
  };

};};};

#endif