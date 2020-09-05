#include "NewTimer.h"

NewTimer::NewTimer(int num,QWidget* parent)
	: num(num),QWidget(parent)
{
	timer = new QTimer(this);
	connect(this,SIGNAL(timeout(int)),parent,SLOT(UpdateDownSpeed(int)));

}
/*qDebug() << "Initalize the timer";
pixmap = new QPixmap("./image/bakc.jpg");
plash = new QSplashScreen(*pixmap);
plash->show();*/
//timer->start(1000);

NewTimer::~NewTimer()
{

}

void NewTimer::WaitShow(int timeout)
{
	//QTimer *PTimer=
}
void NewTimer::HandleTimeout()
{
	qDebug() << "Enter timeout processing function\n";
	emit timeout(num);
}
/*plash->close();
if (timer->isActive())
	timer->stop();*/

void NewTimer::start(int timesev)
{
	connect(timer, SIGNAL(timeout()), this, SLOT(HandleTimeout()));
	timer->start(timesev);
	IsStart = true;
}
void NewTimer::stop()
{
	IsStart = false;
	timer->stop();
}
bool NewTimer::GetSate()
{
	return IsStart;
}
void NewTimer::SetStop()
{
	IsStart = false;
	emit timeout(num);
}