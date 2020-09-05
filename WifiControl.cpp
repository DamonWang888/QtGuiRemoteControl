#include "WifiControl.h"

QtGuiRemoteControl::QtGuiRemoteControl(QWidget *parent, QTcpSocket *tcpSocket, QString HostName, QString baseName, QString Table, 
	QString UserName, QString PassWd)
: QMainWindow(parent),tcpSocket(tcpSocket),HostName(HostName),baseName(baseName), Table(Table),UserName(UserName),PassWd(PassWd)
{
	
	ui.setupUi(this);
	int i;
	QTimer *ptimer;
	timerlist =(QTimer**) malloc( 150*sizeof(QTimer*));
	for (i = 0; i < 150; i++)
	{
		ptimer = new QTimer(this);
		timerlist[i] = ptimer;
	}
	//窗口关闭时释放内存
	setAttribute(Qt::WA_DeleteOnClose);
	connect(ui.TotalWificheckBox1, SIGNAL(clicked()), this, SLOT(Update1()));
	connect(ui.TotalWificheckBox2, SIGNAL(clicked()), this, SLOT(Update2()));
	connect(ui.TotalWificheckBox3, SIGNAL(clicked()), this, SLOT(Update3()));
	connect(ui.TotalWificheckBox_1, SIGNAL(clicked()), this, SLOT(DownLoadFile1()));
	connect(ui.TotalWificheckBox_2, SIGNAL(clicked()), this, SLOT(DownLoadFile2()));
	connect(ui.TotalWificheckBox_3, SIGNAL(clicked()), this, SLOT(DownLoadFile3()));
	connect(ui.TotalWificheckBox_4, SIGNAL(clicked()), this, SLOT(DownLoadFile4()));
	connect(ui.TotalWificheckBox_5, SIGNAL(clicked()), this, SLOT(DownLoadFile5()));
	connect(ui.TotalWificheckBox_6, SIGNAL(clicked()), this, SLOT(DownLoadFile6()));
	connect(this, &QtGuiRemoteControl::getspeed, this, &QtGuiRemoteControl::StartTimer);
	connect(this, &QtGuiRemoteControl::stopdown, this, &QtGuiRemoteControl::StopTimer);
	connect(this,&QtGuiRemoteControl::multicast,this,&QtGuiRemoteControl::MultiDownFile);
	connect(ui.TotalWificheckBox1,SIGNAL(clicked()),this,SLOT(TotalDownFile1()));
	connect(ui.TotalWificheckBox2, SIGNAL(clicked()), this, SLOT(TotalDownFile2()));
	connect(ui.TotalWificheckBox3, SIGNAL(clicked()), this, SLOT(TotalDownFile3()));

}
//ui.SegDowncheckBox_1->setDisabled(true);
//ui.SegUpcheckBox_1->setDisabled(true);
//ui.SegTotalcheckBox_1->setDisabled(true);
//表格只读
//ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//Server.listen(QHostAddress::Any, SERVER_PORT);

//QString ipAddress;
//QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
//// use the first non-localhost IPv4 address
//for (int i = 0; i < ipAddressesList.size(); ++i) {
//	if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
//		ipAddressesList.at(i).toIPv4Address()) {
//		ipAddress = ipAddressesList.at(i).toString();
//		break;
//	}
//}
//// if we did not find one, use IPv4 localhost
//if (ipAddress.isEmpty())
//	ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
//ui.statusLabel->setText(tr("The server is running on IP: %1 port: %2"
//	" Run the  Client example now.").arg(ipAddress).arg(Server.serverPort()));
//ui.statusLabel->adjustSize();
//connect();
//connect(ui.SegDowncheckBox_3, SIGNAL(clicked()), this, SLOT(DownLoadFile()));
//connect(ui.SegDowncheckBox_1, SIGNAL(stateChanged(int)), this, SLOT());
QtGuiRemoteControl::~QtGuiRemoteControl()
{
	int i;
	QTimer *ptimer;
	
	for (i = 0; i < 150; i++)
	{
		ptimer =  timerlist[i];
		ptimer->stop();
		delete ptimer;
	}
	delete timerlist;
}

void QtGuiRemoteControl::SendMsg(char *data)
{
	qDebug() << "SendMsg";
	char *sendmsg = (char*)malloc(64);
	memset(sendmsg, 0, sizeof(sendmsg));
	memcpy(sendmsg, data, sizeof(data));
	tcpSocket->write(sendmsg);
	delete sendmsg;
}


