#pragma execution_character_set("utf-8")
#include"terminal.h"
/*
terminal::terminal(QString name, int ButtonNum, int QLabelNum, QWidget* parent) : QWidget(parent)
{
	int i;
	//pOverallGridLayout=new 
	pBoundaryWidget = new QWidget(parent);//外围widget
	pInternalQVBoxLayout = new QVBoxLayout(pBoundaryWidget);//内部垂直布局
	pInternalWidget =new QWidget(pBoundaryWidget);//内部widget
	pName=new QLabel();//终端名称
	pName->setText(name);
	PLightButton = (LightButton**)malloc(ButtonNum * sizeof(LightButton*));//创建指示灯对象
	for (i = 0; i < ButtonNum; i++)
		PLightButton[i] = new LightButton(pBoundaryWidget);
		PLightButton[i]->setAlarmColor(QColor(0, 255, 0));
		PLightButton[i]->HoldAram();

}
*/
terminal::terminal(QWidget* parent) :QWidget(parent)
{
	this->initControl();
	this->initForm();
	this->showterminal();
}
/*int i;
int ButtonNum = 6;*/
//pOverallGridLayout=new 
//pBoundaryWidget = new QWidget(parent);//外围widget
//pInternalQVBoxLayout = new QVBoxLayout(pBoundaryWidget);//内部垂直布局
//pInternalWidget = new QWidget(pBoundaryWidget);//内部widget
//pName = new QLabel();//终端名称
//QString name = "终端1";
//pName->setText(name);
//PLightButton = (LightButton**)malloc(ButtonNum * sizeof(LightButton*));//创建指示灯对象
//for (i = 0; i < ButtonNum; i++)
//	PLightButton[i] = new LightButton(pBoundaryWidget);
//PLightButton[i]->setAlarmColor(QColor(0, 255, 0));
//PLightButton[i]->HoldAram();
terminal::~terminal()
{
	qDebug() << "~terminal";
	
}
/*
for (int i = 0; i < LightButtonList.size(); i++)
	delete LightButtonList[i];
for (int i = 0; i < WifiLabels.size(); i++)
	delete WifiLabels[i];
for (int i = 0; i < IphoneLabels.size(); i++)
	delete IphoneLabels[i];
for (int i = 0; i < SwitchControlList.size(); i++)
	delete SwitchControlList[i];
for (int i = 0; i < InternalQGridLayoutList.size(); i++)
	delete InternalQGridLayoutList[i];
for (int i = 0; i < widgets.size(); i++)
	delete widgets[i];
for (int i = 0; i < TerminalNameLabels.size(); i++)
	delete TerminalNameLabels[i];
for (int i = 0; i < TerminalNameButtons.size(); i++)
	delete TerminalNameButtons[i];
for (int i = 0; i < QVBoxLayoutList.size(); i++)
	delete QVBoxLayoutList[i];
*/
	
