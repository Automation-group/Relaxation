#include "RxSMD.h"

RxSMD::RxSMD(QlfSMD* smd, double mmps) :
	m_smd(smd), m_mmps(mmps)
{
	connect(smd, SIGNAL(runDone()), this, SIGNAL(moveDone()));
}

void RxSMD::setLoadingSpeed(double speed)
{
	m_smd->setFrequency(speed / m_mmps);
}

void RxSMD::setPosition(double position)
{
	m_smd->setStepCounter(position / m_mmps);
}

double RxSMD::position()
{
	return m_smd->getStepCounter () * m_mmps;
}

void RxSMD::moveTo(double position)
{
	double pos = position - RxSMD::position();
	if (pos>0.0)
		loading(pos);
	if (pos<0.0)
		unloading(-pos);
	//double pos
}

void RxSMD::loading(double distance)
{
	m_smd -> setDirection(QlfSMD::CW);
	m_smd -> run(distance / m_mmps);
}

void RxSMD::unloading(double distance)
{
	m_smd -> setDirection(QlfSMD::CCW);
	m_smd -> run(distance / m_mmps);
}

void RxSMD::stop()
{
	m_smd -> stop();
}
