/*
 * Settings.h
 *
 * Created: 18-12-2019 17:42:05
 *  Author: robe1819
 */ 


#ifndef SETTINGS_H_
#define SETTINGS_H_

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


char button[COLUMN_MAX][ROW_MAX] = {{'1', '4', '7', '*'}, {'2', '5', '8', '0'}, {'3', '6', '9', '#'}, {'A', 'B', 'C', 'D'}};

// Motor settings
bool motor_Enabled = false;
int motor_delay = 0;
#define motor_button 'A'

// Ventilator settings
bool ventilator_Enabled = false;
int ventilator_delay = 0;
#define ventilator_button 'B'



#endif /* SETTINGS_H_ */