void QtGuiRemoteControl::DownLoadFile2()
{

	if (ui.TotalWificheckBox_2->checkState() == Qt::CheckState::Unchecked)//
	{
		char tmp[] = "#4#2#";//命令 id 
		SendMsg(tmp);
		emit stopdown(2);
		return;
	}
	char tmp[] = "#3#2#";//命令 id 
	SendMsg(tmp);
	emit getspeed(2);
}

void QtGuiRemoteControl::DownLoadFile3()
{
	if (ui.TotalWificheckBox_3->checkState() == Qt::CheckState::Unchecked)
	{
		char tmp[] = "#4#3#";//命令 id 
		SendMsg(tmp);
		emit stopdown(3);
		return;
	}
	char tmp[] = "#3#3#";//命令 id 
	SendMsg(tmp);
	emit getspeed(3);
}

void QtGuiRemoteControl::DownLoadFile4()
{
	if (ui.TotalWificheckBox_4->checkState() == Qt::CheckState::Unchecked)
	{
		char tmp[] = "#4#4#";//命令 id 
		SendMsg(tmp);
		emit stopdown(4);
		return;
	}
	char tmp[] = "#3#4#";//命令 id 
	SendMsg(tmp);
	emit getspeed(4);
}

void QtGuiRemoteControl::DownLoadFile5()
{
	if (ui.TotalWificheckBox_5->checkState() == Qt::CheckState::Unchecked)
	{
		char tmp[] = "#4#5#";//命令 id 
		SendMsg(tmp);
		emit stopdown(5);
		return;
	}
	char tmp[] = "#3#5#";//命令 id 
	SendMsg(tmp);
	emit getspeed(5);
}

void QtGuiRemoteControl::DownLoadFile6()
{
	if (ui.TotalWificheckBox_6->checkState() == Qt::CheckState::Unchecked)
	{
		char tmp[] = "#4#6#";//命令 id 
		SendMsg(tmp);
		emit stopdown(6);
		return;
	}
	char tmp[] = "#3#6#";//命令 id 
	SendMsg(tmp);
	emit getspeed(6);
}
//server 给 client下发下载指令  
void QtGuiRemoteControl::DownLoadFile1()
{

	qDebug() << "DownLoadFile";
	

	

	if (ui.TotalWificheckBox_1->checkState() == Qt::CheckState::Unchecked)
	{
		char tmp[] = "#4#1#";//命令 id 
		SendMsg(tmp);
		emit stopdown(1);
		return;
	}
	
	char tmp[] = "#3#1#";//命令 id 
	SendMsg(tmp);
	emit getspeed(1);
	
}



//qDebug() << ui.SegTotalcheckBox_1->checkState() << ui.SegDowncheckBox_1->isTristate() << ui.SegDowncheckBox_1->isChecked();

//if (ui.SegDowncheckBox_1->isChecked()==false)
//	return;

//QFile file("file.flv");
//file.open(QIODevice::ReadOnly);
//QByteArray Block, SendBlock;
//Block = file.readAll();
//QDataStream out(&SendBlock, QIODevice::WriteOnly);
//out.setVersion(QDataStream::Qt_5_9);
//int CanDown = 1;
//out << CanDown;
//char SendInfo[] = "#3#1#";//下载指令
//char length[3];
//int len = sizeof(SendInfo) - 1;//去除后面的‘\0’所占长度
//itoa(len, length, 10);

//ui.lightButton_1->setAlarmColor(QColor(255, 0, 0));
//ui.lightButton_1->HoldAram();
//ui.lightButton_1->setNormalColor(QColor(0, 0, 0));
//ui.lightButton_1->startAlarm();

