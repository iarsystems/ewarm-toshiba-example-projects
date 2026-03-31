########################################################################
#
#                           lwIP_webserver.eww
#
# $Revision: 2543 $
#
########################################################################

DESCRIPTION
===========
   This example application demonstrates the operation of the IAR-TMPA910-SK
  and DM9000A Ethernet controller using the lwIP TCP/IP Stack. The project can be
  configured to use Static IP or DHCP. The address that is selected will be shown
  on the IO windows.

COMPATIBILITY
=============
   The WEB serever example project is compatible with IAR-TMPA910-SK
  evaluation board.
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
