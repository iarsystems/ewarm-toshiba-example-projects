##############################################################################
##                                                                          ##
##         CAN Driver and Sample program for TMPM364 device                 ##
##                                                                          ##
##############################################################################

DESCRIPTION
===========
  This document describes the outline of CAN Driver and Sample program for 
  Toshiba TMPM364 device.

  This program will send the User SW button status data on CAN Bus.
  CAN receiver program will read the User SW button status and reflect
  the status on the LED port.

GETTING STARTED
===============
  1) Build and download the example.
  2) Run the program.
  3) Upper 4 leds will glow continuously.
  4) Press any one or more of the User SW buttons. LEDs will reflect the
     button status in runtime.

UPDATE HISTORY
==============

    [2011/09/17]:   Corrected bug in handling message of size > 4 bytes
    ------------------------------------------------------------------------
    [2011/03/15]:   first release (Provisional)
    ------------------------------------------------------------------------
