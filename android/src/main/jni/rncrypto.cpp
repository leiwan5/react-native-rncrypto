#include "rncrypto.h"
#include <cryptopp/osrng.h>
#include <cryptopp/oids.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/rsa.h>
#include <string>

JNIEXPORT jbyteArray JNICALL Java_cn_jedisto_rncrypto_RNCryptoJni_randomBytes
  (JNIEnv *env, jclass obj, jint size)
{
    CryptoPP::SecByteBlock bytes(size);
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock(bytes, size);

    jbyte* buffer = new jbyte[size];

    for(size_t i = 0; i < bytes.SizeInBytes(); ++i) {
        buffer[i] = *(bytes.BytePtr() + i);
    }

    jbyteArray array = env->NewByteArray(size);
    env->SetByteArrayRegion(array, 0, size, buffer);
    delete[] buffer;
    return array;
}

JNIEXPORT jobjectArray JNICALL Java_cn_jedisto_rncrypto_RNCryptoJni_eccGenerateKeys
  (JNIEnv *env, jclass obj)
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

    jbyte* bytes;
    size_t size;

    size = bq1.CurrentSize();
    jbyteArray array1 = env->NewByteArray(size);
    bytes = new jbyte[size];
    bq1.Get((byte*)bytes, size);
    env->SetByteArrayRegion(array1, 0, size, bytes);
    delete[] bytes;

    size = bq2.CurrentSize();
    jbyteArray array2 = env->NewByteArray(size);
    bytes = new jbyte[size];
    bq2.Get((byte*)bytes, size);
    env->SetByteArrayRegion(array2, 0, size, bytes);
    delete[] bytes;

    jclass byteArrayClass = (env)->FindClass("[B");
    jobjectArray array = env->NewObjectArray(2, byteArrayClass, NULL);
    env->SetObjectArrayElement(array, 0, array1);
    env->SetObjectArrayElement(array, 1, array2);

    return array;
}

JNIEXPORT jbyteArray JNICALL Java_cn_jedisto_rncrypto_RNCryptoJni_eccEncrypt
  (JNIEnv *env, jclass obj, jbyteArray plain, jbyteArray publicKey)
{
    CryptoPP::AutoSeededRandomPool rng;

    const jbyte* plainBytes = env->GetByteArrayElements(plain, 0);

    CryptoPP::ByteQueue publicKeyBq;
    size_t size = env->GetArrayLength(publicKey);
    const jbyte* bytes = env->GetByteArrayElements(publicKey, 0);
    publicKeyBq.Put((byte*)bytes, size);

    CryptoPP::ECIES<CryptoPP::ECP>::Encryptor encryptor;
    encryptor.AccessPublicKey().Load(publicKeyBq);

    std::string s;
    CryptoPP::StringSource ss((byte*)plainBytes, env->GetArrayLength(plain), true, new CryptoPP::PK_EncryptorFilter(rng, encryptor, new CryptoPP::StringSink(s)));

    jbyteArray array = env->NewByteArray(s.length());
    env->SetByteArrayRegion(array, 0, s.length(), (jbyte*)s.c_str());

    return array;
}

JNIEXPORT jbyteArray JNICALL Java_cn_jedisto_rncrypto_RNCryptoJni_eccDecrypt
  (JNIEnv *env, jclass obj, jbyteArray cipher, jbyteArray privateKey)
{
    CryptoPP::AutoSeededRandomPool rng;

    const jbyte* cipherBytes = env->GetByteArrayElements(cipher, 0);

    CryptoPP::ByteQueue privateKeyBq;
    size_t size = env->GetArrayLength(privateKey);
    const jbyte* bytes = env->GetByteArrayElements(privateKey, 0);
    privateKeyBq.Put((byte*)bytes, size);

    CryptoPP::ECIES<CryptoPP::ECP>::Decryptor decryptor;
    decryptor.AccessPrivateKey().Load(privateKeyBq);

    std::string s;
    CryptoPP::StringSource ss((byte*)cipherBytes, env->GetArrayLength(cipher), true, new CryptoPP::PK_DecryptorFilter(rng, decryptor, new CryptoPP::StringSink(s)));

    jbyteArray array = env->NewByteArray(s.length());
    env->SetByteArrayRegion(array, 0, s.length(), (jbyte*)s.c_str());

    return array;
}
