#ifndef _TLOC_INITIALIZE_AND_DESTROY_H_
#define _TLOC_INITIALIZE_AND_DESTROY_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/error/tlocError.h>

namespace tloc { namespace core { namespace base_classes {

  template <typename T_DerivedClass>
  class InitializeAndDestroy_TI
  {
  public:
    enum
    {
      k_initialized = 0,
      k_destroyed,
      k_count
    };

  public:
    typedef T_DerivedClass                            derived_type;
    typedef InitializeAndDestroy_TI<derived_type>     this_type;
    typedef core_err::Error                           error_type;

  public:
    error_type  Initialize();
    error_type  Destroy();

    bool        IsInitialized() const;
    bool        IsDestroyed() const;

  protected:
    InitializeAndDestroy_TI();
    ~InitializeAndDestroy_TI();

  private:
    core_utils::Checkpoints         m_flags;
  };

  // ///////////////////////////////////////////////////////////////////////
  // template definitions

  template <typename T_DerivedClass>
  InitializeAndDestroy_TI<T_DerivedClass>::
    InitializeAndDestroy_TI()
    : m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  InitializeAndDestroy_TI<T_DerivedClass>::
    ~InitializeAndDestroy_TI()
  {
    TLOC_ASSERT(IsDestroyed(),
      "Destroy() was not called OR Destroy() was unsuccessful");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  typename InitializeAndDestroy_TI<T_DerivedClass>::error_type
    InitializeAndDestroy_TI<T_DerivedClass>::
    Initialize()
  {
    TLOC_ASSERT(IsInitialized() == false,
                "This class has already been initialized once");

    error_type err = static_cast<derived_type*>(this)->DoInitialize();
    if (err == ErrorSuccess)
    { m_flags.Mark(k_initialized); }

    return err;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  typename InitializeAndDestroy_TI<T_DerivedClass>::error_type
    InitializeAndDestroy_TI<T_DerivedClass>::
    Destroy()
  {
    TLOC_ASSERT(IsDestroyed() == false,
                "This class has already been destroyed once");

    error_type err = static_cast<derived_type*>(this)->DoDestroy();
    if (err == ErrorSuccess)
    { m_flags.Mark(k_destroyed); }

    return err;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  bool
    InitializeAndDestroy_TI<T_DerivedClass>::
    IsInitialized() const
  { return m_flags.IsMarked(k_initialized); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  bool
    InitializeAndDestroy_TI<T_DerivedClass>::
    IsDestroyed() const
  { return m_flags.IsMarked(k_destroyed); }

};};};

// -----------------------------------------------------------------------
// helper macro

#define TLOC_USING_INITIALIZE_AND_DESTROY_METHODS()\
  using base_type::Initialize;\
  using base_type::Destroy;\
  using base_type::IsInitialized;\
  using base_type::IsDestroyed

#endif