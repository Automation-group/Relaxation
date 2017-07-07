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
Sheet 2 2
Title ""
Date "21 nov 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 3450 4900
Wire Wire Line
	3450 4900 3750 4900
Wire Wire Line
	3750 4900 3750 5000
Wire Wire Line
	3750 5000 4100 5000
Wire Wire Line
	6150 5000 5250 5000
Wire Wire Line
	4100 5200 3550 5200
Wire Wire Line
	3550 5200 3550 5000
Wire Wire Line
	3550 5000 3350 5000
Wire Wire Line
	3450 5200 3450 4600
Wire Wire Line
	3450 5200 3350 5200
Wire Wire Line
	5250 5200 6150 5200
Wire Wire Line
	3450 4600 3350 4600
Wire Wire Line
	3350 4400 3650 4400
Wire Wire Line
	5250 5100 6150 5100
Wire Wire Line
	3650 4400 3650 5100
Wire Wire Line
	3650 5100 4100 5100
$Comp
L PIN_M_9 XP1
U 1 1 4ECA3F37
P 4100 5200
F 0 "XP1" H 4250 4150 50  0000 L BNN
F 1 "DB9M" H 4200 4250 50  0000 L BNN
F 2 "~" H 4550 5350 50  0001 C CNN
	1    4100 5200
	1    0    0    1   
$EndComp
$Comp
L PIN_F_9 XS1
U 1 1 4ECA3EEB
P 5250 5200
F 0 "XS1" H 5400 4150 50  0000 L BNN
F 1 "DB9F" H 5400 4250 50  0000 L BNN
F 2 "~" H 5700 5350 50  0001 C CNN
	1    5250 5200
	-1   0    0    1   
$EndComp
Text Notes 1750 5150 0    60   ~ 0
Верхний конечник
Text Notes 1750 4550 0    60   ~ 0
Нижний конечник
$Comp
L KMT-1 SB2
U 1 1 4ECA3DA2
P 3350 5000
F 0 "SB2" H 2800 5250 60  0000 C CNN
F 1 "KMT-1" H 2800 5150 60  0000 C CNN
	1    3350 5000
	1    0    0    -1  
$EndComp
$Comp
L KMT-1 SB1
U 1 1 4ECA3D8E
P 3350 4400
F 0 "SB1" H 2800 4650 60  0000 C CNN
F 1 "KMT-1" H 2800 4550 60  0000 C CNN
	1    3350 4400
	1    0    0    -1  
$EndComp
Text Notes 6650 5050 0    60   ~ 0
Земля
Text Notes 6650 5150 0    60   ~ 0
Нижний конечник
Text Notes 6650 5250 0    60   ~ 0
Верхний конечник
$Comp
L PIN_F_3 XS2
U 1 1 4ECA3BEE
P 6150 5200
F 0 "XS2" H 6300 4750 50  0000 L BNN
F 1 "WF-3" H 6250 4850 50  0000 L BNN
F 2 "~" H 6600 5350 50  0001 C CNN
	1    6150 5200
	1    0    0    1   
$EndComp
$EndSCHEMATC
