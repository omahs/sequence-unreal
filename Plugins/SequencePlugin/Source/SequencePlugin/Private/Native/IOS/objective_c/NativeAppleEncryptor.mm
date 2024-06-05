﻿// Copyright 2024 Horizon Blockchain Games Inc. All rights reserved.

#import "NativeAppleEncryptor.h"
#import <Foundation/Foundation.h>
#import <Security/Security.h>

static SecKeyRef privateKey;
static SecKeyRef publicKey;
static NSString * ErrorCapture = @"";

@implementation NativeAppleEncryptor

- (BOOL) GenerateKeys 
{
    NSData* tag = [@"com.Sequence.keys.Main" dataUsingEncoding:NSUTF8StringEncoding];
    
    NSDictionary* attributes =
        @{ (id)kSecAttrKeyType:               (id)kSecAttrKeyTypeRSA,
           (id)kSecAttrKeySizeInBits:         @2048,
           (id)kSecPrivateKeyAttrs:
               @{ (id)kSecAttrIsPermanent:    @YES,
                  (id)kSecAttrApplicationTag: tag,
                  },   
         };
    CFErrorRef error = NULL;
    privateKey = SecKeyCreateRandomKey((__bridge CFDictionaryRef)attributes,&error);
    
    
    if (!privateKey) {
        NSError *err = CFBridgingRelease(error);  // ARC takes ownership
        printf("Failed to generate private key");
        return false;
    }
    publicKey = SecKeyCopyPublicKey(privateKey);
    printf("successfully generated private key")
    return true;
}

- (BOOL) LoadKeys 
{
    NSDictionary *query = @ {
        (__bridge id)kSecClass: (__bridge id)kSecClassKey,
        (__bridge id)kSecAttrApplicationTag: @"com.Sequence.keys.Main",
        (__bridge id)kSecReturnRef: @YES,
    };
    
    SecKeyRef privateKeyRef = NULL;
    OSStatus status = SecItemCopyMatching((__bridge CFDictionaryRef)query, (CFTypeRef *)&privateKey);
    if (status == errSecSuccess) 
    {
        ErrorCapture = @"Private key retrieved successfully";
        printf("%s", [ErrorCapture UTF8String]);
        publicKey = SecKeyCopyPublicKey(privateKey);
        return true;
    }
    else if (status == errSecItemNotFound)
    {
        ErrorCapture = @"Private key not found. Add it if needed.";
        printf("%s", [ErrorCapture UTF8String]);
        return [self GenerateKeys];
    }
    else
    {
        //NSLog(@"Keychain error: %ld", (long)status);
        ErrorCapture = @"Keychain error";
        printf("%s", [ErrorCapture UTF8String]);
        return false;
    }
}

- (void) Clean
{
    if (publicKey)  { CFRelease(publicKey);  }
    if (privateKey) { CFRelease(privateKey); }
}

- (char *)Encrypt:(NSString *)str
{
    char *EncryptedChars = nullptr;
    if ([self LoadKeys])
    {
        CFDataRef plainText = (__bridge CFDataRef)[str dataUsingEncoding:NSUTF8StringEncoding];
        CFErrorRef error = NULL;
        
        CFDataRef EncryptedData = SecKeyCreateEncryptedData(
        publicKey,
        kSecKeyAlgorithmRSAEncryptionPKCS1,
        plainText,
        &error);
        
        NSData * PreProcEncryptedData = (__bridge NSData *)EncryptedData;
        NSString * EncryptedDataString = [[NSString alloc] initWithData:PreProcEncryptedData encoding:NSUTF8StringEncoding];
        printf("%s", [EncryptedDataString UTF8String]);
        EncryptedChars = [self ConvertNSStringToChars:EncryptedDataString];
    }
    else
    {//Failure state
        printf("Failed to load encryption key");
        EncryptedChars = [self ConvertNSStringToChars:ErrorCapture];
    }
    //[self Clean];
    return EncryptedChars;
}

- (char *)Decrypt:(NSString *)str
{
    char *DecryptedChars = nullptr;
    if ([self LoadKeys])
    {
            CFDataRef plainText = (__bridge CFDataRef)[str dataUsingEncoding:NSUTF8StringEncoding];
            CFErrorRef error = NULL;
            
            CFDataRef DecryptedData = SecKeyCreateDecryptedData(
            privateKey,
            kSecKeyAlgorithmRSAEncryptionPKCS1,
            plainText,
            &error);
            
            NSData * PreProcDecryptedData = (__bridge NSData *)DecryptedData;
            NSString * DecryptedDataString = [[NSString alloc] initWithData:PreProcDecryptedData encoding:NSUTF8StringEncoding];
            printf("DecryptedData: %s", [DecryptedDataString UTF8String]);
            DecryptedChars = [self ConvertNSStringToChars:DecryptedDataString];
    }
    else
    {//Failure state
        printf("Failed to load decryption key");
        NSString * FailureString = @"Failed to load decryption key";
        DecryptedChars = [self ConvertNSStringToChars:FailureString];
    }
    //[self Clean];
    return DecryptedChars;
}

- (char *)ConvertNSStringToChars:(NSString *)str {
    const char *strChars = [str UTF8String];
    return (char*)strChars;
}
@end