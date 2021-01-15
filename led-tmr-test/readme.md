This project is intended to get the MPLAB H3 toolchain up and running. It just blinks an LED controlled by timer2/3 interrupts. 

It is based on https://github.com/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/wiki/Create-your-first-peripheral-library-(PLIB)-project

HW: Curiosity PIC32MZEF board.

Goal: Blink an LED and establish some familiarity with H3.

Steps:
	1) Install Mplab IDE/IPE, XC32, 'Harmony 3 Launcher' plugin for MPLAB
	2) Create new H3 project in MPLAB
		Chip is PIC32MZ2048EFM100
		Don't use underscore in configuration name or it won't build!
		https://stackoverflow.com/questions/38529540/what-causes-this-missing-whitespace-after-the-macro-name-error
	3) Setup Oscilator
		Tools -> Clock Configuration:
		Board has 24Mhz crystal but for this example just using the on board FRC oscilator
		Sysclk should be 200Mhz and FRC already
	4) Setup Timer 2/3
		Available Components -> Peripherals -> TMR -> TMR2,TMR3
		TMR2: Odd/Even form 32 bit timer
		TMR2: Timer Period (millisec) = 300
		TMR3: Enable interrupts		
	5) Pin Configuration
		RB0->RGB_B, RB1->RGB_G, RB5->RGB_R. RE3->LED_R, RE4->LEDG. They should be set as GPIO OUT.
	6) Save MHC and generate code
	7) Edit main.c
		Register T2 interrupt callback fn
		Handle T2 interrupt callback
		Toggle through RGB LED colors
	8) Make and program
		Using Pickit 4 as programmer but could use dev board PKOB
		Just had to plug in Pickit and restart MPLAB and Pickit was found (Manjaro)
		On dev board J2 all open (use external debugger) and J8 vin to use vbus of J12 as power
	9) Watch LED flash

Remarks:
	This task would be easier and more fun using register writes and a simpler non Harmony structure.
	As projects grow and you become more familar with it perhaps Harmony is worthwhile. It is not Harmonious.

	One of the things I find hardest with Harmony is finding good documentation. It is all over the
	place, hard to find and tedious to navigate.

	The csp examples seem pretty good. From https://github.com/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/wiki
	you can find docs with patience.
