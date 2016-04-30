# react-native-rncrypto
Yet another crypto module for react native. This module is not a polyfill of node-crypto. It's for people who want to use some native cryptographic functions in react native.

It's based on [Crypto++](https://www.cryptopp.com), a free C++ class library of cryptographic schemes.

Codes are in very initial state, and contributions are welcome.


## Features

* Random bytes generating
* ECC Keypair generation (secp521r1)
* ECC Decrypt/Encrypt

## Usage

### install

```bash
npm i -S react-native-rncrypto
rnpm link react-native-rncrypto
```

### import

```javascript
import rncrypto from 'react-native-rncrypto';
```

### rncrypto.randomBytes

```
Promise<Buffer> rncrypto.randomBytes([size:Integer = 32])
```

### rncrypto.ecc.generateKeys

```
Promise<{privateKey: Buffer, publicKey: Buffer}> rncrypto.ecc.generateKeys()
```

### rncrypto.ecc.encryt

```
Promise<Buffer> rncrypto.ecc.encryt(plain:Buffer, publicKey:Buffer)
```

### rncrypto.ecc.decrypt

```
Promise<Buffer> rncrypto.ecc.decryt(cipher:Buffer, privateKey:Buffer)
```

### Buffer

APIs are same with those of [node's Buffer](https://nodejs.org/api/buffer.html). Details can be found at https://github.com/feross/buffer.

## Examples

```javascript
rncrypto.randomBytes(32).then(function(random) {
  // console.log(random.toString('hex'));
  // console.log(random.toString('base64'));
});
var plain = new Buffer('Hello, world!', 'utf-8');
rncrypto.ecc.generateKeys().then(function(keys) {
  rncrypto.ecc.encrypt(plain, keys.publicKey).then(function(cipher) {
    // console.log(cipher.toString('hex'));
    rncrypto.ecc.decrypt(cipher, keys.privateKey).then(function(decrypted) {
      // console.log(decrypted.toString('hex'));
    });
  });
});
```

or

```javascript
const random = yield rncrypto.randomBytes(32);
const plain = new Buffer('Hello, world!', 'utf-8');
const keys = yield rncrypto.ecc.generateKeys();
const cipher = yield rncrypto.ecc.encrypt(plain, keys.publicKey);
const decrypted = yield rncrypto.ecc.decrypt(cipher, keys.privateKey);
```

## Todos

* Error handling
* Supporting more ECC curve types
* ECDSA and ECDH functions
* RSA related functions
* ...

## Demo

There is a demo project can be fount at https://github.com/danielking/react-native-rncrypto-demo, and here are some screenshots below.

iOS:

<img src="https://raw.githubusercontent.com/danielking/react-native-rncrypto-demo/master/screenshots/ios.png" height="700"/>

Android:

<img src="https://raw.githubusercontent.com/danielking/react-native-rncrypto-demo/master/screenshots/android.png" height="700"/>
