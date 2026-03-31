/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2009
 *
 *    File name   : dm9000_iar_tmpa910.c
 *    Description : DM9000A device driver x 16 bits
 *
 *    History :
 *    1. Date        : 1.9.2009
 *       Author      : Stanimir Bonev
 *       Description : initial revision.
 *
 *    $Revision: 41 $
 **************************************************************************/
#include "netif/dm9000_iar_tmpa910.h"

#define _MPMC_PERIOD          10.42      // 10.42 ns 96MHz
#define _1_MC_SEC_DLY         30

#define _P2C(Period)          (((Period<_MPMC_PERIOD)?0:(Int32U)((Flo32)Period/_MPMC_PERIOD))+1)

#define DM9000_TRC            80
#define DM9000_TWC            80
#define DM9000_TPC            10
#define DM9000_TWP            10
#define DM9000_TTR            60
#define DM9000_TCEOE          60

void DM9000A_init_16bit(void)
{
union
{
  Int32U Data;
  __smc_sram_cycles0_bits BitMap;
} smc_set_cycles;

union
{
  Int32U Data;
  __smc_set_opmode_bits BitMap;
} smc_opmode;

  // Init MPMC static memory controller
  smc_set_cycles.Data = 0;
  smc_set_cycles.BitMap.t_rc     = _P2C(DM9000_TRC);
  smc_set_cycles.BitMap.t_wc     = _P2C(DM9000_TWC);
  smc_set_cycles.BitMap.t_ceoe   = _P2C(DM9000_TCEOE);
  smc_set_cycles.BitMap.t_wp     = _P2C(DM9000_TWP);
  smc_set_cycles.BitMap.t_pc     = _P2C(DM9000_TPC);
  smc_set_cycles.BitMap.t_tr     = _P2C(DM9000_TTR);
  smc_set_cycles_3 = smc_set_cycles.Data;

  smc_opmode.Data = 0;
  smc_opmode.BitMap.set_mw            =  2;     // 32 bit
  smc_opmode.BitMap.set_rd_sync       =  0;     // asynchronous read operation
  smc_opmode.BitMap.set_rd_bl         =  0;     // 1 beats
  smc_opmode.BitMap.set_wr_sync       =  0;     // asynchronous write operation
  smc_opmode.BitMap.set_burst_align   =  0;     // Boundary of an arbitrary address can be crossed
  smc_opmode.BitMap.set_adv           =  0;     // Enable Address valid signal
  smc_set_opmode_3 = smc_opmode.Data;

  smc_direct_cmd_3 = (1UL << 23) | (2UL << 21); // UpdateRegs command
}


void DM9000A_reg_write(Int16U addr, Int16U data)
{
  // Set index reg
  iowr(DM9000A_CS_CMD_BASE_ADDR,addr);
  // wtite to data reg
  iowr(DM9000A_CS_DAT_BASE_ADDR,data);
}

Int16U DM9000A_reg_read(Int16U addr)
{
  // Set index reg
  iowr(DM9000A_CS_CMD_BASE_ADDR,addr);
  // read from data reg
  return(iord(DM9000A_CS_DAT_BASE_ADDR));
}

Int16U DM9000A_phy_reg_read(Int16U addr)
{
Int16U tmp;
  // Set Phy reg address
  DM9000A_reg_write(DM9000_EPAR,(addr & 0x3F) | 0x40);
  // Write command
  DM9000A_reg_write(DM9000_EPCR,EPCR_ERPRR | EPCR_EPOS);
  // wait until command done
  do
  {
    tmp = DM9000A_reg_read(DM9000_EPCR);
  }
  while(tmp & EPCR_ERRE);
  // clear read command
  DM9000A_reg_write(DM9000_EPCR,EPCR_EPOS);
  // read data
  tmp = DM9000A_reg_read(DM9000_EPDRH) << 8;
  tmp|= DM9000A_reg_read(DM9000_EPDRL);
  return(tmp);
}

void DM9000A_phy_reg_write(Int16U addr, Int16U data)
{
Int16U tmp;
  // Set Phy reg address
  DM9000A_reg_write(DM9000_EPAR,(addr & 0x3F) | 0x40);
  // load data
  DM9000A_reg_write(DM9000_EPDRH,data >> 8);
  DM9000A_reg_write(DM9000_EPDRL,data);
  // Write command
  DM9000A_reg_write(DM9000_EPCR,EPCR_ERPRW | EPCR_EPOS);
  // wait until command done
  do
  {
    tmp = DM9000A_reg_read(DM9000_EPCR);
  }
  while(tmp & EPCR_ERRE);
  // clear read command
  DM9000A_reg_write(DM9000_EPCR,EPCR_EPOS);
}

Int16U DM9000A_ee_reg_read(Int16U addr)
{
Int16U tmp;
  // Set Phy reg address
  DM9000A_reg_write(DM9000_EPAR,addr & 0x3F);
  // Write command
  DM9000A_reg_write(DM9000_EPCR,EPCR_ERPRR);
  // wait until command done
  do
  {
    tmp = DM9000A_reg_read(DM9000_EPCR);
  }
  while(tmp & EPCR_ERRE);
  // clear read command
  DM9000A_reg_write(DM9000_EPCR,0);
  // read data
  tmp = DM9000A_reg_read(DM9000_EPDRH) << 8;
  tmp|= DM9000A_reg_read(DM9000_EPDRL);
  return(tmp);
}

void DM9000A_ee_reg_write(Int16U addr, Int16U data)
{
Int16U tmp;
  // Set Phy reg address
  DM9000A_reg_write(DM9000_EPAR,addr & 0x3F);
  // load data
  DM9000A_reg_write(DM9000_EPDRH,data >> 8);
  DM9000A_reg_write(DM9000_EPDRL,data);
  // Write command
  DM9000A_reg_write(DM9000_EPCR,EPCR_ERPRW);
  // wait until command done
  do
  {
    tmp = DM9000A_reg_read(DM9000_EPCR);
  }
  while(tmp & EPCR_ERRE);
  // clear read command
  DM9000A_reg_write(DM9000_EPCR,0);
}

void DM9000A_ee_reload(void)
{
Int16U tmp;
  // Write command
  DM9000A_reg_write(DM9000_EPCR,EPCR_REEP);
  // wait until command done
  do
  {
    tmp = DM9000A_reg_read(DM9000_EPCR);
  }
  while(tmp & EPCR_ERRE);
  // clear read command
  DM9000A_reg_write(DM9000_EPCR,0);
}
