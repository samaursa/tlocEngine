#ifndef _TLOC_PREFAB_GRAPHICS_DYNAMIC_TEXT_H_
#define _TLOC_PREFAB_GRAPHICS_DYNAMIC_TEXT_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocTextAlignment.h>
#include <tlocGraphics/component_system/tlocDynamicText.h>
#include <tlocGraphics/media/tlocFont.h>

namespace tloc { namespace prefab { namespace graphics {

  class DynamicText
    : public Prefab_TI<DynamicText, gfx_cs::DynamicText>
  {
  public:
    typedef DynamicText                             this_type;
    typedef Prefab_TI<this_type, component_type>    base_type;

    typedef core_str::StringW                       string_type;
    typedef gfx_cs::alignment::align_type           align_type;
    typedef gfx_med::font_sptr                      font_ptr;

  public:
    DynamicText(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct(BufferArgW a_text, font_ptr a_font) const;

    entity_ptr    Create(BufferArgW a_text, font_ptr a_font) const;
    void          Add(entity_ptr a_ent, BufferArgW a_text, font_ptr a_font) const;

    TLOC_DECL_PARAM_VAR(align_type, Alignment, m_alignment);
  };

};};};

#endif