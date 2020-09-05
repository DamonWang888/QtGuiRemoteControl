
#pragma execution_character_set("utf-8")
#include "TotalMenu.h"
#include"IphoneControl.h"
#include"SelfCheck.h"
#include"CurSelfCheck.h"
#include"WifiControl.h"
TotalMenu::TotalMenu(QWidget*parent)
: QWidget(parent), tcpSocket(new QTcpSocket(this))
{
	ui.setupUi(this);
	ReadConfig();
	QDateTime local(QDateTime::currentDateTime());
	/*QString localTime = local.toString("yyyy-MM-dd:hh:mm:ss");
	QString curTime = local.time().toString("hh:mm:ss");*/
	QString curDate = local.date().toString("yyyy-MM-dd");
	pLog = new Log(curDate+QString("日志.csv"));
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	
	for (int i = 0; i < ipAddressesList.size(); ++i) 
	{
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
			ipAddressesList.at(i).toIPv4Address())
		{
			ipAddress = ipAddressesList.at(i).toString();
			break;
		}
	}
	//change background color

	this->setStyleSheet("background-color:rgb(	173 ,216 ,230);");
	
	QColor col1 = QColor(255 ,250, 205);
	if (col1.isValid()) {
		QString qss = QString("background-color: %1").arg(col1.name());
		ui.ButtonPhone->setStyleSheet(qss);
	}

	QColor col2 = QColor(255, 130, 171);
	if (col2.isValid()) {
		QString qss = QString("background-color: %1").arg(col2.name());
		ui.ButtonWifi->setStyleSheet(qss);
	}

	QColor col3 = QColor(255, 211 ,155);
	if (col3.isValid()) {
		QString qss = QString("background-color: %1").arg(col3.name());
		ui.ButtonSelfCheck->setStyleSheet(qss);
	}
	
	// if we did not find one, use IPv4 localhost
	if (ipAddress.isEmpty())
		ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

	qDebug() << ipAddress;
	ui.EquipMentLabel->setText(QString::number(0, 10, 0));
	

	
	connect(this, &TotalMenu::ConnectSuccess, this, &TotalMenu::RequestInitedData);
	connect(tcpSocket, &QIODevice::readyRead, this,&TotalMenu::readStatusFromServer);
	connect(ui.ButtonPhone,SIGNAL(clicked()),this,SLOT(OnClickedButtonPhone()));
	connect(ui.ButtonWifi, SIGNAL(clicked()), this,SLOT(OnClickedButtonWifi()));
	connect(ui.ButtonSelfCheck, SIGNAL(clicked()), this, SLOT(OnClickedButtonSelfCheck()));
	
}
//Server.listen(QHostAddress::Any, SERVER_PORT);
/*QMap<int, QTcpSocket*> link;
link.clear();*/
//LinkList.clear();
//QString ipAddress;
// use the first non-localhost IPv4 address
//this->setGeometry(173 ,216 ,230, 100);
//this->show();

/*ui.Statuslabel->setText(tr("The server is running on IP: %1 port: %2"
" Run the  Client example now.").arg(ipAddress).arg(Server.serverPort()));*/

//connect(&Server, SIGNAL(newConnection()), this, SLOT(ServerNewConnection()));
//connect(&Server, SIGNAL(readyRead()), this, SLOT(ServerNewMessage()));
//connect(&Server, SIGNAL(newConnection()), this, SLOT(ServerNewConnection()));

//connect(tcpSocket, &QTcpSocket::connected, this,&TotalMenu::RequestInitedData);

TotalMenu::~TotalMenu()
{
	//qDebug() << LinkList.size();
	/*if (LinkList.size())
	{
		QMap<int, QTcpSocket*>::iterator it;
		for (it = LinkList.begin(); it != LinkList.end(); it++)
			delete it.value();
	}*/
}
void TotalMenu::RequestInitedData()
{
	qDebug() << "RequestInitedData";
	SendMacString();
	
}

