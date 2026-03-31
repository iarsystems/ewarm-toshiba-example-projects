########################################################################
#
#                           RotaryEncoder.eww
#
# $Revision: 2824 $
#
########################################################################

DESCRIPTION
===========
  This example project shows how to use the IAR Embedded Workbench for
  ARM to develop Rotary Encoder interface code for IAR TMPM440-SK board.

  It demonstrates basic use of on-board rotary encoder and LEDs.
  Position of lit led on (LED8-LED1) display bar moved right if rotary
  pot is turned right. Display shifts to left if rotary pot is turned left.

COMPATIBILITY
=============
  By default the project is configured to use the I-Jet JTAG interface.

CONFIGURATION
=============
  Make sure the JP3 Endian setting is correct.
  Setup JP1 correctly to power up the board.
  Setup JP6 and JP7 to (1-2).

GETTING STARTED
===============
  1) Build and download the example.
  2) Run the program.
  3) Rotate rotary encoder pot to right and observe led display
     bar on LED8 - LED1.
     LED4 -> LED3 -> LED2 -> LED1 -> LED8 -> LED7 -> LED6 -> LED5 ->
  4) Rotate rotary encoder pot to left and observe led display
     bar on LED8 - LED1.
     <- LED3 <- LED2 <- LED1 <- LED8 <- LED7 <- LED6 <- LED5 <- LED4
