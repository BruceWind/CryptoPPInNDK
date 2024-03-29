## CryptoPPWithNDK

### Background
当你使用java调用加密算法，无论怎么混淆，你都没法隐藏的import。`java imports`暴露了你的算法，而该repo的目的是用C++去加密，正好解决了这些问题。

### Approach
基于Crypto++ 5.6.2,封装一堆的调用。这里并没有直接给出JNI封包的例子，但是我想这已经足够你根据我的代码去自行封装。


## 编译&测试
```
sh ./build_and_push.sh
adb shell
>$: cd /data/local/
>$: ./main

// looking for logs.
```
在这个 shell 中，我尝试连接一个 android 模拟器。 为了让它成功运行，你必须保持你有一个模拟器。

## 更多
该repo编译较早，新版的NDK我可能编译不过。请尝试13或16的NDK版本。

目前引用的`.a`文件虽然很大很大，git clone 时间会很长，必要时请走代理clone。另外，拉完代码请检查.a文件大小是否异常，如果不存在请执行`git lfs pull`。

另外,`.a`文件虽大，编译后的动态库(so)文件依旧会很小，so dont worry!


-------
## 鸣谢

[crypto++ for android官网](https://www.cryptopp.com/wiki/Android_(Command_Line)#setenv-android.sh)

[https://github.com/weidai11/cryptopp](https://github.com/weidai11/cryptopp)
