#ifndef _TLOC_ENTITY_H_
#define _TLOC_ENTITY_H_

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/tlocAssert.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/base_classes/tlocDebugName.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/configs/tlocBuildConfig.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>

namespace tloc { namespace core { namespace component_system {

  class EntityManager;

  class Entity
    : public base_classes::DebugName
    , public core_bclass::NonCopyable_I
  {
  public:
    friend class EntityManager;
    typedef core_sptr::VirtualPtr<EntityManager>        ent_mgr_ptr;

    typedef Entity                                      this_type;
    typedef base_classes::DebugName_TI
      <core_cfg::BuildConfig::build_config_type>        base_type;

    typedef Component::info_type                        component_info_type;
    typedef Component::component_group_type             component_group_type;
    typedef Component::component_type                   component_type;

    typedef core::component_system::
                  component_sptr_array                  component_list;
    typedef component_list::value_type                  component_ptr_type;
    typedef component_list::iterator                    component_iterator;
    typedef component_list::const_iterator              const_component_iterator;

    typedef containers::tl_array_fixed
      <component_list, 
      component_group::k_count>::type                   component_group_list;
    typedef component_group_list::iterator              component_group_iterator;
    typedef component_group_list::const_iterator        const_component_group_iterator;

    typedef tl_size                                     entity_id;
    typedef tl_size                                     size_type;

  public:
    Entity(entity_id  a_id, ent_mgr_ptr a_entMgr);
    Entity(entity_id  a_id, BufferArg a_debugName, ent_mgr_ptr a_entMgr);

    bool                      operator==(const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

    bool                      HasComponent(component_info_type a_info, 
                                           size_type a_index = 0) const;
    component_ptr_type        GetComponent(component_info_type a_info, 
                                           size_type a_index = 0) const;
    component_ptr_type        GetComponentIfExists (component_info_type a_info, 
                                                    size_type a_index = 0) const;

    template <typename T_Component>
    bool                      HasComponent(size_type a_index = 0) const;
    template <typename T_Component>
    core_sptr::SharedPtr<T_Component>
                              GetComponent(size_type a_index = 0) const;
    template <typename T_Component>
    core_sptr::SharedPtr<T_Component>
                              GetComponentIfExists(size_type a_index = 0) const;

    const_component_iterator  begin_components(component_group_type a_groupIndex) const;
    const_component_iterator  end_components(component_group_type a_groupIndex) const;

    const_component_iterator  begin_components(component_info_type a_info) const;
    const_component_iterator  end_components(component_info_type a_info) const;

    template <typename T_Component>
    const_component_iterator  begin_components() const;
    template <typename T_Component>
    const_component_iterator  end_components() const;

    const_component_group_iterator begin_component_groups() const;
    const_component_group_iterator end_component_groups() const;

    size_type                 size_components(component_group_type  a_groupIndex) const;
    size_type                 size_components(component_info_type   a_info) const;
    template <typename T_Component>
    size_type                 size_components() const;

    void                      Activate() const;
    void                      Deactivate() const;

    using base_type::GetDebugName;
    using base_type::SetDebugName;

    TLOC_DECL_AND_DEF_GETTER(bool,  IsActive, m_active);
    TLOC_DECL_AND_DEF_GETTER(entity_id, GetID, m_id);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetIndex, m_index);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (component_group_list, GetComponentGroupList, m_allComponents);

  protected:

    component_iterator  begin_components(component_group_type a_groupIndex);
    component_iterator  end_components(component_group_type a_groupIndex);

    component_iterator  begin_components(component_info_type a_info);
    component_iterator  end_components(component_info_type a_info);

    template <typename T_Component>
    component_iterator  begin_components(component_info_type a_info);
    template <typename T_Component>
    component_iterator  end_components(component_info_type a_info);

    component_group_iterator begin_component_groups();
    component_group_iterator end_component_groups();

    void                DoInsertComponent(component_sptr a_component);
    void                DoRemoveComponent(component_sptr a_component);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT (component_group_list,  
                        DoGetComponentGroupList, m_allComponents);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(entity_id, DoSetID, m_id);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(size_type, DoSetIndex, m_index);

  private:
    void                DoAssertGroupIndex(Component::info_type a_info) const;

  private:

    entity_id             m_id;
    size_type             m_index;

    component_group_list  m_allComponents;

    mutable bool          m_active;
    ent_mgr_ptr           m_entMgr;
  };

