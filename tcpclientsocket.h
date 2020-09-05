#pragma once
#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QTcpSocket>

class TcpClientSocket:public QTcpSocket
{
	Q_OBJECT //����������Ϊ��ʵ���źźͲ۵�ͨ��
public:
	TcpClientSocket(QObject *parent = 0, QTcpSocket *tcpsocket=NULL);
protected slots:
	void receivedata();//����readyRead�źŶ�ȡ����
	void slotclientdisconnected();//�ͻ��˶Ͽ����Ӵ���disconnected�źţ�����ۺ���������������ź�

signals:
	void updateserver(QString, int);//��������tcpserver��Ҫ���½������ʾ
	void clientdisconnected(QTcpSocket *tcpsocket); //����server�пͻ��˶Ͽ�����

private:
	QTcpSocket *tcpsocket;
};

#endif // TCPCLIENTSOCKET_H