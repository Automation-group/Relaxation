#include "RxExperiment.h"
#include <QtDebug>
#include <QtGlobal>

RxExperiment::RxExperiment ()
  :stepSpreadTime (60),
  stepCount (60), running (false),
  stepCounter (0)  
{
  
}

void RxExperiment::setStepSpreadTime (int time)
{
  stepSpreadTime = time;
}
    
void RxExperiment::endStep ()
{
  if (!running) return;
  runFD (1000);
}
  
void RxExperiment::endSampling (const QPolygonF& data)
{
  if (!running) return;
  stopFD ();
  
  double firstForce = data.first ().y ();
  double maxForce = firstForce;
  double lastForce = data.last ().y ();
  
  for (QPolygonF::const_iterator i = data.constBegin (); i != data.constEnd (); ++i)
    maxForce = qMax (maxForce, (*i).y ());      

  measurementReady (data, maxForce, (maxForce - lastForce) / (maxForce - firstForce));
  stepCounter ++;
  startStep ();
}
  
void RxExperiment::setStepCount (int stepCount)
{
  RxExperiment::stepCount = stepCount;
}
  
void RxExperiment::start ()
{
  if (running) return;

  stepCounter = 0;
  running = true;
  startLoading ();
  //startStep ();
}
  
void RxExperiment::endLoading()
{
	startStep ();
}

void RxExperiment::stop ()
{
  if (!running) return;
}

void RxExperiment::startStep ()
{
  runFD (20);
  startSampling ();
  doStep ();
}
