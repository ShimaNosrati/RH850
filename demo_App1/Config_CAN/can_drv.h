/******************************************************************************* 
* File Name    : can_drv.h 
* Version	    : 1.11
* Device(s) 	: RH850/U2A
* Description  : This is include file for CAN configuration.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
* : 31.10.2020 	1.00 	First Release
* : 30.06.2022 	1.10 	Modified for RH850/U2A6
* : 30.06.2022 	1.11 	Modified for RH850/U2A8
******************************************************************************/
#ifndef CAN_DRV_H
#define CAN_DRV_H

#include "can.h"

typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef signed short        int16_t;
typedef unsigned short      uint16_t;
typedef signed long         int32_t;
typedef unsigned long       uint32_t;
typedef signed long long    int64_t;
typedef unsigned long long  uint64_t;

typedef unsigned int  Can_RtnType;

typedef uint8_t can_ch_t;
typedef uint8_t can_rxfifo_t;
typedef uint8_t can_trfifo_t;
typedef uint8_t can_txbuf_t;

/* ---- Channel ---- */
#define CAN_CH0             0U
#define CAN_CH1             1U
#define CAN_CH2             2U
#define CAN_CH3             3U
#define CAN_CH4             4U
#define CAN_CH5             5U
#define CAN_CH6             6U
#define CAN_CH7             7U

/* ---- Rx FIFO ---- */
#define CAN_RXFIFO0         0U
#define CAN_RXFIFO1         1U
#define CAN_RXFIFO2         2U
#define CAN_RXFIFO3         3U
#define CAN_RXFIFO4         4U
#define CAN_RXFIFO5         5U
#define CAN_RXFIFO6         6U
#define CAN_RXFIFO7         7U
#define CAN_MAX_RXFIFO_NUM  8U

/* ---- Common (Tx/Rx) FIFO ---- */
#define CAN_TRFIFO0         0U
#define CAN_TRFIFO1         1U
#define CAN_TRFIFO2         2U
#define CAN_MAX_TRFIFO_NUM  3U

/* ---- Tx buffers ---- */
#define CAN_TXBUF0          0U
#define CAN_TXBUF1          1U
#define CAN_TXBUF2          2U
#define CAN_TXBUF3          3U
#define CAN_TXBUF4          4U
#define CAN_TXBUF5          5U
#define CAN_TXBUF6          6U
#define CAN_TXBUF7          7U
#define CAN_TXBUF8          8U
#define CAN_TXBUF9          9U
#define CAN_TXBUF10         10U
#define CAN_TXBUF11         11U
#define CAN_TXBUF12         12U
#define CAN_TXBUF13         13U
#define CAN_TXBUF14         14U
#define CAN_TXBUF15         15U
#define CAN_MAX_TXBUF_NUM   16U

/* ---- CAN frame ----- */
typedef struct
{
    uint32_t ID :29;   /* ID Data                            */
    uint32_t THDSE :1; /* Transmit History Data Store Enable */
    uint32_t RTR :1;   /* RTR  0:Data 1:Remote               */
    uint32_t IDE :1;   /* IDE  0:Standard 1:Extend           */
    uint32_t TS :16;   /* Timestamp Data                     */
    uint32_t LBL :12;  /* Label Data                         */
    uint32_t DLC :4;   /* DLC Data                           */
    uint32_t FDSTS;    /* FD Status                          */
    uint8_t  DB[64];   /* Data Byte                          */
} can_frame_t;

typedef struct {
    /* ---- Channel control ---- */
    uint32_t  ch_func;
    /* ---- Normal Baudrate ---- */
    uint32_t  nbr_cfg;
	/* ---- Data Baudrate ---- */
	uint32_t  dbr_cfg;
	/* ---- Ch CANFD Config ---- */
	uint32_t  ch_canfd_cfg;
    /* ---- Common (Tx/Rx) FIFO ---- */
    uint32_t  tr0_cfg;
    uint32_t  tr1_cfg;
    uint32_t  tr2_cfg;
    /* ---- Tx queue ---- */
    uint32_t  tq_cfg;
    /* ---- Tx buffer transmission complete interrupt ---- */
    uint16_t  tb_int_cfg;
    uint8_t   dummy[2];
} can_ch_cfg_t;

