#include "RxForceStep.h"
#include <QtDebug>

RxForceStep::RxForceStep (RxBlock* prev, RxSMD* smd, RxForceSensor* forceSensor, double loadingStep)
	: RxBlock(prev), m_smd(smd), m_forceSensor(forceSensor), m_startForce(0.0), m_isLoading(false),
	m_loadingStep(loadingStep)
{
	//connect(smd, SIGNAL(moveDone()), this, SLOT(readySM()));

	QObject::connect (
			forceSensor,
			SIGNAL(forceReady (double, int)),
			this,
			SLOT (forceReady (double, int)));

}

void RxForceStep::readySM ()
{
	if (isRunning())
	{
		m_isLoading = false;
		doNext();
	}
}

void RxForceStep::forceReady(double force, int msTime)
{
	static double position = 0.0;

	if (!isRunning()) return;

	if (isTerminate())
	{
	    m_smd->stop();
	    m_isLoading = false;
	    doNext();
	}

	if (m_isLoading)
	{
		if (force >= (m_startForce + m_loadingStep))
		{
		    m_smd->stop();
		    m_isLoading = false;
		    endLoading(m_smd->position() - position);
		    qDebug()<<"Epos" << position;
		    doNext();
		}
	}
	else
	{
		m_startForce = force;
		position = m_smd->position();
		qDebug()<<"Spos" << position;
		m_smd->loading();
		m_isLoading = true;
	}

}

void RxForceStep::run()
{

}
