/*******************************************************************************
* File Name 		 : m380_int.h
* Version			 : V1.0
* Date				 : 2010/01/XX
* Description		 : SFR define
********************************************************************************/

#ifndef __M380_INT_H
#define __M380_INT_H

/***************************************************************************
 **
 **  TMPM380FxFG Interrupt Lines (PIN No:LQFP)
 **
 ***************************************************************************/
#define MAIN_STACK             0          /* Main Stack                   */
#define RESETI                 1          /* Reset                        */
#define NMII                   2          /* Non-maskable Interrupt       */
#define HFI                    3          /* Hard Fault                   */
#define MMI                    4          /* Memory Management            */
#define BFI                    5          /* Bus Fault                    */
#define UFI                    6          /* Usage Fault                  */
#define SVCI                  11          /* SVCall                       */
#define DMI                   12          /* Debug Monitor                */
#define PSI                   14          /* PendSV                       */
#define STI                   15          /* SysTick                      */
#define EII                   16          /* External Interrupt           */
#define INT0                 ( 0 + EII)   /* Interrupt pin (PH0/62pin)    */
#define INT1                 ( 1 + EII)   /* Interrupt pin (PH1/63pin)    */
#define INT2                 ( 2 + EII)   /* Interrupt pin (PH2/64pin)    */
#define INT3                 ( 3 + EII)   /* Interrupt pin (PA0/30pin)    */
#define INT4                 ( 4 + EII)   /* Interrupt pin (PA2/32pin)     */
#define INT5                 ( 5 + EII)   /* Interrupt pin (PE4/43pin)    */
#define INTRX0               ( 6 + EII)   /* Serial reception (channel.0) */
#define INTTX0               ( 7 + EII)   /* Serial transmit (channel.0)  */
#define INTRX1               ( 8 + EII)   /* Serial reception (channel.1) */
#define INTTX1               ( 9 + EII)   /* Serial transmit (channel.1)  */
#define INTSSP0              (10 + EII)   /* Syncronous Serial Port 0     */
#define INTSSP1              (11 + EII)   /* Syncronous Serial Port 1     */
#define INTEMG0              (12 + EII)   /* 16-bit MPT0 IGBT EMG interrupt*/
#define INTEMG1              (13 + EII)   /* 16-bit MPT1 IGBT EMG interrupt*/
#define INTSBI0              (14 + EII)   /* Serial Bus Interface 0 interrupt */
#define INTSBI1              (15 + EII)   /* Serial Bus Interface 1 interrupt */
#define INTADPD0             (16 + EII)   /* ADC conversion triggered by PMD0 is finished */
#define INTRTC               (17 + EII)   /* Realtime clock interrupt */
#define INTADPD1             (18 + EII)   /* ADC conversion triggered by PMD1 is finished */
#define INTRMCRX             (19 + EII)   /* Remote Controller reception interrupt */
#define INTTB00              (20 + EII)   /* 16bit TMRB0 match detection 0 */
#define INTTB01              (21 + EII)   /* 16bit TMRB0 match detection 1 */
#define INTTB10              (22 + EII)   /* 16bit TMRB1 match detection 0 */
#define INTTB11              (23 + EII)   /* 16bit TMRB1 match detection 1 */
#define INTTB40              (24 + EII)   /* 16bit TMRB4 match detection 0 */
#define INTTB41              (25 + EII)   /* 16bit TMRB4 match detection 1 */
#define INTTB50              (26 + EII)   /* 16bit TMRB5 match detection 0 */
#define INTTB51              (27 + EII)   /* 16bit TMRB5 match detection 1 */
#define INTPMD0              (28 + EII)   /* PMD0 PWM Interrupt            */
#define INTPMD1              (29 + EII)   /* PMD1 PWM Interrupt            */
#define INTCAP00             (30 + EII)   /* 16bit TMRB0 input capture 0   */
#define INTCAP01             (31 + EII)   /* 16bit TMRB0 input capture 1   */
#define INTCAP10             (32 + EII)   /* 16bit TMRB1 input capture 0   */
#define INTCAP11             (33 + EII)   /* 16bit TMRB1 input capture 1   */
#define INTCAP40             (34 + EII)   /* 16bit TMRB2 input capture 0   */
#define INTCAP41             (35 + EII)   /* 16bit TMRB2 input capture 1   */
#define INTCAP50             (36 + EII)   /* 16bit TMRB3 input capture 0   */
#define INTCAP51             (37 + EII)   /* 16bit TMRB3 input capture 1   */
#define INT6                 (38 + EII)   /* Interrupt pin (PE6/46pin)     */
#define INT7                 (39 + EII)   /* Interrupt pin (PE7/47pin)     */
#define INTRX2               (40 + EII)   /* Serial reception (channel.2)  */
#define INTTX2               (41 + EII)   /* Serial transmit (channel.2)   */
#define INTADCP0             (42 + EII)   /* ADC conversion monitoring function interrupt 0 */
#define INTADCP1             (43 + EII)   /* ADC conversion monitoring function interrupt 1 */
#define INTRX4               (44 + EII)   /* Serial reception (channel.4)  */
#define INTTX4               (45 + EII)   /* Serial transmit (channel.4)   */
#define INTTB20              (46 + EII)   /* 16bit TMRB2 match detection 0 */
#define INTTB21              (47 + EII)   /* 16bit TMRB2 match detection 1 */
#define INTTB30              (48 + EII)   /* 16bit TMRB3 match detection 0 */
#define INTTB31              (49 + EII)   /* 16bit TMRB3 match detection 1 */
#define INTCAP20             (50 + EII)   /* 16bit TMRB2 input capture 0   */
#define INTCAP21             (51 + EII)   /* 16bit TMRB2 input capture 1   */
#define INTCAP30             (52 + EII)   /* 16bit TMRB3 input capture 0   */
#define INTCAP31             (53 + EII)   /* 16bit TMRB3 input capture 1   */
#define INTADSFT             (54 + EII)   /* ADC conversion started by software is finished */
/* #define RESERVED          (55 + EII)   */
#define INTADTMR             (56 + EII)   /* ADC conversion triggered by timer is finished */
/* #define RESERVED          (57 + EII)   */
#define INT8                 (58 + EII)   /* Interrupt pin (PA7/37pin)      */
#define INT9                 (59 + EII)   /* Interrupt pin (PD3/2pin)     */
#define INTA                 (60 + EII)   /* Interrupt pin (PJ6/78pin)  */
#define INTB                 (61 + EII)   /* Interrupt pin (PJ7/79pin)  */
#define INTENC0              (62 + EII)   /* Encoder timer 0               */
#define INTENC1              (63 + EII)   /* Encoder timer 1               */
#define INTRX3               (64 + EII)   /* Serial reception (channel.3)  */
#define INTTX3               (65 + EII)   /* Serial transmit (channel.3)   */
#define INTTB60              (66 + EII)   /* 16bit TMRB6 match detection 0 */
#define INTTB61              (67 + EII)   /* 16bit TMRB6 match detection 1 */
#define INTTB70              (68 + EII)   /* 16bit TMRB7 match detection 0 */
#define INTTB71              (69 + EII)   /* 16bit TMRB7 match detection 1 */
#define INTCAP60             (70 + EII)   /* 16bit TMRB6 input capture 0   */
#define INTCAP61             (71 + EII)   /* 16bit TMRB6 input capture 1   */
#define INTCAP70             (72 + EII)   /* 16bit TMRB7 input capture 0   */
#define INTCAP71             (73 + EII)   /* 16bit TMRB7 input capture 1   */
#define INTC                 (74 + EII)   /* Interrupt pin (PD0/5pin)     */
#define INTD                 (75 + EII)   /* Interrupt pin (PD2/3pin)     */
#define INTE                 (76 + EII)   /* Interrupt pin (PN7/55pin)     */
#define INTF                 (77 + EII)   /* Interrupt pin (PL2/56pin)     */
#define INTDMACERR           (78 + EII)   /* DMA transfer error     */
#define INTDMACTC            (79 + EII)   /* DMA end of transfer     */
#define INTMTPTB00           (80 + EII)   /* 16-bit MPT0 IGBT period/ compare match detection 0 */
#define INTMTTTB01           (81 + EII)   /* 16-bit MPT0 IGBT trigger/ compare match detection 1 */
#define INTMTPTB10           (82 + EII)   /* 16-bit MPT1 IGBT period/ compare match detection 0 */
#define INTMTTTB11           (83 + EII)   /* 16-bit MPT1 IGBT trigger/ compare match detection 1 */
#define INTMTPTB20           (84 + EII)   /* 16-bit MPT2 IGBT period/ compare match detection 0 */
#define INTMTTTB21           (85 + EII)   /* 16-bit MPT2 IGBT trigger/ compare match detection 1 */
#define INTMTCAP00           (86 + EII)   /* 16-bit MPT0 input capture 0   */
#define INTMTCAP01           (87 + EII)   /* 16-bit MPT0 input capture 1   */
#define INTMTCAP10           (88 + EII)   /* 16-bit MPT1 input capture 0   */
#define INTMTCAP11           (89 + EII)   /* 16-bit MPT1 input capture 1   */
#define INTMTCAP20           (80 + EII)   /* 16-bit MPT2 input capture 0   */
#define INTMTCAP21           (91 + EII)   /* 16-bit MPT2 input capture 1   */
#define INTMTEMG0              (92 + EII)   /* 16-bit MPT0 IGBT EMG interrupt*/
#define INTMTEMG1            (93 + EII)   /* 16-bit MPT1 IGBT EMG interrupt*/
#define INTMTEMG2            (94 + EII)   /* 16-bit MPT2 IGBT EMG interrupt*/


