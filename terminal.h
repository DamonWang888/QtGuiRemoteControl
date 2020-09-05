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
	QGridLayout* gridLayout;    //��񲼾ִ���ն˱�ǩ
	QLabel *pName;
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
	QList<QLabel*> TerminalNameLabels;
	QList<QPushButton*> TerminalNameButtons;
	QList<QGridLayout*>  InternalQGridLayoutList;//�ն��ڲ��豸��ǩ����
	QList<LightButton*> LightButtonList;
	QList<SwitchControl*> SwitchControlList;
	int TerminalCount;
	//QGridLayout* pOverallGridLayout;//���岼��
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