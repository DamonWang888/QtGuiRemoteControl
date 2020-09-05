#include "IphoneControl.h"

IphoneControl::IphoneControl(QWidget *parent, QTcpSocket *tcpSocket)
	: QWidget(parent), tcpSocket(tcpSocket)
{
	ui.setupUi(this);
	//ui.NumberEdit->setDisabled(true);
	//ui.DownButton->setDisabled(true);
	//if (ui.NumEdit->text()== "")
		//ui.OnButton->setDisabled(true);
	//if (!ui.OnButton->isDown())
		//ui.DownButton->setDisabled(true);
	//ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//connect(ui.NumEdit,SIGNAL(editingFinished()),this,SLOT(UpdateNumberEdit()));
	//connect(ui.NumberEdit,SIGNAL(editingFinished()),this,SLOT(UpdateOnButton()));
	//connect(ui.OnButton,SIGNAL(clicked()),this,SLOT(OnPressOnButton()));
	//connect(ui.DownButton,SIGNAL(clicked()),this,SLOT(OnPressDownButton()));
	connect(ui.checkBox_1,SIGNAL(clicked()),this,SLOT(phonecall_1()));
	connect(ui.checkBox_2, SIGNAL(clicked()), this, SLOT(phonecall_2()));
	connect(ui.checkBox_3, SIGNAL(clicked()), this, SLOT(phonecall_3()));
	connect(ui.checkBox_4, SIGNAL(clicked()), this, SLOT(phonecall_4()));
	connect(ui.checkBox_5, SIGNAL(clicked()), this, SLOT(phonecall_5()));
	connect(ui.checkBox_6, SIGNAL(clicked()), this, SLOT(phonecall_6()));
	connect(ui.checkBox1, SIGNAL(clicked()), this, SLOT(totalphonecall_1()));
	connect(ui.checkBox2, SIGNAL(clicked()), this, SLOT(totalphonecall_2()));
	connect(ui.checkBox3, SIGNAL(clicked()), this, SLOT(totalphonecall_3()));
}

IphoneControl::~IphoneControl()
{
	
	
}
void IphoneControl::totalphonecall_1()
{
	//被点击
	if (ui.checkBox1->checkState() == Qt::CheckState::Checked)
	{
		qDebug() << "Update1 -----1-------";
		char tmp[] = "#12###";//命令 id 
		SendMsg(tmp);
		//ui.TotalWificheckBox_1->setDisabled(true);
		ui.checkBox2->setDisabled(true);
		ui.checkBox3->setDisabled(true);
	}
	//取消
	else if (ui.checkBox1->checkState() == Qt::CheckState::Unchecked)
	{
		//ui.SegDowncheckBox_1->setDisabled(false);

		qDebug() << "Update1 -----2-------";
		ui.checkBox2->setDisabled(false);
		ui.checkBox3->setDisabled(false);
	}

}

void IphoneControl::totalphonecall_2()
{
	//被点击
	if (ui.checkBox2->checkState() == Qt::CheckState::Checked)
	{
		
		char tmp[] = "#14###";//命令 id 
		SendMsg(tmp);
		//ui.TotalWificheckBox_1->setDisabled(true);
		ui.checkBox1->setDisabled(true);
		ui.checkBox3->setDisabled(true);
	}
	//取消
	else if (ui.checkBox2->checkState() == Qt::CheckState::Unchecked)
	{
		//ui.SegDowncheckBox_1->setDisabled(false);

		
		ui.checkBox1->setDisabled(false);
		ui.checkBox3->setDisabled(false);
	}
}

void IphoneControl::totalphonecall_3()
{
	//被点击
	if (ui.checkBox3->checkState() == Qt::CheckState::Checked)
	{
		
		char tmp[] = "#13###";//命令 id 
		SendMsg(tmp);
		//ui.TotalWificheckBox_1->setDisabled(true);
		ui.checkBox2->setDisabled(true);
		ui.checkBox1->setDisabled(true);
	}
	//取消
	else if (ui.checkBox3->checkState() == Qt::CheckState::Unchecked)
	{
		//ui.SegDowncheckBox_1->setDisabled(false);

		
		ui.checkBox2->setDisabled(false);
		ui.checkBox1->setDisabled(false);
	}
}
void IphoneControl::SendMsg(char *data)
{
	qDebug() << "SendMsg";
	char *sendmsg = (char*)malloc(64);
	memset(sendmsg, 0, sizeof(sendmsg));
	memcpy(sendmsg, data, sizeof(data));
	tcpSocket->write(sendmsg);
	delete sendmsg;
}

