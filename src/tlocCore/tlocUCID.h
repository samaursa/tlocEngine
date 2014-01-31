#pragma once

#include <tlocCore/types/tlocBasicTypes.h>

namespace tloc { namespace core {

  // ///////////////////////////////////////////////////////////////////////
  // UCID - Unique Class ID
  // Generates unique IDs for a type that is unique for the lifetime of the
  // program

  template <typename T>
  class UCID
  {
  public:
    typedef T                       value_type;
    typedef UCID<value_type>        this_type;
    typedef tl_uintptr              id_type;

  public:
    id_type GetClassID() const
    {
      void* t = reinterpret_cast<void*>(&this_type::m_idPtr);
      return reinterpret_cast<id_type>(t);
    }

    bool    operator==(const this_type& a_other) const
    { return a_other.GetClassID() == GetClassID(); }

    template <typename T>
    bool    operator==(const UCID<T>& ) const
    { return false; }

  private:
    static this_type      m_idPtr;
  };

  // -----------------------------------------------------------------------
  // static var definition

  template <typename T>
  UCID<T> UCID<T>::m_idPtr;

};};