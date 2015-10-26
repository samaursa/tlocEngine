#include "tlocTestCommon.h"

#include <tlocAnimation/component_system/tlocTransformAnimation.h>
#include <tlocAnimation/component_system/tlocTransformAnimationSystem.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocPrefab/animation/tlocTransformAnimation.h>

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef anim_cs::TransformAnimation             component_type;
  typedef anim_cs::transform_animation_sptr       component_ptr;

  typedef anim_cs::transform_animation_system_vso system_vso;

  TEST_CASE("prefab/animation/TransformAnimation", "")
  {
    core_cs::component_pool_mgr_vso compMgr;
    core_cs::event_manager_vso      evtMgr;
    core_cs::entity_manager_vso     entMgr(evtMgr.get());

    system_vso                      system(evtMgr.get(), entMgr.get());
    TLOC_UNUSED(system);

    anim_t::keyframe_sequence_mat4f32 KFs;

    math_cs::Transform transform;

    using namespace anim_t::p_keyframe;
    {
      transform.SetPosition(math_t::Vec3f32(0, 0, 0));
      anim_t::keyframe_mat4f32 kf(transform.GetTransformation(), 0,
        anim_t::keyframe_mat4f32::interpolation_type(k_linear));
      KFs.AddKeyframe(kf);
    }

    {
      transform.SetPosition(math_t::Vec3f32(10.0f, 0, 0));
      anim_t::keyframe_mat4f32 kf(transform.GetTransformation(), 24 * 4,
        anim_t::keyframe_mat4f32::interpolation_type(k_linear));
      KFs.AddKeyframe(kf);
    }

    {
      transform.SetPosition(math_t::Vec3f32(0.0f, 0, 0));
      anim_t::keyframe_mat4f32 kf(transform.GetTransformation(), 24 * 8,
        anim_t::keyframe_mat4f32::interpolation_type(k_linear));
      KFs.AddKeyframe(kf);
    }

    {
      transform.SetPosition(math_t::Vec3f32(5.0f, 0, 0));
      anim_t::keyframe_mat4f32 kf(transform.GetTransformation(), 24 * 10,
        anim_t::keyframe_mat4f32::interpolation_type(k_linear));
      KFs.AddKeyframe(kf);
    }

    {
      transform.SetPosition(math_t::Vec3f32(0.0f, 0, 0));
      anim_t::keyframe_mat4f32 kf(transform.GetTransformation(), 24 * 12,
        anim_t::keyframe_mat4f32::interpolation_type(k_linear));
      KFs.AddKeyframe(kf);
    }
    
    //SECTION("Construct", "")
    {
      component_ptr ptr = pref_anim::TransformAnimation(entMgr.get(), compMgr.get())
        .Fps(20)
        .Loop(false)
        .Reverse(true)
        .Paused(true)
        .StartingFrame(2)
        .Construct(KFs);

      CHECK(ptr->GetTotalKeyframeSequences() == 1);
      CHECK(ptr->GetCurrentKeyframeSequence().GetTotalFrames() == 288);
      CHECK_FALSE(ptr->IsLooping());
      CHECK(ptr->IsReversed());
      CHECK(ptr->IsPaused());
    }

    //SECTION("Create", "")
    {
      entity_ptr ent =  pref_anim::TransformAnimation(entMgr.get(), compMgr.get())
        .Fps(20)
        .Loop(false)
        .Reverse(true)
        .Paused(true)
        .StartingFrame(2)
        .Create(KFs);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ptr->GetTotalKeyframeSequences() == 1);
      CHECK(ptr->GetCurrentKeyframeSequence().GetTotalFrames() == 288);
      CHECK_FALSE(ptr->IsLooping());
      CHECK(ptr->IsReversed());
      CHECK(ptr->IsPaused());
    }

    //SECTION("Add", "")
    {
      entity_ptr ent = entMgr->CreateEntity();

      pref_anim::TransformAnimation(entMgr.get(), compMgr.get())
        .Fps(20)
        .Loop(true)
        .Reverse(false)
        .Paused(false)
        .StartingFrame(2)
        .Add(ent, KFs);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ptr->GetTotalKeyframeSequences() == 1);
      CHECK(ptr->GetCurrentKeyframeSequence().GetTotalFrames() == 288);
      CHECK(ptr->IsLooping());
      CHECK_FALSE(ptr->IsReversed());
      CHECK_FALSE(ptr->IsPaused());
    }

    system->Initialize();
    system->ProcessActiveEntities();
  }
};
