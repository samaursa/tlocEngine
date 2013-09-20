#include "tlocSceneGraphSystem.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocNode.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  // ///////////////////////////////////////////////////////////////////////
  // typedefs

  typedef SceneGraphSystem::error_type            error_type;

  // ///////////////////////////////////////////////////////////////////////
  // SceneGraphSystem

  SceneGraphSystem::
    SceneGraphSystem
    (event_manager_sptr a_eventMgr, entity_manager_sptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(components::node))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    SceneGraphSystem::
    Pre_Initialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    SceneGraphSystem::
    InitializeEntity(const entity_manager* a_mgr, const entity_type* a_ent)
  {
    TLOC_UNUSED_2(a_mgr, a_ent);

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    SceneGraphSystem::
    ShutdownEntity(const entity_manager* a_mgr, const entity_type* a_ent)
  {
    TLOC_UNUSED_2(a_mgr, a_ent);

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneGraphSystem::
    Pre_ProcessActiveEntities(f64)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneGraphSystem::
    ProcessEntity(const entity_manager* a_mgr, const entity_type* a_ent,
                  f64 a_deltaT)
  {
    TLOC_UNUSED_3(a_mgr, a_ent, a_deltaT);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneGraphSystem::
    Post_ProcessActiveEntities(f64)
  {
  }

};};};
