#include <avr/interrupt.h>

#include "BUFFER.h"
#include "USART.h"

char commBuffer[IN_BUFFER_SIZE];
unsigned char commBufPos = 0;
char command[IN_BUFFER_SIZE+1];
char onCommand = 0;

//SIGNAL(SIG_USART_RECV)
SIGNAL(USART_RX_vect)
{
  char buf = UDR0;
  commBuffer[commBufPos] = buf;
  if (buf == '\n')
  { 
    onCommand = 1;
    for (unsigned char i = 0;i <= commBufPos; ++i)
      command[i] = commBuffer[i];
    command[commBufPos] = 0;
    commBufPos = 0;
  }
  else
    commBufPos++;
  if (commBufPos == IN_BUFFER_SIZE) commBufPos = 0;
}