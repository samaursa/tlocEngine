//
//  OpenGLViewIphone.m
//  tlocGraphics
//
//  Created by Skopworks Inc on 12-08-09.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "tlocOpenGLViewIphone.h"

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#import <QuartzCore/CAEAGLLayer.h>
#import <OpenGLES/EAGLDrawable.h>

//////////////////////////////////////////////////////////////////////////
// OpenGLView extended interface

@interface OpenGLView() {
  EAGLContext* m_context;
  
  GLuint m_viewFrameBuffer;
  
  GLuint m_viewRenderBuffer, m_depthRenderBuffer;
  
  GLenum m_depthBufferFormat;
}

@end

//////////////////////////////////////////////////////////////////////////
// OpenGLView

@implementation OpenGLView

@synthesize context = m_context;

- (id)initWithFrame:(CGRect)a_frame
      retainBacking:(BOOL)a_retained 
       bitsPerPixel:(size_t)a_bitsPerPix
       bitsPerDepth:(size_t)a_depthBits 
     bitsPerStencil:(size_t)a_stencilBits
{
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
    
    assert(colorFormat);
    
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
    assert(m_context);
    
    // NOTE: All OpenGL calls will now use this context
    BOOL result;
    result = [EAGLContext setCurrentContext:m_context];
    assert(result);
    (void)result;
    
    // Scale view to the main screen's scale (Retina screen)
    // Applicable iff property is available
    if ([self respondsToSelector:@selector(contentScaleFactor)])
    {
      self.contentScaleFactor = [UIScreen mainScreen].scale;
    }
    
    // Remember: No allocation preformed here, only handle returned.
    glGenFramebuffers(1, &m_viewFrameBuffer);
    glGenRenderbuffers(1, &m_viewRenderBuffer);
    
    // Instead of creating storage for the renderbuffer we tell the context 
    // that our "layer" is what we want to use as storage.
    glBindFramebuffer(GL_FRAMEBUFFER, m_viewFrameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_viewRenderBuffer);
    [m_context renderbufferStorage:GL_RENDERBUFFER 
                      fromDrawable:(CAEAGLLayer*)self.layer];
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
                              GL_COLOR_ATTACHMENT0, 
                              GL_RENDERBUFFER, 
                              m_viewRenderBuffer);
    
    m_depthBufferFormat = 0;
    
    if ((a_depthBits) || (a_stencilBits))
    {
      // NOTE: If a Stencil buffer is requested, it must be packed with a
      // coupling depth buffer. 
      // NOTE: iOS only supports a 24bit depth buffer and an 8 bit stencil 
      // buffer.
      if (a_stencilBits == 8 && (a_depthBits == 24 || a_depthBits == 0)) 
      {
        m_depthBufferFormat = GL_DEPTH24_STENCIL8_OES;
      }
      else if (a_depthBits == 24)
      {
        m_depthBufferFormat = GL_DEPTH_COMPONENT24_OES;
      }
      
      assert(m_depthBufferFormat);
      
      GLint renderBufferWidth = 0;
      GLint renderBufferHeight = 0;
      
      [OpenGLView DoGetCurrentRenderBufferWidth:&renderBufferWidth 
                                      andHeight:&renderBufferHeight];
      
      glGenRenderbuffers(1, &m_depthRenderBuffer);
      glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderBuffer);
      glRenderbufferStorage(GL_RENDERBUFFER, m_depthBufferFormat, 
                            renderBufferWidth, renderBufferHeight);
      if (a_depthBits) 
      {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 
                                  GL_RENDERBUFFER, m_depthRenderBuffer);
      }
      if (a_stencilBits) 
      {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, 
                                  GL_RENDERBUFFER, m_depthRenderBuffer);
      }
      
    }
    
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    
    // This is so we can properly resize our view when orientation changes.
    self.autoresizingMask = 0;
    
    // This mimics the behaviour when creating a window on the Win32 platform.
    glViewport(0, 0, self.bounds.size.width, self.bounds.size.height);
  }
  return self;
}

- (void)SwapBuffers
{
  glBindRenderbuffer(GL_RENDERBUFFER, m_viewRenderBuffer);
  [m_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)SetAsCurrentContext
{
  [EAGLContext setCurrentContext:m_context];
}

- (void)UpdateRenderBufferDimensions
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_viewFrameBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
                            GL_COLOR_ATTACHMENT0, 
                            GL_RENDERBUFFER, 
                            0);
  glDeleteRenderbuffers(1, &m_viewRenderBuffer);
  
  glGenRenderbuffers(1, &m_viewRenderBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, m_viewRenderBuffer);
  [m_context renderbufferStorage:GL_RENDERBUFFER 
                    fromDrawable:(CAEAGLLayer*)self.layer];
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
                            GL_COLOR_ATTACHMENT0, 
                            GL_RENDERBUFFER, 
                            m_viewRenderBuffer);
  
  if (m_depthRenderBuffer != 0) 
  {
    GLint renderBufferWidth = 0;
    GLint renderBufferHeight = 0;
    
    [OpenGLView DoGetCurrentRenderBufferWidth:&renderBufferWidth 
                                    andHeight:&renderBufferHeight];
    
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, m_depthBufferFormat, 
                          renderBufferWidth, renderBufferHeight);
  }
}

- (void)touchesBegan:(NSSet *)a_touches withEvent:(UIEvent *)a_event
{
  // Stub Func
}

- (void)touchesEnded:(NSSet *)a_touches withEvent:(UIEvent *)a_event
{
  // Stub Func  
}

- (void)touchesMoved:(NSSet *)a_touches withEvent:(UIEvent *)a_event
{
  // Stub Func  
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)a_event
{
  // Stub Func
}

//------------------------------------------------------------------------
// Private inherited functions

- (void)dealloc
{
  [self DoDestroyFramebuffer];
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

- (void)DoDestroyFramebuffer
{
  // Delete all frame/render buffers
  glDeleteFramebuffers(1, &m_viewFrameBuffer);
  glDeleteRenderbuffers(1, &m_viewRenderBuffer);
  
  if (m_depthRenderBuffer) 
  {
    glDeleteRenderbuffers(1, &m_depthRenderBuffer);
  }
}

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