//QByteArray ba = SendInfo.toLatin1();
//! [4] //! [7]
/*QList<QTcpSocket *> m_tcps = PServer->findChildren<QTcpSocket *>();
foreach(QTcpSocket *tcp, m_tcps)
{
	qDebug() << "Address:" << tcp->peerAddress();
	qDebug() << "Port:" << tcp->peerPort();
	tcp->write(length);
	tcp->write(SendInfo);
}*/
//if (LinkList->size())
//{
//	for (QMap<int, QTcpSocket*>::iterator it = LinkList->begin(); it != LinkList->end(); it++)
//	{
//		if(it.key()==ui.comboBox->currentText().toInt())
//		//if (it.key() == 1)
//		{	
//			it.value()->write(length);
//			it.value()->write(SendInfo);
//			
//		}
//	}
//}
//else
//{
//	QMessageBox::information(this, tr("Notice"),
//		tr("No Client is connecting successfully"));
//}
//QTcpSocket *clientConnection = PServer->nextPendingConnection();
//qDebug() << "DownLoadFile"<< clientConnection;
//if (clientConnection)
//{
//	/*connect(clientConnection, &QAbstractSocket::disconnected,
//		clientConnection, &QObject::deleteLater);*/
//	//! [7] //! [8]
//	qDebug() << "write";
//	clientConnection->write(SendBlock);
//	//clientConnection->disconnectFromHost();
//}
//else
//{
//	QMessageBox::information(this, tr("Chat"),
//		tr("The client is not running on your local network"));
//}

void QtGuiRemoteControl::Update3()
{
	//未被点击
	if (ui.TotalWificheckBox3->checkState() == Qt::CheckState::Checked)
	{
		//ui.TotalWificheckBox_1->setDisabled(true);
		ui.TotalWificheckBox2->setDisabled(true);
		ui.TotalWificheckBox1->setDisabled(true);
	}
	//已被点击
	else if (ui.TotalWificheckBox3->checkState() == Qt::CheckState::Unchecked)
	{
		//ui.SegDowncheckBox_1->setDisabled(false);
		ui.TotalWificheckBox2->setDisabled(false);
		ui.TotalWificheckBox1->setDisabled(false);
	}
}

void QtGuiRemoteControl::Update1()
{
	qDebug() <<"current state:"<<ui.TotalWificheckBox1->checkState()<<"IsChecked:"<<ui.TotalWificheckBox1->isChecked();
	//未被点击
	if (ui.TotalWificheckBox1->checkState()== Qt::CheckState::Checked)
	{
		qDebug() << "Update1 -----1-------";
		//ui.TotalWificheckBox_1->setDisabled(true);
		ui.TotalWificheckBox2->setDisabled(true);
		ui.TotalWificheckBox3->setDisabled(true);
	}
	//已被点击
	else if (ui.TotalWificheckBox1->checkState() == Qt::CheckState::Unchecked)
	{
		//ui.SegDowncheckBox_1->setDisabled(false);
		qDebug() << "Update1 -----2-------";
		ui.TotalWificheckBox2->setDisabled(false);
		ui.TotalWificheckBox3->setDisabled(false);
	}
	
}

void QtGuiRemoteControl::Update2()
{
	//未被点击
	if (ui.TotalWificheckBox2->checkState() == Qt::CheckState::Checked)
	{
		//ui.TotalWificheckBox_1->setDisabled(true);
		ui.TotalWificheckBox3->setDisabled(true);
		ui.TotalWificheckBox1->setDisabled(true);
	}
	//已被点击
	else if (ui.TotalWificheckBox2->checkState() == Qt::CheckState::Unchecked)
	{
		//ui.SegDowncheckBox_1->setDisabled(false);
		ui.TotalWificheckBox3->setDisabled(false);
		ui.TotalWificheckBox1->setDisabled(false);
	}
}
//int num = ui.comboBox->currentText().toInt();
//QMap<int, QTcpSocket*>::iterator it;
//if (LinkList->size())
//{
//	for ( it = LinkList->begin(); it != LinkList->end(); it++)
//		if (it.key() == ui.comboBox->currentText().toInt())
//			//if (it.key() == 1)
//		{
//			if (ui.SegTotalcheckBox_1->checkState() == Qt::CheckState::Unchecked)
//			{
//				ui.SegDowncheckBox_1->setDisabled(true);
//			}
//			else if (ui.SegTotalcheckBox_1->checkState() == Qt::CheckState::Checked)
//			{
//				ui.SegDowncheckBox_1->setDisabled(false);
//			}
//			//char SendInfo[] = "connect";//指令
//			//QByteArray block;
//			//QDataStream out(&block,QIODevice::WriteOnly);
//			//out.setVersion(QDataStream::Qt_5_0);
//			//out << quint8(sizeof(SendInfo))<<SendInfo;
//			//it.value()->write(block);
//			char SendInfo[] = "connect";//指令
//			char length[2];
//			memset(length,0,sizeof(length));
//			int len = sizeof(SendInfo) - 1;//去除后面的‘\0’所占长度
//			//整数转化为字符串
//			itoa(len, length, 10);
//			it.value()->write(length);
//			it.value()->write(SendInfo);
//			qDebug() << ui.comboBox->currentText();
//			QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(1));
//			ui.tableWidget->setItem(ui.comboBox->currentText().toInt() - 1, 0, newItem);
//		}
//	if(it==LinkList->end()&&LinkList->size()<num)
//		QMessageBox::information(this, tr("Notice"),
//			tr("Client %1 has not connected successfully").arg(num));
//}
//else
//{
//	QMessageBox::information(this, tr("Notice"),
//		tr("No Client has connected"));
//}
	
	




