#import "tlocOpenGLViewIphone.h"

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#import <QuartzCore/CAEAGLLayer.h>
#import <OpenGLES/EAGLDrawable.h>

#include <tlocGraphics/opengl/tlocError.h>

using namespace tloc;
using namespace input;
using namespace input_hid;
using namespace gfx;
using namespace gfx_gl;

typedef FramebufferObject         fbo_type;
typedef framebuffer_object_sptr   fbo_sptr;

typedef RenderbufferObject          rbo_type;
typedef render_buffer_object_sptr   rbo_sptr;

typedef hid::priv::TouchSurfaceDeviceBase       touch_surface_device_base;
typedef hid::priv::TouchSurfaceDeviceBuffered   touch_surface_device_b;
typedef hid::priv::TouchSurfaceDeviceImmediate  touch_surface_device_i;

typedef touch_surface_device_b::touch_handle_type touch_handle_buffered_type;
typedef touch_surface_device_i::touch_handle_type touch_handle_immediate_type;

//////////////////////////////////////////////////////////////////////////
// OpenGLView extended interface

@interface OpenGLView() {

  EAGLContext* m_context;

  fbo_sptr m_fbo;
  rbo_sptr m_rboColor;

  touch_surface_device_i* m_touchObserverImmediate;
  touch_surface_device_b* m_touchObserverBuffered;
}

@end

//////////////////////////////////////////////////////////////////////////
// OpenGLView

@implementation OpenGLView

@synthesize context = m_context;

- (id)initWithFrame:(CGRect)a_frame
        screenScale:(CGFloat)a_scale
      retainBacking:(BOOL)a_retained 
       bitsPerPixel:(size_t)a_bitsPerPix
       bitsPerDepth:(size_t)a_depthBits 
     bitsPerStencil:(size_t)a_stencilBits
{
  TLOC_ASSERT(a_frame.size.width > 0 && a_frame.size.height > 0,
              "View must have a size of more than 0 per axis");
  self = [super initWithFrame:a_frame];
  if (self) 
  {
    NSString* colorFormat = nil;
    
    if (a_bitsPerPix == 32) 
    {
      colorFormat = kEAGLColorFormatRGBA8;
    }
    else if (a_bitsPerPix == 16)
    {
      colorFormat = kEAGLColorFormatRGB565;
    }
    
    TLOC_ASSERT(colorFormat, "Color format not supported."
                "Bits per pixel can only be 32 bit or 8 bit ");
    
    // CAEGLLayer => rendering layer
    CAEAGLLayer* eaglLayer = (CAEAGLLayer*)self.layer;
    
    // Setting properties 
    // NOTE: If we retain our backing, this means that the layer we render to 
    // will keep it's data as a gurantee, until we re-render. If set to false, 
    // it may change
    eaglLayer.opaque = YES;
    eaglLayer.drawableProperties = 
    [NSDictionary dictionaryWithObjectsAndKeys:
     [NSNumber numberWithBool:a_retained], 
     kEAGLDrawablePropertyRetainedBacking, 
     colorFormat, 
     kEAGLDrawablePropertyColorFormat, 
     nil];
    
    m_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    TLOC_ASSERT(m_context, "OpenGL ES 2.0 Context could not be created");
    
    // NOTE: All OpenGL calls will now use this context
    BOOL result;
    result = [EAGLContext setCurrentContext:m_context];
    TLOC_ASSERT(result,
                "OpenGL ES 2.0 context could not be set as the current context");
    TLOC_UNUSED(result);
    
    // Scale view to the main screen's scale (Retina screen)
    // Applicable iff property is available
    if ([self respondsToSelector:@selector(contentScaleFactor)])
    {
      self.contentScaleFactor = [UIScreen mainScreen].scale;
    }
      
    // Note: We are not initializing the rbo, because it creates its own
    // storage. In this case CAEAGLLayer provides us storage (which will render
    // to the screen)
    GLint renderBufferWidth = 0;
    GLint renderBufferHeight = 0;

    rbo_type::Params rboParams;
    m_rboColor.reset(new RenderbufferObject(rboParams));
    m_rboColor->InitializeWithoutStorage();
    {
      RenderbufferObject::Bind b(m_rboColor.get());
      [m_context renderbufferStorage:GL_RENDERBUFFER
                        fromDrawable:(CAEAGLLayer*)self.layer];

      [OpenGLView DoGetCurrentRenderBufferWidth:&renderBufferWidth
                                      andHeight:&renderBufferHeight];
    }

    using namespace gfx_gl::p_framebuffer_object;
    m_fbo.reset(new fbo_type);

    m_fbo->Attach<p_framebuffer_object::target::Framebuffer,
    p_framebuffer_object::attachment::ColorAttachment<0> >(*m_rboColor);

    if ((a_depthBits) || (a_stencilBits))
    {
      typedef RenderbufferObject::Params rbo_params;
      rbo_params rboDepthParams;
      rboDepthParams.Dimensions
        (rbo_params::dimension_type(renderBufferWidth, renderBufferHeight));

      // NOTE: If a Stencil buffer is requested, it must be packed with a
      // coupling depth buffer. 
      // NOTE: iOS only supports a 24bit depth buffer and an 8 bit stencil 
      // buffer.
      using namespace gfx_gl::p_renderbuffer_object;
      if (a_stencilBits == 8 && (a_depthBits == 24 || a_depthBits == 0))
      {
        rboDepthParams.InternalFormat<internal_format::Depth24Stencil8>();
      }
      else if (a_depthBits == 24)
      {
        rboDepthParams.InternalFormat<internal_format::DepthComponent24>();
      }

      render_buffer_object_sptr rboDepth;
      rboDepth.reset(new RenderbufferObject(rboDepthParams));
      rboDepth->Initialize();

      if (a_depthBits)
      {
        m_fbo->Attach<target::Framebuffer, attachment::Depth>(*rboDepth);
      }
      if (a_stencilBits) 
      {
        m_fbo->Attach<target::Framebuffer, attachment::Stencil>(*rboDepth);
      }
    }

    // This is so we can properly resize our view when orientation changes.
    self.autoresizingMask = 0;
    
    self.multipleTouchEnabled = YES;
    
    // This mimics the behaviour when creating a window on the Win32 platform.
    glViewport(0, 0, self.bounds.size.width * a_scale,
               self.bounds.size.height * a_scale);
  }
  return self;
}

