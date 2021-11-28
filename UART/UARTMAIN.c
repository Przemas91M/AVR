#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
int main(void)
{
//***ustawienia***//
//pin PA0 jako wejscie
DDRA &= ~(1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6)|(1<<PA7);
//podlaczenie rezystora pullup
PORTA |= (1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6)|(1<<PA7);
//inicjalizacja interfejsu uart 
//wyliczamy wartoœæ rejestru UBRR
uint16_t ubrr_cal=F_CPU/16/9600-1;
//konfiguracja baud
UBRRH = (uint8_t)(ubrr_cal>>8);
UBRRL = (uint8_t)ubrr_cal;
//w³¹czenie UART
UCSRB = (1<<RXEN)|(1<<TXEN);
UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
UCSRB |= (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
sei();
uart_puts("siema");
while(1)
	{
	if(!(PINA & (1<<PA0)))
	{
		uart_putc('1');
		_delay_ms(50);
	}
	else if(!(PINA & (1<<PA1)))
	{
		uart_putc('2');
		_delay_ms(50);	
	}
	else if(!(PINA & (1<<PA2)))
	{
		uart_putc('3');
		_delay_ms(50);	
	}
	else if(!(PINA & (1<<PA3)))
	{
		uart_putc('4');
		_delay_ms(50);	
	}
	else if(!(PINA & (1<<PA4)))
	{
		uart_putc('5');
		_delay_ms(50);	
	}
	else if(!(PINA & (1<<PA5)))
	{
		uart_putc('6');
		_delay_ms(50);	
	}
	else if(!(PINA & (1<<PA6)))
	{
		uart_putc('7');
		_delay_ms(50);	
	}
	else if(!(PINA & (1<<PA7)))
	{
		uart_putc('8');
		_delay_ms(50);	
	}
	else
	{
	}
}
}
