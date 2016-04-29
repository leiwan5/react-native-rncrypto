package cn.jedisto.rncrypto;

import com.facebook.react.bridge.*;
import java.util.ArrayList;

public class RNCryptoEcc extends ReactContextBaseJavaModule {

  public RNCryptoEcc(ReactApplicationContext reactContext) {
    super(reactContext);
  }

  @Override
  public String getName() {
    return "RNCryptoEcc";
  }

  @ReactMethod
  public void generateKeys(Callback callback) {
    WritableArray privateKey = Arguments.createArray();
    WritableArray publicKey = Arguments.createArray();

    byte[][] keys = RNCryptoJni.eccGenerateKeys();
    for(byte b : keys[0]) privateKey.pushInt(b & 0xff);
    for(byte b : keys[1]) publicKey.pushInt(b & 0xff);

    WritableMap ret = Arguments.createMap();
    ret.putArray("privateKey", privateKey);
    ret.putArray("publicKey", publicKey);
    callback.invoke(null, ret);
  }

  @ReactMethod
  public void encrypt(ReadableArray plain, ReadableArray publicKey, Callback callback) {
    byte[] plainBytes = new byte[plain.size()];
    for(int i = 0; i < plain.size(); ++i) plainBytes[i] = (byte)(plain.getInt(i) & 0xff);
    byte[] publicKeyBytes = new byte[publicKey.size()];
    for(int i = 0; i < publicKey.size(); ++i) publicKeyBytes[i] = (byte)(publicKey.getInt(i) & 0xff);

    byte[] cipherBytes = RNCryptoJni.eccEncrypt(plainBytes, publicKeyBytes);
    WritableArray cipher = Arguments.createArray();
    for(byte b : cipherBytes) cipher.pushInt(b & 0xff);
    callback.invoke(null, cipher);
  }

  @ReactMethod
  public void decrypt(ReadableArray cipher, ReadableArray privateKey, Callback callback) {
    byte[] cipherBytes = new byte[cipher.size()];
    for(int i = 0; i < cipher.size(); ++i) cipherBytes[i] = (byte)(cipher.getInt(i) & 0xff);
    byte[] privateKeyBytes = new byte[privateKey.size()];
    for(int i = 0; i < privateKey.size(); ++i) privateKeyBytes[i] = (byte)(privateKey.getInt(i) & 0xff);

    byte[] plainBytes = RNCryptoJni.eccDecrypt(cipherBytes, privateKeyBytes);
    WritableArray plain = Arguments.createArray();
    for(byte b : plainBytes) plain.pushInt(b & 0xff);
    callback.invoke(null, plain);
  }

}
