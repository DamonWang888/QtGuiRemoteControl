#pragma once

#include <QWidget>
#include "ui_IphoneControl.h"
#include"qtcpserver.h"
#include<QTcpSocket>
#include"qmessagebox.h"
class IphoneControl : public QWidget
{
	Q_OBJECT

public:
	//IphoneControl(QWidget *parent = Q_NULLPTR,QTcpServer *pser=NULL,QMap<int, QTcpSocket*> *LinkMap=NULL);
	IphoneControl(QWidget *parent = Q_NULLPTR, QTcpSocket *tcpSocket=NULL);
	~IphoneControl();
	void SendMsg(char *data);

private:
	Ui::IphoneControl ui;
	QTcpSocket *tcpSocket;

	//QMap<int,QTcpSocket*> *LinkList;

private slots:
	/*void OnPressOnButton();
	void OnPressDownButton();
	void UpdateOnButton();
	void UpdateNumberEdit();*/
	void phonecall_1();
	void phonecall_2();
	void phonecall_3();
	void phonecall_4();
	void phonecall_5();
	void phonecall_6();
	void totalphonecall_1();
	void totalphonecall_2();
	void totalphonecall_3();
};
