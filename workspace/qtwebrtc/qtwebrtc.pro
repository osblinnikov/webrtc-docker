
TEMPLATE = app
TARGET = qtwebrtc
DEPENDPATH += .

QT += widgets webkit opengl webkitwidgets

DEFINES += WEBRTC_POSIX 
DEFINES += LINUX
DEFINES += POSIX

CONFIG(debug,debug|release) {
	DEFINES += _DEBUG 
	DEFINES += _GLIBCXX_DEBUG=1
}

# Either set this to the correct path or run qmake like this:
#   qmake WEBRTCTRUNK=/path/to/webrtc/trunk
#WEBRTCTRUNK = /path/to/webrtc/trunk/
INCLUDEPATH += .
INCLUDEPATH += $$WEBRTCTRUNK
INCLUDEPATH += $$WEBRTCTRUNK/chromium/src/third_party
INCLUDEPATH += $$WEBRTCTRUNK/third_party
INCLUDEPATH += $$WEBRTCTRUNK/third_party/webrtc
INCLUDEPATH += $$WEBRTCTRUNK/webrtc
INCLUDEPATH += $$WEBRTCTRUNK/net/third_party/nss/ssl
INCLUDEPATH += $$WEBRTCTRUNK/third_party/jsoncpp/overrides/include
INCLUDEPATH += $$WEBRTCTRUNK/third_party/jsoncpp/source/include
INCLUDEPATH += /usr/include/nss 
INCLUDEPATH += /usr/include/nspr

CONFIG(debug,debug|release) {
	WEBRTCBUILD = $$WEBRTCTRUNK/out/Debug
} else {
	WEBRTCBUILD = $$WEBRTCTRUNK/out/Release
}

LIBS += -Wl,--start-group
#++
LIBS += $$WEBRTCBUILD/obj/webrtc/base/librtc_base.a
LIBS += $$WEBRTCBUILD/obj/webrtc/base/librtc_base_approved.a
#LIBS += $$WEBRTCBUILD/obj/webrtc/libwebrtc.a
#LIBS += $$WEBRTCBUILD/obj/webrtc/libwebrtc_common.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/third_party/jsoncpp/libjsoncpp.a
LIBS += $$WEBRTCBUILD/obj/talk/libjingle_peerconnection.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/net/third_party/nss/libcrssl.a
LIBS += $$WEBRTCBUILD/obj/talk/libjingle.a
LIBS += $$WEBRTCBUILD/obj/talk/libjingle_media.a
LIBS += $$WEBRTCBUILD/obj/webrtc/libjingle/xmllite/librtc_xmllite.a
LIBS += $$WEBRTCBUILD/libyuv.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/third_party/libjpeg_turbo/libjpeg_turbo.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/third_party/usrsctp/libusrsctplib.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libvideo_capture_module.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libvideo_capture_module_impl.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libvideo_capture_module_internal_impl.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libwebrtc_utility.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libaudio_coding_module.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libCNG.a
LIBS += $$WEBRTCBUILD/obj/webrtc/common_audio/libcommon_audio.a
LIBS += $$WEBRTCBUILD/obj/webrtc/system_wrappers/source/libsystem_wrappers.a
LIBS += $$WEBRTCBUILD/obj/webrtc/common_audio/libcommon_audio_sse2.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libG711.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libG722.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libiLBC.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libiSAC.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libiSACFix.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libPCM16B.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libneteq.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libwebrtc_opus.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/third_party/opus/libopus.a
#LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libacm2.a
#LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libNetEq4.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libmedia_file.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libwebrtc_video_coding.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libwebrtc_i420.a
LIBS += $$WEBRTCBUILD/obj/webrtc/common_video/libcommon_video.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/video_coding/utility/libvideo_coding_utility.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/video_coding/codecs/vp8/libwebrtc_vp8.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/third_party/libvpx/libvpx.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/third_party/libvpx/libvpx_asm_offsets_vp8.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/third_party/libvpx/libvpx_intrinsics_mmx.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/third_party/libvpx/libvpx_intrinsics_sse2.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/third_party/libvpx/libvpx_intrinsics_ssse3.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/third_party/libvpx/libvpx_intrinsics_sse4_1.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libvideo_render_module.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libvideo_render_module_impl.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libvideo_render_module_internal_impl.a
LIBS += $$WEBRTCBUILD/obj/webrtc/video_engine/libvideo_engine_core.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/librtp_rtcp.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libpaced_sender.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libremote_bitrate_estimator.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/remote_bitrate_estimator/librbe_components.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libbitrate_controller.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libvideo_processing.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libvideo_processing_sse2.a
LIBS += $$WEBRTCBUILD/obj/webrtc/voice_engine/libvoice_engine.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libaudio_conference_mixer.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libaudio_processing.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libaudioproc_debug_proto.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/third_party/protobuf/libprotobuf_lite.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libaudio_processing_sse2.a
LIBS += $$WEBRTCBUILD/obj/webrtc/modules/libaudio_device.a
#LIBS += $$WEBRTCBUILD/obj/talk/libjingle_sound.a
LIBS += $$WEBRTCBUILD/obj/talk/libjingle_p2p.a
LIBS += $$WEBRTCBUILD/obj/chromium/src/third_party/libsrtp/libsrtp.a
LIBS += $$WEBRTCBUILD/obj/webrtc/system_wrappers/source/libfield_trial_default.a
LIBS += -Wl,--end-group
#-lsoftokn3
LIBS += -lnss3 -lsmime3 -lnssutil3 -lplds4 -lplc4 -lnspr4 -lsqlite3 -ldl -lcrypto -lrt -lexpat -lm -lXext -lX11
LIBS += -lXrender -lXcomposite

QMAKE_CXXFLAGS += -fno-rtti

# Input
HEADERS += testvideocapturer.h \
           testwidget.h \
	   widgetstreamer.h
FORMS += testwidget.ui
SOURCES += testvideocapturer.cpp \
           qtmain.cpp \
           testwidget.cpp \
	   widgetstreamer.cpp




