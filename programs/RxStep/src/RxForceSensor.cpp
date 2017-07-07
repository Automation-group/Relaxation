#include "RxForceSensor.h"
#include <QtDebug>

RxForceSensor::RxForceSensor (QlfTUB* tub, double a, double b, double c, double d)
	: m_setZero (false), m_zeroForce (0.0), m_tub(tub), m_a(a), m_b(b), m_c(c), m_d(d)
{
	QObject::connect (
			tub,
			SIGNAL(dataReady (int, int)),
			this,
			SLOT (dataReady (int, int))
			);	  
}

double RxForceSensor::measure()
{
	return calcForce(m_tub->measure());
}

double RxForceSensor::calcForce(int code)
{	
	double force = m_a*code*code*code + m_b*code*code + m_c*code + m_d;
	if (m_setZero)
	{
		m_setZero = false;
		m_zeroForce = force;
	};
	
	force -= m_zeroForce;
	return force;
}

void RxForceSensor::setZero()
{
	m_setZero = true;
}

void RxForceSensor::dataReady (int code, int msTime)
{
	forceReady (calcForce(code), msTime);
}
