#ifndef RXEXPERIMENT_H_
#define RXEXPERIMENT_H_

#include <QObject>
#include <QPolygonF>

class RxExperiment : public QObject
{
  Q_OBJECT
public:
  RxExperiment ();
public Q_SLOTS:
  /**
   * Задать продолжительность шага
   */
  void setStepSpreadTime (int time);
    
  /**
   * Нагружение закончено
   */
  void endStep ();
  
  /**
   */
  void endSampling (const QPolygonF& data);
  
  /**
   * Задать число шагов нагружения
   */
  void setStepCount (int stepCount);
  
  /**
   * Начать эксперимент
   */
  void start ();
  
  /**
   * Закончить эксперимент
   */
  void stop ();
  
  /**
   * Подгрузка завершена
   */
  void endLoading();
Q_SIGNALS:
  /**
   * Сделать шаг нагружения
   */
  void doStep ();
  
  /**
   * Запустить съем данных
   */
  void startSampling ();
   
  /**
   * Запустить датчик силы
   * \param msDelay интервал взятия отсчетов силы в мс
   */
  void runFD (int msDelay);
  
  /**
   * Остановить датчик силы
   */
  void stopFD ();
  
  /**
   * Подгрузить образец
   */
  void startLoading ();
  
  /**
   * Произведено измерение
   * \param data сила от времени F(t)
   * \param force сила при которой измерена глубина релаксации
   * \param rlx глубина релаксации от 0 до 1.0
   */
  void measurementReady (const QPolygonF& data, double force, double rlx);
private:
  void startStep ();
private:
  int stepSpreadTime;
  int stepCount;
  bool running;
  int stepCounter;
};

#endif /*RXEXPERIMENT_H_*/
