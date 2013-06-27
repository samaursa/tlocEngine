#include "tlocArcBallSystem.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

#include <tlocGraphics/component_system/tlocArcBall.h>

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocProjectionComponent.h>
#include <tlocMath/utilities/tlocPythagoras.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // typedefs

  using namespace core::data_structs;

  // ///////////////////////////////////////////////////////////////////////
  // ArcBallSystem

  ArcBallSystem::
    ArcBallSystem
    (event_manager_sptr a_eventMgr, entity_manager_sptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(components::arcball))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBallSystem::
    ProcessEntity(const entity_manager* ,
                  const entity_type* a_ent, f64 )
  {
    using math_utils::Pythagorasf32;

    if (a_ent->HasComponent(math_cs::components::transform) == false)
    { return; }

    typedef math_cs::Transform::position_type     pos_type;
    typedef math_cs::Transform::orientation_type  ori_type;
    typedef gfx_cs::ArcBall::angle_type           angle_type;

    math_cs::Transform* t = a_ent->GetComponent<math_cs::Transform>();
    gfx_cs::ArcBall* arcBall = a_ent->GetComponent<gfx_cs::ArcBall>();

    pos_type pos = t->GetPosition();
    ori_type ori = t->GetOrientation();

    pos_type vecToRot = pos - arcBall->GetFocus();

    angle_type vAngle = arcBall->GetVerticalAngle();
    angle_type hAngle = arcBall->GetHorizontalAngle();

    pos_type leftVec;
    ori.GetCol(0, leftVec);

    pos_type upVec;
    ori.GetCol(1, leftVec);

    ori_type rotMatVertical;
    rotMatVertical.MakeRotation(leftVec, vAngle);

    ori_type rotMatHorizontal;
    rotMatHorizontal.MakeRotation(upVec, hAngle);

    pos = rotMatVertical * pos;
    pos = rotMatVertical * pos;

    t->SetPosition(pos);
  }

};};};