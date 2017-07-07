#ifndef RXUNLOADING_H_
#define RXUNLOADING_H_

#include "RxBlock.h"
#include "RxSMD.h"

class RxUnloading: public RxBlock
{
	Q_OBJECT
public:
	RxUnloading(RxBlock* prev, RxSMD* smd, double smd_frec);
	double m_smd_frec;
private Q_SLOTS:
	/**
	 * БШД выпонил заданное число шагов
	 */
	void readySM ();
private:
	void run();
private:
	RxSMD* m_smd;	
};


#endif /*RXUNLOADING_H_*/
