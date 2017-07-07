EESchema Schematic File Version 2  date Thu 17 Nov 2011 17:37:43 MSK
LIBS:conn
LIBS:power
LIBS:shema_3-cache
EELAYER 23  0
EELAYER END
$Descr A4 8283 11700
Sheet 1 1
Title ""
Date "17 nov 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 5950 3250
Wire Wire Line
	6200 3250 5950 3250
Connection ~ 5950 3850
Wire Wire Line
	5950 4300 5950 3850
Wire Wire Line
	5950 3850 5950 3650
Wire Wire Line
	5950 4300 4850 4300
Wire Wire Line
	4850 4650 4850 4750
Wire Wire Line
	4850 3350 5400 3350
Wire Wire Line
	5400 3350 5400 4050
Wire Wire Line
	5400 4050 6200 4050
Wire Wire Line
	5950 3650 6200 3650
Wire Wire Line
	4850 2800 5950 2800
Wire Wire Line
	4850 3750 5700 3750
Wire Wire Line
	5700 3750 5700 3350
Wire Wire Line
	5700 3350 6200 3350
Wire Wire Line
	6200 3450 5950 3450
Wire Wire Line
	6200 3950 6100 3950
Wire Wire Line
	6100 3950 6100 4700
Wire Wire Line
	6100 4700 4850 4700
Wire Wire Line
	6200 3850 5950 3850
Wire Wire Line
	5950 3450 5950 3250
Wire Wire Line
	5950 3250 5950 2800
Text Notes 4900 4650 0    60   ~ 0
экран
Text Notes 4900 4250 0    60   ~ 0
белый
Text Notes 4900 3700 0    60   ~ 0
синий
Text Notes 4900 3300 0    60   ~ 0
зелёный
Text Notes 4900 2750 0    60   ~ 0
красный
$Comp
L LPC2500 ~
U 1 1 48970433
P 3150 3550
F 0 "~" H 3150 4150 60  0000 C CNN
F 1 "LPC2500" H 3750 3650 60  0000 C CNN
	1    3150 3550
	1    0    0    -1  
$EndComp
Text Notes 3300 5950 0    100  ~ 0
Схема электрическая принципиальная
Text Notes 3300 5650 0    120  ~ 0
и присоединительным разъемом
Text Notes 2950 5400 0    120  ~ 0
Датчик силы LPC2500/LPC3A с кабелем
$Comp
L DB9 XP1
U 1 1 4896F8F5
P 6650 3650
F 0 "XP1" H 6550 2950 70  0000 C CNN
F 1 "DB9М" H 6550 3050 70  0000 C CNN
	1    6650 3650
	1    0    0    1   
$EndComp
$EndSCHEMATC
