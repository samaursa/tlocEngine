#ifndef TLOC_HASH_TABLE_H 
#define TLOC_HASH_TABLE_H 

#include "tlocBase.h"
#include "tlocTypeTraits.h"
#include "tlocAlgorithms.h"
#include "tlocIterator.h"

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in Array

#ifndef TLOC_DISABLE_ASSERT_HASH_TABLE
# define TLOC_ASSERT_HASH_TABLE(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_HASH_TABLE(_Expression, _Msg)
#endif

///-------------------------------------------------------------------------
/// @brief The hash_table is written after looking at EASTL hash_table and SGI
/// hash_table. The container will be optimized for games only and may not be 
/// appropriate for application use
///-------------------------------------------------------------------------
namespace tloc { namespace core {

  ///-------------------------------------------------------------------------
  /// @brief
  /// The standard creates a hash_node instead which is a simple linked
  /// list. We allow the user to choose the type of container they chose
  /// as long as it can accomodate this class as `T`.
  ///-------------------------------------------------------------------------
  template <typename T_Value, bool T_StoreHash = false>
  struct HashtableElement 
  {
    typedef tl_size                                 size_type;
    typedef ConditionalType<size_type, T_StoreHash> hashcode_type;

    T_Value       m_value;
    hashcode_type m_hashCode;
  };


  ///-------------------------------------------------------------------------
  /// @brief
  ///
  /// T_NodeType: The class for storing the nodes. The container must have the
  ///             members 
  ///-------------------------------------------------------------------------
  template <typename T_Key, typename T_Value, typename T_HashFunc, 
    typename T_ExtractKey, typename T_EqualKey, typename T_NodeType, 
    typename T_BucketType>
  class Hashtable 
  {

  };
    

};};