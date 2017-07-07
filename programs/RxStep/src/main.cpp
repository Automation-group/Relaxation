#include <QApplication>
#include <QTextCodec>
#include <QStringList>
#include <QtAlgorithms>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QMessageBox>

#define slots Q_SLOTS
#define signals Q_SIGNALS
#include <qextserialport.h>
#undef signals
#undef slots

#include <QtDebug>
#include <QlfTUB.h>
#include "RxForceSensor.h"
#include "debugSViewerDlg.h"
#include "RxSampling.h"
#include <QlfSMD.h>
#include "RxMainWindow.h"
#include "RxExperiment.h"
#include "RxStrainStep.h"
#include "RxSMD.h"
#include "RxLoading.h"
#include "RxIfBlock.h"
#include "RxStepCounterBlock.h"
#include "RxCalculator.h"
#include "RxDataSaver.h"
#include "RxUnloading.h"
#include "RxCreateReport.h"
#include "RxXmlSettings.h"
#include "ExperimentWizard.h"
#include "ssGlobal.h"
#include "RxForceStep.h"
#include <RxConfig.h>
#include "SearchDevices.h"

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

	QString rxconfig_filename = QString(RXCONFIG_FILENAME);
	qDebug() << "Config file:" << rxconfig_filename;

	if(!QDir().exists(rxconfig_filename))
		rxconfig_filename = "rxstep.conf";

	QSettings globalSettings(rxconfig_filename, QSettings::IniFormat);

	qDebug() << "Config file:" << rxconfig_filename;
	//qDebug() << "SMDSerialPort:" << globalSettings.value("SMDSerialPort").toString();
	//qDebug() << "TUBSerialPort:" << globalSettings.value("TUBSerialPort").toString();

	const double smd_mmps = globalSettings.value("SMD_MMPS").toDouble();
	qDebug() << "SMD_MMPS:" << smd_mmps << "mm per step";
	
	const int smd_invrot = globalSettings.value("SMD_INVROT").toInt();
	qDebug() << "SMD_INVROT:" << smd_invrot;
	
	const double smd_frec = globalSettings.value("SMD_FREC").toDouble();
	qDebug() << "SMD_FREC:" << smd_frec << "Hz";
	
	const double tub_coeff_a = globalSettings.value("TUB_COEFF_A").toDouble();
	const double tub_coeff_b = globalSettings.value("TUB_COEFF_B").toDouble();
	const double tub_coeff_c = globalSettings.value("TUB_COEFF_C").toDouble();
	const double tub_coeff_d = globalSettings.value("TUB_COEFF_D").toDouble();
        qDebug() << "TUB_COEFF_A:" << tub_coeff_a
		 << "TUB_COEFF_B:" << tub_coeff_b
		 << "TUB_COEFF_C:" << tub_coeff_c
		 << "TUB_COEFF_D:" << tub_coeff_d 
		 << "Force = A*code^3 + B*code^2 + C*code + D";
	
	QString portSMD = "";
	QString portTUB = "";
	while(portSMD == "" || portTUB == "")
	{
	  SearchDevices shDevices;
	  shDevices.SearchDev(&portSMD, &portTUB);
	  
	  qDebug() << "PortSMD: " << portSMD;
	  qDebug() << "PortTUB: " << portTUB << endl;
	  if (portSMD == "" || portTUB == "")
	  {
	    QMessageBox msgBox;
	    if (portSMD == "" && portTUB != "")
	    {
	      msgBox.setText(QString::fromUtf8("Устойство УУШД не было найдено."));
	      msgBox.setInformativeText(QString::fromUtf8("Провести повторный поиск устройства?"));
	    }
	    if (portSMD != "" && portTUB == "")
	    {
	      msgBox.setText(QString::fromUtf8("Устойство АСС не было найдено."));
	      msgBox.setInformativeText(QString::fromUtf8("Провести повторный поиск устройства?"));
	    }
	    if (portSMD == "" && portTUB == "")
	    {
	      msgBox.setText(QString::fromUtf8("Устойства УУШД и АСС не были найдены."));
	      msgBox.setInformativeText(QString::fromUtf8("Провести повторный поиск устройств?"));
	    }
	    msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::Cancel);
	    msgBox.setDefaultButton(QMessageBox::Yes);
	    int ret = msgBox.exec();
	    if (ret==(QMessageBox::Cancel)) return 0;
	  }
	}
	
	QextSerialPort smdSP;
	smdSP.setPortName(portSMD);
	smdSP.setBaudRate(BAUD115200);
	smdSP.setDataBits(DATA_8);
	smdSP.setParity(PAR_NONE);
	smdSP.setStopBits(STOP_2);
	//smdSP.setFlowControl(FLOW_HARDWARE);
	smdSP.setFlowControl(FLOW_OFF);
	smdSP.setTimeout(0, 500);
	smdSP.open(QIODevice::ReadWrite | QIODevice::Unbuffered);
	
	QextSerialPort tubSP;
	tubSP.setPortName(portTUB);
	tubSP.setBaudRate(BAUD115200);
	tubSP.setDataBits(DATA_8);
	tubSP.setParity(PAR_NONE);
	tubSP.setStopBits(STOP_2);
	//tubSP.setFlowControl(FLOW_HARDWARE);
	tubSP.setFlowControl(FLOW_OFF);
	tubSP.setTimeout(0, 500);
	tubSP.open(QIODevice::ReadWrite | QIODevice::Unbuffered);
	
	QlfSMD smd(&smdSP);
	smd.stop();
	smd.setFrequency(smd_frec);
	if(smd_invrot)
	  smd.setConformity(QlfSMD::MoveUpForCW);
	else
	  smd.setConformity(QlfSMD::MoveUpForCCW);
	smd.enable();
	
	RxSMD rxSMD(&smd, smd_mmps);
	QlfTUB tub(&tubSP);
	tub.stop();
	
	QRlxPattern pattern;

	// скорость нагружения мм/с
	double loadingSpeed = 0.0;
	
	// шагов нагружения
	int stepCount = 0;

	// время релаксации
	double relaxTime = 0.0;

	double deformation = 0.0;
	QString reportFileName;
	
	{

	    ExperimentWizard startDialog;

		QObject::connect(&startDialog, SIGNAL(runMoveUp()), &rxSMD, SLOT(loading()));
		QObject::connect(&startDialog, SIGNAL(stopMove()), &rxSMD, SLOT(stop()));
		QObject::connect(&startDialog, SIGNAL(runMoveDown()), &rxSMD,
				SLOT(unloading()));

		if (startDialog.exec() != QDialog::Accepted)
		{
		    smd.stop();
		    smd.disable ();
			return 0;
		}
		pattern = startDialog.getPattern();
		loadingSpeed = startDialog.getLoadingSpeed();
		stepCount = startDialog.getStepCount();
		relaxTime = startDialog.getRelaxTime();
		deformation = startDialog.getLoadingDeformation();
		reportFileName = startDialog.reportFileName();
	}

	QString tempDir = QDir::homePath() + QString::fromUtf8("/.lab5/RxStep/temp/") +
		QDateTime::currentDateTime().toString("hh.mm_dd.MM.yyyy") + "/";
	tempDir =  QDir::toNativeSeparators(tempDir);
	QDir().mkpath(tempDir);

	RxMainWindow mainWindow;
	mainWindow.setPattern(pattern);
	mainWindow.show();

	pattern.save(tempDir+"Sample.xml");

	QSettings expSettings(tempDir+"Settings.xml", XmlFormat());
	expSettings.setValue("LoadingSpeed", loadingSpeed);
	expSettings.setValue("RelaxTime", relaxTime);
	expSettings.setValue("StepCount", stepCount);
	expSettings.setValue("LoadingStepDef", deformation);
	//expSettings.setValue("LoadingStepStress", relaxTime);

	RxForceSensor forceSensor(&tub, tub_coeff_a, tub_coeff_b, tub_coeff_c, tub_coeff_d);
	//RxStrainStep strainStep;
	//RxExperiment experiment;
	using boost::bind;

	RxLoading loading(0, 20.0, loadingSpeed, &forceSensor, &rxSMD);
	loading.setTerminateFunctor(
					bind(&RxMainWindow::exitFromExperiment, &mainWindow)
					);

	boost::shared_ptr<RxBlock> loadingStep;  //(new RxStrainStep(&loading, &rxSMD, deformation));

	if (ssSettings().value(QString::fromUtf8("Тип_нагружения")).toString() == QString::fromUtf8("Деформация"))
	{
		loadingStep = boost::shared_ptr<RxBlock> (new RxStrainStep(&loading, &rxSMD, deformation));
	}

	if (ssSettings().value(QString::fromUtf8("Тип_нагружения")).toString() == QString::fromUtf8("Напряжение"))
	{
		loadingStep = boost::shared_ptr<RxBlock> (
				new RxForceStep(
						&loading,
						&rxSMD,
						&forceSensor,
						ssSettings().value(QString::fromUtf8("Шаг_нагружения")).toDouble() * pattern.getArea () * 1e6)
				);
	}

	loadingStep->setTerminateFunctor(
					bind(&RxMainWindow::exitFromExperiment, &mainWindow)
					);

	RxSampling rxSampling(loadingStep.get(), loadingStep.get(), &forceSensor, relaxTime);
	rxSampling.setTerminateFunctor(
					bind(&RxMainWindow::exitFromExperiment, &mainWindow)
					);

	RxCalculator rxCalculator(&rxSampling);

	RxStepCounterBlock rxStepCounter(&rxCalculator, stepCount);

	RxEmptyBlock gotoExperimentDone(0);

	// выход по требованию пользователя
	RxIfBlock testExperimentExit(&rxStepCounter,
			bind(&RxMainWindow::notExitFromExperiment, &mainWindow),
			&gotoExperimentDone
			);

	// &rxStepCounter - предыдущий блок; &strainStep - else блок
	RxIfBlock stepCountWhile(&testExperimentExit,
			bind(&RxStepCounterBlock::test, &rxStepCounter),
			//RxIfBlock::falseConst,
			loadingStep.get(),
			&gotoExperimentDone);

	RxCreateReport rxCreateReport (&gotoExperimentDone, reportFileName, tempDir);
	RxUnloading rxUnloading(&rxCreateReport, &rxSMD, smd_frec);
	RxEmptyBlock experimentDone(&rxUnloading);


	QObject::connect (
			loadingStep.get(),
			SIGNAL(endLoading(double)),
			&mainWindow,
			SLOT (endLoading(double)));

	QObject::connect (
			loadingStep.get(),
			SIGNAL(started()),
			&mainWindow,
			SLOT (beginStep()));

	QObject::connect (
			&rxSampling,
			SIGNAL(finished()),
			&mainWindow,
			SLOT (endStep()));


	QObject::connect (
			&experimentDone,
			SIGNAL(finished()),
			&mainWindow,
			SLOT (experimentDone()));

	QObject::connect (
			&forceSensor,
			SIGNAL(forceReady (double, int)),
			&mainWindow,
			SLOT (forceReady (double, int)));

	QObject::connect (
			&mainWindow,
			SIGNAL(setZero ()),
			&forceSensor,
			SLOT (setZero ()));

	RxDataSaver rxDataSaver(tempDir, pattern);

	QObject::connect (
			loadingStep.get(),
			SIGNAL(endLoading(double)),
			&rxDataSaver,
			SLOT (endLoading(double)));


	QObject::connect (
			&rxCalculator,
			SIGNAL(measurementReady (const QPolygonF&, double, double)),
			&rxDataSaver,
			SLOT (measurementReady (const QPolygonF&, double, double)));

	QObject::connect (
			&rxCalculator,
			SIGNAL(measurementReady (const QPolygonF&, double, double)),
			&mainWindow,
			SLOT (measurementReady (const QPolygonF&, double, double)));



	QObject::connect (
			&mainWindow,
			SIGNAL(startExperiment()),
			&loading,
			SLOT (start()));

	tub.run(50);

	int result = app.exec();
	tub.stop();
	smd.stop();
	smd.disable ();
	return result;
}
