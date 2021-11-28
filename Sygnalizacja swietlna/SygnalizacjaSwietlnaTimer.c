#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h> 
volatile unsigned int flaga = 0;
#define LED1 PA0
#define LED2 PA1
#define LED3 PA2
int main(void)
{
//unsigned int sekundnik = 0;
//inicjalizacja portów wyjsciowych
DDRA |=(1<<LED1)|(1<<LED2)|(1<<LED3);
//ustawienie stanu wysokiego na portach
PORTA |= (1<<LED1)|(1<<LED2)|(1<<LED3);
TCNT1 = 57723;
// Ustawienie timera z przeskalerem 1024
//1s=15625 cykli
TCCR1B |= ((1<<CS10)|(1<<CS12));
//odblokowanie przerwañ od przepe³nienia
TIMSK |= (1<<TOIE1);
//odblokowanie przerwania
sei();
//petla glowna
while(1)
	{
	}

}
//obs³uga przerwania
ISR(TIMER1_OVF_vect)   
{
flaga++;
//czerwone
switch (flaga)
{
//czerwone
case 1:
		PORTA |= (1<<LED2);
		PORTA &= ~(1<<LED1);
		TCNT1 = 18662;
		break;
//czerwone i pomaranczowe
case 2:
		PORTA &= ~ (1<<LED2);
		TCNT1 = 49911;
		break;
//zielone
case 3:
		PORTA |=(1<<LED1)|(1<<LED2);
		PORTA &= ~ (1<<LED3);
		TCNT1 = 18662;
		break;
//pomaranczowe
case 4:
		PORTA |=(1<<LED3);
		PORTA &= ~ (1<<LED2);
		TCNT1 = 49911;
		flaga = 0;
		break;
}
	 
} 	
