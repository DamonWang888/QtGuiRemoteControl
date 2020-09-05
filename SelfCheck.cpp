#include "SelfCheck.h"
#include<QtQuick>
//#include<QML>
//import QtQuick 2.0

SelfCheck::SelfCheck(QWidget* parent, QTcpSocket* tcpSocket)
	: QWidget(parent), tcpSocket(tcpSocket)
{
	ui.setupUi(this);

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
	//QString weightName = "widget_1";
	QColor col1 = QColor(173, 216, 230);
	if (col1.isValid()) {
		QString qss = QString("background-color: %1").arg(col1.name());
		ui.widget_1->setStyleSheet(qss);
		ui.widget_2->setStyleSheet(qss);
		ui.widget_3->setStyleSheet(qss);
		ui.widget_4->setStyleSheet(qss);
		ui.widget_5->setStyleSheet(qss);
		ui.widget_6->setStyleSheet(qss);
		ui.widget_7->setStyleSheet(qss);
		ui.widget_8->setStyleSheet(qss);
		ui.widget_9->setStyleSheet(qss);
		ui.widget_10->setStyleSheet(qss);
		ui.widget_11->setStyleSheet(qss);
		ui.widget_12->setStyleSheet(qss);
		ui.widget_13->setStyleSheet(qss);
		ui.widget_14->setStyleSheet(qss);
		ui.widget_15->setStyleSheet(qss);
		ui.widget_16->setStyleSheet(qss);
		ui.widget_17->setStyleSheet(qss);
		ui.widget_18->setStyleSheet(qss);
		ui.widget_19->setStyleSheet(qss);
		ui.widget_20->setStyleSheet(qss);
		ui.widget_21->setStyleSheet(qss);
		ui.widget_22->setStyleSheet(qss);
		ui.widget_23->setStyleSheet(qss);
		ui.widget_24->setStyleSheet(qss);
		ui.widget_25->setStyleSheet(qss);
		
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
}

SelfCheck::~SelfCheck()
{
}