#define EXT_INT0                  0    /* Interrupt pin (PH0/62pin)    */
#define EXT_INT1                  1    /* Interrupt pin (PH1/63pin)    */
#define EXT_INT2                  2    /* Interrupt pin (PH2/64pin)    */
#define EXT_INT3                  3    /* Interrupt pin (PA0/30pin)    */
#define EXT_INT4                  4    /* Interrupt pin (PA2/32pin)     */
#define EXT_INT5                  5    /* Interrupt pin (PE4/43pin)    */
#define EXT_INTRX0                6    /* Serial reception (channel.0) */
#define EXT_INTTX0                7    /* Serial transmit (channel.0)  */
#define EXT_INTRX1                8    /* Serial reception (channel.1) */
#define EXT_INTTX1                9    /* Serial transmit (channel.1)  */
#define EXT_INTSSP0              10    /* Syncronous Serial Port 0     */
#define EXT_INTSSP1              11    /* Syncronous Serial Port 1     */
#define EXT_INTEMG0              12    /* Encoder input0 interrupt     */
#define EXT_INTEMG1              13    /* Encoder input1 interrupt     */
#define EXT_INTSBI0              14    /* Serial Bus Interface 0 interrupt */
#define EXT_INTSBI1              15    /* Serial Bus Interface 1 interrupt */
#define EXT_INTADPD0             16    /* ADC conversion triggered by PMD0 is finished */
#define EXT_INTRTC               17    /* Realtime clock interrupt */
#define EXT_INTADPD1             18    /* ADC conversion triggered by PMD1 is finished */
#define EXT_INTRMCRX             19    /* Remote Controller reception interrupt */
#define EXT_INTTB00              20    /* 16bit TMRB0 match detection 0 */
#define EXT_INTTB01              21    /* 16bit TMRB0 match detection 1 */
#define EXT_INTTB10              22    /* 16bit TMRB1 match detection 0 */
#define EXT_INTTB11              23    /* 16bit TMRB1 match detection 1 */
#define EXT_INTTB40              24    /* 16bit TMRB4 match detection 0 */
#define EXT_INTTB41              25    /* 16bit TMRB4 match detection 1 */
#define EXT_INTTB50              26    /* 16bit TMRB5 match detection 0 */
#define EXT_INTTB51              27    /* 16bit TMRB5 match detection 1 */
#define EXT_INTPMD0              28    /* PMD0 PWM Interrupt            */
#define EXT_INTPMD1              29    /* PMD1 PWM Interrupt            */
#define EXT_INTCAP00             30    /* 16bit TMRB0 input capture 0   */
#define EXT_INTCAP01             31    /* 16bit TMRB0 input capture 1   */
#define EXT_INTCAP10             32    /* 16bit TMRB1 input capture 0   */
#define EXT_INTCAP11             33    /* 16bit TMRB1 input capture 1   */
#define EXT_INTCAP40             34    /* 16bit TMRB2 input capture 0   */
#define EXT_INTCAP41             35    /* 16bit TMRB2 input capture 1   */
#define EXT_INTCAP50             36    /* 16bit TMRB3 input capture 0   */
#define EXT_INTCAP51             37    /* 16bit TMRB3 input capture 1   */
#define EXT_INT6                 38    /* Interrupt pin (PE6/46pin)     */
#define EXT_INT7                 39    /* Interrupt pin (PE7/47pin)     */
#define EXT_INTRX2               40    /* Serial reception (channel.2)  */
#define EXT_INTTX2               41    /* Serial transmit (channel.2)   */
#define EXT_INTADCP0             42    /* ADC conversion monitoring function interrupt 0 */
#define EXT_INTADCP1             43    /* ADC conversion monitoring function interrupt 1 */
#define EXT_INTRX4               44    /* Serial reception (channel.4)  */
#define EXT_INTTX4               45    /* Serial transmit (channel.4)   */
#define EXT_INTTB20              46    /* 16bit TMRB2 match detection 0 */
#define EXT_INTTB21              47    /* 16bit TMRB2 match detection 1 */
#define EXT_INTTB30              48    /* 16bit TMRB3 match detection 0 */
#define EXT_INTTB31              49    /* 16bit TMRB3 match detection 1 */
#define EXT_INTCAP20             50    /* 16bit TMRB2 input capture 0   */
#define EXT_INTCAP21             51    /* 16bit TMRB2 input capture 1   */
#define EXT_INTCAP30             52    /* 16bit TMRB3 input capture 0   */
#define EXT_INTCAP31             53    /* 16bit TMRB3 input capture 1   */
#define EXT_INTADSFT             54    /* ADC conversion started by software is finished */
/* #define RESERVED              55    */
#define EXT_INTADTMR             56    /* ADC conversion triggered by timer is finished */
/* #define RESERVED              57    */
#define EXT_INT8                 58    /* Interrupt pin (PA7/37pin)      */
#define EXT_INT9                 59    /* Interrupt pin (PD3/2pin)     */
#define EXT_INTA                 60    /* Interrupt pin (PJ6/78pin)  */
#define EXT_INTB                 61    /* Interrupt pin (PJ7/79pin)  */
#define EXT_INTENC0              62    /* Encoder timer 0               */
#define EXT_INTENC1              63    /* Encoder timer 1               */
#define EXT_INTRX3               64    /* Serial reception (channel.3)  */
#define EXT_INTTX3               65    /* Serial transmit (channel.3)   */
#define EXT_INTTB60              66    /* 16bit TMRB6 match detection 0 */
#define EXT_INTTB61              67    /* 16bit TMRB6 match detection 1 */
#define EXT_INTTB70              68    /* 16bit TMRB7 match detection 0 */
#define EXT_INTTB71              69    /* 16bit TMRB7 match detection 1 */
#define EXT_INTCAP60             70    /* 16bit TMRB6 input capture 0   */
#define EXT_INTCAP61             71    /* 16bit TMRB6 input capture 1   */
#define EXT_INTCAP70             72    /* 16bit TMRB7 input capture 0   */
#define EXT_INTCAP71             73    /* 16bit TMRB7 input capture 1   */
#define EXT_INTC                 74    /* Interrupt pin (PD0/5pin)     */
#define EXT_INTD                 75    /* Interrupt pin (PD2/3pin)     */
#define EXT_INTE                 76    /* Interrupt pin (PN7/55pin)     */
#define EXT_INTF                 77    /* Interrupt pin (PL2/56pin)     */
#define EXT_INTDMACERR           78    /* DMA transfer error     */
#define EXT_INTDMACTC            79    /* DMA end of transfer     */
#define EXT_INTMTPTB00           80    /* 16-bit MPT0 IGBT period/ compare match detection 0 */
#define EXT_INTMTTTB01           81    /* 16-bit MPT0 IGBT trigger/ compare match detection 1 */
#define EXT_INTMTPTB10           82    /* 16-bit MPT1 IGBT period/ compare match detection 0 */
#define EXT_INTMTTTB11           83    /* 16-bit MPT1 IGBT trigger/ compare match detection 1 */
#define EXT_INTMTPTB20           84    /* 16-bit MPT2 IGBT period/ compare match detection 0 */
#define EXT_INTMTTTB21           85    /* 16-bit MPT2 IGBT trigger/ compare match detection 1 */
#define EXT_INTMTCAP00           86    /* 16-bit MPT0 input capture 0   */
#define EXT_INTMTCAP01           87    /* 16-bit MPT0 input capture 1   */
#define EXT_INTMTCAP10           88    /* 16-bit MPT1 input capture 0   */
#define EXT_INTMTCAP11           89    /* 16-bit MPT1 input capture 1   */
#define EXT_INTMTCAP20           80    /* 16-bit MPT2 input capture 0   */
#define EXT_INTMTCAP21           91    /* 16-bit MPT2 input capture 1   */
#define EXT_INTMTEMG0              92    /* 16-bit MPT0 IGBT EMG interrupt*/
#define EXT_INTMTEMG1            93    /* 16-bit MPT1 IGBT EMG interrupt*/
#define EXT_INTMTEMG2            94    /* 16-bit MPT2 IGBT EMG interrupt*/



	/* ICRCG */			/* API_INT_ReqClr */
