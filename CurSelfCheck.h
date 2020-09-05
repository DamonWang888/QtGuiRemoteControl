#pragma once
#pragma once
#include"ui_CurSelfCheck.h"
#include<QTcpSocket>
#include"terminal.h"
class CurSelfCheck :public QWidget
{
	Q_OBJECT

public:
	//IphoneControl(QWidget *parent = Q_NULLPTR,QTcpServer *pser=NULL,QMap<int, QTcpSocket*> *LinkMap=NULL);
	CurSelfCheck(QWidget* parent = Q_NULLPTR, QTcpSocket* tcpSocket = NULL);
	~CurSelfCheck();


private:
	Ui::CurSelfCheck ui;
	QTcpSocket* tcpSocket;
	terminal* pTerminal;
	//QMap<int,QTcpSocket*> *LinkList;

private slots:
	/*void OnPressOnButton();
	void OnPressDownButton();
	void UpdateOnButton();
	void UpdateNumberEdit();*/

};