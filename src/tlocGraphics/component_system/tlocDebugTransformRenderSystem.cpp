#include "tlocDebugTransformSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocMath/component_system/tlocTransform.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef DebugTransformRenderSystem::error_type          error_type;

  // ///////////////////////////////////////////////////////////////////////
  // DebugTransformRenderSystem

  DebugTransformRenderSystem::
    DebugTransformRenderSystem(event_manager_ptr a_eventMgr, 
                               entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr, 
                Variadic<component_type, 1>(math_cs::components::transform))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  DebugTransformRenderSystem::
    ~DebugTransformRenderSystem()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    DebugTransformRenderSystem::
    InitializeEntity(entity_ptr a_ent)
  {
    base_type::InitializeEntity(a_ent);
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    DebugTransformRenderSystem::
    ShutdownEntity(entity_ptr )
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DebugTransformRenderSystem::
    Post_ProcessActiveEntities(f64 a_deltaT)
  {
    base_type::Post_ProcessActiveEntities(a_deltaT);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    DebugTransformRenderSystem::
    OnComponentInsert(const core_cs::EntityComponentEvent&)
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    DebugTransformRenderSystem::
    OnComponentRemove(const core_cs::EntityComponentEvent&)
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
  void 
    DebugTransformRenderSystem::
    OnComponentDisable(const core_cs::EntityComponentEvent&)
  { } 

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    DebugTransformRenderSystem::
    OnComponentEnable(const core_cs::EntityComponentEvent&)
  { }

};};};