## CryptoPPWithNDK
基于Crypto++ 5.6.2,封装一堆的Jni调用，本身java也有这些加密算法，纯粹做一些特殊的需求，满足一些需要在jni里做加密的特殊用户。


目前引用的`.a`文件虽然很大很大，git clone 时间会很长，必要时请走代理clone。

另外,`.a`文件虽大，编译后的动态库(so)文件依旧会很小，so dont worry!

## 编译&测试
```
sh ./build_and_push.sh
adb shell 
>$: cd /data/local/ 
>$: ./main

// looking for logs.  


```



-------
## 鸣谢

[crypto++ for android官网](https://www.cryptopp.com/wiki/Android_(Command_Line)#setenv-android.sh)

[https://github.com/weidai11/cryptopp](https://github.com/weidai11/cryptopp)



