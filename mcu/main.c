#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "USART.h"
#include "COMMANDS.h"
#include "BUFFER.h"

// входы
#define devise_overload PC0
#define devise_overload_i PINC0

#define smd_overheat PC3
#define smd_overheat_i PINC3

#define up_ovt_switches PC4
#define up_ovt_switches_i PINC4

#define down_ovt_switches PC5
#define down_ovt_switches_i PINC5

// выходы
#define smd_pul PB3
#define smd_pul_i PINB3
#define smd_dir PB4
#define smd_ena PB5

long int motorCounter = 0; // число шагов 1<=N<=2000000
long int motorCounterRM = 0; // шаги которые должен сделать дигатель по команде RM
char motorDirection = 'F'; // направление вращения мотора F по часовой, B - против часовой
int smdDirection = 1; // если мотор вращется по часовой то 1 если против часовой то -1
char motorInfo = 'D'; // состояние мотора: D выключен, R вращается, S остановлен
long int motorFrequency = 20000; // частота мотора 1,000 Гц<=f<=32000,000 Гц
char ovtSwitches[2] = {'U', 'U'}; // состояния концевиков
int directionRotation = 0; // соотвенствие между вращением двигателя и пуансона
int smdOverheat = 0; // перегрев БУШД (!у ND2282 такого сигнала нет!)
int smdOverload = 0; // перегрузка тензодатчика
int downPressed = 0; // 0 - отпущен нижний конечник, 1 - сработал нижний конечник
int upPressed = 0; // 0 - отпущен верхний конечник, 1 - сработал верхний конечник

int numON = 0; // число опросов состояния конечных выключателей до принятия решения о их срабатывании
int numOverload = 0; // число опросов перегрузки до принятия решения о её наличии 
//int numOverheat = 0; // число опросов перегрева до принятия решения о его наличии
int commandRM = 1; // при commandRM = 0 шаговый двигатель вращается до получения команды стоп
int smdOn = 0; // 0 - обмотки ШД выключены, 1 - обмотки ШД включены

int main (void) {

  //Инициализация USART
  USART_Init(8);	/*  bits per second = f_cpu/(16*(ubrr+1)) */
  UCSR0B |= _BV(RXCIE0);

  // Инициализация 16-ти битного таймера/счётчика
  // Настраиваем таймер на счёт тактовой, сброс и прерывание по достижению OCR1A
  TCCR1B |= _BV(WGM12)|_BV(CS11)|_BV(CS10);
  TIMSK1 |= _BV(OCIE1A);
  OCR1A = 6250; // Частота по умолчанию 20 Гц, 65535 - max
  
  // Инициализация 8-ти битного таймера
  TCCR2B = _BV(CS22)|_BV(CS21);
  // Разрешение прерывания по переполнению
  TIMSK2 = _BV(TOIE2);

  // Разрешение прерываний SREG |=(1 << 7);
  sei();
  
  // Конфирурирование ног МК для отслеживания событий.
  // devise_overload - пегегрузка тензодачика;
  // smd_overheat - перегрев драйвера шагового двигателя;
  // up_ovt_switches - верхний конечный выключатель;
  // down_ovt_switches - нижний конечный выключатель
  DDRC &= ~(_BV(devise_overload)|_BV(smd_overheat)|_BV(up_ovt_switches)|_BV(down_ovt_switches));
  PORTC |= _BV(up_ovt_switches)|_BV(down_ovt_switches)|_BV(devise_overload)|_BV(smd_overheat);
  
  // Конфигурирование ног микроконтроллера для управления драйвером ШД.
  // smd_pul - PUL, smd_dir - DIR, smd_ena - ENA
  // PUL - число шагов задаётся передним фронтом импульса
  // DIR - направление вращения
  // ENA - сигнал отвечающий за включение/выключение драйвера
  DDRB |= _BV(smd_pul)|_BV(smd_dir)|_BV(smd_ena);
  PORTB |= _BV(smd_pul);
  PORTB &= ~(_BV(smd_dir)|_BV(smd_ena));
  
  while(1) {
    // Обработка команд от последовательного порта.
    if (onCommand) {
      onCommand = 0;
      invokeCommand(command);
    }
  }
}

// Счётчик шагов.
ISR(TIMER1_COMPA_vect) {
  if (motorInfo == 'R' && smdOn) {
    if (PINB & _BV(smd_pul_i)) PORTB ^= _BV(smd_pul);
    else {
      PORTB ^= _BV(smd_pul);
      motorCounter += smdDirection;
      if (commandRM) motorCounterRM--;
    }
    if (!motorCounterRM && commandRM) setSMDstop();
  }
}

