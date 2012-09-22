#include "tlocTouchSurfaceDevice.h"

namespace tloc { namespace input { namespace priv {

  //////////////////////////////////////////////////////////////////////////
  // TouchSurfaceDeviceBase

  TouchSurfaceDeviceBase::TouchSurfaceDeviceBase()
  {
  }

  const TouchSurfaceDeviceBase::container_type&
    TouchSurfaceDeviceBase::GetCurrentTouches() const
  {
    return m_currentTouches;
  }

  const TouchSurfaceDeviceBase::touch_surface_event_type*
    TouchSurfaceDeviceBase::GetTouch(touch_handle_type a_touchHandle) const
  {
    const container_type::const_iterator touchItr = DoFindTouch(a_touchHandle);
    const container_type::const_iterator touchItrEnd = m_currentTouches.end();

    if (touchItr != touchItrEnd)
    {
      return &(*touchItr);
    }
    else
    {
      return NULL;
    }
  }

  TouchSurfaceDeviceBase::container_type&
    TouchSurfaceDeviceBase::DoGetCurrentTouches()
  {
    return m_currentTouches;
  }

  TouchSurfaceDeviceBase::container_type::const_iterator
    TouchSurfaceDeviceBase::DoFindTouch(touch_handle_type a_touchHandle) const
  {
    container_type::const_iterator itr = m_currentTouches.begin();
    const container_type::const_iterator itrEnd = m_currentTouches.end();

    while (itr != itrEnd)
    {
      if ((*itr).m_touchHandle == a_touchHandle)
      {
        break;
      }
    }
    return itr;
  }

  TouchSurfaceDeviceBase::container_type::iterator
    TouchSurfaceDeviceBase::DoFindTouch(touch_handle_type a_touchHandle)
  {
    container_type::iterator itr = m_currentTouches.begin();
    const container_type::const_iterator itrEnd = m_currentTouches.end();

    while (itr != itrEnd)
    {
      if ((*itr).m_touchHandle == a_touchHandle)
      {
        break;
      }
      ++itr;
    }
    return itr;
  }

  void TouchSurfaceDeviceBase::
    DoUpdateTouch(touch_surface_event_type& a_touchToUpdate,
                  const touch_surface_event_type& a_update)
  {
    DoUpdateTouch(a_touchToUpdate,
                  a_update.m_X.m_abs().Get(),
                  a_update.m_Y.m_abs().Get());
  }

  void TouchSurfaceDeviceBase::
    DoUpdateTouch(touch_surface_event_type& a_touchToUpdate,
                  tl_float a_x, tl_float a_y)
  {
    a_touchToUpdate.m_X.m_rel() += a_x - a_touchToUpdate.m_X.m_abs();
    a_touchToUpdate.m_Y.m_rel() += a_y - a_touchToUpdate.m_Y.m_abs();

    a_touchToUpdate.m_X.m_abs() = a_x;
    a_touchToUpdate.m_Y.m_abs() = a_y;
  }

  void TouchSurfaceDeviceBase::
    DoPushBackTouch(const touch_surface_event_type& a_event)
  {
    // TODO: add assertion macro if we're near full
    m_currentTouches.push_back(a_event);
  }

  void TouchSurfaceDeviceBase::DoEraseTouch(container_type::iterator a_itr)
  {
    m_currentTouches.erase(a_itr);
    // TODO:Assert here (Touch was not found, for some reason)
  }

  void TouchSurfaceDeviceBase::DoClear()
  {
    m_currentTouches.clear();
  }

  //////////////////////////////////////////////////////////////////////////
  // TouchSurfaceDeviceBuffered

  TouchSurfaceDeviceBuffered::TouchSurfaceDeviceBuffered()
    : base_type()
  {
  }

  const TouchSurfaceDeviceBuffered::buffer_container_type&
    TouchSurfaceDeviceBuffered::GetBufferedTouches() const
  {
    return m_bufferTouches;
  }
  
  void TouchSurfaceDeviceBuffered::
    SendOnTouchBegin(touch_handle_type a_touchHandle,
                     tl_float a_x, tl_float a_y)
  {
    buffered_elem_type bufferedElem(buffered_elem_type::begin,
                                    a_touchHandle, a_x, a_y);
    DoPushBackBufferedElement(bufferedElem);
    DoUpdateTouch(bufferedElem);
  }

