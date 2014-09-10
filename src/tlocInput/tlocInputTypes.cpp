#include "tlocInputTypes.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/string/tlocString.h>

namespace tloc { namespace input { namespace Component {

  // ///////////////////////////////////////////////////////////////////////
  // Point of view

  const char* Pov::s_enumStrings [] =
  {
    "centered",
    "north",
    "south",
    "east",
    "west",
    "north east",
    "south east",
    "north west",
    "south west"
  };

  const char* Pov::s_enumStringsShort [] =
  {
    "c",
    "n",
    "s",
    "e",
    "w",
    "ne",
    "se",
    "nw",
    "sw"
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const char*
    Pov::
    GetDirectionAsString(direction_type a_dir) const
  {
    TLOC_ASSERT( (core_utils::ArraySize(s_enumStrings) == k_count),
      "s_enumStrings size should match number of enums directly");
    switch(a_dir)
    {
    case k_centered:
      return s_enumStrings[core_utils::EnumToIndex_T<k_centered, true>::result];
    case k_north:
    case k_south:
    case k_east:
    case k_west:
      if (a_dir & k_north)
      {
        if (a_dir & k_east)
        { return "north east"; }
        else if (a_dir & k_west)
        { return "north west"; }
        else
        { return "north"; }
      }
      else if (a_dir & k_south)
      {
        if (a_dir & k_east)
        { return "south east"; }
        else if (a_dir & k_west)
        { return "south west"; }
        else
        { return "south"; }
      }
      else if (a_dir & k_east)
      {
        if (a_dir & k_north)
        { return "north east"; }
        else if (a_dir & k_south)
        { return "south east"; }
        else
        { return "east"; }
      }
      else if (a_dir & k_west)
      {
        if (a_dir & k_north)
        { return "north west"; }
        else if (a_dir & k_south)
        { return "south west"; }
        else
        { return "west"; }
      }
      else
      { TLOC_ASSERT_FALSE("Invalid case statement - see cases above"); }
    case k_north_east:
      return s_enumStrings[core_utils::EnumToIndex_T<k_north_east, true>::result];
    case k_south_east:
      return s_enumStrings[core_utils::EnumToIndex_T<k_south_east, true>::result];
    case k_north_west:
      return s_enumStrings[core_utils::EnumToIndex_T<k_north_west, true>::result];
    case k_south_west:
      return s_enumStrings[core_utils::EnumToIndex_T<k_south_west, true>::result];
    default:
      TLOC_ASSERT_FALSE("Invalid direction is stored");
      return s_enumStrings[core_utils::EnumToIndex_T<k_centered, true>::result];
    };
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const char*
    Pov::
    GetDirectionAsShortString(direction_type a_dir) const
  {
    TLOC_ASSERT( (core_utils::ArraySize(s_enumStrings) == k_count),
      "s_enumStrings size should match number of enums directly");

    switch(a_dir)
    {
    case k_centered:
      return s_enumStringsShort[core_utils::EnumToIndex_T<k_centered, true>::result];
    case k_north:
    case k_south:
    case k_east:
    case k_west:
      if (a_dir & k_north)
      {
        if (a_dir & k_east)
        { return "ne"; }
        else if (a_dir & k_west)
        { return "nw"; }
        else
        { return "n"; }
      }
      else if (a_dir & k_south)
      {
        if (a_dir & k_east)
        { return "se"; }
        else if (a_dir & k_west)
        { return "sw"; }
        else
        { return "s"; }
      }
      else if (a_dir & k_east)
      {
        if (a_dir & k_north)
        { return "ne"; }
        else if (a_dir & k_south)
        { return "se"; }
        else
        { return "e"; }
      }
      else if (a_dir & k_west)
      {
        if (a_dir & k_north)
        { return "nw"; }
        else if (a_dir & k_south)
        { return "sw"; }
        else
        { return "w"; }
      }
      else
      { TLOC_ASSERT_FALSE("Invalid case statement - see cases above"); }
    case k_north_east:
      return s_enumStringsShort[core_utils::EnumToIndex_T<k_north_east, true>::result];
    case k_south_east:
      return s_enumStringsShort[core_utils::EnumToIndex_T<k_south_east, true>::result];
    case k_north_west:
      return s_enumStringsShort[core_utils::EnumToIndex_T<k_north_west, true>::result];
    case k_south_west:
      return s_enumStringsShort[core_utils::EnumToIndex_T<k_south_west, true>::result];
    default:
      TLOC_ASSERT_FALSE("Invalid direction is stored");
      return s_enumStringsShort[core_utils::EnumToIndex_T<k_centered, true>::result];
    };
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Pov::
    IsDirection(direction_type a_dir) const
  { return (m_direction & a_dir) != 0; }

};};};