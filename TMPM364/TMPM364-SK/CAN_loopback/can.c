/***********************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *   (c) Copyright IAR Systems 2011
 *
 *   File name   : can.c
 *
 **********************************************************************/

#include <string.h>
#include <Toshiba\iotmpm364F10FG.h>
#include <intrinsics.h>
#include "can.h"


/***********************************************************************
 * Function:    CAN_InitPort
 * Description: Port PIN setup of CAN Port
 * Parameters:  none
 * Return:      none
 **********************************************************************/
static void CAN_InitPort(void)
{
    PEFR1_bit.PE4F1 = 0;
    PEFR1_bit.PE5F1 = 0;
    PEFR2_bit.PE4F2 = 0;
    PEFR2_bit.PE5F2 = 0;
//  PEFR3_bit.PE4F3 = 1;    /* CTXD Pin */
//  PEFR3_bit.PE5F3 = 1;    /* CRXD Pin */
    PEFR3 |= 0x30;
    PECR_bit.PE4C = 1;      /* Output mode: CTXD Pin */
    PECR_bit.PE5C = 0;
    PEIE_bit.PE4IE = 0;
    PEIE_bit.PE5IE = 1;     /* Input mode: CRXD Pin */
    PEOD_bit.PE4OD = 0;     /* CMOS mode: CTXD Pin */
    PECR_bit.PE4C = 1;      /* Output mode: CTXD Pin */
    PEPUP_bit.PE4UP = 0;
    PEPUP_bit.PE5UP = 0;

}


/***********************************************************************
 * Function:    CAN_Init
 * Description: CAN Interface initialization
 * Parameters:  pSetPar:    Setup descriptor
 * Return:      0:      Success
 *              -1:     Fail
 **********************************************************************/
int CAN_Init(sCANSetup *pSetPar)
{
    CANMCR_bit.SRES = 1;    /* Apply software reset */
    CAN_InitPort();     /* setup CAN port pins */

    switch (pSetPar->baudrate) {
    case 100000:        /* baudrate = 100kbps */
        CANBCR1 = 0x0E;         /* prescaler */
        CANBCR2 = 0x00000114;   /* SJW:1, SAM:0, TSEG1:4, TSEG2:1 */
        break;
    case 200000:        /* baudrate = 200kbps */
        CANBCR1 = 0x05;         /* prescaler */
        CANBCR2 = 0x00000225;   /* SJW:2, SAM:0, TSEG1:5, TSEG2:2 */
        break;
    case 300000:        /* baudrate = 300kbps */
        CANBCR1 = 0x04;         /* prescaler */
        CANBCR2 = 0x00000114;   /* SJW:1, SAM:0, TSEG1:4, TSEG2:1 */
        break;
    case 400000:        /* baudrate = 400kbps */
        CANBCR1 = 0x02;         /* prescaler */
        CANBCR2 = 0x00000225;   /* SJW:2, SAM:0, TSEG1:5, TSEG2:2 */
        break;
    case 500000:        /* baudrate = 500kbps */
        CANBCR1 = 0x02;         /* prescaler */
        CANBCR2 = 0x00000114;   /* SJW:1, SAM:0, TSEG1:4, TSEG2:1 */
        break;
    case 600000:        /* baudrate = 600kbps */
        CANBCR1 = 0x01;         /* prescaler */
        CANBCR2 = 0x00000225;   /* SJW:2, SAM:0, TSEG1:5, TSEG2:2 */
        break;

    default:
        return -1;      /* Not supported in this program */
    }

    if (pSetPar->loopback) {
        CANMCR_bit.TSTLB = 1;   /* Set loopback mode */
    }
    CANMC = 0x0;
    CANMCR_bit.MTOS = 1;    /* Transmit as per ID priority */

    CANMCR_bit.CCR = 0;     /* clear CCR (change to Normal mode) */
    while (CANGSR_bit.CCE != 0);

    return 0;
}

/***********************************************************************
 * Function:    CAN_SetMbx_Rx
 * Description: Set Receiver Mailbox
 * Parameters:  ch:     Mailbox channel
 *              pAtr:   Mailbox attribute (ID)
 * Return:      0:      Success
 *              -1:     Fail
 **********************************************************************/
