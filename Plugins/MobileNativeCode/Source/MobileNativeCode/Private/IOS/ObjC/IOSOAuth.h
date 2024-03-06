#pragma once

#if PLATFORM_IOS
#import <Foundation/Foundation.h>
#import <SafariServices/SafariServices.h>

@interface IOSOAuth : UIViewController <SFSafariViewControllerDelegate>
+ (NSString *)url;
+ (void)loadBrowserWithUrl: (NSString *)providerUrl;
+ (void)loadBrowserURLInIOSThread;
@end
#endif
