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
#include "Menu/Keypad.h"
	
int main(void)
{		
	MaxtrixKeypad_Init();
	ServoMotor_Init();
	Ventilator_Init();
	
	while(1)
	{
		Menu();
		Check_Temperatur();
	}
}