void TotalMenu::OnClickedButtonPhone()
{
	qDebug() << "OnClickedButtonPhone";
	/*IphoneControl *qI=new IphoneControl(NULL, tcpSocket);
	pIphonecontrol = qI;*/
	if (pNewIphoneControl != NULL)
		return;
	NewIphoneControl* qI = new NewIphoneControl(this,pLog,NULL, tcpSocket);
	//NewIphoneControl* qI = NewIphoneControl::getInstance(pLog, NULL, tcpSocket);
	qI->setAttribute(Qt::WA_DeleteOnClose);
	pNewIphoneControl = qI;
	qI->show();
}
void TotalMenu::OnClickedButtonWifi()
{
	qDebug() << "OnClickedButtonWifi";
	if (pNewWifiControl != NULL)
		return;
	NewWifiControl* qI = new NewWifiControl(this,pLog,NULL,tcpSocket);
	//NewWifiControl* qI = new NewWifiControl(pLog, NULL, tcpSocket);
	qI->setAttribute(Qt::WA_DeleteOnClose);
	pNewWifiControl = qI;
	qI->show();
}
/*if (ui.lineEditconf_1->cursorPosition() == 0 || ui.lineEditconf_2->cursorPosition() == 0 ||
	ui.lineEditconf_3->cursorPosition() == 0 || ui.lineEditconf_4->cursorPosition() == 0
	|| ui.lineEditconf_5->cursorPosition() == 0
	)
{
	QMessageBox::warning(NULL, QStringLiteral("提示"),  "mysql info exist null", QMessageBox::Yes);
	return;
}
qDebug() <<"+++++++++++++++"<< ui.lineEditconf_1->cursorPosition();
HostName = ui.lineEditconf_1->text();
baseName = ui.lineEditconf_2->text();
UserName = ui.lineEditconf_3->text();
PassWd = ui.lineEditconf_4->text();
Table = ui.lineEditconf_5->text();*/
//qDebug() << "OnClickedButtonWifi\n"<< HostName<<" "<< baseName<<" "<<Table<<" "<< UserName<<" "<< PassWd;
/*
QtGuiRemoteControl *qW=new QtGuiRemoteControl(NULL,tcpSocket, HostName, baseName,Table, UserName, PassWd);
connect(this,&TotalMenu::receivespeed,qW,&QtGuiRemoteControl::UpdateNetSpeed);
pwificontrol = qW;
connect(this,&TotalMenu::deviceoffline,pwificontrol, &QtGuiRemoteControl::errormsg);
qW->show();
*/
	
/*IphoneControl *qI=new IphoneControl(NULL, tcpSocket);
pIphonecontrol = qI;*/

void TotalMenu::ServerNewConnection()
{
	//qDebug() << "onNewConnection";
	//QTcpSocket* tcp = Server.nextPendingConnection();     //获取新的客户端信息
	//QString info = tcp->peerAddress().toString() + ":" + QString("%1").arg(tcp->peerPort());
	////ui->targetObject->addItem(info);
	//QMessageBox::information(this, "Notice", QString("New client connected:%1").arg(info), QMessageBox::Ok);
	//tcp->setObjectName(info);       //设置名称,方便查找
	//LinkList.insert(++EquipMentNum,tcp);
	//TcpClientSocket *tcpclientsocket = new TcpClientSocket(this,tcp);
	//tcpclientsocketlist.append(tcpclientsocket);
	//connect(tcpclientsocket,&TcpClientSocket::updateserver,this,&TotalMenu::ServerNewMessage);
	//connect(tcpclientsocket,&TcpClientSocket::clientdisconnected,this,&TotalMenu::updateLinkList);
	////connect(tcp,&QTcpSocket::readyRead,this,&TotalMenu::ServerNewMessage);
}

void TotalMenu::SendMacString()
{
	QString Mac = getHostMacAddress();
	QByteArray ba = Mac.toLatin1();
	char *sendmsg =(char*)malloc(64);
	memset(sendmsg,0,sizeof(sendmsg));
	char tmp[] = "#5#0#";//命令 id 
	memcpy(sendmsg, tmp,sizeof(tmp));
	strcat(sendmsg,ba.data());//数据
	strcat(sendmsg,"#");//结尾
	tcpSocket->write(sendmsg); 
	delete sendmsg;
}

