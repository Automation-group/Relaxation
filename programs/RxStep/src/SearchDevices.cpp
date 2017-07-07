#include "SearchDevices.h"
#include <qextserialport.h>
#include <QlfTUB.h>
#include <QlfSMD.h>

#include <QtDebug>
#include <QString>
#include <QProcess>
#include <QRegExp>

void SearchDevices::SearchDev(QString *portSMD, QString *portTUB)
{ 
  *portSMD = "";
  *portTUB = "";
  
  // Поиск всех подключённых устройств
  QProcess process;
  process.setProcessChannelMode(QProcess::SeparateChannels);
  process.setReadChannel(QProcess::StandardOutput);
  process.start("ls /dev", QIODevice::ReadWrite);
  process.waitForReadyRead (500);
  
  QString ports;
  QString buffer;
  ports = process.readAllStandardOutput();
  process.close();
  
  // Определение портов отвечающих SMD и TUB
  int sizeBuffer = 0;
  for (int i = 0; i<ports.size(); i++)
  {
    buffer[i-sizeBuffer] = ports[i];
    if (ports[i]=='\n'){
      QString portBuf = buffer;
      if (portBuf.remove(QRegExp("[\n\t\r 0123456789]"))=="ttyUSB")
      {
	QString portDev = "/dev/" + buffer.remove(QRegExp("[\n\t\r ]"));
	//qDebug() << portDev;
	if (*portSMD == "" && portDev!=*portTUB && SearchSMD(portDev))
	  *portSMD = portDev;
	if (*portTUB == "" && portDev!=*portSMD && SearchTUB(portDev))
	  *portTUB = portDev;
      }
      sizeBuffer = i;
      buffer = "";
    }
  }
}

bool SearchDevices::SearchSMD(QString port)
{
  bool ret = 0; 
  QextSerialPort smdSP;
  smdSP.setBaudRate(BAUD115200);
  smdSP.setDataBits(DATA_8);
  smdSP.setParity(PAR_NONE);
  smdSP.setStopBits(STOP_2);
  //smdSP.setFlowControl(FLOW_HARDWARE);
  smdSP.setFlowControl(FLOW_OFF);
  smdSP.setTimeout(0, 500);
  smdSP.setPortName(port);
  
  if (!smdSP.open(QIODevice::ReadWrite | QIODevice::Unbuffered)) {
    //qDebug() << QString::fromUtf8("Ошибка при инициализации последовательнго порта SMD");
    return ret;
  }

  smd = new QlfSMD (&smdSP);
  if (smd->testConnection())
  {
    //qDebug() << QString::fromUtf8("Ошибка подключения к SMD");
    ret = 1;
  }
  
  if (smd)
  {
    QlfSMD* temp = smd;
    smd = 0;
    delete temp;
  }
  smdSP.close();
  
  return ret;
}

bool SearchDevices::SearchTUB(QString port)
{
  bool ret = 0;
  QextSerialPort tubSP;
  tubSP.setBaudRate(BAUD115200);
  tubSP.setDataBits(DATA_8);
  tubSP.setParity(PAR_NONE);
  tubSP.setStopBits(STOP_2);
  //tubSP.setFlowControl(FLOW_HARDWARE);
  tubSP.setFlowControl(FLOW_OFF);
  tubSP.setTimeout(0, 500);
  tubSP.setPortName(port);
  
  if (!tubSP.open(QIODevice::ReadWrite | QIODevice::Unbuffered)) {
    //qDebug() << QString::fromUtf8("Ошибка при инициализации последовательнго порта TUB");
    return ret;
  }
  
  tub = new QlfTUB (&tubSP);
  if (tub->symbolState()) {
    //qDebug() << QString::fromUtf8("Ошибка подключения к TUB");
    ret = 1;
  }
  
  if (tub)
  {
    QlfTUB* temp = tub;
    tub = 0;
    delete temp;
  }
  tubSP.close();
  
  return ret;
}