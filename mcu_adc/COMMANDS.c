#include <string.h>
#include <avr/io.h>
#include <stdlib.h>

#include "COMMANDS.h"

void invokeCommand(char* __buf) {
  char* buffer = __buf;
  
  // Произвести единичное измерение кода АЦП.
  if (buffer[0] == 'G' && buffer[1] == 'M' && strlen(buffer) == 2) {
    printf("GM%ld\n", getADC());
    return;
  }
  
  // Запустить измерение кода АЦП в непрерывном режиме.
  if (buffer[0] == 'R' && buffer[1] == 'С' && strlen(buffer) >= 4 && strlen(buffer) <= 7) {
    char* value = buffer+2;
    setPeriod(atoi(value));
    return;
  }
  
  // Остановить непрерывный режим измерений.
  if (buffer[0] == 'S' && buffer[1] == 'C' && strlen(buffer) == 2) {
    setADCstop();
    return;
  }
  
  // Получить состояние прибора.
  if (buffer[0] == 'G' && buffer[1] == 'S' && strlen(buffer) == 2) {
    printf("GM%c\n", getInfo());
    return;
  }
  
  // Получить допустимые пределы силы.
  if (buffer[0] == 'S' && buffer[1] == 'O' && strlen(buffer) == 2) {
    printf("SO%li,%li\n", getADCx(), getADCy());
    return;
  }
  
  // Установить допустимые пределы силы.
  if (buffer[0] == 'S' && buffer[1] == 'O' && strlen(buffer) >= 5 && strlen(buffer) <= 13) {
    char* value = buffer+2;
    char* arg2 = value;
    while (*value) {
        if (*value == ',') {
          *value = 0;
          arg2 = value + 1;
        }
        value++;
    }
    long int argx = atol(buffer+2);
    long int argy = atol(arg2);
    if (argx < argy && argx >=0 && argy <= 65535) setADCxy(argx, argy);
    printf("SO%li,%li\n", argx, argy);
    return;
  }
  
  // Запрос о перегрузке.
  if (buffer[0] == 'G' && buffer[1] == 'O' && strlen(buffer) == 2) {
    printf("GO%i\n", getOverload());
    return;
  }

  // Получить идентификатор прибора.
  if (buffer[0] == 'I' && buffer[1] == 'D' && strlen(buffer) == 2) {
    printf("ID%s\n", "2f8771d5ebf55e0983210304c6d5197e");
    return;
  }
  
  printf("?%s\n", buffer);
}