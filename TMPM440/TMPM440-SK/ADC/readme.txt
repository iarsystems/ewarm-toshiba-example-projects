########################################################################
#
#                           ADC.eww
#
# $Revision: 2824 $
#
########################################################################

DESCRIPTION
===========
  This example project shows how to use the IAR Embedded Workbench for
  ARM to develop ADC interface code for IAR TMPM440-SK board.

  It demonstrates basic use of on-board variable resistors VR1 and VR2.
  VR1 pot position is indicated on (LED8-LED7-LED6-LED5) display bar.
  VR2 pot position is indicated on (LED4-LED3-LED2-LED1) display bar.

COMPATIBILITY
=============
  By default the project is configured to use the I-Jet JTAG interface.

CONFIGURATION
=============
  Make sure the JP3 Endian setting is correct.
  Setup JP1 correctly to power up the board.

GETTING STARTED
===============
  1) Build and download the example.
  2) Run the program.
  3) Change VR1 pot position from low to high and observe led display
     bar on LED8 - LED5.
     VR1 pot position =  0% --> 20% --> 40% --> 60% --> 80% --> 100%
     led display = All OFF ++ LED8 +++ LED7 ++ LED6 ++ LED5
  4) Change VR2 pot position from low to high and observe led display
     bar on LED4 - LED1.
     VR2 pot position =  0% --> 20% --> 40% --> 60% --> 80% --> 100%
     led display =    All OFF ++ LED4 +++ LED3 ++ LED2 ++ LED1
