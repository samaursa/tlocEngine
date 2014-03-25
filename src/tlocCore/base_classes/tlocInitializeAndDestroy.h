#ifndef _TLOC_INITIALIZE_AND_DESTROY_H_
#define _TLOC_INITIALIZE_AND_DESTROY_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/types/tlocTypeTraits.h>

namespace tloc { namespace core { namespace base_classes {

  namespace p_initialize_and_destroy
  {
    class NoParams    { };
    class OneParam    { };
    class TwoParams   { };
    class ThreeParams { };
  };

  template <typename T_DerivedClass>
  class InitializeAndDestroyBase_TI
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
    typedef InitializeAndDestroyBase_TI<derived_type> this_type;
    typedef core_err::Error                           error_type;

  public:
    error_type  Destroy();

    void        AssertIsInitialized() const;
    void        AssertIsDestroyed() const;

    void        AssertIsNotInitialized() const;
    void        AssertIsNotDestroyed() const;

    bool        IsInitialized() const;
    bool        IsDestroyed() const;

  protected:
    InitializeAndDestroyBase_TI();
    ~InitializeAndDestroyBase_TI();

  protected:
    core_utils::Checkpoints         m_flags;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_DerivedClass>
  InitializeAndDestroyBase_TI<T_DerivedClass>::
    InitializeAndDestroyBase_TI()
    : m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  InitializeAndDestroyBase_TI<T_DerivedClass>::
    ~InitializeAndDestroyBase_TI()
  {
    if (IsDestroyed() == false)
    { Destroy(); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  typename InitializeAndDestroyBase_TI<T_DerivedClass>::error_type
    InitializeAndDestroyBase_TI<T_DerivedClass>::
    Destroy()
  {
    AssertIsInitialized();
    AssertIsNotDestroyed();

    error_type err = static_cast<derived_type*>(this)->DoDestroy();
    if (err == ErrorSuccess)
    { m_flags.Mark(k_destroyed); }

    return err;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  void
    InitializeAndDestroyBase_TI<T_DerivedClass>::
    AssertIsInitialized() const
  { TLOC_ASSERT(this->IsInitialized(), "Object not initialized"); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  void
    InitializeAndDestroyBase_TI<T_DerivedClass>::
    AssertIsDestroyed() const
  { TLOC_ASSERT(this->IsDestroyed(), "Object not destroyed"); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  void
    InitializeAndDestroyBase_TI<T_DerivedClass>::
    AssertIsNotInitialized() const
  { TLOC_ASSERT(this->IsInitialized() == false, "Object is already initialized"); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  void
    InitializeAndDestroyBase_TI<T_DerivedClass>::
    AssertIsNotDestroyed() const
  { TLOC_ASSERT(this->IsDestroyed() == false, "Object is already destroyed"); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  bool
    InitializeAndDestroyBase_TI<T_DerivedClass>::
    IsInitialized() const
  { return m_flags.IsMarked(k_initialized); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DerivedClass>
  bool
    InitializeAndDestroyBase_TI<T_DerivedClass>::
    IsDestroyed() const
  { return m_flags.IsMarked(k_destroyed); }

  // ///////////////////////////////////////////////////////////////////////
  // InitializeAndDestroy_TI

  template <typename T_DerivedClass,
            typename T_NumParams = p_initialize_and_destroy::NoParams>
  class InitializeAndDestroy_TI;

  // ///////////////////////////////////////////////////////////////////////
  // InitializeAndDestroy_TI<NoParams>

  template <typename T_DerivedClass>
  class InitializeAndDestroy_TI<T_DerivedClass,
                                p_initialize_and_destroy::NoParams>
    : public InitializeAndDestroyBase_TI<T_DerivedClass>
  {
  public:
    typedef typename InitializeAndDestroyBase_TI<T_DerivedClass>  base_type;
    typedef base_type::error_type                                 error_type;

    error_type  Initialize();

    using base_type::Destroy;
    using base_type::AssertIsInitialized;
    using base_type::AssertIsDestroyed;
    using base_type::IsInitialized;
    using base_type::IsDestroyed;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_DerivedClass>
  typename InitializeAndDestroy_TI<T_DerivedClass,
                                p_initialize_and_destroy::NoParams>::error_type
    InitializeAndDestroy_TI<T_DerivedClass,
                            p_initialize_and_destroy::NoParams>::
    Initialize()
  {
    AssertIsNotInitialized();

    error_type err = static_cast<derived_type*>(this)->DoInitialize();
    if (err == ErrorSuccess)
    { m_flags.Mark(k_initialized); }

    return err;
  }

  // ///////////////////////////////////////////////////////////////////////
  // InitializeAndDestroy_TI<NoParams>

  template <typename T_DerivedClass>
  class InitializeAndDestroy_TI<T_DerivedClass,
                                p_initialize_and_destroy::OneParam>
    : public InitializeAndDestroyBase_TI<T_DerivedClass>
  {
  public:
    typedef InitializeAndDestroyBase_TI<T_DerivedClass>     base_type;
    typedef base_type::error_type                           error_type;

    template <typename T>
    error_type  Initialize( const T& a_p1 );

    using base_type::Destroy;
    using base_type::AssertIsInitialized;
    using base_type::AssertIsDestroyed;
    using base_type::IsInitialized;
    using base_type::IsDestroyed;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_DerivedClass>
  template <typename T>
  typename InitializeAndDestroy_TI<T_DerivedClass,
                                p_initialize_and_destroy::OneParam>::error_type
    InitializeAndDestroy_TI<T_DerivedClass,
                            p_initialize_and_destroy::OneParam>::
    Initialize(const T& a_p1)
  {
    AssertIsNotInitialized();

    error_type err = static_cast<derived_type*>(this)->DoInitialize(a_p1);
    if (err == ErrorSuccess)
    { m_flags.Mark(k_initialized); }

    return err;
  }

  // ///////////////////////////////////////////////////////////////////////
  // InitializeAndDestroy_TI<NoParams>

  template <typename T_DerivedClass>
  class InitializeAndDestroy_TI<T_DerivedClass,
                                p_initialize_and_destroy::TwoParams>
    : public InitializeAndDestroyBase_TI<T_DerivedClass>
  {
  public:
    typedef InitializeAndDestroyBase_TI<T_DerivedClass>     base_type;
    typedef base_type::error_type                           error_type;

    template <typename T, typename U>
    error_type  Initialize( const T& a_p1, const U& a_p2 );

    using base_type::Destroy;
    using base_type::AssertIsInitialized;
    using base_type::AssertIsDestroyed;
    using base_type::IsInitialized;
    using base_type::IsDestroyed;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_DerivedClass>
  template <typename T, typename U>
  typename InitializeAndDestroy_TI<T_DerivedClass,
                                p_initialize_and_destroy::TwoParams>::error_type
    InitializeAndDestroy_TI<T_DerivedClass,
                            p_initialize_and_destroy::TwoParams>::
    Initialize(const T& a_p1, const U& a_p2)
  {
    AssertIsNotInitialized();

    error_type err = static_cast<derived_type*>(this)->DoInitialize(a_p1, a_p2);
    if (err == ErrorSuccess)
    { m_flags.Mark(k_initialized); }

    return err;
  }

  // ///////////////////////////////////////////////////////////////////////
  // InitializeAndDestroy_TI<NoParams>

  template <typename T_DerivedClass>
  class InitializeAndDestroy_TI<T_DerivedClass,
                                p_initialize_and_destroy::ThreeParams>
    : public InitializeAndDestroyBase_TI<T_DerivedClass>
  {
  public:
    typedef InitializeAndDestroyBase_TI<T_DerivedClass>     base_type;
    typedef base_type::error_type                           error_type;

    template <typename T, typename U, typename V>
    error_type  Initialize( const T& a_p1, const U& a_p2, const V& a_p3 );

    using base_type::Destroy;
    using base_type::AssertIsInitialized;
    using base_type::AssertIsDestroyed;
    using base_type::IsInitialized;
    using base_type::IsDestroyed;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_DerivedClass>
  template <typename T, typename U, typename V>
  typename InitializeAndDestroy_TI<T_DerivedClass,
                                p_initialize_and_destroy::ThreeParams>::error_type
    InitializeAndDestroy_TI<T_DerivedClass,
                            p_initialize_and_destroy::ThreeParams>::
    Initialize(const T& a_p1, const U& a_p2, const V& a_p3)
  {
    AssertIsNotInitialized();

    error_type err = static_cast<derived_type*>( this )->
      DoInitialize( a_p1, a_p2, a_p3 );

    if (err == ErrorSuccess)
    { m_flags.Mark(k_initialized); }

    return err;
  }

};};};

// -----------------------------------------------------------------------
// helper macro

#define TLOC_DECLARE_FRIEND_INITIALIZE_AND_DESTROY(_type_)\
  friend class tloc::core::base_classes::InitializeAndDestroyBase_TI<_type_>;\
  friend class tloc::core::base_classes::InitializeAndDestroy_TI<_type_>

#define TLOC_DECLARE_FRIEND_INITIALIZE_AND_DESTROY_ONE_PARAM(_type_)\
  friend class tloc::core::base_classes::InitializeAndDestroyBase_TI<_type_>;\
  friend class tloc::core::base_classes::InitializeAndDestroy_TI<_type_, tloc::core::base_classes::p_initialize_and_destroy::OneParam>

#define TLOC_DECLARE_FRIEND_INITIALIZE_AND_DESTROY_TWO_PARAMS(_type_)\
  friend class tloc::core::base_classes::InitializeAndDestroyBase_TI<_type_>;\
  friend class tloc::core::base_classes::InitializeAndDestroy_TI<_type_, tloc::core::base_classes::p_initialize_and_destroy::TwoParams>

#define TLOC_DECLARE_FRIEND_INITIALIZE_AND_DESTROY_THREE_PARAMS(_type_)\
  friend class tloc::core::base_classes::InitializeAndDestroyBase_TI<_type_>;\
  friend class tloc::core::base_classes::InitializeAndDestroy_TI<_type_, tloc::core::base_classes::p_initialize_and_destroy::ThreeParams>


#define TLOC_USING_INITIALIZE_AND_DESTROY_METHODS()\
  using base_type::AssertIsInitialized;\
  using base_type::AssertIsDestroyed;\
  using base_type::Initialize;\
  using base_type::Destroy;\
  using base_type::IsInitialized;\
  using base_type::IsDestroyed

#endif