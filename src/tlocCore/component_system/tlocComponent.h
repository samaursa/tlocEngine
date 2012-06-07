#ifndef TLOC_COMPONENT_H
#define TLOC_COMPONENT_H

#include <tlocCore/component_system/tlocComponentType.h>

namespace tloc { namespace core {

  class Component
  {
  public:
    Component(components::type a_type) : m_type(a_type) {}

    component_type::type  GetType() { return m_type; }

  protected:
    component_type::type m_type;
  };

};};

#endif