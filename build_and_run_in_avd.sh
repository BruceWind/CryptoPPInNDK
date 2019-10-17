#!/bin/bash

ndk-build clean > /dev/null # dont show any logs.
ndk-build NDK_DEBUG=1 > /dev/null

adb push ./libs/armeabi/main /data/local/ > /dev/null
# next to execute 'main' in an avd, pls startup an arm avd. 
adb shell "
cd /data/local/
./main
"
printf "\033[1;32m:) \033[0m\n"
