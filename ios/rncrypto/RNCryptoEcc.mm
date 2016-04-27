//
//  RNCryptoEcc.m
//  HiReactNative
//
//  Created by Daniel King on 16/4/19.
//  Copyright © 2016年 Facebook. All rights reserved.
//

#import "RNCryptoEcc.h"

@implementation RNCryptoEcc
RCT_EXPORT_MODULE();

RCT_EXPORT_METHOD(generateKeys:(RCTResponseSenderBlock)callback)
{
  CryptoPP::AutoSeededRandomPool rng;
  CryptoPP::ECIES<CryptoPP::ECP>::Decryptor decryptor(rng, CryptoPP::ASN1::secp521r1());
  CryptoPP::ECIES<CryptoPP::ECP>::Encryptor encryptor(decryptor);
  
  const CryptoPP::PrivateKey& privateKey = decryptor.GetPrivateKey();
  const CryptoPP::PublicKey& publicKey = encryptor.GetPublicKey();
  
  CryptoPP::ByteQueue bq1;
  privateKey.Save(bq1);
  bq1.MessageEnd();
  
  CryptoPP::ByteQueue bq2;
  publicKey.Save(bq2);
  bq2.MessageEnd();
  
  callback(@[[NSNull null], [NSDictionary dictionaryWithObjectsAndKeys:[self byteQueueToByteArray:bq1], @"privateKey", [self byteQueueToByteArray:bq2], @"publicKey", nil]]);
}

RCT_EXPORT_METHOD(decrypt:(NSArray*)cipherBytes privateKey:(NSArray*)privateKey callback:(RCTResponseSenderBlock)callback)
{
  CryptoPP::AutoSeededRandomPool rng;
  CryptoPP::ByteQueue cipherBq([self byteArrayToByteQueue:cipherBytes]);

  CryptoPP::ByteQueue privateKeyBq = [self byteArrayToByteQueue:privateKey];
  CryptoPP::ECIES<CryptoPP::ECP>::Decryptor decryptor;
  decryptor.AccessPrivateKey().Load(privateKeyBq);
  
  std::string s;
  
  byte* bytes = new byte[cipherBq.CurrentSize()];
  cipherBq.Get(bytes, cipherBq.CurrentSize());
  
  CryptoPP::StringSource ss(bytes, cipherBytes.count, true, new CryptoPP::PK_DecryptorFilter(rng, decryptor, new CryptoPP::StringSink(s)));

  callback(@[[NSNull null], [self bytesToByteArray:(byte*)s.c_str() size:s.length()]]);
  delete[] bytes;
}

RCT_EXPORT_METHOD(encrypt:(NSArray*)plainBytes publicKey:(NSArray*)publicKey callback:(RCTResponseSenderBlock)callback)
{
  CryptoPP::AutoSeededRandomPool rng;
  CryptoPP::ByteQueue plainBq([self byteArrayToByteQueue:plainBytes]);
  CryptoPP::ByteQueue publicKeyBq([self byteArrayToByteQueue:publicKey]);
  CryptoPP::ECIES<CryptoPP::ECP>::Encryptor encryptor;
  encryptor.AccessPublicKey().Load(publicKeyBq);
  CryptoPP::ByteQueue cipher;
  
  std::string s;

  byte* bytes = new byte[plainBq.CurrentSize()];
  plainBq.Get(bytes, plainBq.CurrentSize());
  
  CryptoPP::StringSource ss(bytes, plainBytes.count, true, new CryptoPP::PK_EncryptorFilter(rng, encryptor, new CryptoPP::StringSink(s)));
  
  callback(@[[NSNull null], [self bytesToByteArray:(byte*)s.c_str() size:s.length()]]);
  delete[] bytes;
}

- (NSArray*)byteQueueToByteArray:(CryptoPP::ByteQueue)queue
{
  size_t size = queue.CurrentSize();
  
  NSMutableArray* arr = [[NSMutableArray alloc] initWithCapacity:size];
  byte* bytes = new byte[size];
  queue.Get(bytes, size);
  for(size_t i = 0; i < size; ++i) {
    NSNumber *byte = [NSNumber numberWithUnsignedChar:bytes[i]];
    [arr addObject: byte];
  }
  delete[] bytes;
  return arr;
}

- (NSArray*)bytesToByteArray:(byte*)bytes size:(size_t)size
{
  NSMutableArray* arr = [[NSMutableArray alloc] initWithCapacity:size];
  for(size_t i = 0; i < size; ++i) {
    NSNumber *byte = [NSNumber numberWithUnsignedChar:bytes[i]];
    [arr addObject: byte];
  }
  return arr;
}

- (CryptoPP::ByteQueue)byteArrayToByteQueue:(NSArray*)array
{
  CryptoPP::ByteQueue bq;
  size_t size = array.count;
  byte* bytes = new byte[size];
  for(size_t i = 0; i < size; ++i) {
    NSNumber *byte = array[i];
    bytes[i] = [byte unsignedCharValue];
  }
  bq.Put(bytes, size);
  delete[] bytes;
  return bq;
}

@end

