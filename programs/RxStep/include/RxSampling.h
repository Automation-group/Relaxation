#ifndef RXSAMPLING_H_
#define RXSAMPLING_H_

#include <QObject>
#include <QPolygonF>
#include <QTime>
#include "RxBlock.h"
#include "RxForceSensor.h"

class RxSampling: public RxBlock
{
	Q_OBJECT
public:
	/**
	 * Установить продолжительность съема данных
	 * \param durationTime продолжительность, с 
	 */
	RxSampling (RxBlock* prev, RxBlock* loadingBlock, RxForceSensor* forceCensor,  int durationTime);
	
	const QPolygonF& data() const { return m_data; }
Q_SIGNALS:
	void endSampling (const QPolygonF& data);
private Q_SLOTS:
	void forceReady(double force, int msTime);
	void startLoading();
private:
	void run();	
private:
	RxBlock* m_loadingBlock;
	QPolygonF m_data;
	bool m_running;
	int m_durationTime;
	RxForceSensor* m_forceSensor;
	QTime m_timer;
	bool m_beginLoading;
};

#endif /*RXSAMPLING_H_*/
