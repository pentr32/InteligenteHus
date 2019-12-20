/*
 * Ventilator.c
 *
 * Created: 18-12-2019 17:06:19
 *  Author: robe1819
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Ventilator.h"
#include "lcd.h"

// Ventilator settings
bool ventilator_Enabled = false;

float ADC_data;
float tempk;
unsigned int tempc;
float ADC_voltage;

uint8_t r;
uint8_t g;
uint8_t b;

// Funktion der initialiser DC-Motoren.
void Ventilator_Init()
{	
	ADMUX = (1 << REFS0);	// 5V supply used for ADC reference, select ADC channel 0, datasheet 28.9.1
	DIDR0 = (1 << ADC0D);	// disable digital input on ADC0 pin, datasheet 28.9.6
	// enable ADC, start ADC, ADC clock = 16MHz / 128 = 125kHz, datasheet 28.9.2
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1)| (1<<COM1C1);
	//Waveform Generation Mode: Mode 5 Fast PWM: WGM10 = 1, WGM12 = 1 (Table 16-8)
	TCCR1A |= (1<<WGM10);
	// Clock Select Bit: clk/64 prescaling: CS = 011 : CS01 = 1, CS00 = 1 (Table 16-9), frekv. = 980Hz
	TCCR1B |= (1<<CS11) | (1<<CS10);		// datasheet 16.9.2
	// Set output to OC0A = PB7, see datasheet 16.9.4 and Arduino MEGA pin configuration: (pin 13), same as LED
	DDRB |= (1<<PB7) | (1<<PB6) | (1<<PB5);
}

// Funktion der tjekker temperaturen.
void Check_Temperatur()
{
	if (!(ADCSRA & (1 << ADSC)))
	{												// Tjekker ADC
		ADC_data = log(10000.0 * (1024.0/ADC -1));
		tempk = 1/(0.001129148+(0.000234125+(0.0000000876741*ADC_data*ADC_data))*ADC_data);

		tempc = tempk-273.15;

		ADCSRA |= (1 << ADSC);						// Begynd på den næste ADC
		_delay_ms(100);
		
		if(ventilator_Enabled)
		{
			if(tempc > 30)
			{
				OCR1A = 255;	// DC-Motor
				OCR1B = 0;		// R
				OCR1C = 255;	// G
			}
			if(tempc < 30)
			{
				OCR1A = 100;	// DC-Motor
				OCR1B = 255;	// R
				OCR1C = 0;		// G
			}
		}
	}
}

// Funktion der tænder/slukke DC-Motoren.
void Toggle_Ventilator()
{
	ventilator_Enabled = !ventilator_Enabled;
	if(ventilator_Enabled)
	{
		lcd_clrscr();
		lcd_puts("Ventilator ON");
	}
	
	if(!ventilator_Enabled)
	{
		OCR1A = 0;
		OCR1B = 0;
		OCR1C = 0;
		
		lcd_clrscr();
		lcd_puts("Ventilator OFF");
	}
}