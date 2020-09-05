#include "WifiControl.h"
#include"TotalMenu.h"
#include <QtWidgets/QApplication>
#include<QSplashScreen>
#include"MyTimer.h"
#include<windows.h>
#include"Log.h"
//#include<QTimer>

int main(int argc, char *argv[])
{
	QApplication::addLibraryPath("./plugins");
	QApplication a(argc, argv); 

	MyTimer Timer;
	Sleep(1000);
	TotalMenu M;
	M.ConnectToServer();
	M.show();

	return a.exec();
}
/*Log* pLog = new Log("ÈÕÖ¾.csv");
extern pLog;*/
/*QTimer *timer = new QTimer();
timer->singleShot(1000,this,);

splash.close();*/
/*QtGuiRemoteControl w;
w.show();*/
