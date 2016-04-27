import { Buffer } from 'buffer';
import ReactNative, {
  NativeModules
} from 'react-native';

var ecc = {
  generateKeys: function() {
    return new Promise(function(resolve, reject) {
      NativeModules.RNCryptoEcc.generateKeys(function(error, keys) {
        if(error) {
          reject(error);
        } else {
          resolve({
            privateKey: new Buffer(keys.privateKey),
            publicKey: new Buffer(keys.publicKey)
          });
        }
      });
    });
  },
  encrypt: function(plain, publicKey) {
    return new Promise(function(resolve, reject) {
      NativeModules.RNCryptoEcc.encrypt(plain.toJSON().data, publicKey.toJSON().data, function(error, cipher) {
        if(error) {
          reject(error);
        } else {
          resolve(new Buffer(cipher));
        }
      });
    });
  },
  decrypt: function(cipher, privateKey) {
    return new Promise(function(resolve, reject) {
      NativeModules.RNCryptoEcc.decrypt(cipher.toJSON().data, privateKey.toJSON().data, function(error, plain) {
        if(error) {
          reject(error);
        } else {
          resolve(new Buffer(plain));
        }
      });
    });
  }
};

var rncrypto = {
  ecc,
  randomBytes: function(size = 32) {
    return new Promise(function(resolve, reject) {
      NativeModules.RNCrypto.randomBytes(size, function(error, bytes) {
        if(error) {
          reject(error);
        } else {
          resolve(new Buffer(bytes));
        }
      });
    });
  }
};

export default rncrypto;
