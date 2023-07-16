/*
 * lcd.h
 *
 *  Created on: Mar 25, 2023
 *      Author: nada
 */

#ifndef LCD_H_
#define LCD_H_
/*-----------------------------------------INCLUDES--------------------------------------------*/
#include"std_types.h"
/*------------------------------------------DEFINATIONS----------------------------------------*/
/*HW PORTS AND PINS*/
#define LCD_DAT_BITES_MODE                 8
#define LCD_RS_PORT_ID                 PORTD_ID
#define LCD_RS_PIN_ID                  PIN0_ID
#define LCD_E_PORT_ID                  PORTD_ID
#define LCD_E_PIN_ID                   PIN2_ID
#if(LCD_DAT_BITES_MODE == 8)
#define LCD_DATA_PORT_ID               PORTC_ID
#elif(LCD_DAT_BITES_MODE == 4)
#define LCD_DATA_PORT_ID               PORTA_ID
#define LCD_DATA_PIN_1                 PIN3_ID
#define LCD_DATA_PIN_2                 PIN4_ID
#define LCD_DATA_PIN_3                 PIN5_ID
#define LCD_DATA_PIN_4                 PIN6_ID
#endif
/*LCD COMMANDS*/
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

/*---------------------------------------FUNCTION PROTOTYPES-----------------------------------*/
void LCD_sendcommand(uint8 command);
void LCD_displyCharacter(uint8 command);
void LCD_init(void);
void LCD_writeString(const uint8 *str);
void LCD_clearScreen(void);
void LCD_intgerToString(int data);
void LCD_moveCursor(uint8 row, uint8 col);
void LCD_displayStringRowCol(uint8 row, uint8 col, const uint8* str);


#endif /* LCD_H_ */
