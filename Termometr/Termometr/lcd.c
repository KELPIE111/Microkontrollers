/*
 * lcd.c
 *
 * Created: 11.09.2024 14:11:57
 *  Author: JakubM
 */ 

#include "lcd.h"

void lcd_command(uint8_t cmd)
{
	PORTD = (cmd & 0xF0);
	PORTD &= ~(1 << RS);
	PORTD |= (1 << E);
	_delay_ms(1);
	PORTD &= ~(1 << E);
	
	_delay_ms(200);
	
	PORTD = (cmd << 4);
	PORTD &= ~(1 << RS);
	PORTD |= (1 << E);
	_delay_ms(1);
	PORTD &= ~(1 << E);
	
	_delay_ms(2);
}

void lcd_data(uint8_t data)
{
	PORTD = (data & 0xF0);
	PORTD |= (1 << RS);
	PORTD |= (1 << E);
	_delay_ms(1);
	PORTD &= ~(1 << E);
	
	_delay_ms(200);
	
	PORTD = (data << 4);
	PORTD |= (1 << RS);
	PORTD |= (1 << E);
	_delay_ms(1);
	PORTD &= ~(1 << E);
	
	_delay_ms(2);
}


void lcd_init(void)
{
	DDRD = 0xFF;
	_delay_ms(20);
	
	lcd_command(0x02);
	lcd_command(0x28);
	lcd_command(0x0C);
	lcd_command(0x06);
	lcd_command(0x01);
	
	_delay_ms(2);
}

void lcd_string(const char *str)
{
	while (*str)
	{
		lcd_data(*str++);
	}
}

void lcd_set_cursor(uint8_t col, uint8_t row)
{
	uint8_t address;
	
	switch(row)
	{
		case 0: 
		address = 0x00 + col;
		break;
		
		case 1:
		address = 0x40 + col;
		break;
		 
		default:
		address = 0x00 + col;
		break;
		
	}
	lcd_command(0x80 | address);
}