#ifndef _TLOC_CORE_BASE_CLASSES_DEBUG_NAME_H_
#define _TLOC_CORE_BASE_CLASSES_DEBUG_NAME_H_

#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/configs/tlocBuildConfig.h>

namespace tloc{ namespace core { namespace base_classes {

  // ///////////////////////////////////////////////////////////////////////
  // DebugName<>

  template <typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
  class DebugName_TI
  {
  public:
    typedef core_str::String                string_type;

  protected:
    DebugName_TI(BufferArg a_name)
      : m_name(a_name)
    { }

    ~DebugName_TI()
    { }
    
    void          SetDebugName(BufferArg a_name)
    { m_name = a_name; }

    const char*   GetDebugName() const
    { return m_name.c_str(); }

  private:
    core_str::String m_name;
  };

  // ///////////////////////////////////////////////////////////////////////
  // DebugName<Release>

  template <>
  class DebugName_TI<core_cfg::p_build_config::Release>
  {
  public:
    typedef core_str::String                string_type;

  protected:
    DebugName_TI(BufferArg )
    { }

    ~DebugName_TI()
    { }
    
    void          SetDebugName(BufferArg ) { }
    const char*   GetDebugName() const
    { return "No name assigned - RELEASE CONFIG"; }
  };

  // -----------------------------------------------------------------------
  // typedef

  typedef DebugName_TI<>                              DebugName;

};};};

#endif