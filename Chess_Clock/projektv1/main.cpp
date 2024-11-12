#include <avr/io.h>
#include <avr/interrupt.h>

9
const uint8_t segment_data[] = {
	0b11000000, 
	0b11111001, 
	0b10100100, 
	0b10110000, 
	0b10011001, 
	0b10010010, 
	0b10000010, 
	0b11111000, 
	0b10000000, 
	0b10010000  
};

volatile uint16_t delay_counter = 0;
volatile uint8_t active_player = 0; 

uint16_t player1_minutes = 0; 
uint16_t player1_seconds = 0; 
uint16_t player2_minutes = 0; 
uint16_t player2_seconds = 0; 

volatile uint8_t button_pressed = 0;
volatile uint8_t reset_flag = 0;
volatile uint8_t start_flag = 0;
volatile uint8_t stop_flag = 0;

void init_timer1() {
	
	TCCR1B |= (1 << WGM12); 
	TCCR1B |= (1 << CS12) | (1 << CS10); 
	TIMSK1 |= (1 << OCIE1A); 
	OCR1A = 15624;
	sei(); 
}

ISR(TIMER1_COMPA_vect) {
	delay_counter++; 
}

void init_buttons() {
	
	DDRB &= ~((1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3));
	PORTB |= ((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3));

	
	DDRB &= ~(1 << DDB7);
	PORTB |= (1 << PORTB7);

	
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3) | (1 << PCINT7);
}

void simple_delay_ms(uint16_t ms) {
	
	for (uint16_t i = 0; i < ms; i++) {
		for (uint16_t j = 0; j < 1000; j++) {
			asm volatile("nop");
		}
	}
}

ISR(PCINT0_vect) {
	
	simple_delay_ms(50);

	
	if (!(PINB & (1 << PINB0))) {
		reset_flag = 1;
	}
	if (!(PINB & (1 << PINB1))) {
		stop_flag = 1;
	}
	if (!(PINB & (1 << PINB2))) {
		start_flag = 1;
	}
	
	if (!(PINB & (1 << PINB3))) {
		
		if (active_player == 0) {
			if (player1_minutes < 60) {
				player1_minutes++;
				} else {
				player1_minutes = 0;
			}
			} else {
			if (player2_minutes < 60) {
				player2_minutes++;
				} else {
				player2_minutes = 0;
			}
		}
	}
	if (!(PINB & (1 << PINB7))) {
		button_pressed = 1;
	}
}

void display_digit(uint8_t digit, uint8_t value) {
	
	PORTC = ~(1 << digit); 

	
	PORTD = segment_data[value];

	
	simple_delay_ms(2); 
}

void update_display(uint16_t minutes, uint16_t seconds) {
	uint8_t digits[4];

	digits[0] = minutes / 10;   
	digits[1] = minutes % 10;   
	digits[2] = seconds / 10;   
	digits[3] = seconds % 10;   

	for (uint8_t i = 0; i < 4; i++) {
		display_digit(i, digits[i]);
	}
}

void update_timer(volatile uint16_t* minutes, volatile uint16_t* seconds) {
	if (*seconds == 0) {
		if (*minutes == 0) {
			return;
			} else {
			(*minutes)--;
			*seconds = 59;
		}
		} else {
		(*seconds)--;
	}
}

int main(void) {
	DDRD = 0xFF;
	DDRC = 0x0F;

	init_timer1(); 
	init_buttons(); 

	uint8_t counting = 0;

	while (1) {
		if (delay_counter >= 1) { 
			delay_counter = 0;

			if (counting) {
				if (active_player == 0) {
					update_timer(&player1_minutes, &player1_seconds);
					} else {
					update_timer(&player2_minutes, &player2_seconds);
				}
			}
		}

		 if (reset_flag) {
			 reset_flag = 0;
			 
			 player1_minutes = 0;
			 player1_seconds = 0;
			 player2_minutes = 0;
			 player2_seconds = 0;
			 counting = 0;
		 }

		if (start_flag) {
			start_flag = 0;
			counting = 1;
		}

		if (stop_flag) {
			stop_flag = 0;
			counting = 0;
		}

		if (button_pressed) {
			button_pressed = 0;
			
			active_player = !active_player;
		}

		
		if (active_player == 0) {
			update_display(player1_minutes, player1_seconds);
			} else {
			update_display(player2_minutes, player2_seconds);
		}
	}

	return 0;
}
