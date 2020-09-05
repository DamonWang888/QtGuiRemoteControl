#pragma execution_character_set("utf-8")
#include "NewWifiControl.h"
#include<QtQuick>
//#include<QML>
//import QtQuick 2.0

NewWifiControl::NewWifiControl(QWidget* sigparent,Log* pLog,QWidget* parent, QTcpSocket* tcpSocket)
	:sigparent(sigparent),pLog(pLog), QWidget(parent), tcpSocket(tcpSocket)
{
	ui.setupUi(this);
	SwitchControl* pSwitchControl = NULL;
	TimeInterval = 1;
	pOperateTimer = new QTimer;
	connect(pOperateTimer,SIGNAL(timeout()), this,SLOT(RecordLog()));
	pOperateTimer->start(1000*60* TimeInterval);//5min
	connect(this,SIGNAL(InformParent()),sigparent,SLOT(InitWifiPointer()));
	//initlize switchcontrol pointer
	for (int i = 0; i < 4; i++)
	{
		pSwitchControl = new SwitchControl(0, i, this, this);
		pMasterSwitchList.append(pSwitchControl);
	}

	for (int i = 0; i < 25; i++)
	{
		pSwitchControl = new SwitchControl(1, i, this, this);
		pInternalMasterSwitchList.append(pSwitchControl);
	}

	for (int i = 0; i < 150; i++)
	{
		pSwitchControl = new SwitchControl(2, i, this, this);
		pInternalTerminalSwitchList.append(pSwitchControl);
	}
	this->init();
	this->initFormGlobal();
}
//QTime timer;
//timer.start();
//for (int j = 0; j < 65536; j++)
//{
//}
//	QSet<int> WifiStatus;
//	QSet<int> IphoneStatus;
//	QString TimeQuantum="7:00-8:00";
//	for (int i = 1; i <= 256; i++)
//	{
//		WifiStatus.insert(i);
//		IphoneStatus.insert(i * 2);
//	}
//	pLog->add(TimeQuantum,IphoneStatus,WifiStatus);
//qDebug() << "exec success spend time:" << runtime << "ms" << endl;

//int runtime = timer.elapsed(); //gets the runtime in ms
//QString name = "终端1";
//pTerminal = new terminal(name,12,12,this);

//change the background color
/*ui.Title->setAutoFillBackground(true);
QPalette pal = palette();
pal.setColor(QPalette::Background, Qt::yellow);
ui.Title->setPalette(pal);*/

/*ui.widget1->setAutoFillBackground(true);
QPalette palweight = palette();
palweight.setColor(QPalette::Background, RGB(0 ,245, 255));
ui.widget1->setPalette(palweight);

ui.widget_2->setAutoFillBackground(true);
ui.widget_2->setPalette(palweight);*/
//this->initForm();

/*Rectangle
{
	width:100
	height:100
	color:"red"
	border.color:"black"
	border.width:5
	radius:10
}*/


NewWifiControl::~NewWifiControl()
{
	emit InformParent();
}
void NewWifiControl::init()
{
	pGlobalLayOut = new QVBoxLayout;
	pGlobalLayOut->setSpacing(6);//栅格之间的空白
	pGlobalLayOut->setMargin(0);//边缘
	pGlobalLayOut->setObjectName("gridLayout");
	this->setLayout(pGlobalLayOut);
}

