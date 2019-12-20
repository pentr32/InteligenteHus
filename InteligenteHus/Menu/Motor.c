/*
 * Motor.c
 *
 * Created: 18-12-2019 11:33:07
 *  Author: robe1819
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "Motor.h"

// Motor settings
bool motor_Enabled = false;

void ServoMotor_Init()
{
	DDRE |= (1<<DDE5);
	
	TCCR3B |= (1<<WGM33);
	
	TCCR3A |= (1<<COM3A1) | (1<<WGM31);
	
	ICR1 = 20000;
	
	OCR3C = 1000;
	
	TCCR1B |= ((1<<CS31));

}

void OpenWindows()
{
	//OCR2A = 1000;
	for(OCR3C=2000;OCR3C >= 1000;OCR3C--)
	{
		_delay_ms(2);
	}
}

void CloseWindows()
{
	//OCR2A = 2000;
	for(OCR2A=1000;OCR3C <= 2000;OCR3C++)
	{
		_delay_ms(2);
	}
}

void Toggle_ServoMotor()
{
	motor_Enabled = !motor_Enabled;
	
	if(motor_Enabled)
	{
		OpenWindows();
		
		lcd_clrscr();
		lcd_puts("Window is open");
	}
	
	if(!motor_Enabled)
	{
		CloseWindows();
		
		lcd_clrscr();
		lcd_puts("Window is closed");
	}
}