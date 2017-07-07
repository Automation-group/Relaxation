EESchema Schematic File Version 2  date Mon 21 Nov 2011 16:09:23 MSK
LIBS:LFcapitors
LIBS:LFcomponents
LIBS:LFconnectors
LIBS:LFdiod
LIBS:LFresistor
LIBS:LFtransformator
LIBS:LFbutton
EELAYER 24  0
EELAYER END
$Descr A4 8283 11700
Sheet 1 2
Title ""
Date "21 nov 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S -1050 5750 500  650 
U 4ECA3BA0
F0 "ovtSwitches" 60
F1 "ovtSwitches.sch" 60
$EndSheet
Wire Wire Line
	2450 2950 2050 2950
Wire Wire Line
	2050 2750 2450 2750
Wire Wire Line
	5400 4900 5700 4900
Wire Wire Line
	5400 4150 5700 4150
Connection ~ 6100 5850
Wire Wire Line
	6300 5850 6100 5850
Wire Wire Line
	6100 5850 5750 5850
Wire Wire Line
	6100 5400 6100 5100
Wire Wire Line
	5750 4550 6300 4550
Wire Wire Line
	6300 4450 6050 4450
Wire Wire Line
	6050 4450 5750 4450
Wire Wire Line
	6300 4350 6050 4350
Wire Wire Line
	6050 4350 5750 4350
Wire Wire Line
	6100 2500 6100 2200
Wire Wire Line
	6300 2950 6100 2950
Wire Wire Line
	6100 2950 5750 2950
Wire Wire Line
	6300 3550 5750 3550
Wire Wire Line
	6300 3350 5750 3350
Wire Wire Line
	6300 3450 6200 3450
Connection ~ 2150 5050
Wire Wire Line
	2150 5050 2150 4950
Wire Wire Line
	2150 4950 2050 4950
Wire Wire Line
	2450 4300 2050 4300
Wire Wire Line
	2450 4200 2050 4200
Wire Wire Line
	2450 4100 2050 4100
Wire Wire Line
	2050 5050 2150 5050
Wire Wire Line
	2150 5050 2450 5050
Wire Wire Line
	2450 4850 2050 4850
Wire Wire Line
	6200 3250 6200 3450
Wire Wire Line
	6200 3450 6200 3650
Wire Wire Line
	6200 3650 6300 3650
Connection ~ 6200 3450
Wire Wire Line
	6300 3150 5750 3150
Wire Wire Line
	6300 3050 5750 3050
Wire Wire Line
	6100 2750 6100 2950
Connection ~ 6100 2950
Wire Wire Line
	5750 3250 6200 3250
Wire Wire Line
	6200 3250 6300 3250
Connection ~ 6200 3250
Wire Wire Line
	6100 5650 6100 5850
Wire Wire Line
	6300 5950 5750 5950
Wire Wire Line
	2450 4000 2050 4000
Wire Wire Line
	5950 4150 6050 4150
Wire Wire Line
	6050 4150 6050 4350
Connection ~ 6050 4350
Wire Wire Line
	6050 4450 6050 4900
Connection ~ 6050 4450
Wire Wire Line
	6050 4900 5950 4900
Wire Wire Line
	2450 2850 2050 2850
$Comp
L RESISTOR R7
U 1 1 4EB926F1
P 5700 4900
F 0 "R7" H 5825 5150 71  0000 C CNN
F 1 "1 k" H 5825 5025 71  0000 C CNN
	1    5700 4900
	1    0    0    -1  
$EndComp
Text Label 5400 4900 0    60   ~ 0
+5V
Text Label 5400 4150 0    60   ~ 0
+5V
$Comp
L RESISTOR R6
U 1 1 4EB926BC
P 5700 4150
F 0 "R6" H 5825 4400 71  0000 C CNN
F 1 "1 k" H 5825 4275 71  0000 C CNN
	1    5700 4150
	1    0    0    -1  
$EndComp
Text Label 2450 4000 2    60   ~ 0
PC2
Text Notes 6750 5900 0    60   ~ 0
К ТЕНЗОУСИЛИТЕЛЮ
Text Label 5750 5950 0    60   ~ 0
GND
Text Label 5750 5850 0    60   ~ 0
PC2
$Comp
L RESISTOR R8
U 1 1 4EB91A23
P 6100 5650
F 0 "R8" V 6250 5850 71  0000 C CNN
F 1 "1 k" V 6150 5850 71  0000 C CNN
	1    6100 5650
	0    -1   -1   0   
