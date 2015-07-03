#!/bin/bash

set -x

# Absolute path to this script. /home/user/bin/foo.sh
SCRIPT=$(readlink -f $0)
# Absolute path this script is in. /home/user/bin
SCRIPTPATH=`dirname $SCRIPT`

rm -R $SCRIPTPATH/org
mkdir -p $SCRIPTPATH/org/webrtc

cp -R ~/webrtc.googlecode.com/src/talk/app/webrtc/java/android/org/webrtc/* $SCRIPTPATH/org/webrtc/
cp -R ~/webrtc.googlecode.com/src/talk/app/webrtc/java/src/org/webrtc/* $SCRIPTPATH/org/webrtc/
cp -R ~/webrtc.googlecode.com/src/webrtc/modules/video_render/android/java/src/org/webrtc/videoengine $SCRIPTPATH/org/webrtc/
cp -R ~/webrtc.googlecode.com/src/webrtc/modules/audio_device/android/java/src/org/webrtc/voiceengine $SCRIPTPATH/org/webrtc/
mkdir -p $SCRIPTPATH/armeabi-v7a
cp ~/webrtc.googlecode.com/src/out_android/Release/lib/libjingle_peerconnection_so.so $SCRIPTPATH/armeabi-v7a/
rm -R $SCRIPTPATH/linux
mkdir -p $SCRIPTPATH/linux

cd ~/webrtc.googlecode.com/src
find . -name '*.h' | cpio -pdm $SCRIPTPATH/linux
cd ~/webrtc.googlecode.com/src/out/Release
find . -name '*.a'  | cpio -pdm $SCRIPTPATH/linux/Release
find . -name '*.so' | cpio -pdm $SCRIPTPATH/linux/Release

cd ~/webrtc.googlecode.com/src/out/Debug
find . -name '*.a'  | cpio -pdm $SCRIPTPATH/linux/Debug
find . -name '*.so' | cpio -pdm $SCRIPTPATH/linux/Debug