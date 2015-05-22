//#ifndef _TLOC_CORE_CONTAINERS_SET_H_
//#define _TLOC_CORE_CONTAINERS_SET_H_
//
//#include <tlocCore/tlocCoreBase.h>
//
//#include <tlocCore/tlocAssert.h>
//#include <tlocCore/types/tlocTypes.h>
//#include <tlocCore/containers/tlocArray.h>
//
//namespace tloc { namespace core { namespace containers {
//
//  //////////////////////////////////////////////////////////////////////////
//  // Notes On Set
//  /*
//   * This is an ordered set, following the interface provided by the standard 
//   * but does not give the same complexity guarantees. We would like to avoid 
//   * using lists or list like structures (which are generally required by
//   * the binary-tree or red-black tree implementations of set)
//   */
//
//  template <typename T, typename T_Compare = less<T> >
//  class 
//  {
//  public:
//    typedef T                                           key_type;
//    typedef key_type                                    value_type;
//    typedef tl_size                                     size_type;
//    typedef tl_ptrdiff                                  difference_type;
//    typedef T_Compare                                   key_compare;
//    typedef T_Compare                                   value_compare;
//    typedef T&                                          reference;
//    typedef const T&                                    const_reference;
//    typedef T*                                          pointer;
//    typedef const T*                                    const_pointer;
//
//    typedef Array<T>                                    cont_type;
//    typedef cont_type::iterator                         iterator;
//    typedef cont_type::const_iterator                   const_iterator;
//    typedef cont_type::reverse_iterator                 reverse_iterator;
//    typedef cont_type::const_reverse_iterator           const_reverse_iterator;
//
//  public:
//    Stack();
//    explicit Stack(const T_Container& aCont);
//
//    //------------------------------------------------------------------------
//    // Capacity
//
//    size_type          size() const;
//    bool               empty() const;
//
//    //------------------------------------------------------------------------
//    // Element Access
//
//    reference          top();
//    const_reference    top() const;
//
//    //------------------------------------------------------------------------
//    // Modifiers
//
//    void               push(const value_type& aVal);
//    void               pop();
//
//	private:
//    //------------------------------------------------------------------------
//    // Variables
//
//    T_Container             m_container;
//	};
//
//};};};
//
//#endif