#pragma execution_character_set("utf-8")

#include "NewIphoneControl.h"

#include<QtQuick>
//#include<QML>
//import QtQuick 2.0

NewIphoneControl::NewIphoneControl(QWidget* sigparent,Log* pLog,QWidget* parent, QTcpSocket* tcpSocket)
	:sigparent(sigparent), pLog(pLog),QWidget(parent), tcpSocket(tcpSocket)
{
	ui.setupUi(this);
	SwitchControl* pSwitchControl = NULL;
	TimeInterval = 1;
	pOperateTimer = new QTimer;
	connect(pOperateTimer, SIGNAL(timeout()), this, SLOT(RecordLog()));
	connect(this, SIGNAL(InformParent()), sigparent, SLOT(InitIphonePointer()));

	pOperateTimer->start(1000 * 60 * TimeInterval);//5min
	//initlize switchcontrol pointer
	for (int i = 0; i < 4; i++)
	{
		pSwitchControl = new SwitchControl(0,i,this,this);
		pMasterSwitchList.append(pSwitchControl);
		
		
	}

	for (int i = 0; i < 25; i++)
	{
		pSwitchControl = new SwitchControl(1,i,this,this);
		pInternalMasterSwitchList.append(pSwitchControl);
	}

	for(int i = 0; i < 150;i++ )
	{
		pSwitchControl = new SwitchControl(2,i,this,this);
		pInternalTerminalSwitchList.append(pSwitchControl);
	}


	this->init();
	//this->initForm();
	this->initFormGlobal();
}
/*for (int i = 0; i < 150; i++)
{
		
	qDebug()<<i<<":"<< pInternalTerminalSwitchList[i];
}*/

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

/*Rectangle
{
	width:100
	height:100
	color:"red"
	border.color:"black"
	border.width:5
	radius:10
}*/


NewIphoneControl::~NewIphoneControl()
{
	qDebug() << "NewIphoneControl";
	emit InformParent();
}
/*
delete pTerminalSwitch;
delete pSwitchButtonWidget;
delete pTerminalSwitchLayOut;

delete pTerminal;
delete pTerminalWidget;
delete pTerminalLayOut;

delete pTitle;
delete pFill1;
delete pFill2;
delete pTitleWidget;
delete pTitleLayOut;
delete pGlobalLayOut;
*/
void NewIphoneControl::init()
{
	pGlobalLayOut = new QVBoxLayout;
	pGlobalLayOut->setSpacing(6);//栅格之间的空白
	pGlobalLayOut->setMargin(0);//边缘
	pGlobalLayOut->setObjectName("gridLayout");
	this->setLayout(pGlobalLayOut);
}


