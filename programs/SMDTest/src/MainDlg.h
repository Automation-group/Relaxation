#ifndef MAINDLG_H_
#define MAINDLG_H_

#include <QDialog>
#include "../ui_mainDlg.h"
#include <qextserialport.h>
#include <QlfSMD.h>
#include <QTimer>

class MainDialog : public QDialog
{
	Q_OBJECT
public:
	MainDialog ();
	~MainDialog ();
private Q_SLOTS:
	void on_pbOpen_clicked();
	void on_pbClose_clicked();
	void on_pbEnableMotor_clicked();
	void on_pbDisableMotor_clicked();
	void on_pbReadSpeed_clicked();
	void on_pbWriteSpeed_clicked();
	void on_pbReadCounter_clicked();
	void on_pbWriteCounter_clicked();

	void on_tbUp_clicked();
	void on_tbDown_clicked();
	void on_tbStop_clicked();
	
	void on_tbMoveUp_pressed();
	void on_tbMoveDown_pressed();
	void on_tbMoveUp_released();
	void on_tbMoveDown_released();
	
	void readAlarms();
	
	void on_cbInvertion_stateChanged(int i);
private:
	void setAlarm(QLabel* label, bool alarm);
	void readConformity();
private:
	Ui_MainDialog ui;
	QextSerialPort smdSP;
	QlfSMD* smd;
	QTimer timer;
};
#endif /*MAINDLG_H_*/
