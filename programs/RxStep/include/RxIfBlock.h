#ifndef RXIFBLOCK_H_
#define RXIFBLOCK_H_

#include <boost/function.hpp>
#include "RxBlock.h"

class RxEmptyBlock : public RxBlock
{
	Q_OBJECT
public:
	RxEmptyBlock (RxBlock* prev)
	: RxBlock(prev) {}
private:
	void run() { doNext(); }
};

class RxElseBlock;

class RxIfBlock : public RxBlock
{
	Q_OBJECT
public:
	typedef boost::function<bool (void)> IfFunctor_t;
	RxIfBlock (RxBlock* prev, IfFunctor_t ifFunctor = trueConst, RxBlock* else_block = 0, RxBlock* then_block = 0);

	RxBlock* thenBlock() { return m_then; }
	RxBlock* elseBlock() { return m_else; }

private:
	void run();
private:
	IfFunctor_t m_ifFunctor;
	RxBlock* m_then;
	RxBlock* m_else;
};

#endif /*RXIFBLOCK_H_*/