int CAN_SetMbx_Rx(int ch, sCANMsgType *pAtr)
{
    if (ch > 31) return -1;
    CANMC &= ~(1<<ch);      /* Disable Mailbox */
    CANMD |= (1<<ch);       /* Set as Receive Mailbox */
    if (pAtr->format == 0) {
        /* Standard format Id */
        (&CANMB0ID)[8*ch] = (pAtr->id & 0x7FF)<<18;
    }
    else {
        /* Extended format Id */
        (&CANMB0ID)[8*ch] = (pAtr->id & 0x1FFFFFFFF) | (1<<31);
    }
    CANMC |= (1<<ch);       /* Enable Mailbox */
    return 0;
}


/***********************************************************************
 * Function:    CAN_SetMbx_Tx
 * Description: Set Transmitter Mailbox
 * Parameters:  ch:     Mailbox channel
 *              pAtr:   Mailbox attribute (ID)
 * Return:      0:      Success
 *              -1:     Fail
 **********************************************************************/
int CAN_SetMbx_Tx(int ch, sCANMsgType *pAtr)
{
    if (ch >= 31) return -1;
    CANMC &= ~(1<<ch);      /* Disable Mailbox */
    CANMD &= ~(1<<ch);      /* Set as Transmitter Mailbox */
    if (pAtr->format == 0) {
        /* Standard format Id */
        (&CANMB0ID)[8*ch] = (pAtr->id & 0x7FF)<<18;
    }
    else {
        /* Extended format Id */
        (&CANMB0ID)[8*ch] = (pAtr->id & 0x1FFFFFFFF) | (1<<31);
    }
    CANMC |= (1<<ch);       /* Enable Mailbox */
    return 0;
}


/***********************************************************************
 * Function:    CAN_RecvMsg
 * Description: Receive Message from Mailbox
 * Parameters:  ch:     Mailbox channel
 *              pMsg:   Message
 * Return:      0:      Success
 *              -1:     Fail
 **********************************************************************/
int CAN_RecvMsg(int ch, sCANMsg *pMsg)
{
    char *pDat = (char *)&CANMB0DH + (0x20*ch);
    if (ch > 31) return -1;
    if (!(CANRMP & (1<<ch))) return -1;     /* no message in mailbox */

    pMsg->atr.type = ((&CANMB0TSVMCF)[8*ch] >> 4) & 1;
    if (pMsg->atr.type == 0)    /* Data Frame type */
    {
        /* Read data and data length */
        pMsg->dlen = (&CANMB0TSVMCF)[8*ch] & 0xF;
        if (pMsg->dlen > 8)
        {
            CANRMP = (1<<ch);       /* release the mailbox */
            return -1;
        }
        if (pMsg->dlen > 4) {
            memcpy(&pMsg->data[0], pDat, 4);
            pDat = (char *)&CANMB0DL + (0x20*ch);
            memcpy(&pMsg->data[4], pDat, pMsg->dlen-4);
        }
        else {
            memcpy(pMsg->data, pDat, pMsg->dlen);
        }
    }
    else
    {
        memset(pMsg->data, 0, 8);
    }

    pMsg->atr.format = ((&CANMB0ID)[8*ch] >> 31) & 1;
    if (pMsg->atr.format == 0)  /* Standard format ID */
    {
        pMsg->atr.id = ((&CANMB0ID)[8*ch] >> 18) & 0x7FF;
    }
    else
    {
        pMsg->atr.id = (&CANMB0ID)[8*ch] & 0x1FFFFFFF;
    }

    pMsg->time = ((&CANMB0TSVMCF)[8*ch] >> 16) & 0xFFFF;
    CANRMP = (1<<ch);       /* release the mailbox */
    return 0;
}

/***********************************************************************
 * Function:    CAN_SendMsg
 * Description: Send Message
 * Parameters:  ch:     Mailbox channel
 *              pMsg:   Message
 * Return:      0:      Success
 *              -1:     Fail
 **********************************************************************/
int CAN_SendMsg(int ch, sCANMsg *pMsg)
{
    char *pDat = (char *)&CANMB0DH + (0x20*ch);
    if (ch >= 31) return -1;
    if (pMsg->dlen > 8) return -1;

    /* Set data and data length */
    (&CANMB0TSVMCF)[8*ch] = pMsg->dlen & 0xF;
    if (pMsg->dlen > 4) {
        memcpy(pDat, &pMsg->data[0], 4);
        pDat = (char *)&CANMB0DL + (0x20*ch);
        memcpy(pDat, &pMsg->data[4], pMsg->dlen-4);
    }
    else {
        memcpy(pDat, pMsg->data, pMsg->dlen);
    }
    
    CANTRS |= (1<<ch);      /* request transmission */

    while (!(CANTA & (1<<ch)));     /* Wait for end of transmission */
    CANTA = (1<<ch);                    /* acknowledge transmission */
    return 0;
}


