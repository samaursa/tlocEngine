#ifndef TLOC_COMPONENT_H
#define TLOC_COMPONENT_H

#include <tlocCore/component_system/tlocComponentType.h>

namespace tloc { namespace core { namespace component_system {

  class Component
  {
  public:
    Component(components::type a_type) : m_type(a_type) {}

    components::type  GetType() { return m_type; }

  protected:
    components::type m_type;
  };

};};};

#endif