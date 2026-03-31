/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : ttbl.c
 *    Description : MMU Translation tables
 *
 *    History :
 *    1. Date        : March, 20 2008
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *        The physical memory map is:
 *
 *      0x00000000
 *                  |---------------------------|
 *      0x00001FFF  | Remap iROM, SRAM3, SMCCS0 |
 *                  |---------------------------|
 *      0x00002000  |          SMCCS0n          |
 *                  |         RW cached         |
 *      0x00003FFF  |---------------------------|
 *                  |       Unused Area         |
 *      0x1FFFFFFF  |                           |
 *                  |---------------------------|
 *      0x20000000  |          SMCCS0n          |
 *                  |       NOR Flash 32MB      |
 *      0x3FFFFFFF  |       Read only cached    |
 *                  |---------------------------|
 *      0x40000000  |          DMCCSn           |
 *                  |         SDRAM 64MB        |
 *      0x5FFFFFFF  |         RW cached         |
 *                  |---------------------------|
 *      0x60000000  |          SMCCS1n          |
 *                  |          Ethernet         |
 *                  |        RW Nocached        |
 *      0x7FFFFFFF  |---------------------------|
 *                  |                           |
 *                  ~                           ~
 *                  |                           |
 *                  |                           |
 *                  |---------------------------|
 *      0xF0000000  |      Built-in IO area     |
 *                  |        RW Nocached        |
 *                  |---------------------------|
 *      0xF8002000  |       Built-in RAM3       |
 *                  |       RW Nocached         |
 *                  |---------------------------|
 *      0xF8004000  |                           |
 *                  |     Built-in RAM area     |
 *                  |       RW Nocached        |
 *                  |---------------------------|
 *      0xF8004000  |                           |
 *                  |     Built-in RAM area     |
 *                  |                           |
 *      0xFFFFFFFF  |---------------------------|
 *
 *    $Revision: 41 $
 **************************************************************************/
#include "ttbl.h"

#pragma segment="MMU_TT"

#pragma location="MMU_TT"
#pragma data_alignment=16384
__no_init Int32U L1Table[L1_ENTRIES_NUMB];

#pragma location="MMU_TT"
#pragma data_alignment=2048
__no_init Int32U L2Coarses1[L2_CP_ENTRIES_NUMB];

const TtSectionBlock_t TtSB[] =
{
  // L1
  //   1 MB RW coarse table
  L1_COARSES_PAGE_ENTRY(  1,0x00000000,(Int32U)L2Coarses1   ,1    ),
  // 512 MB Rread only section cached
  L1_SECTIONS_ENTRY(    512,0x20000000,0x20000000           ,0,0,1,0),
  //  512 MB RW section cached
  L1_SECTIONS_ENTRY(    512,0x40000000,0x40000000           ,3,1,1,1),
  //  512 MB RW section no cached
  L1_SECTIONS_ENTRY(    512,0x60000000,0x60000000           ,3,1,0,0),
  //  128 MB RW section no cached full access in privilege mode only
  L1_SECTIONS_ENTRY(    128,0xF0000000,0xF0000000           ,2,1,0,0),
  //  64 MB RW section cached
  L1_SECTIONS_ENTRY(     64,0xF8000000,0xF8000000           ,3,1,1,1),
  //  64 MB RW section no cached
  L1_SECTIONS_ENTRY(     64,0xFC000000,0xFC000000           ,3,1,0,0),
  TSB_INVALID,
  // L2 coarse table 4 * 4kB = 16kB
  L2_CT_SMALL_PAGE_ENTRY(4 ,0x00000000,0x00000000           ,3,3,3,3,1,1),
  TSB_INVALID
};

const TtTableBlock_t TtTB[] =
{
  {L1Table,TableL1},
  {L2Coarses1,TableL2_Coarse},
  TTB_INVALID
};
