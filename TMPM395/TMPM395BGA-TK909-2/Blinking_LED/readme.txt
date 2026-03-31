########################################################################
#
#                           Blinking_LED.eww
#
# $Revision: 2543 $
#
########################################################################

DESCRIPTION
===========
   This example project shows how to use the IAR Embedded Workbench for ARM to
  develop code for Toshiba TMPM395 family microcontrollers. It is developed for
  Toshiba TMPM395BGA-TK909-2 Eval Board.

   It uses the WDT to toggle the port PJ0.

COMPATIBILITY
=============
   The LED example project is compatible with Toshiba TMPM395BGA-TK909-2
  board.
   By default the project is configured to use the J-Link JTAG interface.

CONFIGURATION
=============
  Please set correct SWO CPU clock (9MHz) in J-Link->SWO Settings...
  for correct operation of SWO features

  Jumpers:
    JP31 - Filled
    Connect J24.2 (PJ0) to J14.1

GETTING STARTED
===============
  1) Build and download the example.
  2) Run the program.
