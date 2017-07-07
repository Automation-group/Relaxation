#include "StepViewForm.h"
#include <qwt_plot_grid>
#include <qwt_plot_curve>
#include <qwt_symbol>
#include <qwt_plot_marker>

StepViewForm::StepViewForm(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	configurePlots();
}

void StepViewForm::configurePlots()
{
	QwtSymbol symbol(QwtSymbol::Ellipse, QBrush(Qt::blue), QPen(Qt::darkBlue),
			QSize(7, 7));

	stepDataCurve = new QwtPlotCurve (tr("σ(t)"));
	stepDataCurve -> attach(ui.qwtpStepData);
	stepDataCurve -> setSymbol(symbol);

	ui.qwtpStepData -> setAxisTitle(QwtPlot::xBottom, tr("t, сек"));
	ui.qwtpStepData -> setAxisTitle(QwtPlot::yLeft, tr("σ, МПа"));
	ui.qwtpStepData -> setAutoReplot(true);

	QwtPlotGrid* grid = new QwtPlotGrid ();
	grid -> enableXMin(true);
	grid -> enableYMin(true);
	grid -> setMajPen(QPen(Qt::black, 0, Qt::DotLine));
	grid -> setMinPen(QPen(Qt::gray, 0, Qt::DotLine));
	grid -> attach(ui.qwtpStepData);

	//for (int i = 0;i<100;i+=8)
	//{
	//    RxMainWindow::data << QPointF (i, (i*i/1e2));
	//  }
	//dataCurve -> setData(RxMainWindow::data);

}

void StepViewForm::setData(const QPolygonF& data)
{
	stepDataCurve->setData(data);  
}
