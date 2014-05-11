#ifndef _TLOC_ARGS_H_
#define _TLOC_ARGS_H_

#include <tlocCore/utilities/tlocTemplateUtils.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc
{

  // base type used to distinguish an Args type from other types
  struct ArgsType { };

  // -----------------------------------------------------------------------
  // helper class to find out if a type is Args or not

  template <typename T>
  struct IsArgs
  {
    enum {k_value = Loki::Conversion<T, ArgsType>::exists };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Args
  
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
  struct Args;

  template <class T1>
  struct Args<T1>
    : public ArgsType
  {
    enum { size = 1 };

    typedef T1 arg_type_1;

    Args()
    { }

    Args(const arg_type_1& p1)
      : m_arg1(&p1)
    { }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_1, Arg1, *m_arg1);

  private:
    const arg_type_1* m_arg1;
  };

  template <class T1, class T2>
  struct Args<T1, T2>
    : public ArgsType
  {
    enum { size = 2 };

    typedef T1 arg_type_1;
    typedef T2 arg_type_2;

    Args()
    { }

    Args(const arg_type_1& p1, const arg_type_2& p2)
      : m_arg1(&p1)
      , m_arg2(&p2)
    { }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_1, Arg1, *m_arg1);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_2, Arg2, *m_arg2);

  private:
    const arg_type_1*  m_arg1;
    const arg_type_2*  m_arg2;
  };

  template <class T1, class T2, class T3>
  struct Args<T1, T2, T3>
    : public ArgsType
  {
    enum { size = 3 };

    typedef T1 arg_type_1;
    typedef T2 arg_type_2;
    typedef T3 arg_type_3;

    Args()
    { }

    Args(const arg_type_1& p1, const arg_type_2& p2, 
              const arg_type_3& p3)
      : m_arg1(&p1)
      , m_arg2(&p2)
      , m_arg3(&p3)
    { }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_1, Arg1, *m_arg1);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_2, Arg2, *m_arg2);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_3, Arg3, *m_arg3);

  private:
    const arg_type_1*  m_arg1;
    const arg_type_2*  m_arg2;
    const arg_type_3*  m_arg3;
  };

  template <class T1, class T2, class T3, class T4>
  struct Args<T1, T2, T3, T4>
    : public ArgsType
  {
    enum { size = 4 };

    typedef T1 arg_type_1;
    typedef T2 arg_type_2;
    typedef T3 arg_type_3;
    typedef T4 arg_type_4;

    Args()
    { }

    Args(const arg_type_1& p1, const arg_type_2& p2, 
              const arg_type_3& p3, const arg_type_4& p4)
      : m_arg1(&p1)
      , m_arg2(&p2)
      , m_arg3(&p3)
      , m_arg4(&p4)
    { }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_1, Arg1, *m_arg1);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_2, Arg2, *m_arg2);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_3, Arg3, *m_arg3);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_4, Arg4, *m_arg4);

  private:
    const arg_type_1*  m_arg1;
    const arg_type_2*  m_arg2;
    const arg_type_3*  m_arg3;
    const arg_type_4*  m_arg4;
  };

  template <class T1, class T2, class T3, class T4, class T5>
  struct Args<T1, T2, T3, T4, T5>
    : public ArgsType
  {
    enum { size = 5 };

    typedef T1 arg_type_1;
    typedef T2 arg_type_2;
    typedef T3 arg_type_3;
    typedef T4 arg_type_4;
    typedef T5 arg_type_5;

    Args()
    { }

    Args(const arg_type_1& p1, const arg_type_2& p2, 
              const arg_type_3& p3, const arg_type_4& p4, 
              const arg_type_5& p5)
      : m_arg1(&p1)
      , m_arg2(&p2)
      , m_arg3(&p3)
      , m_arg4(&p4)
      , m_arg5(&p5)
    { }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_1, Arg1, *m_arg1);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_2, Arg2, *m_arg2);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_3, Arg3, *m_arg3);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_4, Arg4, *m_arg4);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_5, Arg5, *m_arg5);

  private:
    const arg_type_1*  m_arg1;
    const arg_type_2*  m_arg2;
    const arg_type_3*  m_arg3;
    const arg_type_4*  m_arg4;
    const arg_type_5*  m_arg5;
  };

  template <class T1, class T2, class T3, class T4, class T5, class T6>
  struct Args<T1, T2, T3, T4, T5, T6>
    : public ArgsType
  {
    enum { size = 6 };

    typedef T1 arg_type_1;
    typedef T2 arg_type_2;
    typedef T3 arg_type_3;
    typedef T4 arg_type_4;
    typedef T5 arg_type_5;
    typedef T6 arg_type_6;

    Args()
    { }

    Args(const arg_type_1& p1, const arg_type_2& p2, 
              const arg_type_3& p3, const arg_type_4& p4, 
              const arg_type_5& p5, const arg_type_6& p6)
      : m_arg1(&p1)
      , m_arg2(&p2)
      , m_arg3(&p3)
      , m_arg4(&p4)
      , m_arg5(&p5)
      , m_arg6(&p6)
    { }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_1, Arg1, *m_arg1);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_2, Arg2, *m_arg2);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_3, Arg3, *m_arg3);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_4, Arg4, *m_arg4);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_5, Arg5, *m_arg5);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_6, Arg6, *m_arg6);

  private:
    const arg_type_1*  m_arg1;
    const arg_type_2*  m_arg2;
    const arg_type_3*  m_arg3;
    const arg_type_4*  m_arg4;
    const arg_type_5*  m_arg5;
    const arg_type_6*  m_arg6;
  };

  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7>
  struct Args<T1, T2, T3, T4, T5, T6, T7>
    : public ArgsType
  {
    enum { size = 7 };

    typedef T1 arg_type_1;
    typedef T2 arg_type_2;
    typedef T3 arg_type_3;
    typedef T4 arg_type_4;
    typedef T5 arg_type_5;
    typedef T6 arg_type_6;
    typedef T7 arg_type_7;

    Args()
    { }

    Args(const arg_type_1& p1, const arg_type_2& p2, 
              const arg_type_3& p3, const arg_type_4& p4, 
              const arg_type_5& p5, const arg_type_6& p6,
              const arg_type_7& p7)
      : m_arg1(&p1)
      , m_arg2(&p2)
      , m_arg3(&p3)
      , m_arg4(&p4)
      , m_arg5(&p5)
      , m_arg6(&p6)
      , m_arg7(&p7)
    { }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_1, Arg1, *m_arg1);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_2, Arg2, *m_arg2);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_3, Arg3, *m_arg3);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_4, Arg4, *m_arg4);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_5, Arg5, *m_arg5);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_6, Arg6, *m_arg6);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_7, Arg7, *m_arg7);

  private:
    const arg_type_1*  m_arg1;
    const arg_type_2*  m_arg2;
    const arg_type_3*  m_arg3;
    const arg_type_4*  m_arg4;
    const arg_type_5*  m_arg5;
    const arg_type_6*  m_arg6;
    const arg_type_7*  m_arg7;
  };

  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7, class T8>
  struct Args<T1, T2, T3, T4, T5, T6, T7, T8>
    : public ArgsType
  {
    enum { size = 8 };

    typedef T1 arg_type_1;
    typedef T2 arg_type_2;
    typedef T3 arg_type_3;
    typedef T4 arg_type_4;
    typedef T5 arg_type_5;
    typedef T6 arg_type_6;
    typedef T7 arg_type_7;
    typedef T8 arg_type_8;

    Args()
    { }

    Args(const arg_type_1& p1, const arg_type_2& p2, 
              const arg_type_3& p3, const arg_type_4& p4, 
              const arg_type_5& p5, const arg_type_6& p6,
              const arg_type_7& p7, const arg_type_8& p8)
      : m_arg1(&p1)
      , m_arg2(&p2)
      , m_arg3(&p3)
      , m_arg4(&p4)
      , m_arg5(&p5)
      , m_arg6(&p6)
      , m_arg7(&p7)
      , m_arg8(&p8)
    { }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_1, Arg1, *m_arg1);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_2, Arg2, *m_arg2);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_3, Arg3, *m_arg3);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_4, Arg4, *m_arg4);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_5, Arg5, *m_arg5);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_6, Arg6, *m_arg6);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_7, Arg7, *m_arg7);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_8, Arg8, *m_arg8);

  private:
    const arg_type_1*  m_arg1;
    const arg_type_2*  m_arg2;
    const arg_type_3*  m_arg3;
    const arg_type_4*  m_arg4;
    const arg_type_5*  m_arg5;
    const arg_type_6*  m_arg6;
    const arg_type_7*  m_arg7;
    const arg_type_8*  m_arg8;
  };

  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7, class T8, class T9>
  struct Args<T1, T2, T3, T4, T5, T6, T7, T8, T9>
    : public ArgsType
  {
    enum { size = 9 };

    typedef T1 arg_type_1;
    typedef T2 arg_type_2;
    typedef T3 arg_type_3;
    typedef T4 arg_type_4;
    typedef T5 arg_type_5;
    typedef T6 arg_type_6;
    typedef T7 arg_type_7;
    typedef T8 arg_type_8;
    typedef T9 arg_type_9;

    Args()
    { }

    Args(const arg_type_1& p1, const arg_type_2& p2, 
              const arg_type_3& p3, const arg_type_4& p4, 
              const arg_type_5& p5, const arg_type_6& p6,
              const arg_type_7& p7, const arg_type_8& p8, 
              const arg_type_9& p9)
      : m_arg1(&p1)
      , m_arg2(&p2)
      , m_arg3(&p3)
      , m_arg4(&p4)
      , m_arg5(&p5)
      , m_arg6(&p6)
      , m_arg7(&p7)
      , m_arg8(&p8)
      , m_arg9(&p9)
    { }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_1, Arg1, *m_arg1);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_2, Arg2, *m_arg2);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_3, Arg3, *m_arg3);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_4, Arg4, *m_arg4);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_5, Arg5, *m_arg5);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_6, Arg6, *m_arg6);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_7, Arg7, *m_arg7);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_8, Arg8, *m_arg8);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_9, Arg9, *m_arg9);

  private:
    const arg_type_1*  m_arg1;
    const arg_type_2*  m_arg2;
    const arg_type_3*  m_arg3;
    const arg_type_4*  m_arg4;
    const arg_type_5*  m_arg5;
    const arg_type_6*  m_arg6;
    const arg_type_7*  m_arg7;
    const arg_type_8*  m_arg8;
    const arg_type_9*  m_arg9;
  };

  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7, class T8, class T9, class T10>
  struct Args<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
    : public ArgsType
  {
    enum { size = 10 };

    typedef T1  arg_type_1;
    typedef T2  arg_type_2;
    typedef T3  arg_type_3;
    typedef T4  arg_type_4;
    typedef T5  arg_type_5;
    typedef T6  arg_type_6;
    typedef T7  arg_type_7;
    typedef T8  arg_type_8;
    typedef T9  arg_type_9;
    typedef T10 arg_type_10;

    Args()
    { }

    Args(const arg_type_1& p1, const arg_type_2& p2, 
              const arg_type_3& p3, const arg_type_4& p4, 
              const arg_type_5& p5, const arg_type_6& p6,
              const arg_type_7& p7, const arg_type_8& p8, 
              const arg_type_9& p9, const arg_type_10& p10)
      : m_arg1(&p1)
      , m_arg2(&p2)
      , m_arg3(&p3)
      , m_arg4(&p4)
      , m_arg5(&p5)
      , m_arg6(&p6)
      , m_arg7(&p7)
      , m_arg8(&p8)
      , m_arg9(&p9)
      , m_arg10(&p10)
    { }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_1, Arg1, *m_arg1);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_2, Arg2, *m_arg2);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_3, Arg3, *m_arg3);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_4, Arg4, *m_arg4);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_5, Arg5, *m_arg5);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_6, Arg6, *m_arg6);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_7, Arg7, *m_arg7);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_8, Arg8, *m_arg8);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_9, Arg9, *m_arg9);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(arg_type_10, Arg10, *m_arg10);

  private:
    const arg_type_1*    m_arg1;
    const arg_type_2*    m_arg2;
    const arg_type_3*    m_arg3;
    const arg_type_4*    m_arg4;
    const arg_type_5*    m_arg5;
    const arg_type_6*    m_arg6;
    const arg_type_7*    m_arg7;
    const arg_type_8*    m_arg8;
    const arg_type_9*    m_arg9;
    const arg_type_10*   m_arg10;
  };

  // ///////////////////////////////////////////////////////////////////////
  // MakeArgs

  template <typename T1>
  Args<T1>
    MakeArgs(const T1& a_arg1)
  { 
      return Args<T1> 
        (a_arg1);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2>
  Args<T1, T2>
    MakeArgs(const T1& a_arg1, const T2& a_arg2)
  { 
      return Args<T1, T2> 
        (a_arg1, a_arg2);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3>
  Args<T1, T2, T3>
    MakeArgs(const T1& a_arg1, const T2& a_arg2, const T3& a_arg3)
  { 
      return Args<T1, T2, T3> 
        (a_arg1, a_arg2, a_arg3);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4>
  Args<T1, T2, T3, T4>
    MakeArgs(const T1& a_arg1, const T2& a_arg2, const T3& a_arg3, 
               const T4& a_arg4)
  { 
      return Args<T1, T2, T3, T4> 
        (a_arg1, a_arg2, a_arg3, a_arg4);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4, typename T5>
  Args<T1, T2, T3, T4, T5>
    MakeArgs(const T1& a_arg1, const T2& a_arg2, const T3& a_arg3, 
               const T4& a_arg4, const T5& a_arg5)
  { 
      return Args<T1, T2, T3, T4, T5> 
        (a_arg1, a_arg2, a_arg3, a_arg4, a_arg5);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
            typename T6>
  Args<T1, T2, T3, T4, T5, T6>
    MakeArgs(const T1& a_arg1, const T2& a_arg2, const T3& a_arg3, 
               const T4& a_arg4, const T5& a_arg5, const T6& a_arg6)
  { 
      return Args<T1, T2, T3, T4, T5, T6> 
        (a_arg1, a_arg2, a_arg3, a_arg4, a_arg5,
         a_arg6);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
            typename T6, typename T7>
  Args<T1, T2, T3, T4, T5, T6, T7>
    MakeArgs(const T1& a_arg1, const T2& a_arg2, const T3& a_arg3, 
               const T4& a_arg4, const T5& a_arg5, const T6& a_arg6, 
               const T7& a_arg7)
  { 
      return Args<T1, T2, T3, T4, T5, T6, T7> 
        (a_arg1, a_arg2, a_arg3, a_arg4, a_arg5,
         a_arg6, a_arg7);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
            typename T6, typename T7, typename T8>
  Args<T1, T2, T3, T4, T5, T6, T7, T8>
    MakeArgs(const T1& a_arg1, const T2& a_arg2, const T3& a_arg3, 
               const T4& a_arg4, const T5& a_arg5, const T6& a_arg6, 
               const T7& a_arg7, const T8& a_arg8)
  { 
      return Args<T1, T2, T3, T4, T5, T6, T7, T8> 
        (a_arg1, a_arg2, a_arg3, a_arg4, a_arg5,
         a_arg6, a_arg7, a_arg8);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
            typename T6, typename T7, typename T8, typename T9>
  Args<T1, T2, T3, T4, T5, T6, T7, T8, T9>
    MakeArgs(const T1& a_arg1, const T2& a_arg2, const T3& a_arg3, 
               const T4& a_arg4, const T5& a_arg5, const T6& a_arg6, 
               const T7& a_arg7, const T8& a_arg8, const T9& a_arg9)
  { 
      return Args<T1, T2, T3, T4, T5, T6, T7, T8, T9> 
        (a_arg1, a_arg2, a_arg3, a_arg4, a_arg5,
         a_arg6, a_arg7, a_arg8, a_arg9);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
            typename T6, typename T7, typename T8, typename T9, typename T10>
  Args<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
    MakeArgs(const T1& a_arg1, const T2& a_arg2, const T3& a_arg3, 
               const T4& a_arg4, const T5& a_arg5, const T6& a_arg6, 
               const T7& a_arg7, const T8& a_arg8, const T9& a_arg9, 
               const T10& a_arg10)
  { 
      return Args<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> 
        (a_arg1, a_arg2, a_arg3, a_arg4, a_arg5,
         a_arg6, a_arg7, a_arg8, a_arg9, a_arg10);
  }

  // ///////////////////////////////////////////////////////////////////////
  // ctor helpers
  // 
  // NOTE: Don't use these helpers directly. Use the engine's smart pointers
  //       which includes VSO, VirtualPtr, SharedPtr and UniquePtr.

  template <typename T_Obj, 
            typename T>
  T_Obj*
    New(const Args<T>& a_args)
  { return new T_Obj(a_args.Arg1()); }

  template <typename T_Obj, 
            typename T1, typename T2>
  T_Obj*
    New(const Args<T1, T2>& a_args)
  { return new T_Obj(a_args.Arg1(), a_args.Arg2()); }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3>
  T_Obj*
    New(const Args<T1, T2, T3>& a_args)
  { 
    return new T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4>
  T_Obj*
    New(const Args<T1, T2, T3, T4>& a_args)
  { 
    return new T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                     a_args.Arg4());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4, typename T5>
  T_Obj*
    New(const Args<T1, T2, T3, T4, T5>& a_args)
  { 
    return new T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                     a_args.Arg4(), a_args.Arg5());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4, typename T5, typename T6>
  T_Obj*
    New(const Args<T1, T2, T3, T4, T5, T6>& a_args)
  { 
    return new T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                     a_args.Arg4(), a_args.Arg5(), a_args.Arg6());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4, typename T5, typename T6,
            typename T7>
  T_Obj*
    New(const Args<T1, T2, T3, T4, T5, T6, T7>& a_args)
  { 
    return new T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                     a_args.Arg4(), a_args.Arg5(), a_args.Arg6(),
                     a_args.Arg7());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4, typename T5, typename T6,
            typename T7, typename T8>
  T_Obj*
    New(const Args<T1, T2, T3, T4, T5, T6, T7, T8>& a_args)
  { 
    return new T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                     a_args.Arg4(), a_args.Arg5(), a_args.Arg6(),
                     a_args.Arg7(), a_args.Arg8());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9>
  T_Obj*
    New(const Args<T1, T2, T3, T4, T5, T6, T7, T8, T9>& a_args)
  { 
    return new T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                     a_args.Arg4(), a_args.Arg5(), a_args.Arg6(),
                     a_args.Arg7(), a_args.Arg8(), a_args.Arg9());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, 
            typename T10>
  T_Obj*
    New(const Args<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>& a_args)
  { 
    return new T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                     a_args.Arg4(), a_args.Arg5(), a_args.Arg6(),
                     a_args.Arg7(), a_args.Arg8(), a_args.Arg9(),
                     a_args.Arg10());
  }

  // ///////////////////////////////////////////////////////////////////////
  // MakeOnStack helper

  template <typename T_Obj, 
            typename T>
  T_Obj
    MakeOnStack(const Args<T>& a_args)
  { return T_Obj(a_args.Arg1()); }

  template <typename T_Obj, 
            typename T1, typename T2>
  T_Obj
    MakeOnStack(const Args<T1, T2>& a_args)
  { return T_Obj(a_args.Arg1(), a_args.Arg2()); }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3>
  T_Obj
    MakeOnStack(const Args<T1, T2, T3>& a_args)
  { 
    return T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4>
  T_Obj
    MakeOnStack(const Args<T1, T2, T3, T4>& a_args)
  { 
    return T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                 a_args.Arg4());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4, typename T5>
  T_Obj
    MakeOnStack(const Args<T1, T2, T3, T4, T5>& a_args)
  { 
    return T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                 a_args.Arg4(), a_args.Arg5());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4, typename T5, typename T6>
  T_Obj
    MakeOnStack(const Args<T1, T2, T3, T4, T5, T6>& a_args)
  { 
    return T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                 a_args.Arg4(), a_args.Arg5(), a_args.Arg6());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4, typename T5, typename T6,
            typename T7>
  T_Obj
    MakeOnStack(const Args<T1, T2, T3, T4, T5, T6, T7>& a_args)
  { 
    return T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                 a_args.Arg4(), a_args.Arg5(), a_args.Arg6(),
                 a_args.Arg7());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4, typename T5, typename T6,
            typename T7, typename T8>
  T_Obj
    MakeOnStack(const Args<T1, T2, T3, T4, T5, T6, T7, T8>& a_args)
  { 
    return T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                 a_args.Arg4(), a_args.Arg5(), a_args.Arg6(),
                 a_args.Arg7(), a_args.Arg8());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9>
  T_Obj
    MakeOnStack(const Args<T1, T2, T3, T4, T5, T6, T7, T8, T9>& a_args)
  { 
    return T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                 a_args.Arg4(), a_args.Arg5(), a_args.Arg6(),
                 a_args.Arg7(), a_args.Arg8(), a_args.Arg9());
  }

  template <typename T_Obj, 
            typename T1, typename T2, typename T3,
            typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, 
            typename T10>
  T_Obj
    MakeOnStack(const Args<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>& a_args)
  { 
    return T_Obj(a_args.Arg1(), a_args.Arg2(), a_args.Arg3(),
                 a_args.Arg4(), a_args.Arg5(), a_args.Arg6(),
                 a_args.Arg7(), a_args.Arg8(), a_args.Arg9(),
                 a_args.Arg10());
  }
};

#endif