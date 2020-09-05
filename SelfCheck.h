#pragma once
#include"ui_SelfCheck.h"
#include<QTcpSocket>
class SelfCheck :public QWidget
{
	Q_OBJECT

public:
	//IphoneControl(QWidget *parent = Q_NULLPTR,QTcpServer *pser=NULL,QMap<int, QTcpSocket*> *LinkMap=NULL);
	SelfCheck(QWidget* parent = Q_NULLPTR, QTcpSocket* tcpSocket = NULL);
	~SelfCheck();
	

private:
	Ui::SelfCheckUi ui;
	QTcpSocket* tcpSocket;

	//QMap<int,QTcpSocket*> *LinkList;

private slots:
	/*void OnPressOnButton();
	void OnPressDownButton();
	void UpdateOnButton();
	void UpdateNumberEdit();*/
	
};