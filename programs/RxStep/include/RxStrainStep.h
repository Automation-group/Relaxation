#ifndef RXSTRAINSTEP_H_
#define RXSTRAINSTEP_H_

#include <QObject>
#include "RxBlock.h"
#include "RxSMD.h"

class RxStrainStep: public RxBlock
{
	Q_OBJECT
public:
	/**
	 * \param deformation деформация в мм
	 */
	RxStrainStep (RxBlock* prev, RxSMD* smd, double deformation);

Q_SIGNALS:
	void endLoading(double deformation);	
private Q_SLOTS:
	/**
	 * БШД выпонил заданное число шагов
	 */
	void readySM ();
private:
	void run();
private:
	double m_deformation;
	RxSMD* m_smd;
};

#endif /*RXSTRAINSTEP_H_*/
