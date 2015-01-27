export QT_X11_NO_MITSHM=1
export HOME=/home/webrtc
export JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64
export PATH=$PATH:/home/webrtc/depot_tools
source /home/webrtc/webrtc.googlecode.com/src/build/android/envsetup.sh
export GYP_DEFINES="$GYP_DEFINES OS=android"