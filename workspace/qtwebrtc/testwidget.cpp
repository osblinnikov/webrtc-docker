#include "talk/app/webrtc/test/fakeconstraints.h"
#include "talk/app/webrtc/videosourceinterface.h"
#include "talk/media/devices/devicemanager.h"
#include "testvideocapturer.h"
#include "testwidget.h"
#include <QPlainTextEdit>
#include <iostream>
#include <stdio.h>

using namespace std;

class DummySetSessionDescriptionObserver : public webrtc::SetSessionDescriptionObserver 
{
public:
	static DummySetSessionDescriptionObserver* Create() 
	{
        return new rtc::RefCountedObject<DummySetSessionDescriptionObserver>();
	}

	void OnSuccess() 
	{
		cerr << "DummySetSessionDescriptionObserver: onSuccess" << endl;
	}

	void OnFailure(const std::string& error) 
	{
		cerr << "DummySetSessionDescriptionObserver::OnFailure" << endl;
	}
protected:
	DummySetSessionDescriptionObserver() 
	{
	}
	
	~DummySetSessionDescriptionObserver() 
	{
	}
};

TestConnectionObserver::TestConnectionObserver()
{
	cerr << "TestConnectionObserver::TestConnectionObserver" << endl;
}

TestConnectionObserver::~TestConnectionObserver()
{
	cerr << "TestConnectionObserver::~TestConnectionObserver" << endl;
}

void TestConnectionObserver::OnError()
{
	cerr << "TestConnectionObserver::OnError" << endl;
}

void TestConnectionObserver::OnStateChange(webrtc::PeerConnectionObserver::StateType state_changed)
{
	cerr << "TestConnectionObserver::OnStateChange" << endl;
}

void TestConnectionObserver::OnAddStream(webrtc::MediaStreamInterface* stream)
{
	cerr << "TestConnectionObserver::OnAddStream" << endl;
}

void TestConnectionObserver::OnRemoveStream(webrtc::MediaStreamInterface* stream)
{
	cerr << "TestConnectionObserver::OnRemoveStream" << endl;
}

void TestConnectionObserver::OnRenegotiationNeeded() 
{
	cerr << "TestConnectionObserver::OnRenegotiationNeeded" << endl;
}

void TestConnectionObserver::OnIceChange() 
{
	cerr << "TestConnectionObserver::OnIceChange" << endl;
}

void TestConnectionObserver::OnIceCandidate(const webrtc::IceCandidateInterface* candidate)
{
	cerr << "TestConnectionObserver::OnIceCandidate" << endl;
	string iceStr;

	int mlineIdx = candidate->sdp_mline_index();
	string sdpMid = candidate->sdp_mid();
	candidate->ToString(&iceStr);

	size_t len = iceStr.length();
	if (len > 0 && iceStr[len-1] == '\n')
		iceStr = iceStr.substr(0, len-1);
	
	len = iceStr.length();
	if (len > 0 && iceStr[len-1] == '\r')
		iceStr = iceStr.substr(0, len-1);

#define BUFLEN 1024
	char buf[BUFLEN];

	snprintf(buf, BUFLEN, "{\"sdpMLineIndex\":%d,\"sdpMid\":\"%s\",\"candidate\":\"%s\\r\\n\"}", mlineIdx, sdpMid.c_str(), iceStr.c_str());

	emit signalIceCandidate(QString(buf));
}

TestSDObserver::TestSDObserver()
{
	cerr << "TestSDObserver::TestSDObserver" << endl;
}

TestSDObserver::~TestSDObserver()
{
	cerr << "TestSDObserver::~TestSDObserver" << endl;
}

void TestSDObserver::OnSuccess(webrtc::SessionDescriptionInterface* desc)
{
	cerr << "TestSDObserver::OnSuccess" << endl;
	string sdpStr;

	desc->ToString(&sdpStr);
	cerr << sdpStr << endl;

	emit signalSDPText(QString(sdpStr.c_str()));
}

void TestSDObserver::OnFailure(const std::string& error)
{
	cerr << "TestSDObserver::OnFailure" << endl;
}

