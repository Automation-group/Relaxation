#include "RxLoading.h"
#include <QtDebug>

RxLoading::RxLoading (RxBlock* prev, double maxforce, double loadingSpeed, RxForceSensor* forceSensor, RxSMD* smd)
	: RxBlock(prev),  m_running (false), m_maxforce(maxforce), m_loadingSpeed(loadingSpeed), m_forceSensor(forceSensor), m_smd(smd)
{
	QObject::connect (
			forceSensor,
			SIGNAL(forceReady (double, int)),
			this,
			SLOT (forceReady (double, int)));
}

void RxLoading::run()
{
	m_smd->setPosition(0.0);
	m_smd->loading();
	m_running = true;
}

void RxLoading::forceReady (double force, int msTime)
{
	if (! m_running) return;

	if (! isTerminate() && (force < m_maxforce)) return;
	//if (force < m_maxforce) return;

	m_running = false;
	m_smd->stop();
	m_smd->setLoadingSpeed(m_loadingSpeed);
	doNext();
}
