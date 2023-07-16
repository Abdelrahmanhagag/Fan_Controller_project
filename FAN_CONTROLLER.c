#include "lm35_sensor.h"
#include "lcd.h"
#include "motor.h"
#include "adc.h"
int main(void){
	uint8 temprature ;
	DcMotor_init();
	ADC_configType config = {ADC_INTERNAL_2_56_VOLT,DIVISION_FACTOR_8};
	LCD_init();
	ADC_init(&config);
	LCD_displayStringRowCol(0, 4, "FAN IS ");
	LCD_displayStringRowCol(1, 4, "temp =   c");
	while(1){
		temprature =  LM35_getTemperature();
		LCD_moveCursor(1,10);
		LCD_intgerToString(temprature);
		if (temprature <= 30){
			LCD_displayStringRowCol(0, 12, "OFF");
			DcMotor_Rotate(STOP,0);
		}
		else if (temprature > 30 && temprature < 60){
				LCD_displayStringRowCol(0, 12, "ON");
				DcMotor_Rotate(CW,25);
		}
		else if (temprature >= 60 && temprature < 90){
			LCD_displayStringRowCol(0, 12, "ON");

			DcMotor_Rotate(CW,50);
		}
		else if (temprature >= 90 && temprature < 120){
			LCD_displayStringRowCol(0, 12, "ON");
			DcMotor_Rotate(CW,75);

		}
		else if (temprature >= 120){
			LCD_displayStringRowCol(0, 12, "ON");
			DcMotor_Rotate(CW,100);

		}

	}
	return 0;
}