$EndComp
Text Label 6100 5100 3    60   ~ 0
+5V
Text Notes 6750 4500 0    60   ~ 0
НИЖНИЙ КОН. ВЫКЛ
Text Notes 6750 4400 0    60   ~ 0
ВЕРХНИЙ КОН. ВЫКЛ
Text Notes 6750 3600 0    60   ~ 0
PUL
Text Notes 6750 3400 0    60   ~ 0
DIR
Text Notes 6750 3200 0    60   ~ 0
ENA
Text Notes 6750 3000 0    60   ~ 0
FAULT
Text Label 5750 4350 0    60   ~ 0
PC4
Text Label 5750 4450 0    60   ~ 0
PC5
Text Label 5750 4550 0    60   ~ 0
GND
Text Label 5750 3250 0    60   ~ 0
+5V
Text Label 6100 2200 3    60   ~ 0
+5V
$Comp
L RESISTOR R5
U 1 1 4EB91787
P 6100 2750
F 0 "R5" V 6250 2950 71  0000 C CNN
F 1 "1 k" V 6150 2950 71  0000 C CNN
	1    6100 2750
	0    -1   -1   0   
$EndComp
Text Label 5750 2950 0    60   ~ 0
PC3
Text Label 5750 3050 0    60   ~ 0
GND
Text Label 5750 3150 0    60   ~ 0
PB2
Text Label 5750 3350 0    60   ~ 0
PB1
Text Label 5750 3550 0    60   ~ 0
PB0
Text Label 2450 4850 2    60   ~ 0
+5V
Text Label 2450 5050 2    60   ~ 0
GND
Text Label 2450 4100 2    60   ~ 0
PC3
Text Label 2450 4200 2    60   ~ 0
PC4
Text Label 2450 4300 2    60   ~ 0
PC5
Text Label 2450 2950 2    60   ~ 0
PB2
Text Label 2450 2850 2    60   ~ 0
PB1
Text Label 2450 2750 2    60   ~ 0
PB0
$Comp
L PIN_M_10 XP4
U 1 1 4EB9138E
P 6300 2750
F 0 "XP4" H 6450 2950 50  0000 L BNN
F 1 "IDC-10MS" H 6350 2850 50  0000 L BNN
F 2 "~" H 6750 2900 50  0001 C CNN
	1    6300 2750
	1    0    0    -1  
$EndComp
$Comp
L PIN_M_6 XP?
U 1 1 4EB91376
P 2050 3800
AR Path="/4EB912B4" Ref="XP?"  Part="1" 
AR Path="/4EB91376" Ref="XP2"  Part="1" 
F 0 "XP2" H 2200 4000 50  0000 L BNN
F 1 "PBS-6" H 2100 3900 50  0000 L BNN
F 2 "~" H 2500 3950 50  0001 C CNN
	1    2050 3800
	-1   0    0    -1  
$EndComp
$Comp
L PIN_M_8 XP?
U 1 1 4EB91375
P 2050 3450
AR Path="/4EB912BA" Ref="XP?"  Part="1" 
AR Path="/4EB91375" Ref="XP1"  Part="1" 
F 0 "XP1" H 2250 2500 50  0000 L BNN
F 1 "PBS-8" H 2150 2600 50  0000 L BNN
F 2 "~" H 2500 3600 50  0001 C CNN
	1    2050 3450
	-1   0    0    1   
$EndComp
$Comp
L PIN_M_3 XP5
U 1 1 4EB912E2
P 6300 4350
F 0 "XP5" H 6450 4550 50  0000 L BNN
F 1 "WF-3" H 6400 4450 50  0000 L BNN
F 2 "~" H 6750 4500 50  0001 C CNN
	1    6300 4350
	1    0    0    -1  
$EndComp
$Comp
L PIN_M_2 XP6
U 1 1 4EB912DA
P 6300 5850
F 0 "XP6" H 6450 6050 50  0000 L BNN
F 1 "WF-2" H 6400 5950 50  0000 L BNN
F 2 "~" H 6750 6000 50  0001 C CNN
	1    6300 5850
	1    0    0    -1  
$EndComp
$Comp
L PIN_M_6 XP3
U 1 1 4EB912B4
P 2050 4650
F 0 "XP3" H 2200 4850 50  0000 L BNN
F 1 "PBS-6" H 2100 4750 50  0000 L BNN
F 2 "~" H 2500 4800 50  0001 C CNN
	1    2050 4650
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
