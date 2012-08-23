//
//  AppDelegateIphone.m
//  tlocCore
//
//  Created by Skopworks Inc on 12-08-09.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "tlocAppDelegateIphone.h"

#include <tlocCore/tlocBase.h>
#include <tlocGraphics/window/tlocWindow.h>

static int g_argc;
static char** g_argv;

int main(int argc, char** argv)
{
  g_argc = argc;
  g_argv = argv;
  
  @autoreleasepool
  { 
    UIApplicationMain(argc, argv, nil, 
                      NSStringFromClass([AppDelegateIphone class])); 
  }
}

@implementation AppDelegateIphone

- (void)postApplicationDidFinishLaunching
{
  TLOC_MAIN(g_argc, g_argv);
}

- (BOOL)application:(UIApplication*)application 
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  // Tricks the application delegate into calling the user defined "main" instead
  // of entering the applications "RunLoop". The user defined main is called 
  // immediately after this function completes execution.
  [self performSelector:@selector(postApplicationDidFinishLaunching) 
             withObject:nil afterDelay:0.0];
  return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
  // Sent when the application is about to move from active to inactive state. 
  // This can occur for certain types of temporary interruptions (such as an 
  // incoming phone call or SMS message) or when the user quits the application 
  // and it begins the transition to the background state.
  // Use this method to pause ongoing tasks, disable timers, and throttle down 
  // OpenGL ES frame rates. Games should use this method to pause the game.
  tloc::graphics::Window<>* currentActiveWindow;
  currentActiveWindow = tloc::graphics::GetCurrentActiveWindow();
  if (currentActiveWindow != NULL) 
  {
    currentActiveWindow->SendEvent(tloc::graphics::WindowEvent::lost_focus);
  }
  
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
  // Restart any tasks that were paused (or not yet started) while the 
  // application was inactive. If the application was previously in the 
  // background, optionally refresh the user interface.
  tloc::graphics::Window<>* currentActiveWindow;
  currentActiveWindow = tloc::graphics::GetCurrentActiveWindow();
  if (currentActiveWindow != NULL) 
  {
    currentActiveWindow->SendEvent(tloc::graphics::WindowEvent::gained_focus);
  }
}

@end
