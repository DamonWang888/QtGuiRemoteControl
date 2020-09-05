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
	QGridLayout* gridLayout;    //��񲼾ִ���ն˱�ǩ
	QLabel* pName;
	QWidget* pBoundaryWidget;//��ΧQWidget
	QWidget* pInternalWidget;//�ڲ�QWidget,�������ø������֡�
	QVBoxLayout* pInternalQVBoxLayout;//�ڲ�����
	QLabel** pEquipMent1;
	QLabel** pEquipMent2;
	int ButtonNum;//��ʾ������
	int QLabelNum;//�豸��������
	LightButton** PLightButton;
	QList<QWidget*> widgets;    //�ն˱�ǩ����
	QList<QVBoxLayout*> QVBoxLayoutList;//�����ն��ڲ�����
	QList<QLabel*> WifiLabels;
	QList<QLabel*> IphoneLabels;
	QList<QLabel*> newterminalNameLabels;
	QList<QPushButton*> newterminalNameButtons;
	QList<QGridLayout*>  InternalQGridLayoutList;//�ն��ڲ��豸��ǩ����
	QList<LightButton*> LightButtonList;
	QList<SwitchControl*> SwitchControlList;
	QList<QLineEdit*> WifiSpeedList;
	int newterminalCount;
	//QGridLayout* pOverallGridLayout;//���岼��

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