void TotalMenu::readStatusFromServer()
{
	int ID = -1;
	int commod = -1;
	int len = -1;
	char *data = new char[30];
	char *tmpmsg=NULL;
	//memset(tmpmsg, 0, sizeof(tmpmsg));
	int sz = 0;
	QString msgheader;
	memset(data, 0, sizeof(data));
	qDebug() << "readStatusFromServer";
	QByteArray array = tcpSocket->readAll();
	QString msg = array;
	QByteArray ba = msg.toLatin1();//在字符串后加上空格
	tmpmsg = ba.data();
	len = msg.length();
	//len = sizeof(tmpmsg)-1;
	ParseMsg(tmpmsg,len,&ID,&commod,data);
	qDebug("[server]len %d,commod %d,ID %d,data %s\n",len, commod, ID,data);
	switch (commod)
	{
	case 5:
		msgheader = "Total equipments:";
		//msgheader = "总设备数:";
		ui.EquipMentLabel->setText(QString(data));
		//ui.Statuslabel->setText(msgheader + data);
		break;
	case 6:
		emit deviceoffline(ID);
		break;
		//自检信息返回
	case 10:
		emit UpdatesSelfcheck(ID,data);
		break;
	default:
		break;
	}
	
	
	//qDebug() << msg;



}


//多客户端解析数据
void TotalMenu::ServerNewMessage(QString msg, int length)
{
	qDebug() << msg;
	emit(receivespeed(msg,length));
}
/*QByteArray message;
QMap<int, QTcpSocket*>::iterator it;
for ( it = LinkList.begin(); it != LinkList.end(); it++)
{
	message = it.value()->readAll();
	if (!message.isEmpty())
		qDebug() << message;
}
*/

/*QByteArray buffer;
//读取缓冲区数据
buffer = socket->readAll();
if (!buffer.isEmpty())
{
	QString str = ui->textEdit_Recv->toPlainText();
	str += tr(buffer);
	//刷新显示
	ui->textEdit_Recv->setText(str);
}
*/

void TotalMenu::incomingConnection( int socketDescriptor)
{
	qDebug() << "new connection";
	TcpClientSocket *tcpclientsocket = new TcpClientSocket(this);//只要有新的连接就生成一个新的通信套接字
	//将新创建的通信套接字描述符指定为参数socketdescriptor
	tcpclientsocket->setSocketDescriptor(socketDescriptor);

	//将这个套接字加入客户端套接字列表中
	tcpclientsocketlist.append(tcpclientsocket);


	//接收到tcpclientsocket发送过来的更新界面的信号
	connect(tcpclientsocket, &TcpClientSocket::updateserver, this, &TotalMenu::ServerNewMessage);
	//connect(tcpclientsocket, &TcpClientSocket::clientdisconnected, this, &Server::slotclientdisconnect);
	
}

void TotalMenu::updateLinkList(QTcpSocket *ptcp)
{
	int num = 0;
	QMap<int, QTcpSocket*> LinkListTmp;
	LinkListTmp.clear();
	QString info = ptcp->peerAddress().toString() + ":" + QString("%1").arg(ptcp->peerPort());
	//ui->targetObject->addItem(info);
	QMessageBox::information(this, "Notice", QString("client disconnected:%1").arg(info), QMessageBox::Ok);
	QMap<int, QTcpSocket*>::iterator it;
}
/*if (LinkList.size() < 0)
	return;
for (it = LinkList.begin(); it != LinkList.end()&&(*it!=nullptr); it++)
	if (it.value() == ptcp)
	{
		LinkList.remove(it.key());
		break;
	}
if (LinkList.size())
{
	for (it = LinkList.begin(); it != LinkList.end()&& (*it != nullptr); it++)
		LinkListTmp.insert(++num, it.value());
	LinkList.clear();
	for (it = LinkListTmp.begin(); it != LinkListTmp.end()&& (*it != nullptr); it++)
		LinkList.insert(it.key(), it.value());
	EquipMentNum = LinkList.size();
}
else
	EquipMentNum = 0;*/