  //------------------------------------------------------------------------
  // template definitions

  template <typename T_Component>
  core_sptr::SharedPtr<T_Component>
    Entity::GetComponent(size_type a_index) const
  {
    TLOC_ASSERT(HasComponent<T_Component>(), 
                "Component doesn't exist in this entity");

    return 
      core_sptr::static_pointer_cast<T_Component>
      (GetComponent(typename T_Component::Info()
        .GroupIndex(T_Component::k_component_group) 
        .Type(T_Component::k_component_type), a_index) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Component>
  core_sptr::SharedPtr<T_Component>
    Entity::GetComponentIfExists(size_type a_index) const
  {
    return 
      core_sptr::static_pointer_cast<T_Component>
      (GetComponentIfExists(typename T_Component::Info()
        .GroupIndex(T_Component::k_component_group) 
        .Type(T_Component::k_component_type), a_index) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Component>
  bool
    Entity::HasComponent(size_type a_index) const
  { 
    return HasComponent(typename T_Component::Info()
                        .GroupIndex(T_Component::k_component_group)
                        .Type(T_Component::k_component_type), a_index);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Component>
  Entity::const_component_iterator  
    Entity::
    begin_components() const
  {
    return begin_components(Component::info_type()
                            .GroupIndex(T_Component::k_component_group)
                            .Type(T_Component::k_component_type));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Component>
  Entity::const_component_iterator
    Entity::
    end_components() const
  {
    return end_components(Component::info_type()
                          .GroupIndex(T_Component::k_component_group)
                          .Type(T_Component::k_component_type));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Component>
  Entity::size_type          
    Entity::
    size_components() const
  {
    return size_components(Component::info_type()
                           .GroupIndex(T_Component::k_component_group)
                           .Type(T_Component::k_component_type));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Component>
  Entity::component_iterator  
    Entity:: 
    begin_components(component_info_type a_info)
  {
    return begin_components(Component::info_type()
                            .GroupIndex(T_Component::k_component_group)
                            .Type(T_Component::k_component_type));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Component>
  Entity::component_iterator  
    Entity::end_components(component_info_type a_info)
  {
    return ent_components(Component::info_type()
                          .GroupIndex(T_Component::k_component_group)
                          .Type(T_Component::k_component_type));
  }

  // -----------------------------------------------------------------------
  // typedef

  TLOC_TYPEDEF_ALL_SMART_PTRS(Entity, entity);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(Entity, entity);

  typedef containers::tl_array<entity_vptr>::type            entity_ptr_array;
  typedef containers::tl_array<const_entity_vptr>::type      const_entity_ptr_array;

  typedef containers::tl_array<entity_uptr>::type            entity_uptr_array;
  typedef containers::tl_array<const_entity_uptr>::type      const_entity_uptr_array;
};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ARRAY_FIXED(tloc::core_cs::Entity::component_list,
                                 tloc::core_cs::component_group::k_count);

namespace tloc { namespace core {

  namespace logging {

    template <typename T_Logger, typename T_BuildConfig>
    Log_T<T_Logger, T_BuildConfig>&
      operator << (Log_T<T_Logger, T_BuildConfig>& a_log,
                   const core_cs::Entity& a_entity)
    {
      a_log << "(" << a_entity.GetDebugName() << ")[" 
        << core_utils::MemoryAddress(&a_entity) << "]";

      return a_log;
    }

  };

};};

#endif