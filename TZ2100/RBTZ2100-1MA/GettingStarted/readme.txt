########################################################################
#
#                           GettingStarted.eww
#
# $Revision: 379 $
#
########################################################################

DESCRIPTION
===========
  This example project shows how to use the IAR Embedded Workbench for ARM
  to develop code for the Toshiba RBTZ2000-1MA.
  It shows basic use of I/O, timers, GIC and some core initializations.
  TMR0 interrupt is used to display LED patterns at interval of 250ms.

COMPATIBILITY
=============
   The example project is compatible with Toshiba RBTZ2100-1MA board.
  By default, the projects are configured to use I-Jet JTAG interface.

CONFIGURATIONS
===============

  SRAM Debug:
  -------------
   This configuration is intended for debugging in the internal SRAM memory.

GETTING STARTED
===============

   1) Start the IAR Embedded Workbench for ARM.

   2) Select File->Open->Workspace...
      Open the following workspace:

      <installation-root>\arm\examples\Toshiba\
      TZ2100\RBTZ2100-1MA\GettingStarted\GettingStarted.eww

   3) Run the program.

NOTE
====

  I-cache is enabled in this sample.
  If you don't want to enable I-cache, please modify following file.
    $PROJ_DIR$\config\RBTZ2100SK_SRAM.mac



