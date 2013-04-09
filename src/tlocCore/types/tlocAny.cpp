#include "tlocAny.h"
#include "tlocAny.inl"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>

namespace tloc { namespace core { namespace types {

  Any::Any()  : m_policy(p_any::GetPolicy<p_any::detail::Empty>())
              , m_object(nullptr)
  { }

  Any::Any( const char* a_other )
    : m_policy(p_any::GetPolicy<p_any::detail::Empty>())
    , m_object(nullptr)
  {
    Assign(a_other);
  }

  Any::Any( const this_type& a_other )
    : m_policy(p_any::GetPolicy<p_any::detail::Empty>())
    , m_object(nullptr)
  {
    Assign(a_other);
  }

  Any::~Any()
  {
    m_policy->Delete(&m_object);
  }

  void Any::Assign( const this_type& a_other )
  {
    Reset();
    m_policy = a_other.m_policy;
    m_policy->Clone(&a_other.m_object, &m_object);
  }

  Any::this_type&
    Any::Swap( this_type& a_other )
  {
    core::swap(m_policy, a_other.m_policy);
    core::swap(m_object, a_other.m_object);
    return *this;
  }

  bool Any::IsEmpty() const
  {
    return m_policy == p_any::GetPolicy<p_any::detail::Empty>();
  }

  void Any::Reset()
  {
    if (IsEmpty() == false)
    {
      m_policy->Delete(&m_object);
      m_policy = p_any::GetPolicy<p_any::detail::Empty>();
    }
  }

  bool Any::IsSameType( const this_type& a_other ) const
  {
    return m_policy == a_other.m_policy;
  }

};};};