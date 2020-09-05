#pragma execution_character_set("utf-8")

#include "NewSelfCheck.h"

#include<QtQuick>
//#include<QML>
//import QtQuick 2.0

NewSelfCheck::NewSelfCheck(QWidget* sigparent,QWidget* parent, QTcpSocket* tcpSocket)
	:sigparent(sigparent), QWidget(parent), tcpSocket(tcpSocket)
{
	ui.setupUi(this);
	connect(this, SIGNAL(InformParent()), sigparent, SLOT(InitSelfCheckPointer()));
	this->init();
	this->initFormGlobal();
}
//QString name = "�ն�1";
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


NewSelfCheck::~NewSelfCheck()
{
	emit InformParent();
}
void NewSelfCheck::init()
{
	//���㲼��
	pGlobalLayOut = new QVBoxLayout;
	pGlobalLayOut->setSpacing(6);//դ��֮��Ŀհ�
	pGlobalLayOut->setMargin(0);//��Ե
	pGlobalLayOut->setObjectName("gridLayout");
	this->setLayout(pGlobalLayOut);
}

void NewSelfCheck::initFormGlobal()
{
	pTitleWidget = new QWidget(this);
	pTitleWidget->setObjectName(QStringLiteral("layoutWidget"));
	pTitle = new QLabel(pTitleWidget);
	pTitle->setObjectName(QString("GlobalTitle"));
	pTitle->setText(QString("ϵͳ�Լ�"));
	pFill1 = new QLabel(pTitleWidget);
	pFill1->setObjectName(QString("FillLabel1"));
	pFill2 = new QLabel(pTitleWidget);
	pFill2->setObjectName(QString("FillLabel2"));
	QFont font1;
	font1.setPointSize(27);
	pTitle->setFont(font1);
	pTitle->setTextFormat(Qt::AutoText);

	pTitleLayOut = new QHBoxLayout();
	pTitleWidget->setLayout(pTitleLayOut);
	pTitle->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	pFill1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	pFill2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	pTitleWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	pTitleLayOut->setMargin(0);
	pTitleLayOut->setSpacing(0);
	pTitleLayOut->addWidget(pFill1);
	pTitleLayOut->addWidget(pTitle);
	pTitleLayOut->addWidget(pFill2);


	QColor col1 = QColor(255, 211, 155);
	if (col1.isValid()) {
		QString qss = QString("background-color: %1").arg(col1.name());
		pFill1->setStyleSheet(qss);
		pFill2->setStyleSheet(qss);
		pTitle->setStyleSheet(qss);
	}

	pTerminalWidget = new QWidget(this);
	pTerminalWidget->setObjectName(QStringLiteral("layoutWidget"));

	pTerminalLayOut = new QGridLayout;
	pTerminalLayOut->setSpacing(6);//դ��֮��Ŀհ�
	pTerminalLayOut->setMargin(0);//��Ե
	pTerminalLayOut->setObjectName("TerminalLayout");
	pTerminalWidget->setLayout(pTerminalLayOut);

	int TerminalCount = 25;

	for (int i = 0; i < TerminalCount; i++) {


		QWidget* widget = new QWidget;
		widget->setObjectName(QString("terminal%1").arg(i + 1));
		widget->installEventFilter(this);
		widget->setFocusPolicy(Qt::StrongFocus);
		widget->setWindowTitle(QString("�ն� %1").arg(i + 1));;
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
		terminalName->setText(QString("�ն� %1").arg(i + 1));
		terminalName->setGeometry(100, 0, 122, 15);//ax,ay,length,height

		verticalLayout->addWidget(terminalName);

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(1, 15, 200, 180);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(6);
		InternalQGridLayout->setVerticalSpacing(6);
		InternalQGridLayout->setMargin(9);
		for (int j = 0; j < 12; j++)
		{
			LightButton* pLightButton = new LightButton();
			//pLightButton->setLightGreen();
			pLightButton->setAlarmColor(QColor(0, 255, 0));
			pLightButton->HoldAram();
			pLightButton->setObjectName(QStringLiteral("lightButton%1_%1").arg(i + 1, j + 1));
			LightButtonList.append(pLightButton);
			QLabel* internalLabel = new QLabel(Internalwidget);
			if (j <= 5)
			{
				internalLabel->setObjectName(QString("Phonelabe%1_%2").arg(i + 1, j + 1));
				internalLabel->setText(QString("�ֻ� %1").arg(j + 1));

			}
			else
			{
				internalLabel->setObjectName(QString("WifiLabel%1_%2").arg(i + 1, j % 6 + 1));
				internalLabel->setText(QString("WiFi %1").arg(j % 6 + 1));
			}
			//
			if (j / 6 == 0)
			{
				InternalQGridLayout->addWidget(internalLabel, j % 6, j / 6 + 1, 1, 1);//row column
				InternalQGridLayout->addWidget(pLightButton, j % 6, j / 6, 1, 1);
				IphoneLightButtonList.append(pLightButton);
			}
			else
			{
				InternalQGridLayout->addWidget(internalLabel, j % 6, j / 6 + 2, 1, 1);//row column
				InternalQGridLayout->addWidget(pLightButton, j % 6, j / 6 + 1, 1, 1);
				WifiLightButtonList.append(pLightButton);
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
	pGlobalLayOut->addWidget(pTerminalWidget);
}
void NewSelfCheck::UpdateDeviceStatus(int id, char*data)
{
	qDebug() << "NewSelfCheck::UpdateDeviceStatus" << endl;
	char Status1[] = "00";
	char Status2[] = "11";
	char Status3[] = "01";//wifi has problem
	char Status4[] = "10";//iphone has problem
	if (!strcmp(data, Status1))
	{
		WifiLightButtonList[id]->setLightRed();
		IphoneLightButtonList[id]->setLightRed();
	}
	if (!strcmp(data, Status2))
	{
		return;
	}
	if (!strcmp(data, Status3))
	{
		WifiLightButtonList[id]->setLightRed();
	}
	if (!strcmp(data, Status4))
	{
		IphoneLightButtonList[id]->setLightRed();
	}
}
//pTitleWidget->setGeometry(QRect(0, 0, 900, 36));
//pFill->setText(QString("ϵͳ�Լ�"));
//pTitle->setGeometry(600, 0, 150, 36);
//pTitle->();
//pFill1->setGeometry(20, 0, 375, 36);
//pFill2->setGeometry(545, 0, 375, 36);
//pFill->setText(QString("ϵͳ�Լ�"));
//pTitleLayOut->SetFixedSize();
//pTitle->setLayout(pTitleLayOut);
//pTitleLayOut->setSizeConstraint(QLayout::SetFixedSize);
//pTerminalWidget->setGeometry(QRect(0, 40, 900, 900));
/*
QLabel* widget = new QLabel;
widget->setObjectName(QString("video%1").arg(i + 1));
widget->installEventFilter(this);
widget->setFocusPolicy(Qt::StrongFocus);
widget->setAlignment(Qt::AlignCenter);

//��ѡһ����ѡ����ʾ����,Ҳ����ѡ����ʾ����ͼƬ
widget->setText(QString("�ն� %1").arg(i + 1));
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
widgets.append(widget);*/
//widget->setAlignment(Qt::AlignCenter);

//��ѡһ����ѡ����ʾ����,Ҳ����ѡ����ʾ����ͼƬ
//widget->setText(QString("�ն� %1").arg(i + 1));
//QVBoxLayoutList.append(verticalLayout);
//terminalName->resize(122, 15);
//TerminalNameLabels.append(terminalName);
//Internalwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//InternalQGridLayoutList.append(InternalQGridLayout);
////����׼������,���÷����,ƽ������������,�ȱ�������
//QPainter painter(this);
//painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//pLightButton->setGeometry(QRect(540, 370, 51, 16));
//internalLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//IphoneLabels.append(internalLabel);
//WifiLabels.append(internalLabel);
//internalLabel->setGeometry(25, 9 + 18 * i, 30, 12);
//internalLabel->resize();
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
//pTerminal = new terminal(pTerminalWidget);
//pTerminal->setGeometry();
//pTerminalLayOut->addWidget(pTerminal);
//pGlobalLayOut->addLayout(pTitleLayOut);
//pGlobalLayOut->setSizeConstraint(QLayout::SetMinimumSize);

//void NewSelfCheck::initForm()
//{
//	pTitleWidget = new QWidget(this);
//	pTitleWidget->setObjectName(QStringLiteral("layoutWidget"));
//	//pTitleWidget->setGeometry(QRect(0, 0, 900, 36));
//	pTitle = new QLabel(pTitleWidget);
//	pTitle->setObjectName(QString("GlobalTitle"));
//	pTitle->setText(QString("ϵͳ�Լ�"));
//	pFill1 = new QLabel(pTitleWidget);
//	pFill1->setObjectName(QString("FillLabel1"));
//	pFill2 = new QLabel(pTitleWidget);
//	pFill2->setObjectName(QString("FillLabel2"));
//	//pFill->setText(QString("ϵͳ�Լ�"));
//	QFont font1;
//	font1.setPointSize(27);
//	pTitle->setFont(font1);
//	pTitle->setTextFormat(Qt::AutoText);
//	//pTitle->setGeometry(600, 0, 150, 36);
//	//pTitle->();
//	//pFill1->setGeometry(20, 0, 375, 36);
//	//pFill2->setGeometry(545, 0, 375, 36);
//	//pFill->setText(QString("ϵͳ�Լ�"));
//
//	pTitleLayOut = new QHBoxLayout();
//	pTitleWidget->setLayout(pTitleLayOut);
//	//pTitleLayOut->SetFixedSize();
//	//pTitle->setLayout(pTitleLayOut);
//	pTitle->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
//	pFill1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//	pFill2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//	pTitleWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//	pTitleLayOut->setMargin(0);
//	pTitleLayOut->setSpacing(0);
//	pTitleLayOut->addWidget(pFill1);
//	pTitleLayOut->addWidget(pTitle);
//	pTitleLayOut->addWidget(pFill2);
//
//	//pTitleLayOut->setSizeConstraint(QLayout::SetFixedSize);
//
//	QColor col1 = QColor(255, 211, 155);
//	if (col1.isValid()) {
//		QString qss = QString("background-color: %1").arg(col1.name());
//		pFill1->setStyleSheet(qss);
//		pFill2->setStyleSheet(qss);
//		pTitle->setStyleSheet(qss);
//	}
//
//	pTerminalWidget = new QWidget(this);
//	pTerminalWidget->setObjectName(QStringLiteral("layoutWidget"));
//	//pTerminalWidget->setGeometry(QRect(0, 40, 900, 900));
//	
//	pTerminalLayOut = new QVBoxLayout;
//	pTerminalLayOut->setSpacing(6);//դ��֮��Ŀհ�
//	pTerminalLayOut->setMargin(0);//��Ե
//	pTerminalLayOut->setObjectName("TerminalLayout");
//	pTerminalWidget->setLayout(pTerminalLayOut);
//	
//	pTerminal = new terminal(pTerminalWidget);
//	//pTerminal->setGeometry();
//	pTerminalLayOut->addWidget(pTerminal);
//	//pGlobalLayOut->addLayout(pTitleLayOut);
//	pGlobalLayOut->addWidget(pTitleWidget);
//	pGlobalLayOut->addWidget(pTerminalWidget);
//	//pGlobalLayOut->setSizeConstraint(QLayout::SetMinimumSize);
//}