typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;



#pragma segment="CSTACK"

void __iar_program_start( void );
void main( void );
void NmiSR(void);
void FaultISR(void);
void SVCallISR(void);


void Int_CecRcv(void);
void Int_CecSend(void);
void Int_RemRcv0(void);
void Int_RemRcv1(void);
void Int_INTTB0(void);
void Int_INTTB6(void);
void Int_HINTTX0(void);
void Int_HINTRX0(void);
void Int_INTAD(void);
void Int_INTSBI0(void);

#pragma location = ".intvec"

const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NmiSR,
  FaultISR,
  0,
  0,
  0,
  0, 0, 0, 0,            /* Reserved */ 
  SVCallISR,
  0,
  0,                      /* Reserved */
  0,
  0,
0,	/*  0 */
0,	/*  1 */
0,	/*  2 */
0,	/*  3 */
0,	/*  4 */
0,	/*  5 */
Int_HINTRX0,	/*  6 */
Int_HINTTX0,	/*  7 */
0,	/*  8 */
0,	/*  9 */
Int_INTSBI0,	/* 10 */
0,	/* 11 */
Int_CecRcv,	/* 12 */
Int_CecSend,	/* 13 */
Int_RemRcv0,	/* 14 */
0,	/* 15 */
0,	/* 16 */
0,	/* 17 */
Int_INTTB0,	/* 18 */
0,	/* 19 */
0,	/* 20 */
0,	/* 21 */
0,	/* 22 */
0,	/* 23 */
Int_INTTB6,	/* 24 */
0,	/* 25 */
0,	/* 26 */
0,	/* 27 */
0,	/* 28 */
0,	/* 29 */
0,	/* 30 */
0,	/* 31 */
0,	/* 32 */
0,	/* 33 */
0,	/* 34 */
0,	/* 35 */
0,	/* 36 */
0,	/* 37 */
0,	/* 38 */
Int_RemRcv1,	/* 39 */
0,	/* 40 */
0,	/* 41 */
0,	/* 42 */
0,	/* 43 */
0,	/* 44 */
0,	/* 45 */
0,	/* 46 */
0,	/* 47 */
0,	/* 48 */
Int_INTAD	/* 49 */
};
