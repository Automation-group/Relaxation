#ifndef RXSTEPMOTOR_H_
#define RXSTEPMOTOR_H_

#include <QObject>

class RxStepMotor : public QObject
{
  Q_OBJECT
public:
  RxStepMotor ();
public slots:
  /*
   * Запустить мотор
   * \param count число шагов
   * \param forward направление
   */
  void run (int count = 0, bool forward = true);
  
  /**
   * Остановить мотор 
   */
  void stop ();
  
  /**
   * задать скорость вращения двигателя
   * \param speed скорость вращения шаг/сек
   */
  void setSpeed (double speed);
  
  /** Установить значение счетчика шагов
   * \param counter новое значение счетчика 
   */
  void setCounter (int counter);
  
signals:
  void speedChanged (double speed);
  void counterChanged (int counter);
};

#endif /*RXSTEPMOTOR_H_*/
