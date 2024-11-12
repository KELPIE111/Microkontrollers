/*
 * lcd.h
 *
 * Created: 06.09.2024 14:22:12
 *  Author: KubaM
 */ 


#ifndef LCD_H_
#define LCD_H_

/* 
 * File: lcd16x2.h
 * Author: elektronikawsrode inspirowany ksia¿k¹ "Mikrokontrolery PIC w praktycznych zastosowaniach" Paw³a Borkowskiego
 */
#define _XTAL_FREQ 16000000 // rezonator jest na 18 MHz

void Wyslij_do_LCD(unsigned char bajt)
{
    //ustawienie EN
    EN_LCD = 1;
    //wys³anie 4 najstarszych bitów danych
    if(bajt & 0x80) DB7_LCD = 1; else DB7_LCD = 0;
    if(bajt & 0x40) DB6_LCD = 1; else DB6_LCD = 0;
    if(bajt & 0x20) DB5_LCD = 1; else DB5_LCD = 0;
    if(bajt & 0x10) DB4_LCD = 1; else DB4_LCD = 0;
    //zaczekaj 1 ?s
    __delay_us(1);
    //potwierdzenie wys³ania danych (opadaj¹cym zboczem EN)
    EN_LCD = 0;
    //zaczekaj 1 ?s
    __delay_us(1);
    //ustawienie EN
    EN_LCD = 1;
    //wys³anie 4 najm³odszych bitów danych
    if(bajt & 0x08) DB7_LCD = 1; else DB7_LCD = 0;
    if(bajt & 0x04) DB6_LCD = 1; else DB6_LCD = 0;
    if(bajt & 0x02) DB5_LCD = 1; else DB5_LCD = 0;
    if(bajt & 0x01) DB4_LCD = 1; else DB4_LCD = 0;
    //zaczekaj 1 ?s
    __delay_us(1);
    //potwierdzenie wys³ania danych (opadaj¹cym zboczem EN)
    EN_LCD = 0;
    //zaczekaj 37 ?s
    __delay_us(37);
}
void CzyscLCD()
{
    RS_LCD = 0;
    Wyslij_do_LCD(1);
    RS_LCD = 1;
    //czekaj 1.64 ms
    __delay_us(1640);
}
void WyswietlLCD(char *napis, unsigned char ile)
{
    for (unsigned int k = 0; k<ile; k++)
    {
        Wyslij_do_LCD(napis[k]);
    }
}
void UstawKursorLCD(unsigned char y, unsigned char x)
{
    //ustal nowy adres pamiêci DD RAM
    unsigned char n;
    if (y==1) 
        n = x - 1;
    else 
        n = 0x40 + x - 1;
    //ustaw kod
    n |= 0b10000000;
    //wyœlij rozkaz ustawienia nowego adresu DD RAM
    RS_LCD = 0;
    Wyslij_do_LCD(n);
    RS_LCD = 1;
}
void WlaczLCD()
{
    //ustawienie kierunku wyjœciowego linii pod³¹czonych do LCD
    TRIS_RS_LCD = 0;
    TRIS_EN_LCD = 0;
    TRIS_DB7_LCD = 0;
    TRIS_DB6_LCD = 0;
    TRIS_DB5_LCD = 0;
    TRIS_DB4_LCD = 0;
    //stan niski na liniach
    RS_LCD = 0;
    EN_LCD = 0;
    DB7_LCD = 0;
    DB6_LCD = 0;
    DB5_LCD = 0;
    DB4_LCD = 0;
    //zaczekaj co najmniej 45 ms na ustabilizowanie siê napiêcia
    __delay_us(45000);
    //1
    //ustaw liniê EN
    EN_LCD = 1;
    //za³aduj sekwencjê 0011
    DB7_LCD = 0;
    DB6_LCD = 0;
    DB5_LCD = 1;
    DB4_LCD = 1;
    //zaczekaj 1 ?s
    __delay_us(1);
    //potwierdŸ opadaj¹cym zboczem EN
    EN_LCD = 0;
    //zaczekaj co najmniej 4,1 ms
    __delay_us(4100);
    //2
    //ustaw liniê EN
    EN_LCD = 1;
    //zaczekaj 1 ?s
    __delay_us(1);
    //potwierdŸ opadaj¹cym zboczem EN sekwencjê 0011
    EN_LCD = 0;
    //zaczekaj co najmniej 100 ?s
    __delay_us(100);
    //3
    //ustaw liniê EN
    EN_LCD = 1;
    //zaczekaj 1 ?s
    __delay_us(1);
    //potwierdŸ opadaj¹cym zboczem EN sekwencjê 0011
    EN_LCD = 0;
    //zaczekaj co najmniej 100 ?s
    __delay_us(100);
    //4
    //ustaw liniê EN
    EN_LCD = 1;
    //ustawienie interfejsu 4-bitowego
    DB4_LCD = 0;
    //zaczekaj 1 ?s
    __delay_us(1);
    //potwierdŸ opadaj¹cym zboczem EN
    EN_LCD = 0;
    //ustaw parametry wyœwietlacza
    //bit 4 = 0 (s³owo danych ma 4 bity)
    //bit 3 = 1 (2 wiersze znaków)
    //bit 2 = 0 (matryca 5×8 pikseli)
    RS_LCD = 0;
    Wyslij_do_LCD(0b00101000);
    RS_LCD = 1;
    //w³¹cz wyœwietlacz
    //bit 2 = 1 (w³¹czenie wyœwietlania)
    //bit 1 = 0 (kursor nieaktywny)
    //bit 0 = 0 (kursor nie miga)
    RS_LCD = 0;
    Wyslij_do_LCD(0b00001100);
    RS_LCD = 1;
    //ustaw tryb pracy wyœwietlacza
    //bit 2 = 1 (inkrementowanie adresu zapisu danych)
    //bit 1 = 1 (wy³¹czenie przesuwania w prawo)
    RS_LCD = 0;
    Wyslij_do_LCD(0b00000110);
    RS_LCD = 1;
    CzyscLCD();
}





#endif /* LCD_H_ */