extern const uint8_t       g_ch_use_table[MAX_CH_NUM];
extern const uint8_t       g_rxfifo_use_table[CAN_MAX_RXFIFO_NUM];
#if USE_CH_NUM > 0
extern const uint8_t       g_trfifo_use_table[USE_CH_NUM][CAN_MAX_TRFIFO_NUM];
extern const uint8_t       g_txqueue_use_table[USE_CH_NUM];
extern const can_ch_cfg_t  g_can_ch_cfg[USE_CH_NUM];
#endif /* USE_CH_NUM > 0 */
extern const uint8_t  g_fifo_lost_isr;
#if CAN_RX_RULE_NUM > 0
extern const uint32_t g_rxrule_table[CAN_RX_RULE_NUM][4];
#endif /* CAN_RX_RULE_NUM > 0 */

/* ---- Configuration ---- */
#define CAN_NOUSE                           0x00U
#define CAN_USE                             0x80U
#define CAN_USE_RX_MODE                     0x81U
#define CAN_USE_TX_MODE                     0x82U
#define CAN_USE_GW_MODE                     0x83U
#define CAN_USE_CH_MASK                     0x07U

/* ---- function return value ---- */
#define CAN_RTN_OK                          0U
#define CAN_RTN_OK_WITH_LOST                1U
#define CAN_RTN_FIFO_FULL                   2U
#define CAN_RTN_BUFFER_EMPTY                3U
#define CAN_RTN_MODE_WAIT                   4U
#define CAN_RTN_RAM_INIT                    5U

#define CAN_RTN_TRANSMITTING                0U
#define CAN_RTN_TX_ABORT_OVER               1U
#define CAN_RTN_TX_END                      2U
#define CAN_RTN_TX_END_WITH_ABORT_REQ       3U

#define CAN_RTN_ERROR                       (0x80000000UL)
#define CAN_RTN_ARG_ERROR                   (CAN_RTN_ERROR + 0x7FFFFFFF)
#define CAN_RTN_STS_ERROR                   (CAN_RTN_ERROR + 0x7FFFFFFE)
#define CAN_RTN_OVERWRITE                   (CAN_RTN_ERROR + 0x7FFFFFFD)
#define CAN_RTN_MODE_ERROR                  (CAN_RTN_ERROR + 0x7FFFFFFC)

extern Can_RtnType R_CAN_Init(void);
extern Can_RtnType R_CAN_GlobalStart(void);
extern Can_RtnType R_CAN_ChStart(can_ch_t ch_idx);
extern Can_RtnType R_CAN_TrmByTxBuf(can_ch_t ch_idx, can_txbuf_t txbuf_idx, const can_frame_t* pFrame);
extern Can_RtnType R_CAN_AbortTrm(can_ch_t ch_idx, can_txbuf_t txbuf_idx);
extern Can_RtnType R_CAN_CheckTxBufResult(can_ch_t ch_idx, can_txbuf_t txbuf_idx);
extern Can_RtnType R_CAN_TrmByTRFIFO(can_ch_t ch_idx, can_trfifo_t trfifo_idx, const can_frame_t* pFrame);
extern Can_RtnType R_CAN_TrmByTxQueue(can_ch_t ch_idx, const can_frame_t* pFrame);
extern Can_RtnType R_CAN_ReadRxBuffer(uint8_t* p_rxbuf_idx, can_frame_t* pFrame);
extern Can_RtnType R_CAN_ReadRxFIFO(can_rxfifo_t rxfifo_idx, can_frame_t* pFrame);
extern Can_RtnType R_CAN_ReadTRFIFO(can_ch_t ch_idx, can_trfifo_t trfifo_idx, can_frame_t* pFrame);
extern Can_RtnType R_CAN_ReadChStatus(can_ch_t ch_idx);

#endif /* R_RH850_CAN_DRV_H */
