#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stdio.h>

void invokeCommand(char* __buf);
//char* searchingNumber(char* __buf);

// Обработка команд.
void setSMDsteps (void);
long int setSMDstep(long int step);
char setSMDdirection(char dir);
void setSMDon(void);
void setSMDoff(void);
void setSMDstop(void);
char getSMDinfo(void);
char getSMDdirectionInfo(void);
long int setSMDcounter(long int number);
long int getSMDcounter(void);
long int setSMDfrequency(long int freq);
long int getSMDfrequency(void);
char* getSMDovertravelSwitches(void);
int setSMDdirectionRotationPunch(int dirrot);
int getSMDdirectionRotationPunch(void);
int getSMDoverheat(void);
int getSMDoverload(void);

void directionMotor(void);
void setTimer (int n, long int freq);
int checkDirection(void);
#endif /* COMMANDS_H_ */