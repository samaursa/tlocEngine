#pragma once

#include <tlocCore/base_classes/tlocNonCopyable.h>

namespace tloc { namespace core { namespace smart_ptr {

  template <typename T, typename T_BuildConfig>
  class VirtualStackObject
    : core_bclass::NonCopyable_I
  {
  public:
    typedef T                                   value_type;
    typedef T_BuildConfig                       build_config;

  public:
    explicit VirtualStackObject(const value_type& a_other)
      : m_value(a_other)
    { }

    ~VirtualStackObject()
    { }



  private:

    value_type        m_value;
  };

};};};