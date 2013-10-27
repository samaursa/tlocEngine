#ifndef TLOC_TOUCH_SURFACE_DEVICE_H
#define TLOC_TOUCH_SURFACE_DEVICE_H

#include <tloccore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

#include <tlocInput/hid/tlocTouchSurfaceImpl.h>

namespace tloc { namespace input { namespace hid { namespace priv {

  class TouchSurfaceBufferedElement
  {
  public:
    enum BufferedTouchState
    {
      none,
      begin,
      move,
      end,

      count
    }; typedef u32 buffered_touch_state_type;

    TouchSurfaceBufferedElement(BufferedTouchState a_currentState = none,
                                const TouchSurfaceEvent& a_event = TouchSurfaceEvent())
                               : m_currentState(a_currentState)
                               , m_event(a_event) {}

    TouchSurfaceBufferedElement(BufferedTouchState a_currentState,
                                TouchSurfaceEvent::touch_handle_type a_handle,
                                TouchSurfaceEvent::axis_value_type a_x,
                                TouchSurfaceEvent::axis_value_type a_y)
                                : m_currentState(a_currentState)
                                , m_event(a_handle, a_x, a_y) {}

    buffered_touch_state_type m_currentState;

    TouchSurfaceEvent m_event;
  };

  class TouchSurfaceDeviceBase
  {
    static const tl_size sm_maxTouches = 11;
  public:
    typedef core_conts::tl_array_fixed
      <TouchSurfaceEvent, sm_maxTouches>::type      container_type;

    typedef TouchSurfaceBufferedElement             buffered_elem_type;

    typedef core_conts::tl_array_fixed
      <buffered_elem_type,
      buffer_size::touch_surface_buffer_size>::type buffer_container_type;

    typedef TouchSurfaceEvent                       touch_surface_event_type;
    typedef TouchSurfaceEvent::touch_handle_type    touch_handle_type;

    const container_type& GetCurrentTouches() const;

    const touch_surface_event_type*
      GetTouch(touch_handle_type a_touchHandle) const;

  protected:

    TouchSurfaceDeviceBase();

    container_type& DoGetCurrentTouches();

    container_type::const_iterator
    DoFindTouch(touch_handle_type a_touchHandle) const;
    container_type::iterator DoFindTouch(touch_handle_type a_touchHandle);

    static void DoUpdateTouch(touch_surface_event_type& a_touchToUpdate,
                              const touch_surface_event_type& a_update);
    static void DoUpdateTouch(touch_surface_event_type& a_touchToUpdate,
                              tl_float a_x, tl_float a_y);

    void DoPushBackTouch(const touch_surface_event_type& a_event);
    void DoEraseTouch(container_type::iterator a_itr);
    void DoClear();

  private:
    container_type m_currentTouches;
  };

  class TouchSurfaceDeviceBuffered
    : public TouchSurfaceDeviceBase
  {
  public:

    typedef TouchSurfaceDeviceBase                  base_type;

    typedef base_type::container_type               touch_container_type;

    typedef base_type::buffered_elem_type           buffered_elem_type;
    typedef base_type::buffer_container_type        buffer_container_type;

    typedef base_type::touch_surface_event_type     touch_surface_event_type;
    typedef base_type::touch_handle_type            touch_handle_type;

    TouchSurfaceDeviceBuffered();

    const buffer_container_type& GetBufferedTouches() const;

    void SendOnTouchBegin(touch_handle_type a_touchHandle,
                          tl_float a_x, tl_float a_y);
    void SendOnTouchEnd(touch_handle_type a_touchHandle,
                        tl_float a_x, tl_float a_y);
    void SendOnTouchMove(touch_handle_type a_touchHandle,
                         tl_float a_x, tl_float a_y);
    void SendOnTouchCancel(touch_handle_type a_touchHandle,
                           tl_float a_x, tl_float a_y);

    void Reset();
  private:
    void DoPushBackBufferedElement(const buffered_elem_type& a_elem);
    void DoUpdateTouch(const buffered_elem_type& a_elem);

    buffer_container_type m_bufferTouches;
  };

  class TouchSurfaceDeviceImmediate
    : public TouchSurfaceDeviceBase
  {
  public:

    typedef TouchSurfaceDeviceBase                base_type;
    typedef base_type::container_type             touch_container_type;

    typedef base_type::touch_surface_event_type   touch_surface_event_type;
    typedef base_type::touch_handle_type          touch_handle_type;

    TouchSurfaceDeviceImmediate();

    const buffer_container_type& GetBufferedTouches() const;

    void SendOnTouchBegin(touch_handle_type a_touchHandle,
                          tl_float a_x, tl_float a_y);
    void SendOnTouchEnd(touch_handle_type a_touchHandle,
                        tl_float a_x, tl_float a_y);
    void SendOnTouchMove(touch_handle_type a_touchHandle,
                         tl_float a_x, tl_float a_y);
    void SendOnTouchCancel(touch_handle_type a_touchHandle,
                           tl_float a_x, tl_float a_y);

    void Reset();

  };

};};};};

#endif
