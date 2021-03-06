#ifndef TLOC_TEMPLATE_PARAMS_H
#define TLOC_TEMPLATE_PARAMS_H

#include <tlocCore/utilities/tlocTemplateUtils.h>

namespace tloc
{
  template <class T1  = TLOC_DUMMY_PARAM,
            class T2  = TLOC_DUMMY_PARAM,
            class T3  = TLOC_DUMMY_PARAM,
            class T4  = TLOC_DUMMY_PARAM,
            class T5  = TLOC_DUMMY_PARAM,
            class T6  = TLOC_DUMMY_PARAM,
            class T7  = TLOC_DUMMY_PARAM,
            class T8  = TLOC_DUMMY_PARAM,
            class T9  = TLOC_DUMMY_PARAM,
            class T10 = TLOC_DUMMY_PARAM,
            class T11 = TLOC_DUMMY_PARAM>
  struct ParamList;

  template <class T1>
  struct ParamList<T1>
  {
    enum { size = 1 };

    typedef T1 param_type_1;

    ParamList()
    { }

    ParamList(param_type_1 p1)
      : m_param1(p1)
    { }

    param_type_1 m_param1;
  };

  template <class T1, class T2>
  struct ParamList<T1, T2>
  {
    enum { size = 2 };

    typedef T1 param_type_1;
    typedef T2 param_type_2;

    ParamList()
    { }

    ParamList(param_type_1 p1, param_type_2 p2)
      : m_param1(p1)
      , m_param2(p2)
    { }

    param_type_1  m_param1;
    param_type_2  m_param2;
  };

  template <class T1, class T2, class T3>
  struct ParamList<T1, T2, T3>
  {
    enum { size = 3 };

    typedef T1 param_type_1;
    typedef T2 param_type_2;
    typedef T3 param_type_3;

    ParamList()
    { }

    ParamList(param_type_1 p1, param_type_2 p2, param_type_3 p3)
      : m_param1(p1)
      , m_param2(p2)
      , m_param3(p3)
    { }

    param_type_1  m_param1;
    param_type_2  m_param2;
    param_type_3  m_param3;
  };

  template <class T1, class T2, class T3, class T4>
  struct ParamList<T1, T2, T3, T4>
  {
    enum { size = 4 };

    typedef T1 param_type_1;
    typedef T2 param_type_2;
    typedef T3 param_type_3;
    typedef T4 param_type_4;

    ParamList()
    { }

    ParamList(param_type_1 p1, param_type_2 p2, param_type_3 p3,
              param_type_4 p4)
      : m_param1(p1)
      , m_param2(p2)
      , m_param3(p3)
      , m_param4(p4)
    { }

    param_type_1  m_param1;
    param_type_2  m_param2;
    param_type_3  m_param3;
    param_type_4  m_param4;
  };

  template <class T1, class T2, class T3, class T4, class T5>
  struct ParamList<T1, T2, T3, T4, T5>
  {
    enum { size = 5 };

    typedef T1 param_type_1;
    typedef T2 param_type_2;
    typedef T3 param_type_3;
    typedef T4 param_type_4;
    typedef T5 param_type_5;

    ParamList()
    { }

    ParamList(param_type_1 p1, param_type_2 p2, param_type_3 p3,
              param_type_4 p4, param_type_5 p5)
      : m_param1(p1)
      , m_param2(p2)
      , m_param3(p3)
      , m_param4(p4)
      , m_param5(p5)
    { }

    param_type_1  m_param1;
    param_type_2  m_param2;
    param_type_3  m_param3;
    param_type_4  m_param4;
    param_type_5  m_param5;
  };

  template <class T1, class T2, class T3, class T4, class T5, class T6>
  struct ParamList<T1, T2, T3, T4, T5, T6>
  {
    enum { size = 6 };

    typedef T1 param_type_1;
    typedef T2 param_type_2;
    typedef T3 param_type_3;
    typedef T4 param_type_4;
    typedef T5 param_type_5;
    typedef T6 param_type_6;

    ParamList()
    { }

    ParamList(param_type_1 p1, param_type_2 p2, param_type_3 p3,
              param_type_4 p4, param_type_5 p5, param_type_6 p6)
      : m_param1(p1)
      , m_param2(p2)
      , m_param3(p3)
      , m_param4(p4)
      , m_param5(p5)
      , m_param6(p6)
    { }

