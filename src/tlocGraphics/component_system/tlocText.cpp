#include "tlocText.h"

namespace tloc { namespace graphics { namespace component_system {

  enum 
  {
    k_text_updated,
    k_alignment_updated,
    k_count
  };

  // ///////////////////////////////////////////////////////////////////////
  // Text

  Text::
    Text()
    : base_type(k_component_type)
    , m_alignment(alignment::k_align_left)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Text::
    Text(BufferArgW a_text, align_type a_alignment)
    : base_type(k_component_type)
    , m_text(a_text)
    , m_alignment(a_alignment)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Text::
    Align(align_type a_alignment)
  { 
    base_type::SetUpdateRequired(true);
    m_flags.Mark(k_alignment_updated);
    m_alignment = a_alignment;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Text::
    Set(BufferArgW a_text)
  {
    base_type::SetUpdateRequired(true);
    m_flags.Mark(k_text_updated);
    m_text = a_text;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Text::
    TextUpdated() const
  {
    return m_flags.ReturnAndUnmark(k_text_updated);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Text::
    AlignmentUpdated() const
  {
    return m_flags.ReturnAndUnmark(k_alignment_updated);
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

using namespace tloc::gfx_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Text);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(Text);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(Text);