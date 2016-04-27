package cn.jedisto.rncrypto;

import com.facebook.react.bridge.*;

public class RNCrypto extends ReactContextBaseJavaModule {

  public RNCrypto(ReactApplicationContext reactContext) {
    super(reactContext);
  }

  @Override
  public String getName() {
    return "RNCrypto";
  }

  @ReactMethod
  public void randomBytes(int size, Callback callback) {
    byte[] bytes = RNCryptoJni.randomBytes(size);
    WritableArray array = Arguments.createArray();
    for(byte b : bytes) array.pushInt(b & 0xff);
    callback.invoke(null, array);
  }
}
