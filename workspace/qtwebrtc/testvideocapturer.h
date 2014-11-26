#ifndef TESTVIDEOCAPTURER_H

#define TESTVIDEOCAPTURER_H

#include "talk/media/base/videocapturer.h"
#include <QThread>
#include <QMutex>

class CaptureThread : public QThread
{
public:
	CaptureThread(cricket::VideoCapturer *pCapturer);
	~CaptureThread();

	void stop(); 
	void setImageData(uint8_t *pImageBytes, size_t len, int width, int height);
private:
	void run();

	cricket::VideoCapturer *m_pCapturer;
	bool m_stopped;
	QMutex m_stopMutex;
	QMutex m_imageMutex;

	uint8_t *m_pImageBytes;
	size_t m_imageDataLen;
	int m_width;
	int m_height;

};

class TestVideoCapturer : public cricket::VideoCapturer
{
public:
	TestVideoCapturer();

	bool GetBestCaptureFormat(const cricket::VideoFormat& desired, cricket::VideoFormat* best_format);
	cricket::CaptureState Start(const cricket::VideoFormat& capture_format);
	void Stop();
	bool IsRunning();
	bool IsScreencast() const;
	bool GetPreferredFourccs(std::vector<uint32>* fourccs);

	void setImageData(uint8_t *pImageBytes, size_t len, int width, int height);
private:
	CaptureThread m_captureThread;
};

#endif // TESTVIDEOCAPTURER_H
