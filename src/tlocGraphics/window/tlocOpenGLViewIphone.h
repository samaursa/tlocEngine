//
//  OpenGLViewIphone.h
//  tlocGraphics
//
//  Created by Skopworks Inc on 12-08-09.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface OpenGLView : UIView

@property (nonatomic, strong, readonly) EAGLContext* context;

///-------------------------------------------------------------------------
/// Creates the context as well as the framebuffers/renderbuffers needed to
/// display OpenGL content in a window
///
/// @param  a_frame       The dimensions of our view
/// @param  a_retained    Retain the contents of the colour buffer after 
///                       rendering
/// @param  a_bitsPerPix  Bits per pixel. 32 and 16 bits are only supported
/// @param  a_depthBits   Depth buffer bits. 24 is currently only supported.
///                       A depth buffer will not be created if 0.
/// @param  a_stencilBits Stencil buffer bits. 8 is currently only supported.
///                       A stencil buffer will not be created if 0.
///-------------------------------------------------------------------------
- (id)initWithFrame:(CGRect)a_frame
      retainBacking:(BOOL)a_retained
       bitsPerPixel:(size_t)a_bitsPerPix
       bitsPerDepth:(size_t)a_depthBits
     bitsPerStencil:(size_t)a_stencilBits;

///-------------------------------------------------------------------------
/// Calls the display update for our view
///-------------------------------------------------------------------------
- (void)SwapBuffers;

///-------------------------------------------------------------------------
/// Set the context of this view as the current one.
///-------------------------------------------------------------------------
- (void)SetAsCurrentContext;

///-------------------------------------------------------------------------
/// Allows us to update the render buffer dimensions. Especially useful if
/// application supports screen rotation.
///-------------------------------------------------------------------------
- (void)UpdateRenderBufferDimensions;

///-------------------------------------------------------------------------
/// Callback function that will be called once, immediately after the user 
/// has started touching the screen. Must be called if overridden.
///
/// @param  a_touches     A set of UITouch instances that represent the 
///                       touches for the starting phase of the event.
/// @param  a_event       An object rpresenting the event to which the
///                       touches belong.
///-------------------------------------------------------------------------
- (void)touchesBegan:(NSSet *)a_touches withEvent:(UIEvent *)a_event;

///-------------------------------------------------------------------------
/// Callback function that will be called once, immediately after the user 
/// has stopped touching the screen. Must be called if overridden.
///
/// @param  a_touches     A set of UITouch instances that represent the 
///                       touches for the ending phase of the event.
/// @param  a_event       An object rpresenting the event to which the
///                       touches belong.
///-------------------------------------------------------------------------
- (void)touchesEnded:(NSSet *)a_touches withEvent:(UIEvent *)a_event;

///-------------------------------------------------------------------------
/// Callback function that will be called while the user has started 
/// touching the screen. Must be called if overridden.
///
/// @param  a_touches     A set of UITouch instances that represent the 
///                       touches that are moving during the phase of the
///                       event.
/// @param  a_event       An object rpresenting the event to which the
///                       touches belong.
///-------------------------------------------------------------------------
- (void)touchesMoved:(NSSet *)a_touches withEvent:(UIEvent *)a_event;

@end