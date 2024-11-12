#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "lcd.h"  


void adc_init(void) {
	
	ADMUX = (1 << REFS0); 
	
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}


uint16_t adc_read(uint8_t ch) {
	
	ch &= 0b00000111; 
	ADMUX = (ADMUX & 0xF8) | ch; 
	ADCSRA |= (1 << ADSC); 
	while (ADCSRA & (1 << ADSC)); 
	return ADC; 
}

int main(void) {
	char buffer[16]; 
	uint16_t adc_value;
	float temperature;

	lcd_init();  
	adc_init();  

	while (1) {
		
		adc_value = adc_read(0);
		
		
		snprintf(buffer, sizeof(buffer), "ADC: %d", adc_value);
		lcd_set_cursor(0, 0); 
		lcd_string(buffer);
		_delay_ms(2000); 

		
		float voltage = adc_value * (5.0 / 1024.0);
		
		
		temperature = voltage * 100;

		
		snprintf(buffer, sizeof(buffer), "Temp: %d C", (int)temperature);
		lcd_set_cursor(0, 1); 
		lcd_string(buffer);
		
		_delay_ms(2000); 
	}
}
