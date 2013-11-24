#ifndef _TLOC_PREFAB_BASE_H_
#define _TLOC_PREFAB_BASE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

// All major namespaces that prefab uses should go here

namespace tloc {

  // ///////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace prefab
  {
    namespace core      {};
    namespace graphics  {};
    namespace input     {};
    namespace math      {};
    namespace physics   {};
    namespace animation {};
  };

  // ///////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace prefab_core   = prefab::core;
  namespace prefab_gfx    = prefab::graphics;
  namespace prefab_input  = prefab::input;
  namespace prefab_phys   = prefab::physics;
  namespace prefab_anim   = prefab::animation;

  // ///////////////////////////////////////////////////////////////////////
  // Base for all prefab objects

  class Prefab_I
    : core_bclass::NonCopyable_I
  {
  public:
    typedef core_cs::EntityManager          entity_mgr_type;
    typedef core_cs::ComponentPoolManager   comp_pool_mgr_type;
    typedef core_cs::Entity                 entity_type;

  protected:
    Prefab_I(core_cs::EntityManager*  a_entMgr,
             core_cs::ComponentPoolManager* a_poolMgr)
             : m_entMgr(a_entMgr)
             , m_compPoolMgr(a_poolMgr)
    { }

  protected:
    entity_mgr_type*          m_entMgr;
    comp_pool_mgr_type*       m_compPoolMgr;
  };

};


#endif