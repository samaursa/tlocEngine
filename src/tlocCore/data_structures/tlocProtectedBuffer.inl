#ifndef TLOC_PROTECTED_BUFFER_INL
#define TLOC_PROTECTED_BUFFER_INL

#ifndef TLOC_PROTECTED_BUFFER_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/data_structures/tlocProtectedBuffer.h>

namespace tloc { namespace core {

#define PROTECTED_BUFFER_TEMP typename T, tl_size T_Size
#define PROTECTED_BUFFER_PARAMS T, T_Size
#define PROTECTED_BUFFER_TYPE typename ProtectedBuffer<PROTECTED_BUFFER_PARAMS>


  //------------------------------------------------------------------------
  // Static initialization

  template <PROTECTED_BUFFER_TEMP>
  T ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::s_protectedArea
    [ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::overflow_type::size + 1];

  //------------------------------------------------------------------------
  // Methods

  template <PROTECTED_BUFFER_TEMP>
  ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::ProtectedBuffer()
  {
    DoInit(build_config_type());
  }

  template <PROTECTED_BUFFER_TEMP>
  ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::~ProtectedBuffer()
  {
    TLOC_ASSERT(DoIsBufferValid(build_config_type()), 
                "Buffer overflow detected!");
  }

  template <PROTECTED_BUFFER_TEMP>
  T* ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::operator *()
  {
    return m_buffer;
  }

  template <PROTECTED_BUFFER_TEMP>
  const T* ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::operator *() const
  {
    return m_buffer;
  }

  template <PROTECTED_BUFFER_TEMP>
  T* ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::Get()
  {
    return m_buffer;
  }

  template <PROTECTED_BUFFER_TEMP>
  const T* ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::Get() const
  {
    return m_buffer;
  }

  template <PROTECTED_BUFFER_TEMP>
  PROTECTED_BUFFER_TYPE::size_type 
    ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::GetSize() const
  {
    return buffer_size;
  }

  template <PROTECTED_BUFFER_TEMP>
  template <typename T_BuildConfig>
  void ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::DoInit(T_BuildConfig)
  {
    for (tl_int i = 0; i < overflow_type::size; ++i)
    {
      s_protectedArea[i] = (T) - (i + 1);
      m_buffer[buffer_size + i] = s_protectedArea[i];
    }
  }

  template <PROTECTED_BUFFER_TEMP>
  void ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::
    DoInit(configs::p_build_config::Release)
  {
  }

  template <PROTECTED_BUFFER_TEMP>
  template <typename T_BuildConfig>
  bool ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::
    DoIsBufferValid(T_BuildConfig)
  {
    for (tl_int i = 0; i < overflow_type::size; ++i)
    {
      if (m_buffer[buffer_size + i] != s_protectedArea[i]) 
      { return false; }
    }
    return true;
  }

  template <PROTECTED_BUFFER_TEMP>
  bool ProtectedBuffer<PROTECTED_BUFFER_PARAMS>::
    DoIsBufferValid(configs::p_build_config::Release)
  {
    return true;
  }

};};

#endif