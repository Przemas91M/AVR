#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define SPEAKER_PORT	PORTC

#define SPEAKER_DDR  	DDRC

#define SPEAKER_PIN  	7


void PLAYNOTE(float duration, float frequency);
int main(void)
{
//piny PA0-PA7 jako wejscie
DDRA &= ~(1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6)|(1<<PA7);
while(1)
	{

	if(!(PINA & (1<<PA0)))
		{
			 PLAYNOTE(50,880);
		}
	else if(!(PINA & (1<<PA1)))
		{
			 PLAYNOTE(50,932);
		}
	else if(!(PINA & (1<<PA2)))
		{
			 PLAYNOTE(50,988);
		}   
	else if(!(PINA & (1<<PA3)))
		{
			 PLAYNOTE(50,1047);
		}
	else if(!(PINA & (1<<PA4)))
		{
			 PLAYNOTE(50,1175);
		}
	else if(!(PINA & (1<<PA5)))
		{
			 PLAYNOTE(50,1319);
		}
	else if(!(PINA & (1<<PA6)))
		{
			 PLAYNOTE(50,1397);
		}
	else if(!(PINA & (1<<PA7)))
		{
			 PLAYNOTE(50,1568);
		}

	}


}
void PLAYNOTE(float duration, float frequency)
{

	long int i,cycles;
	float half_period;	
	float wavelength;
	
	wavelength=(1/frequency)*1000;	
	cycles=duration/wavelength;	
	half_period = wavelength/2;	

	
	SPEAKER_DDR |= (1 << SPEAKER_PIN);

	for (i=0;i<cycles;i++) 	
	{
		_delay_ms(half_period);	
		SPEAKER_PORT |= (1 << SPEAKER_PIN);	
		_delay_ms(half_period);	
		SPEAKER_PORT &= ~(1 << SPEAKER_PIN);
	}

	return;
}

