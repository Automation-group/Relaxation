#include "RxIfBlock.h"

RxIfBlock::RxIfBlock (RxBlock* prev, IfFunctor_t ifFunctor, RxBlock* else_block, RxBlock* then_block)
	: RxBlock(prev), m_ifFunctor(ifFunctor), m_else (else_block), m_then (then_block)
{
	
}

void RxIfBlock::run ()
{
	if (m_ifFunctor())
	{
		if (m_then) m_then->start();
		else doNext();
	}
	else
	    if (m_else) m_else->start();
}