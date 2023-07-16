/*-----------------------------------------INCLUDES---------------------------------------------*/
#include"common_macros.h"
#include"lcd.h"
#include<util/delay.h>
#include"gpio.h"
/*
 * This fuction has a role to write comand on the lcd that takes the comand an aut it on the lcd
 * */
void LCD_sendcommand(uint8 command)
{
#if (LCD_DAT_BITES_MODE == 8)
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID, LOGIC_LOW);/*make the Rs pin is zero as it comand mode*/
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);/*To Enabel the lcd */
	_delay_ms(1);
	GPIO_writePort(PORTC_ID,command); /*write comand */
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);/*make the port used to send comand as output*/
	_delay_ms(1);
#elif (LCD_DAT_BITES_MODE == 4)
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_1, GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_2, GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_3, GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_4, GET_BIT(command,7));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_1, GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_2, GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_3, GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_4, GET_BIT(command,3));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#endif
}
/*
 * This fuction has a role to write comand on the lcd that takes the comand an aut it on the lcd
 * */
void LCD_displyCharacter(uint8 character)
{
#if (LCD_DAT_BITES_MODE == 8)
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID, LOGIC_HIGH);/*make the Rs pin is zero as it comand mode*/
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);/*To Enabel the lcd */
	_delay_ms(1);
	GPIO_writePort(PORTC_ID,character); /*write comand */
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);/*make the port used to send comand as output*/
	_delay_ms(1);
#elif (LCD_DAT_BITES_MODE == 4)
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_1, GET_BIT(character,4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_2, GET_BIT(character,5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_3, GET_BIT(character,6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_4, GET_BIT(character,7));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_1, GET_BIT(character,0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_2, GET_BIT(character,1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_3, GET_BIT(character,2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_4, GET_BIT(character,3));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#endif
}
/*
 * This fuction is used to iniate the lcd */
void LCD_init(void)
{
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);/*make the rs pin as output */
	GPIO_setupPinDirection(LCD_E_PORT_ID , LCD_E_PIN_ID, PIN_OUTPUT);/*make the enable  pin as output */
	_delay_ms(25);
	#if (LCD_DAT_BITES_MODE == 8)
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);/*make the port as output */
	LCD_sendcommand(LCD_TWO_LINES_EIGHT_BITS_MODE);/*iniate lcd using 8bit and 2lines mode*/
#elif (LCD_DAT_BITES_MODE == 4)
	/*SETUP DIRECTION OF FOUR PINS TO BE OUTPUT PINS */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_PIN_1, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_PIN_2, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_PIN_3, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_PIN_4, PIN_OUTPUT);

	/*USING 2 FUNCTIONS TO INIT THE LCD*/
	LCD_sendcommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendcommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/*USE ININT DERECTLY TO COMPLETELY INIT THE LCD */
	LCD_sendcommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#endif

	LCD_sendcommand(LCD_CURSOR_OFF);/*make cursor off */
	LCD_sendcommand(LCD_CLEAR_COMMAND);/*remove any data from lcd*/

}
void LCD_writeString(const uint8 *str)
{
	uint8 i = 0;
	while(str[i] != '\0'){
		LCD_displyCharacter(str[i]);
		_delay_ms(50);
		i++;
	}
}
/**/
void LCD_moveCursor(uint8 row, uint8 col)
{
	uint8 LCD_ADDRESS ;
	switch(row)
	{
	case 0:
		LCD_ADDRESS = col ;
		break;
	case 1:
		LCD_ADDRESS = col + 0X40 ;
		break;
	case 2:
		LCD_ADDRESS = col + 0X10 ;
		break;
	case 3:
		LCD_ADDRESS = col + 0X50 ;
		break;
	}
	LCD_sendcommand(LCD_ADDRESS | LCD_SET_CURSOR_LOCATION);
}
void LCD_displayStringRowCol(uint8 row, uint8 col, const uint8* str)
{
	LCD_moveCursor(row,col);
	LCD_writeString(str);
}
void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_writeString(buff); /* Display the string */
}
void LCD_clearScreen(void)
{
	LCD_sendcommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}
