#include <stdio.h>
#include <avr/io.h>
#include "USART.h"

// Output buffer
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,
                                             _FDEV_SETUP_WRITE);

int uart_putchar(char c, FILE *stream){
  //if (c == '\n')
  //  uart_putchar('\r', stream);
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
  return 0;
}

char ReceiveData (void)
{
  // Wait for data to be received
  while ( !(UCSR0A & (1<<RXC0)) ) ;
  // Get and return received data from buffer
  return UDR0;
}

void USART_Flush (void)
{
  unsigned char dummy;
  while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}

void USART_Init (unsigned int ubrr)
{
  // Set baud ubrr
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;

  // Enable receiver and transmitter
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);

  // Set frame format: 8data, 2stop bit
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
  
  stdout = &mystdout;
}

void USART_Transmit (char data)
{
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) );

  /* Put data into buffer, sends the data */
  UDR0 = data;
}

