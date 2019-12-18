/*
 * Keypad.c
 *
 * Created: 16-12-2019 13:53:38
 *  Author: robe1819
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>
#include "Keypad.h"
#include "lcd.h"

#pragma region Defines

// Output Port
#define C1 PK3	// Channel 0
#define C2 PK2	// Channel 1
#define C3 PK1	// Channel 2
#define C4 PK0	// Channel 3

// Input Pin
#define R1 PK4
#define R2 PK5
#define R3 PK6
#define R4 PK7

// Column, Row Max antal
#define COLUMN_MAX 4
#define ROW_MAX 4
#pragma endregion

#pragma region Global variables

char button[COLUMN_MAX][ROW_MAX] = {{'1', '4', '7', '*'}, {'2', '5', '8', '0'}, {'3', '6', '9', '#'}, {'A', 'B', 'C', 'D'}};
	
#pragma endregion

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
		_delay_ms(10); 
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
		_delay_ms(10); 
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
		_delay_ms(10); 
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
		_delay_ms(10); 
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
void DecodeKeyboard()
{	
	int column = ColumnScan();
	int row = ReadRows();
	char buffer[16];
	
	if(row != -1)
	{	
		sprintf(buffer, "%c", button[column][row]); 
		lcd_puts(buffer);
	}
}