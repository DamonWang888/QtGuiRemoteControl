#pragma execution_character_set("utf-8")

#include "WifiSpeed.h"
#include<QtQuick>
//#include<QML>
//import QtQuick 2.0

WifiSpeed::WifiSpeed(QWidget* sigparent,QList<SwitchControl*>* SwitchControlList,QWidget* parent, QTcpSocket* tcpSocket)
	:sigparent(sigparent),pInternalTerminalSwitchList(SwitchControlList),QWidget(parent), tcpSocket(tcpSocket)
{
	ui.setupUi(this);
	ReadConfig();
	NewTimer* ptimer;
	connect(this, SIGNAL(InformParent()), sigparent, SLOT(InitWifiSpeedPointer()));

	timerlist = (NewTimer**)malloc(150 * sizeof(NewTimer*));
	for (int i = 0; i < 150; i++)
	{
		ptimer = new NewTimer(i,this);
		timerlist[i] = ptimer;
	}
	this->init();
	//this->initForm();
	this->initFormGlobal();
	CheckSwitchSate();
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


WifiSpeed::~WifiSpeed()
{
	qDebug() << "~WifiSpeed";
	emit InformParent();
	int i=0;
	NewTimer* ptimer;

	QList<SwitchControl*>::iterator item = pInternalTerminalSwitchList->begin();
	while (item != pInternalTerminalSwitchList->end())
	{
		SwitchControl *index=(SwitchControl*)*item;
		if (index->isToggled())
		{
		ptimer = timerlist[i];
		ptimer->stop();
		delete ptimer;

		}
		i++;
		item++;
	}
	/*
	for (i = 0; i < 150; i++)
	{
		if (pInternalTerminalSwitchList[i]->isToggled())
		{
			ptimer = timerlist[i];
			ptimer->stop();
			delete ptimer;
		}
	}
	*/
	delete timerlist;
}
void WifiSpeed::init()
{
	pGlobalLayOut = new QVBoxLayout;
	pGlobalLayOut->setSpacing(6);//դ��֮��Ŀհ�
	pGlobalLayOut->setMargin(0);//��Ե
	pGlobalLayOut->setObjectName("gridLayout");
	this->setLayout(pGlobalLayOut);
}
void WifiSpeed::ReadConfig()
{
	int i = 0;
	QString displayString;
	QFile file("./config.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Can't open the file!" << endl;
	}

	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
		QString str(line);
		QStringList list1 = str.split(' ', QString::SkipEmptyParts);
		//for (i = 0; i < list1.size(); i++)
		if (list1.at(0) == "HostName") //����
		{
			HostName = list1.at(1);
			HostName.replace(QString("\n"), QString(""));
		}
		if (list1.at(0) == "baseName") //���ݿ�
		{
			baseName = list1.at(1);
			baseName.replace(QString("\n"), QString(""));
		}
		if (list1.at(0) == "Table") //��
		{
			Table = list1.at(1);
			Table.replace(QString("\n"), QString(""));
		}
		if (list1.at(0) == "UserName") //�û���
		{
			UserName = list1.at(1);
			UserName.replace(QString("\n"), QString(""));
		}
		if (list1.at(0) == "PassWd") //����
		{
			PassWd = list1.at(1);
			PassWd.replace(QString("\n"), QString(""));
		}
		//qDebug() << list1;
		displayString.append(str);
	}
}

void WifiSpeed::StartTimer(int id)
{

	/*QTimer* timer = new QTimer(this);*/
	//qDebug() << "ptimer:" << timer << endl;
	//timerlist[id] = timer;
	//connect(timer, SIGNAL(timeout()), this, SLOT(UpdateDownSpeed(int)));
	timerlist[id]->start(3000);
}