//void NewIphoneControl::initForm()
//{
//	/*
//	static float baseWidth = 930;
//	static float baseHeight = 950;
//	static float widgetWidth = this->width();
//	static float widgetHeight = this->height();
//	static float widgetX = this->geometry().x();
//	static float widgetY = this->geometry().y();
//	QRect resizeRect = this->rect();
//	qDebug() << resizeRect << widgetX << widgetY;
//	qDebug() << widgetWidth << widgetHeight ;
//	float horRatio = this->rect().width() / baseWidth;
//	float verRatio = this->rect().height() / baseHeight;
//	*/
//
//	/*
//	 resizeRect.setX(widgetX*horRatio);
//	 resizeRect.setY(widgetY*verRatio);
//
//	 //resize the verticalLayoutWidget
//	 resizeRect.setWidth(widgetWidth*horRatio);
//	 resizeRect.setHeight(widgetHeight*verRatio);
//	 //set Geometry
//	 resizeWidget->setGeometry(resizeRect);
//	*/
//
//	
//	pTitleWidget = new QWidget(this);
//	pTitleWidget->setObjectName(QStringLiteral("TitleWidget"));
//	pTitleWidget->setGeometry(QRect(0, 0, 900, 36));
//	pTitle = new QLabel(pTitleWidget);
//	pTitle->setObjectName(QString("GlobalTitle"));
//	pTitle->setText(QString("手机拨打控制"));
//	pFill1 = new QLabel(pTitleWidget);
//	pFill1->setObjectName(QString("FillLabel1"));
//	pFill2 = new QLabel(pTitleWidget);
//	pFill2->setObjectName(QString("FillLabel2"));
//	
//	/*
//	pTitle = new QLabel(this);
//	pTitle->setObjectName(QString("GlobalTitle"));
//	pTitle->setText(QString("手机拨打控制"));
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
//	pFill1->setGeometry(20, 0, 340, 36);
//	pTitle->setGeometry(360, 0, 220, 36);
//	pFill2->setGeometry(580, 0, 340, 36);
//	//pFill->setText(QString("系统自检"));
//	QColor col1 = QColor(255, 211, 155);
//	if (col1.isValid()) {
//		QString qss = QString("background-color: %1").arg(col1.name());
//		pFill1->setStyleSheet(qss);
//		pFill2->setStyleSheet(qss);
//		pTitle->setStyleSheet(qss);
//	}
//
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
//	pTerminalSwitchLayOut->setSpacing(6);//栅格之间的空白
//	pTerminalSwitchLayOut->setMargin(0);//边缘
//	pTerminalSwitchLayOut->setObjectName("TerminalSwitchLayout");
//	pSwitchButtonWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
//	pSwitchButtonWidget->setMaximumHeight(60);
//	pSwitchButtonWidget->setLayout(pTerminalSwitchLayOut);
//
//	pTerminalSwitch = new terminal(3, pSwitchButtonWidget);
//	//pTerminal->setGeometry();
//	pTerminalSwitchLayOut->addWidget(pTerminalSwitch);
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
//	//pTerminalWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//
//	pTerminal = new terminal(0,pTerminalWidget);
//	//pTerminal->setGeometry();
//	pTerminalLayOut->addWidget(pTerminal);
//
//	
//	//pGlobalLayOut->addLayout(pTitleLayOut);
//	pGlobalLayOut->addWidget(pTitleWidget);
//	pGlobalLayOut->addWidget(pSwitchButtonWidget);
//	pGlobalLayOut->addWidget(pTerminalWidget);
//
//
//	//qDebug() << "TitleWidget width:" << pTitleWidget->width() << "height:" << pTitleWidget->height();
//	qDebug() << "SwitchButtonWidget width:" << pSwitchButtonWidget->width() << "height:" << pSwitchButtonWidget->height();
//	qDebug() << "TerminalWidget width:" << pTerminalWidget->width() << "height:" << pTerminalWidget->height();
//	qDebug() << "ThisWidget width:" << this->width() << "height:" << this->height();
//	/*pGlobalLayOut->addLayout(pTitleLayOut);
//	pGlobalLayOut->addLayout(pTerminalSwitchLayOut);
//	pGlobalLayOut->addLayout(pGlobalLayOut);*/
//}


