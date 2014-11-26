#include "talk/media/devices/deviceinfo.h"
#include "talk/media/base/mediacommon.h"
//#include "talk/base/logging.h"
#include "talk/media/base/videoframe.h"
#include "testvideocapturer.h"
#include <QElapsedTimer>
#include <stdlib.h>

using namespace cricket;

CaptureThread::CaptureThread(VideoCapturer *pCapturer)
{
	m_pCapturer = pCapturer;
	m_stopped = false;
	m_pImageBytes = 0;
	m_width = 0;
	m_height = 0;
	m_imageDataLen = 0;
}

CaptureThread::~CaptureThread()
{
	stop();
}

void CaptureThread::stop()
{
	QElapsedTimer timer;

	timer.start();

	m_stopMutex.lock();
	m_stopped = true;
	m_stopMutex.unlock();

	while (isRunning() && !timer.hasExpired(300)) // wait 300ms at most
	{
		QThread::msleep(50);
	}

	if (isRunning())
	{
		LOG(LS_INFO) << "CaptureThread: KILLING THREAD";
		terminate();
	}
	else
	{
		LOG(LS_INFO) << "CaptureThread: Thread stopped nicely";
	}

	delete [] m_pImageBytes;
	m_pImageBytes = 0;
}

void CaptureThread::run()
{
	LOG(LS_INFO) << "CaptureThread: STARTED";

	bool stopped = false;
	uint64_t prevTimestamp = 0;

	while (!stopped)
	{
		CapturedFrame frame;
		
		frame.elapsed_time = 33333333;
		frame.time_stamp = prevTimestamp;
		prevTimestamp += frame.elapsed_time;  // 30 fps

		m_imageMutex.lock();
		if (m_pImageBytes && m_imageDataLen > 0 && m_width > 0 && m_height > 0)
		{
			frame.data = m_pImageBytes;
			frame.width = m_width;
			frame.height = m_height;
			frame.fourcc = FOURCC_ABGR;
			frame.data_size = m_imageDataLen;

			if (frame.width*frame.height*4 != m_imageDataLen)
				LOG(LS_INFO) << "CaptureThread: with and height don't match size for ABGR data, skipping frame";
			else
			{
				//LOG(LS_INFO) << "CaptureThread: got frame " << (int)frameVal << " glGetError: " << glGetError();
				m_pCapturer->SignalFrameCaptured(m_pCapturer, &frame);
			}
		}
		m_imageMutex.unlock();

		QThread::msleep(33);

		m_stopMutex.lock();
		stopped = m_stopped;
		m_stopMutex.unlock();
	}
}

void CaptureThread::setImageData(uint8_t *pImageBytes, size_t len, int width, int height)
{
	m_imageMutex.lock();

	delete [] m_pImageBytes;

	m_pImageBytes = pImageBytes;
	m_imageDataLen = len;
	m_width = width;
	m_height = height;

	m_imageMutex.unlock();
}

TestVideoCapturer::TestVideoCapturer() : m_captureThread(this)
{
}

bool TestVideoCapturer::GetBestCaptureFormat(const VideoFormat& desired, VideoFormat* best_format)
{
	LOG(LS_INFO) << "TestVideoCapturer::GetBestCaptureFormat";
	*best_format = desired; // TODO
	return true;
}

CaptureState TestVideoCapturer::Start(const VideoFormat& capture_format)
{
	LOG(LS_INFO) << "TestVideoCapturer::Start";
	
	m_captureThread.start();

	return CS_RUNNING; 
}

void TestVideoCapturer::Stop()
{
	LOG(LS_INFO) << "TestVideoCapturer::Stop";
	
	m_captureThread.stop();
}

bool TestVideoCapturer::IsRunning()
{
	LOG(LS_INFO) << "TestVideoCapturer::IsRunning";
	return m_captureThread.isRunning();
}

bool TestVideoCapturer::IsScreencast() const
{
	//LOG(LS_INFO) << "TestVideoCapturer::IsScreencast";
	// TODO: is this appropriate here?
	return true;
}

bool TestVideoCapturer::GetPreferredFourccs(std::vector<uint32>* fourccs)
{
	fourccs->push_back(FOURCC_ABGR);
	return true;
}

void TestVideoCapturer::setImageData(uint8_t *pImageBytes, size_t len, int width, int height)
{
	m_captureThread.setImageData(pImageBytes, len, width, height);
}

