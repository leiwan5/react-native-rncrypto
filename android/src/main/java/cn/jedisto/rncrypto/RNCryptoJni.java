package cn.jedisto.rncrypto;

import java.util.HashMap;

public class RNCryptoJni {
  public native static byte[] randomBytes(int size);
  public native static byte[][] eccGenerateKeys();
  public native static byte[] eccEncrypt(byte[] plain, byte[] publicKey);
  public native static byte[] eccDecrypt(byte[] cipher, byte[] privateKey);

  static {
    System.loadLibrary("rncrypto");
  }
}
