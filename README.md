## CryptoPPWithNDK
[中文](https://github.com/BruceWind/CryptoPPInNDK/blob/master/README_zh.md)
### Background
Although the encrypting algorithm is in Java, you still can not hide your algorithm about encrypting. 


### Approach
To hide your algorithm, this repo provides an approach: encrypting in C++.
So you don't need to care about decomposing.
It bases on Crypto++ 5.6.2 to meet the algorithm code hidden.


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

[crypto++ for android Official](https://www.cryptopp.com/wiki/Android_(Command_Line)#setenv-android.sh)

[https://github.com/weidai11/cryptopp](https://github.com/weidai11/cryptopp)
