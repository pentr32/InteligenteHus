/*
 * InteligenteHus.c
 *
 * Created: 16-12-2019 13:52:05
 * Author : robe1819
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "MatrixKeypad/Keypad.h"
#include "ServoMotor/Motor.h"
	
int main(void)
{	
	MaxtrixKeypad_Init();
	ServoMotor_Init();
	
	//SpinMotor();
	
	while(1)
	{
		DecodeKeyboard();
	}
}

void Menu()
{
	
}

