/*
 * uart.c
 *
 *  Created on: 23-05-2013
 *      Author: Piotr Rzeszut
 *  
 * Description: Przyk�ad obs�ugi UART z zastosowaniem przerwa� i bufora ko�owego
 */
#include "uart.h"
#define F_CPU 16000000UL
volatile char UART_RX_BUF[UART_BUFFER_SIZE];
volatile uint8_t uart_rx_h=0;
volatile uint8_t uart_rx_t=0;

volatile char UART_TX_BUF[UART_BUFFER_SIZE];
volatile uint8_t uart_tx_h=0;
volatile uint8_t uart_tx_t=0;

volatile uint8_t rx_overrun=0;

void uart_init(uint16_t baud){
	//wyliczamy warto�� rejestru UBRR
	uint16_t ubrr_cal=F_CPU/16/baud-1;
	//konfiguracja baud
	UBRRH = (uint8_t)(ubrr_cal>>8);
	UBRRL = (uint8_t)ubrr_cal;
	//w��czenie UART
	UCSRB = (1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UCSRB |= (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
}

void uart_putc(char data){
	uint8_t new_h=(uart_tx_h+1)&UART_BUFFER_MASK;
	while(new_h==uart_tx_t);
	UART_TX_BUF[new_h]=data;
	uart_tx_h=new_h;
	UCSRB |= (1<<UDRIE);
}

void uart_puts(char *string){
	char c;
	while((c=*string++))uart_putc(c);
}

void uart_putint(int number, uint8_t base){
	char buffer[20];
	itoa(number,buffer,base);
	uart_puts(buffer);
}

char uart_getc(void){
	if(uart_rx_t==uart_rx_h)return 0;
	uart_rx_t=(uart_rx_t+1)&UART_BUFFER_MASK;
	return UART_RX_BUF[uart_rx_t];
}

uint16_t uart_getint(void){
  char odebrany=0;
  uint16_t liczba=0;
  do{
  	odebrany=uart_getc();
    if(odebrany!=0){
      if(odebrany!='\r'){//filtrujemy znak zako�czenia liczby
	  	uart_putc(odebrany);
        liczba*=10;
        liczba+=odebrany-'0';
      }
    }
  }while(odebrany!='\r');//je�li odebrali�my znak zako�czenia liczby to wychodzimy z p�tli  
  return liczba;//zwracamy odebran� liczb�
}

ISR(USART_RXC_vect){
	uint8_t new_h=(uart_rx_h+1)&UART_BUFFER_MASK;

	if(new_h!=uart_rx_t){
		uart_rx_h=new_h;
		UART_RX_BUF[uart_rx_h]=UDR;
	}else{
		rx_overrun=1;
		new_h=UDR;//odczytujemy bufor, �eby nie zawiesi� systemu
	}
}

ISR(USART_UDRE_vect){
	if(uart_tx_t!=uart_tx_h){
		uart_tx_t=(uart_tx_t+1)&UART_BUFFER_MASK;
		UDR=UART_TX_BUF[uart_tx_t];
	}else{
		UCSRB &= ~(1<<UDRIE);
	}
}


