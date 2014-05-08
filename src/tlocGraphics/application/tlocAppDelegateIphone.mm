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

- (void)applicationWillTerminate:(UIApplication *)application
{
  // Called when the application is about to terminate. Temporarily sending
  // the event to the window until the concept of an application exists.

  using namespace tloc::gfx_win;

  Window_T<>* currentActiveWindow = GetCurrentActiveWindow();
  if (currentActiveWindow != nullptr)
  {
    WindowEvent evt(WindowEvent::destroy,
                    currentActiveWindow->GetWidth(),
                    currentActiveWindow->GetHeight());
    currentActiveWindow->SendEvent(evt);
  }

}

- (void)applicationWillResignActive:(UIApplication *)application
{
  // Sent when the application is about to move from active to inactive state. 
  // This can occur for certain types of temporary interruptions (such as an 
  // incoming phone call or SMS message) or when the user quits the application 
  // and it begins the transition to the background state.
  // Use this method to pause ongoing tasks, disable timers, and throttle down 
  // OpenGL ES frame rates. Games should use this method to pause the game.
  tloc::graphics::win::Window_T<>* currentActiveWindow;
  currentActiveWindow = tloc::graphics::win::GetCurrentActiveWindow();
  if (currentActiveWindow != NULL) 
  {
    using namespace tloc::graphics::win;
    
    WindowEvent evt(WindowEvent::lost_focus,
                    currentActiveWindow->GetWidth(),
                    currentActiveWindow->GetHeight());
    currentActiveWindow->SendEvent(evt);
  }
  
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
  using namespace tloc::graphics::win;
  // Restart any tasks that were paused (or not yet started) while the 
  // application was inactive. If the application was previously in the
  // background, optionally refresh the user interface.
  tloc::graphics::win::Window_T<>* currentActiveWindow;
  currentActiveWindow = tloc::graphics::win::GetCurrentActiveWindow();
  if (currentActiveWindow != NULL)
  {
    WindowEvent evt(WindowEvent::gained_focus,
                    currentActiveWindow->GetWidth(),
                    currentActiveWindow->GetHeight());
    currentActiveWindow->SendEvent(evt);
  }
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
  // Called when a URL is sent to our application to be opened. In this case
  // we are temporarily using the window to send the event. In the future when
  // the concept of an application exists, we will be sending the even through
  // there.

  using namespace tloc::graphics::win;
  typedef WindowEvent::string_type  string_type;

  Window_T<>* currentActiveWindow = GetCurrentActiveWindow();
  if (currentActiveWindow != nullptr)
  {
    const NSString* urlStr = [url absoluteString];
    const string_type url([urlStr UTF8String]);
    const string_type urlSourceApplication([sourceApplication UTF8String]);

    WindowEvent evt(WindowEvent::open_url,
                    currentActiveWindow->GetWidth(),
                    currentActiveWindow->GetHeight(),
                    url,
                    urlSourceApplication);
    currentActiveWindow->SendEvent(evt);
  }

  return YES;
}

@end
