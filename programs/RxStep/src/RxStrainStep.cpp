#include "RxStrainStep.h"

RxStrainStep::RxStrainStep(RxBlock* prev, RxSMD* smd, double deformation) :
	RxBlock(prev), m_smd(smd), m_deformation(deformation)
{
	connect(smd, SIGNAL(moveDone()), this, SLOT(readySM()));
}

void RxStrainStep::run()
{
	m_smd->loading(m_deformation);
}

void RxStrainStep::readySM()
{
	if (isRunning())
	{
		endLoading(m_deformation);
		doNext();
	}
}
