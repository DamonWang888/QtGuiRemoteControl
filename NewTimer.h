#pragma once
#pragma once

#include <QObject>
#include<QTimer>
#include<QSplashScreen>
#include<qdebug.h>
//#include"WifiSpeed.h"
class QTimer;
class NewTimer : public QWidget
{
	Q_OBJECT

public:
	NewTimer(int num,QWidget* parent = NULL);
	~NewTimer();
	void WaitShow(int timeout);
	void start(int timesev);
	void stop();
	bool GetSate();
	void SetStop();
signals:
	void timeout(int);

private:
	bool IsStart=false;
	int num;//¶¨Ê±Æ÷±àºÅ
	QTimer* timer;
	QPixmap* pixmap;
	QSplashScreen* plash;
public slots:
	void HandleTimeout();
};
