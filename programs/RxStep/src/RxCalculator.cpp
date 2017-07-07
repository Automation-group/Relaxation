#include "RxCalculator.h"

RxCalculator::RxCalculator(RxSampling* prev) :
	RxBlock(prev), m_sampling(prev)
{

}

void RxCalculator::run()
{
	if (!m_sampling)
	{
		terminated(QString::fromUtf8("error RxCalculator: RxSampling is null."));
		return;
	}

	const QPolygonF& data = m_sampling->data();
	
	double firstForce = data.first ().y();
	double maxForce = firstForce;
	double lastForce = data.last ().y();

	for (QPolygonF::const_iterator i = data.constBegin(); i != data.constEnd(); ++i)
		maxForce = qMax(maxForce, (*i).y());

	measurementReady(data, maxForce, (maxForce - lastForce) / (maxForce
			- firstForce));

	doNext();
}
