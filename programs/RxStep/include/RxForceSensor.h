#ifndef RXFORCESENSOR_H_
#define RXFORCESENSOR_H_

#include <QObject>
#include <QlfTUB.h>

class RxForceSensor: public QObject
{
	Q_OBJECT
public:
	RxForceSensor (QlfTUB* tub, double a, double b, double c, double d);
	
	/**
	 * @brief Провести измерение
	 * @return Сила в Ньютонах
	 */
	double measure();
	
	void run(int msTimeout = 100)
	{
		m_tub->run(msTimeout);
	}
	
public Q_SLOTS:
	void setZero();
Q_SIGNALS:
 	void forceReady (double force, int msTime);
 	
private Q_SLOTS:
	void dataReady (int code, int msTime); 	
private:
	double calcForce(int code);
private:
	bool m_setZero;
	double m_zeroForce;
	QlfTUB* m_tub;
	double m_a;
	double m_b;
        double m_c;
	double m_d;
};

#endif /*RXFORCESENSOR_H_*/
