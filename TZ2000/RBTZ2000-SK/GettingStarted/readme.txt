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
  to develop code for the Toshiba RBTZ2000-SK.
  It shows basic use of I/O, timers, GIC and some core initializations.
  The two onboard leds start to blink with different frequencies.
  At this stage the onboard certified SPI_Flash_ROM makes initializations to the system 
  (clock domains init, ddr init etc.).

COMPATIBILITY
=============
   The example project is compatible with Toshiba RBTZ2000-SK board.
  By default, the projects are configured to use the J-Link JTAG interface.

CONFIGURATIONS
===============

  SRAM Debug:

   This configuration is intended for debugging in the internal SRAM non-main memory.

   Set DSW1 to: on-off-off-off (boot from SPI)
   Set SW1 to:  position 2-3 and 5-6 (boot from SPI_Flash_ROM, CPU_CS0 wired to FLASH_CS1)
 
  DDR Debug:

   This configuration is intended for debugging in the external DDR3 main memory. 

   Set DSW1 to: on-off-off-off (boot from SPI)
   Set SW1 to:  position 2-3 and 5-6 (boot from SPI_Flash_ROM, CPU_CS0 wired to FLASH_CS1)

GETTING STARTED
===============

  1) Power-up the board and set JP2 to position 1-2 (non-reset state)

  2) Build and download the example.

  3) Run the program.
