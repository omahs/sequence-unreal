#pragma once

#if PLATFORM_IOS
#import <Foundation/Foundation.h>
#import <SafariServices/SafariServices.h>

@interface IOSOAuth : UIViewController <SFSafariViewControllerDelegate>
+ (void)loadBrowserWithUrl;
@end
#endif
