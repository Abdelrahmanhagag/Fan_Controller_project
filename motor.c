/*------------------------------------includes------------------------------------------------*/
#include "motor.h"
#include "gpio.h"
#include "PWM.h"
/*THIS FUNCTION INTIATE THE MOTER BY SETTING THE DIRECTION OF connected pins to the h bridge
 * and stop the motor at the begging until motor setting has been chosen */
void DcMotor_init(void){


	/*using gpio driver to setup the direction of pins connected to the h-bridge*/
	GPIO_setupPinDirection(DC_PIN_CONNECTED_PORT, INPUT1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_PIN_CONNECTED_PORT, INPUT2_PIN, PIN_OUTPUT);

	/*ENABLE SETUP DIRECTION*/
	//GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);


	/*MOTER SHOULD BE STOPPED UNTIL ALL SETTINGS IS KNOWN*/
	GPIO_writePin(DC_PIN_CONNECTED_PORT, INPUT1_PIN, LOGIC_LOW);
	GPIO_writePin(DC_PIN_CONNECTED_PORT, INPUT2_PIN, LOGIC_LOW);

}

/*DETECT THE MOTER SETTING LIKE ROTATION DIRECTION AND SPEED TO BE ROTATE*/
void DcMotor_Rotate(DcMOTOR_state state, uint8 speed){
	Timer0_PWM_Init(speed);
	if (state == STOP){
		GPIO_writePin(DC_PIN_CONNECTED_PORT, INPUT1_PIN, LOGIC_LOW);
		GPIO_writePin(DC_PIN_CONNECTED_PORT, INPUT2_PIN, LOGIC_LOW);
	}
	else if (state == A_CW){
		GPIO_writePin(DC_PIN_CONNECTED_PORT, INPUT1_PIN, LOGIC_HIGH);
		GPIO_writePin(DC_PIN_CONNECTED_PORT, INPUT2_PIN, LOGIC_LOW);
	}
	else if (state == CW){
		GPIO_writePin(DC_PIN_CONNECTED_PORT, INPUT1_PIN, LOGIC_LOW);
		GPIO_writePin(DC_PIN_CONNECTED_PORT, INPUT2_PIN, LOGIC_HIGH);

	}
}

