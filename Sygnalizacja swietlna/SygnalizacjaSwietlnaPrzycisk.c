#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h> 
volatile int flaga = 4;
volatile int przycisniety = 0;
volatile int skonczony = 0;
volatile int drugi = 0;
volatile int counter = 0;
int licznik = 0;
#define LED1 PA0//czerwone
#define LED2 PA1//pomaranczowe
#define LED3 PA2//zielone
#define LED4 PA3//zielone dla pieszych
int main(void)
{
//unsigned int sekundnik = 0;
//inicjalizacja portów wyjsciowych
DDRA |=(1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4);
//ustawienie pinu jako wejsciowego
DDRC &= ~(1<<PC0);
//podlaczenie rezystora pullup
PORTA |= (1<<PC0);
//ustawienie stanu wysokiego na portach
PORTA |= (1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4);
TCNT1 = 65535;
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
		//przycisk wcisniety od razu(natychmiast)
		if(!(PINC & (1<<PC0)) && przycisniety == 0)
		{
			flaga = 0;
			TCNT1=65535;
			przycisniety = 1;
		}
		//obsluga drgan przycisku
		else if(!(PINC & (1<<PC0)) && przycisniety == 1)
		{			
			if(counter < 100)
			{
				counter++;
			}
			else
			{
				przycisniety = 2;
				counter = 0;
			}
		}
		else if//sekwencja juz dziala, drugi raz przycisk wcisniety
		(!(PINC & (1<<PC0)) && przycisniety == 2 && skonczony == 0)
		{
			drugi = 1;	
		}
		//sekwencja skonczona, oczekiwanie na ponowne uruchomienie sekwencji
		else if(przycisniety == 2 && skonczony == 1 && drugi == 1)
		{
			flaga = 0;
			TCNT1 = 0;
			przycisniety = 0;
			skonczony = 0;
			drugi = 0;	
		}
		//sekwencja skonczona, nie bylo drugiego wcisniecia
		else if(przycisniety == 2 && skonczony == 1 && drugi == 0)
		{
			flaga = 4;
			TCNT1 = 0;
			skonczony = 0;
			przycisniety = 0;
		}

	}

}
//obs³uga przerwania
ISR(TIMER1_OVF_vect)   
{
//uruchamiamy sekwencje
switch (flaga)
{
//pomaranczowe
case 0:
		PORTA |= (1<<LED3);
		PORTA &= ~(1<<LED2);
		TCNT1 = 18662;
		flaga++;
		break;
//czerwone i zielone dla pieszych
case 1:
		PORTA |= (1<<LED2);
		PORTA &= ~ (1<<LED1);
		PORTA &= ~ (1<<LED4);
		TCNT1 = 0;
		flaga++;
		break;
//miganie zielonego dla pieszych
case 2:
		PORTA ^= (1<<LED4);
		TCNT1 = 57723;
		licznik++;
		if(licznik == 5)
			{
				flaga = 3;
				licznik = 0;
				TCNT1 = 57723;
			}
//pomaranczowe dla aut
case 3:
		PORTA |=(1<<LED1)|(1<<LED4);
		PORTA &= ~ (1<<LED2);
		TCNT1 = 49911;
		flaga++;
		break;
//zielone dla aut
default:
		PORTA |=(1<<LED2);
		PORTA &= ~ (1<<LED3);
		TCNT1 = 0;
		flaga = 4;
		skonczony = 1;
		break;
}
	 
} 	
