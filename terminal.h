#pragma once
#include<QWidget>
#include<QLabel>
#include"lightbutton.h"
#include<QGridLayout>
#include<QVBoxLayout>
#include<QPainter>
#include"SwitchControl.h"
#include"WifiSpeed.h"
#include<QPushButton>
//#include"ButtonQWidget.h"
class terminal :public QWidget
{
	Q_OBJECT

public:
	//explicit terminal(QString name, int ButtonNum, int QLabelNum,QWidget* parent = 0 );
	explicit terminal( QWidget* parent = 0);
	explicit terminal(int TerminalType,QWidget* parent = 0);//0:iphone ,1:wifi, 2:wifispeed
	explicit terminal(int TerminalType, QTcpSocket* tcpSocket = NULL,QWidget* parent = Q_NULLPTR);//0:iphone ,1:wifi, 2:wifispeed
	~terminal();
private:
	QTcpSocket* tcpSocket;
	QGridLayout* gridLayout;    //表格布局存放终端标签
	QLabel *pName;
	QWidget* pBoundaryWidget;//外围QWidget
	QWidget* pInternalWidget;//内部QWidget,用来放置各个部分。
	QVBoxLayout* pInternalQVBoxLayout;//内部布局
	QLabel** pEquipMent1;
	QLabel** pEquipMent2;
	int ButtonNum;//显示灯数量
	int QLabelNum;//设备名称数量
	LightButton** PLightButton;
	QList<QWidget*> widgets;    //终端标签集合
	QList<QVBoxLayout*> QVBoxLayoutList;//单个终端内部布局
	QList<QLabel*> WifiLabels;
	QList<QLabel*> IphoneLabels;
	QList<QLabel*> TerminalNameLabels;
	QList<QPushButton*> TerminalNameButtons;
	QList<QGridLayout*>  InternalQGridLayoutList;//终端内部设备标签布局
	QList<LightButton*> LightButtonList;
	QList<SwitchControl*> SwitchControlList;
	int TerminalCount;
	//QGridLayout* pOverallGridLayout;//整体布局
private slots:
	void initControl();
	void initForm();
	void showterminal(int index = 0);
	void initFormIphone();
	void initFormWifi();
	void initFormWifiSpeed();
	void initFormIphoneSwitch();
	void initFormWifiSwitch();
	void ShowSpeed();

	
};