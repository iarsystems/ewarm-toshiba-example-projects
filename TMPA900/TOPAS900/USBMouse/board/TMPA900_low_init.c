/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : TMPA900_low_init.c
 *    Description : Low level init
 *
 *    History :
 *    1. Date        : 20, March 2008
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 41 $
 **************************************************************************/
#include <intrinsics.h>
#include <assert.h>
#include "TMPA900_low_init.h"
#include "board.h"

#define _MPMC_PERIOD          10.42      // 10.42 ns 96MHz
#define _1_MC_SEC_DLY         30

#define _P2C(Period)          (((Period<_MPMC_PERIOD)?0:(Int32U)((Flo32)Period/_MPMC_PERIOD))+1)

#define SDRAM_REFRESH         7812
#define SDRAM_TRP             18
#define SDRAM_TRAS            42
#define SDRAM_TAPR            1
#define SDRAM_TWR             2
#define SDRAM_TRC             60
#define SDRAM_TRFC            60
#define SDRAM_TXSR            67
#define SDRAM_TRRD            12
#define SDRAM_TMRD            2
#define SDRAM_TRCD            18

#define NOR_FLASH_TRC         110
#define NOR_FLASH_TWC         110
#define NOR_FLASH_TPC         30
#define NOR_FLASH_TWP         35
#define NOR_FLASH_TTR         35
#define NOR_FLASH_TCEOE       0

#ifdef SDRAM_INIT
/*************************************************************************
 * Function Name: Dly_us
 * Parameters: Int32U Dly [us]
 *
 * Return: none
 *
 * Description:
 *
 *************************************************************************/
static void Dly_us (Int32U Dly)
{
  while(Dly--)
  {
    for(volatile Int32U i = _1_MC_SEC_DLY; i; i--);
  }
}
#endif // SDRAM_INIT

/*************************************************************************
 * Function Name: low_level_init
 * Parameters: none
 *
 * Return: none
 *
 * Description: This function is used for low level initialization
 *
 *************************************************************************/