void IphoneControl::phonecall_1()
{
	//取消
	if (ui.checkBox_1->checkState() == Qt::CheckState::Unchecked)
	{
		return;
	}
	char tmp[32];//命令 id 
	memset(tmp, 0, sizeof(tmp));
	QString NumberStr = ui.NumberEdit_1->text();//电话号码
	QByteArray ba = NumberStr.toLatin1();
	//qDebug() << "ba.data:"<<ba.data();
	snprintf(tmp, sizeof(tmp) - 1, "#1#1#%s#", ba.data());
	SendMsg(tmp);
}
void IphoneControl::phonecall_2()
{
	//取消
	if (ui.checkBox_2->checkState() == Qt::CheckState::Unchecked)
	{
		return;
	}
	char tmp[32];//命令 id 
	memset(tmp, 0, sizeof(tmp));
	QString NumberStr = ui.NumberEdit_2->text();//电话号码
	QByteArray ba = NumberStr.toLatin1();
	//qDebug() << "ba.data:"<<ba.data();
	snprintf(tmp, sizeof(tmp) - 1, "#1#2#%s#", ba.data());
	SendMsg(tmp);
}
void IphoneControl::phonecall_3()
{
	//取消
	if (ui.checkBox_3->checkState() == Qt::CheckState::Unchecked)
	{
		return;
	}
	char tmp[32];//命令 id 
	memset(tmp, 0, sizeof(tmp));
	QString NumberStr = ui.NumberEdit_3->text();//电话号码
	QByteArray ba = NumberStr.toLatin1();
	//qDebug() << "ba.data:"<<ba.data();
	snprintf(tmp, sizeof(tmp) - 1, "#1#3#%s#", ba.data());
	SendMsg(tmp);
}
void IphoneControl::phonecall_4()
{
	//取消
	if (ui.checkBox_4->checkState() == Qt::CheckState::Unchecked)
	{
		return;
	}
	char tmp[32];//命令 id 
	memset(tmp, 0, sizeof(tmp));
	QString NumberStr = ui.NumberEdit_4->text();//电话号码
	QByteArray ba = NumberStr.toLatin1();
	//qDebug() << "ba.data:"<<ba.data();
	snprintf(tmp, sizeof(tmp) - 1, "#1#4#%s#", ba.data());
	
	SendMsg(tmp);
}
void IphoneControl::phonecall_5()
{
	//取消
	if (ui.checkBox_5->checkState() == Qt::CheckState::Unchecked)
	{
		return;
	}
	char tmp[32];//命令 id 
	memset(tmp, 0, sizeof(tmp));
	QString NumberStr = ui.NumberEdit_5->text();//电话号码
	QByteArray ba = NumberStr.toLatin1();
	//qDebug() << "ba.data:"<<ba.data();
	snprintf(tmp, sizeof(tmp) - 1, "#1#5#%s#", ba.data());
	SendMsg(tmp);
}
void IphoneControl::phonecall_6()
{
	//取消
	if (ui.checkBox_6->checkState() == Qt::CheckState::Unchecked)
	{
		return;
	}
	char tmp[32];//命令 id 
	memset(tmp,0,sizeof(tmp));
	QString NumberStr = ui.NumberEdit_6->text();//电话号码
	QByteArray ba = NumberStr.toLatin1();
	//qDebug() << "ba.data:"<<ba.data();
	snprintf(tmp,sizeof(tmp)-1,"#1#6#%s#",ba.data());
	SendMsg(tmp);
}

/*
void IphoneControl::OnPressOnButton()
{
	

	//给指定客户端发送电话号码
	QString NumStr = ui.NumEdit->text();
	int num = NumStr.toInt();//设备编号
	QString NumberStr = ui.NumberEdit->text();//电话号码
	QByteArray ba = NumberStr.toLatin1();
	char NumberLength[1];//电话号码长度字符串
	//char lengthpre[4];
	int length = ba.size();//电话号码长度
	if (length > 11)
	{
		QMessageBox::information(this, tr("Notice"),
			tr("the phone number is too long,please input again!"));
		return;
	}
	//int lengthplus=0;
	if(length<10)
		itoa(length,NumberLength,10 );//电话号码长度转字符串
	else switch (length)
	{
	case 10:
		NumberLength[0] = 'A';
		break;
	case 11:
		NumberLength[0] = 'B';
		break;
	case 12:
		NumberLength[0] = 'C';
		break;
	case 13:
		NumberLength[0] = 'D';
		break;
	case 14:
		NumberLength[0] = 'E';
		break;
	case 15:
		NumberLength[0] = 'F';
		break;
	default:
		break;
	}
	/*for (int i = 0; i < sizeof(NumberLength); i++)
		if (NumberLength[i] != '\0')
			lengthplus++;
		else
			break;
	itoa(lengthplus, lengthpre, 10);*/
	//if (LinkList->size())
	//{
	//	QMap<int, QTcpSocket*>::iterator it;
	//	for ( it= LinkList->begin(); it != LinkList->end(); it++)
	//	{
	//		if (it.key() == num)
	//		{
	//			/*it.value()->write(lengthpre);
	//			qDebug() << lengthpre<<sizeof(lengthpre);*/
	//			it.value()->write(NumberLength);
	//			qDebug() << NumberLength;
	//			it.value()->write(ba.data());
	//			qDebug() << ba.data();
	//			QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(1));
	//			ui.tableWidget->setItem(num - 1, 0, newItem);

	//			ui.OnButton->setDisabled(true);
	//			ui.DownButton->setDisabled(false);
	//			ui.NumEdit->setDisabled(true);
	//			break;
	//		}
	//	}
	//	if(it==LinkList->end())
	//		QMessageBox::information(this, tr("Notice"),
	//			tr("Current Client has not connect,please input another number"));
	//	
	//}
	//else
	//{
	//	QMessageBox::information(this, tr("Notice"),
	//		tr("No Client is connecting successfully"));
	//}
//}*/

/*
void IphoneControl::OnPressDownButton()
{
	QString numstr = ui.NumEdit->text();
	int num = numstr.toInt();
	ui.DownButton->setDisabled(true);
	ui.OnButton->setDisabled(false);
	ui.NumEdit->setDisabled(false);
	QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(0));
	ui.tableWidget->setItem(num-1, 0, newItem);
}

void IphoneControl::UpdateOnButton()
{
	ui.NumberEdit->setDisabled(false);
	ui.OnButton->setDisabled(false);
}

void IphoneControl::UpdateNumberEdit()
{
	ui.NumberEdit->setDisabled(false);
}

*/