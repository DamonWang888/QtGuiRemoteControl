#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_wifiControl.h"
#include"qtcpserver.h"
#include<QNetworkInterface>
#include<QFile>
#include<QTcpSocket>
#include <QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QSqlQuery>//执行sql语句相关
#include <QSqlDatabase>//连接数据库相关
//#include <QSqlError>//数据库错误相关 
#include <QSqlRecord>//数据库记录相关 
#include <QSqlQueryModel>//数据查询模型
#include <QMessageBox>
#include<qmessagebox.h>
#include"Mytimer.h"
#include<windows.h>

static int SERVER_PORT = 2000;

class QtGuiRemoteControl : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiRemoteControl(QWidget *parent = Q_NULLPTR, QTcpSocket*tcpSocket = NULL, QString HostName = "",
		QString baseName = "", QString Table="", QString UserName = "", QString PassWd = "");
	double GetSpeedFromMysql(int id);
	~QtGuiRemoteControl();
	void SendMsg(char *data);

private:
	Ui::QtGuiRemoteControlClass ui;
	QTcpSocket *tcpSocket;
	QDataStream FileStream;
	//QMap<int, QTcpSocket*> *LinkList;
	QTimer **timerlist;
	QString HostName;
	QString baseName;
	QString UserName;
	QString PassWd;
	QString Table;

signals:
	void getspeed(int);
	void stopdown(int);
	void multicast(int);


public slots:
	void Update1();
	void Update2();
	void Update3();
	void DownLoadFile1();
	void DownLoadFile2();
	void DownLoadFile3();
	void DownLoadFile4();
	void DownLoadFile5();
	void DownLoadFile6();
	void UpdateNetSpeed(QString msg, int length);

	void UpdateDownSpeed1();
	void UpdateDownSpeed2();
	void UpdateDownSpeed3();
	void UpdateDownSpeed4();
	void UpdateDownSpeed5();
	void UpdateDownSpeed6();

	void StartTimer(int id);
	void StopTimer(int id);
	void errormsg(int id);

	void MultiDownFile(int devicecount);
	void TotalDownFile1();
	void TotalDownFile2();
	void TotalDownFile3();
};
