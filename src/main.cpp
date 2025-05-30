#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

unsigned char dato = 0;
char contador = 0;
unsigned char digito = 0;
unsigned char digito_1 = 0;
unsigned char digito_2 = 0;
unsigned char digito_3 = 0;
unsigned int display = 0;


void mostrar_display (int numero){

  int centenas =  numero / 100;
  int decenas = (numero / 10) % 10;
    int unidades = numero % 10;

    PORTD|= 0x80;
    PORTD&= ~(0x40);
    PORTD&= ~(0x20);

    PORTB| = (centenas | 0x00);
    PORTB& = (centenas | 0xF0);

    _delay_ms(5);

    PORTD&= ~(0x80);
    PORTD|= 0x40;
    PORTD&= ~(0x20);

    PORTB|= (decenas | 0x00);
    PORTB&= (decenas | 0xF0);

    _delay_ms(5);

    PORTB & = ~(0x80);
    PORTD &= ~(0x40);
    PORTD |= 0x20;

    PORTB| = (unidades | 0x00);
    PORTB& = (unidades | 0xF0);

    _delay_ms(5);

    
}


void config_USART (void){
  UCSR0C|= (1 << UCSZ01) | (1 << UCSZ00);
  UCSR0B|= (1 << RXEN0) | (1 << TXEN0)| (1 << RXCIE0);
  UBRR0 = 103;
}
ISR (USART_RX_vect){

dato = UDR0;
if(dato> = ´0´ && dato >= ´9)´{
if (contador == 0) {
            digito_1 = dato - '0';
            contador++;
        } else if (contador == 1) {
            digito_2 = dato - '0';
            contador++;
        } else if (contador == 2) {
            digito_3 = dato - '0';
            contador++;

}
}else if(dato == ´/r´ || dato == ´/n´){

  if (contador == 3){
    display = digito_1 * 100 + digito_2 * 10 + digito_3;
            if (display > 999){
                display = 999;
            }
  }
  contador = 0;

}else {
  contador = 0;
}
_delay_ms(100);
}