#define IP_INT_CLR_INT0			0x00		/* INT0 ReqClr			 */
#define IP_INT_CLR_INT1			0x01		/* INT1 ReqClr			 */
#define IP_INT_CLR_INT2			0x02		/* INT2 ReqClr			 */
#define IP_INT_CLR_INT3			0x03		/* INT3 ReqClr			 */
#define IP_INT_CLR_INT4			0x04		/* INT4 ReqClr			 */
#define IP_INT_CLR_INT5			0x05		/* INT5 ReqClr			 */
#define IP_INT_CLR_INT6			0x06		/* INT6 ReqClr			 */
#define IP_INT_CLR_INT7			0x07		/* INT7 ReqClr			 */
#define IP_INT_CLR_INT8			0x08		/* INT8 ReqClr			 */
#define IP_INT_CLR_INT9			0x09		/* INT9 ReqClr			 */
#define IP_INT_CLR_INTA			0x0A		/* INTA ReqClr			 */
#define IP_INT_CLR_INTB			0x0B		/* INTB ReqClr			 */
#define	IP_INT_CLR_INTC			0x0C		/* INTC ReqClr			 */
#define IP_INT_CLR_INTD			0x0D		/* INTD ReqClr			 */
#define IP_INT_CLR_INTE			0x0E		/* INTE ReqClr			 */
#define	IP_INT_CLR_INTF			0x0F		/* INTF ReqClr			 */
#define IP_INT_CLR_INTRTC		0x10		/* INTE ReqClr			 */
#define	IP_INT_CLR_INTRMCRX		0x11		/* INTF ReqClr			 */

	/* IMCGA,IMCGB,IMCGC,IMCGD */			/* API_INT_ActSt_Set */
