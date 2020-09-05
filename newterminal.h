#pragma once
#pragma once
#include<QWidget>
#include<QLabel>
#include"lightbutton.h"
#include<QGridLayout>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QPainter>
#include"SwitchControl.h"
#include"ButtonQWidget.h"
#include<QPushButton>
//#include"WifiSpeed.h"
class newterminal :public QWidget
{
	Q_OBJECT

public:
	//explicit newterminal(QString name, int ButtonNum, int QLabelNum,QWidget* parent = 0 );
	explicit newterminal(QWidget* parent = 0);
	explicit newterminal(int newterminalType, QWidget* parent = 0);//0:iphone ,1:wifi, 2:wifispeed
private:
	QGridLayout* gridLayout;    //表格布局存放终端标签
	QLabel* pName;
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
	QList<QLabel*> newterminalNameLabels;
	QList<QPushButton*> newterminalNameButtons;
	QList<QGridLayout*>  InternalQGridLayoutList;//终端内部设备标签布局
	QList<LightButton*> LightButtonList;
	QList<SwitchControl*> SwitchControlList;
	QList<QLineEdit*> WifiSpeedList;
	int newterminalCount;
	//QGridLayout* pOverallGridLayout;//整体布局

private slots:
	void initControl();
	void initForm();
	void shownewterminal(int index = 0);
	void initFormIphone();
	void initFormWifi();
	void initFormWifiSpeed();
	void initFormIphoneSwitch();
	void initFormWifiSwitch();

	//void ShowSpeed();

};