void NewIphoneControl::initFormGlobal()
{
	pTitleWidget = new QWidget(this);
	pTitleWidget->setObjectName(QStringLiteral("TitleWidget"));
	pTitleWidget->setGeometry(QRect(0, 0, 900, 36));
	pTitle = new QLabel(pTitleWidget);
	pTitle->setObjectName(QString("GlobalTitle"));
	pTitle->setText(QString("手机拨打控制"));
	pFill1 = new QLabel(pTitleWidget);
	pFill1->setObjectName(QString("FillLabel1"));
	pFill2 = new QLabel(pTitleWidget);
	pFill2->setObjectName(QString("FillLabel2"));

	
	QFont font1;
	font1.setPointSize(30);
	pTitle->setFont(font1);
	pTitle->setTextFormat(Qt::AutoText);
	pFill1->setGeometry(20, 0, 340, 36);
	pTitle->setGeometry(360, 0, 220, 36);
	pFill2->setGeometry(580, 0, 340, 36);
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
		SwitchControl* pSwitchControl = new SwitchControl(0,j,this,this);
		
		pMasterSwitchList[j] = pSwitchControl;
		QLabel* internalLabel = new QLabel();
		internalLabel->setObjectName(QString("PhoneTotalSwitch%1_%1").arg(j));
		if(j == 0)
		{
			internalLabel->setText(QString("全部手机拨打开关"));
			pTerminalSwitchLayOut->addWidget(internalLabel, 0, 1, 1, 1);//row column
			pTerminalSwitchLayOut->addWidget(pSwitchControl, 0, 0, 1, 1);
		}
		else if(j == 1)
		{
			internalLabel->setText(QString("1-50拨打开关"));
			pTerminalSwitchLayOut->addWidget(internalLabel, 0, 3, 1, 1);//row column
			pTerminalSwitchLayOut->addWidget(pSwitchControl, 0, 2, 1, 1);
		}
		else if(j == 2)
		{
			internalLabel->setText(QString("51-100拨打开关"));
			pTerminalSwitchLayOut->addWidget(internalLabel, 1, 1, 1, 1);//row column
			pTerminalSwitchLayOut->addWidget(pSwitchControl, 1, 0, 1, 1);
		}
		else
		{
			internalLabel->setText(QString("101-150拨打开关"));
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

		QLabel* terminalName = new QLabel(widget);
		terminalName->setObjectName(QString("terminal_label_%1").arg(i + 1));
		terminalName->setText(QString("终端 %1").arg(i + 1));
		terminalName->setGeometry(100, 0, 122, 15);//ax,ay,length,height
		verticalLayout->addWidget(terminalName);

		SwitchControl* pSwitchControl = new SwitchControl(1,i, this,widget);
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
			SwitchControl* pSwitchControl = new SwitchControl(2,i*6+j,this);
			pSwitchControl->setObjectName(QStringLiteral("SwitchControl%1_%1").arg(i + 1, j + 1));
			pInternalTerminalSwitchList[i * 6 + j] = pSwitchControl;
			
			QLabel* internalLabel = new QLabel(Internalwidget);
			internalLabel->setObjectName(QString("Phone%1_%1").arg(i + 1, j + 1));
			internalLabel->setText(QString("手机 %1").arg(j + 1));
			

			if (j / 3 == 0)
			{
				InternalQGridLayout->addWidget(internalLabel, j % 3, j / 3 + 1, 1, 1);//row column
				InternalQGridLayout->addWidget(pSwitchControl, j % 3, j / 3, 1, 1);
			}
			else
			{
				InternalQGridLayout->addWidget(internalLabel, j % 3, j / 3 + 2, 1, 1);//row column
				InternalQGridLayout->addWidget(pSwitchControl, j % 3, j / 3+1, 1, 1);
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
/*qDebug() << "SwitchButtonWidget width:" << pSwitchButtonWidget->width() << "height:" << pSwitchButtonWidget->height();
qDebug() << "TerminalWidget width:" << pTerminalWidget->width() << "height:" << pTerminalWidget->height();
qDebug() << "ThisWidget width:" << this->width() << "height:" << this->height();*/
//IphoneLabels.append(internalLabel);
//InternalQGridLayout->addWidget(pInternalTerminalSwitchList[i*TerminalCount+j], j % 3, j / 3, 1, 1);
//InternalQGridLayout->addWidget(pInternalTerminalSwitchList[i * TerminalCount + j], j % 3, j / 3 + 1, 1, 1);
//internalLabel->setGeometry(25, 9 + 18 * i, 30, 12);
//internalLabel->resize();
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
//pTerminalWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//pTerminal = new terminal(0, pTerminalWidget);
//pTerminal->setGeometry();
//pTerminalLayOut->addWidget(pTerminal);
//pGlobalLayOut->addLayout(pTitleLayOut);
//qDebug() << "TitleWidget width:" << pTitleWidget->width() << "height:" << pTitleWidget->height();
/*pGlobalLayOut->addLayout(pTitleLayOut);
pGlobalLayOut->addLayout(pTerminalSwitchLayOut);
pGlobalLayOut->addLayout(pGlobalLayOut);*/
//QString videoType = "1_16";
/*
QLabel* widget = new QLabel;
widget->setObjectName(QString("video%1").arg(i + 1));
widget->installEventFilter(this);
widget->setFocusPolicy(Qt::StrongFocus);
widget->setAlignment(Qt::AlignCenter);

//二选一可以选择显示文字,也可以选择显示背景图片
widget->setText(QString("终端 %1").arg(i + 1));
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
widgets.append(widget);*/
//IphoneLabels.append(internalLabel);
//pSwitchControl->setDisabled(true);
//被点发出toggled信号 改变按钮状态
//connect(pSwitchControl, SIGNAL(toggled(int)), this, SLOT(SwitchControl0()));
//connect(pSwitchControl, SIGNAL(toggled(bool)), this, SLOT(SwitchControl1()));
//connect(pSwitchControl, SIGNAL(toggled(bool)), this, SLOT(SwitchControl2()));
//connect(pSwitchControl, SIGNAL(toggled(bool)), this, SLOT(SwitchControl3()));
//pTerminalSwitch = new terminal(3, pSwitchButtonWidget);

//pTerminalSwitchLayOut->addWidget(pTerminalSwitch);

//pSwitchButtonWidget->setGeometry(QRect(20, 40, 900, 100));
/*
pSwitchButtonLayOut = new QGridLayout;
pSwitchButtonLayOut->setSpacing(6);//栅格之间的空白
pSwitchButtonLayOut->setMargin(0);//边缘
pSwitchButtonLayOut->setObjectName("gridLayout");
pSwitchButtonWidget->setLayout(pSwitchButtonLayOut);


pTotalSwitch = new QLabel(pSwitchButtonWidget);
p1_50Switch = new QLabel(pSwitchButtonWidget);
p51_100Switch = new QLabel(pSwitchButtonWidget);
p101_150Switch = new QLabel(pSwitchButtonWidget);
pTotalSwitch->setObjectName(QStringLiteral("TotalSwitch"));
p1_50Switch->setObjectName(QStringLiteral("1_50Switch"));
p51_100Switch->setObjectName(QStringLiteral("51_100Switch"));
p101_150Switch->setObjectName(QStringLiteral("101_150Switch"));
pTotalSwitch->setGeometry(QRect(20, 40, 900, 100));
*/
//widget->setAlignment(Qt::AlignCenter);
//二选一可以选择显示文字,也可以选择显示背景图片
//widget->setText(QString("终端 %1").arg(i + 1));
//widget->setWindowTitle(QString("终端 %1").arg(i + 1));;
//QVBoxLayoutList.append(verticalLayout);
//terminalName->resize(122, 15);
//TerminalNameLabels.append(terminalName);
//LightButton* pLightButton = new LightButton();
//pSwitchControl->setObjectName(QStringLiteral("TotalSwitchControl"));
//SwitchControlList.append(pSwitchControl);
//IphoneLabels.append(internalLabel);
//InternalQGridLayoutList.append(InternalQGridLayout);
////绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
//QPainter painter(this);
//painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//LightButton* pLightButton = new LightButton();
/*qDebug() << "size:" << pInternalTerminalSwitchList.size();
qDebug() << "pInternalTerminalSwitchList[i * TerminalCount + j]:" << i * 6 + j <<":"<< pInternalTerminalSwitchList[i * 6 + j];*/
//SwitchControlList.append(pSwitchControl);
//pLightButton->setGeometry(QRect(540, 370, 51, 16));
void NewIphoneControl::SwitchControl0()
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
		snprintf(tmp, sizeof(tmp) - 1, "#1#%c##", 'A');//全部设备开始拨打
		SendMsg(tmp);

	}
	else
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#2#%c##", 'A');//全部设备暂停拨打
		SendMsg(tmp);
	}

	//send msg
	//QString NumberStr = ui.NumberEdit_1->text();//电话号码
	//QByteArray ba = NumberStr.toLatin1();
	//qDebug() << "ba.data:"<<ba.data();

}
void NewIphoneControl::SwitchControl1()
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
		snprintf(tmp, sizeof(tmp) - 1, "#1#%c##", 'B');//前50设备开始拨打
		SendMsg(tmp);

	}
	else
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#2#%c##", 'B');//前50设备暂停拨打
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
void NewIphoneControl::SwitchControl2()
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
		snprintf(tmp, sizeof(tmp) - 1, "#1#%c##", 'C');//前51-100设备开始拨打
		SendMsg(tmp);

	}
	else
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#2#%c##", 'C');//前51-100设备暂停拨打
		SendMsg(tmp);
	}
}
void NewIphoneControl::SwitchControl3()
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
	if (pMasterSwitchList[3]->isToggled())
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#1#%c##", 'D');//前101-150设备开始拨打
		SendMsg(tmp);

	}
	else
	{
		char tmp[32];//命令 id 
		memset(tmp, 0, sizeof(tmp));
		snprintf(tmp, sizeof(tmp) - 1, "#2#%c##", 'D');//前101-150设备暂停拨打
		SendMsg(tmp);
	}
}

