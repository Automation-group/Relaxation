#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "USART.h"
#include "COMMANDS.h"
#include "BUFFER.h"
#include "COMMANDS_AD7730.h"

int stateADC = 0; //! если 0 - АЦП выключен, если 1 - АЦП включен
char infoADC = 'D'; //! информация о состоянии прибора:
// D - тензодатчик не подключен,
// С - запущен непрерывный режим,
// W - прибор готов к работе.
int overload = 0; //! если 0 - нет перегрузки, если 1 - есть перегрузка
long int strongMin = 0; //! нижний допустимый предел с АЦП
long int strongMax = 65535; //! верхний допустимый предел с АЦП
unsigned int adc_code = 0x7FFF; //! Измеренный код АЦП

int main (void) {
  
  //Инициализация USART на 115200 БОД
  USART_Init(8); //  bits per second = f_cpu/(16*(ubrr+1))
  UCSR0B |= _BV(RXCIE0);
  
  // Задание опорной частоты для AD7730
  DDRB |= _BV(PB1);
  TCCR1A = _BV(COM1A0);
  TCCR1B = _BV(WGM12) | _BV(CS10);
  OCR1A = 3; // 2.0 МГц
  //OCR1A = 1; // 4.0 МГц
  
  // Инициализация spi // PB2->PB0, PB3->PB4, PB4->PB3 PB5->PB5
  DDRB |=  _BV(PB2);
  PORTB &= ~_BV(PB2); // подтянуть CS на AD7730 к GND
  DDRB |=  _BV(PB3);
  DDRB |=  _BV(PB5);
  SPCR = _BV(SPE) | _BV(MSTR) | _BV(CPHA) | _BV(SPR0) | _BV(CPOL);
  
  // Инициализация АЦП
  ad_init();
  
  /*
  //! Режим работы ацп, true - непрерывное преобразование
  char adc_continuous_mode = 0x00;
  char on_adc = 0;
  /**
  * Минимально допустимый код АЦП,
  * если измеренный код АЦП меньше устанавливвется флаг перегрузки
  */
  /*unsigned int min_code = 0;
  /**
  * Максимально допустимый код АЦП,
  * если измеренный код АЦП больше устанавливвется флаг перегрузки
  */
  /*unsigned int max_code = 0xFFFF;
  //! Флаг перегрузки
  int overloading = 0x00;
  */
  
  // Инициализация 16-ти битного таймера/счётчика
  // Настраиваем таймер на счёт тактовой, сброс и прерывание по достижению OCR1A
  //TCCR1B |= _BV(WGM12)|_BV(CS11)|_BV(CS10);
  //TIMSK1 |= _BV(OCIE1A);
  //OCR1A = 6250; // Частота по умолчанию 20 Гц, 65535 - max
  
  // Инициализация 8-ти битного таймера
  // Задание опорной частоты для AD7730
  //TCCR2B = _BV(CS20)|_BV(CS21)|_BV(CS22);
  // Разрешение прерывания по переполнению
  //TIMSK2 = _BV(TOIE2);
  
  
  // Разрешение прерываний SREG |=(1 << 7);
  sei();
  
  // Инициализация ног для работы с АЦП
  // PB0 - SCLK,
  // PB2 - RDY,
  // PB3 - DOUT,
  // PB4 - DIN,
  // PB5 - SCLK
  //PORTB |= ~(_BV(PB0)|_BV(PB2)|_BV(PB3)|_BV(PB4)|_BV(PB5));
  
  // Инициализация ног для обработки событий
  // PD4 - зарезервирована
  // PD5 - сигнал оп перегрузке
  // PD6 - частота передачи значений АЦП по USART
  //PORTD |= ~(_BV(PD4)|_BV(PD5));
  
  while(1) {
    // Обработка команд от последовательного порта.
    if (onCommand) {
      onCommand = 0;
      invokeCommand(command);
    }
  }
}

/*
// Частота считывания данных с АЦП.
ISR(TIM1_COMPA_vect) {
  if (stateADC){
  }
}
*/
// Обработка событий.(перегрузка, перегрев)
/*ISR(TIMER1_OVF_vect) {
  if (ad_check_rdy()) {
    adc_code = ad_ReadDataReg24() / 256;
  }
}*/

/*!
    Обработка команд
*/

// Произвести единичное измерение.
// Команда - GM ответ - GMx, где x - код АЦП.
unsigned long getADC(void) {
  /*if (ad_check_rdy()) {
    adc_code = ad_ReadDataReg24() / 256;
    if ((adc_code > min_code)&&(adc_code < max_code)) overloading = 0;
    else overloading = 1;
  }*/
  if (ad_check_rdy()) adc_code = ad_ReadDataReg24() / 256;
  return adc_code;
}

// Запустить измерения в непрерывном режиме.
//  Команда - RCx ответ - , где x - интервал измеререний 10 <= x <= 18000 мс.
void setPeriod(int period) {
  double dperiod = period;
  double freq = 1/(dperiod*1e-3);
  
  // clk_io / 1024
  if (freq >= 0.12 && freq < 8) {
    TCCR1B |= _BV(CS12);
    TCCR1B |= ~_BV(CS11);
    TCCR1B |= _BV(CS10);
    setTimer(2048, freq);
  }
  // clk_io / 64
  if (freq >= 8 && freq < 32) {
    TCCR1B |= ~_BV(CS12);
    TCCR1B |= _BV(CS11);
    TCCR1B |= _BV(CS10);
    setTimer(128, freq);
  }
  // clk_io / 8
  if (freq >= 32 && freq <= 1024) {
    TCCR1B |= ~_BV(CS12);
    TCCR1B |= _BV(CS11);
    TCCR1B &= ~_BV(CS10);
    setTimer(16, freq);
  }
  // clk_io / 1
  if (freq > 1024 && freq <= 10000) {
    TCCR1B |= ~_BV(CS12);
    TCCR1B &= ~_BV(CS11);
    TCCR1B |= _BV(CS10);
    setTimer(2, freq);
  }
  stateADC = 1;
  infoADC = 'C';
}
// Задание частоты.
void setTimer(int n, long int freq) {
  OCR1A = F_CPU/n/freq;
}

// Остановить измерения в непрерывном режиме.
// Команда - SC ответ -.
void setADCstop(void) {
  stateADC = 0;
}

// Получить состояние прибора.
// Команда - GS ответ - GSx,
// где x = D - тензодатчик не подключен,
// x = С - запущен непрерывный режим,
// x = W - прибор готов к работе.
char getInfo(void) {
  return infoADC;
}

// Установить допустимые пределы силы.
// Команда - SOx,y ответ - SOx,y
// Если значения АЦП выходят за пределы x <= АЦП <= y то выдаётся сигнал о перегрузке.
void setADCxy(long int argx, long int argy) {
  strongMin = argx;
  strongMax = argy;
}

// Получить допустимые пределы силы.
// Команда - SO, ответ - SOx,y
long int getADCx(void) {
  return strongMin;
}
long int getADCy(void) {
  return strongMax;
}

// Запрос о наличии перегрузки.
// Команда - GO, ответ - GOx, если x = 1 - перегрузка, x = 0 - нет прегрузки.
int getOverload(void) {
  return overload;
}
