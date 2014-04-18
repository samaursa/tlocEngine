#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXT_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXT_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/utilities/tlocCheckpoints.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocGraphics/component_system/tlocTextAlignment.h>
#include <tlocGraphics/component_system/tlocText_I.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace graphics { namespace component_system {

  class Text
    : public core_cs::Component_T<Text, components::text>
    , public Text_I
  {
  public:
    typedef Text                                            this_type;
    typedef Component_T<this_type, components::text>        base_type;

  public:
    Text();
    explicit Text(BufferArgW a_text, 
                  align_type a_alignment = alignment::k_align_left);

    void SetAlignment(align_type a_alignment);

    bool IsTextUpdated() const;
    bool IsAlignmentUpdated() const;

    TLOC_DECL_SETTER_BY_VALUE(BufferArgW, Set);

  private:
    mutable core_utils::Checkpoints m_flags;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Text, text);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Text, text);
  TLOC_TYPEDEF_COMPONENT_POOL(Text, text);

};};};

#endif