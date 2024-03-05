#pragma once

#if PLATFORM_IOS
#import <Foundation/Foundation.h>
#import <SafariServices/SafariServices.h>

@interface IOSOAuthWebview : UIViewController <SFSafariViewControllerDelegate>
+ (void)loadBrowserWithUrl;
@end
#endif