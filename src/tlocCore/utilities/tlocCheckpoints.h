#ifndef TLOC_CHECKPOINTS_H
#define TLOC_CHECKPOINTS_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/containers/tlocContainers.h>

namespace tloc { namespace core { namespace utils {

  ///-------------------------------------------------------------------------
  /// @brief
  /// Checkpoints is used when a class needs to track various behaviors.
  /// For example, a class may need to check for initialization before
  /// running a certain function. Instead of creating several boolean
  /// variables, Checkpoints can be used and tied to enums.
  ///-------------------------------------------------------------------------
  class Checkpoints
  {
  public:
    typedef bool                                      value_type;
    typedef containers::tl_array<value_type>::type    flags_type;
    typedef tl_int                                    size_type;

    Checkpoints(tl_uint a_numberOfCheckpoints, bool a_initial = false);

    value_type& operator[](tl_int a_index);
    value_type  operator[](tl_int a_index) const;

    value_type  IsMarked(tl_int a_index) const;
    value_type  IsUnMarked(tl_int a_index) const;

    void       Mark(size_type a_index);
    void       Unmark(size_type a_index);
    void       Toggle(size_type a_index);

    void       MarkAll();
    void       UnmarkAll();
    void       ToggleAll();
    void       SetAllTo(value_type a_flag);

    value_type ReturnAndMark(size_type a_index);
    value_type ReturnAndUnmark(size_type a_index);
    value_type ReturnAndToggle(size_type a_index);

  private:
    flags_type  m_flags;
  };

};};};

#endif