double WifiSpeed::GetSpeedFromMysql(int id)
{
	/*
	*test
	*/
	//DatabaseName ---terminal
	//UserName ---root
	//PassWd ----1308
	//addDatabase����������һ�����ӣ������������ʱ�����ǿ��Դ�������Ҫ�����������͵����ݿ�
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");     //���� 

	db.setHostName(HostName);          //���ݿ��ַ��һ�㶼�Ǳ��أ�����localhost�Ϳ��� 
	db.setDatabaseName(baseName);      //���ݿ�����������Mysql��������ݿ���������д��������Mysql�����и����ݿ��test��������Navicat������Լ������ݿ�����
	db.setUserName(UserName);          //�û�����һ���Ǳ����û�������root�Ϳ���
	db.setPassword(PassWd);            //���룬��д���Լ���Mysql��½���룬Ϊ�˱�����������*�����ҵ�����
	db.setPort(3306);                  //�˿�Ĭ�ϵ���3306�����Բ���д 
	//QString table = "speed";
	if (db.open())
	{
		//QMessageBox::warning(NULL, QStringLiteral("��ʾ"), "open ok", QMessageBox::Yes);
		QSqlQuery query;
		//QString sql_temp = QString("SELECT * from %1 where device_ID=%2 order by Time ASC").arg(Table).arg(id);
		QString sql_temp = QString("select * from %1 where ID in (SELECT max(ID) from %1 where device_ID=%2)").arg(Table).arg(id);
		bool result;
		QTime timer;
		timer.start();
		result = query.exec(sql_temp);
		int runtime = timer.elapsed(); //gets the runtime in ms
		if (result)
			qDebug() << "exec success spend time:" << runtime << "ms" << endl;
		else
			qDebug() << "exec failed spend time:" << runtime << "ms" << endl;

		////��ȡ����
		double speed = -1;
		while (query.next())
		{
			speed = query.value("Speed").toDouble();
			//QString  humidity = query.value(1).toString();

		}
		qDebug() << "id " << id;
		qDebug() << "speed" << speed << endl;
		return speed;
	}
	else
	{
		QMessageBox::warning(NULL, QStringLiteral("��ʾ"), "open mysql failed", QMessageBox::Yes);
	}
	db.close();
	return -1;
}
//qDebug() << sql_temp;      
//ִ��sql��䲢�ж�ִ�н��
/*if (!query.exec(sql_temp))
{
	QSqlError lastError = query.lastError();
	qDebug() << lastError.driverText() << QString(QObject::tr("select failed!"));
	return -1;
}*/
////�������ݿ⣺
//QSqlQuery query;
////���
//QString sql = QString("select temperature,humidity from data where num like '%' ");
////ִ��SQL���
/*result = query.exec("INSERT INTO speed1 (ID, Speed, Time) "
	"VALUES (1001, '34.5', '12:45')");*/
////�������ݿ� 
//QSqlQuery query;
//query.exec("select * from users");
////ָ��ڶ�����¼
//query.seek(1);
////��ȡ��ǰ�еļ�¼                                                   
//QSqlRecord record = query.record();
////��ȡ�ֶ��м�¼��ֵ
//QString id = record.value("ID").toString();
//QString name = record.value("name").toString();
//qDebug() << "name:" << name;

void WifiSpeed::UpdateDownSpeed(int num)
{
	if (!timerlist[num]->GetSate())
	{
		WifiEditList[num]->setText(QString(""));
		return;
	}
	double speed = GetSpeedFromMysql(num+1);
	if (speed >= 0)
	{
		/*ui.lightButton_1->setAlarmColor(QColor(0, 255, 0));
		ui.lightButton_1->HoldAram();*/
		WifiEditList[num]->setText(QString::number(speed, 10, 2) );
	}
}
//WifiEditList[num]->setText(QString::number(speed, 10, 2) + "KB/s");

