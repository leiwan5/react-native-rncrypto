package cn.jedisto.rncrypto;

import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Callback;

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
    callback.invoke(null, "PrivateKey", "PublicKey");
  }

  @ReactMethod
  public void encrypt(Callback callback) {
    callback.invoke(null, "encrypted");
  }

  @ReactMethod
  public void decrypt(Callback callback) {
    callback.invoke(null, "decrypted");
  }

}
