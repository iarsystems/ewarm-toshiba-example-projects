########################################################################
#
#                           GettingStarted.eww
#
# $Revision: 2543 $
#
########################################################################

DESCRIPTION
===========
   This example project shows how to use the IAR Embedded Workbench for ARM
  to develop code for IAR-TMPA910-SK board. It shows
  basic use of I/O, timer and the interrupt controllers.
   It starts by togging LED1 (PB0).

COMPATIBILITY
=============
   The Getting started example project is compatible with IAR-TMPA910-SK
  board.
   By default the project is configured to use the J-Link JTAG interface.

CONFIGURATION
=============
   Make sure that the following jumpers are correctly configured on the
  IAR-TMPA910-SK board:

  Jumpers:
     JP2  - 2-3 (1) Boot Select
     JP3  - 1-2 (0) Boot Select
     JP4  - 1-2     SN0
     JP5  - 2-3     SN1
     JP6  - 1-2     SN2
     JP11 - filled  +1.8V
     JP13 - filled  +1.5V
     JP14 - filled  +3.3V
     JP20 - filled

GETTING STARTED
===============
  1) Build and download the example.
  2) Run the program.