TestWidget::TestWidget()
{
	m_pCapturer = 0;
	m_pcfIface = 0;

	setupUi(this);

	QObject::connect(m_pStartButton, SIGNAL(clicked()), this, SLOT(onStartClicked()));
	QObject::connect(m_pProcessAnswerButton, SIGNAL(clicked()), this, SLOT(onAnswerClicked()));
	QObject::connect(m_pProcessRemoteICEButton, SIGNAL(clicked()), this, SLOT(onRemoteICEClicked()));
}

TestWidget::~TestWidget()
{
}

void TestWidget::onStartClicked()
{
	if (m_pcfIface != 0)
	{
		cerr << "onStartClicked: already exists" << endl;
		return;
	}

	m_pcfIface = webrtc::CreatePeerConnectionFactory();

	if (!m_pcfIface.get()) // This means that the initialization failed for some reason (get retrieves the pointer)
	{
		m_pcfIface = 0; // Since it's ref counted, this will destroy it
		return;
	}

  	webrtc::PeerConnectionInterface::IceServers servers;
	webrtc::PeerConnectionInterface::IceServer server;
  	webrtc::FakeConstraints constraints;

	constraints.SetAllowDtlsSctpDataChannels();

	server.uri = "stun:stun.l.google.com:19302";
	servers.push_back(server);

	// TODO: this is a memory leak for now
	TestConnectionObserver *pTestConnObserver = new TestConnectionObserver();

	QObject::connect(pTestConnObserver, SIGNAL(signalIceCandidate(const QString &)), this, SLOT(onLocalIceCandidate(const QString &)));

    m_peerConnection = m_pcfIface->CreatePeerConnection(servers, &constraints, NULL, NULL, pTestConnObserver);
  
    rtc::scoped_refptr<webrtc::VideoSourceInterface> videoSource;
	videoSource = m_pcfIface->CreateVideoSource(OpenVideoCaptureDevice(), 0);

    rtc::scoped_refptr<webrtc::VideoTrackInterface> videoTrack;
	videoTrack = m_pcfIface->CreateVideoTrack("testVideoTrack", videoSource);
  	
    rtc::scoped_refptr<webrtc::AudioTrackInterface> audioTrack;
      	audioTrack = m_pcfIface->CreateAudioTrack("testAudioTrack", m_pcfIface->CreateAudioSource(NULL));

    rtc::scoped_refptr<webrtc::MediaStreamInterface> stream;
	stream = m_pcfIface->CreateLocalMediaStream("testStream");

	stream->AddTrack(audioTrack);
  	stream->AddTrack(videoTrack);

  	if (!m_peerConnection->AddStream(stream, 0))
	{
    		cerr << "Adding stream to PeerConnection failed" << endl;
		return;
  	}
	cerr << "Successfully added stream" << endl;

	TestSDObserver *pTestSD = new TestSDObserver();
	
	QObject::connect(pTestSD, SIGNAL(signalSDPText(const QString &)), this, SLOT(onLocalSDPInfo(const QString &)));

	m_peerConnection->CreateOffer(pTestSD, 0);
}

void TestWidget::onAnswerClicked()
{
	cout << "onAnswerClicked" << endl;
	string sdpInfo = m_pAnswerText->toPlainText().toStdString();

	cerr << sdpInfo << endl;
    
    	webrtc::SessionDescriptionInterface* pSessionDescription = webrtc::CreateSessionDescription("answer", sdpInfo);

	m_peerConnection->SetRemoteDescription(DummySetSessionDescriptionObserver::Create(), pSessionDescription);
}

