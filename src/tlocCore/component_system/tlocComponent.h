#ifndef TLOC_COMPONENT_H
#define TLOC_COMPONENT_H

#include <tlocCore/component_system/tlocComponentType.h>

namespace tloc { namespace core { namespace component_system {

  class Component
  {
  public:
    typedef components::value_type    component_type;

    Component(component_type a_type) : m_type(a_type) {}

    component_type GetType() { return m_type; }

  protected:
    component_type m_type;
  };

};};};

#endif