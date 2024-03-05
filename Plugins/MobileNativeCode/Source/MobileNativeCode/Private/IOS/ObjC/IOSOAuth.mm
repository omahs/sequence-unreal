#import "Native/IOS/IOSOAuth.h"

#if PLATFORM_IOS
#include "IOSAppDelegate.h"
#import <Foundation/Foundation.h>
#include "UMobileNativeCodeBlueprint.h"
#endif

 @interface IOSOAuth()
 @end
 
 @implementation IOSOAuth
 
 + (IOSOAuthWebview*)GetDelegate {
   static IOSOAuthWebview *Singleton = [[IOSOAuthWebview alloc] init];
 
   return Singleton;
 }
 
 + (void)loadBrowserWithUrl {
   [[IOSOAuthWebview GetDelegate] performSelectorOnMainThread:@selector(loadBrowserURLInIOSThread) withObject:nil waitUntilDone:NO];
 }
 
 - (void)loadBrowserURLInIOSThread: (NSString *)providerUrl {
   NSLog(@"IN LOAD BROWSER URL IN IOS THREAD");
 
   NSURL *url = [NSURL URLWithString:providerUrl];
 
   SFSafariViewController *safariVC = [[SFSafariViewController alloc] initWithURL:url];
   safariVC.delegate = self;
 
   UINavigationController *navigationController = [[UINavigationController alloc]initWithRootViewController:safariVC];
   [navigationController setNavigationBarHidden:YES animated:NO];
 
   [[IOSAppDelegate GetDelegate].IOSController presentViewController:navigationController animated:YES completion:nil];
 }

@end
#endif
