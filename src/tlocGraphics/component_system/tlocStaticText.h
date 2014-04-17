#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_STATIC_TEXT_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_STATIC_TEXT_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/memory/tlocBufferArg.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocGraphics/component_system/tlocTextAlignment.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace graphics { namespace component_system {

  class StaticText
    : public core_cs::Component_T<StaticText, components::static_text>
  {
  public:
    typedef StaticText                                      this_type;
    typedef Component_T<this_type, components::static_text> base_type;
    typedef f32                                             real_type;
    typedef core_str::StringW                               str_type;
    typedef ushort                                          font_size_type;
    typedef alignment::align_type                           align_type;

  public:
    StaticText();
    explicit StaticText(BufferArgW a_text, 
                        align_type a_alignment = alignment::k_align_left);

    void Align(align_type a_alignment);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(BufferArgW, Set, m_text);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(str_type, Get, m_text);
    TLOC_DECL_AND_DEF_GETTER(align_type, GetAlignment, m_alignment);

  private:
    str_type                m_text;
    align_type              m_alignment;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(StaticText, static_text);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(StaticText, static_text);
  TLOC_TYPEDEF_COMPONENT_POOL(StaticText, static_text);

};};};

#endif