#import "IOSOAuth.h"

#if PLATFORM_IOS
#include "IOSAppDelegate.h"
#import <Foundation/Foundation.h>
#endif

 @interface IOSOAuth()
 @end

 static NSString *url = @"https://www.google.com";
 
 @implementation IOSOAuth

 + (NSString *)url {return url;}
 
 + (IOSOAuth*)GetDelegate {
   static IOSOAuth *Singleton = [[IOSOAuth alloc] init];
 
   return Singleton;
 }
 
 + (void)loadBrowserWithUrl: (NSString *)providerUrl {
     NSLog(@"IN LOAD BROWSER WITH URL");
     url = providerUrl;
     [self performSelectorOnMainThread:@selector(loadBrowserURLInIOSThread) withObject:nil waitUntilDone:YES];
 }
 
 + (void)loadBrowserURLInIOSThread {
   NSLog(@"IN LOAD BROWSER URL IN IOS THREAD");
 
   NSURL *_url = [NSURL URLWithString:[IOSOAuth url]];
 
   SFSafariViewController *safariVC = [[SFSafariViewController alloc] initWithURL:_url];
//   safariVC.delegate = self;
 
   UINavigationController *navigationController = [[UINavigationController alloc]initWithRootViewController:safariVC];
   [navigationController setNavigationBarHidden:YES animated:NO];
 
   [[IOSAppDelegate GetDelegate].IOSController presentViewController:navigationController animated:YES completion:nil];
 }


// -(void)safariViewController:(SFSafariViewController *)controller :(didCompleteInitialLoad:BOOL)didLoadSuccessfully {
//   //Load finished
//     NSLog(@"IN LOAD FINISHED");
// }

 -(void)safariViewControllerDidFinish:(SFSafariViewController *)controller {
   //Done button pressed
     NSLog(@"IN DONE BUTTON PRESSED");
     [self dismissViewControllerAnimated:NO completion:nil];
 }

 - (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<NSString *, id> *)options {
     NSLog(@"HERE");
   NSString *sourceApplication = [options objectForKey:@"UIApplicationOpenURLOptionsSourceApplicationKey"];
   NSString *urlScheme = [url scheme];
   NSString *urlQuery = [url query];

   if ([urlScheme isEqualToString:@"freedomofkeima"] && [sourceApplication isEqualToString:@"com.apple.SafariViewService"]) {

     //TODO check for success query param

     NSLog(@"Value: %@", urlQuery);
     NSDictionary *data = [NSDictionary dictionaryWithObject:urlQuery forKey:@"key"];

     [[NSNotificationCenter defaultCenter] postNotificationName:@"SafariCallback" object:self userInfo:data];

     return YES;
   }

   return NO;
 }

 - (void)safariCallback:(NSNotification *)notification {
     NSLog(@"IN SAFARI CALLBACK");
   [[IOSAppDelegate GetDelegate].IOSController dismissViewControllerAnimated:NO completion:nil];
 }

@end
