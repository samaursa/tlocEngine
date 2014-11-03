#ifndef TLOC_ENTITY_SYSTEM_BASE_H
#define TLOC_ENTITY_SYSTEM_BASE_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/component_system/tlocEvent.h>
#include <tlocCore/component_system/tlocEntityEvent.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

namespace tloc { namespace core { namespace component_system {

  class EntitySystemBase
    : public EventListener
    , public core_bclass::NonCopyable_I
    , public core_bclass::DebugName
  {
  public:

    typedef EntitySystemBase                      this_type;

    typedef components::value_type                component_type;
    typedef Component::info_type                  component_info_type;

    typedef tl_size                               size_type;
    typedef core::error::Error                    error_type;

    typedef core_cs::EventManager                 event_manager;
    typedef core_cs::event_manager_vptr           event_manager_ptr;
    typedef core_cs::EventBase                    event_type;

    typedef core_cs::EntityManager                entity_manager;
    typedef core_cs::entity_manager_vptr          entity_manager_ptr;
    typedef core_cs::const_entity_manager_vptr    const_entity_manager_ptr;

    typedef core_cs::Entity                       entity_type;
    typedef core_cs::entity_vptr                  entity_ptr;
    typedef core_cs::const_entity_vptr            const_entity_ptr;
    typedef EventBase::event_type                 event_value_type;

    typedef core::Pair<entity_ptr, size_type>     entity_count_pair;
    typedef core_conts::Array<entity_count_pair>  entity_count_cont;

    typedef f64                                   time_type;

  public:
    struct Register
    {
    public:
      typedef Register                                this_type;
      typedef core_conts::Array<component_info_type>  component_info_cont;
      typedef component_info_cont::iterator           iterator;

    public:
      this_type&  Add(component_info_type a_info);

      template <typename T_Component>
      this_type&  Add();

    public:
      component_info_cont m_registeredComps;
    }; 
    typedef Register                              register_type;

  public:

    virtual       ~EntitySystemBase();

    error_type    Initialize();
    bool          IsInitialized() const;
    error_type    Shutdown();

    ///-------------------------------------------------------------------------
    /// @brief
    /// Process the active entities. The entities are not processed if
    /// CheckProcessing returns false.
    ///-------------------------------------------------------------------------
    void          ProcessActiveEntities(time_type a_deltaT = 0);

    virtual void  SortEntities() = 0;

    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumEntities, m_activeEntities.size());

  protected:

    EntitySystemBase(event_manager_ptr a_eventMgr,
                     entity_manager_ptr a_entityMgr,
                     register_type a_compsToRegister, 
                     BufferArg a_debugName);

    ///-------------------------------------------------------------------------
    /// @brief Called before DoInitializeEntity is called
    ///-------------------------------------------------------------------------
    virtual error_type Pre_Initialize() = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called by Initialize()
    ///-------------------------------------------------------------------------
    virtual error_type DoInitialize(const entity_count_cont& a_entities) = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called after DoInitializeEntity is called
    ///-------------------------------------------------------------------------
    virtual error_type Post_Initialize() = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called before DoInitializeEntity is called
    ///-------------------------------------------------------------------------
    virtual error_type Pre_Shutdown() = 0;


    ///-------------------------------------------------------------------------
    /// @brief Called by Initialize()
    ///-------------------------------------------------------------------------
    virtual error_type DoShutdown(const entity_count_cont& a_entities) = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called after DoInitializeEntity is called
    ///-------------------------------------------------------------------------
    virtual error_type Post_Shutdown() = 0;

    ///-------------------------------------------------------------------------
    /// @brief
    /// Called by ProcessActiveEntities() before deciding whether to
    /// process entities.
    ///
    /// @return true if we want to process entities
    ///-------------------------------------------------------------------------
    virtual bool CheckProcessing() = 0;


    ///-------------------------------------------------------------------------
    /// @brief Called before processing entities
    ///-------------------------------------------------------------------------
    virtual void Pre_ProcessActiveEntities(time_type a_deltaT) = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called by ProcessActiveEntities() for base classes
    ///-------------------------------------------------------------------------
    virtual void DoProcessActiveEntities(const entity_count_cont& a_entities,
                                         time_type a_deltaT) = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called after processing entities
    ///-------------------------------------------------------------------------
    virtual void Post_ProcessActiveEntities(time_type a_deltaT) = 0;

    virtual void OnComponentInsert(const EntityComponentEvent& a_event) = 0;
    virtual void OnComponentRemove(const EntityComponentEvent& a_event) = 0;

    virtual void OnComponentDisable(const EntityComponentEvent& a_event) = 0;
    virtual void OnComponentEnable(const EntityComponentEvent& a_event) = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called by EventManager (we are/should-be a registered listener).
    ///
    /// @param  a_event The event.
    ///
    /// @return true if the message was processed, false if it was ignored.
    ///-------------------------------------------------------------------------
    EventReturn OnEvent(const event_type& a_event);

    TLOC_DECL_AND_DEF_GETTER(entity_manager_vptr, DoGetEntityManager,
                             entity_manager_vptr(m_entityMgr));
    TLOC_DECL_AND_DEF_GETTER(event_manager_vptr, DoGetEventManager,
                             event_manager_vptr(m_eventMgr));
    TLOC_DECL_AND_DEF_GETTER_DIRECT(entity_count_cont, DoGetActiveEntities,
                                    m_activeEntities);

  private:
    register_type           m_compRegistry;
    entity_count_cont       m_activeEntities;

    event_manager_ptr       m_eventMgr;
    entity_manager_ptr      m_entityMgr;

    core_utils::Checkpoints m_flags;

  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_Component>
  EntitySystemBase::Register::this_type&
    EntitySystemBase::Register::
    Add()
  {
    return Add(component_info_type()
               .GroupIndex(T_Component::k_component_group)
               .Type(T_Component::k_component_type));
  }

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_VIRTUAL_PTR(EntitySystemBase, entity_system_base);
  TLOC_TYPEDEF_UNIQUE_PTR(EntitySystemBase, entity_system_base);

  namespace algos { namespace entity_system  {

    // ///////////////////////////////////////////////////////////////////////
    // initialize

    TLOC_DECL_ALGO_UNARY(Initialize_T, );
    TLOC_DEFINE_ALGO_UNARY(Initialize_T, )
    { extract()(a).Initialize(); return true; }

    typedef Initialize_T<core::use_reference>   Initialize;
    typedef Initialize_T<core::use_pointee>     Initialize_Deref;

    // ///////////////////////////////////////////////////////////////////////
    // shutdown

    TLOC_DECL_ALGO_UNARY(Shutdown_T, );
    TLOC_DEFINE_ALGO_UNARY(Shutdown_T, )
    { extract()(a).Shutdown(); return true; }

    typedef Shutdown_T<core::use_reference>     Shutdown;
    typedef Shutdown_T<core::use_pointee>       Shutdown_Deref;

    // ///////////////////////////////////////////////////////////////////////
    // process

    TLOC_DECL_ALGO_WITH_CTOR_UNARY(Process_T, EntitySystemBase::time_type, );
    TLOC_DEFINE_ALGO_WITH_CTOR_UNARY(Process_T, )
    { extract()(a).ProcessActiveEntities(m_value); return true; }

    typedef Process_T<use_reference>            Process;
    typedef Process_T<core::use_pointee>        Process_Deref;

  };};
  
};};};

// -----------------------------------------------------------------------
// extern template
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::core_cs::EntitySystemBase);

#endif