#ifndef DEBUGSVIEWERDLG_H_
#define DEBUGSVIEWERDLG_H_

#include <QDialog>
#include <QPolygonF>
#define slots Q_SLOTS
#define signals Q_SIGNALS
#include <ui_debugStepViewer.h>
#undef signals
#undef slots
#include <qwt_plot_curve>

class DebugSViewerDlg: public QDialog
{
  Q_OBJECT
public:
  DebugSViewerDlg ();
public Q_SLOTS:
  void endSampling (const QPolygonF& data);
private:
  Ui_debugStepViewerDialog ui;
  QwtPlotCurve *dataCurve;
};

#endif /*DEBUGSVIEWERDLG_H_*/
