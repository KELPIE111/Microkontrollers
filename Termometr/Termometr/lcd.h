/*
 * lcd.h
 *
 * Created: 11.09.2024 14:05:32
 *  Author: JakubM
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>

#define RS PD2
#define E PD3
#define D4 PD4
#define D5 PD5
#define D6 PD6
#define D7 PD7

void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_string(const char *str);
void lcd_set_cursor(uint8_t col, uint8_t row);




#endif /* LCD_H_ */