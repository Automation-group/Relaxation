#include "RxSampling.h"
#include <QtDebug>

RxSampling::RxSampling(RxBlock* prev, RxBlock* loadingBlock, RxForceSensor* forceSensor, int durationTime)
	: RxBlock(prev), m_loadingBlock(loadingBlock), m_running (false),
	m_forceSensor(forceSensor), m_durationTime(durationTime), m_beginLoading(false)
{
	m_timer.start ();
	QObject::connect (
			forceSensor,
			SIGNAL(forceReady (double, int)),
			this,
			SLOT (forceReady (double, int)));


	QObject::connect (
			loadingBlock,
			SIGNAL(started()),
			this,
			SLOT (startLoading()));
}

void RxSampling::startLoading()
{
    m_data.clear();
	m_forceSensor->run(20);
	m_beginLoading = true;
}

void RxSampling::run()
{
	m_timer.restart();

	m_running = true;
	m_forceSensor->run(150);
}

void RxSampling::forceReady(double force, int msTime)
{
	if (!(m_running | m_beginLoading)) return;

	m_data << QPointF((double)msTime / 1000.0, force);

	if (!m_running) return;
	if ((m_timer.elapsed() >= (m_durationTime * 1000)) || isTerminate())
	{
		m_running = false;
		endSampling(m_data);
		doNext();
	}
}
