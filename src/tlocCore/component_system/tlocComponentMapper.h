#ifndef TLOC_COMPONENT_MAPPER_H
#define TLOC_COMPONENT_MAPPER_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>

namespace tloc { namespace core { namespace component_system {

  ///-------------------------------------------------------------------------
  /// @brief Component mapper allows easy access to a component from a list
  ///-------------------------------------------------------------------------
  template <typename T>
  class ComponentMapper
  {
  public:
    typedef component_sptr_array                component_list;
    typedef typename component_list::size_type  size_type;

    ComponentMapper(component_list const& a_list) : m_compList(a_list) {}

    size_type size() const { return m_compList.size(); }

    core_sptr::SharedPtr<T> operator[](size_type a_index)
    {
      return core_sptr::static_pointer_cast<T>(m_compList[a_index]);
    }

  private:

    void operator = (const ComponentMapper& a_other) {}

    component_list const & m_compList;
  };

};};};

#endif