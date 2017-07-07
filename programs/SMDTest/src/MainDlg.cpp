#include "MainDlg.h"
#include <QMessageBox>

MainDialog::MainDialog() :
	smdSP(), smd(0), timer()
{
	smdSP.setBaudRate(BAUD115200);
	smdSP.setDataBits(DATA_8);
	smdSP.setParity(PAR_NONE);
	smdSP.setStopBits(STOP_2);
	//smdSP.setFlowControl(FLOW_HARDWARE);
	smdSP.setFlowControl(FLOW_OFF);
	smdSP.setTimeout(0, 500);

	ui.setupUi(this);
	this->setWindowTitle("SMDtest");
	ui.leSerialPortName->setText("/dev/ttyUSB0");
	connect(&timer, SIGNAL(timeout()), this, SLOT(readAlarms())); 
}

MainDialog::~MainDialog ()
{
	if (smd)
		on_pbClose_clicked();
}

void MainDialog::on_pbOpen_clicked()
{
	smdSP.setPortName(ui.leSerialPortName->text());
	if (!smdSP.open(QIODevice::ReadWrite | QIODevice::Unbuffered))
	{
		QMessageBox::critical (this, QString::fromUtf8("Ошибка"),
				QString::fromUtf8("Ошибка при инициализации\n последовательнго порта"));
		return;
	}
	
	ui.pbOpen->setEnabled (false);
	ui.pbClose->setEnabled (true);
	
	smd = new QlfSMD (&smdSP);
	
	if (! smd->testConnection())
	{
		on_pbClose_clicked();
		QMessageBox::critical (this, tr("Ошибка подключения"),
				tr("Проверьте подключение устройства"));	
		return;
	}
	
	if (smd->state() == QlfSMD::MotorDisable)
		ui.pbDisableMotor->setDisabled(true);
		else
		ui.pbEnableMotor->setDisabled(true);
	
	readAlarms();
	timer.start (200);
	
	on_pbReadSpeed_clicked();
	on_pbReadCounter_clicked();	
	readConformity();
}

void MainDialog::on_tbMoveUp_pressed()
{
	if (!smd) return;	
	smd->setDirection(QlfSMD::CW);
	smd->run();
}

void MainDialog::on_tbMoveDown_pressed()
{
	if (!smd) return;
	smd->setDirection(QlfSMD::CCW);
	smd->run();
}

void MainDialog::on_tbMoveUp_released()
{
	if (smd) smd->stop();
}

void MainDialog::on_tbMoveDown_released()
{
	on_tbMoveUp_released();
}

void MainDialog::on_tbUp_clicked()
{
	if (!smd) return;	
	smd->setDirection(QlfSMD::CW);
	smd->run(ui.sbStepCount->value());	
}

void MainDialog::on_tbDown_clicked()
{
	if (!smd) return;
	smd->setDirection(QlfSMD::CCW);
	smd->run(ui.sbStepCount->value());	
}

void MainDialog::on_tbStop_clicked()
{
	if (smd) smd->stop();
}


void MainDialog::on_pbEnableMotor_clicked()
{
	if (smd) smd->enable();
}

void MainDialog::on_pbDisableMotor_clicked()
{
	if (smd) smd->disable();
}


void MainDialog::on_pbReadSpeed_clicked()
{
	if (smd) ui.dsbSpeed->setValue(smd->getFrequency());
}

void MainDialog::on_pbWriteSpeed_clicked()
{
	if (smd) smd->setFrequency(ui.dsbSpeed->value());
}

void MainDialog::on_pbReadCounter_clicked()
{
	if (smd) ui.sbCounter->setValue(smd->getStepCounter());
}

void MainDialog::on_pbWriteCounter_clicked()
{
	if (smd) smd->setStepCounter(ui.sbCounter->value());
}

void MainDialog::on_cbInvertion_stateChanged(int i)
{
	if (smd)
		smd->setConformity (i != Qt::Checked ? QlfSMD::MoveUpForCW : QlfSMD::MoveUpForCCW);
}

void MainDialog::readConformity()
{
	if (!smd) return;
	ui.cbInvertion->setChecked(smd->conformity() != QlfSMD::MoveUpForCW);
}

void MainDialog::readAlarms()
{
	bool forwardLimit = true;
	bool reverseLimit = true;
	bool overloading = true;
	bool overheat = true;
	
	if (smd)
	{
		smd->getLimits (forwardLimit, reverseLimit);
		overloading = smd->getOverloading();
		overheat = smd->getOverheat();
	}
	
	setAlarm(ui.lForwardLimit, forwardLimit);
	setAlarm(ui.lReverseLimit, reverseLimit);
	setAlarm(ui.lOverloading, overloading);
	setAlarm(ui.lOverheat, overheat);
}

void MainDialog::setAlarm(QLabel* label, bool alarm)
{
	label->setText (alarm ? tr("<b>Да") : tr("Нет"));	
}

void MainDialog::on_pbClose_clicked()
{
	timer.stop();
	if (smd)
	{
		QlfSMD* temp = smd;
		smd = 0;
		delete temp;
	}
	smdSP.close();
	ui.pbOpen->setEnabled (true);
	ui.pbClose->setEnabled (false);	
}
