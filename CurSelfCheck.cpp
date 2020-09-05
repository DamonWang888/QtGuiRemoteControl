#include "CurSelfCheck.h"

#include<QtQuick>
//#include<QML>
//import QtQuick 2.0

CurSelfCheck::CurSelfCheck(QWidget* parent, QTcpSocket* tcpSocket)
	: QWidget(parent), tcpSocket(tcpSocket)
{
	ui.setupUi(this);
	//QString name = "жу╤к1";
	//pTerminal = new terminal(name,12,12,this);

	//change the background color
	/*ui.Title->setAutoFillBackground(true);
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::yellow);
	ui.Title->setPalette(pal);*/

	/*ui.widget1->setAutoFillBackground(true);
	QPalette palweight = palette();
	palweight.setColor(QPalette::Background, RGB(0 ,245, 255));
	ui.widget1->setPalette(palweight);

	ui.widget_2->setAutoFillBackground(true);
	ui.widget_2->setPalette(palweight);*/

	
	}

	/*Rectangle
	{
		width:100
		height:100
		color:"red"
		border.color:"black"
		border.width:5
		radius:10
	}*/


CurSelfCheck::~CurSelfCheck()
{
}

