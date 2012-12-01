//
//  OpenGLViewControllerIphone.h
//  tlocGraphics
//
//  Created by Skopworks Inc on 12-08-09.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/window/tlocWindowImpl.h>

namespace tloc { namespace graphics { namespace priv {
      template <>
      class WindowImpl<Window<> >;
};};};

namespace ogl_view_controller
{
  typedef tloc::graphics::priv::WindowImpl<tloc::graphics::Window<> > win_impl_type;
};

@interface OpenGLViewController : UIViewController

@property (assign) 
  ogl_view_controller::win_impl_type* windowImpl;

///-------------------------------------------------------------------------
/// Initializes the view controller with a parent window. This is essential
/// for updating the view when the device rotates
///
/// @param  a_window  The parent window that contains our view
///-------------------------------------------------------------------------
- (id)initWithWindow:(ogl_view_controller::win_impl_type*)a_windowImpl;

///-------------------------------------------------------------------------
/// Callback function that is called if device is rotated. Returns a bool
/// stating whether the view should rotate to the device orientation.
///
/// @param  a_toInterfaceOrientation  The orientation the interface may
///                                   be rotated to.
///-------------------------------------------------------------------------
- (BOOL)shouldAutorotateToInterfaceOrientation:
    (UIInterfaceOrientation)a_toInterfaceOrientation;

///-------------------------------------------------------------------------
/// Callback function that is called if a view is being loaded. This
/// function ultimately loads the nib file. Does nothing in our
/// implementation since we do not allow loading from a nib file.
///-------------------------------------------------------------------------
- (void)loadView;

///-------------------------------------------------------------------------
/// Callback function that is called if interface is rotated. Returns a bool
/// stating whether the view should rotate to the device orientation.
///
/// @param  a_fromInterfaceOrientation  The orientation the interface was
///                                     rotated from.
///-------------------------------------------------------------------------
- (void)didRotateFromInterfaceOrientation:
    (UIInterfaceOrientation)a_fromInterfaceOrientation;
@end
