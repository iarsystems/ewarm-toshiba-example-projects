########################################################################
#
#                           USB.eww
#
# $Revision: 2543 $
#
########################################################################

DESCRIPTION
===========
  This example project shows how to use IAR Embedded Workbench for ARM
  to develop code for the IAR-TMPM330-SK board. It demonstrates basic use of USB
  and the LCD display.

  It displays "Hello world!" via a USB cable which connects the board to a PC.

  We recommend that you first run example applications according to the
  QuickStart Guide, QSARMTMPM330.ENU.pdf, found on the TMPM330
  KickStart kit CD.

CONFIGURATION
=============
  Make sure that the jumpers are set as described in the QuickStart Guide.

  Connect the board to the PC using a USB cable.

  Use these communication settings:
      Bit rate    : 19,200 kbits/sec
      Data bit    : 8
      Parity      : none
      Stop bit    : 1
      Flow control: none

  Download the USB-UART bridge VCP driver from the following URL and install it on the PC.
    https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx

GETTING STARTED
===============
  1) Build and download the example.
  2) Run the program.
  3) Open a terminal window and set up the communications as above.
  4) Press the K1 key.
  5) "Hello world!" is displayed in the terminal window on the PC.
