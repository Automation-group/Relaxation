#ifndef RXLOADING_H_
#define RXLOADING_H_

#include <QObject>
#include "RxSMD.h"
#include "RxBlock.h" 
#include "RxForceSensor.h"

class RxLoading : public RxBlock
{
	Q_OBJECT
public:
	explicit RxLoading (RxBlock* prev, double maxforce, double loadingSpeed, RxForceSensor* forceSensor, RxSMD* smd);
public Q_SLOTS:
	void forceReady (double force, int msTime);
private:
	void run();
private:
	bool m_running;
	double m_maxforce;
	double m_loadingSpeed;
	RxForceSensor* m_forceSensor;
	RxSMD* m_smd;
};

#endif /*RXLOADING_H_*/
