/*
 * LCD_test.c
 *
 * Created: 06.09.2024 13:41:27
 * Author : KubaM
 */ 



/*
 * File:   main_wyswietlacz_LCD_16x2.c
 * Author:  elektronikawsrode inspirowany ksia�k� "Mikrokontrolery PIC w praktycznych zastosowaniach" Paw�a Borkowskiego
 * hardware: PIC16F1827 i LCD 16x2
 */
// PIC16F1827 Configuration Bit Settings
// CONFIG1



/* 
 * podstawiaj�c odpowiednie warto�ci rejestr�w syfrowych wej�� i wyj��(I/O), czyli rejestru TRIS i PORT dla odpowiednich port�w 
 * w�asnego mikrokontrolera (zobacz to w datasheet) uczynimy skrypt naprawd� uniwesalnym
*/ 
#define TRIS_RS_LCD TRISBbits.TRISB2 // podstaw w�asny bit rejestru TRIS poru I/O swojego PICa kt�ry pod��czony jest do wy�wietlacza na RS
#define TRIS_EN_LCD TRISBbits.TRISB3 // podstaw w�asny bit rejestru TRIS poru I/O swojego PICa kt�ry pod��czony jest do wy�wietlacza na EN
#define TRIS_DB4_LCD TRISBbits.TRISB4 // podstaw w�asny bit rejestru TRIS poru I/O swojego PICa kt�ry pod��czony jest do wy�wietlacza na DB4
#define TRIS_DB5_LCD TRISBbits.TRISB5 // podstaw w�asny bit rejestru TRIS poru I/O swojego PICa kt�ry pod��czony jest do wy�wietlacza na DB5
#define TRIS_DB6_LCD TRISBbits.TRISB6 // podstaw w�asny bit rejestru TRIS poru I/O swojego PICa kt�ry pod��czony jest do wy�wietlacza na DB6
#define TRIS_DB7_LCD TRISBbits.TRISB7 // podstaw w�asny bit rejestru TRIS poru I/O swojego PICa kt�ry pod��czony jest do wy�wietlacza na DB7

#define RS_LCD PORTBbits.RB2 // podstaw odpowiednie bit rejestru PORT twojego kontrolera podobnie jak wy�ej
#define EN_LCD PORTBbits.RB3
#define DB4_LCD PORTBbits.RB4  
#define DB5_LCD PORTBbits.RB5
#define DB6_LCD PORTBbits.RB6
#define DB7_LCD PORTBbits.RB7

#include <avr/io.h>
#include <stdio.h> // potrzebne aby dzia�a�y np. takie funkcje jak sprintf()
#include "lcd.h" // nasz plik nag��wkowy

#define _XTAL_FREQ 16000000 // rezonator zewn�trzny jest na 18 MHz potrzebne jako odniesienie do makra __delay_

void main(void) {
    // pierwsza napis dla jednej lini
    char napis1[] = "Odliczanie";
    // drugi napis dla drugiej lini
    char napis2[] = "Ka Bummm!!!";
    // wyliczenie d�ugo�ci wyraz�w
    int dlugosc1 = 0; int dlugosc2 = 0; // deklaracja zmiennych typu int
    dlugosc1 = sizeof(napis1) / sizeof(napis1[0])-1; // wyliczenie d�ugo�ci naspisu 1 (pomniejszone o 1 aby dobrze wpisywa�o si� w liczenie tablicowe)
    dlugosc2 = sizeof(napis2) / sizeof(napis2[0])-1; // wyliczenie d�ugo�ci naspisu 2 (pomniejszone o 1 aby dobrze wpisywa�o si� w liczenie tablicowe)
    char bufor[2]; // zmienna potrzebna do zmiany liczby na znak
    unsigned int i; // zmienna i do p�tli for
  
    ANSELB = 0b00000000; //wy��czenie linii analogowych (wszystkie linie cyfrowe)
  
    WlaczLCD(); //inicjalizacja wy�wietlacza LCD
    UstawKursorLCD(1, 2); //wiersz 1. kolumna 2.
    WyswietlLCD(napis1, dlugosc1); //wy�wietl napis
    // odliczanie
    for(i=9; i>0; i--)
    {
        sprintf(bufor, "%d", i); // konwersja liczby na napis aby przyj�a go funkcja WyswietlLCD()
        UstawKursorLCD(1,15); //wiersz 1. kolumna 15.
        WyswietlLCD(bufor, 1); //wy�wietl napis
        __delay_ms(1000); //zaczekaj 1 s
    }
    UstawKursorLCD(2, 4); //wiersz 2. kolumna 4.
    WyswietlLCD(napis2, dlugosc2); //wy�wietl napis
    
    while(1); //p�tla niesko�czona
}

