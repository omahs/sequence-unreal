#import "Native/IOS/IOSOAuthWebview.h"

#if PLATFORM_IOS
#include "IOSAppDelegate.h"
#import <Foundation/Foundation.h>
#import <SafariServices/SafariServices.h>
#endif

namespace IOSOAuth {
	void RequestAuthCode(const FString& providerUrl) {
        NSLog(@"IN IOS REQUEST AUTH");
        NSString * myString = @"https://www.google.com";
//         [IOSOAuthWebview openWebview: myString];

	}
}

// @implementation IOSOAuthWebview
// + (void)openWebview: (NSString *)providerUrl {
//         NSLog(@"IN OPEN WEBVIEW");
//         NSURL *url = [NSURL URLWithString: providerUrl];
//         
//         UIWindow * currentwindow = [[UIApplication sharedApplication] delegate].window;
//         UIViewController *rootViewController = currentwindow.rootViewController;
// 
//         SFSafariViewController *svc = [[SFSafariViewController alloc] initWithURL:url];
// // //             [self->window.rootViewController presentViewController:svc animated:NO completion:nil];
// 	}
// @end


// #if PLATFORM_IOS
// @interface IOSOAuthWebview()
// @end
// 
// @implementation IOSOAuthWebview
// 
// + (IOSOAuthWebview*)GetDelegate {
//   static IOSOAuthWebview *Singleton = [[IOSOAuthWebview alloc] init];
// 
//   return Singleton;
// }
// 
// + (void)loadBrowserWithUrl {
//   [[IOSOAuthWebview GetDelegate] performSelectorOnMainThread:@selector(loadBrowserURLInIOSThread) withObject:nil waitUntilDone:NO];
// }
// 
// - (void)loadBrowserURLInIOSThread: (NSString *)providerUrl {
// 
//   NSURL *url = [NSURL URLWithString:providerUrl];
// 
//   SFSafariViewController *safariVC = [[SFSafariViewController alloc] initWithURL:url];
//   safariVC.delegate = self;
// 
//   UINavigationController *navigationController = [[UINavigationController alloc]initWithRootViewController:safariVC];
//   [navigationController setNavigationBarHidden:YES animated:NO];
// 
//   [[IOSAppDelegate GetDelegate].IOSController presentViewController:navigationController animated:YES completion:nil];
// }
// 
// #pragma mark - SFSafariViewController delegate methods

// -(void)safariViewController:(SFSafariViewController *)controller (didCompleteInitialLoad:BOOL)didLoadSuccessfully {
//   //Load finished
// }
// 
// -(void)safariViewControllerDidFinish:(SFSafariViewController *)controller {
//   //Done button pressed
// }
// 
// - (BOOL)application:(UIApplication *)app (openURL:NSURL *)url (options:NSDictionary<NSString *, id> *)options {
//   NSString *sourceApplication = [options objectForKey:@"UIApplicationOpenURLOptionsSourceApplicationKey"];
//   NSString *urlScheme = [url scheme];
//   NSString *urlQuery = [url query];
// 
//   if ([urlScheme isEqualToString:@"freedomofkeima"] && [sourceApplication isEqualToString:@"com.apple.SafariViewService"]) {
// 
//     //TODO check for success query param
// 
//     NSLog(@"Value: %@", urlQuery);
//     NSDictionary *data = [NSDictionary dictionaryWithObject:urlQuery forKey:@"key"];
// 
//     [NSNotificationCenter defaultCenter] postNotificationName:@"SafariCallback" object:self userInfo:data];
// 
//     return YES;
//   }
// 
//   return NO;
// }

// - (void)safariCallback:(NSNotification *)notification {
//   [IOSAppDelegate GetDelegate].IOSController dismissViewControllerAnimated:NO completion:nil];
// }

// @end
// #endif
