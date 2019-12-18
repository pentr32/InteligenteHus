/*
 * Keypad.c
 *
 * Created: 16-12-2019 13:53:38
 *  Author: robe1819
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "Settings.h"
#include "Motor.h"
#include "Keypad.h"
#include "lcd.h"
#include "Ventilator.h"


// Funktion der initialiser Pull-up
void MaxtrixKeypad_Init()
{		
	lcd_init(LCD_DISP_ON_CURSOR);
	lcd_clrscr();
		
	DDRK |= (1<<C1) | (1<<C2) | (1<<C3) | (1<<C4);				// Output
	
	PORTK |= (1<<DDK4) | (1<<DDK5) | (1<<DDK6) | (1<<DDK7);		// Enable Pull-up
}

// Funktion der styre C1-C4 via portbit
int ColumnScan()
{	
	static int columnCount = 1;
	PORTK |= (1<<C1) | (1<<C2) | (1<<C3) | (1<<C4);				// Sætter bit til logik 1. dvs. man sætter 1 på alle koloner.
	
	switch(columnCount)
	{
		case 1:
			PORTK &= ~(1<<C1);									// Sætter bit logik 0. PK3
			columnCount++;
			_delay_ms(40);
			return 0;
		break;
		
		case 2:
			PORTK &= ~(1<<C2);									// Sætter bit logik 0. PK2
			columnCount++;
			_delay_ms(40);
			return 1;
		break;
		
		case 3:
			PORTK &= ~(1<<C3);									// Sætter bit logik 0. PK1
			columnCount++;
			_delay_ms(40);
			return 2;
		break;
		
		case 4:
			PORTK &= ~(1<<C4);									// Sætter bit logik 0. PK0
			columnCount = 1;
			_delay_ms(40);
			return 3;
		break;
	}
}

// Funktion der læse R1-R4 og returner den specifik row.
int ReadRows()
{		
	if(~PINK & (1<<R1))
	{
		_delay_ms(40); 
		if(~PINK & (1<<R1))
		{ 
			return 0;					// PK4
		}
		else
		{
			return -1;
		}
	}
	
	if(~PINK & (1<<R2))
	{
		_delay_ms(40); 
		if(~PINK & (1<<R2))
		{
			return 1;					// PK5
		}
		else
		{
			return -1;
		}
	}
	
	if(~PINK & (1<<R3))
	{
		_delay_ms(40); 
		if(~PINK & (1<<R3))
		{
			return 2;					// PK6
		}
		else
		{
			return -1;
		}
	}
	
	if(~PINK & (1<<R4)) 
	{
		_delay_ms(40); 
		if(~PINK & (1<<R4))
		{
			return 3;					// PK7
		}
		else
		{
			return -1;
		}
	}
}

// Funktion der decoder mine knapper på bestemt koloner og rækker.
char DecodeKeyboard()
{	
	int column = ColumnScan();
	int row = ReadRows();
	
	if(row != -1)
	{	
		//sprintf(buffer, "%c", button[column][row]); 
		//lcd_puts(buffer);
		
		return button[column][row];
	}
}

void Menu()
{
	char buffer[16];
	
	char input_Button = DecodeKeyboard();
	
	switch(input_Button)
	{
		case motor_button:
			
			//sprintf(buffer, "%c", 'T'); lcd_puts(buffer);
			
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
			
		break;
		
		case ventilator_button:
			ventilator_Enabled = !ventilator_Enabled;
			
		break;
	}
}