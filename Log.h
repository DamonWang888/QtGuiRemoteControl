#pragma once
#include<QString>
#include<QFile>
#include<QTextStream>
#include<QMap>
#include<QSet>
#include<qDebug>
class Log
{
	public:
		Log(QString FileName);
		~Log();
		void add(QString TimeQuantum, QSet<int>& WifiStatus, QSet<int>& IphoneStatus);
		void addWifi(QString TimeQuantum, QVector<int>& Status);
		void addIphone(QString TimeQuantum, QVector<int>& Status);
	private:
		QString FileName;
};