terminal::terminal(int TerminalType, QWidget* parent )//0:iphone ,1:wifi, 2:wifispeed ,3:iphone switch ,4:wifi switch
{
	this->initControl();
	switch (TerminalType)
	{
	case 0:
		this->initFormIphone();
		break;
	case 1:
		this->initFormWifi();
		break;
	case 2:
		this->initFormWifiSpeed();
		break;
	case 3:
		this->initFormIphoneSwitch();
		break;
	case 4:
		this->initFormWifiSwitch();
		break;
	default:
		break;
	}
	this->showterminal();
}
terminal::terminal(int TerminalType, QTcpSocket* tcpSocket,QWidget* parent   )
{
	this->initControl();
	switch (TerminalType)
	{
	case 0:
		this->initFormIphone();
		break;
	case 1:
		this->initFormWifi();
		break;
	case 2:
		this->initFormWifiSpeed();
		break;
	case 3:
		this->initFormIphoneSwitch();
		break;
	case 4:
		this->initFormWifiSwitch();
		break;
	default:
		break;
	}
	this->showterminal();
}
void terminal::initControl()
{
	gridLayout = new QGridLayout;
	gridLayout->setSpacing(6);//栅格之间的空白
	gridLayout->setMargin(0);//边缘
	gridLayout->setObjectName("gridLayout");
	this->setLayout(gridLayout);
}
void terminal::initFormIphoneSwitch()
{
	TerminalCount = 1;
	for (int i = 0; i < TerminalCount; i++) {
		
		QWidget* widget = new QWidget;
		widget->setObjectName(QString("terminal%1").arg(i + 1));
		widget->installEventFilter(this);
		widget->setFocusPolicy(Qt::StrongFocus);
		
		QColor col1 = QColor(255, 211, 155);
		if (col1.isValid()) {
			QString qss = QString("background-color: %1").arg(col1.name());
			widget->setStyleSheet(qss);
		}
		

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(0, 10, 900, 60);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(6);
		InternalQGridLayout->setVerticalSpacing(6);
		InternalQGridLayout->setMargin(9);//
		InternalQGridLayoutList.append(InternalQGridLayout);
		for (int j = 0; j < 4; j++)
		{
			
			SwitchControl* pSwitchControl = new SwitchControl(Internalwidget);
		
			pSwitchControl->setObjectName(QStringLiteral("TotalSwitchControl%1_%1").arg(i + 1,j+1));
			//pSwitchControl->setGeometry(QRect(9, 48, 50, 15));//margin=9
			SwitchControlList.append(pSwitchControl);
			
			QLabel* internalLabel = new QLabel(Internalwidget);
			internalLabel->setObjectName(QString("PhoneTotalSwitch%1_%1").arg(i + 1,j+1));
			if (j == 0)
			{
				//pSwitchControl->setDisabled(true);
				internalLabel->setText(QString("全部手机拨打开关"));
				InternalQGridLayout->addWidget(internalLabel, 0, 1, 1, 1);//row column
				InternalQGridLayout->addWidget(pSwitchControl, 0, 0, 1, 1);
			}
			else if (j == 1)
			{
				internalLabel->setText(QString("1-50拨打开关"));
				InternalQGridLayout->addWidget(internalLabel, 0, 3, 1, 1);//row column
				InternalQGridLayout->addWidget(pSwitchControl, 0, 2, 1, 1);
			}
			else if (j == 2)
			{
				internalLabel->setText(QString("51-100拨打开关"));
				InternalQGridLayout->addWidget(internalLabel, 1, 1, 1, 1);//row column
				InternalQGridLayout->addWidget(pSwitchControl, 1, 0, 1, 1);
			}
			else
			{
				internalLabel->setText(QString("101-150拨打开关"));
				InternalQGridLayout->addWidget(internalLabel, 1, 3, 1, 1);//row column
				InternalQGridLayout->addWidget(pSwitchControl, 1, 2, 1, 1);
			}
			IphoneLabels.append(internalLabel);	

		}
		//verticalLayout->addWidget(Internalwidget);
		widgets.append(widget);

	}
}
/*QVBoxLayout* verticalLayout = new QVBoxLayout();
verticalLayout->setObjectName(QString("verticalLayout%1").arg(i + 1));
verticalLayout->setSpacing(6);
QVBoxLayoutList.append(verticalLayout);*/

//QLabel* terminalName = new QLabel(widget);
//terminalName->setObjectName(QString("terminal_label_%1").arg(i + 1));
//terminalName->setText(QString("终端 %1").arg(i + 1));
//terminalName->setGeometry(70, 0, 122, 15);//ax,ay,length,height
////terminalName->resize(122, 15);
//TerminalNameLabels.append(terminalName);
//verticalLayout->addWidget(terminalName);

//SwitchControl* pSwitchControl = new SwitchControl(widget);
////LightButton* pLightButton = new LightButton();
//pSwitchControl->setObjectName(QStringLiteral("TotalSwitchControl"));
//pSwitchControl->setGeometry(QRect(9, 48, 30, 10));//margin=9
//SwitchControlList.append(pSwitchControl);
//verticalLayout->addWidget(pSwitchControl);

