#!/bin/bash

cd /home/webrtc/webrtc.googlecode.com/trunk
source ./build/android/envsetup.sh
export GYP_DEFINES="$GYP_DEFINES OS=android" 
export JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64/ 
export PATH=$PATH:/home/webrtc/depot_tools

ninja -C out/Debug
ninja -C out/Release