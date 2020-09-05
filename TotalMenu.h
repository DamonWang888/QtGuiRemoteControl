#pragma once

#include <QMainWindow>
#include "ui_TotalMenu.h"
#include"qtcpserver.h"
#include"tcpclientsocket.h"
#include"WifiControl.h"
#include"IphoneControl.h"
#include"SelfCheck.h"
#include"CurSelfCheck.h"
#include"NewSelfCheck.h"
#include"NewIphoneControl.h"
#include"NewWifiControl.h"
#include<stdio.h>
#include<QFile>
#include"Log.h"
static int EquipMentNum=0;
class TotalMenu : public QWidget
{
	Q_OBJECT

public:
	TotalMenu(QWidget*parent = Q_NULLPTR);
	~TotalMenu();
	QString getHostMacAddress();
	void ConnectToServer();
	void SendMacString();
	int ParseMsg( char *msg, int sz, int *ID, int *Commod, char Data[]);
	void ReadConfig();
	void SendSelfCheckCommod();

private:
	QTcpSocket *tcpSocket = nullptr;
	Ui::TotalMenu ui;
	//QTcpServer Server;
	QList<TcpClientSocket*> tcpclientsocketlist;
	QString ipAddress;
	QtGuiRemoteControl *pwificontrol = NULL;
	IphoneControl *pIphonecontrol = NULL;
	SelfCheck* pSelfCheck = NULL;
	CurSelfCheck* pCurSelfCheck = NULL;
	NewSelfCheck* pNewSelfCheck = NULL;
	NewIphoneControl* pNewIphoneControl = NULL;
	NewWifiControl* pNewWifiControl = NULL;
	QString HostName;
	QString baseName;
	QString Table;
	QString UserName;
	QString PassWd;
	QString ServerIp;
	QString ServerPort;
	Log* pLog;
	
	//QMap<int,QTcpSocket*> LinkList;

protected:
	void incomingConnection(int socketDescriptor);//只要出现一个新的连接，就会自动调用这个函数

signals:
	void receivespeed(QString msg, int length);
	void ConnectSuccess();
	void deviceoffline(int id);
	void InputNull();
	void UpdatesSelfcheck(int, char*);

private slots:
	void OnClickedButtonPhone();
	void OnClickedButtonWifi();
	void OnClickedButtonSelfCheck();
	void ServerNewConnection();
	void ServerNewMessage(QString msg,int length);
	void updateLinkList(QTcpSocket *ptcp);
	void readStatusFromServer();
	void RequestInitedData();
	void InitWifiPointer();
	void InitIphonePointer();
	void InitSelfCheckPointer();
	
	
};
