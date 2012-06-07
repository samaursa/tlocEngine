#ifndef TLOC_TEMPLATE_DISPATCH_H
#define TLOC_TEMPLATE_DISPATCH_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/string/tlocString.h>

namespace tloc { namespace core {

  /// Use this class as a base class for callback classes that use the zero
  /// virtual overhead observer callback pattern. The inherited callback classes
  /// use virtual or pure virtual methods that define the actual callbacks for
  /// the Subject (in the observer pattern)
  template <typename T_CallbackMethods>
  class CallbackBase : public T_CallbackMethods
  {
  public:

    CallbackBase(const char* a_typename) : m_typename(a_typename) {}

    const char* GetType()
    {
      return m_typename;
    }

    template <typename T>
    const char* IsSame()
    {
      return StrCmp(m_typename, tl_type_to_string<T>().value()) == 0;
    }

    const char* m_typename;
  };

  /// Use this class as a base class for the actual callback class that can
  /// use any type. T_Container must support the function push_back()
  template <typename T_CallbackMethods, typename T_ContainerWithType>
  class CallbackGroupT : public CallbackBase<T_CallbackMethods>
  {
  public:

    typedef CallbackBase<T_CallbackMethods>       base_type;
    typedef T_ContainerWithType                   container_type;

    // value_type must be a pointer
    typedef typename container_type::value_type               pointer;
    typedef typename container_type::size_type                size_type;
    typedef typename Loki::TypeTraits<pointer>::PointeeType   value_type;
    typedef typename const value_type*                        const_pointer;

    CallbackGroupT() : CallbackBase<T_CallbackMethods>(tl_type_to_string<value_type>().value()) {}

    void Register(pointer a_observer)
    {
      m_observers.push_back(a_observer);
    }

    bool UnRegister(const_pointer a_observer)
    {
      container_type::iterator itr =
        find(m_observers.begin(), m_observers.end(), a_observer);

      if (itr != m_observers.end())
      {
        m_observers.erase(itr);
        return true;
      }

      return false;
    }

    size_type GetNumRegistered()
    {
      return m_observers.size();
    }

    // List of all the observers of the type value_type that this class is
    // responsible for
    container_type m_observers;
  };

  /// Base class for the dispatcher (the class responsible for firing the
  /// callbacks). T_CallbacksT is the type of your implemented callback
  /// class.
  template <typename T_Callbacks,
            template <typename T> class T_CallbackGroupT,
            template <typename T> class T_ContainerT>
  class DispatcherBase
  {
  public:

    // We don't know what the base type is yet

    typedef CallbackBase<T_Callbacks>                 callback_base_type;
    typedef T_ContainerT<callback_base_type*>         container_type;
    typedef typename container_type::value_type       value_type;

    typedef T_ContainerT<callback_base_type*>         container_type;
    typedef typename container_type::value_type       value_type;
    typedef typename container_type::size_type        size_type;

    ~DispatcherBase()
    {
      typedef container_type::iterator itr_type;

      for (itr_type itr = m_allObservers.begin(),
           itrEnd = m_allObservers.end();
           itr != itrEnd; ++itr)
      {
        delete *itr;
      }

      m_allObservers.clear();
    }

    template <typename T_Ref>
    void foo(T_Ref a)
    {
      TLOC_STATIC_ASSERT_IS_REFERENCE(T_Ref);
    }

    ///-------------------------------------------------------------------------
    /// Registers this object.
    ///
    /// @param [in] a_observer Pointer to the observer to register (cannot be
    ///                        NULL)
    ///-------------------------------------------------------------------------
    template <typename T_Ptr>
    void Register(T_Ptr a_observer)
    {
      TLOC_STATIC_ASSERT_IS_POINTER(T_Ptr);

      typedef typename Loki::TypeTraits<T_Ptr>::PointeeType value_type;
      typedef T_CallbackGroupT<value_type>         callback_type;
      typedef container_type::iterator             itr_type;

      const char* type_string = tl_type_to_string<value_type>().value();

      // Find the callback with the given type if it already exists
      for (itr_type itr = m_allObservers.begin(),
           itrEnd = m_allObservers.end();
           itr != itrEnd; ++itr)
      {
        if ( StrCmp( (*itr)->GetType(), type_string) == 0)
        {
          callback_type* currCallback = static_cast<callback_type*>(*itr);
          currCallback->Register(a_observer);
          return;
        }
      }

      // We could not find the callback with the given type. Create a new one.
      callback_type* newCallback = new callback_type();
      newCallback->Register(a_observer);
      m_allObservers.push_back(newCallback);
    }

    //template <typename T>
    //void Register(T a_observer)
    //{
    //  TLOC_STATIC_ASSERT(false, Function_does_not_take_non_pointers_types);
    //}

    ///-------------------------------------------------------------------------
    /// Un-register a previously registered observer.
    ///
    /// @param [in] a_observer Pointer to the observer to un-register (cannot
    ///                        be NULL)
    ///
    /// @return false is returned if a_observer is not previously registered.
    ///-------------------------------------------------------------------------
    template <typename T_Ptr>
    bool UnRegister(const T_Ptr a_observer)
    {
      TLOC_STATIC_ASSERT_IS_POINTER(T_Ptr);

      typedef typename Loki::TypeTraits<T_Ptr>::PointeeType value_type;
      typedef T_CallbackGroupT<value_type>         callback_type;
      typedef container_type::iterator             itr_type;

      const char* type_string = tl_type_to_string<value_type>().value();

      // Find the callback with the given type if it already exists
      for (itr_type itr = m_allObservers.begin(),
           itrEnd = m_allObservers.end();
           itr != itrEnd; ++itr)
      {
        if ( StrCmp( (*itr)->GetType(), type_string) == 0)
        {
          callback_type* currCallback = static_cast<callback_type*>(*itr);
          return currCallback->UnRegister(a_observer);
        }
      }

      return false;
    }

    size_type GetNumRegisteredGroups() const
    {
      return m_allObservers.size();
    }

    template <typename T>
    size_type GetNumRegisteredTypes() const
    {
      typedef T_CallbackGroupT<T>             callback_type;
      typedef container_type::const_iterator  itr_type;

      // Find the callback with the given type if it already exists
      for (itr_type itr = m_allObservers.begin(),
           itrEnd = m_allObservers.end();
           itr != itrEnd; ++itr)
      {
        if ( StrCmp( (*itr)->GetType(), tl_type_to_string<T>().value() ) == 0)
        {
          callback_type* currCallback = static_cast<callback_type*>(*itr);
          return currCallback->GetNumRegistered();
        }
      }

      return 0;
    }

  protected:

    container_type m_allObservers;
  };


};};

#endif
