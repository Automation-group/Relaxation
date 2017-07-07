#include "RxUnloading.h"

RxUnloading::RxUnloading(RxBlock* prev, RxSMD* smd, double smd_frec)
	: RxBlock(prev), m_smd(smd), m_smd_frec(smd_frec)
{
	connect(smd, SIGNAL(moveDone()), this, SLOT(readySM()));
}

void RxUnloading::readySM ()
{
	if (isRunning())
		doNext();
}

void RxUnloading::run()
{
	m_smd->lfsmd()->setFrequency(m_smd_frec);
	m_smd->moveTo(-1.0);
}
