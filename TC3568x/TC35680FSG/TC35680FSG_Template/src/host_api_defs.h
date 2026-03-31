/*
 * COPYRIGHT (C) 2016
 * TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION
 * ALL RIGHTS RESERVED
 *
 * THE SOURCE CODE AND ITS RELATED DOCUMENTATION IS PROVIDED "AS IS". TOSHIBA
 * ELECTRONIC DEVICES & STORAGE CORPORATION MAKES NO OTHER WARRANTY OF ANY
 * KIND, WHETHER EXPRESS, IMPLIED OR, STATUTORY AND DISCLAIMS ANY AND ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY, SATISFACTORY QUALITY, NON
 * INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * THE SOURCE CODE AND DOCUMENTATION MAY INCLUDE ERRORS. TOSHIBA ELECTRONIC
 * DEVICES & STORAGE CORPORATION RESERVES THE RIGHT TO INCORPORATE
 * MODIFICATIONS TO THE SOURCE CODE IN LATER REVISIONS OF IT, AND TO MAKE
 * IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR THE PRODUCTS OR
 * TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME.
 *
 * TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION SHALL NOT BE LIABLE FOR
 * ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGE OR LIABILITY ARISING FROM YOUR
 * USE OF THE SOURCE CODE OR ANY DOCUMENTATION, INCLUDING BUT NOT LIMITED TO,
 * LOST REVENUES, DATA OR PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL NATURE, PUNITIVE DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS
 * ARISING OUT OF OR IN CONNECTION WITH THIS AGREEMENT, OR BEING UNUSABLE,
 * EVEN IF ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES AND
 * WHETHER A CLAIM FOR SUCH DAMAGE IS BASED UPON WARRANTY, CONTRACT, TORT,
 * NEGLIGENCE OR OTHERWISE.
 */
/* VERSION : 20181010A */
/* TARGET  : TC35680-ROM002 */

/*****************************************************************************/
#ifndef HOST_API_DEFS_H
#define HOST_API_DEFS_H

/* Module ID */
#define TIMER_MOD_ID             (1)
#define FAT_IF_MOD_ID           (73)
#define FAT_API_MOD_ID         (130)

/* Mailbox ID */
#define FIF_MBOX_ID             (61)    /* Mailbox to Upper task(FATIF task) */
#define C2_MBOX_ID              (64)    /* Mailbox to UserApplication task   */

/* Event Flag */
#define HOST_APL_EVENT_FLG_A    (47)
#define HOST_APL_EVENT_FLG_B    (48)
#define HOST_APL_EVENT_FLG_C    (49)

/* Event Flag bits for HOST_APL_EVENT_FLG_A */
/* Signaled when OS message to C2 task is sent. */
#define C2_MSG_INT_BIT          (1 << 0)
/* Reserved for future use. (Reserved for timer C) */
#define C2_UP_TIM_C_TO_BIT      (1 << 2)
/* Reserved for future use. (Reserved for timer E) */
#define C2_UP_TIM_E_TO_BIT      (1 << 3)
/* Reserved for future use. (Reserved for timer F) */
#define C2_UP_TIM_F_TO_BIT      (1 << 4)
/* Reserved for future use. (Reserved for timer G) */
#define C2_UP_TIM_G_TO_BIT      (1 << 5)
/* Signaled when getting up from Sleep mode due to GPIO level change. */
#define C2_GPIO_WAKEUP_BIT      (1 << 7)
/* Signaled when getting up from Backup mode due to GPIO level change. */
#define C2_GPIO_WAKEUP_2_BIT    (1 << 8)
/* Signaled when getting up from Backup mode
   due to finishing specified number of Advertising. */
#define C2_AUTO_WAKEUP_BIT      (1 << 9)

/* Fixed Memory ID and size */
/* Used to receive responses and events of TCU commands */
#define FIF_EVT_MPF_ID            (85)
#define FIF_EVT_MPF_ID_SIZE       (312)
#define FIF_EVT_MPF_ID_COUNT      (4)
/* Used to send TCU commands to UpperTask */
#define FIF_ACL_CMD_MPF_ID        (87)
#define FIF_ACL_CMD_MPF_ID_SIZE   (304)
#define FIF_ACL_CMD_MPF_ID_COUNT  (8)
/* Used to send data to UART task */
#define UART_EVT_MPF_ID           (90)
#define UART_EVT_MPF_ID_SIZE      (312)
#define UART_EVT_MPF_ID_COUNT     (3)
/* Used to receive data from UART task */
#define UART_ACL_CMD_MPF_ID       (92)
#define UART_ACL_CMD_MPF_ID_SIZE  (416)
#define UART_ACL_CMD_MPF_ID_COUNT (3)

/* GPIO port number for interrupt */
#define GPIO0_INT_BIT           (1<< 0)
#define GPIO1_INT_BIT           (1<< 1)
#define GPIO2_INT_BIT           (1<< 2)
#define GPIO3_INT_BIT           (1<< 3)
#define GPIO4_INT_BIT           (1<< 4)
#define GPIO5_INT_BIT           (1<< 5)
#define GPIO6_INT_BIT           (1<< 6)
#define GPIO7_INT_BIT           (1<< 7)
#define GPIO8_INT_BIT           (1<< 8)
#define GPIO9_INT_BIT           (1<< 9)
#define GPIO10_INT_BIT          (1<<10)
#define GPIO11_INT_BIT          (1<<11)
#define GPIO12_INT_BIT          (1<<12)
#define GPIO13_INT_BIT          (1<<13)
#define GPIO14_INT_BIT          (1<<14)
#define GPIO15_INT_BIT          (1<<15)
#define GPIO16_INT_BIT          (1<<16)
#define GPIO17_INT_BIT          (1<<17)

#endif /* HOST_API_DEFS_H */
