#ifndef _TLOC_PREFAB_GRAPHICS_DYNAMIC_TEXT_H_
#define _TLOC_PREFAB_GRAPHICS_DYNAMIC_TEXT_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocTextAlignment.h>

namespace tloc { namespace prefab { namespace graphics {

  class DynamicText
    : public Prefab_I
  {
  public:
    typedef DynamicText                       this_type;
    typedef core_str::StringW                 string_type;
    typedef gfx_cs::alignment::align_type     align_type;

  public:
    DynamicText(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr)
      : Prefab_I(a_entMgr, a_poolMgr)
      , m_alignment(gfx_cs::alignment::k_align_left)
    { }

    entity_ptr  Create(BufferArgW a_text);
    void        Add(entity_ptr a_ent, BufferArgW a_text);

    TLOC_DECL_PARAM_VAR(align_type, Alignment, m_alignment);
  };

};};};

#endif