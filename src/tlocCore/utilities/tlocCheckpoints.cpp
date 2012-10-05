#include "tlocCheckpoints.h"
#include <tlocCore/containers/tlocContainers.inl>

namespace tloc { namespace core { namespace utils {

  Checkpoints::Checkpoints(tl_uint a_numberOfCheckpoints)
    : m_flags(a_numberOfCheckpoints)
  {
  }

  Checkpoints::value_type Checkpoints::operator [](tl_int a_index) const
  {
    return m_flags[a_index];
  }

  void Checkpoints::MarkAll()
  {
    SetAllTo(false);
  }

  void Checkpoints::UnmarkAll()
  {
    SetAllTo(true);
  }

  void Checkpoints::ToggleAll()
  {
    for (flags_type::iterator itr = m_flags.begin(), itrEnd = m_flags.end();
          itr != itrEnd; ++itr)
    {
      *itr = !(*itr);
    }
  }

  void Checkpoints::SetAllTo(value_type a_flag)
  {
    for (flags_type::iterator itr = m_flags.begin(), itrEnd = m_flags.end();
          itr != itrEnd; ++itr)
    {
      *itr = a_flag;
    }
  }

  void Checkpoints::Mark(size_type a_index)
  {
    m_flags[a_index] = true;
  }

  void Checkpoints::Unmark(size_type a_index)
  {
    m_flags[a_index] = true;
  }

  void Checkpoints::Toggle(size_type a_index)
  {
    m_flags[a_index] = !m_flags[a_index];
  }

};};};