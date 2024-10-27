/******************************************************************************* 
* File Name    : can.h
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
#ifndef CAN_H
#define CAN_H

/* ---- Device information: RH850/U2A ---- */
#define MAX_CH_NUM                      4
#define USED_UNIT_NUM                   0

#if USED_UNIT_NUM == 0
  #define CAN_START_ADDR                (0xFFF50000UL)
#elif USED_UNIT_NUM == 1
  #define CAN_START_ADDR                (0xFFD00000UL) /*Shima */
#endif

#define __CHECK__

#define CAN_ENABLE                      1U
#define CAN_DISABLE                     0U

/* ---- Channel number ---- */
#define USE_CH_NUM                      1

/* ---- Global setting ---- */
#define CAN_CFG_TX_PRIORITY             CAN_TX_ID_FIRST
#define CAN_CFG_DLC_CHECK               CAN_ENABLE
#define CAN_CFG_DLC_REPLACE             CAN_ENABLE
#define CAN_CFG_MIRROR                  CAN_DISABLE
#define CAN_CFG_CLOCK                   CAN_SOURCE_PCLOCK_PLL2
#define CAN_CFG_TS_CLOCK                CAN_TS_CAN0_BT_CLOCK
#define CAN_CFG_TS_PR                   CAN_TS_NO_DIV
#define CAN_CFG_IT_PR                   0U
#define CAN_CFG_PL_OV_MODE              CAN_PL_NO_STORED

#define CAN_CFG_HISTORY_OVERFLOW_IE     CAN_DISABLE
#define CAN_CFG_MSG_LOST_IE             CAN_DISABLE
#define CAN_CFG_DLC_ERROR_IE            CAN_DISABLE
#define CAN_CFG_PAYLOAD_OVERFLOW_IE     CAN_DISABLE

/* ---- Rx rule ---- */
#define CAN_RX_RULE_NUM_CH0             (0U)
#define CAN_RX_RULE_NUM_CH1             (0U)
#define CAN_RX_RULE_NUM_CH2             (0U)
#define CAN_RX_RULE_NUM_CH3             (0U)
#define CAN_RX_RULE_NUM_CH4             (0U)
#define CAN_RX_RULE_NUM_CH5             (0U)
#define CAN_RX_RULE_NUM_CH6             (0U)
#define CAN_RX_RULE_NUM_CH7             (0U)
#define CAN_RX_RULE_NUM                 (0U)

/* ---- Rx buffer ---- */
#define CAN_CFG_RBSIZE                  CAN_RBSIZE_8BYTE
#define CAN_CFG_RBNUM                   (0x0U)

/* ---- RxFIFO ---- */
#define CAN_CFG_RXFIFO0                 0x0UL
#define CAN_CFG_RXFIFO1                 0x0UL
#define CAN_CFG_RXFIFO2                 0x0UL
#define CAN_CFG_RXFIFO3                 0x0UL
#define CAN_CFG_RXFIFO4                 0x0UL
#define CAN_CFG_RXFIFO5                 0x0UL
#define CAN_CFG_RXFIFO6                 0x0UL
#define CAN_CFG_RXFIFO7                 0x0UL

/* ---- Register value ---- */
#define CAN_CFG_GLB_CFG \
    CAN_CFG_GCFG(CAN_CFG_TX_PRIORITY, \
                 CAN_CFG_DLC_CHECK, CAN_CFG_DLC_REPLACE, \
                 CAN_CFG_MIRROR, CAN_CFG_CLOCK, \
                 CAN_CFG_TS_CLOCK, CAN_CFG_PL_OV_MODE, \
                 CAN_CFG_TS_PR, CAN_CFG_IT_PR)

#define CAN_CFG_GLB_ERR_INT \
    CAN_CFG_GCTR(CAN_CFG_PAYLOAD_OVERFLOW_IE, CAN_CFG_HISTORY_OVERFLOW_IE, \
                 CAN_CFG_MSG_LOST_IE, CAN_CFG_DLC_ERROR_IE)

#define CAN_CFG_RBUFF \
    CAN_CFG_RMNB(CAN_CFG_RBSIZE, \
                 CAN_CFG_RBNUM)

#if MAX_CH_NUM == 1
#define CAN_CFG_RN0   (CAN_RX_RULE_NUM_CH0 << 16)

#elif MAX_CH_NUM == 2
#define CAN_CFG_RN0  ((CAN_RX_RULE_NUM_CH0 << 16) | \
                      (CAN_RX_RULE_NUM_CH1 << 0))

#elif MAX_CH_NUM == 3
#define CAN_CFG_RN0  ((CAN_RX_RULE_NUM_CH0 << 16) | \
                      (CAN_RX_RULE_NUM_CH1 << 0))
#define CAN_CFG_RN1   (CAN_RX_RULE_NUM_CH2 << 16)

#elif MAX_CH_NUM == 4
#define CAN_CFG_RN0  ((CAN_RX_RULE_NUM_CH0 << 16) | \
                      (CAN_RX_RULE_NUM_CH1 << 0))
#define CAN_CFG_RN1  ((CAN_RX_RULE_NUM_CH2 << 16) | \
                      (CAN_RX_RULE_NUM_CH3 << 0))

#elif MAX_CH_NUM == 5
#define CAN_CFG_RN0  ((CAN_RX_RULE_NUM_CH0 << 16) | \
                      (CAN_RX_RULE_NUM_CH1 << 0))
#define CAN_CFG_RN1  ((CAN_RX_RULE_NUM_CH2 << 16) | \
                      (CAN_RX_RULE_NUM_CH3 << 0))
#define CAN_CFG_RN2   (CAN_RX_RULE_NUM_CH4 << 16)

#elif MAX_CH_NUM == 6
#define CAN_CFG_RN0  ((CAN_RX_RULE_NUM_CH0 << 16) | \
                      (CAN_RX_RULE_NUM_CH1 << 0))
#define CAN_CFG_RN1  ((CAN_RX_RULE_NUM_CH2 << 16) | \
                      (CAN_RX_RULE_NUM_CH3 << 0))
#define CAN_CFG_RN2  ((CAN_RX_RULE_NUM_CH4 << 16) | \
                      (CAN_RX_RULE_NUM_CH5 << 0))

#elif MAX_CH_NUM == 7
#define CAN_CFG_RN0  ((CAN_RX_RULE_NUM_CH0 << 16) | \
                      (CAN_RX_RULE_NUM_CH1 << 0))
#define CAN_CFG_RN1  ((CAN_RX_RULE_NUM_CH2 << 16) | \
                      (CAN_RX_RULE_NUM_CH3 << 0))
#define CAN_CFG_RN2  ((CAN_RX_RULE_NUM_CH4 << 16) | \
                      (CAN_RX_RULE_NUM_CH5 << 0))
#define CAN_CFG_RN3   (CAN_RX_RULE_NUM_CH6 << 16)

#elif MAX_CH_NUM == 8
#define CAN_CFG_RN0  ((CAN_RX_RULE_NUM_CH0 << 16) | \
                      (CAN_RX_RULE_NUM_CH1 << 0))
#define CAN_CFG_RN1  ((CAN_RX_RULE_NUM_CH2 << 16) | \
                      (CAN_RX_RULE_NUM_CH3 << 0))
#define CAN_CFG_RN2  ((CAN_RX_RULE_NUM_CH4 << 16) | \
                      (CAN_RX_RULE_NUM_CH5 << 0))
#define CAN_CFG_RN3  ((CAN_RX_RULE_NUM_CH6 << 16) | \
                      (CAN_RX_RULE_NUM_CH7 << 0))

#endif

#endif

