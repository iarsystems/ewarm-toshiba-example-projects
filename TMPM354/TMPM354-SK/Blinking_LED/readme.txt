########################################################################
#
#                           Blinking_LED.eww
#
# $Revision: 2543 $
#
########################################################################

DESCRIPTION
===========
   This example project shows how to use the
  IAR Embedded Workbench for ARM to develop code for Toshiba TMPM354
  family microcontrollers. It is developed for TMPM354-SK Board.
   It uses TIMER0 to toggle the LEDs on PORTA and PORTH.

COMPATIBILITY
=============
   The LED example project is compatible with TMPM354-SK
  board. By default the project is configured to use the J-Link SWD
  interface.

CONFIGURATION
=============
  Debug iFlash - The Progam is loaded to internal Flash.
  Debug iRAM - The Progam is loaded to internal SRAM.

 Jumpers:
  JP9 - filled
  JP14 - filled
  JP10,JP11,JP13 - depend of power source
  E_JP8 - E_JP15 (LEDs) - filled
  J3P6 - 2-3
  J3P7 - 1-2

GETTING STARTED
===============
  1) Power the board and connect the J-Link.
  2) Select a configuration.
  3) Build and download the example.
