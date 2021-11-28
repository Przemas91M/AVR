#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
int main(void)
{
//inicjalizacja portów wyjsciowych
DDRA |=(1<<PA0)|(1<<PA1)|(1<<PA2);
//ustawienie stanu wysokiego na portach
PORTA |= (1<<PA0)|(1<<PA1)|(1<<PA2);
// Ustawienie timera z przeskalerem 1024
TCCR1B |= ((1 << CS10) | (1 << CS12));
//petla glowna
while(1)
	{
		//czerwone
		PORTA |= (1<<PA1);
		PORTA &= ~(1<<PA0);
		_delay_ms(8000);
		//czerwone i pomaranczowe
		PORTA &= ~(1<<PA1);
		_delay_ms(1000);
		//zielone
		PORTA |= (1<<PA0)|(1<<PA1);
		PORTA &= ~(1<<PA2);
		_delay_ms(8000);
		//pomaranczowe(do czerwonego)
		PORTA |=(1<<PA2);
		PORTA &= ~(1<<PA1);
		_delay_ms(2500);
	
	}





}
