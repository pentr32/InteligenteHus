/*
 * Keypad.h
 *
 * Created: 16-12-2019 13:54:45
 *  Author: robe1819
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

// Function proprieties.
void MaxtrixKeypad_Init();					//Funktion der initialiser Pull-up

int ColumnScan();							//Funktion der styre C1-C4 via 4 portbit.

int ReadRows();								//Funktion der læse R1-R4 og returner den specifik row.

void DecodeKeyboard();						//Funktion der decoder mine knapper på bestemt koloner og rækker.

#endif /* KEYPAD_H_ */