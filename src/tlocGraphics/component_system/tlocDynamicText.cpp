#include "tlocDynamicText.h"

namespace tloc { namespace graphics { namespace component_system {

  enum 
  {
    k_text_updated,
    k_alignment_updated,
    k_count
  };

  // ///////////////////////////////////////////////////////////////////////
  // Text

  DynamicText::
    DynamicText()
    : base_type("DynamicText")
    , Text_I()
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  DynamicText::
    DynamicText(BufferArgW a_text, font_ptr a_font, align_type a_alignment, 
                align_type a_horAlignment)
    : base_type("DynamicText")
    , Text_I(a_text, a_font, a_alignment, a_horAlignment)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    DynamicText::
    SetAlignment(align_type a_alignment)
  { 
    base_type::SetUpdateRequired(true);
    m_flags.Mark(k_alignment_updated);
    Text_I::SetAlignment(a_alignment);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    DynamicText::
    SetHorizontalAlignment(align_type a_alignment)
  { 
    base_type::SetUpdateRequired(true);
    m_flags.Mark(k_alignment_updated);
    Text_I::SetHorizontalAlignment(a_alignment);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DynamicText::
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
    DynamicText::
    IsTextUpdated() const
  {
    return m_flags.ReturnAndUnmark(k_text_updated);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    DynamicText::
    IsAlignmentUpdated() const
  {
    return m_flags.ReturnAndUnmark(k_alignment_updated);
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

using namespace tloc::gfx_cs;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(DynamicText);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(DynamicText);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(DynamicText);