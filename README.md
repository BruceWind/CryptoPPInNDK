## CryptoPPWithNDK
[中文](https://github.com/BruceWind/CryptoPPInNDK/blob/master/README_zh.md)

## Background
Although encrypting algorithms exist in Java, you cannot conceal your encryption algorithm due to imports.

## Approach
This repository provides a method for hiding your algorithms: C++ encoding. Therefore, you should not worry about the exposure of your algorithms. It uses Crypto++ 5.6.2 to fulfil the hidden algorithm requirements.


## Build & Test
```
sh ./build_and_push.sh
adb shell 
>$: cd /data/local/ 
>$: ./main

// looking for logs.  
```
In this shell, I try to connect an android emulator. For it running successfully, you must keep you have a emulator. 

## In addition
This repo was written so early that it could go wrong in case of building with a new version of NDK.
You may need to use NDK 13/14/16.


-------
## Thanks

[crypto++ for android - Official Page](https://www.cryptopp.com/wiki/Android_(Command_Line)#setenv-android.sh)

[https://github.com/weidai11/cryptopp](https://github.com/weidai11/cryptopp)
