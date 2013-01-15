#ifndef TLOC_CORE_MEMORY_BUFFER_ARG_H
#define TLOC_CORE_MEMORY_BUFFER_ARG_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocBasicTypes.h>

namespace tloc { namespace core { namespace memory {

  ///-------------------------------------------------------------------------
  /// @brief Meant to be used only as a function argument.
  ///-------------------------------------------------------------------------
  class BufferArg
  {
  public:
    typedef tl_size   size_type;
  public:

    ///-------------------------------------------------------------------------
    /// @brief
    /// Assumes a_buffer is NULL terminated. Call IsValid() to check if
    /// it is.
    ///-------------------------------------------------------------------------
    BufferArg(const char* a_buffer);
    BufferArg(const char* a_buffer, size_type a_end);

    template <typename T_String>
    BufferArg(T_String const& a_string);

    ///-------------------------------------------------------------------------
    /// @brief
    /// A buffer is valid if doesn't exceed a_maximumValidBufferSize iff
    /// m_size == 0. If m_size != 0, buffer is always valid.
    ///-------------------------------------------------------------------------
    bool IsValid() const;

    ///-------------------------------------------------------------------------
    /// @brief Same as IsValid() except with a user specified maximum size
    ///-------------------------------------------------------------------------
    bool IsValid(size_type a_maximumSize) const;

    const char operator[](tl_int a_index) const;

    const char* GetPtr() const;
    size_type   GetSize() const;

    static size_type   GetMaxAllowedBuffSize();

  private:
    const char* m_buffer;
    const char* m_end;
  };

};};};

namespace tloc
{
  typedef core::memory::BufferArg   BufferArg;
};

#endif