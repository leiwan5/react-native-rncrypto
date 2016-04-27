//
//  RNCryptoEcc.h
//  HiReactNative
//
//  Created by Daniel King on 16/4/19.
//  Copyright © 2016年 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCTBridgeModule.h"
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>
#include <cryptopp/eccrypto.h>

@interface RNCryptoEcc : NSObject<RCTBridgeModule>

- (NSArray*)byteQueueToByteArray:(CryptoPP::ByteQueue)queue;
- (NSArray*)bytesToByteArray:(byte*)bytes size:(size_t)size;
- (CryptoPP::ByteQueue)byteArrayToByteQueue:(NSArray*)array;

@end


