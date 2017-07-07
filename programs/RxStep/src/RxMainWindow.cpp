#include "RxMainWindow.h"
#include <qwt_plot_grid>
#include <qwt_plot_curve>
#include <qwt_symbol>
#include <qwt_plot_marker>

#include "StepViewForm.h"
#include <algorithm>
#include <QCloseEvent>
#include <QAction>

#include "ssGlobal.h"

RxMainWindow::RxMainWindow ()
  :QMainWindow (), m_stepView(0), m_exitFromExperiment(false), m_experimentDone(false),
  m_deformation(0.0), m_stepCounter(1), m_stepStarted(false), m_endLoading(false)
{
  ui.setupUi (this);

  configurePlots ();
}


void RxMainWindow::closeEvent (QCloseEvent* event)
{
	if(m_experimentDone || ! ui.actionStop->isEnabled())
	{
		if (m_stepView)
		{
			delete m_stepView;
			m_stepView = 0;
		}
	}
	else
		event->ignore();
}

void RxMainWindow::experimentDone()
{
	statusBar()->showMessage(tr("Эксперимент закончен!!!"));
	m_experimentDone = true;
}

void RxMainWindow::endLoading(double deformation)
{
	m_deformation += deformation;
	ui.leDeformation->setText(QString::number(m_deformation*1000.0));
	ui.leDeformationInPercent->setText(QString::number(m_deformation * 1e-3 / m_pattern.getHeight() * 100.0));
	m_endLoading = true;
}

RxMainWindow::~RxMainWindow ()
{
	if (m_stepView) delete m_stepView;
}

bool RxMainWindow::notExitFromExperiment()
{
	return !m_exitFromExperiment;
}

void RxMainWindow::on_actionStop_triggered()
{
	statusBar()->showMessage(tr("Ждите завершения эксперимента."));
	m_exitFromExperiment = true;
}

void RxMainWindow::configurePlots ()
{
  QwtSymbol symbol (QwtSymbol::Ellipse, QBrush (Qt::blue), QPen (Qt::darkBlue), QSize (7, 7));

  dataCurve = new QwtPlotCurve (tr("Δσ/σ<sub>step</sub>(σ)"));
  dataCurve -> attach (ui.qwtpData);
  dataCurve -> setStyle (QwtPlotCurve::NoCurve);
  dataCurve -> setSymbol (symbol);
  // σΔ
  ui.qwtpData -> setAxisTitle (QwtPlot::yLeft, tr("Δσ/σ<sub>step</sub>, %"));
  ui.qwtpData -> setAxisTitle (QwtPlot::xBottom, tr("σ, МПа"));
  ui.qwtpData -> setAutoReplot (true);
  ui.qwtpData -> setAxisScale (QwtPlot::yLeft, 0, 120.0, 20.0);


  QwtPlotGrid* grid = new QwtPlotGrid ();
  grid -> enableXMin (true);
  grid -> enableYMin (true);
  grid -> setMajPen (QPen (Qt::black, 0, Qt::DotLine));
  grid -> setMinPen (QPen (Qt::gray, 0, Qt::DotLine));
  grid -> attach (ui.qwtpData);

  QwtPlotMarker* marker = new QwtPlotMarker ();
  marker -> setYValue (100.0);
  marker -> setLineStyle (QwtPlotMarker::HLine);
  marker -> setLinePen (QPen (Qt::darkRed, 2, Qt::SolidLine));
  marker -> attach (ui.qwtpData);

  dataCurve -> setData (RxMainWindow::data);
}

void RxMainWindow::on_actionShowStep_triggered()
{
	if (!m_stepView)
		m_stepView = new StepViewForm;
	m_stepView->show();
	m_stepView->setFocus(Qt::MouseFocusReason);
}

void RxMainWindow::on_actionRunExperiment_triggered()
{
	startExperiment();
}

void RxMainWindow::on_actionSetZero_triggered()
{
	setZero();
}

void RxMainWindow::beginStep()
{
	m_stepData.clear();
	m_stepStarted = true;
	m_endLoading = false;
}

void RxMainWindow::endStep()
{
	m_stepStarted = false;
}


void RxMainWindow::forceReady (double force, int time)
{
	ui.leForce->setText(QString::number(force,'f',1));
	ui.leStress->setText(QString::number(force / m_pattern.getArea() / 1e6,'f',1));

	if (m_stepStarted)
	{
		static int forcecounter = 0;
		static const double coefficientOfElasticity = ssSettings().value(QString::fromUtf8("Образец_МодульУпругости")).toDouble();

		double curTime = (double)time / 1000.0;
		m_stepData << QPointF(curTime, force / (m_pattern.getArea() * 1e6));


		if (m_stepView && m_endLoading && (forcecounter % 4 == 0)) m_stepView->setData(m_stepData);
		++forcecounter;

		static double maxForce = -1e18;
		static double maxForceTime = 0.0;

		if (!m_endLoading) maxForce = -1e18;

		if (m_endLoading && (forcecounter % 4 == 0))
		{
			if (force > maxForce)
			{
				maxForce = force;
				maxForceTime = curTime;
			}
			const int i = m_stepData.size() - 6 + 2;

			double defSpeed = (maxForce - force) / (curTime - maxForceTime)
				/ coefficientOfElasticity / (m_pattern.getArea() * 1e6);

			ui.leDeformationSpeed->setText(QString::number(defSpeed));
			double fullDef = m_deformation * 1e-3 / m_pattern.getHeight();
			double plasticDef = force / (m_pattern.getArea() * 1e6) / coefficientOfElasticity;
			ui.lePlasticDeformationInPercent->setText(QString::number((fullDef - plasticDef) * 100.0));
		}
	}
}

namespace
{
	struct CalcStress
	{
		  CalcStress(double area) : area(area) {}
		  QPointF operator()(const QPointF& p)
		  {
			  return QPointF(p.x(), p.y()/area);
		  }
	private:
		  double area;
	};
}

void RxMainWindow::measurementReady (const QPolygonF& data, double force, double rlx)
{
   ui.leLoadingStep->setText(QString::number(++m_stepCounter));

  RxMainWindow::data << QPointF (force / m_pattern.getArea() / 1e6, rlx * 100.0);
  ui.leRelaxation->setText(QString::number(rlx * 100.0,'f',1) + "%");
  dataCurve -> setData (RxMainWindow::data);

  if (m_stepView)
  {
	  QPolygonF buffer = data;
          std::transform(buffer.begin(), buffer.end(), buffer.begin(), CalcStress(m_pattern.getArea() * 1e6));
	  m_stepView->setData(buffer);
  }
}
