#ifndef TLOC_COMPONENT_MAPPER_H
#define TLOC_COMPONENT_MAPPER_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/component_system/tlocComponent.h>

namespace tloc { namespace core { namespace component_system {

  ///-------------------------------------------------------------------------
  /// @brief Component mapper allows easy access to a component from a list
  ///-------------------------------------------------------------------------
  template <typename T>
  class ComponentMapper
  {
  public:
    typedef component_ptr_array                 component_list;
    typedef typename component_list::size_type  size_type;

    ComponentMapper(component_list const& a_list) : m_compList(a_list) {}

    size_type size() const { return m_compList.size(); }

    T& operator[](tl_int a_index)
    {
      return *(static_cast<T*>(m_compList[a_index]));
    }

  private:

    void operator = (const ComponentMapper& a_other) {}

    component_list const & m_compList;
  };

};};};

#endif