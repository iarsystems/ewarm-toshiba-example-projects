##############################################################################
##                                                                          ##
##         UART I/F demonstartion sample program for TMPM380-SK Board       ##
##                                                                          ##
##############################################################################

DESCRIPTION
===========
  This example project shows how to use IAR Embedded Workbench for ARM
  to develop UART device interface code for TMPM380-SK board. 
  It demonstrates a basic use of UART and 7-Segment display.

  On TMPM380-SK Platform, UART is bridged to USB port using CP2102 bridge 
  controller. UART serial communication can be performed over the USB link
  interface. Sample program displays "Hello" string on serial console 
  connected via USB cable. Sample program also performs echo of characters
  received from serial console.

CONFIGURATION
=============
  Download the USB-UART bridge VCP driver from the following URL and 
  install it on the PC.
  https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx

  Connect the board to the PC using a USB cable.
  Once the TMPM380-SK platform is powered ON, you may need to setup
  the device driver of USB-UART bridge device.

  Open the serial console with the communication settings below: 
    Bit rate    : 57600 bits/sec
    Data bit    : 8
    Parity      : none
    Stop bit    : 1
    Flow control: none


GETTING STARTED
===============
  1) Build and download the example.
  2) Run the program.
  3) Open a terminal window and set up the communications as above.
  4) Choose appropriate configuration (FLASH or RAM) and start execution.
  5) The string below will be displayed on the terminal window on the PC.

     "Hello!! 
      This program is running with TMPM380"

  6) Enter the character data in terminal. Sample program will echo back 
     the character data on the terminal.
     The 7-Segment digit display will show the count of characters 
     echoed back to terminal.