//void NewWifiControl::initForm()
//{
//	pTitleWidget = new QWidget(this);
//	pTitle = new QLabel(pTitleWidget);
//	pTitle->setObjectName(QString("GlobalTitle"));
//	pTitle->setText(QString("WIFI通信控制"));
//	pFill1 = new QLabel(pTitleWidget);
//	pFill1->setObjectName(QString("FillLabel1"));
//	pFill2 = new QLabel(pTitleWidget);
//	pFill2->setObjectName(QString("FillLabel2"));
//	/*
//	pTitle = new QLabel(this);
//	pTitle->setObjectName(QString("GlobalTitle"));
//	pTitle->setText(QString("WIFI通信控制"));
//	pFill1 = new QLabel(this);
//	pFill1->setObjectName(QString("FillLabel1"));
//	pFill2 = new QLabel(this);
//	pFill2->setObjectName(QString("FillLabel2"));
//	*/
//	//pFill->setText(QString("系统自检"));
//	QFont font1;
//	font1.setPointSize(27);
//	pTitle->setFont(font1);
//	pTitle->setTextFormat(Qt::AutoText);
//	pTitle->setGeometry(360, 0, 220, 36);
//	pFill1->setGeometry(20, 0, 340, 36);
//	pFill2->setGeometry(580, 0, 340, 36);
//	//pFill->setText(QString("系统自检"));
//	QColor col1 = QColor(255, 211, 155);
//	if (col1.isValid()) {
//		QString qss = QString("background-color: %1").arg(col1.name());
//		pFill1->setStyleSheet(qss);
//		pFill2->setStyleSheet(qss);
//		pTitle->setStyleSheet(qss);
//	}
//	pTitleLayOut = new QHBoxLayout();
//	pTitleWidget->setLayout(pTitleLayOut);
//	//pTitleLayOut->SetFixedSize();
//	//pTitle->setLayout(pTitleLayOut);
//
//	pTitle->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//	pFill1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//	pFill2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//
//	pTitleWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
//	pTitleWidget->setMaximumHeight(36);
//	//pTitle->setSizePolicy();
//
//	pTitleLayOut->setMargin(0);
//	pTitleLayOut->setSpacing(0);
//	pTitleLayOut->addWidget(pFill1);
//	pTitleLayOut->addWidget(pTitle);
//	pTitleLayOut->addWidget(pFill2);
//
//	pSwitchButtonWidget = new QWidget(this);
//	pSwitchButtonWidget->setObjectName(QStringLiteral("layoutWidget"));
//	pSwitchButtonWidget->setGeometry(QRect(20, 40, 900, 100));
//	if (col1.isValid())
//	{
//		QString qss = QString("background-color: %1").arg(col1.name());
//		pSwitchButtonWidget->setStyleSheet(qss);
//	}
//	pTerminalSwitchLayOut = new QVBoxLayout;
//	pTerminalSwitchLayOut->setSpacing(0);//栅格之间的空白
//	pTerminalSwitchLayOut->setMargin(0);//边缘
//	pTerminalSwitchLayOut->setObjectName("TerminalSwitchLayout");
//	pSwitchButtonWidget->setLayout(pTerminalSwitchLayOut);
//	pSwitchButtonWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
//	pSwitchButtonWidget->setMaximumHeight(60);
//	//pTerminalSwitch = new terminal(4, pSwitchButtonWidget);
//	//pTerminal->setGeometry();
//	pTerminalSwitchLayOut->addWidget(pTerminalSwitch);
//
//
//	//pSwitchButtonWidget->setGeometry(QRect(20, 40, 900, 100));
//	/*
//	pSwitchButtonLayOut = new QGridLayout;
//	pSwitchButtonLayOut->setSpacing(6);//栅格之间的空白
//	pSwitchButtonLayOut->setMargin(0);//边缘
//	pSwitchButtonLayOut->setObjectName("gridLayout");
//	pSwitchButtonWidget->setLayout(pSwitchButtonLayOut);
//
//
//	pTotalSwitch = new QLabel(pSwitchButtonWidget);
//	p1_50Switch = new QLabel(pSwitchButtonWidget);
//	p51_100Switch = new QLabel(pSwitchButtonWidget);
//	p101_150Switch = new QLabel(pSwitchButtonWidget);
//	pTotalSwitch->setObjectName(QStringLiteral("TotalSwitch"));
//	p1_50Switch->setObjectName(QStringLiteral("1_50Switch"));
//	p51_100Switch->setObjectName(QStringLiteral("51_100Switch"));
//	p101_150Switch->setObjectName(QStringLiteral("101_150Switch"));
//	pTotalSwitch->setGeometry(QRect(20, 40, 900, 100));
//	*/
//
//	pTerminalWidget = new QWidget(this);
//	pTerminalWidget->setObjectName(QStringLiteral("layoutWidget"));
//	pTerminalWidget->setGeometry(QRect(20, 145, 900, 800));
//
//	pTerminalLayOut = new QVBoxLayout;
//	pTerminalLayOut->setSpacing(6);//栅格之间的空白
//	pTerminalLayOut->setMargin(0);//边缘
//	pTerminalLayOut->setObjectName("TerminalLayout");
//	pTerminalWidget->setLayout(pTerminalLayOut);
//
//	pTerminal = new terminal(1, pTerminalWidget);
//	//pTerminal->setGeometry();
//	pTerminalLayOut->addWidget(pTerminal);
//	pGlobalLayOut->addWidget(pTitleWidget);
//	pGlobalLayOut->addWidget(pSwitchButtonWidget);
//	pGlobalLayOut->addWidget(pTerminalWidget);
//	//pGlobalLayOut->addWidget(pTitle);
//	//pGlobalLayOut->addWidget(pTerminalWidget);
//}
void NewWifiControl::initFormGlobal()
{
	pTitleWidget = new QWidget(this);
	pTitleWidget->setObjectName(QStringLiteral("TitleWidget"));
	pTitleWidget->setGeometry(QRect(0, 0, 900, 50));
	pTitle = new QLabel(pTitleWidget);
	pTitle->setObjectName(QString("GlobalTitle"));
	pTitle->setText(QString("WIFI通信控制"));
	pFill1 = new QLabel(pTitleWidget);
	pFill1->setObjectName(QString("FillLabel1"));
	pFill2 = new QLabel(pTitleWidget);
	pFill2->setObjectName(QString("FillLabel2"));


	QFont font1;
	font1.setPointSize(30);
	pTitle->setFont(font1);
	pTitle->setTextFormat(Qt::AutoText);
	pFill1->setGeometry(20, 0, 340, 50);
	pTitle->setGeometry(360, 0, 220, 50);
	pFill2->setGeometry(580, 0, 340, 50);
	QColor col1 = QColor(255, 211, 155);
	if (col1.isValid()) {
		QString qss = QString("background-color: %1").arg(col1.name());
		pFill1->setStyleSheet(qss);
		pFill2->setStyleSheet(qss);
		pTitle->setStyleSheet(qss);
	}

	pTitleLayOut = new QHBoxLayout();
	pTitleWidget->setLayout(pTitleLayOut);


	pTitle->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	pFill1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	pFill2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	pTitleWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
	pTitleWidget->setMaximumHeight(50);

	pTitleLayOut->setMargin(0);
	pTitleLayOut->setSpacing(0);
	pTitleLayOut->addWidget(pFill1);
	pTitleLayOut->addWidget(pTitle);
	pTitleLayOut->addWidget(pFill2);


	pSwitchButtonWidget = new QWidget(this);
	pSwitchButtonWidget->setObjectName(QStringLiteral("layoutWidget"));
	pSwitchButtonWidget->setGeometry(QRect(20, 40, 900, 100));
	if (col1.isValid())
	{
		QString qss = QString("background-color: %1").arg(col1.name());
		pSwitchButtonWidget->setStyleSheet(qss);
	}
	pTerminalSwitchLayOut = new QGridLayout;
	//pTerminalSwitchLayOut->setSpacing(6);//栅格之间的空白
	pTerminalSwitchLayOut->setHorizontalSpacing(0);
	pTerminalSwitchLayOut->setVerticalSpacing(20);
	pTerminalSwitchLayOut->setMargin(6);//边缘
	pTerminalSwitchLayOut->setObjectName("TerminalSwitchLayout");
	pSwitchButtonWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
	pSwitchButtonWidget->setMaximumHeight(70);
	pSwitchButtonWidget->setLayout(pTerminalSwitchLayOut);

	for (int j = 0; j < 4; j++)
	{
		SwitchControl* pSwitchControl = new SwitchControl(0, j, this, this);

		pMasterSwitchList[j] = pSwitchControl;
		QLabel* internalLabel = new QLabel();
		internalLabel->setObjectName(QString("PhoneTotalSwitch%1_%1").arg(j));
		if (j == 0)
		{
			internalLabel->setText(QString("全部WIFI开关"));
			pTerminalSwitchLayOut->addWidget(internalLabel, 0, 1, 1, 1);//row column
			pTerminalSwitchLayOut->addWidget(pSwitchControl, 0, 0, 1, 1);
		}
		else if (j == 1)
		{
			internalLabel->setText(QString("1-50WIFI开关"));
			pTerminalSwitchLayOut->addWidget(internalLabel, 0, 3, 1, 1);//row column
			pTerminalSwitchLayOut->addWidget(pSwitchControl, 0, 2, 1, 1);
		}
		else if (j == 2)
		{
			internalLabel->setText(QString("51-100WIFI开关"));
			pTerminalSwitchLayOut->addWidget(internalLabel, 1, 1, 1, 1);//row column
			pTerminalSwitchLayOut->addWidget(pSwitchControl, 1, 0, 1, 1);
		}
		else
		{
			internalLabel->setText(QString("101-150WIFI开关"));
			pTerminalSwitchLayOut->addWidget(internalLabel, 1, 3, 1, 1);//row column
			pTerminalSwitchLayOut->addWidget(pSwitchControl, 1, 2, 1, 1);
		}
	}
	pTerminalWidget = new QWidget(this);
	pTerminalWidget->setObjectName(QStringLiteral("layoutWidget"));
	pTerminalWidget->setGeometry(QRect(20, 145, 900, 800));

	pTerminalLayOut = new QGridLayout;
	pTerminalLayOut->setSpacing(6);//栅格之间的空白
	pTerminalLayOut->setMargin(0);//边缘
	pTerminalLayOut->setObjectName("TerminalLayout");
	pTerminalWidget->setLayout(pTerminalLayOut);
	int TerminalCount = 25;

	for (int i = 0; i < TerminalCount; i++) {



		QWidget* widget = new QWidget(pTerminalWidget);
		widget->setObjectName(QString("terminal%1").arg(i + 1));
		widget->installEventFilter(this);
		widget->setFocusPolicy(Qt::StrongFocus);
		QColor col1 = QColor(173, 216, 230);
		if (col1.isValid()) {
			QString qss = QString("background-color: %1").arg(col1.name());

			widget->setStyleSheet(qss);
		}
		QVBoxLayout* verticalLayout = new QVBoxLayout();
		verticalLayout->setObjectName(QString("verticalLayout%1").arg(i + 1));
		verticalLayout->setSpacing(6);

		QPushButton* terminalName = new QPushButton(widget);
		terminalName->setObjectName(QString("terminal_label_%1").arg(i + 1));
		terminalName->setText(QString("终端 %1").arg(i + 1));
		terminalName->setGeometry(100, 0, 100, 20);//ax,ay,length,height
		verticalLayout->addWidget(terminalName);
		connect(terminalName, SIGNAL(clicked()), this, SLOT(ShowSpeed()));

		

		SwitchControl* pSwitchControl = new SwitchControl(1, i, this, widget);
		pSwitchControl->setGeometry(QRect(9, 28, 30, 15));//margin=9
		pInternalMasterSwitchList[i] = pSwitchControl;
		verticalLayout->addWidget(pSwitchControl);

		QLabel* internalLabel = new QLabel(widget);
		internalLabel->setObjectName(QString("TotalSwitch"));
		internalLabel->setText(QString("全开"));
		internalLabel->setGeometry(QRect(52, 25, 40, 15));

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(0, 46, 250, 80);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(8);
		InternalQGridLayout->setVerticalSpacing(6);
		InternalQGridLayout->setMargin(9);//
		for (int j = 0; j < 6; j++)
		{
			SwitchControl* pSwitchControl = new SwitchControl(2, i * 6 + j, this);
			pSwitchControl->setObjectName(QStringLiteral("SwitchControl%1_%1").arg(i + 1, j + 1));
			pInternalTerminalSwitchList[i * 6 + j] = pSwitchControl;

			QLabel* internalLabel = new QLabel(Internalwidget);
			internalLabel->setObjectName(QString("Phone%1_%1").arg(i + 1, j + 1));
			internalLabel->setText(QString("WIFI %1").arg(j + 1));


			if (j / 3 == 0)
			{
				InternalQGridLayout->addWidget(internalLabel, j % 3, j / 3 + 1, 1, 1);//row column
				InternalQGridLayout->addWidget(pSwitchControl, j % 3, j / 3, 1, 1);
			}
			else
			{
				InternalQGridLayout->addWidget(internalLabel, j % 3, j / 3 + 2, 1, 1);//row column
				InternalQGridLayout->addWidget(pSwitchControl, j % 3, j / 3 + 1, 1, 1);
			}

		}
		verticalLayout->addWidget(Internalwidget);
		widgets.append(widget);

	}

	int count = 0;
	int row = 0;
	int column = 0;
	int flag = 5;
	int index = 0;
	for (int i = 0; i < TerminalCount; i++) {
		if (i >= index) {
			pTerminalLayOut->addWidget(widgets.at(i), row, column);
			widgets.at(i)->setVisible(true);

			count++;
			column++;
			if (column == flag) {
				row++;
				column = 0;
			}
		}

		if (count == (flag * flag)) {
			break;
		}
	}
	pGlobalLayOut->addWidget(pTitleWidget);
	pGlobalLayOut->addWidget(pSwitchButtonWidget);
	pGlobalLayOut->addWidget(pTerminalWidget);
}
//terminalName->resize(122, 15);
//TerminalNameButtons.append(terminalName);
/*
QLabel* terminalName = new QLabel(widget);
terminalName->setObjectName(QString("terminal_label_%1").arg(i + 1));
terminalName->setText(QString("终端 %1").arg(i + 1));
terminalName->setGeometry(70, 0, 122, 15);//ax,ay,length,height
verticalLayout->addWidget(terminalName);
*/
void NewWifiControl::SwitchControl0()
{
	qDebug() << "SwitchControl0";
	
	for (int i = 1; i < 4; i++)
		if (pMasterSwitchList[0]->isToggled())
			pMasterSwitchList[i]->setDisabled(true);
		else
			pMasterSwitchList[i]->setDisabled(false);
	for (int i = 0; i < 150; i++)
	{
		if (pMasterSwitchList[0]->isToggled())
		{
			pInternalTerminalSwitchList[i]->setToggle(true);

		}
		else
			pInternalTerminalSwitchList[i]->setToggle(false);
	}
	for (int i = 0; i < 25; i++)
	{
		if (pMasterSwitchList[0]->isToggled())
			pInternalMasterSwitchList[i]->setDisabled(true);
		else
			pInternalMasterSwitchList[i]->setDisabled(false);
	}
	if (pMasterSwitchList[0]->isToggled())
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#3#%c##", 'A');//全部设备开始下载
		SendMsg(tmp);

	}
	else
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#4#%c##", 'A');//全部设备暂停下载
		SendMsg(tmp);
	}

	//send msg
	//QString NumberStr = ui.NumberEdit_1->text();//电话号码
	//QByteArray ba = NumberStr.toLatin1();
	//qDebug() << "ba.data:"<<ba.data();

}
void NewWifiControl::SwitchControl1()
{
	qDebug() << "SwitchControl1";
	
	for (int i = 0; i < 50; i++)
	{
		if (pMasterSwitchList[1]->isToggled())
		{
			pInternalTerminalSwitchList[i]->setToggle(true);
		}
		else
		{
			pInternalTerminalSwitchList[i]->setToggle(false);
		}
	}
	for (int i = 0; i < 25; i++)
	{
		if (pMasterSwitchList[1]->isToggled())
			pInternalMasterSwitchList[i]->setDisabled(true);
		else
			pInternalMasterSwitchList[i]->setDisabled(false);
	}
	if (pMasterSwitchList[1]->isToggled())
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#3#%c##", 'B');//前50设备开始下载
		SendMsg(tmp);

	}
	else
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#4#%c##", 'B');//前50设备暂停下载
		SendMsg(tmp);
	}
}
//if (i<50)
//被打开
//if (i < 50)
/*else
pInternalTerminalSwitchList[i]->setDisabled(true);*/
//if (i < 50)
//else
//pInternalTerminalSwitchList[i]->setDisabled(false);
void NewWifiControl::SwitchControl2()
{
	qDebug() << "SwitchControl2";
	
	for (int i = 50; i < 100; i++)
	{
		if (pMasterSwitchList[2]->isToggled())
			pInternalTerminalSwitchList[i]->setToggle(true);
		else
			pInternalTerminalSwitchList[i]->setToggle(false);
	}
	for (int i = 0; i < 25; i++)
	{
		if (pMasterSwitchList[2]->isToggled())
			pInternalMasterSwitchList[i]->setDisabled(true);
		else
			pInternalMasterSwitchList[i]->setDisabled(false);
	}
	if (pMasterSwitchList[2]->isToggled())
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#3#%c##", 'C');//50-100设备开始下载
		SendMsg(tmp);

	}
	else
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#4#%c##", 'C');//50-100设备暂停下载
		SendMsg(tmp);
	}
}
void NewWifiControl::SwitchControl3()
{
	qDebug() << "SwitchControl3";

	for (int i = 100; i < 150; i++)
	{
		if (pMasterSwitchList[3]->isToggled())
			pInternalTerminalSwitchList[i]->setToggle(true);
		else
			pInternalTerminalSwitchList[i]->setToggle(false);
	}
	for (int i = 0; i < 25; i++)
	{
		if (pMasterSwitchList[3]->isToggled())
			pInternalMasterSwitchList[i]->setDisabled(true);
		else
			pInternalMasterSwitchList[i]->setDisabled(false);
	}
	if (pMasterSwitchList[2]->isToggled())
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#3#%c##", 'D');//101-150设备开始下载
		SendMsg(tmp);

	}
	else
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#4#%c##", 'D');//101-150设备暂停下载
		SendMsg(tmp);
	}
}

