#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
signed char sec = 0;
signed char min = 0;
signed char hour = 0;
char count_flag =  0;
void display (void){
	PORTC = (PORTC & 0xF0) | (hour/10 & 0x0F);
	PORTA = 0b00000001;
	_delay_ms(5);
	PORTA=0;
	PORTC = (PORTC & 0xF0) | (hour%10 & 0x0F);

	PORTA = 0b00000010;
	_delay_ms(5);
	PORTA=0;
	PORTC = (PORTC & 0xF0) | (min/10 & 0x0F);

	PORTA = 0b00000100;
	_delay_ms(5);
	PORTA=0;
	PORTC = (PORTC & 0xF0) | (min%10 & 0x0F);

	PORTA = 0b00001000;
	_delay_ms(5);
	PORTA=0;
	PORTC = (PORTC & 0xF0) | (sec/10 & 0x0F);

	PORTA = 0b00010000;
	_delay_ms(5);
	PORTA=0;
	PORTC = (PORTC & 0xF0) | (sec%10 & 0x0F);
	PORTA = 0b00100000;
	_delay_ms(5);
	PORTA=0;
}
void Timer1_init(void){
	SREG |= (1<<7);
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS10) | (1<<CS12);
	ICR1 = 15625;
	TIMSK |= (1<<OCIE1A);
	TCCR1A = 0;
}
void INT0_init(void){
	MCUCR |= (1<<ISC01);
	MCUCR &= ~(1<<ISC00);
	GICR |= (1<<INT0);
}
void INT1_init(void){
	MCUCR |= (1<<ISC10) | (1<ISC11);
	GICR |= (1<<INT1);
}
void INT2_init(void){
	GICR |= (1<<INT2);
	MCUCR &= ~(1<<ISC2);

}
int main (void){
	Timer1_init();
	INT0_init();
	INT1_init();
	INT2_init();
	DDRB &= ~(1<<1) & ~(1<<0) & ~(1<<6) & ~(1<<6) & ~(1<<5) & ~(1<<4) & ~(1<<3);
	PORTB |= (1<<1) | (1<<0) | (1<<6) | (1<<5) | (1<<4) | (1<<3);
	DDRB &= ~(1<<7);
	PORTB |= (1<<7);
	DDRB &= ~(1<<2);
	PORTB |= (1<<2);
	DDRD &= ~(1<<3);
	DDRA |= 1;
	DDRD &= ~(1<<2);
	PORTD |= (1<<2);
	PORTD |= (1<<3);
	PORTA &= ~(1);
	DDRC |= 0b00001111;
	PORTC &= 11110000;
	PORTC = 0;
	DDRD |= (1<<4) | (1<<5);
	PORTD |= (1<<4);
	PORTD &= ~(1<<5);
	DDRD |= 1;
	PORTD &= ~(1);
	for(;;){
		if(!(PINB & (1<<7))){
			count_flag ^= 1;
		}
		while(!(PINB & (1<<7))){
			display();
		}
		if(!(PINB & (1<<1))){
			hour ++;
		}
		while(!(PINB & (1<<1))){
			display();
		}
		if(!(PINB & (1<<0))){
			hour --;
		}
		while(!(PINB & (1<<0))){
			display();
		}
		if(!(PINB & (1<<4))){
			min ++;
		}
		while(!(PINB & (1<<4))){
			display();
		}
		if(!(PINB & (1<<3))){
			min --;
		}
		while(!(PINB & (1<<3))){
			display();
		}
		if(!(PINB & (1<<6))){
			sec ++;
		}
		while(!(PINB & (1<<6))){
			display();
		}
		if(!(PINB & (1<<5))){
			sec --;
		}
		while(!(PINB & (1<<5))){
			display();
		}
		if(sec > 59){
			sec = 0;
			min ++;
		}
		if(min > 59){
			min = 0;
			hour ++;
		}
		if((sec < 0) && (min != 0)){
			min --;
			sec = 59;
		}
		else if((sec < 0) && (hour != 0)){
			hour --;
			min = 59;
			sec = 59;
		}
		if(sec == 0 && min ==0 && hour ==0 && count_flag ==1){
			PORTD |= 1;
		}
		else{
			PORTD &= ~(1);
		}
		if((min < 0) && (hour != 0)){
			hour --;
			min = 59;
		}
		display();
	}

}
ISR(INT1_vect){
	TIMSK &= ~(1<<OCIE1A);
}
ISR(INT2_vect){
	TIMSK |= (1<<OCIE1A);
}
ISR(TIMER1_COMPA_vect){
	if(sec == 0 && min ==0 && hour ==0 && count_flag ==1){

	}
	else if(count_flag){
		if(!(sec == 0 && min ==0 && hour ==0)){
		sec --;
		PORTD |= (1<<5);
		PORTD &= ~(1<<4);
		}
	}
	else if(count_flag == 0){
		sec ++;
		PORTD |= (1<<4);
		PORTD &= ~(1<<5);
	}

}
ISR(INT0_vect){
	sec = 0;
	min = 0;
	hour = 0;
}