//QLabel* internalLabel = new QLabel(widget);
//internalLabel->setObjectName(QString("TotalSwitch"));
//internalLabel->setText(QString("全开"));
//internalLabel->setGeometry(QRect(52, 45, 30, 13));
//IphoneLabels.append(internalLabel);
void terminal::initFormWifiSwitch()
{
	TerminalCount = 1;
	for (int i = 0; i < TerminalCount; i++) {

		QWidget* widget = new QWidget;
		widget->setObjectName(QString("terminal%1").arg(i + 1));
		widget->installEventFilter(this);
		widget->setFocusPolicy(Qt::StrongFocus);

		QColor col1 = QColor(255, 211, 155);
		if (col1.isValid()) {
			QString qss = QString("background-color: %1").arg(col1.name());
			widget->setStyleSheet(qss);
		}
		

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(0, 10, 900, 60);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(6);
		InternalQGridLayout->setVerticalSpacing(6);
		InternalQGridLayout->setMargin(9);//
		InternalQGridLayoutList.append(InternalQGridLayout);
		for (int j = 0; j < 4; j++)
		{

			SwitchControl* pSwitchControl = new SwitchControl(Internalwidget);

			pSwitchControl->setObjectName(QStringLiteral("TotalSwitchControl%1_%1").arg(i + 1, j + 1));
			//pSwitchControl->setGeometry(QRect(9, 48, 50, 15));//margin=9
			SwitchControlList.append(pSwitchControl);

			QLabel* internalLabel = new QLabel(Internalwidget);
			internalLabel->setObjectName(QString("PhoneTotalSwitch%1_%1").arg(i + 1, j + 1));
			if (j == 0)
			{
				internalLabel->setText(QString("全部WIFI开关"));
				InternalQGridLayout->addWidget(internalLabel, 0, 1, 1, 1);//row column
				InternalQGridLayout->addWidget(pSwitchControl, 0, 0, 1, 1);
			}
			else if (j == 1)
			{
				internalLabel->setText(QString("1-50WIFI开关"));
				InternalQGridLayout->addWidget(internalLabel, 0, 3, 1, 1);//row column
				InternalQGridLayout->addWidget(pSwitchControl, 0, 2, 1, 1);
			}
			else if (j == 2)
			{
				internalLabel->setText(QString("51-100WIFI开关"));
				InternalQGridLayout->addWidget(internalLabel, 1, 1, 1, 1);//row column
				InternalQGridLayout->addWidget(pSwitchControl, 1, 0, 1, 1);
			}
			else
			{
				internalLabel->setText(QString("101-150WIFI开关"));
				InternalQGridLayout->addWidget(internalLabel, 1, 3, 1, 1);//row column
				InternalQGridLayout->addWidget(pSwitchControl, 1, 2, 1, 1);
			}
			IphoneLabels.append(internalLabel);

		}
		widgets.append(widget);

	}
}
void terminal::initFormIphone()
{
	TerminalCount = 25;
	//QString videoType = "1_16";

	for (int i = 0; i < TerminalCount; i++) {
		


		QWidget* widget = new QWidget;
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
		QVBoxLayoutList.append(verticalLayout);

		QLabel* terminalName = new QLabel(widget);
		terminalName->setObjectName(QString("terminal_label_%1").arg(i + 1));
		terminalName->setText(QString("终端 %1").arg(i + 1));
		terminalName->setGeometry(70, 0, 122, 15);//ax,ay,length,height
		//terminalName->resize(122, 15);
		TerminalNameLabels.append(terminalName);
		verticalLayout->addWidget(terminalName);

		SwitchControl* pSwitchControl = new SwitchControl(widget);
		//LightButton* pLightButton = new LightButton();
		pSwitchControl->setObjectName(QStringLiteral("TotalSwitchControl"));
		pSwitchControl->setGeometry(QRect(9, 28, 30, 10));//margin=9
		SwitchControlList.append(pSwitchControl);
		verticalLayout->addWidget(pSwitchControl);

		QLabel* internalLabel = new QLabel(widget);
		internalLabel->setObjectName(QString("TotalSwitch"));
		internalLabel->setText(QString("全开"));
		internalLabel->setGeometry(QRect(52, 25, 30, 13));
		IphoneLabels.append(internalLabel);

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(0, 46, 180, 60);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(6);
		InternalQGridLayout->setVerticalSpacing(3); 
		InternalQGridLayout->setMargin(9);//
		InternalQGridLayoutList.append(InternalQGridLayout);
		for (int j = 0; j < 6; j++)
		{
		    SwitchControl* pSwitchControl = new SwitchControl(Internalwidget);
			pSwitchControl->setObjectName(QStringLiteral("SwitchControl%1_%1").arg(i + 1, j + 1));
			SwitchControlList.append(pSwitchControl);
			QLabel* internalLabel = new QLabel(Internalwidget);
			internalLabel->setObjectName(QString("Phone%1_%1").arg(i + 1, j + 1));
			internalLabel->setText(QString("手机 %1").arg(j + 1));
			IphoneLabels.append(internalLabel);
			
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
}
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
//widget->setAlignment(Qt::AlignCenter);

//二选一可以选择显示文字,也可以选择显示背景图片
//widget->setText(QString("终端 %1").arg(i + 1));
//widget->setWindowTitle(QString("终端 %1").arg(i + 1));;
////绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
//QPainter painter(this);
//painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//LightButton* pLightButton = new LightButton();
//pLightButton->setGeometry(QRect(540, 370, 51, 16));
//internalLabel->setGeometry(25, 9 + 18 * i, 30, 12);
//internalLabel->resize();
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
void terminal::initFormWifi()
{
	TerminalCount = 25;

	for (int i = 0; i < TerminalCount; i++) {
		

		QWidget* widget = new QWidget;
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
		verticalLayout->setSpacing(0);
		QVBoxLayoutList.append(verticalLayout);

		QPushButton* terminalName = new QPushButton(widget);
		terminalName->setObjectName(QString("terminal_label_%1").arg(i + 1));
		terminalName->setText(QString("终端 %1").arg(i + 1));
		terminalName->setGeometry(40, 0, 122, 15);//ax,ay,length,height
		//terminalName->resize(122, 15);
		TerminalNameButtons.append(terminalName);
		verticalLayout->addWidget(terminalName);
		connect(terminalName, SIGNAL(clicked()),this,SLOT(ShowSpeed()));

		SwitchControl* pSwitchControl = new SwitchControl(widget);
		//LightButton* pLightButton = new LightButton();
		pSwitchControl->setObjectName(QStringLiteral("TotalSwitchControl"));
		pSwitchControl->setGeometry(QRect(9, 28, 30, 10));//margin=9
		SwitchControlList.append(pSwitchControl);
		verticalLayout->addWidget(pSwitchControl);

		QLabel* internalLabel = new QLabel(widget);
		internalLabel->setObjectName(QString("TotalSwitch"));
		internalLabel->setText(QString("全开"));
		internalLabel->setGeometry(QRect(52, 25, 30, 13));
		IphoneLabels.append(internalLabel);

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(0, 46, 180, 60);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(6);
		InternalQGridLayout->setVerticalSpacing(6);
		InternalQGridLayout->setMargin(9);//
		InternalQGridLayoutList.append(InternalQGridLayout);
		for (int j = 0; j < 6; j++)
		{
			
			SwitchControl* pSwitchControl = new SwitchControl(Internalwidget);
			pSwitchControl->setObjectName(QStringLiteral("SwitchControl%1_%1").arg(i + 1, j + 1));
			SwitchControlList.append(pSwitchControl);
			QLabel* internalLabel = new QLabel(Internalwidget);
			internalLabel->setObjectName(QString("Phone%1_%1").arg(i + 1, j + 1));
			internalLabel->setText(QString("WIFI%1").arg(j + 1));
			IphoneLabels.append(internalLabel);

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
}

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
//QWidget* widget = new ButtonQWidget;
//connect(widget, SIGNAL(pressed()),widget,SLOT(ButtonQWidget::initFormWifiSpeed));
//widget->setAlignment(Qt::AlignCenter);

//二选一可以选择显示文字,也可以选择显示背景图片
//widget->setText(QString("终端 %1").arg(i + 1));
//widget->setWindowTitle(QString("终端 %1").arg(i + 1));;
/*
QLabel* terminalName = new QLabel(widget);
terminalName->setObjectName(QString("terminal_label_%1").arg(i + 1));
terminalName->setText(QString("终端 %1").arg(i + 1));
terminalName->setGeometry(70, 0, 122, 15);//ax,ay,length,height
//terminalName->resize(122, 15);
TerminalNameLabels.append(terminalName);
verticalLayout->addWidget(terminalName);
*/
////绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
//QPainter painter(this);
//painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//LightButton* pLightButton = new LightButton();
//pLightButton->setGeometry(QRect(540, 370, 51, 16));
//internalLabel->setGeometry(25, 9 + 18 * i, 30, 12);
//internalLabel->resize();
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
void terminal::initFormWifiSpeed()
{
	qDebug() << "initFormWifiSpeed";
	TerminalCount = 25;
	QString videoType = "1_16";

	for (int i = 0; i < TerminalCount; i++) {
		


		QWidget* widget = new QWidget;
		widget->setObjectName(QString("terminal%1").arg(i + 1));
		widget->installEventFilter(this);
		widget->setFocusPolicy(Qt::StrongFocus);
		widget->setWindowTitle(QString("终端 %1").arg(i + 1));;
		QColor col1 = QColor(173, 216, 230);
		if (col1.isValid()) {
			QString qss = QString("background-color: %1").arg(col1.name());
			widget->setStyleSheet(qss);
		}
		QVBoxLayout* verticalLayout = new QVBoxLayout();
		verticalLayout->setObjectName(QString("verticalLayout%1").arg(i + 1));
		verticalLayout->setSpacing(6);
		QVBoxLayoutList.append(verticalLayout);

		QLabel* terminalName = new QLabel(widget);
		terminalName->setObjectName(QString("terminal_label_%1").arg(i + 1));
		terminalName->setText(QString("终端 %1").arg(i + 1));
		terminalName->setGeometry(50, 0, 122, 15);//ax,ay,length,height
		TerminalNameLabels.append(terminalName);

		verticalLayout->addWidget(terminalName);

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(1, 22, 140, 120);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(6);
		InternalQGridLayout->setVerticalSpacing(6);
		InternalQGridLayout->setMargin(9);
		InternalQGridLayoutList.append(InternalQGridLayout);
		for (int j = 0; j < 12; j++)
		{
			LightButton* pLightButton = new LightButton();
			pLightButton->setObjectName(QStringLiteral("lightButton%1_%1").arg(i + 1, j + 1));
			LightButtonList.append(pLightButton);
			QLabel* internalLabel = new QLabel(Internalwidget);
			if (j <= 5)
			{
				internalLabel->setObjectName(QString("Phonelabe%1_%2").arg(i + 1, j + 1));
				internalLabel->setText(QString("手机 %1").arg(j + 1));
				IphoneLabels.append(internalLabel);

			}
			else
			{
				internalLabel->setObjectName(QString("WifiLabel%1_%2").arg(i + 1, j % 6 + 1));
				internalLabel->setText(QString("WiFi %1").arg(j % 6 + 1));
				WifiLabels.append(internalLabel);
			}

			if (j / 6 == 0)
			{
				InternalQGridLayout->addWidget(internalLabel, j % 6, j / 6 + 1, 1, 1);//row column
				InternalQGridLayout->addWidget(pLightButton, j % 6, j / 6, 1, 1);
			}
			else
			{
				InternalQGridLayout->addWidget(internalLabel, j % 6, j / 6 + 2, 1, 1);//row column
				InternalQGridLayout->addWidget(pLightButton, j % 6, j / 6 + 1, 1, 1);
			}

		}
		verticalLayout->addWidget(Internalwidget);



		widgets.append(widget);

	}
}
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
//widget->setAlignment(Qt::AlignCenter);

//二选一可以选择显示文字,也可以选择显示背景图片
//widget->setText(QString("终端 %1").arg(i + 1));
//terminalName->resize(122, 15);
////绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
//QPainter painter(this);
//painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//pLightButton->setGeometry(QRect(540, 370, 51, 16));
//internalLabel->setGeometry(25, 9 + 18 * i, 30, 12);
//internalLabel->resize();
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
void terminal::initForm()
{
	TerminalCount = 25;
	QString videoType = "1_16";

	for (int i = 0; i < TerminalCount; i++) {
	

		QWidget* widget = new QWidget;
		widget->setObjectName(QString("terminal%1").arg(i + 1));
		widget->installEventFilter(this);
		widget->setFocusPolicy(Qt::StrongFocus);
		widget->setWindowTitle(QString("终端 %1").arg(i + 1));;
		QColor col1 = QColor(173, 216, 230);
		if (col1.isValid()) {
			QString qss = QString("background-color: %1").arg(col1.name());
			widget->setStyleSheet(qss);
		}
		QVBoxLayout* verticalLayout = new QVBoxLayout();
		verticalLayout->setObjectName(QString("verticalLayout%1").arg(i+1));
		verticalLayout->setSpacing(6);
		QVBoxLayoutList.append(verticalLayout);

		QLabel* terminalName = new QLabel(widget);
		terminalName->setObjectName(QString("terminal_label_%1").arg(i + 1));
		terminalName->setText(QString("终端 %1").arg(i + 1));
		terminalName->setGeometry(50,0,122,15);//ax,ay,length,height
		//terminalName->resize(122, 15);
		TerminalNameLabels.append(terminalName);

		verticalLayout->addWidget(terminalName);

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(1,15,140,120);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		//Internalwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		InternalQGridLayout->setHorizontalSpacing(6);
		InternalQGridLayout->setVerticalSpacing(6);
		InternalQGridLayout->setMargin(9);
		InternalQGridLayoutList.append(InternalQGridLayout);
		for (int j = 0; j < 12; j++)
		{
		
			LightButton* pLightButton = new LightButton();
			pLightButton->setObjectName(QStringLiteral("lightButton%1_%1").arg(i+1,j+1));
			LightButtonList.append(pLightButton);
			QLabel* internalLabel = new QLabel(Internalwidget);
			if (j <= 5)
			{
				internalLabel->setObjectName(QString("Phonelabe%1_%2").arg(i + 1, j + 1));
				internalLabel->setText(QString("手机 %1").arg(j + 1));
				IphoneLabels.append(internalLabel);
				
			}
			else
			{
				internalLabel->setObjectName(QString("WifiLabel%1_%2").arg(i + 1, j % 6 + 1));
				internalLabel->setText(QString("WiFi %1").arg(j % 6 + 1));
				WifiLabels.append(internalLabel);
			}
			
			if (j / 6 == 0)
			{
				InternalQGridLayout->addWidget(internalLabel, j % 6, j / 6 + 1, 1, 1);//row column
				InternalQGridLayout->addWidget(pLightButton, j % 6, j / 6, 1, 1);
			}
			else
			{
				InternalQGridLayout->addWidget(internalLabel, j % 6, j / 6 + 2, 1, 1);//row column
				InternalQGridLayout->addWidget(pLightButton, j % 6, j / 6+1, 1, 1);
			}

		}
		verticalLayout->addWidget(Internalwidget);
		


		widgets.append(widget);

	}

}
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
//widget->setAlignment(Qt::AlignCenter);
//二选一可以选择显示文字,也可以选择显示背景图片
//widget->setText(QString("终端 %1").arg(i + 1));
////绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
//QPainter painter(this);
//painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//pLightButton->setGeometry(QRect(540, 370, 51, 16));
//internalLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//internalLabel->setGeometry(25, 9 + 18 * i, 30, 12);
//internalLabel->resize();
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
void terminal::showterminal(int index)
{
	int count = 0;
	int row = 0;
	int column = 0;
	int flag = 5;
	for (int i = 0; i < TerminalCount; i++) {
		if (i >= index) {
			gridLayout->addWidget(widgets.at(i), row, column);
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
}
void terminal::ShowSpeed()
{
	qDebug() << "ShowSpeed";
	QWidget* pNewWidget = new WifiSpeed(this,&SwitchControlList,NULL, tcpSocket);
	pNewWidget->setAttribute(Qt::WA_DeleteOnClose);
	pNewWidget->show();
}