    param_type_1  m_param1;
    param_type_2  m_param2;
    param_type_3  m_param3;
    param_type_4  m_param4;
    param_type_5  m_param5;
    param_type_6  m_param6;
  };

  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7>
  struct ParamList<T1, T2, T3, T4, T5, T6, T7>
  {
    enum { size = 7 };

    typedef T1 param_type_1;
    typedef T2 param_type_2;
    typedef T3 param_type_3;
    typedef T4 param_type_4;
    typedef T5 param_type_5;
    typedef T6 param_type_6;
    typedef T7 param_type_7;

    ParamList()
    { }

    ParamList(param_type_1 p1, param_type_2 p2, param_type_3 p3,
              param_type_4 p4, param_type_5 p5, param_type_6 p6,
              param_type_7 p7)
      : m_param1(p1)
      , m_param2(p2)
      , m_param3(p3)
      , m_param4(p4)
      , m_param5(p5)
      , m_param6(p6)
      , m_param7(p7)
    { }

    param_type_1  m_param1;
    param_type_2  m_param2;
    param_type_3  m_param3;
    param_type_4  m_param4;
    param_type_5  m_param5;
    param_type_6  m_param6;
    param_type_7  m_param7;
  };

  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7, class T8>
  struct ParamList<T1, T2, T3, T4, T5, T6, T7, T8>
  {
    enum { size = 8 };

    typedef T1 param_type_1;
    typedef T2 param_type_2;
    typedef T3 param_type_3;
    typedef T4 param_type_4;
    typedef T5 param_type_5;
    typedef T6 param_type_6;
    typedef T7 param_type_7;
    typedef T8 param_type_8;

    ParamList()
    { }

    ParamList(param_type_1 p1, param_type_2 p2, param_type_3 p3,
              param_type_4 p4, param_type_5 p5, param_type_6 p6,
              param_type_7 p7, param_type_8 p8)
      : m_param1(p1)
      , m_param2(p2)
      , m_param3(p3)
      , m_param4(p4)
      , m_param5(p5)
      , m_param6(p6)
      , m_param7(p7)
      , m_param8(p8)
    { }

    param_type_1  m_param1;
    param_type_2  m_param2;
    param_type_3  m_param3;
    param_type_4  m_param4;
    param_type_5  m_param5;
    param_type_6  m_param6;
    param_type_7  m_param7;
    param_type_8  m_param8;
  };

  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7, class T8, class T9>
  struct ParamList<T1, T2, T3, T4, T5, T6, T7, T8, T9>
  {
    enum { size = 9 };

    typedef T1 param_type_1;
    typedef T2 param_type_2;
    typedef T3 param_type_3;
    typedef T4 param_type_4;
    typedef T5 param_type_5;
    typedef T6 param_type_6;
    typedef T7 param_type_7;
    typedef T8 param_type_8;
    typedef T9 param_type_9;

    ParamList()
    { }

    ParamList(param_type_1 p1, param_type_2 p2, param_type_3 p3,
              param_type_4 p4, param_type_5 p5, param_type_6 p6,
              param_type_7 p7, param_type_8 p8, param_type_9 p9)
      : m_param1(p1)
      , m_param2(p2)
      , m_param3(p3)
      , m_param4(p4)
      , m_param5(p5)
      , m_param6(p6)
      , m_param7(p7)
      , m_param8(p8)
      , m_param9(p9)
    { }

    param_type_1  m_param1;
    param_type_2  m_param2;
    param_type_3  m_param3;
    param_type_4  m_param4;
    param_type_5  m_param5;
    param_type_6  m_param6;
    param_type_7  m_param7;
    param_type_8  m_param8;
    param_type_9  m_param9;
  };

  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7, class T8, class T9, class T10>
  struct ParamList<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
  {
    enum { size = 10 };

    typedef T1  param_type_1;
    typedef T2  param_type_2;
    typedef T3  param_type_3;
    typedef T4  param_type_4;
    typedef T5  param_type_5;
    typedef T6  param_type_6;
    typedef T7  param_type_7;
    typedef T8  param_type_8;
    typedef T9  param_type_9;
    typedef T10 param_type_10;

    ParamList()
    { }

