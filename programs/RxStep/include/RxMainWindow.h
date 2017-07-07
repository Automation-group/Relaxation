#ifndef RXMAINWINDOW_H_
#define RXMAINWINDOW_H_

#include <QMainWindow>
#include <qwt_plot_curve>
#define slots Q_SLOTS
#define signals Q_SIGNALS
#include "ui_mainWindow.h"
#undef signals
#undef slots
#include <QPolygonF>
#include <QRlxData.h>

class StepViewForm;

class RxMainWindow: public QMainWindow
{
	Q_OBJECT
public:
	RxMainWindow ();
	~RxMainWindow ();
	void setPattern(const QRlxPattern& pattern)
	{
		m_pattern = pattern;
	}

	bool notExitFromExperiment();
	bool exitFromExperiment()
	{
		return ! notExitFromExperiment();
	}
Q_SIGNALS:
	void setZero();
	void startExperiment();
	void stopExperiment();
public Q_SLOTS:
	void measurementReady (const QPolygonF& data, double force, double rlx);
	void beginStep();
	void endStep();
	void forceReady(double force, int time);
	void experimentDone();
	void endLoading(double deformation);
protected:
	 void closeEvent (QCloseEvent* event);
private Q_SLOTS:
	void on_actionSetZero_triggered();
	void on_actionRunExperiment_triggered();
	void on_actionShowStep_triggered();
	void on_actionStop_triggered();
private:
	void configurePlots ();
private:
	Ui_MainWindow ui;
	//QwtPlotCurve *stepDataCurve;
	QwtPlotCurve *dataCurve;
	QPolygonF data;
	QRlxPattern m_pattern;
	StepViewForm* m_stepView;
	bool m_exitFromExperiment;
	bool m_experimentDone;
	double m_deformation;
	int m_stepCounter;
	bool m_stepStarted;
	QPolygonF m_stepData;
	bool m_endLoading;
};

#endif /*RXMAINWINDOW_H_*/