void WifiSpeed::initFormGlobal()
{
	pTitleWidget = new QWidget(this);
	pTitle = new QLabel(pTitleWidget);
	pTitle->setObjectName(QString("GlobalTitle"));
	pTitle->setText(QString("WIFIͨ������"));

	pDeclare = new QLabel(pTitleWidget);
	pDeclare->setObjectName(QString("Declare"));
	pDeclare->setText(QString("���ʵ�λ:kbps"));

	pFill1 = new QLabel(pTitleWidget);
	pFill1->setObjectName(QString("FillLabel1"));
	pFill2 = new QLabel(pTitleWidget);
	pFill2->setObjectName(QString("FillLabel2"));
	QFont font1,font2;
	font1.setPointSize(30);
	font2.setPointSize(12);
	pTitle->setFont(font1);
	pTitle->setTextFormat(Qt::AutoText);
	pTitle->setGeometry(360, 0, 220, 36);
	pDeclare->setGeometry(750, 0, 170, 36);
	pDeclare->setFont(font2);
	pFill1->setGeometry(20, 0, 340, 36);
	pFill2->setGeometry(580, 0, 170, 36);
	QColor col1 = QColor(255, 211, 155);
	if (col1.isValid()) {
		QString qss = QString("background-color: %1").arg(col1.name());
		pFill1->setStyleSheet(qss);
		pFill2->setStyleSheet(qss);
		pTitle->setStyleSheet(qss);
		pDeclare->setStyleSheet(qss);
	}
	pTitleLayOut= new QHBoxLayout;
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
	pTitleLayOut->addWidget(pDeclare);
	pTitleWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
	pTitleWidget->setMaximumHeight(50);

	pTerminalWidget = new QWidget(this);
	pTerminalWidget->setObjectName(QStringLiteral("layoutWidget"));

	pTerminalLayOut = new QGridLayout();
	pTerminalLayOut->setSpacing(6);//դ��֮��Ŀհ�
	pTerminalLayOut->setMargin(0);//��Ե
	pTerminalLayOut->setObjectName("TerminalLayout");
	pTerminalWidget->setLayout(pTerminalLayOut);

	int newterminalCount = 25;

	for (int i = 0; i < newterminalCount; i++) {

		QWidget* widget = new QWidget;
		widget->setObjectName(QString("newterminal%1").arg(i + 1));
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
		verticalLayout->setSpacing(0);
		verticalLayout->setMargin(0);
		widget->setLayout(verticalLayout);

		QWidget* TerminalNamewidget = new QWidget(widget);
		QLabel* newterminalFill1 = new QLabel(TerminalNamewidget);
		QLabel* newterminalName = new QLabel(TerminalNamewidget);
		newterminalName->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		QLabel* newterminalFill2 = new QLabel(TerminalNamewidget);
		newterminalName->setObjectName(QString("newterminal_label_%1").arg(i + 1));
		newterminalName->setText(QString("�ն� %1").arg(i + 1));
		newterminalName->setGeometry(80, 0, 122, 15);//ax,ay,length,height

		QHBoxLayout* TerminalNameLayout = new QHBoxLayout;
		TerminalNamewidget->setLayout(TerminalNameLayout);
		TerminalNameLayout->addWidget(newterminalFill1);
		TerminalNameLayout->addWidget(newterminalName);
		TerminalNameLayout->addWidget(newterminalFill2);
		TerminalNamewidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
		TerminalNamewidget->setMaximumHeight(25);
		TerminalNameLayout->setMargin(0);
		verticalLayout->addWidget(TerminalNamewidget);

		QWidget* Internalwidget = new QWidget(widget);
		Internalwidget->setGeometry(1, 15, 180, 120);
		QGridLayout* InternalQGridLayout = new QGridLayout(Internalwidget);
		InternalQGridLayout->setHorizontalSpacing(1);
		InternalQGridLayout->setVerticalSpacing(1);
		InternalQGridLayout->setMargin(0);
		for (int j = 0; j < 6; j++)
		{
			QLineEdit* pSpeedEdit = new QLineEdit();
			pSpeedEdit->setObjectName(QStringLiteral("SpeedEdit%1_%1").arg(i + 1, j + 1));
			pSpeedEdit->setStyleSheet("background-color:white;");
			pSpeedEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
			WifiEditList.append(pSpeedEdit);
			QLabel* internalLabel = new QLabel(Internalwidget);
			internalLabel->setObjectName(QString("Wifilabe%1_%2").arg(i + 1, j + 1));
			internalLabel->setText(QString("WIFI%1��������").arg(j + 1));
			internalLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

			InternalQGridLayout->addWidget(internalLabel, j % 6, j / 6, 1, 1);//row column
			InternalQGridLayout->addWidget(pSpeedEdit, j % 6, j / 6 + 1, 1, 1);

		}
		verticalLayout->addWidget(Internalwidget);

		widgets.append(widget);

	}
	int index = 0;
	int count = 0;
	int row = 0;
	int column = 0;
	int flag = 5;
	for (int i = 0; i < newterminalCount; i++) {
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
void WifiSpeed::CheckSwitchSate()
{
	/*
	for (int i = 0; i < pInternalTerminalSwitchList.size(); i++)
		if (pInternalTerminalSwitchList[i]->isToggled())
			StartTimer(i);
	*/
	int i = 0;
	QList<SwitchControl*>::iterator item = pInternalTerminalSwitchList->begin();
	while (item != pInternalTerminalSwitchList->end())
	{
		SwitchControl* index = (SwitchControl*)*item;
		if (index->isToggled())
			StartTimer(i);
		else if (timerlist[i]->GetSate())//�û��򿪺��ֹر�
		{
			timerlist[i]->SetStop();
		}
		i++;
		item++;
	}
}
	

//pTerminalWidget->setGeometry(QRect(20, 40, 930, 700));
/*pTerminalWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
pTerminalWidget->setMaximumHeight(700);*/
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
//QVBoxLayout* pTotalLayout = new QVBoxLayout;
//QVBoxLayoutList.append(verticalLayout);
//newterminalName->resize(122, 15);
//newterminalNameLabels.append(newterminalName);
//verticalLayout->addWidget(newterminalName);
//InternalQGridLayoutList.append(InternalQGridLayout);
////����׼������,���÷����,ƽ������������,�ȱ�������
//QPainter painter(this);
//painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//WifiSpeedList.append(pSpeedEdit);
//pSpeedEdit->setGeometry(QRect(540, 370, 51, 16));
//WifiLabels.append(internalLabel);
//internalLabel->setGeometry(25, 9 + 18 * i, 30, 12);
//internalLabel->resize();
//widget->setPixmap(QPixmap(":/bg_novideo.png"));
//pTerminalLayOut = new QGridLayout;
//pTerminalLayOut->setSpacing(6);//դ��֮��Ŀհ�
//pTerminalLayOut->setMargin(0);//��Ե
//pTerminalLayOut->setObjectName("TerminalLayout");
//pTerminalWidget->setLayout(pTerminalLayOut);
//pTerminal->setGeometry();
//pTerminalLayOut->addWidget(pTerminal);
/*pFillWidget = new QWidget(this);
pFillLayOut = new QVBoxLayout;
pFillWidget->setLayout(pFillLayOut);
pFillWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
pFillWidget->setMaximumHeight(200);
pGlobalLayOut->addWidget(pFillWidget);*/


//void WifiSpeed::initForm()
//{
//	pTitleWidget = new QWidget(this);
//	pTitle = new QLabel(pTitleWidget);
//	pTitle->setObjectName(QString("GlobalTitle"));
//	pTitle->setText(QString("WIFIͨ������"));
//
//
//	pDeclare = new QLabel(pTitleWidget);
//	pDeclare->setObjectName(QString("Declare"));
//	pDeclare->setText(QString("���ʵ�λ:kbps"));
//
//	pFill1 = new QLabel(pTitleWidget);
//	pFill1->setObjectName(QString("FillLabel1"));
//	pFill2 = new QLabel(pTitleWidget);
//	pFill2->setObjectName(QString("FillLabel2"));
//	//pFill->setText(QString("ϵͳ�Լ�"));
//	QFont font1,font2;
//	font1.setPointSize(27);
//	font2.setPointSize(12);
//	pTitle->setFont(font1);
//	pTitle->setTextFormat(Qt::AutoText);
//	pTitle->setGeometry(360, 0, 220, 36);
//	pDeclare->setGeometry(750, 0, 170, 36);
//	pDeclare->setFont(font2);
//	pFill1->setGeometry(20, 0, 340, 36);
//	pFill2->setGeometry(580, 0, 170, 36);
//	//pFill->setText(QString("ϵͳ�Լ�"));
//	QColor col1 = QColor(255, 211, 155);
//	if (col1.isValid()) {
//		QString qss = QString("background-color: %1").arg(col1.name());
//		pFill1->setStyleSheet(qss);
//		pFill2->setStyleSheet(qss);
//		pTitle->setStyleSheet(qss);
//		pDeclare->setStyleSheet(qss);
//	}
//	pTitleLayOut= new QHBoxLayout;
//	pTitleWidget->setLayout(pTitleLayOut);
//	pTitle->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//	pFill1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//	pFill2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//	pTitleWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//	pTitleLayOut->setMargin(0);
//	pTitleLayOut->setSpacing(0);
//	pTitleLayOut->addWidget(pFill1);
//	pTitleLayOut->addWidget(pTitle);
//	pTitleLayOut->addWidget(pFill2);
//	pTitleLayOut->addWidget(pDeclare);
//	pTitleWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
//	pTitleWidget->setMaximumHeight(36);
//
//	pTerminalWidget = new QWidget(this);
//	pTerminalWidget->setObjectName(QStringLiteral("layoutWidget"));
//	//pTerminalWidget->setGeometry(QRect(20, 40, 930, 700));
//
//	pTerminalLayOut = new QVBoxLayout;
//	pTerminalLayOut->setSpacing(6);//դ��֮��Ŀհ�
//	pTerminalLayOut->setMargin(0);//��Ե
//	pTerminalLayOut->setObjectName("TerminalLayout");
//	pTerminalWidget->setLayout(pTerminalLayOut);
//	/*pTerminalWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
//	pTerminalWidget->setMaximumHeight(700);*/
//
//	pTerminal = new newterminal(pTerminalWidget);
//	//pTerminal->setGeometry();
//	pTerminalLayOut->addWidget(pTerminal);
//	pGlobalLayOut->addWidget(pTitleWidget);
//    pGlobalLayOut->addWidget(pTerminalWidget);
//
//	/*pFillWidget = new QWidget(this);
//	pFillLayOut = new QVBoxLayout;
//	pFillWidget->setLayout(pFillLayOut);
//	pFillWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
//	pFillWidget->setMaximumHeight(200);
//	pGlobalLayOut->addWidget(pFillWidget);*/
//}
