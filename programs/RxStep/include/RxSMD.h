#ifndef RXSMD_H_
#define RXSMD_H_

#include <QObject>
#include <QlfSMD.h>

class RxSMD : public QObject
{
  Q_OBJECT
public:
	
	/**
	 * \param mmsp калибровочный коэффициент мм/шаг
	 */
	RxSMD (QlfSMD* smd, double mmps);

	/**
	 * Задать новое значение положения пуансона, мм
	 */
	void setPosition(double position);

	/**
	 * Положение пуансона, мм
	 */
	double position();
	
	/**
	 * \param speed скорость нагружения мм/с
	 */
	void setLoadingSpeed(double speed);
	
	QlfSMD* lfsmd() const { return m_smd; }
public Q_SLOTS:
	/**
	 * \param distance дистанция в мм
	 */
	void loading (double distance = 0.0);
	void unloading(double distance = 0.0);
	void moveTo(double position);
	void stop();
Q_SIGNALS:
	void moveDone();
private:
	QlfSMD* m_smd;
	double m_mmps;
};

#endif /*RXSMD_H_*/
