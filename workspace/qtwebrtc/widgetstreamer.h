#ifndef WIDGETSTREAMER_H

#define WIDGETSTREAMER_H

#include "testwidget.h"

class WidgetStreamer : public QObject
{
	Q_OBJECT
public:
	WidgetStreamer(QWidget *pRenderWidget, TestWidget *pStreamWidget);
	~WidgetStreamer();
private slots:
	void onTimeout();
private:
	QWidget *m_pRenderWidget;
	TestWidget *m_pStreamWidget;
};

#endif // WIDGETSTREAMER_H


