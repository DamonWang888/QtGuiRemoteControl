#include "MyTimer.h"

MyTimer::MyTimer(QObject *parent)
	: QObject(parent)
{
	qDebug() << "Initalize the timer";
	pixmap=new QPixmap("./image/bakc.jpg");
	plash=new QSplashScreen(*pixmap);
	plash->show();
	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(HandleTimeout()));
	timer->start(1000);
	
}

MyTimer::~MyTimer()
{

}

void MyTimer::WaitShow(int timeout)
{
	//QTimer *PTimer=
}
void MyTimer::HandleTimeout()
{
	qDebug() << "Enter timeout processing function\n";
	plash->close();
	if (timer->isActive())
		timer->stop();
}