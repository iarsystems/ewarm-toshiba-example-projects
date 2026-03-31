########################################################################
#
#                           MassStorage.eww
#
# $Revision: 2543 $
#
########################################################################

DESCRIPTION
===========
   This example project shows how to use the IAR Embedded Workbench for ARM
  to develop code for Toshiba TMPM369 family microcontrollers. It is
  developed for IAR TMPM369-SK Eval Board.

  It implements a MMC/SD card drive.

  The first free drive letters will be used. For example, if your PC
  configuration includes two hard disk partitions (C:\ and D:\) and a CD-ROM
  drive (E:\), the memory card drive will appear as F:\.

  LED8 will indicate drive activity.

  The example handles Standard SD and SDHD cards, but not SDXC cards.

COMPATIBILITY
=============
  The MassStorage example project is compatible with IAR-TMPM369-SK board.
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
