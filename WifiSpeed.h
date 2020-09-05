#pragma once
#include"ui_WifiSpeed.h"
#include<QTcpSocket>
#include<QVBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QMessageBox>
#include<QSqlQuery>
#include"SwitchControl.h"
#include"NewTimer.h"
//#include"newterminal.h"
//namespace Ui
//{
//	class WifiSpeed;
//};
class WifiSpeed :public QWidget
{
	Q_OBJECT

public:
	//IphoneControl(QWidget *parent = Q_NULLPTR,QTcpServer *pser=NULL,QMap<int, QTcpSocket*> *LinkMap=NULL);
	WifiSpeed(QWidget*sigparent,QList<SwitchControl*> *SwitchControlList,QWidget* parent = Q_NULLPTR, QTcpSocket* tcpSocket = NULL);
	~WifiSpeed();
	
	double GetSpeedFromMysql(int id);
	void ReadConfig();
	void StartTimer(int id);
	void CheckSwitchSate();
private:
	//newterminal* pTerminal;
	Ui::WifiSpeed ui;
	QTcpSocket* tcpSocket;
	QWidget* sigparent;
	QLabel* pTitle;
	QLabel* pFill1;
	QLabel* pFill2;
	QLabel* pDeclare;

	QVBoxLayout* pGlobalLayOut;
	QHBoxLayout* pTitleLayOut;

	QWidget* pTerminalWidget;
	QWidget* pTitleWidget;
	QWidget* pFillWidget;

	//QVBoxLayout* pTerminalLayOut;
	QVBoxLayout* pFillLayOut;
	QGridLayout* pTerminalLayOut;
	//QMap<int,QTcpSocket*> *LinkList;

	QList<QLineEdit*> WifiEditList;

	QList<QWidget*> widgets;    //终端标签集合

	NewTimer** timerlist;        //定时更新速度

	QList<SwitchControl*> *pInternalTerminalSwitchList;

	//数据库配置
	QString HostName;
	QString baseName;
	QString UserName;
	QString PassWd;
	QString Table;
signals:
	void InformParent();
private slots:
	/*void OnPressOnButton();
	void OnPressDownButton();
	void UpdateOnButton();
	void UpdateNumberEdit();*/
	//void initForm();
	void init();
	void initFormGlobal();
	
	void UpdateDownSpeed(int num);
};