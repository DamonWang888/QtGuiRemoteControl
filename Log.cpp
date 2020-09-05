#pragma execution_character_set("utf-8")
#include"Log.h"
Log::Log(QString filename) :FileName(filename)
{
	QFile file(FileName);
	QString Data = " ";
	if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
		QTextStream stream(&file);
		if (!file.size())
		{
			Data = "时间段,设备,个数,具体设备\n";
			file.write(Data.toLocal8Bit());
		}
	}
}

void Log::add(QString TimeQuantum, QSet<int>& WifiStatus, QSet<int>& IphoneStatus)
{
    QFile file(FileName);
    QString Data = " ";
    QString Type1 = "手机";
    QString Type2 = "WIFI";
    int terminalid = -1;
    int deviceid = -1;
    if (file.open(QIODevice::ReadWrite| QIODevice::Append)) {
        QTextStream stream(&file);
		if (WifiStatus.size())
			stream << TimeQuantum << "," << Type2 << "," << WifiStatus.size();
		foreach(const int& value, WifiStatus)
		{
			if (value % 6 == 0)
			{
				terminalid = value / 6;
				deviceid = 6;
			}
			else
			{
				terminalid = value / 6 + 1;
				deviceid = value % 6;
			}
			stream << "," << terminalid<< QString("_")<<deviceid;
		}
		stream << endl;
   
		if (IphoneStatus.size())
			stream << TimeQuantum << "," << Type1 << "," << IphoneStatus.size();
		foreach(const int& value, IphoneStatus)
		{
			if (value % 6 == 0)
			{
				terminalid = value / 6;
				deviceid = 6;
			}
			else
			{
				terminalid = value / 6 + 1;
				deviceid = value % 6;
			}
			
			stream << "," << terminalid << QString("_") << deviceid;
		}
		stream << endl;
    }
}
void Log::addWifi(QString TimeQuantum, QVector<int>& Status)
{
	QFile file(FileName);
	QString Data = " ";
	QString Type1 = "WIFI";
	int terminalid = -1;
	int deviceid = -1;
	if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
		QTextStream stream(&file);
		if (Status.size())
			stream << TimeQuantum << "," << Type1 << "," << Status.size();
		foreach(const int& value, Status)
		{
			if (value % 6 == 0)
			{
				terminalid = value / 6;
				deviceid = 6;
			}
			else
			{
				terminalid = value / 6 + 1;
				deviceid = value % 6;
			}
			stream << "," << terminalid << QString("_") << deviceid;
		}
		stream << endl;
	}
}

void Log::addIphone(QString TimeQuantum, QVector<int>& Status)
{
	QFile file(FileName);
	QString Data = " ";
	QString Type2 = "手机";
	int terminalid = -1;
	int deviceid = -1;
	if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
		QTextStream stream(&file);
		if (Status.size())
		{
			//qDebug() <<"FileName:"<<FileName<<"addIphone:"<< TimeQuantum <<"set size:"<< Status.size() << endl;
			stream << TimeQuantum << "," << Type2 << "," << Status.size();
		}
		foreach(const int& value, Status)
		{
			if (value % 6 == 0)
			{
				terminalid = value / 6;
				deviceid = 6;
			}
			else
			{
				terminalid = value / 6 + 1;
				deviceid = value % 6;
			}
			stream << "," << terminalid << QString("_") << deviceid;
		}
		stream << endl;
	}
}
//Type1 = Type1.toLocal8Bit();
/*if (!file.size())
{
    Data = "时间段,设备,个数,具体设备\n";
    file.write(Data.toLocal8Bit());
}*/
	//deviceid = value;
	//QString TmpData = terminalid + QString("_") + deviceid;
	/*QString TmpData = terminalid + QString("_") + deviceid;
	stream << "," << TmpData;*/
/*  QMap<int, QSet<int>>::const_iterator i = WifiStatus.constBegin();*/
/* while (i != WifiStatus.constEnd()) {
terminalid = i.key();*/
//++i;
//}
Log::~Log()
{

}