// Обработка событий.(конечные выключатели, перегрузка, перегрев)
ISR(TIMER2_OVF_vect) {
  downPressed = 0;
  upPressed = 0;
  int overload = 0;
  //int overheat = 0;
  if ( numON > 10 ) numON = 10;
  if ( numOverload > 10 ) numOverload = 10;
  //if ( numOverheat > 10 ) numOverheat = 10;
  if (PINC & _BV(up_ovt_switches_i)) {
    numON++;
    if( numON > 10 ) {
      upPressed = 1; // Сработал верхний конечный выключатель.
    }
  }
  if (PINC & _BV(down_ovt_switches_i)) {
    numON++;
    if( numON > 10 ){
      downPressed = 1; // Сработал нижний конечный выключатель.
    }
  }
  if (PINC & _BV(devise_overload_i)) {
    numOverload++;
    if( numOverload > 10 ){
      overload = 1; // Перегрузка тензодачтика.
    }
  }
  /*if (PINC & _BV(smd_overheat_i)) {
    numOverheat++;
    if( numOverheat > 10 ){
      overheat = 1; // Перегрев драйвера шагового двигателя.
    }
  }*/
  // Сработал верхний конечный выключатель
  if ( upPressed && ovtSwitches[0] == 'U' ) {
    ovtSwitches[0] = 'D';
    setSMDstop();
    printf("%s\n","EVDU");
  }
  // Сработал нижний конечный выключатель
  if ( downPressed && ovtSwitches[1] == 'U' ) {
    ovtSwitches[1] = 'D';
    setSMDstop();
    printf("%s\n","EVDD");
  }
  // Отпущен верхний конечный выключатель
  if ( !upPressed && ovtSwitches[0] == 'D' ) {
    ovtSwitches[0] = 'U';
    printf("%s\n","EVUU");
    numON = 0;
  }
  // Отпущен нижний конечный выключатель
  if ( !downPressed  && ovtSwitches[1] == 'D' ) {
    ovtSwitches[1] = 'U';
    printf("%s\n","EVUD");
    numON = 0;
  }
  // Перегрузка тензодатичика.
  if ( overload && !smdOverload ) {
    smdOverload = 1;  
    if ( motorDirection == 'F' && directionRotation && motorInfo == 'R' ) setSMDstop();
    if ( motorDirection == 'B' && !directionRotation && motorInfo == 'R' ) setSMDstop();
    printf("%s\n","EVUF");
  }
  if (!overload) smdOverload = 0;
  // Перегрев драйвера шагового двигателя. !У ND2282 нет сигнала о перегреве!
  /*if ( overheat && !smdOverheat ) {
    smdOverheat = 1;
    printf("%s\n","EVUF")
  }
  if (!overheat) smdOverheat = 0;*/
}

/*!
    Обработка команд
*/

// Задание направления вращения двигателя.
void directionMotor (void) {
  if (motorDirection == 'F') {
    if (!directionRotation) PORTB &= ~_BV(smd_dir);
    else PORTB |= _BV(smd_dir);
  }
  if (motorDirection == 'B') {
    if (!directionRotation) PORTB |= _BV(smd_dir);
    else PORTB &= ~_BV(smd_dir);
  }
}

// запустить мотор до получения команды СТОП
// команда RM, ответа RM
void setSMDsteps(void) {
  if (!checkDirection()) {
    commandRM = 0;
    motorInfo = 'R';
  }
}

// запустить мотор на x шагов
// команда RMx, ответа RMx
long int setSMDstep(long int step) {
  if (step > 0 && step <= 4100000000 && !checkDirection()) {
    commandRM = 1;
    motorCounterRM = step;
    motorInfo = 'R';
  }
  return step;
}

// Проверка направления вращения при перегрузке или срабатывании конечных выключателей.
int checkDirection(void) {
  if (ovtSwitches[0] == 'U' && ovtSwitches[1] == 'U' && !smdOverload && !smdOverheat) return 0;
  
  if ((ovtSwitches[0] == 'D' || smdOverload) && ovtSwitches[1] == 'U' &&
       motorDirection == 'F' && !directionRotation) return 0; // двигаться только вниз 
  
  if ((ovtSwitches[0] == 'D' || smdOverload) && ovtSwitches[1] == 'U' &&
       motorDirection == 'B' && directionRotation) return 0; // двигаться только вниз
	   
  if (ovtSwitches[1] == 'D' && !smdOverload && motorDirection == 'B' &&
      ovtSwitches[0] == 'U' && !directionRotation) return 0; // двигаться только вверх
	
  if (ovtSwitches[1] == 'D' && !smdOverload && motorDirection == 'F' &&
      ovtSwitches[0] == 'U' && directionRotation) return 0; // двигаться только вверх
  return 1;
}