- (void)SwapBuffers
{
  RenderbufferObject::Bind b(m_rboColor.get());
  [m_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)SetAsCurrentContext
{
  [EAGLContext setCurrentContext:m_context];
}

- (void)UpdateRenderBufferDimensions
{
//  fbo_type::Bind(m_fbo);
//  m_fbo
//  glBindFramebuffer(GL_FRAMEBUFFER, m_viewFrameBuffer);
//  glBindRenderbuffer(GL_RENDERBUFFER, 0);
//  glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
//                            GL_COLOR_ATTACHMENT0, 
//                            GL_RENDERBUFFER, 
//                            0);
//  glDeleteRenderbuffers(1, &m_viewRenderBuffer);
//
//  glGenRenderbuffers(1, &m_viewRenderBuffer);
//  glBindRenderbuffer(GL_RENDERBUFFER, m_viewRenderBuffer);
//  [m_context renderbufferStorage:GL_RENDERBUFFER 
//                    fromDrawable:(CAEAGLLayer*)self.layer];
//  glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
//                            GL_COLOR_ATTACHMENT0, 
//                            GL_RENDERBUFFER, 
//                            m_viewRenderBuffer);
//  
//  if (m_depthRenderBuffer != 0) 
//  {
//    GLint renderBufferWidth = 0;
//    GLint renderBufferHeight = 0;
//    
//    [OpenGLView DoGetCurrentRenderBufferWidth:&renderBufferWidth
//                                    andHeight:&renderBufferHeight];
//    
//    glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderBuffer);
//    glRenderbufferStorage(GL_RENDERBUFFER, m_depthBufferFormat, 
//                          renderBufferWidth, renderBufferHeight);
//  }
}

- (void)RegisterTouchSurfaceDeviceBuffered:
    (touch_surface_device_base*)a_touchDevice
{
  if (m_touchObserverBuffered == NULL)
  {
    m_touchObserverBuffered =
      static_cast <touch_surface_device_b*>(a_touchDevice);
  }
}

- (void)RegisterTouchSurfaceDeviceImmediate:
    (touch_surface_device_base*)a_touchDevice
{
  if (m_touchObserverImmediate == NULL)
  {
    m_touchObserverImmediate =
      static_cast <touch_surface_device_i*>(a_touchDevice);
  }
}

- (bool)UnRegisterTouchSurfaceDeviceBuffered:
    (touch_surface_device_base*)a_touchDevice
{
  if (a_touchDevice == m_touchObserverBuffered)
  {
    m_touchObserverBuffered = NULL;
    return true;
  }
  else
  {
    return false;
  }
}

- (bool)UnRegisterTouchSurfaceDeviceImmediate:
    (touch_surface_device_base*)a_touchDevice
{
  if (a_touchDevice == m_touchObserverImmediate)
  {
    m_touchObserverBuffered = NULL;
    return true;
  }
  else
  {
    return false;
  }
}

- (void)touchesBegan:(NSSet *)a_touches withEvent:(UIEvent *)a_event
{
  for (UITouch* touch in a_touches)
  {
    CGPoint touchLocation = [touch locationInView:self];
    if (m_touchObserverBuffered != NULL)
    {
      m_touchObserverBuffered->SendOnTouchBegin((touch_handle_buffered_type)touch,
                                                touchLocation.x, touchLocation.y);
    }
    if (m_touchObserverImmediate != NULL) 
    {
      m_touchObserverImmediate->SendOnTouchBegin((touch_handle_immediate_type)touch,
                                                 touchLocation.x, touchLocation.y);
    }
  }
}

- (void)touchesEnded:(NSSet *)a_touches withEvent:(UIEvent *)a_event
{
  for (UITouch* touch in a_touches)
  {
    CGPoint touchLocation = [touch locationInView:self];
    if (m_touchObserverBuffered != NULL)
    {
      m_touchObserverBuffered->SendOnTouchEnd((touch_handle_buffered_type)touch,
                                              touchLocation.x, touchLocation.y);
    }
    if (m_touchObserverImmediate != NULL)
    {
      m_touchObserverImmediate->SendOnTouchEnd((touch_handle_immediate_type)touch,
                                                 touchLocation.x, touchLocation.y);
    }
  }
}

- (void)touchesMoved:(NSSet *)a_touches withEvent:(UIEvent *)a_event
{
  for (UITouch* touch in a_touches)
  {
    CGPoint touchLocation = [touch locationInView:self];
    if (m_touchObserverBuffered != NULL)
    {
      m_touchObserverBuffered->SendOnTouchMove((touch_handle_buffered_type)touch,
                                               touchLocation.x, touchLocation.y);
    }
    if (m_touchObserverImmediate != NULL)
    {
      m_touchObserverImmediate->SendOnTouchMove((touch_handle_immediate_type)touch,
                                                 touchLocation.x, touchLocation.y);
    }
  } 
}

- (void)touchesCancelled:(NSSet *)a_touches withEvent:(UIEvent *)a_event
{
  for (UITouch* touch in a_touches)
  {
    CGPoint touchLocation = [touch locationInView:self];
    if (m_touchObserverBuffered != NULL) 
    {
      m_touchObserverBuffered->SendOnTouchCancel((touch_handle_buffered_type)touch, 
                                                    touchLocation.x, touchLocation.y);
    }
    if (m_touchObserverImmediate != NULL)
    {
      m_touchObserverImmediate->SendOnTouchCancel((touch_handle_immediate_type)touch,
                                                  touchLocation.x, touchLocation.y);
    }
  }
}

- (fbo_sptr)GetFramebuffer
{
  return m_fbo;
}

//------------------------------------------------------------------------
// Private inherited functions

- (void)dealloc
{
  if ([EAGLContext currentContext] == m_context )
  {
    [EAGLContext setCurrentContext:nil];
  }
  [m_context release];
  [super dealloc];
}

+ (Class)layerClass
{
  return [CAEAGLLayer class];
}

//------------------------------------------------------------------------
// Private helper functions

+ (void)DoGetCurrentRenderBufferWidth:(GLint*)a_width andHeight:(GLint*)a_height
{
  // Grab the width and height of our current view renderbuffer. This should
  // be set to the correct resolution of the main screen of our device.
  glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, 
                               a_width);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, 
                               a_height);
}

@end
