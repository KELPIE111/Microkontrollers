/*
 * wyscig.c
 *
 * Created: 05.09.2024 14:09:04
 * Author : JakubM
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 0b111111;
	PORTD = 0b10000000; 
	int green = 0;
	int restart = 0;
	
	int is_pressed(void)
	{
		if (!(PIND & (1 << PD7)))
		{
			_delay_ms(50);
			if (!(PIND & (1 << PD7)))
			{
				return 1;
			}
		}
		return 0;
	}
	
    while (1) 
    {
		if (is_pressed())
		{
			_delay_ms(50);
			
			if (green == 0 && restart == 0)
			{
				PORTB |= (1 << PB5);
				_delay_ms(500);
				PORTB |= (1 << PB4);
				_delay_ms(500);
				PORTB |= (1 << PB3);
				_delay_ms(500);
				PORTB |= (1 << PB2);
				_delay_ms(500);
				PORTB |= (1 << PB1);
			} 
			else if (green == 1 && restart == 0) 
			{
				PORTB = 0b000000;
				PORTB |= (1 << PB0);
				
				restart = !restart;
			}
			else if (green == 1 && restart == 1)
			{
				PORTB &= ~(1 << PB0);
				_delay_ms(50);
				
				restart = !restart;
			}
			green = !green;
		} 
    }
}

