#pragma execution_character_set("utf-8")
#include"newterminal.h"
/*
newterminal::newterminal(QString name, int ButtonNum, int QLabelNum, QWidget* parent) : QWidget(parent)
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
newterminal::newterminal(QWidget* parent) :QWidget(parent)
{
	this->initControl();
	this->initForm();
	this->shownewterminal();
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
newterminal::newterminal(int newterminalType, QWidget* parent)//0:iphone ,1:wifi, 2:wifispeed ,3:iphone switch ,4:wifi switch
{
	this->initControl();
	switch (newterminalType)
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
	this->shownewterminal();
}
void newterminal::initControl()
{
	gridLayout = new QGridLayout;
	gridLayout->setSpacing(6);//栅格之间的空白
	gridLayout->setMargin(0);//边缘
	gridLayout->setObjectName("gridLayout");
	this->setLayout(gridLayout);
}
void newterminal::initFormIphoneSwitch()
{
	newterminalCount = 1;
	for (int i = 0; i < newterminalCount; i++) {

		QWidget* widget = new QWidget;
		widget->setObjectName(QString("newterminal%1").arg(i + 1));
		widget->installEventFilter(this);
		widget->setFocusPolicy(Qt::StrongFocus);

		QColor col1 = QColor(255, 211, 155);
		if (col1.isValid()) {
			QString qss = QString("background-color: %1").arg(col1.name());
			widget->setStyleSheet(qss);
		}
	

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(0, 10, 900, 80);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(6);
		InternalQGridLayout->setVerticalSpacing(36);
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

//QLabel* newterminalName = new QLabel(widget);
//newterminalName->setObjectName(QString("newterminal_label_%1").arg(i + 1));
//newterminalName->setText(QString("终端 %1").arg(i + 1));
//newterminalName->setGeometry(70, 0, 122, 15);//ax,ay,length,height
////newterminalName->resize(122, 15);
//newterminalNameLabels.append(newterminalName);
//verticalLayout->addWidget(newterminalName);

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
void newterminal::initFormWifiSwitch()
{
	newterminalCount = 1;
	for (int i = 0; i < newterminalCount; i++) {

		QWidget* widget = new QWidget;
		widget->setObjectName(QString("newterminal%1").arg(i + 1));
		widget->installEventFilter(this);
		widget->setFocusPolicy(Qt::StrongFocus);

		QColor col1 = QColor(255, 211, 155);
		if (col1.isValid()) {
			QString qss = QString("background-color: %1").arg(col1.name());
			widget->setStyleSheet(qss);
		}


		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(0, 10, 900, 80);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(6);
		InternalQGridLayout->setVerticalSpacing(36);
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
void newterminal::initFormIphone()
{
	newterminalCount = 25;
	
	for (int i = 0; i < newterminalCount; i++) {


		QWidget* widget = new QWidget;
		widget->setObjectName(QString("newterminal%1").arg(i + 1));
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

		QLabel* newterminalName = new QLabel(widget);
		newterminalName->setObjectName(QString("newterminal_label_%1").arg(i + 1));
		newterminalName->setText(QString("终端 %1").arg(i + 1));
		newterminalName->setGeometry(70, 0, 122, 15);//ax,ay,length,height
		//newterminalName->resize(122, 15);
		newterminalNameLabels.append(newterminalName);
		verticalLayout->addWidget(newterminalName);

		SwitchControl* pSwitchControl = new SwitchControl(widget);
		//LightButton* pLightButton = new LightButton();
		pSwitchControl->setObjectName(QStringLiteral("TotalSwitchControl"));
		pSwitchControl->setGeometry(QRect(9, 48, 30, 10));//margin=9
		SwitchControlList.append(pSwitchControl);
		verticalLayout->addWidget(pSwitchControl);

		QLabel* internalLabel = new QLabel(widget);
		internalLabel->setObjectName(QString("TotalSwitch"));
		internalLabel->setText(QString("全开"));
		internalLabel->setGeometry(QRect(52, 45, 30, 13));
		IphoneLabels.append(internalLabel);

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(0, 66, 180, 80);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(6);
		InternalQGridLayout->setVerticalSpacing(12);
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

//widget->setAlignment(Qt::AlignCenter);

//二选一可以选择显示文字,也可以选择显示背景图片
//widget->setText(QString("终端 %1").arg(i + 1));
//widget->setWindowTitle(QString("终端 %1").arg(i + 1));;

////绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
//QPainter painter(this);
//painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//LightButton* pLightButton = new LightButton();
//internalLabel->setGeometry(25, 9 + 18 * i, 30, 12);
//internalLabel->resize();
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
//pLightButton->setGeometry(QRect(540, 370, 51, 16));
void newterminal::initFormWifi()
{
	newterminalCount = 25;
	

	for (int i = 0; i < newterminalCount; i++) {

		QWidget* widget = new QWidget;
		widget->setObjectName(QString("newterminal%1").arg(i + 1));
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

		
		QPushButton* newterminalName = new QPushButton(widget);
		newterminalName->setObjectName(QString("newterminal_label_%1").arg(i + 1));
		newterminalName->setText(QString("终端 %1").arg(i + 1));
		newterminalName->setGeometry(40, 0, 122, 15);//ax,ay,length,height
		//newterminalName->resize(122, 15);
		newterminalNameButtons.append(newterminalName);
		verticalLayout->addWidget(newterminalName);
		connect(newterminalName, SIGNAL(clicked()), this, SLOT(ShowSpeed()));

		SwitchControl* pSwitchControl = new SwitchControl(widget);
		//LightButton* pLightButton = new LightButton();
		pSwitchControl->setObjectName(QStringLiteral("TotalSwitchControl"));
		pSwitchControl->setGeometry(QRect(9, 48, 30, 10));//margin=9
		SwitchControlList.append(pSwitchControl);
		verticalLayout->addWidget(pSwitchControl);

		QLabel* internalLabel = new QLabel(widget);
		internalLabel->setObjectName(QString("TotalSwitch"));
		internalLabel->setText(QString("全开"));
		internalLabel->setGeometry(QRect(52, 45, 30, 13));
		IphoneLabels.append(internalLabel);

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(0, 66, 180, 80);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(6);
		InternalQGridLayout->setVerticalSpacing(12);
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
QLabel* newterminalName = new QLabel(widget);
newterminalName->setObjectName(QString("newterminal_label_%1").arg(i + 1));
newterminalName->setText(QString("终端 %1").arg(i + 1));
newterminalName->setGeometry(70, 0, 122, 15);//ax,ay,length,height
//newterminalName->resize(122, 15);
newterminalNameLabels.append(newterminalName);
verticalLayout->addWidget(newterminalName);
*/
////绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
//QPainter painter(this);
//painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//LightButton* pLightButton = new LightButton();
//pLightButton->setGeometry(QRect(540, 370, 51, 16));
//internalLabel->setGeometry(25, 9 + 18 * i, 30, 12);
//internalLabel->resize();
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
void newterminal::initFormWifiSpeed()
{
	qDebug() << "initFormWifiSpeed";
	newterminalCount = 25;
	QString videoType = "1_16";

	for (int i = 0; i < newterminalCount; i++) {
	
		QWidget* widget = new QWidget;
		widget->setObjectName(QString("newterminal%1").arg(i + 1));
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

		QLabel* newterminalName = new QLabel(widget);
		newterminalName->setObjectName(QString("newterminal_label_%1").arg(i + 1));
		newterminalName->setText(QString("终端 %1").arg(i + 1));
		newterminalName->setGeometry(50, 0, 122, 15);//ax,ay,length,height
		//newterminalName->resize(122, 15);
		newterminalNameLabels.append(newterminalName);

		verticalLayout->addWidget(newterminalName);

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
////绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
//QPainter painter(this);
//painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//pLightButton->setGeometry(QRect(540, 370, 51, 16));
//internalLabel->setGeometry(25, 9 + 18 * i, 30, 12);
//internalLabel->resize();
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
void newterminal::initForm()
{
	newterminalCount = 25;
	QString videoType = "1_16";

	for (int i = 0; i < newterminalCount; i++) {
		
		

		QWidget* widget = new QWidget;
		widget->setObjectName(QString("newterminal%1").arg(i + 1));
		widget->installEventFilter(this);
		widget->setFocusPolicy(Qt::StrongFocus);
		widget->setWindowTitle(QString("终端 %1").arg(i + 1));;
		QColor col1 = QColor(173, 216, 230);
		if (col1.isValid()) {
			QString qss = QString("background-color: %1").arg(col1.name());
			widget->setStyleSheet(qss);
		}

		//QVBoxLayout* pTotalLayout = new QVBoxLayout;
		QVBoxLayout* verticalLayout = new QVBoxLayout();
		verticalLayout->setObjectName(QString("verticalLayout%1").arg(i + 1));
		verticalLayout->setSpacing(0);
		verticalLayout->setMargin(0);
		widget->setLayout(verticalLayout);
		QVBoxLayoutList.append(verticalLayout);

		QWidget* TerminalNamewidget = new QWidget(widget);
		QLabel* newterminalFill1 = new QLabel(TerminalNamewidget);
		QLabel* newterminalName = new QLabel(TerminalNamewidget);
		newterminalName->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		QLabel* newterminalFill2= new QLabel(TerminalNamewidget);
		newterminalName->setObjectName(QString("newterminal_label_%1").arg(i + 1));
		newterminalName->setText(QString("终端 %1").arg(i + 1));
		newterminalName->setGeometry(80, 0, 122, 15);//ax,ay,length,height
		//newterminalName->resize(122, 15);
		newterminalNameLabels.append(newterminalName);

		QHBoxLayout* TerminalNameLayout = new QHBoxLayout; 
		TerminalNamewidget->setLayout(TerminalNameLayout);
		TerminalNameLayout->addWidget(newterminalFill1);
		TerminalNameLayout->addWidget(newterminalName);
		TerminalNameLayout->addWidget(newterminalFill2);
		TerminalNamewidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
		TerminalNamewidget->setMaximumHeight(25);
		TerminalNameLayout->setMargin(0);
		verticalLayout->addWidget(TerminalNamewidget);
		//verticalLayout->addWidget(newterminalName);

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(1, 15, 180, 120);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(1);
		InternalQGridLayout->setVerticalSpacing(1);
		InternalQGridLayout->setMargin(0);
		InternalQGridLayoutList.append(InternalQGridLayout);
		for (int j = 0; j < 6; j++)
		{
			
			QLineEdit* pSpeedEdit = new QLineEdit();
			pSpeedEdit->setObjectName(QStringLiteral("SpeedEdit%1_%1").arg(i + 1, j + 1));
			pSpeedEdit->setStyleSheet("background-color:white;");
			pSpeedEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
			WifiSpeedList.append(pSpeedEdit);
		
			QLabel* internalLabel = new QLabel(Internalwidget);
			internalLabel->setObjectName(QString("Wifilabe%1_%2").arg(i + 1, j + 1));
			internalLabel->setText(QString("WIFI%1下载速率").arg(j + 1));
			internalLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
			WifiLabels.append(internalLabel);
			InternalQGridLayout->addWidget(internalLabel, j % 6, j / 6 , 1, 1);//row column
			InternalQGridLayout->addWidget(pSpeedEdit, j % 6, j / 6+1, 1, 1);
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
//pSpeedEdit->setGeometry(QRect(540, 370, 51, 16));
//internalLabel->setGeometry(25, 9 + 18 * i, 30, 12);
//internalLabel->resize();
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
void newterminal::shownewterminal(int index)
{
	int count = 0;
	int row = 0;
	int column = 0;
	int flag = 5;
	for (int i = 0; i < newterminalCount; i++) {
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
//void newterminal::ShowSpeed()
//{
//	qDebug() << "ShowSpeed";
//	QWidget* pNewWidget = new WifiSpeed();
//	pNewWidget->show();
//}
