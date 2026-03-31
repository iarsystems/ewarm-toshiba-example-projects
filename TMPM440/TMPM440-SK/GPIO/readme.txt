########################################################################
#
#                           GPIO.eww
#
# $Revision: 2824 $
#
########################################################################

DESCRIPTION
===========
  This example project shows how to use the IAR Embedded Workbench for
  ARM to develop GPIO interface code for IAR TMPM440-SK board.

  It demonstrates basic use of on-board PSW and LED ports.

  Program supports both polling mode and interrupt mode interface.

COMPATIBILITY
=============
  By default the project is configured to use the I-Jet JTAG interface.

CONFIGURATION
=============
  Make sure the JP3 Endian setting is correct.
  Setup JP1 correctly to power up the board.

GETTING STARTED
===============
  1) Build and download the example.
  2) Run the program.
  3) Push PSW8-PSW1 to turn ON corresponding LED8-LED1.
     Switch =  PSW8 - PSW7 - PSW6 - PSW5 - PSW4 - PSW3 - PSW2 - PSW1
     LED    =  LED8 - LED7 - LED6 - LED5 - LED4 - LED3 - LED2 - LED1