int __low_level_init(void)
{
int i;
volatile unsigned long * pVecAdd, *pVecCntl;

  // Init clocks
  if(SYSCR5_bit.PROTECT)
  {
    // System registers unlock
    SYSCR6 = 0x5A;
    SYSCR7 = 0xA5;
    SYSCR6 = 0xA5;
    SYSCR7 = 0x5A;
  }
  // switch to main OSC
  SYSCR2_bit.FCSEL = 0;

#ifdef NOR_INIT
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
  smc_set_cycles.BitMap.t_rc     = _P2C(NOR_FLASH_TRC);
  smc_set_cycles.BitMap.t_wc     = _P2C(NOR_FLASH_TWC);
  smc_set_cycles.BitMap.t_ceoe   = _P2C(NOR_FLASH_TCEOE);
  smc_set_cycles.BitMap.t_wp     = _P2C(NOR_FLASH_TWP);
  smc_set_cycles.BitMap.t_pc     = _P2C(NOR_FLASH_TPC);
  smc_set_cycles.BitMap.t_tr     = _P2C(NOR_FLASH_TTR);
  smc_set_cycles_3 = smc_set_cycles.Data;

  smc_opmode.Data = 0;
  smc_opmode.BitMap.set_mw            =  1;     // 16 bit
  smc_opmode.BitMap.set_rd_sync       =  0;     // asynchronous read operation
  smc_opmode.BitMap.set_rd_bl         =  0;     // 1 beats
  smc_opmode.BitMap.set_wr_sync       =  0;     // asynchronous write operation
  smc_opmode.BitMap.set_burst_align   =  0;     // Boundary of an arbitrary address can be crossed
  smc_opmode.BitMap.set_adv           =  1;     // Enable Address valid signal
  smc_set_opmode_3 = smc_opmode.Data;

  // update data into SMC for CS0
  smc_direct_cmd_3 = 2UL << 21; // UpdateRegs command
#endif // NOR_INIT

  // Set clock gear divider /1
  SYSCR1_bit.GEAR = 0;
  // Set MPMC SRAM/ROM Clock = FCLK/2
  CLKCR5_bit.SEL_SMC_MCLK = 1;
  // Timer0/1s' clock connect to FCLK/2
  CLKCR5_bit.SEL_TIM01 = 1;
  // Timer2/3s' clock connect to FCLK/2
  CLKCR5_bit.SEL_TIM23 = 1;
  // Timer4/5s' clock connect to FCLK/2
  CLKCR5_bit.SEL_TIM45 = 1;
  // Init PLL
  SYSCR3_bit.ND = 7;      // *8
  // enable PLL
  SYSCR3_bit.PLLON = 1;
  // Wait until PLL lock frequency
  while(0 == SYSCR2_bit.LUPFLAG);
  // switch to clock from the PLL
  SYSCR2_bit.FCSEL = 1;
  // System registers lock
  SYSCR6 = 0x5A;
  SYSCR7 = 0xA5;
  SYSCR6 = 0xA5;
  SYSCR7 = 0x5A;

#ifdef SDRAM_INIT
  PMCDRV_bit.DRV_MEM1 = 0;
  PMCDRV_bit.DRV_MEM0 = 1;
  
  // Init MPMC0 (dynamic SDR memory controller)
  if(1 == dmc_memc_status_3_bit.memc_status)
  {
    dmc_memc_cmd_3 = 3;                         // pause
    while(2 != dmc_memc_status_3_bit.memc_status);
  }
  dmc_memc_cmd_3 = 4;                         // Configure
  dmc_user_config_3 = 1;                      // 32 bits bus

  dmc_cas_latency_3_bit.cas_latency = 3;      // CAS
  dmc_t_dqss_3_bit.t_dqss = 0;                // DQS setting for SDRAM memories must be 0
  dmc_t_mrd_3_bit.t_mrd = SDRAM_TMRD;         // Mode register command time
  dmc_t_ras_3_bit.t_ras = _P2C(SDRAM_TRAS);   // Time between RAS and Precharge
  dmc_t_rc_3_bit.t_rc = _P2C(SDRAM_TRC);      // Time between RAS and Precharge
  dmc_t_rcd_3_bit.t_rcd = _P2C(SDRAM_TRCD);   // Set min delay from RAS to CAS
  dmc_t_rcd_3_bit.schedule_rcd = 2;
  dmc_t_rfc_3_bit.t_rfc = _P2C(SDRAM_TRFC);   // Set autorefresh command time setting
  dmc_t_rfc_3_bit.schedule_rfc = 15;
  dmc_t_rp_3_bit.t_rp = _P2C(SDRAM_TRP);      // Set precharge delay setting to RAS
  dmc_t_rp_3_bit.schedule_rp = 2;
  dmc_t_rrd_3_bit.t_rrd = _P2C(SDRAM_TRRD);   // Delay from Active bank A to Active bank B
  dmc_t_wr_3_bit.t_wr = SDRAM_TWR;            // Delay from write to Precharge
  dmc_t_wtr_3_bit.t_wtr = SDRAM_TWR;          // Delay from write to read
  dmc_t_xp_3_bit.t_xp = 1;                    // Set the exit power-down command time
  dmc_t_xsr_3_bit.t_xsr = _P2C(SDRAM_TXSR);   // Set time between the Exit self-refresh command and Exit
  dmc_t_esr_3_bit.t_esr = 20;                 // Set minimum time from self-refresh Entry to Exit
  dmc_refresh_prd_3 = _P2C(SDRAM_REFRESH);    // Set auto refresh period

  dmc_memory_cfg_3_bit.column_bits      = 1;  // col - 9
  dmc_memory_cfg_3_bit.row_bits         = 2;  // row - 13
  dmc_memory_cfg_3_bit.ap_bit           = 0;  // Auto-precharge bit Addr10 line
  dmc_memory_cfg_3_bit.auto_power_down  = 0;  // disable auto power-down
  dmc_memory_cfg_3_bit.stop_mem_clock   = 0;  // enable memory clock
  dmc_memory_cfg_3_bit.memory_burst     = 3;  // Burst 8

  dmc_chip_0_cfg_3_bit.brc_n_rbc = 1;         // bank, row, column
  dmc_chip_0_cfg_3_bit.address_match = 0x40;  // 0x4xxx xxxx - 0x5xxx xxxx
  dmc_chip_0_cfg_3_bit.address_mask  = 0xE0;

  // SDRAM Initialization Sequence
  // DELAY to allow power and clocks to stabilize ~100 us
  Dly_us(100);
  // NOP
  dmc_direct_cmd_3 = 3UL<<18;
  Dly_us(100);
  // PALL
  dmc_direct_cmd_3 = 0;
  Dly_us(100);
  // AUTOREFRESH x 2
  dmc_direct_cmd_3 = 1UL<<18;
  for(volatile Int32U i= 128; i; --i);
  dmc_direct_cmd_3 = 1UL<<18;
  for(volatile Int32U i= 128; i; --i);
  // COMM
  // Burst 8, Sequential, CAS-3
  dmc_direct_cmd_3 = (2UL << 18)
                   | (3UL << 0)   // Burst 8
                   | (3UL << 4)   // CAS 3
                     ;
  // NOP
  dmc_direct_cmd_3 = 3UL<<18;
  // NORM
  dmc_memc_cmd_3 = 0;
  Dly_us(100);
#endif // SDRAM_INIT

  // Init interrupt controller
  // Assign all interrupt channels to IRQ
  VICINTSELECT  =  0;
  // Disable all interrupts
  VICINTENCLEAR = 0xFFFFFFFF;
  // Clear all software interrupts
  VICSOFTINTCLEAR = 0xFFFFFFFF;
  // VIC registers can be accessed in User or privileged mode
  VICPROTECTION = 0;
  // Clear interrupt
  VICADDRESS = 0;

  // Clear address of the Interrupt Service routine (ISR) for vectored IRQs
  // and disable all vectored IRQ slots
  for(i = 0,  pVecCntl = &VICVECTPRIORITY0, pVecAdd = &VICVECTADDR0; i < 32; ++i)
  {
    *pVecCntl++ = *pVecAdd++ = 0;
  }
  return(1);
}
