#include "RxStepCounterBlock.h"

RxStepCounterBlock::RxStepCounterBlock(RxBlock* prev, int maxStepCount)
	: RxBlock(prev), m_currentStepCount(0), m_maxStepCount(maxStepCount)
{
}
	
bool RxStepCounterBlock::test()
{
	return m_currentStepCount >= m_maxStepCount; 
}
void RxStepCounterBlock::run()
{
	++m_currentStepCount;
	doNext();
}
