/***********************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *   (c) Copyright IAR Systems 2011
 *
 *   File name   : can.h
 *
 **********************************************************************/

#ifndef _can_h_
#define _can_h_

typedef struct {
	int 	baudrate;
	int		loopback;
} sCANSetup;

typedef struct  {
	unsigned int	id;			/* message ID */
	unsigned char	format;		/* 0: Standard ID, 1: Extended ID */
	unsigned char	type;		/* 0: DATA frame, 1: REMOTE frame */
} sCANMsgType;

typedef struct  {
	sCANMsgType		atr;		/* Message attribute */
	unsigned char	data[8];	/* data */
	unsigned int	dlen;		/* data length */
	unsigned int	time;		/* time stamp */
} sCANMsg;

int CAN_Init(sCANSetup *pSetPar);
int CAN_SetMbx_Rx(int ch, sCANMsgType *pAtr);
int CAN_SetMbx_Tx(int ch, sCANMsgType *pAtr);
int CAN_RecvMsg(int ch, sCANMsg *pMsg);
int CAN_SendMsg(int ch, sCANMsg *pMsg);


#endif /* _can_h_ */
