#pragma once
#pragma once
#pragma once
#pragma once
#include"ui_NewIphoneControl.h"
#include<QTcpSocket>
#include<QVBoxLayout>
#include<QLabel>
#include"SwitchControl.h"
#include<QList>
#include<QGridLayout>
#include"Log.h"
//#include"terminal.h"
//namespace Ui
//{
//	class NewIphoneControl;
//};
class NewIphoneControl :public QWidget
{
	Q_OBJECT

public:
	//IphoneControl(QWidget *parent = Q_NULLPTR,QTcpServer *pser=NULL,QMap<int, QTcpSocket*> *LinkMap=NULL);
	NewIphoneControl(QWidget* sigparent,Log* pLog=NULL,QWidget* parent = Q_NULLPTR, QTcpSocket* tcpSocket = NULL);
	~NewIphoneControl();
	void SendMsg(char* data);
	//static NewIphoneControl* getInstance(Log* pLog = NULL, QWidget* parent = Q_NULLPTR, QTcpSocket* tcpSocket = NULL);
	/*
	static NewIphoneControl* NewIphoneControl::getInstance(Log* pLog, QWidget* parent, QTcpSocket* tcpSocket)
	{
		if (instance == NULL)
			instance = new NewIphoneControl(pLog, NULL, tcpSocket);
		return instance;
	}
	*/
private:
	//NewIphoneControl(Log* pLog = NULL, QWidget* parent = Q_NULLPTR, QTcpSocket* tcpSocket = NULL);
	static NewIphoneControl* instance;
	QWidget* sigparent;
	Log* pLog;
	QTimer* pOperateTimer;
	int TimeInterval;//minute
	Ui::NewIphoneControl ui;
	QTcpSocket* tcpSocket;

	//realize by Object-oriented
	/*terminal* pTerminal;
	terminal* pTerminalSwitch;*/

	QLabel* pTitle;
	QLabel* pFill1;
	QLabel* pFill2;
	
	QGridLayout* pSwitchButtonLayOut;

	//overall widget
	QWidget* pTerminalWidget;
	QWidget* pSwitchButtonWidget;
	QWidget* pTitleWidget;

	//internal small widget
	QList<QWidget*> widgets;    //÷’∂À±Í«©ºØ∫œ

	//overall arrangement
	QHBoxLayout* pTitleLayOut;
	QGridLayout* pTerminalLayOut;
	QGridLayout* pTerminalSwitchLayOut;
	QVBoxLayout* pGlobalLayOut;


	//Master Switch label
	QLabel* pTotalSwitch;
	QLabel* p1_50Switch;
	QLabel* p51_100Switch;
	QLabel* p101_150Switch;

	//Master Switch
	QList<SwitchControl*> pMasterSwitchList;

	//terminal internal switch
	QList<SwitchControl*> pInternalTerminalSwitchList;

	//terminal internal Master switch
	QList<SwitchControl*> pInternalMasterSwitchList;

	//QMap<int,QTcpSocket*> *LinkList;
signals:
	void InformParent();
private slots:
	/*void OnPressOnButton();
	void OnPressDownButton();
	void UpdateOnButton();
	void UpdateNumberEdit();*/
	void init();
	//void initForm();
	void initFormGlobal();
	void SwitchControl0();
	void SwitchControl1();
	void SwitchControl2();
	void SwitchControl3();
	void SwitchSlot(int type,int num);
	void RecordLog();
};