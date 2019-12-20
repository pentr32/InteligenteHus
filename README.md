
# Den Inteligente Hus

![enter image description here](https://i.imgur.com/V27wEM0.jpg)

Et software der kan styre forskellige ting f.eks. servomotor, DC motor ved hjælp af en 4x4 keypad. Ideen var at vise dig en demo, hvordan du kan gøre dit lokale hjem til et intelligent hus. 

# Kravspecifikation
- Programmet skal kunne styre måle temperatur i huset. (**Termometer**)
- Programmet skal kunne arbejder sammen keypad. (**4x4 Keypad**)
- Programmet skal kunne tænd eller slukke for blæseren (**DC-Motoren**)
- Hvis temperatur bliver for varmt så skal blæseren dreje hurtiger.
- Programmet skal kunne vise status på LCD.

# Ting som jeg har brugt

En AVR controller som hedder ATMega2560 som har:
- 54 digital input/output pins, hvor 14 af dem kan bruges til PWM (Pulse with modulation)
- SRAM: 8 KB
- EEPROM: 4 KB
- Flash Memory på 256 KB
- 
- ![enter image description here](https://i.imgur.com/0w2KneB.png)

En LCD display:
- Størrelse: 2x16
- Model: 1602

![enter image description here](https://i.imgur.com/cQVI2pS.jpg)

Som har:
 - VSS: Pin der går til 0 V (eller ground)
 - VDD: Pin der går til 5 V
 - VO: som styre konstranten på skærm
 - RS: En registre som kontroller hvor i LCDens hukommelse man skrive data.
 - R/W: Står for Read/Write mode
 - E: Står for enabling pin.
 - D0 - D7: Pin der læse og skrive data.
 - A - K: Pin der kontroller LEDens baglysen.


En  DC-Motor. Og til at styre DC-Motoren så har jeg brugt en PMIC motordrive og fordi DC-Motoren bruge rigtig meget strøm så skulle jeg sæt en breadboard PSU.

![enter image description here](https://i.imgur.com/hhbzaOh.jpg)

En termometer.

En 4x4 Keypad som har:
 - 4 Input pin (R1-R4)
 - 4 Output port (C1-C4)
 
 ![enter image description here](https://i.imgur.com/CEyCjmq.gif)
 
 ![enter image description here](https://i.imgur.com/rT1wfdz.png)
 I min situation har jeg lagt keypad til alle PORTK

| Output Port   |Arduino Port       
| ------------- |:-------------:|
| C1    | PK3 | 
| C2    | PK2 | 
| C3    | PK1 |
| C4    | PK0 |


| Input Port   |Arduino Port       
| ------------ |:-------------:|
| R1    | PK4 |
| R2    | PK5 |
| R3    | PK6 |
| R4    | PK7 |  

Den måde som jeg har programmeret min keypad'en det er at jeg sætter logik 1 på alle **Output port**så tjekker jeg hver koloner ved at sætter logik 0. F.eks. den første vi tjekker det er C1 så vi sætter 0 på den output der så tjekker vi hver rækker.

Ind i **Keypad.c** har jeg en multidimensional array til så jeg kan bedre ved på hvilken knap trykker jeg.

    char button[COLUMN_MAX][ROW_MAX] = {{'1', '4', '7', '*'}, {'2', '5', '8', '0'}, {'3', '6', '9', '#'}, {'A', 'B', 'C', 'D'}};

Her er der billeder af min **Logic Analyzer** til keypad'en.
![enter image description here](https://i.imgur.com/T5p90uy.png)

# Funktioner og filer
***Keypad.c***
> MatrixKeypad_Init();

Funktion der initialiser keypad'en og LCD'en.

> ColumnScan();

Funktion der styre C1-C4 via portbit.

> ReadRows();

Funktion der læse R1-R4 og returner den specifik row.

> DecodeKeyboard();

Funktion der decoder mine knapper på bestemt koloner og rækker og returner den specifik knap som jeg har trykket på vha. min multidimensional array.
> Menu();

Funktion der styre de forskellige enheder vha. keypad.