// задать направление вращения мотора
// F - по часовой, B - против часовой
// команда SDx, ответа SDx
char setSMDdirection(char dir) {
  if ( dir == 'F' ) {
    smdDirection = 1;
    motorDirection = dir;
    directionMotor();
  }
  if ( dir == 'B') {
    smdDirection = -1;
    motorDirection = dir;
    directionMotor(); 
  }
  return dir;
}

// подать напряжение на обмотки мотора
// команда EM, ответа EM
void setSMDon(void) {
  smdOn = 1;
  motorInfo = 'S';
  PORTB |= _BV(smd_ena);
}

// убрать напряжение с обмоток мотора
// команда DM, ответа DM
void setSMDoff(void) {
  if (motorCounterRM > 0) setSMDstop();
  smdOn = 0;
  motorInfo = 'D';
  PORTB &= ~_BV(smd_ena);
}

// остановить мотор (СТОП)
// комнда SM, ответа SM
void setSMDstop(void) {
  motorCounterRM = 0;
  motorInfo = 'S';
  printf("EVRD\n");
}

// получить информацию о состоянии мотора
// D выключен, R вращается, S остановлен
// команда GE, ответ GEx
char getSMDinfo(void) {
  return motorInfo;
}

// получить направление вращения мотора
// F - по часовой, B - против часовой
// команда GD, ответ GDx
char getSMDdirectionInfo(void) {
  return motorDirection;
}

// установить занчение счётчика шагов
// команда SCx, ответа SCx
long int setSMDcounter(long int number) {
  if ( number >= -4100000000 && number <= 4100000000 ) {
    motorCounter = number;
  }
  return number;
}

// получить занчение счётчика шагов
// команда GC, ответа GCx
long int getSMDcounter(void) {
  return motorCounter;
}

// установить значени частоты в тысячных долях герца
// команда SFx, ответа SFx
long int setSMDfrequency(long int freq) {
  // clk_io / 64
  if (freq >= 1000 && freq < 32000) {
    TCCR1B |= _BV(CS11);
    TCCR1B |= _BV(CS10);
    setTimer(128, freq);
    return motorFrequency;
  }
  // clk_io / 8
  if (freq >= 32000 && freq <= 1024000) {
    TCCR1B |= _BV(CS11);
    TCCR1B &= ~_BV(CS10);
    setTimer(16, freq);
    return motorFrequency;
  }
  // clk_io / 1
  if (freq > 1024000 && freq <= 32000000) {
    TCCR1B &= ~_BV(CS11);
    TCCR1B |= _BV(CS10);
    setTimer(2, freq);
    return motorFrequency;
  }
  return freq;
}
// Задание частоты.
void setTimer(int n, long int freq) {
  OCR1A = F_CPU/n/(freq/1000);
  motorFrequency = freq;
}

// получить значени частоты в тысячных долях герца
// команда GF, ответа GFx
long int getSMDfrequency(void) {
  return motorFrequency;
}

// получить состояние конечных выключательей
// DU - сработал верхний концевик
// UD - сработал нижний концевик
// DD - сработал оба конечника
// UU - верхний и нижний конечники свободны
// команда GT, ответ GTxy
char* getSMDovertravelSwitches(void) {
  return ovtSwitches;
}

// задать соотвенстие между направлением вращения двигателя и вращением пуансона
// команда SUx, ответ SUx
// 0 - пуансон перемещается вверх при вращении двигателя по часовой стрелке
// 1 - пуансон перемещается вверх при вращении двигателя против часовой стрелке
int setSMDdirectionRotationPunch(int dirrot){
  if( !dirrot || dirrot ) {
    directionRotation = dirrot;
    directionMotor();
  }
  return dirrot;
}

// получить соотвенстие между направлением вращения двигателя и вращением пуансона
// команда GU, ответ GUx
// 0 - пуансон перемещается вверх при вращении двигателя по часовой стрелке
// 1 - пуансон перемещается вверх при вращении двигателя против часовой стрелке
int getSMDdirectionRotationPunch(){
  return directionRotation;
}

// получить наличие перегрева в БУШД
// команда GMT, ответ GMTx
// 0 - нет перегрева
// 1 - перегрев
int getSMDoverheat() {
  return smdOverheat;
}

// получить наличие перегрузки у тензодатчика
// команда GMF, ответ GMFx
// 0 - нет перегрузки
// 1 - перегрузка
int getSMDoverload() {
  return smdOverload;
}
