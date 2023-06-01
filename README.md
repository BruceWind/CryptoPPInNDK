## CryptoPPWithNDK
[中文](https://github.com/BruceWind/CryptoPPInNDK/blob/master/README_zh.md)

## Background
Although encrypting algorithms exist in Java, you cannot conceal your encryption algorithm due to `java imports`.

## Approach
This repository provides a method for hiding your algorithms: C++ encoding. Therefore, you should not worry about the exposure of your algorithms. It uses Crypto++ 5.6.2 to fulfil the hidden algorithm requirements.


## Build & Test
```
git clone git@github.com:BruceWind/CryptoPPInNDK.git
cd CryptoPPInNDK && git lfs pull
sh ./build_and_push.sh
adb shell
>$: cd /data/local/
>$: ./main

// looking for logs.
```
Before running this shell, you must connect an android emulator in advance. 

## In addition
The repo was written so early that it could go wrong in case of building with a new version of NDK.
You may need to build with NDK 13/14/16.

Be careful with **git clone**, I've used `git lfs` to store *.a files.

-------
## Thanks

[Crypto++ for android - Official Page](https://www.cryptopp.com/wiki/Android_(Command_Line)#setenv-android.sh)

[weidai11/cryptopp](https://github.com/weidai11/cryptopp)
