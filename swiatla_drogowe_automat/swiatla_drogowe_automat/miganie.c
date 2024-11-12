/*
 * Street_Lights_automatic.c
 *
 * Created: 02.09.2024 19:00:59
 * Author : JakubM
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	
	DDRB = 0b000001;
	PORTD = 0b10000000;
    
	int button_pressed = 0;
	int led_state = 0;
	
    while (1) 
    {
		if(!(PIND & (1 << PD7)))
		{
			_delay_ms(50);
			
			if(!(PIND & (1 << PD7)) && button_pressed == 0)
			{
				led_state = !led_state;
				button_pressed = 1;
			}
		}
		else
		{
			button_pressed = 0;
		}
			
		while(led_state == 1)
		{
			
			if(!(PIND & (1 << PD7)) && !button_pressed)
			{
				_delay_ms(50);
				
				if (!button_pressed)
				{
					led_state = 0;
					button_pressed = 1;
				}
			}
			else
			{
				button_pressed = 0;
			}
			
			PORTB |= (1 << PB0);
			_delay_ms(500);
			PORTB &= ~(1 << PB0);
			_delay_ms(500);
		}
    }
}

