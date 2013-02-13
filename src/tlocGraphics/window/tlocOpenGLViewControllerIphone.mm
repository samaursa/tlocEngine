//
//  OpenGLViewControllerIphone.m
//  tlocGraphics
//
//  Created by Skopworks Inc on 12-08-09.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "tlocOpenGLViewControllerIphone.h"
#include <tlocGraphics/window/tlocWindowImplIphone.h>

//////////////////////////////////////////////////////////////////////////
// OpenGLViewController

@implementation OpenGLViewController

@synthesize windowImpl;

- (id)initWithWindow:
    (ogl_view_controller::win_impl_type*)a_windowImpl
{
  self = [super init];
  if (self) 
  {
    self.windowImpl = a_windowImpl;
  }
  return self;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:
    (UIInterfaceOrientation)toInterfaceOrientation
{
  // TODO: based on window settings, allow or disallow the view to change 
  // orientation
  return YES;
}

- (void)loadView
{
  // Intentionally empty
}

- (void)didRotateFromInterfaceOrientation:
    (UIInterfaceOrientation)fromInterfaceOrientation
{
  // TODO: instead of grabbing the bounds of the main screen, make it grab
  // grab from the screen it's on. Only use dimensions that the window
  // already has.
  UIWindow* uiwindow = self->windowImpl->GetWindowHandle();
  UIScreen* uiscreen = [uiwindow screen];
  
  CGRect frame;
  if (self->windowImpl->GetWindowSettings().m_style& 
      tloc::graphics::win::WindowSettings::style_titlebar)
  {
    frame = [uiscreen applicationFrame];
  }
  else 
  {
    frame = [uiscreen bounds];
  }
  
  [uiwindow setFrame:frame];
  
  OpenGLView* view = self->windowImpl->GetOpenGLViewHandle();
  [view setFrame:uiwindow.bounds];
  [view UpdateRenderBufferDimensions];
  
  self->windowImpl->GetParentWindowHandle()
    ->SendEvent(tloc::graphics::win::WindowEvent::resized);
}

@end