void QtGuiRemoteControl::UpdateNetSpeed(QString msg,int length)
{

	//ui.DownSpeed_1->setText(msg);
}

void QtGuiRemoteControl::UpdateDownSpeed1()
{
	//GetSpeedFromMysql(1);
	double speed= GetSpeedFromMysql(1);
	if (speed >= 0)
	{
		ui.lightButton_1->setAlarmColor(QColor(0, 255, 0));
		ui.lightButton_1->HoldAram();
		ui.lineEdit_1->setText(QString::number(speed, 10, 2) + "KB/s");
	}
	
}

void QtGuiRemoteControl::UpdateDownSpeed2()
{

	double speed = GetSpeedFromMysql(2);
	if (speed >= 0)
	{
		ui.lightButton_2->setAlarmColor(QColor(0, 255, 0));
		ui.lightButton_2->HoldAram();
		ui.lineEdit_2->setText(QString::number(speed, 10, 2) + "KB/s");
	}
}


void QtGuiRemoteControl::UpdateDownSpeed3()
{

	double speed = GetSpeedFromMysql(3);

	if (speed >= 0)
	{
		ui.lightButton_3->setAlarmColor(QColor(0, 255, 0));
		ui.lightButton_3->HoldAram();
		ui.lineEdit_3->setText(QString::number(speed, 10, 2) + "KB/s");
	}
}

void QtGuiRemoteControl::UpdateDownSpeed4()
{

	double speed = GetSpeedFromMysql(4);
	if (speed >= 0)
	{
		ui.lightButton_4->setAlarmColor(QColor(0, 255, 0));
		ui.lightButton_4->HoldAram();
		ui.lineEdit_4->setText(QString::number(speed, 10, 2) + "KB/s");
	}
}

void QtGuiRemoteControl::UpdateDownSpeed5()
{

	double speed = GetSpeedFromMysql(5);
	if (speed >= 0)
	{
		ui.lightButton_5->setAlarmColor(QColor(0, 255, 0));
		ui.lightButton_5->HoldAram();
		ui.lineEdit_5->setText(QString::number(speed, 10, 2) + "KB/s");
	}
}

void QtGuiRemoteControl::UpdateDownSpeed6()
{

	double speed = GetSpeedFromMysql(6);
	if (speed >= 0)
	{
		ui.lightButton_6->setAlarmColor(QColor(0, 255, 0));
		ui.lightButton_6->HoldAram();
		ui.lineEdit_6->setText(QString::number(speed, 10, 2) + "KB/s");
	}
}

