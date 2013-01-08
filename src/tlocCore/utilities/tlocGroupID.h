#ifndef TLOC_GROUP_ID_H
#define TLOC_GROUP_ID_H

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/utilities/tlocObjectCtorCounter.h>

namespace tloc { namespace core { namespace utils {

  ///-------------------------------------------------------------------------
  /// @brief Class used to track a unique ID within a class group
  ///
  /// @note IDs always start from 1
  ///-------------------------------------------------------------------------
  template <typename T>
  class GroupID : ObjectCtorCounter<T>
  {
  public:
    typedef GroupID<T>                          this_type;
    typedef ObjectCtorCounter<T>                base_type;
    typedef typename base_type::size_type       size_type;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(size_type, GetUniqueGroupID, m_groupId);

  protected:
    GroupID()
    {
      m_groupId = base_type::GetTotalInstantiations();
    }
    GroupID(const GroupID&)
    {
      m_groupId = base_type::GetTotalInstantiations();
    }

  private:
    size_type     m_groupId;
  };

};};};

#endif