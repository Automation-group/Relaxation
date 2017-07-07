#ifndef COMMANDS_AD7730_H_
#define COMMANDS_AD7730_H_

#include <stdio.h>

void ad_init(void);
void ad_wait_rdy(void);
char ad_check_rdy(void);
char spi(char data);

char ad_ReadStatusReg (void);
unsigned long ad_ReadGainReg (void);
unsigned long ad_ReadOffsetReg (void);
unsigned long ad_ReadTestReg (void);
unsigned long ad_ReadModeReg (void);
unsigned long ad_ReadFilterReg (void);
char ad_ReadDacReg (void);
unsigned long ad_ReadDataReg24 (void);
unsigned int ad_ReadDataReg16 (void);

void ad_WriteFilterReg (unsigned long mr);
void ad_WriteModeReg (unsigned long mr);
void ad_WriteOffsetReg (unsigned long mr);
void ad_WriteGainReg (unsigned long mr);
void ad_WriteDacReg (char mr);

#endif /* COMMANDS_AD7730_H_ */