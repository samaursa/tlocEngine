#pragma once // make VS happy (if header is not included in any cpp, VS complains)

#ifndef TLOC_UI_ERROR_TYPES_H
#define TLOC_UI_ERROR_TYPES_H

#include <tlocUI/tlocUIBase.h>

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/error/tlocErrorTypes.h>

namespace tloc { namespace ui { namespace error {

  enum Type
  {
    error_ui_generic = core::error::error_groups::error_ui
  };

};};};

#endif
