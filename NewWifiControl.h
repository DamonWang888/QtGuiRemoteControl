#pragma once

#include"ui_NewWifiControl.h"
#include<QTcpSocket>
#include<QVBoxLayout>
#include"SwitchControl.h"
#include<QList>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>
#include"WifiSpeed.h"
#include"Log.h"
#include<QSet>
//#include"terminal.h"
//namespace Ui
//{
//	class NewWifiControl;
//};
class NewWifiControl :public QWidget
{
	Q_OBJECT

public:
	//WifiControl(QWidget *parent = Q_NULLPTR,QTcpServer *pser=NULL,QMap<int, QTcpSocket*> *LinkMap=NULL);
	NewWifiControl(QWidget* sigparent ,Log* pLog=NULL,QWidget* parent = Q_NULLPTR, QTcpSocket* tcpSocket = NULL);
	~NewWifiControl();
	void SendMsg(char* data);

private:
	/*terminal* pTerminal;
	terminal* pTerminalSwitch;*/
	//QMap<int,QTcpSocket*> *LinkList;
	QWidget* sigparent;
	Log* pLog;

	int TimeInterval;//minute

	//keep time
	//QString tBeginOperate;  //开始操作
	//QString tend;    //
	//QTime *pBegin;  //开始操作
	//QTime* PEnd;    //开始操作

	QTimer* pOperateTimer;

	Ui::NewWifiControl ui;
	QTcpSocket* tcpSocket;
	QLabel* pTitle;
	QLabel* pFill1;
	QLabel* pFill2;

	//overall arrangement
	QHBoxLayout* pTitleLayOut;
	QGridLayout* pTerminalLayOut;
	QGridLayout* pTerminalSwitchLayOut;
	QVBoxLayout* pGlobalLayOut;
	QGridLayout* pSwitchButtonLayOut;

	//internal small widget
	QList<QWidget*> widgets;    //终端标签集合

	//overall widget
	QWidget* pTerminalWidget;
	QWidget* pSwitchButtonWidget;
	QWidget* pTitleWidget;

	//Master Switch
	QList<SwitchControl*> pMasterSwitchList;

	//terminal internal switch
	QList<SwitchControl*> pInternalTerminalSwitchList;

	//terminal internal Master switch
	QList<SwitchControl*> pInternalMasterSwitchList;

	QLabel* pTotalSwitch;	
	QLabel* p1_50Switch;
	QLabel* p51_100Switch;
	QLabel* p101_150Switch;

	WifiSpeed* pWifiSpeed = NULL;
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
	void SwitchControl0();
	void SwitchControl1();
	void SwitchControl2();
	void SwitchControl3();
	void SwitchSlot(int type, int num);
	void ShowSpeed();
	void RecordLog();
	void InitWifiSpeedPointer();
};