double QtGuiRemoteControl::GetSpeedFromMysql(int id)
{
	//addDatabase（）来创建一个连接，调用这个函数时，我们可以传递我们要访问哪种类型的数据库
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");     //驱动 


	/*
	*test
	*/
	//DatabaseName ---terminal
	//UserName ---root
	//PassWd ----1308
	
	
	db.setHostName(HostName);          //数据库地址，一般都是本地，就填localhost就可以 
	db.setDatabaseName(baseName);      //数据库名，根据你Mysql里面的数据库名称来填写，比如我Mysql里面有个数据库叫test，可以用Navicat软件看自己的数据库名字
	db.setUserName(UserName);          //用户名，一般是本地用户，就填root就可以
	db.setPassword(PassWd);            //密码，填写你自己的Mysql登陆密码，为了保密我这里用*代替我的密码
	db.setPort(3306);                  //端口默认的是3306，可以不用写 
	//QString table = "speed";
	if (db.open())
	{
		//QMessageBox::warning(NULL, QStringLiteral("提示"), "open ok", QMessageBox::Yes);
		QSqlQuery query;
		//QString sql_temp = QString("SELECT * from %1 where device_ID=%2 order by Time ASC").arg(Table).arg(id);



		QString sql_temp = QString("select * from %1 where ID in (SELECT max(ID) from %1 where device_ID=%2)").arg(Table).arg(id);
		//qDebug() << sql_temp;      
		//执行sql语句并判断执行结果
		/*if (!query.exec(sql_temp))
		{
			QSqlError lastError = query.lastError();
			qDebug() << lastError.driverText() << QString(QObject::tr("select failed!"));
			return -1;
		}*/
		////遍历数据库：
		//QSqlQuery query;
		////组包
		//QString sql = QString("select temperature,humidity from data where num like '%' ");
		////执行SQL语句
		bool result;
		QTime timer;
		timer.start();
		result = query.exec(sql_temp);
		int runtime = timer.elapsed(); //gets the runtime in ms
		/*result = query.exec("INSERT INTO speed1 (ID, Speed, Time) "
			"VALUES (1001, '34.5', '12:45')");*/
		if (result)
			qDebug() << "exec success spend time:" << runtime << "ms" << endl;
		else
			qDebug() << "exec failed spend time:" << runtime << "ms" << endl;

		////获取内容
		double speed=-1;
		
		while (query.next())
		{
			 speed= query.value("Speed").toDouble();
			//QString  humidity = query.value(1).toString();
			
			
		}
		qDebug() << "id " << id;
		qDebug() << "speed" << speed << endl;
		return speed;
		////遍历数据库 
		//QSqlQuery query;
		//query.exec("select * from users");
		////指向第二条记录
		//query.seek(1);
		////获取当前行的记录                                                   
		//QSqlRecord record = query.record();
		////获取字段中记录的值
		//QString id = record.value("ID").toString();
		//QString name = record.value("name").toString();
		//qDebug() << "name:" << name;

	}
	else
	{
		QMessageBox::warning(NULL, QStringLiteral("提示"), "open mysql failed", QMessageBox::Yes);
	}
	db.close();
	return -1;
}

void QtGuiRemoteControl::StartTimer(int id)
{

	QTimer *timer = new QTimer(this);
	qDebug() << "ptimer:" << timer << endl;
	timerlist[id] = timer;
	switch (id)
	{
	case 1:
		connect(timer, SIGNAL(timeout()), this, SLOT(UpdateDownSpeed1()));
		timer->start(3000);
		break;
	case 2:
		connect(timer, SIGNAL(timeout()), this, SLOT(UpdateDownSpeed2()));
		timer->start(3000);
		break;
	case 3:
		connect(timer, SIGNAL(timeout()), this, SLOT(UpdateDownSpeed3()));
		timer->start(3000);
		break;
	case 4:
		connect(timer, SIGNAL(timeout()), this, SLOT(UpdateDownSpeed4()));
		timer->start(3000);
		break;
	case 5:
		connect(timer, SIGNAL(timeout()), this, SLOT(UpdateDownSpeed5()));
		timer->start(3000);
		break;
	case 6:
		connect(timer, SIGNAL(timeout()), this, SLOT(UpdateDownSpeed6()));
		timer->start(3000);
		break;
	default:
		break;
	}
	
}

void QtGuiRemoteControl::StopTimer(int id)
{
	int i = 0;
	if (id > 0)
	{
		timerlist[id]->stop();
		qDebug() << "ptimer:" << timerlist[id] << endl;
	}
	switch (id)
	{
	case 1:
		ui.lightButton_1->setLightBlue();
		ui.lineEdit_1->setText(0);
		break;
	case 2:
		ui.lightButton_2->setLightBlue();
		ui.lineEdit_2->setText(0);
		break;
	case 3:
		ui.lightButton_3->setLightBlue();
		ui.lineEdit_3->setText(0);
		break;
	case 4:
		ui.lightButton_4->setLightBlue();
		ui.lineEdit_4->setText(0);
		break;
	case 5:
		ui.lightButton_5->setLightBlue();
		ui.lineEdit_5->setText(0);
		break;
	case 6:
		ui.lightButton_6->setLightBlue();
		ui.lineEdit_6->setText(0);
		break;
	case -1:
		for (i = 0; i < 150; i++)
		{
			ui.lineEdit_1->setText(0);
			ui.lineEdit_2->setText(0);
			ui.lineEdit_3->setText(0);
			ui.lineEdit_4->setText(0);
			ui.lineEdit_5->setText(0);
			ui.lineEdit_6->setText(0);
			timerlist[i]->stop();
		}
		break;
	case -2:
		for (i = 0; i < 100; i++)
		{
			ui.lineEdit_1->setText(0);
			ui.lineEdit_2->setText(0);
			ui.lineEdit_3->setText(0);
			ui.lineEdit_4->setText(0);
			timerlist[i]->stop();
		}
		break;
	case -3:
		for (i = 0; i < 50; i++)
		{
			ui.lineEdit_1->setText(0);
			ui.lineEdit_2->setText(0);
			timerlist[i]->stop();
		}
		break;
	default:
		break;
	}
}