    ParamList(param_type_1 p1, param_type_2 p2, param_type_3 p3,
              param_type_4 p4, param_type_5 p5, param_type_6 p6,
              param_type_7 p7, param_type_8 p8, param_type_9 p9,
              param_type_10 p10)
      : m_param1(p1)
      , m_param2(p2)
      , m_param3(p3)
      , m_param4(p4)
      , m_param5(p5)
      , m_param6(p6)
      , m_param7(p7)
      , m_param8(p8)
      , m_param9(p9)
      , m_param10(p10)
    { }

    param_type_1    m_param1;
    param_type_2    m_param2;
    param_type_3    m_param3;
    param_type_4    m_param4;
    param_type_5    m_param5;
    param_type_6    m_param6;
    param_type_7    m_param7;
    param_type_8    m_param8;
    param_type_9    m_param9;
    param_type_10   m_param10;
  };

  // ///////////////////////////////////////////////////////////////////////
  // MakeParams

  template <typename T1>
  ParamList<T1>
    MakeParams(const T1& a_param1)
  {
      return ParamList<T1>
        (a_param1);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2>
  ParamList<T1, T2>
    MakeParams(const T1& a_param1, const T2& a_param2)
  {
      return ParamList<T1, T2>
        (a_param1, a_param2);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3>
  ParamList<T1, T2, T3>
    MakeParams(const T1& a_param1, const T2& a_param2, const T3& a_param3)
  {
      return ParamList<T1, T2, T3>
        (a_param1, a_param2, a_param3);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4>
  ParamList<T1, T2, T3, T4>
    MakeParams(const T1& a_param1, const T2& a_param2, const T3& a_param3,
    const T4& a_param4)
  {
      return ParamList<T1, T2, T3, T4>
        (a_param1, a_param2, a_param3, a_param4);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4, typename T5>
  ParamList<T1, T2, T3, T4, T5>
    MakeParams(const T1& a_param1, const T2& a_param2, const T3& a_param3,
    const T4& a_param4, const T5& a_param5)
  {
      return ParamList<T1, T2, T3, T4, T5>
        (a_param1, a_param2, a_param3, a_param4, a_param5);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6>
    ParamList<T1, T2, T3, T4, T5, T6>
    MakeParams(const T1& a_param1, const T2& a_param2, const T3& a_param3,
    const T4& a_param4, const T5& a_param5, const T6& a_param6)
  {
      return ParamList<T1, T2, T3, T4, T5, T6>
        (a_param1, a_param2, a_param3, a_param4, a_param5,
        a_param6);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7>
    ParamList<T1, T2, T3, T4, T5, T6, T7>
    MakeParams(const T1& a_param1, const T2& a_param2, const T3& a_param3,
    const T4& a_param4, const T5& a_param5, const T6& a_param6,
    const T7& a_param7)
  {
      return ParamList<T1, T2, T3, T4, T5, T6, T7>
        (a_param1, a_param2, a_param3, a_param4, a_param5,
        a_param6, a_param7);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8>
    ParamList<T1, T2, T3, T4, T5, T6, T7, T8>
    MakeParams(const T1& a_param1, const T2& a_param2, const T3& a_param3,
    const T4& a_param4, const T5& a_param5, const T6& a_param6,
    const T7& a_param7, const T8& a_param8)
  {
      return ParamList<T1, T2, T3, T4, T5, T6, T7, T8>
        (a_param1, a_param2, a_param3, a_param4, a_param5,
        a_param6, a_param7, a_param8);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9>
    ParamList<T1, T2, T3, T4, T5, T6, T7, T8, T9>
    MakeParams(const T1& a_param1, const T2& a_param2, const T3& a_param3,
    const T4& a_param4, const T5& a_param5, const T6& a_param6,
    const T7& a_param7, const T8& a_param8, const T9& a_param9)
  {
      return ParamList<T1, T2, T3, T4, T5, T6, T7, T8, T9>
        (a_param1, a_param2, a_param3, a_param4, a_param5,
        a_param6, a_param7, a_param8, a_param9);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10>
    ParamList<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
    MakeParams(const T1& a_param1, const T2& a_param2, const T3& a_param3,
    const T4& a_param4, const T5& a_param5, const T6& a_param6,
    const T7& a_param7, const T8& a_param8, const T9& a_param9,
    const T10& a_param10)
  {
      return ParamList<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
        (a_param1, a_param2, a_param3, a_param4, a_param5,
        a_param6, a_param7, a_param8, a_param9, a_param10);
  }

};

#endif