  void TouchSurfaceDeviceBuffered::
    SendOnTouchEnd(touch_handle_type a_touchHandle,
                   tl_float a_x, tl_float a_y)
  {
    buffered_elem_type bufferedElem(buffered_elem_type::end,
                                    a_touchHandle, a_x, a_y);
    DoPushBackBufferedElement(bufferedElem);
    DoUpdateTouch(bufferedElem);
  }

  void TouchSurfaceDeviceBuffered::
    SendOnTouchMove(touch_handle_type a_touchHandle,
                    tl_float a_x, tl_float a_y)
  {
    buffered_elem_type bufferedElem(buffered_elem_type::move,
                                    a_touchHandle, a_x, a_y);
    DoPushBackBufferedElement(bufferedElem);
    DoUpdateTouch(bufferedElem);
  }

  void TouchSurfaceDeviceBuffered::
    SendOnTouchCancel(touch_handle_type a_touchHandle,
                      tl_float a_x, tl_float a_y)
  {
    SendOnTouchEnd(a_touchHandle, a_x, a_y);
  }

  void TouchSurfaceDeviceBuffered::Reset()
  {
    m_bufferTouches.clear();
    DoClear();
  }

  void TouchSurfaceDeviceBuffered::
    DoPushBackBufferedElement(const buffered_elem_type& a_elem)
  {
    if (m_bufferTouches.full())
    {
      m_bufferTouches.erase(m_bufferTouches.begin());
    }
    m_bufferTouches.push_back(a_elem);
  }

  void TouchSurfaceDeviceBuffered::
    DoUpdateTouch(const buffered_elem_type& a_elem)
  {
    touch_container_type::iterator touchItr =
      DoFindTouch(a_elem.m_event.m_touchHandle);

    if (touchItr == GetCurrentTouches().end())
    {
      DoPushBackTouch(a_elem.m_event);
    }
    else
    {
      base_type::DoUpdateTouch((*touchItr), a_elem.m_event);
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // TouchSurfaceDeviceImmediate

  TouchSurfaceDeviceImmediate::TouchSurfaceDeviceImmediate()
    : base_type()
  {
  }

  const TouchSurfaceDeviceImmediate::buffer_container_type&
    TouchSurfaceDeviceImmediate::GetBufferedTouches() const
  {
    // Function is never called.
    TLOC_STATIC_ASSERT(false, "This function is only a stub and should never be called!");
    return buffer_container_type();
  }

  void TouchSurfaceDeviceImmediate::
    SendOnTouchBegin(touch_handle_type a_touchHandle,
                     tl_float a_x, tl_float a_y)
  {
    TouchSurfaceEvent event(a_touchHandle);

    event.m_X.m_abs() = a_x;
    event.m_Y.m_abs() = a_y;

    base_type::DoPushBackTouch(event);
  }

  void TouchSurfaceDeviceImmediate::
    SendOnTouchEnd(touch_handle_type a_touchHandle, tl_float a_x, tl_float a_y)
  {
    const touch_container_type::iterator itr = base_type::DoFindTouch(a_touchHandle);

    base_type::DoEraseTouch(itr);
  }

  void TouchSurfaceDeviceImmediate::
    SendOnTouchMove(touch_handle_type a_touchHandle, tl_float a_x, tl_float a_y)
  {
    const touch_container_type::iterator itr = DoFindTouch(a_touchHandle);

    DoUpdateTouch((*itr), a_x, a_y);
  }

  void TouchSurfaceDeviceImmediate::
    SendOnTouchCancel(touch_handle_type a_touchHandle, tl_float a_x, tl_float a_y)
  {
    SendOnTouchEnd(a_touchHandle, a_x, a_y);
  }

  void TouchSurfaceDeviceImmediate::Reset()
  {
    touch_container_type* currentTouches = &(DoGetCurrentTouches());
    touch_container_type::iterator itr = currentTouches->begin();
    const touch_container_type::const_iterator itrEnd = currentTouches->end();

    while (itr != itrEnd)
    {
      (*itr).m_X.m_rel() = 0.f;
      (*itr).m_Y.m_rel() = 0.f;
      ++itr;
    }
  }

};};};