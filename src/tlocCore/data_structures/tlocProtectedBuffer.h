#ifndef TLOC_PROTECTED_BUFFER_H
#define TLOC_PROTECTED_BUFFER_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/configs/tlocBuildConfig.h>

namespace tloc { namespace core { namespace data_structs {

  namespace priv
  {
    namespace p_procted_buffer
    {
      template <typename T_BuildConfig>
      struct Overflow
      {
        enum { size = 2 };
      };

      template <>
      struct Overflow<configs::p_build_config::Release>
      {
        enum { size = 0 };
      };
    }
  };

  template <typename T, tl_size T_Size>
  class ProtectedBuffer
  {
  public:
    typedef T                                           value_type;
    typedef tl_size                                     size_type;
    typedef typename
      configs::BuildConfig:: build_config_type        build_config_type;

    typedef priv::p_procted_buffer::Overflow<build_config_type>   overflow_type;

    enum { buffer_size = T_Size };

    ProtectedBuffer();
    ~ProtectedBuffer();

    T* operator*();
    const T* operator*() const;
    T* Get();
    const T* Get() const;

    size_type GetSize() const;

  private:

    template <typename T_BuildConfig>
    void DoInit(T_BuildConfig);

    void DoInit(configs::p_build_config::Release);

    template <typename T_BuildConfig>
    bool DoIsBufferValid(T_BuildConfig);
    bool DoIsBufferValid(configs::p_build_config::Release);

    enum { buffer_size_for_debugging = buffer_size + overflow_type::size};

    T         m_buffer[buffer_size_for_debugging];
    static T  s_protectedArea[overflow_type::size + 1];
  };

};};};

#endif