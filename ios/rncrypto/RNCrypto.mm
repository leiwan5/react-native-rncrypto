//
//  RNCrypto.m
//  rncrypto
//
//  Created by Daniel King on 16/4/24.
//  Copyright © 2016年 Daniel King. All rights reserved.
//

#import "RNCrypto.h"
#import <cryptopp/osrng.h>

@implementation RNCrypto
RCT_EXPORT_MODULE();

RCT_EXPORT_METHOD(randomBytes:(NSInteger)size callback:(RCTResponseSenderBlock)callback)
{
    CryptoPP::SecByteBlock bytes(size);
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock(bytes, size);
    
    NSMutableArray* arr = [[NSMutableArray alloc] initWithCapacity:size];
    for(size_t i = 0; i < size; ++i) {
        NSNumber *byte = [NSNumber numberWithUnsignedChar:*(bytes.BytePtr() + i)];
        [arr addObject: byte];
    }
    callback(@[[NSNull null], arr]);
}

@end
