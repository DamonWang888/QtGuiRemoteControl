#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent, QTcpSocket *ptcpsocket)
:tcpsocket(ptcpsocket)
{
	//�ͻ��˷������ݹ����ͻᴥ��readyRead�ź�
	connect(tcpsocket, &TcpClientSocket::readyRead, this, &TcpClientSocket::receivedata);
	connect(tcpsocket, &TcpClientSocket::disconnected, this, &TcpClientSocket::slotclientdisconnected);
}

void TcpClientSocket::receivedata()
{
	//    while(bytesAvailable() > 0)
	//    {
	//        int length = bytesAvailable();
	//        char buf[1024]; //������Ż�ȡ������
	//        read(buf, length);
	//        QString msg = buf;
	//        //���źŸ����棬�ý�����ʾ��¼�ߵ���Ϣ
	//        emit updateserver(msg, length);
	//    }
	qDebug() << "receivedata";
	int length = 12;
	QByteArray array = tcpsocket->readAll();
	QString msg = array;
	emit updateserver(msg, length);
}

void TcpClientSocket::slotclientdisconnected()
{
	emit clientdisconnected(tcpsocket);
}