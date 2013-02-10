#ifndef TLOC_QUEUE_H
#define TLOC_QUEUE_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/containers/tlocList.h>

//////////////////////////////////////////////////////////////////////////
// Notes On Queue
/*
 * Queue is a container adapter, built to limit a container to FIFO
 * (First in first out) control. The Queue implemented in tloc is heavily
 * influenced by the STL Queue, specifically with function names, and
 * general operation.
 *
 * Since queue is meant to be more of an adapter of a pre-existing container
 * it does not inherit from a container; Rather has a templatable one built
 * into itself, allowing for any container with the appropriate functionality
 * to be plugged into it.
 */

//------------------------------------------------------------------------
// fine grain control to enable/disable assertions in Queue

#ifndef TLOC_DISABLE_ASSERT_QUEUE
# define TLOC_ASSERT_QUEUE(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_QUEUE(_Expression, _Msg)
#endif

namespace tloc { namespace core { namespace containers {

  template <typename T, typename T_Container = List<T> >
  class Queue
  {
  public:
    //------------------------------------------------------------------------
    // typedefs (similar to queue)
    typedef T_Container                               container_type;
    typedef typename T_Container::value_type          value_type;
    typedef typename T_Container::reference           reference;
    typedef typename T_Container::const_reference     const_reference;
    typedef typename T_Container::size_type           size_type;

    //------------------------------------------------------------------------
    // Functions
    //
    // Notes: The following methods, unlike all other methods in the engine
    // are started with lower case and match std::queue. This is to facilitate
    // switching between the containers easily if need be

    //------------------------------------------------------------------------
    // Constructors

    Queue();
    explicit Queue(const T_Container& aCont);

    //------------------------------------------------------------------------
    // Capacity

    size_type          size() const;
    bool               empty() const;

    //------------------------------------------------------------------------
    // Element Access

    reference          front();
    const_reference    front() const;

    reference          back();
    const_reference    back() const;

    //------------------------------------------------------------------------
    // Modifiers

    void               push(const value_type& aVal);
    void               pop();

  private:
    //------------------------------------------------------------------------
    // Variables

    T_Container             m_container;
  };

};};};


#endif