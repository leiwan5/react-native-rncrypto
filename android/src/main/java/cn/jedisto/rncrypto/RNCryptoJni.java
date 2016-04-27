package cn.jedisto.rncrypto;

public class RNCryptoJni {
  public native static byte[] randomBytes(int size);
  public native static byte[] eccGenerateKeys();

  static {
    System.loadLibrary("rncrypto");
  }
}
