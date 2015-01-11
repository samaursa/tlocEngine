#include "tlocEntity.h"

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocEntityManager.h>

namespace tloc { namespace core { namespace component_system {

  using algos::component::compare::ComponentType_Deref;

  // ///////////////////////////////////////////////////////////////////////
  // Entity

  Entity::
    Entity(entity_id a_id, ent_mgr_ptr a_entMgr)
    : base_type("No name assigned")
    , m_id(a_id)
    , m_index(size_type() - 1)
    , m_active(true)
    , m_entMgr(a_entMgr)
  {
    m_allComponents.resize(component_group::k_count);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::
    Entity(entity_id a_id, BufferArg a_debugName, ent_mgr_ptr a_entMgr)
    : base_type(a_debugName)
    , m_id(a_id)
    , m_index(size_type() - 1)
    , m_active(true)
    , m_entMgr(a_entMgr)
  {
    m_allComponents.resize(component_group::k_count);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Entity::
    operator==(const this_type& a_other) const
  {
    return m_id == a_other.m_id &&
           m_index == a_other.m_index &&
           m_active == a_other.m_active;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool 
    Entity::
    HasComponent(component_info_type a_info, size_type a_index) const
  {
    const auto compSize = size_components(a_info);

    return compSize > a_index;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::component_ptr_type
    Entity::
    GetComponent(component_info_type a_info, size_type a_index) const
  {
    auto itr    = begin_components(a_info);
    auto itrEnd = end_components(a_info);

    const auto numComponents = core::distance(itr, itrEnd);
    TLOC_UNUSED_RELEASE(numComponents);
    TLOC_ASSERT(a_index < core_utils::CastNumber<size_type>(numComponents), 
                "Component at index does not exist in this entity");

    core::advance(itr, a_index);
    return *itr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::const_component_iterator
    Entity::
    begin_components(component_group_type a_groupIndex) const
  {
    const component_list& cl = m_allComponents[a_groupIndex];
    return cl.begin();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::const_component_iterator
    Entity::
    end_components(component_group_type a_groupIndex) const
  {
    const component_list& cl = m_allComponents[a_groupIndex];
    return cl.end();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::const_component_iterator
    Entity::
    begin_components(component_info_type a_info) const
  {
    DoAssertGroupIndex(a_info);

    const component_list& cl = m_allComponents[a_info.m_groupIndex];

    return core::find_if_all(cl, ComponentType_Deref(a_info));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::const_component_iterator
    Entity::
    end_components(component_info_type a_info) const
  {
    DoAssertGroupIndex(a_info);

    const component_list& cl = m_allComponents[a_info.m_groupIndex];

    auto itr    = cl.begin();
    auto itrEnd = cl.end();

    const_component_iterator toRet = 
      core::find_if_end(itr, itrEnd, ComponentType_Deref(a_info));

    return toRet == itrEnd ? toRet : ++toRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::component_iterator
    Entity::
    begin_components(component_group_type a_groupIndex)
  {
    component_list& cl = m_allComponents[a_groupIndex];
    return cl.begin();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::component_iterator
    Entity::
    end_components(component_group_type a_groupIndex)
  {
    component_list& cl = m_allComponents[a_groupIndex];
    return cl.end();
  }


  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::component_iterator
    Entity::
    begin_components(component_info_type a_info)
  {
    DoAssertGroupIndex(a_info);

    component_list& cl = m_allComponents[a_info.m_groupIndex];

    return core::find_if_all(cl, ComponentType_Deref(a_info));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::component_iterator
    Entity::
    end_components(component_info_type a_info)
  {
    DoAssertGroupIndex(a_info);

    component_list& cl = m_allComponents[a_info.m_groupIndex];

    component_iterator toRet = 
      core::find_if_end(cl.begin(), cl.end(), ComponentType_Deref(a_info));

    return ++toRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::const_component_group_iterator
    Entity::
    begin_component_groups() const
  { return m_allComponents.begin(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::const_component_group_iterator
    Entity::
    end_component_groups() const
  { return m_allComponents.end(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::size_type
    Entity::
    size_components(component_group_type a_groupIndex) const
  { return m_allComponents[a_groupIndex].size(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::size_type
    Entity::
    size_components(component_info_type a_info) const
  { 
    const_component_iterator  itr    = begin_components(a_info);
    const_component_iterator  itrEnd = end_components(a_info);

    return distance(itr, itrEnd);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::component_group_iterator
    Entity::
    begin_component_groups()
  { return m_allComponents.begin(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Entity::component_group_iterator
    Entity::
    end_component_groups()
  { return m_allComponents.end(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Entity::
    DoInsertComponent(component_sptr a_component)
  {
    Component::info_type itype = a_component->GetInfo();
    DoAssertGroupIndex(itype);

    component_list& cl = m_allComponents[itype.m_groupIndex];
    cl.push_back(a_component);

    // keep similar components together
    using algos::component::comparison::component_type::LessThan_Deref;
    core::sort(cl.begin(), cl.end(), LessThan_Deref());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Entity::
    DoRemoveComponent(component_sptr a_component)
  {
    Component::info_type info = a_component->GetInfo();
    DoAssertGroupIndex(info);

    component_iterator itr    = begin_components(info);
    component_iterator itrEnd = end_components(info);

    TLOC_ASSERT(itr != itrEnd, "Requested component does not exist");

    component_list::iterator foundItr = core::find(itr, itrEnd, a_component);

    m_allComponents[a_component->GetInfo().m_groupIndex].erase(foundItr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Entity::
    Activate() const
  { 
    m_entMgr->ActivateEntity(const_entity_vptr(this));
    //m_active = true; // EntityManager sets this flag now
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Entity::
    Deactivate() const
  { 
    m_entMgr->DeactivateEntity(const_entity_vptr(this));
    //m_active = false; // EntityManager sets this flag now
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Entity::
    DoAssertGroupIndex(Component::info_type a_info) const
  {
    TLOC_UNUSED_RELEASE(a_info);
    TLOC_ASSERT(a_info.m_groupIndex < (component_type)m_allComponents.size(),
                "Component is from an unsupported group. See tlocComponentType.h" 
                " for valid groups.");
  }


};};};

using namespace tloc::core_cs;

#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Entity::component_list);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(entity_vptr);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(const_entity_vptr);

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(entity_uptr);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(const_entity_uptr);

TLOC_EXPLICITLY_INSTANTIATE_ARRAY_FIXED(Entity::component_list, component_group::k_count);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(tloc::core_cs::Entity);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::core_cs::Entity);