void TestWidget::onRemoteICEClicked()
{
	cout << "onRemoteICEClicked" << endl;
	
	QStringList iceInfo = m_pRemoteICEText->toPlainText().split('\n');

	for (int i = 0 ; i < iceInfo.size() ; i++)
	{
		QString iceLine = iceInfo.at(i);

		//cerr << iceLine.toStdString() << endl;

		QStringList parts = iceLine.split(',');
		QStringList remainingParts;
		for (int j = 0 ; j < parts.size() ; j++)
		{
			QString part = parts.at(j);
			cerr << part.toStdString() << endl;

			QStringList values = part.split('"', QString::SkipEmptyParts);

			if (values.size() > 2)
			{
				remainingParts << values.at(2);
				//cerr << values.at(0).toStdString() << " " << values.at(2).toStdString() << endl;
			}
		}

		if (remainingParts.size() == 3)
		{
			int sdpMLineIndex = atoi(remainingParts.at(0).toLatin1());
			string sdpMid = remainingParts.at(1).toStdString();
			QString candidate = remainingParts.at(2);
			
			candidate.replace(QString("\\r\\n"),QString(""));

			cerr << "ICE: " << sdpMLineIndex << " " << sdpMid << " " << candidate.toStdString() << endl;

            rtc::scoped_ptr<webrtc::IceCandidateInterface> c(webrtc::CreateIceCandidate(sdpMid, sdpMLineIndex, candidate.toStdString()));

			if (!c.get()) 
			{
				cerr << "Can't parse candidate message" << endl;
			}
			else
			{
				if (!m_peerConnection->AddIceCandidate(c.get())) 
				{
					cerr << "Failed to apply the received candidate" << endl;
				}	
			}
		}
	}
}

cricket::VideoCapturer* TestWidget::OpenVideoCaptureDevice() 
{
	cricket::VideoCapturer* capturer = NULL;

#if 0
	// TODO: doesn't seem to work using some webcams, produces an assertion error in debug mode,
	//       and a crash in release mode
	talk_base::scoped_ptr<cricket::DeviceManagerInterface> devManager(cricket::DeviceManagerFactory::Create());

	if (!devManager->Init()) 
	{
		cerr << "Can't create device manager" << endl;
		return 0;
	}

	cerr << "devManager->Init ok" << endl;

	std::vector<cricket::Device> devs;
	
	if (!devManager->GetVideoCaptureDevices(&devs)) 
	{
		cerr << "Can't enumerate video devices" << endl;
		return 0;
	}

	cerr << "devs.size() = " << devs.size() << endl;

	std::vector<cricket::Device>::iterator dev_it = devs.begin();
	
	for ( ; dev_it != devs.end(); ++dev_it) 
	{
		capturer = devManager->CreateVideoCapturer(*dev_it);
		if (capturer != NULL)
			break;
	}


#else
	m_pCapturer = new TestVideoCapturer();
	capturer = m_pCapturer;
#endif
	cerr << "capturer = " << capturer << endl;

	return capturer;
}

void TestWidget::onLocalSDPInfo(const QString &sdpText)
{
	m_pOfferText->setPlainText(sdpText);

	string sdpStr = sdpText.toStdString();

    	webrtc::SessionDescriptionInterface* pSessionDescription = webrtc::CreateSessionDescription("offer", sdpStr);
	m_peerConnection->SetLocalDescription(DummySetSessionDescriptionObserver::Create(), pSessionDescription);
}

void TestWidget::onLocalIceCandidate(const QString &iceCandidate)
{
	QString str = m_pOwnICEText->toPlainText();

	str += iceCandidate + "\n";

	m_pOwnICEText->setPlainText(str);
}

void TestWidget::setNewFrame(const QImage &img)
{
	int width = img.width();
	int height = img.height();

	if (width <= 0 || height <= 0)
		return;
	if (m_pCapturer == 0)
		return;

	int numBytes = width*height*4;
	uint8_t *pData = new uint8_t[numBytes];

	for (int y = 0 ; y < height ; y++)
	{
		for (int x = 0 ; x < width ; x++)
		{
			QRgb pixel = img.pixel(x,y);

			int offset = (x+y*width)*4;
			pData[offset+3] = qAlpha(pixel);
			pData[offset+2] = qBlue(pixel);
			pData[offset+1] = qGreen(pixel);
			pData[offset+0] = qRed(pixel);
		}
	}

	m_pCapturer->setImageData(pData, numBytes, width, height);
}

