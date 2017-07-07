#include <string.h>
#include <avr/io.h>
#include <stdlib.h>

#include "COMMANDS.h"

void invokeCommand(char* __buf) {
  char* buffer = __buf;
  
  // Шагать до получения команды СТОП.
  if (buffer[0] == 'R' && buffer[1] == 'M' && strlen(buffer) == 2) {
    setSMDsteps();
    printf("RM\n");
    return;
  }
  
  // Сделать n шагов.
  if (buffer[0] == 'R' && buffer[1] == 'M' && strlen(buffer) >= 3 && strlen(buffer) <= 9) {
    char* value = buffer+2;
    long int step = setSMDstep(atol(value));
    printf("RM%li\n", step);
    return;
  }
  
  // Задать направление вращения.
  if (buffer[0] == 'S' && buffer[1] == 'D' && strlen(buffer) == 3) {
    char value = buffer[2];
    char dir = setSMDdirection(value);
    printf("SD%c\n", dir);
    return;
  }
  
  // Включить мотор.
  if (buffer[0] == 'E' && buffer[1] == 'M' && strlen(buffer) == 2) {
    setSMDon();
    printf("EM\n");
    return;
  }
  
  // Выключить мотор.
  if (buffer[0] == 'D' && buffer[1] == 'M' && strlen(buffer) == 2) {
    setSMDoff();
    printf("DM\n");
    return;
  }
  
  // Стоп.
  if (buffer[0] == 'S' && buffer[1] == 'M' && strlen(buffer) == 2) {
    setSMDstop();
    printf("SM\n");
    return;
  }
  
  // Получить информацию о состоянии мотора.
  if(buffer[0] == 'G' && buffer[1] == 'E' && strlen(buffer) == 2) {
    printf("GE%c\n", getSMDinfo());
    return;
  }
  
  // Получить информацию о направлении вращения мотора мотора.
  if(buffer[0] == 'G' && buffer[1] == 'D'  && strlen(buffer) == 2) {
    printf("GD%c\n", getSMDdirectionInfo());
    return;
  }
  
  // Установить значение счётчика шагов.
  if(buffer[0] == 'S' && buffer[1] == 'C' && strlen(buffer) >= 3 && strlen(buffer) <= 13) {
    char* value = buffer+2;
    long int number = setSMDcounter(atol(value));
    printf("SC%li\n", number);
    return;
  }
  
  // Получить значение счётчика шагов.
  if(buffer[0] == 'G' && buffer[1] == 'C'  && strlen(buffer) == 2) {
    printf("GC%li\n", getSMDcounter());
    return;
  }
  
  // Установить значение частоты в тысяных долях герца.
  if(buffer[0] == 'S' && buffer[1] == 'F' && strlen(buffer) >= 3 && strlen(buffer) <= 10) {
    char* value = buffer+2;
    long int freq = setSMDfrequency(atol(value));
    printf("SF%li\n", freq);
    return;
  }
  
  // Получить занчение частоты мотора в тысячных долях герца.
  if(buffer[0] == 'G' && buffer[1] == 'F'  && strlen(buffer) == 2) {
    printf("GF%li\n", getSMDfrequency());
    return;
  }
  
  // Получить состояние конечных выключательей.
  if(buffer[0] == 'G' && buffer[1] == 'T'  && strlen(buffer) == 2) {
    printf("GT%c%c\n", getSMDovertravelSwitches()[0], getSMDovertravelSwitches()[1]);
    return;
  }
  
  // Установить соответствие между движением двигателя и вращением пуансона.
  if(buffer[0] == 'S' && buffer[1] == 'U'  && strlen(buffer) == 3) {
    char* value = buffer+2;
    int dirrot = setSMDdirectionRotationPunch(atoi(value));
    printf("%s%i\n","SU",dirrot);
    return;
  }
  
  // Получить соответствие между движением двигателя и вращением пуансона.
  if(buffer[0] == 'G' && buffer[1] == 'U'  && strlen(buffer) == 2) {
    printf("GU%i\n", getSMDdirectionRotationPunch());
    return;
  }
  
  // Получить наличие перегрева в БУШД
  if(buffer[0] == 'G' && buffer[1] == 'M' && buffer[2] == 'F'  && strlen(buffer) == 3) {
    printf("GMF%i\n", getSMDoverheat());
    return;
  }
  
  // Получить наличие перегрузки у тензодачика
  if(buffer[0] == 'G' && buffer[1] == 'M' && buffer[2] == 'T'  && strlen(buffer) == 3) {
    printf("GMT%i\n", getSMDoverload());
    return;
  }
  
  printf("?%s\n", buffer);
}