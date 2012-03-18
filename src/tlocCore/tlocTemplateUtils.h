#ifndef TLOC_TEMPLATE_UTILS_H
#define TLOC_TEMPLATE_UTILS_H

///-------------------------------------------------------------------------
/// @brief Used for dummy template typename
///-------------------------------------------------------------------------
struct DummyStruct
{
};

#define TLOC_DUMMY_TYPE typename T_Dummy
#define TLOC_DUMMY_PARAM DummyStruct

///-------------------------------------------------------------------------
/// @brief This struct is used to diagnose template types.
///-------------------------------------------------------------------------
template <typename T>
struct TemplateDiagnose;

template <typename T>
struct DiagnoseTemplate;

#endif