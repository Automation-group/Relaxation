#ifndef STEPVIEWFORM_H_
#define STEPVIEWFORM_H_

#include <QWidget>

class QwtPlotCurve;

#define slots Q_SLOTS
#define signals Q_SIGNALS
#include <ui_StepView.h>
#undef signals
#undef slots

class StepViewForm : public QWidget
{
	Q_OBJECT
public:
	StepViewForm(QWidget* parent = 0);
	void configurePlots ();
	void setData(const QPolygonF& data);
private:
	Ui_StepViewForm ui;
	QwtPlotCurve *stepDataCurve;
};
#endif /*STEPVIEWFORM_H_*/
