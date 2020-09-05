#pragma once
#pragma once
#pragma once
#include"ui_NewSelfCheck.h"
#include<QTcpSocket>
#include<QVBoxLayout>
#include<QLabel>
#include<QGridLayout>
#include<LightButton.h>
//#include"terminal.h"
//namespace Ui
//{
//	class NewSelfCheck;
//};
class NewSelfCheck :public QWidget
{
	Q_OBJECT
		
public:
	NewSelfCheck(QWidget* sigparent,QWidget* parent = Q_NULLPTR, QTcpSocket* tcpSocket = NULL);
	~NewSelfCheck();
	//IphoneControl(QWidget *parent = Q_NULLPTR,QTcpServer *pser=NULL,QMap<int, QTcpSocket*> *LinkMap=NULL);


private:
	Ui::NewSelfCheck ui;
	QWidget* sigparent;
	QTcpSocket* tcpSocket;
	QLabel* pTitle;
	QLabel* pFill1;
	QLabel* pFill2;

	QVBoxLayout* pGlobalLayOut;
	QWidget* pTerminalWidget;
	QWidget* pTitleWidget;

	QGridLayout* pTerminalLayOut;
	QHBoxLayout* pTitleLayOut;


	QList<QWidget*> widgets;    //�ն˱�ǩ����
	QList<LightButton*> LightButtonList; //�Ƽ���
	QList<LightButton*> WifiLightButtonList; //wifi�Ƽ���
	QList<LightButton*> IphoneLightButtonList; //iphone�Ƽ���

	//terminal* pTerminal;
	//QMap<int,QTcpSocket*> *LinkList;
signals:
	void InformParent();
private slots:
	void init();
	void initFormGlobal();
	void UpdateDeviceStatus(int, char*);
	//void initForm();
	/*void OnPressOnButton();
	void OnPressDownButton();
	void UpdateOnButton();
	void UpdateNumberEdit();*/

};