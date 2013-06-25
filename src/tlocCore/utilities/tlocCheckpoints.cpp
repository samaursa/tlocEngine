#include "tlocCheckpoints.h"
#include <tlocCore/containers/tlocContainers.inl.h>

namespace tloc { namespace core { namespace utils {

  Checkpoints::
    Checkpoints(tl_uint a_numberOfCheckpoints, bool a_initial)
    : m_flags(a_numberOfCheckpoints, a_initial)
  {
  }

  Checkpoints::value_type&
    Checkpoints::
    operator [](tl_int a_index)
  {
    return m_flags[a_index];
  }

  Checkpoints::value_type
    Checkpoints::
    operator [](tl_int a_index) const
  {
    return m_flags[a_index];
  }

  bool Checkpoints::
    IsMarked(tl_int a_index) const
  {
    return m_flags[a_index];
  }

  void Checkpoints::
    MarkAll()
  {
    SetAllTo(true);
  }

  void Checkpoints::
    UnmarkAll()
  {
    SetAllTo(false);
  }

  void Checkpoints::
    ToggleAll()
  {
    for (flags_type::iterator itr = m_flags.begin(), itrEnd = m_flags.end();
          itr != itrEnd; ++itr)
    {
      *itr = !(*itr);
    }
  }

  void Checkpoints::
    SetAllTo(value_type a_flag)
  {
    for (flags_type::iterator itr = m_flags.begin(), itrEnd = m_flags.end();
          itr != itrEnd; ++itr)
    {
      *itr = a_flag;
    }
  }

  void Checkpoints::
    Mark(size_type a_index)
  {
    m_flags[a_index] = true;
  }

  void Checkpoints::
    Unmark(size_type a_index)
  {
    m_flags[a_index] = false;
  }

  void Checkpoints::
    Toggle(size_type a_index)
  {
    m_flags[a_index] = !m_flags[a_index];
  }

  Checkpoints::value_type Checkpoints::
    ReturnAndMark(size_type a_index)
  {
    value_type toRet = IsMarked(a_index);
    Mark(a_index);
    return toRet;
  }

  Checkpoints::value_type Checkpoints::
    ReturnAndUnmark(size_type a_index)
  {
    value_type toRet = IsMarked(a_index);
    Unmark(a_index);
    return toRet;
  }

  Checkpoints::value_type Checkpoints::
    ReturnAndToggle(size_type a_index)
  {
    value_type toRet = IsMarked(a_index);
    Toggle(a_index);
    return toRet;
  }

};};};