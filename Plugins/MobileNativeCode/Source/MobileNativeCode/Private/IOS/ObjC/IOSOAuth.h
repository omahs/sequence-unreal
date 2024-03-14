#pragma once

#if PLATFORM_IOS
#import <Foundation/Foundation.h>
#import <AuthenticationServices/AuthenticationServices.h>

@interface IOSOAuth : UIViewController <ASWebAuthenticationPresentationContextProviding>
+ (NSString *)url;
+ (IOSOAuth*)GetDelegate;
- (ASPresentationAnchor)presentationAnchorForWebAuthenticationSession: (ASWebAuthenticationSession *)session;
+ (ASPresentationAnchor)presentationAnchorForWebAuthenticationSession: (ASWebAuthenticationSession *)session;
@end
#endif
