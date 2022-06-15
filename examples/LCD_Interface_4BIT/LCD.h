/*
 * LCD.h
 *
 *  Created on: Apr 18, 2022
 *      Author: Kushal Nesarkar
 */

#ifndef LCD_H_
#define LCD_H_

   extern void LCD_Command(uint8_t c);
   extern void LCD_init(void);
   extern void LCD_Clear(void);
   extern void LCD_cursorPosition(uint8_t line);

   extern void Display_character(unsigned char d);
   extern void Display_string(unsigned char *d);


   extern char *i_to_a(int num);
   extern int no_of_digits(int num);
   extern void Display_Digits(int value);




   extern void Display_FloatValue(double value);





#endif /* LCD_H_ */
