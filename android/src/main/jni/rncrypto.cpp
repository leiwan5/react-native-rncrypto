#include "rncrypto.h"
#include <cryptopp/osrng.h>

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