void QtGuiRemoteControl::errormsg(int id)
{
	QString msg = id + "is offline";
	emit stopdown(id);
	/*witch (id)
	{
	case 1:
		ui.lineEdit_1->setText(0);
		emit 
		break;
	default:
		break;
	}*/
	QMessageBox::warning(NULL, QStringLiteral("提示"),"current id is offline", QMessageBox::Yes);
}


void QtGuiRemoteControl::MultiDownFile(int devicecount)
{
	switch (devicecount)
	{
	//开启所有设备
	case 150:
		DownLoadFile1();
		DownLoadFile2();
		DownLoadFile3();
		DownLoadFile4();
		DownLoadFile5();
		DownLoadFile6();
		break;
	//开启前100个设备
	case 100:
		DownLoadFile1();
		DownLoadFile2();
		DownLoadFile3();
		DownLoadFile4();
		break;
	//开启前50个设备
	case 50:
		DownLoadFile1();
		DownLoadFile2();
		break;
	default:
		break;
	}
}

void QtGuiRemoteControl::TotalDownFile1()
{

	if (ui.TotalWificheckBox1->checkState() == Qt::CheckState::Unchecked)
	{
		
			ui.TotalWificheckBox_1->setChecked(false);
			ui.TotalWificheckBox_2->setChecked(false);
			ui.TotalWificheckBox_3->setChecked(false);
			ui.TotalWificheckBox_4->setChecked(false);
			ui.TotalWificheckBox_5->setChecked(false);
			ui.TotalWificheckBox_6->setChecked(false);
		
		char tmp[] = "#7###";//命令 id 
		SendMsg(tmp);
		emit stopdown(-1);
		return;
	}
	
	
		ui.TotalWificheckBox_1->setChecked(true);
		ui.TotalWificheckBox_2->setChecked(true);
		ui.TotalWificheckBox_3->setChecked(true);
		ui.TotalWificheckBox_4->setChecked(true);
		ui.TotalWificheckBox_5->setChecked(true);
		ui.TotalWificheckBox_6->setChecked(true);
	
	char tmp[] = "#6###";//命令 id 
	SendMsg(tmp);

	emit multicast(150);
}


void QtGuiRemoteControl::TotalDownFile2()
{
	if(ui.TotalWificheckBox2->checkState() == Qt::CheckState::Unchecked)
	{
		ui.TotalWificheckBox_1->setChecked(false);
		ui.TotalWificheckBox_2->setChecked(false);
		char tmp[] = "#9###";//命令 id 
		SendMsg(tmp);
		emit stopdown(-3);
		return;
	}
	
		
		
	ui.TotalWificheckBox_1->setChecked(true);
	ui.TotalWificheckBox_2->setChecked(true);
	char tmp[] = "#8###";//命令 id 
	SendMsg(tmp);
	emit multicast(50);
}

void QtGuiRemoteControl::TotalDownFile3()
{
	if(ui.TotalWificheckBox3->checkState() == Qt::CheckState::Unchecked)
	{
		ui.TotalWificheckBox_1->setChecked(false);
		ui.TotalWificheckBox_2->setChecked(false);
		ui.TotalWificheckBox_3->setChecked(false);
		ui.TotalWificheckBox_4->setChecked(false);
		char tmp[] = "#11###";//命令 id 
		SendMsg(tmp);
		emit stopdown(-2);
		return;
	}
	ui.TotalWificheckBox_1->setChecked(true);
	ui.TotalWificheckBox_2->setChecked(true);
	ui.TotalWificheckBox_3->setChecked(true);
	ui.TotalWificheckBox_4->setChecked(true);
	char tmp[] = "#10###";//命令 id 
	SendMsg(tmp);
	emit multicast(100);
}