#pragma once

#include <QObject>
#include<QTimer>
#include<QSplashScreen>
#include<qdebug.h>
class QTimer;
class MyTimer : public QObject
{
	Q_OBJECT

public:		
	MyTimer(QObject *parent=NULL);
	~MyTimer();
	void WaitShow(int timeout);

private:
	QTimer *timer;
	QPixmap *pixmap;
	QSplashScreen *plash;
public slots:
	void HandleTimeout();
};
