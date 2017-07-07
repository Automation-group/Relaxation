#ifndef RXSTEPCOUNTERBLOCK_H_
#define RXSTEPCOUNTERBLOCK_H_

#include "RxBlock.h"

class RxStepCounterBlock : public RxBlock
{
	Q_OBJECT
public:
	RxStepCounterBlock(RxBlock* prev, int maxStepCount);
	
	/**
	 * Проверка достижения максимального числа нагружений
	 */
	bool test();
private:
	void run();
private:
	int m_currentStepCount;
	int m_maxStepCount;
};

#endif /*RXSTEPCOUNTERBLOCK_H_*/
