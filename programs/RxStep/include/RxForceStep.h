#ifndef RXFORCESTEP_H_
#define RXFORCESTEP_H_

#include <QObject>
#include <QPolygonF>

#include "RxBlock.h"
#include "RxSMD.h"
#include "RxForceSensor.h"

class RxForceStep: public RxBlock
{
	Q_OBJECT
public:
	/**
	 * \param loadingStep шаг нагружения, Н
	 */
	RxForceStep (RxBlock* prev, RxSMD* smd, RxForceSensor* forceCensor, double loadingStep);

Q_SIGNALS:
	void endLoading(double deformation);
private Q_SLOTS:
	/**
	 * БШД выпонил заданное число шагов
	 */
	void readySM ();
	
	void forceReady(double force, int msTime);
private:
	void run();
private:
	double m_loadingStep;
	RxSMD* m_smd;
	RxForceSensor* m_forceSensor;
	double m_startForce;
	bool m_isLoading;
};


#endif /*RXFORCESTEP_H_*/