void NewIphoneControl::SendMsg(char* data)
{
	//qDebug() << "SendMsg";
	char* sendmsg = (char*)malloc(64);
	memset(sendmsg, 0, sizeof(sendmsg));
	memcpy(sendmsg, data, sizeof(data));
	tcpSocket->write(sendmsg);
	delete sendmsg;
}
void NewIphoneControl::SwitchSlot(int type,int num)
{
	qDebug() << "NewIphoneControl:***SwitchSlot***;type:"<<type<<"num:"<<num;
	pOperateTimer->stop();
	pOperateTimer->start(1000 * 60 * TimeInterval);
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
				pInternalTerminalSwitchList[num * 6 + i]->setToggle(true);
			else
				pInternalTerminalSwitchList[num * 6 + i]->setToggle(false);
		if (pInternalMasterSwitchList[num]->isToggled())
		{
			char tmp[32];//命令 id 
			memset(tmp, 0, sizeof(tmp));
			snprintf(tmp, sizeof(tmp) - 1, "#1#%c#%d#", 'A', num + 1);//第 num+1 个终端上全部设备开始拨打
			SendMsg(tmp);
		}
		else
		{
			char tmp[32];//命令 id 
			memset(tmp, 0, sizeof(tmp));
			snprintf(tmp, sizeof(tmp) - 1, "#2#%c#%d#", 'A', num + 1);//第 num+1 个终端上全部设备开始中断拨打
			SendMsg(tmp);
		}
		break;
	case 2:
		if (pInternalTerminalSwitchList[num]->isToggled())
		{
			char tmp[32];//命令 id 
			memset(tmp, 0, sizeof(tmp));
			snprintf(tmp, sizeof(tmp) - 1, "#1#%d##", num + 1);
			SendMsg(tmp);
		}
		else
		{
			char tmp[32];//命令 id 
			memset(tmp, 0, sizeof(tmp));
			snprintf(tmp, sizeof(tmp) - 1, "#2#%d##", num + 1);
			SendMsg(tmp);
		}
		break;
	default:
		break;
	}
}
void NewIphoneControl::RecordLog()
{
	qDebug() << "RecordLog";
	QVector<int> WorkingDevices;
	for (int i = 0; i < 150; i++)
	{
		if (pInternalTerminalSwitchList[i]->isToggled())
		{
			WorkingDevices.append(i + 1);
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

	QString TimeQuantum = LastHourStr + QString(":") +LastMinuteStr+  QString("-") + HourStr + QString(":") + MinuteStr;
	//QString TimeQuantum = QString::number(LastHour) + ":"+ QString::number(LastMinute) + QString("-") + QString::number(Hour) + ":" + QString::number(Minute);

	//qDebug() << TimeQuantum << endl;
	pLog->addIphone(TimeQuantum, WorkingDevices);
}

