#!/bin/bash

ndk-build clean > /dev/null # dont show any logs.
ndk-build NDK_DEBUG=1 > /dev/null
fileurl="./libs/armeabi/main"
if [ ! -f "$fileurl" ]
then
	   echo "$0: File '${fileurl}' not found."
	   exit 1
fi
printf "\033[1;32m:)  built suc. \033[0m\n"
echo " "
sleep 2
echo "find avd...."
echo " "
sleep 3
adb push ${fileurl} /data/local/ > /dev/null
# next to execute 'main' in an avd, pls startup an arm avd.
adb shell "
cd /data/local/
./main
"
printf "\033[1;32m:) \033[0m\n"
