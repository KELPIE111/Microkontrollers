/*
 * LCD_test.c
 *
 * Created: 06.09.2024 13:41:27
 * Author : KubaM
 */ 



/*
 * File:   main_wyswietlacz_LCD_16x2.c
 * Author:  elektronikawsrode inspirowany ksia¿k¹ "Mikrokontrolery PIC w praktycznych zastosowaniach" Paw³a Borkowskiego
 * hardware: PIC16F1827 i LCD 16x2
 */
// PIC16F1827 Configuration Bit Settings
// CONFIG1



/* 
 * podstawiaj¹c odpowiednie wartoœci rejestrów syfrowych wejœæ i wyjœæ(I/O), czyli rejestru TRIS i PORT dla odpowiednich portów 
 * w³asnego mikrokontrolera (zobacz to w datasheet) uczynimy skrypt naprawdê uniwesalnym
*/ 
#define TRIS_RS_LCD TRISBbits.TRISB2 // podstaw w³asny bit rejestru TRIS poru I/O swojego PICa który pod³¹czony jest do wyœwietlacza na RS
#define TRIS_EN_LCD TRISBbits.TRISB3 // podstaw w³asny bit rejestru TRIS poru I/O swojego PICa który pod³¹czony jest do wyœwietlacza na EN
#define TRIS_DB4_LCD TRISBbits.TRISB4 // podstaw w³asny bit rejestru TRIS poru I/O swojego PICa który pod³¹czony jest do wyœwietlacza na DB4
#define TRIS_DB5_LCD TRISBbits.TRISB5 // podstaw w³asny bit rejestru TRIS poru I/O swojego PICa który pod³¹czony jest do wyœwietlacza na DB5
#define TRIS_DB6_LCD TRISBbits.TRISB6 // podstaw w³asny bit rejestru TRIS poru I/O swojego PICa który pod³¹czony jest do wyœwietlacza na DB6
#define TRIS_DB7_LCD TRISBbits.TRISB7 // podstaw w³asny bit rejestru TRIS poru I/O swojego PICa który pod³¹czony jest do wyœwietlacza na DB7

#define RS_LCD PORTBbits.RB2 // podstaw odpowiednie bit rejestru PORT twojego kontrolera podobnie jak wy¿ej
#define EN_LCD PORTBbits.RB3
#define DB4_LCD PORTBbits.RB4  
#define DB5_LCD PORTBbits.RB5
#define DB6_LCD PORTBbits.RB6
#define DB7_LCD PORTBbits.RB7

#include <avr/io.h>
#include <stdio.h> // potrzebne aby dzia³a³y np. takie funkcje jak sprintf()
#include "lcd.h" // nasz plik nag³ówkowy

#define _XTAL_FREQ 16000000 // rezonator zewnêtrzny jest na 18 MHz potrzebne jako odniesienie do makra __delay_

void main(void) {
    // pierwsza napis dla jednej lini
    char napis1[] = "Odliczanie";
    // drugi napis dla drugiej lini
    char napis2[] = "Ka Bummm!!!";
    // wyliczenie d³ugoœci wyrazów
    int dlugosc1 = 0; int dlugosc2 = 0; // deklaracja zmiennych typu int
    dlugosc1 = sizeof(napis1) / sizeof(napis1[0])-1; // wyliczenie d³ugoœci naspisu 1 (pomniejszone o 1 aby dobrze wpisywa³o siê w liczenie tablicowe)
    dlugosc2 = sizeof(napis2) / sizeof(napis2[0])-1; // wyliczenie d³ugoœci naspisu 2 (pomniejszone o 1 aby dobrze wpisywa³o siê w liczenie tablicowe)
    char bufor[2]; // zmienna potrzebna do zmiany liczby na znak
    unsigned int i; // zmienna i do pêtli for
  
    ANSELB = 0b00000000; //wy³¹czenie linii analogowych (wszystkie linie cyfrowe)
  
    WlaczLCD(); //inicjalizacja wyœwietlacza LCD
    UstawKursorLCD(1, 2); //wiersz 1. kolumna 2.
    WyswietlLCD(napis1, dlugosc1); //wyœwietl napis
    // odliczanie
    for(i=9; i>0; i--)
    {
        sprintf(bufor, "%d", i); // konwersja liczby na napis aby przyjê³a go funkcja WyswietlLCD()
        UstawKursorLCD(1,15); //wiersz 1. kolumna 15.
        WyswietlLCD(bufor, 1); //wyœwietl napis
        __delay_ms(1000); //zaczekaj 1 s
    }
    UstawKursorLCD(2, 4); //wiersz 2. kolumna 4.
    WyswietlLCD(napis2, dlugosc2); //wyœwietl napis
    
    while(1); //pêtla nieskoñczona
}

