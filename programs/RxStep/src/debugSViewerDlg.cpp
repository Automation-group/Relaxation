#include "debugSViewerDlg.h"

DebugSViewerDlg::DebugSViewerDlg ()
  : QDialog ()
{
  ui.setupUi (this);
  
  dataCurve = new QwtPlotCurve ("Curve 1");
  dataCurve -> attach (ui.qwtpData);
  
  /*
  QwtPlotGrid* grid = new QwtPlotGrid ();
  grid -> enableXMin (true);
  grid -> enableYMin (true);
  grid -> setMajPen (QPen (Qt::black, 0, Qt::DotLine));
  grid -> setMinPen (QPen (Qt::gray, 0, Qt::DotLine));
  grid -> attach (dataPlot);
  */
  
  //dataPlot -> setAxisTitle (QwtPlot::xBottom, tr ("N"));
  //dataPlot -> setAxisTitle (QwtPlot::yLeft, tr ("log(A)"));
  
}

void DebugSViewerDlg::endSampling (const QPolygonF& data)
{
  dataCurve -> setData (data);
  ui.qwtpData -> replot ();  
}
