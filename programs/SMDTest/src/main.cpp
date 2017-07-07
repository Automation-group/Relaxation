#include <QApplication>
#include <QTextCodec>
#include <QStringList>
#include <QtAlgorithms>
#include <QFile>
#include <QtDebug>

#include "MainDlg.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	MainDialog mainDlg;
	mainDlg.show();
	/*
	 QextSerialPort smdSP("/dev/ttyS0");
	 smdSP.setBaudRate (BAUD115200);
	 smdSP.setDataBits (DATA_8);
	 smdSP.setParity (PAR_NONE);
	 smdSP.setStopBits (STOP_2);
	 smdSP.setFlowControl (FLOW_HARDWARE);
	 smdSP.setTimeout (0, 500);
	 smdSP.open (QIODevice::ReadWrite | QIODevice::Unbuffered);
	 
	 QlfSMD smd (&smdSP);
	 smd.setFrequency (400.0);
	 smd.enable ();
	 
	 smd.setConformity (QlfSMD::MoveUpForCW);
	 
	 int result = app.exec ();
	 smd.disable ();
	 */
	return app.exec();
}
