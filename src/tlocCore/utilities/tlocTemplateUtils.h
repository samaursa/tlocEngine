#ifndef TLOC_TEMPLATE_UTILS_H
#define TLOC_TEMPLATE_UTILS_H

///-------------------------------------------------------------------------
/// @brief Used for dummy template typename
///-------------------------------------------------------------------------
struct DummyStruct
{
};

///-------------------------------------------------------------------------
/// @brief  An empty struct that is guaranteed to be unique. This can be useful
/// in creating a false static assert
///-------------------------------------------------------------------------
struct UniqueDummyStruct
{
private:
  UniqueDummyStruct();
};

#define TLOC_DUMMY_TYPE typename T_Dummy
#define TLOC_DUMMY_PARAM DummyStruct

#endif