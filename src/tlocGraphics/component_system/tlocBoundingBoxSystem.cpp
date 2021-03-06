#include "tlocBoundingBoxSystem.h"

#include <tlocMath/tlocBounds.h>

#include <tlocCore/logging/tlocLogger.h>

#include <tlocGraphics/component_system/tlocMesh.h>
#include <tlocGraphics/component_system/tlocBoundingBox.h>
#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace graphics { namespace component_system {

  namespace {

    template <typename T_BoundsType, typename T_MeshArray, typename T_BoundsOut>
    void DoCalculateBoundingBox(const T_MeshArray& a_mesh, T_BoundsOut& a_out)
    {
      typename T_BoundsType::vec_cont positions;
      for (auto itr = a_mesh.begin(), itrEnd = a_mesh.end(); itr != itrEnd; ++itr)
      { positions.push_back(itr->GetPosition()); }

      T_BoundsType b(positions);
      a_out = T_BoundsOut(b.GetMin(), b.GetMax());
    }

    template <typename T_BoundsType, typename T_MeshArray, typename T_BoundsOut>
    void DoCalculateBoundingCircle(const T_MeshArray& a_mesh, T_BoundsOut& a_out)
    {
      typename T_BoundsType::vec_cont positions;
      for (auto itr = a_mesh.begin(), itrEnd = a_mesh.end(); itr != itrEnd; ++itr)
      { positions.push_back(itr->GetPosition()); }

      typedef typename T_BoundsOut::position position;
      typedef typename T_BoundsOut::radius   radius;

      T_BoundsType b(positions);
      a_out = T_BoundsOut(radius(b.GetRadius()), position(b.GetCenter()));
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      DoCalculateBoundingBox(const gfx_cs::Mesh& a_mesh, 
                             gfx_cs::BoundingBox3D::bounds_type& a_out3d,
                             gfx_cs::BoundingBox2D::bounds_type& a_out2d,
                             gfx_cs::BoundingBox2D::circular_bounds_type& a_outCirc2d, 
                             bool a_circular = false)
    {
      switch(a_mesh.GetVertexType())
      {
        case(GL_FLOAT_VEC2):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fp>();

          if (a_circular == false)
          { DoCalculateBoundingBox<math::bounds_2d_f32>(arr, a_out2d); }
          else
          { DoCalculateBoundingCircle<math::circular_bounds_2d_f32>(arr, a_outCirc2d); }

          break;
        }
        case(GL_FLOAT_VEC3):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fp>();
          DoCalculateBoundingBox<math::bounds_3d_f32>(arr, a_out3d);
          break;
        }
        // POSITION2F
        case(TLOC_GL_POSITION2F_NORMAL3F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fpn>();

          if (a_circular == false)
          { DoCalculateBoundingBox<math::bounds_2d_f32>(arr, a_out2d); }
          else
          { DoCalculateBoundingCircle<math::circular_bounds_2d_f32>(arr, a_outCirc2d); }

          break;
        }
        case(TLOC_GL_POSITION2F_TEXTURE2F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fpt>();

          if (a_circular == false)
          { DoCalculateBoundingBox<math::bounds_2d_f32>(arr, a_out2d); }
          else
          { DoCalculateBoundingCircle<math::circular_bounds_2d_f32>(arr, a_outCirc2d); }

          break;
        }
        case(TLOC_GL_POSITION2F_COLOR4F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fpc>();

          if (a_circular == false)
          { DoCalculateBoundingBox<math::bounds_2d_f32>(arr, a_out2d); }
          else
          { DoCalculateBoundingCircle<math::circular_bounds_2d_f32>(arr, a_outCirc2d); }

          break;
        }
        case(TLOC_GL_POSITION2F_NORMAL3F_COLOR4F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fpnc>();

          if (a_circular == false)
          { DoCalculateBoundingBox<math::bounds_2d_f32>(arr, a_out2d); }
          else
          { DoCalculateBoundingCircle<math::circular_bounds_2d_f32>(arr, a_outCirc2d); }

          break;
        }
        case(TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fpnt>();

          if (a_circular == false)
          { DoCalculateBoundingBox<math::bounds_2d_f32>(arr, a_out2d); }
          else
          { DoCalculateBoundingCircle<math::circular_bounds_2d_f32>(arr, a_outCirc2d); }

          break;
        }
        case(TLOC_GL_POSITION2F_NORMAL3F_COLOR4F_TEXTURE2F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fpnct>();

          if (a_circular == false)
          { DoCalculateBoundingBox<math::bounds_2d_f32>(arr, a_out2d); }
          else
          { DoCalculateBoundingCircle<math::circular_bounds_2d_f32>(arr, a_outCirc2d); }

          break;
        }
        // POSITION3F
        case(TLOC_GL_POSITION3F_NORMAL3F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fpn>();
          DoCalculateBoundingBox<math::bounds_3d_f32>(arr, a_out3d);
          break;
        }
        case(TLOC_GL_POSITION3F_TEXTURE2F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fpt>();
          DoCalculateBoundingBox<math::bounds_3d_f32>(arr, a_out3d);
          break;
        }
        case(TLOC_GL_POSITION3F_COLOR4F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fpc>();
          DoCalculateBoundingBox<math::bounds_3d_f32>(arr, a_out3d);
          break;
        }
        case(TLOC_GL_POSITION3F_NORMAL3F_COLOR4F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fpnc>();
          DoCalculateBoundingBox<math::bounds_3d_f32>(arr, a_out3d);
          break;
        }
        case(TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fpnt>();
          DoCalculateBoundingBox<math::bounds_3d_f32>(arr, a_out3d);
          break;
        }
        case(TLOC_GL_POSITION3F_TEXTURE2F_TBN):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fptm>();
          DoCalculateBoundingBox<math::bounds_3d_f32>(arr, a_out3d);
          break;
        }
        case(TLOC_GL_POSITION3F_NORMAL3F_COLOR4F_TEXTURE2F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fpnct>();
          DoCalculateBoundingBox<math::bounds_3d_f32>(arr, a_out3d);
          break;
        }
        default: TLOC_LOG_GFX_ERR_FILENAME_ONLY() 
          << "Unsupported vertex type (" << a_mesh.GetVertexType() 
          << ") in Mesh. Failed to create bounding box.";
      }
    }

  };

  // ///////////////////////////////////////////////////////////////////////
  // BoundingBoxSystem

  BoundingBoxSystem::
    BoundingBoxSystem(event_manager_ptr a_eventMgr, entity_manager_ptr a_entMgr)
    : base_type(a_eventMgr, a_entMgr,
                register_type().Add<BoundingBox2D>().Add<BoundingBox3D>(),
                "BoundingBoxSystem")
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    BoundingBoxSystem::
    InitializeEntity(entity_ptr a_ent) -> error_type
  { 
    gfx_cs::BoundingBox2D::bounds_type          bt2d;
    gfx_cs::BoundingBox2D::circular_bounds_type circ_bt2d;
    gfx_cs::BoundingBox3D::bounds_type          bt3d;

    auto mesh = a_ent->GetComponent<gfx_cs::Mesh>();
    if (mesh == nullptr)
    {
      TLOC_LOG_GFX_WARN_FILENAME_ONLY() << "Entity " << *a_ent
        << " doesn't have a Mesh to use for BoundingBox.";
      return ErrorSuccess;
    }

    auto bb2d = a_ent->GetComponentIfExists<gfx_cs::BoundingBox2D>();
    auto bb3d = a_ent->GetComponentIfExists<gfx_cs::BoundingBox3D>();

    DoCalculateBoundingBox(*mesh, bt3d, bt2d, circ_bt2d, bb2d ? bb2d->GetIsCircular() : false);

    if (bb2d)
    { 
      if (bb2d->GetIsCircular())
      { *bb2d = gfx_cs::BoundingBox2D(circ_bt2d); }
      else
      { *bb2d = gfx_cs::BoundingBox2D(bt2d); }
    }
    else
    { *bb3d = gfx_cs::BoundingBox3D(bt3d); }

    return ErrorSuccess; 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    BoundingBoxSystem::
    ProcessEntity(entity_ptr, f64)
  { }

};};};

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(BoundingBoxSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(BoundingBoxSystem);