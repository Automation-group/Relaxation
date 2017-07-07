#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stdio.h>

void invokeCommand(char* __buf);
//char* searchingNumber(char* __buf);

// Обработка команд.
unsigned long getADC(void);
void setPeriod(int period);
void setTimer(int n, long int freq);
void setADCstop(void);
char getInfo(void);

void setADCxy(long int argx, long int argy);
long int getADCx(void);
long int getADCy(void);

int getOverload(void);

#endif /* COMMANDS_H_ */