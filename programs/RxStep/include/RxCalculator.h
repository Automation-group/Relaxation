#ifndef RXCALCULATOR_H_
#define RXCALCULATOR_H_

#include "RxBlock.h"
#include "RxSampling.h"

class RxCalculator : public RxBlock
{
	Q_OBJECT
public:
	RxCalculator (RxSampling* prev);
Q_SIGNALS:
	/**
	 * Произведено измерение
	 * \param data сила от времени F(t)
	 * \param force сила при которой измерена глубина релаксации
	 * \param rlx глубина релаксации от 0 до 1.0
	 */
	void measurementReady (const QPolygonF& data, double force, double rlx);
private:
	void run();
private:
	RxSampling* m_sampling;
};

#endif /*RXCALCULATOR_H_*/
