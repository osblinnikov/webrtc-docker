webrtcDocker
============

Docker container for [WebRTC](http://www.webrtc.org/reference/getting-started). Runs ubuntu 14.04 trusty

get from docker hub:

    docker pull oleg/webrtc
    docker run -p 6080:6080 -t -i oleg/webrtc

or to build container from dockerfile, type command in current directory:

    git clone https://github.com/osblinnikov/webrtc-docker.git
    cd webrtc-docker
    docker build -t oleg/webrtc .

To start the fresh built container simply type:

    ./run

Lets test the WebRTC build:
    
    sudo apt-get install qt-sdk
    cd ./workspace/qtwebrtc
    qmake-qt4 WEBRTCTRUNK=../linux
    make
    ./qtwebrtc

Last command will start qt application in vnc, it's the right time to test noVNC installation:

Browse http://127.0.0.1:6080/vnc.html and connect to the vnc desktop

Go to the local host and open workspace/qtwebrtc/receiver.html in Chrome
  
    google-chrome --allow-file-access-from-files workspace/qtwebrtc/receiver.html

Connect browser and application by following the instructions in the video http://research.edm.uhasselt.be/~jori/page/index.php?n=Misc.QtWebRTC

If you'd like to configure launch steps of the container, fix a `startcontainer`
script and rebuild the container

Commit:

    docker commit --author="FIXME" --message="FIXME" FIXME_75f05d8f7da3 oleg/webrtc:FIXME
