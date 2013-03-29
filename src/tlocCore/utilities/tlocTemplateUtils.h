#ifndef TLOC_TEMPLATE_UTILS_H
#define TLOC_TEMPLATE_UTILS_H

///-------------------------------------------------------------------------
/// @brief Used for dummy template typename as well as a guaranteed unique
/// class. This can be useful in creating a false static assert i.e.
/// TLOC_STATIC_ASSERT((Loki::IsSameType<T, DummyStruct>::value), _message_);
///-------------------------------------------------------------------------
struct DummyStruct
{
private:
  DummyStruct() {}
};

#define TLOC_DUMMY_TYPE typename T_Dummy
#define TLOC_DUMMY_PARAM DummyStruct

#endif