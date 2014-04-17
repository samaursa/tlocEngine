#include "tlocText_I.h"

namespace tloc { namespace graphics { namespace component_system {

#define TLOC_TEXT_TEMPS   typename T_Derived
#define TLOC_TEXT_PARAMS  T_Derived

  // ///////////////////////////////////////////////////////////////////////
  // Text_TI

  Text_I::
    Text_I()
    : m_alignment(alignment::k_align_left)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Text_I::
    Text_I(BufferArgW a_text, align_type a_alignment)
    : m_text(a_text)
    , m_alignment(a_alignment)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Text_I::
    ~Text_I()
  { }

};};};