QString TotalMenu::getHostMacAddress()
{
	QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
	int nCnt = nets.count();
	QString strMacAddr = "";
	for (int i = 0; i < nCnt; i++)
	{
		// 如果此网络接口被激活并且正在运行并且不是回环地址，则就是我们需要找的Mac地址
		if (nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
		{
			strMacAddr = nets[i].hardwareAddress();
			break;
		}
	}
	return strMacAddr;
}


void TotalMenu::ConnectToServer()
{
	//tcpSocket->connectToHost("113.54.153.232", 9995);
	tcpSocket->connectToHost(ServerIp, ServerPort.toInt());
	bool connected = tcpSocket->waitForConnected();
	if (connected)
	{
		
		/*qDebug() << "Connect to server successfully";
		char msg[] = "#5";
		tcpSocket->write(msg);*/
		emit ConnectSuccess();
	}
}


int TotalMenu::ParseMsg( char *msg,int sz, int *ID, int *Commod, char Data[])
{
	if (sz > 0)
	{
		int i = 1;
		std::string commod = "";  
		std::string id = "";
		std::string data = "";
		while (i < sz && msg[i] != '#')
		{
			commod += msg[i];
			i++;
		}
		i++;
		while (i < sz && msg[i] != '#')
		{
			id += msg[i];
			i++;
		}
		i++;
		while (i < sz && msg[i] != '#')
		{
			data += msg[i];
			i++;
		}
		if (sizeof(commod.c_str()))
			*Commod = atoi(commod.c_str());
		if (sizeof(id.c_str()))
			*ID = atoi(id.c_str());
		if (sizeof(data.c_str()))
		{
			memcpy(Data, data.c_str(), 21);
			//qDebug() << "[server]data:" << Data << endl;
			printf("[server]data:%s\n", data.c_str());
		}
		return 1;
	}
	return 1;

}

void TotalMenu::ReadConfig()
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
		if (list1.at(0) == "HostName") //主机
		{
			HostName = list1.at(1);
			HostName.replace(QString("\n"), QString(""));
		}
		if (list1.at(0) == "baseName") //数据库
		{
			baseName = list1.at(1);
			baseName.replace(QString("\n"), QString(""));
		}
		if (list1.at(0) == "Table") //表
		{
			Table = list1.at(1);
			Table.replace(QString("\n"), QString(""));
		}
		if (list1.at(0) == "UserName") //用户名
		{
			UserName = list1.at(1);
			UserName.replace(QString("\n"), QString(""));
		}
		if (list1.at(0) == "PassWd") //密码
		{
			PassWd = list1.at(1);
			PassWd.replace(QString("\n"), QString(""));
		}
		if (list1.at(0) == "ServerIp") //服务器ip
		{
			ServerIp = list1.at(1);
			ServerIp.replace(QString("\n"), QString(""));
		}
		if (list1.at(0) == "ServerPort") //服务器ip
		{
			ServerPort = list1.at(1);
			ServerPort.replace(QString("\n"), QString(""));
		}
		//qDebug() << list1;
		displayString.append(str);
	}
}
//qDebug() << "ReadConfig\n" << HostName << " " << baseName << " " << Table << " " << UserName << " " << PassWd;
/*ui->textEdit->clear();
ui->textEdit->setPlainText(displayString);*/
void TotalMenu::OnClickedButtonSelfCheck()
{
	qDebug() << "OnClickedButtonSelfCheck";
	if (pNewSelfCheck != NULL)
		return;
	SendSelfCheckCommod();
	NewSelfCheck* qS = new NewSelfCheck(this,NULL, tcpSocket);
	pNewSelfCheck = qS;
	connect(this,SIGNAL(UpdatesSelfcheck(int ,char*)),pNewSelfCheck,SLOT(UpdateDeviceStatus(int ,char*)));
	qS->setAttribute(Qt::WA_DeleteOnClose);
	qS->show();
}
/*CurSelfCheck* qS = new CurSelfCheck(NULL, tcpSocket);
pCurSelfCheck = qS;*/

/*SelfCheck* qS = new SelfCheck(NULL, tcpSocket);
pSelfCheck = qS;*/

void TotalMenu::InitWifiPointer()
{
	pNewWifiControl = NULL;
}


void TotalMenu::InitIphonePointer()
{
	pNewIphoneControl = NULL;
}
void TotalMenu::InitSelfCheckPointer()
{
	pNewSelfCheck = NULL;
}
void TotalMenu::SendSelfCheckCommod()
{
	char tmp[32];//命令 id 
	memset(tmp, 0, sizeof(tmp));
	snprintf(tmp, sizeof(tmp) - 1, "#0#A##");
	//qDebug() << "sizeof(tmp):" << sizeof(tmp);
	tcpSocket->write(tmp);
}