void NewWifiControl::SendMsg(char* data)
{
	//qDebug() << "SendMsg";
	char* sendmsg = (char*)malloc(64);
	memset(sendmsg, 0, sizeof(sendmsg));
	memcpy(sendmsg, data, sizeof(data));
	tcpSocket->write(sendmsg);
	delete sendmsg;
}
void NewWifiControl::SwitchSlot(int type, int num)
{
	qDebug() << "NewWifiControl:***SwitchSlot***;type:" << type << "num:" << num;
	pOperateTimer->stop();
	pOperateTimer->start(1000*60* TimeInterval);
	switch (type)
	{
	case 0:
		if (num == 0)
			SwitchControl0();
		else if (num == 1)
			SwitchControl1();
		else if (num == 2)
			SwitchControl2();
		else
			SwitchControl3();
		break;
	case 1:
		for (int i = 0; i < 6; i++)
			if (pInternalMasterSwitchList[num]->isToggled())
			{
				pInternalTerminalSwitchList[num * 6 + i]->setToggle(true);

			}
			else
			{

				pInternalTerminalSwitchList[num * 6 + i]->setToggle(false);
			}
		if (pInternalMasterSwitchList[num]->isToggled())
		{
			char tmp[32];//命令 id 
			memset(tmp, 0, sizeof(tmp));
			snprintf(tmp, sizeof(tmp) - 1, "#3#%c#%d#", 'A',num+1);//第 num+1 个终端上全部设备开始下载
			SendMsg(tmp);
		}
		else
		{
			char tmp[32];//命令 id 
			memset(tmp, 0, sizeof(tmp));
			snprintf(tmp, sizeof(tmp) - 1, "#4#%c#%d#", 'A',num+1);//第 num+1 个终端上全部设备开始中断下载
			SendMsg(tmp);
		}
		break;
	case 2:
		if (pInternalTerminalSwitchList[num]->isToggled())
		{
			char tmp[32];//命令 id 
			memset(tmp, 0, sizeof(tmp));
			snprintf(tmp, sizeof(tmp) - 1, "#3#%d##", num + 1);
			SendMsg(tmp);
		}
		else
		{
			char tmp[32];//命令 id 
			memset(tmp, 0, sizeof(tmp));
			snprintf(tmp, sizeof(tmp) - 1, "#4#%d##", num + 1);
			SendMsg(tmp);
		}
		break;
	default:
		break;
	}
	if (pWifiSpeed != NULL)
	{
		pWifiSpeed->CheckSwitchSate();
		return;
	}
}
void NewWifiControl::ShowSpeed()
{
	qDebug() << "ShowSpeed";
	if (pWifiSpeed != NULL)
	{
		pWifiSpeed->CheckSwitchSate();
		return;
	}
	pWifiSpeed = new WifiSpeed(this,&pInternalTerminalSwitchList,NULL, tcpSocket);//从远程数据库查询相应数据。
	pWifiSpeed->setAttribute(Qt::WA_DeleteOnClose);
	pWifiSpeed->show();
}
void NewWifiControl::RecordLog()
{
	qDebug() << "RecordLog";
	QVector<int> WorkingDevices;
	for (int i = 0; i < 150; i++)
	{
		if (pInternalTerminalSwitchList[i]->isToggled())
		{
			WorkingDevices.append(i+1);
		}
	}
	if (!WorkingDevices.size())
		return;
	int LastMinute, LastHour;
	QDateTime local(QDateTime::currentDateTime());
	QString hour = local.time().toString("hh");
	QString minute = local.time().toString("mm");
	QString second = local.time().toString("ss");
	int Hour = hour.toInt();
	int Minute = minute.toInt();
	int Second = second.toInt();
	if (Minute < TimeInterval)//跨小时
	{
		LastMinute = 60 - (TimeInterval - Minute);
		if (Hour == 0)
			LastHour = 23;
		else
			LastHour = Hour - 1;
	}
	else //未跨
	{
		LastMinute = Minute - TimeInterval;
		LastHour = Hour;
	}
	int zero = 0;
	QString LastHourStr = LastHour <= 9 ? QString::number(zero) + QString::number(LastHour) : QString::number(LastHour);
	QString LastMinuteStr = LastMinute <= 9 ? QString::number(zero) + QString::number(LastMinute) : QString::number(LastMinute);
	QString HourStr = Hour <= 9 ? QString::number(zero) + QString::number(Hour) : QString::number(Hour);
	QString MinuteStr = Minute <= 9 ? QString::number(zero) + QString::number(Minute) : QString::number(Minute);
	//qDebug() << LastHourStr << ":" << LastMinuteStr << "-" << HourStr << ":" << MinuteStr << endl;

	QString TimeQuantum = LastHourStr + QString(":") + LastMinuteStr + QString("-") + HourStr + QString(":") + MinuteStr;
	//QString TimeQuantum = QString::number(LastHour) + ":"+ QString::number(LastMinute) + QString("-") + QString::number(Hour) + ":" + QString::number(Minute);

	//qDebug() << TimeQuantum << endl;
	pLog->addWifi(TimeQuantum, WorkingDevices);
}

void NewWifiControl::InitWifiSpeedPointer()
{
	pWifiSpeed = NULL;
}