########################################################################
#
#                           Blinking_LED.eww
#
# $Revision: 2543 $
#
########################################################################

DESCRIPTION
===========
   This example project shows how to use the IAR Embedded Workbench for
  ARM to develop code for Toshiba TMPM358 family microcontrollers. It is
  developed for TMPM358-SK Board.
   It uses TIMER0 to toggle the LEDs on PORTB.

COMPATIBILITY
=============
   The LED example project is compatible with TMPM358-SK
  board. By default the project is configured to use the J-Link SWD
  interface.

CONFIGURATION
=============
  Debug iFlash - The Progam is loaded to internal Flash.
  Debug iRAM - The Progam is loaded to internal SRAM.

 Jumpers:
  JP4,JP5,JP6,JP8 - depend of the power source
  SW1 (MODE0) - L
  SW2 (MODE1) - H

GETTING STARTED
===============
  1) Power the board and connect the debugger probe.
  2) Select configuration
  3) Build and download the example.
  4) Run the program.
  5) The LEDs on the board will start to blink.
