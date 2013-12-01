#ifndef _TLOC_CORE_COMMON_H_
#define _TLOC_CORE_COMMON_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that core uses should go here

namespace tloc {

  //////////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace core
  {
    namespace base_classes     {};
    namespace component_system {};
    namespace configs          {};
    namespace containers       {};
    namespace data_structs     {};
    namespace error            {};
    namespace logger           {};
    namespace io               {};
    namespace memory           {};
    namespace parsers          {};
    namespace platform         {};
    namespace rng              {};
    namespace smart_ptr        {};
    namespace string           {};
    namespace time             {};
    namespace types            {};
    namespace utils            {};
  };

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace core_bclass       = core::base_classes;
  namespace core_cs           = core::component_system;
  namespace core_cfg          = core::configs;
  namespace core_conts        = core::containers;
  namespace core_ds           = core::data_structs;
  namespace core_err          = core::error;
  namespace core_log          = core::logger;
  namespace core_io           = core::io;
  namespace core_mem          = core::memory;
  namespace core_parse        = core::parsers;
  namespace core_plat         = core::platform;
  namespace core_rng          = core::rng;
  namespace core_sptr         = core::smart_ptr;
  namespace core_str          = core::string;
  namespace core_time         = core::time;
  namespace core_t            = core::types;
  namespace core_utils        = core::utils;

};


#endif