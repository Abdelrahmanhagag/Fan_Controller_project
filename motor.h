/*
 * DESCRIPTION: DRIVER FOR DC MOTOR AND CONTROL THE DIRECTION OF MOVEMENT AND INITIATE THE MOTER
 * AUTHER: ABDELRAHMAN MOSTAFA HAJJAJ
 **/

#ifndef MOTOR_H_
#define MOTOR_H_
/*-----------------------------------------INCLUDES--------------------------------------------*/

#include "std_types.h"
/*--------------------------------------DEFINATIONS--------------------------------------------*/
typedef enum {
	STOP,A_CW,CW
}DcMOTOR_state;
/*--------------------------------------configuration------------------------------------------*/
/*definations for the pins connected to the h-bridge*/
#define DC_PIN_CONNECTED_PORT            PORTB_ID
#define INPUT1_PIN                        PIN0_ID
#define INPUT2_PIN                        PIN1_ID
/*ENABLE MUST BE CONNECTED TO PB_3 SO IT WILL BE NOT CONFIGURED HERE*/
/*--------------------------------------FUNCTION PROTOTYPES------------------------------------*/
/*SETUP PINS FOR MOTOR AND STOP MOTOR AT BEGINNIGN*/
void DcMotor_init(void);
/*DETECT THE MOTER SETTING LIKE ROTATION DIRECTION AND SPEED TO BE ROTATE*/
void DcMotor_Rotate(DcMOTOR_state state, uint8 speed);



#endif /* MOTOR_H_ */
