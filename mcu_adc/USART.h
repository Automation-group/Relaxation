#ifndef __USART_H_
#define __USART_H_

#include <stdio.h>

char ReceiveData (void);

void USART_Flush (void);

void USART_Init (unsigned int baud);

void USART_Transmit (char data);

extern int uart_putchar(char c, FILE *stream); //Функция побайтового вывода

#endif // __USART_H_
