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
#include "Motor.h"

void ServoMotor_Init()
{
	DDRB |= (1<<DDB5);
	
	TCCR1B |= (1<<WGM13);
	
	TCCR1A |= (1<<COM1A1) | (1<<WGM11);
	
	ICR1 = 20000;
	
	OCR1A = 1000;
	
	TCCR1B |= ((1<<CS11));

}

void SpinMotor()
{
	CloseWindows();
	
	OpenWindows();
}

void OpenWindows()
{
	//OCR1A = 1000;
	for(OCR1A=2000;OCR1A >= 1000;OCR1A--)
	{
		_delay_ms(2);
	}
}

void CloseWindows()
{
	//OCR1A = 2000;
	for(OCR1A=1000;OCR1A <= 2000;OCR1A++)
	{
		_delay_ms(2);
	}
}