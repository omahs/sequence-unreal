#import "IOSOAuth.h"

#if PLATFORM_IOS
#include "IOSAppDelegate.h"
#import <Foundation/Foundation.h>
#endif

static NSString *url = @"https://www.google.com";

@implementation IOSOAuth

+ (NSString *)url {return url;}

+ (IOSOAuth*)GetDelegate {
    static IOSOAuth *Singleton = [[IOSOAuth alloc] init];
    return Singleton;
}

- (ASPresentationAnchor)presentationAnchorForWebAuthenticationSession: (ASWebAuthenticationSession *)session {
    NSLog(@"IN INSTANCE PRESENTATION ANCHOR FOR WEB AUTH SESSION");
    return UIApplication.sharedApplication.keyWindow;
}

+ (ASPresentationAnchor)presentationAnchorForWebAuthenticationSession: (ASWebAuthenticationSession *)session {
    NSLog(@"IN STATIC PRESENTATION ANCHOR FOR WEB AUTH SESSION");
    IOSOAuth *singleton = [self GetDelegate];
    return [singleton presentationAnchorForWebAuthenticationSession: session];
}

+ (void)loadBrowserWithUrl: (NSString *)providerUrl {
    NSLog(@"IN LOAD BROWSER WITH URL");
    url = providerUrl;
    [self performSelectorOnMainThread:@selector(loadBrowserURLInIOSThread) withObject:nil waitUntilDone:YES];
}

+ (void)loadBrowserURLInIOSThread {
    NSLog(@"IN LOAD BROWSER URL IN IOS THREAD");
    NSURL *_url = [NSURL URLWithString:[IOSOAuth url]];
    NSLog(@"_url: %@", _url);
    NSString *redirectURlScheme = @"powered-by-sequence";
    ASWebAuthenticationSession *authSessionAS = [[ASWebAuthenticationSession alloc]initWithURL:_url callbackURLScheme:redirectURlScheme completionHandler:^(NSURL * _Nullable callbackURL, NSError * _Nullable error) {
        NSLog(@"IN BROWSER CALLBACK");
        NSLog(@"CALLBACK URL: %@", callbackURL);
        if(callbackURL)
        {
            NSLog(@"CALLBACK URL EXISTS: %@", callbackURL.absoluteString);
//            resultStream(callbackURL.absoluteString);
        }else
        {
            NSLog(@"CALLBACK URL DOES NOT EXIST");
//            resultStream(@"");
        }
        NSLog(@"CALLBACK URL IS NOW NULL");
//        resultStream = NULL;
    }];
    
//    if (@available(iOS 13, *)) {
//        NSLog(@"AVAILABLE FOR IOS 13");
    NSLog(@"ABOUT TO PRESENT");
        authSessionAS.presentationContextProvider = (id) self;
//    }
    
    NSLog(@"STARTING");
    [authSessionAS start];
}

@end
