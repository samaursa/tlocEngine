#pragma once

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/configs/tlocBuildConfig.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>

namespace tloc { namespace core { namespace smart_ptr {

  template <typename T, typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
  class VirtualStackObject
    : core_bclass::NonCopyable_I
  {
  public:
    typedef T                                                 value_type;
    typedef T_BuildConfig                                     build_config;

    typedef VirtualStackObject<value_type, build_config>      this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>           ptr_type;

  public:
    VirtualStackObject()
      : m_value()
      , m_valuePtr(&m_value)
    { }

    explicit VirtualStackObject(const value_type& a_other)
      : m_value(a_other)
      , m_valuePtr(&m_value)
    { }

    VirtualStackObject(const this_type& a_other)
      : m_value(a_other.m_value)
      , m_valuePtr(&m_value)
    { }

    ~VirtualStackObject()
    {
      TLOC_ASSERT_LOW_LEVEL(m_valuePtr.unique(),
        "This object appears to be still in use");

      // this ensures that no checks are performed after m_value is automatically
      // deleted
      m_valuePtr.reset();
    }

    this_type& operator=(this_type a_other)
    {
      a_other.swap(*this);
      return *this;
    }

    this_type& operator=(const value_type& a_newValue)
    {
      this_type(a_newValue).swap(*this);
      return *this;
    }

    operator value_type&()
    { return m_value; }

    operator const value_type&() const
    { return m_value; }

    ptr_type get()
    { return m_valuePtr; }

    const ptr_type& get() const
    { return m_valuePtr; }

    bool operator==(const this_type& a_other)
    { return m_value == a_other.m_value; }

    bool operator==(const value_type& a_other)
    { return m_value == a_other; }

    bool operator!=(const this_type& a_other)
    { return m_value != a_other.m_value; }

    bool operator!=(const value_type& a_other)
    { return m_value != a_other; }

    void swap(this_type& a_other)
    {
      using core::swap;

      swap(m_value, a_other.m_value);
    }

  private:

    value_type        m_value;
    ptr_type          m_valuePtr;
  };

};};};