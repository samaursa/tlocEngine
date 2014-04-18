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
    , Text_I()
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Text::
    Text(BufferArgW a_text, align_type a_alignment)
    : base_type(k_component_type)
    , Text_I(a_text, a_alignment)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Text::
    SetAlignment(align_type a_alignment)
  { 
    base_type::SetUpdateRequired(true);
    m_flags.Mark(k_alignment_updated);
    Text_I::SetAlignment(a_alignment);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Text::
    Set(BufferArgW a_text)
  {
    base_type::SetUpdateRequired(true);
    m_flags.Mark(k_text_updated);

    // if left aligned already, then don't mark alignment to be updated
    if (m_flags.IsUnMarked(k_alignment_updated) && GetAlignment() != 
        alignment::k_align_left)
    { m_flags.Mark(k_alignment_updated); }

    Text_I::Set(a_text);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Text::
    IsTextUpdated() const
  {
    return m_flags.ReturnAndUnmark(k_text_updated);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Text::
    IsAlignmentUpdated() const
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