#define IP_INT_ACTST_L			0x00		/* Standby Active State "L"	 */
#define IP_INT_ACTST_H			0x10		/* Standby Active State "H"	 */
#define IP_INT_ACTST_FALLING	0x20		/* Standby Active State "FALLING"	 */
#define IP_INT_ACTST_RISING		0x30		/* Standby Active State "RISING"	 */
#define IP_INT_ACTST_BOTH		0x40		/* Standby Active State "BOTH(FALLING,RISING)"	 */

	/* IMCGA,IMCGB,IMCGC,IMCGD */			/* API_INT_Enable */
#define IP_INT_DIS			0x00		/* Interrupt Disable	 */
#define IP_INT_ENA			0x01		/* Interrupt Enable	 */



void API_INT_Init(void);
void API_INT_claer_Init(void);
void API_CG_Active_Set(uint8_t ip_intnum, uint8_t active, uint8_t enable);
void API_CG_Active_Reset(void);
void API_INT_CER_All_Set(void);
void API_INT_CER_Set(uint8_t intnum);
void API_INT_PR_Set(uint8_t intnum, uint8_t pri);
void API_INT_PR_Reset(void);
void API_INT_SPR_ALL_Set(void);
void API_INT_SPR_Set(uint8_t intnum);
void API_INT_SER_Set(uint8_t intnum);


#endif

/*************************** END OF FILE **************************************/

