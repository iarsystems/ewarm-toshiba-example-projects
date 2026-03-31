########################################################################
#
#                           USBMouse.eww
#
# $Revision: 2543 $
#
########################################################################

DESCRIPTION
===========
   This example project shows how to use the IAR Embedded Workbench for ARM
  to develop code for Toshiba TMPM369 family of microcontrollers. It is
  developed for IAR-TMPM369-SK Eval Board.

  It implements an USB HID mouse.

COMPATIBILITY
=============
  The USBMouse example project is compatible with IAR-TMPM369-SK board.
  By default the project is configured to use the J-Link SWD interface.

  If IAR-TMPM369-SK Rev.A board is used then the following line should
  be uncommented in the board.h file:

  #define REV_A_BOARD

CONFIGURATION
=============
  JP1 - Opened
  JP2 - Closed

  iRAM - The Progam is loaded to internal RAM.
  iFlash - The Progam is loaded to internal Flash.

GETTING STARTED
===============
  1) Build and download the program.
  2) Run the program.
