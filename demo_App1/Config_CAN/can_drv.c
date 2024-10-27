/******************************************************************************* 
* File Name    : can_drv.c 
* Version	    : 1.11
* Device(s) 	: RH850/U2A
* Description  : This is source file for CAN driver code.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
* : 31.10.2020 	1.00 	First Release
* : 30.06.2022 	1.10 	Modified for RH850/U2A6
* : 30.06.2022 	1.11 	Modified for RH850/U2A8
******************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "can_drv.h"
#include "can_sfr.h"
#include "iodefine.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/

#define CAN_FIFO_PTR_INC                    0xffUL

#define CAN_PAGE_RX_RULE_IDX_MASK           0xfU
#define CAN_RX_RULE_PAGE_IDX_BIT_POS        4U

#define CAN_8_BITS_MASK                     0x000000FFUL


/*****************************************************************************
 Private variables and functions
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/

/****************************************************************************** 
* Function Name: R_Can_Init
* Description  : Initialize CAN controller after reset
* Arguments    : none 
* Return Value : CAN_RTN_OK - 
*                    normal completion
*                CAN_RTN_RAM_INIT -
*                    CAN RAM initializing
*                CAN_RTN_MODE_WAIT -
*                    wait to change global mode or channel mode
******************************************************************************/
Can_RtnType R_CAN_Init(void)
{
    uint8_t ch_idx;

    const can_ch_cfg_t * p_cfg;
    const can_ch_cfg_t * p_top_cfg;

    volatile can_ch_sfr1_t * ptr_sfr1;
	volatile can_ch_sfr2_t * ptr_sfr2;

    /* ==== CAN RAM initialization ==== */
    while((RSCFDnCFDGSTS & CAN_RAM_INIT_BIT_ON) != 0U);

    /* ==== global mode switch (stop->reset) ==== */
    if ((RSCFDnCFDGSTS & CAN_GLB_STP_STS_BIT_ON) != 0U)
    {
        /* exit global stop mode */
        RSCFDnCFDGCTR &= (uint32_t)~(CAN_GLB_STP_BIT_ON);
        while((RSCFDnCFDGSTS & CAN_GLB_STP_STS_BIT_ON) != 0U);
    }
	
	/* ==== Classical CAN mode-> CANFD mode ==== */
//    RSCFD0.CFDGRMCFG.UINT32 = 0x00000001;

    /* ==== channel mode switch ==== */
    ptr_sfr1 = (volatile can_ch_sfr1_t *)&RSCFDnCFDCmNCFG(4);
    for (ch_idx = 0; ch_idx < MAX_CH_NUM; ch_idx++)
    {
        if (g_ch_use_table[ch_idx] != CAN_NOUSE)
        {
            /* --- switch from channel stop mode ---- */
            if ((ptr_sfr1->CFDCmSTS & CAN_STP_STS_BIT_ON) != 0U)
            {
                /* exit channel stop mode */
                ptr_sfr1->CFDCmCTR &= (uint32_t)~CAN_STP_BIT_ON;
                while((ptr_sfr1->CFDCmSTS & CAN_STP_STS_BIT_ON) != 0U);
            }
        }
        ptr_sfr1++;
    }

    /* configuration table */
    p_top_cfg = &g_can_ch_cfg[4];

    /* ==== global function setting ==== */
    RSCFDnCFDGCFG = CAN_CFG_GLB_CFG;

    /* ==== communication speed setting ==== */
    ptr_sfr1 = (volatile can_ch_sfr1_t *)&RSCFDnCFDCmNCFG(4);
	ptr_sfr2 = (volatile can_ch_sfr2_t *)&RSCFDnCFDCmDCFG(4);
    p_cfg = p_top_cfg;
    for (ch_idx = 0; ch_idx < MAX_CH_NUM; ch_idx++)
    {
        if (g_ch_use_table[ch_idx] != CAN_NOUSE)
        {
            ptr_sfr1->CFDCmNCFG = p_cfg->nbr_cfg;
            ptr_sfr2->CFDCmDCFG = p_cfg->dbr_cfg;
            ptr_sfr2->CFDCmFDCFG = p_cfg->ch_canfd_cfg;
            p_cfg++;
        }
        ptr_sfr1++;
    	ptr_sfr2++;
    }

    /* ==== Rx rule setting ==== */
#if CAN_RX_RULE_NUM > 0
    {
        volatile uint32_t * ptr_reg;

        uint16_t rxrule_idx;

        /* ---- Set Rx rule number per channel ---- */

        RSCFDnCFDGAFLCFGw(0) = CAN_CFG_RN0;
#if MAX_CH_NUM > 2
        RSCFDnCFDGAFLCFGw(1) = CAN_CFG_RN1;
#endif
#if MAX_CH_NUM > 4
        RSCFDnCFDGAFLCFGw(2) = CAN_CFG_RN2;
#endif
#if MAX_CH_NUM > 6
        RSCFDnCFDGAFLCFGw(3) = CAN_CFG_RN3;
#endif

        /* ---- Rx rule write enable. ---- */
        RSCFDnCFDGAFLECTR = CAN_RX_RULE_WRT_EN_BIT_ON;

        /* ---- Copy Rx rule one by one ---- */
        ptr_reg = &RSCFDnCFDGAFLIDj(0);
        for (rxrule_idx = 0U; rxrule_idx < CAN_RX_RULE_NUM; rxrule_idx++)
        {
            /* Update target Rx rule page if necessary */
            if ((rxrule_idx & CAN_PAGE_RX_RULE_IDX_MASK) == 0U)
            {
                RSCFDnCFDGAFLECTR = CAN_RX_RULE_WRT_EN_BIT_ON |
                                (rxrule_idx >> CAN_RX_RULE_PAGE_IDX_BIT_POS);
                ptr_reg = &RSCFDnCFDGAFLIDj(0);
            }

            /* Set a single Rx rule */
            *(ptr_reg++) = g_rxrule_table[rxrule_idx][0];	/* GAFLID */
            *(ptr_reg++) = g_rxrule_table[rxrule_idx][1];	/* GAFLM */
            *(ptr_reg++) = g_rxrule_table[rxrule_idx][2];	/* GAFLP0 */
            *(ptr_reg++) = g_rxrule_table[rxrule_idx][3];	/* GAFLP1 */
        }

        /* ---- Rx rule write disable ---- */
        RSCFDnCFDGAFLECTR = 0x0UL;
    }
#endif /* CAN_RX_RULE_NUM > 0 */

    /* ==== buffer setting ==== */
    /* ---- Set Rx buffer number ---- */
    RSCFDnCFDRMNB = CAN_CFG_RBUFF;

    /* ---- Set Rx FIFO buffer ---- */
    RSCFDnCFDRFCCx(0) = CAN_CFG_RXFIFO0;
    RSCFDnCFDRFCCx(1) = CAN_CFG_RXFIFO1;
    RSCFDnCFDRFCCx(2) = CAN_CFG_RXFIFO2;
    RSCFDnCFDRFCCx(3) = CAN_CFG_RXFIFO3;
    RSCFDnCFDRFCCx(4) = CAN_CFG_RXFIFO4;
    RSCFDnCFDRFCCx(5) = CAN_CFG_RXFIFO5;
    RSCFDnCFDRFCCx(6) = CAN_CFG_RXFIFO6;
    RSCFDnCFDRFCCx(7) = CAN_CFG_RXFIFO7;

    {
        volatile uint32_t * p_CFCCk;
        volatile uint16_t * p_TMIEC;
        volatile uint32_t * p_TXQCCm;

        p_cfg    = p_top_cfg;
        p_CFCCk  = &RSCFDnCFDCFCCk(4, 0);
        p_TMIEC  = &RSCFDnCFDTMIECy(4);
        p_TXQCCm = &RSCFDnCFDTXQCC0m(4);
        for (ch_idx = 0U; ch_idx < MAX_CH_NUM; ch_idx++)
        {
            if (g_ch_use_table[ch_idx] != CAN_NOUSE)
            {
                /* ---- Tx/Rx FIFO buffer ---- */
                *(p_CFCCk    ) = p_cfg->tr0_cfg;
                *(p_CFCCk + 1) = p_cfg->tr1_cfg;
                *(p_CFCCk + 2) = p_cfg->tr2_cfg;

                /* ---- Tx buffer transmission complete interrupt ---- */
                *(p_TMIEC) = p_cfg->tb_int_cfg;

                /* ---- Tx queue ---- */
                *(p_TXQCCm) = p_cfg->tq_cfg;

                p_cfg++;
            }
            p_CFCCk += 3;
            p_TMIEC++;
            p_TXQCCm++;
        }
    }

    /* ==== global error interrupt setting ==== */
    RSCFDnCFDGCTR = (RSCFDnCFDGCTR & (CAN_GLB_STP_BIT_ON | CAN_GLB_MODE_BITS_ON)) +
                        CAN_CFG_GLB_ERR_INT;

    /* ==== channel function setting ==== */
    ptr_sfr1 = (volatile can_ch_sfr1_t *)&RSCFDnCFDCmNCFG(4);
    p_cfg = p_top_cfg;
    for (ch_idx = 0; ch_idx < MAX_CH_NUM; ch_idx++)
    {
        if (g_ch_use_table[ch_idx] != CAN_NOUSE)
        {
            ptr_sfr1->CFDCmCTR = (ptr_sfr1->CFDCmCTR &
                                  (CAN_GLB_STP_STS_BIT_ON | CAN_MODE_BITS_ON))
                                 + p_cfg->ch_func;
            p_cfg++;
        }
        ptr_sfr1++;
    }

    return CAN_RTN_OK;
}

/****************************************************************************** 
* Function Name: R_CAN_GlobalStart
* Description  : Start global operation
* Arguments    : none 
* Return Value : CAN_RTN_OK -
*                    normal completion
*                CAN_RTN_MODE_WAIT -
*                    wait to change global mode
******************************************************************************/
Can_RtnType R_CAN_GlobalStart(void)
{
    const uint8_t * p_use_value;

    /* ==== switch to global operation mode from global reset mode ==== */
    if ((RSCFDnCFDGSTS & CAN_GLB_RST_STS_BIT_ON) != 0U)
    {
        RSCFDnCFDGCTR = (RSCFDnCFDGCTR & (uint32_t)~CAN_GLB_MODE_BITS_ON) |
                    CAN_GLB_OPERATION_MODE;
	    while((RSCFDnCFDGSTS & CAN_GLB_RST_STS_BIT_ON) != 0U);
    }

    /* ==== Global error ==== */
    RSCFDnCFDGERFL = 0x0UL;

    /* ==== enable reception FIFO ==== */
    {
        volatile uint32_t * p_RFCCm;
        uint8_t  rxfifo_idx;

        p_RFCCm = &RSCFDnCFDRFCCx(4);
        p_use_value = &g_rxfifo_use_table[0];
        for (rxfifo_idx = 0; rxfifo_idx < CAN_MAX_RXFIFO_NUM; rxfifo_idx++)
        {
            if (*(p_use_value) != CAN_NOUSE)
            {
                *(p_RFCCm) |= CAN_RFIFO_EN_BIT_ON;
            }
            p_RFCCm++;
            p_use_value++;
        }
    }

    /* ==== Tx/Rx FIFO setting ==== */
    {
        volatile uint32_t * p_CFCCk;
        uint8_t ch_idx;
        uint8_t trfifo_idx;

        p_CFCCk = &RSCFDnCFDCFCCk(4, 0);
        p_use_value = &g_trfifo_use_table[4][0];
        for (ch_idx = 0U; ch_idx < MAX_CH_NUM; ch_idx++)
        {
            if (g_ch_use_table[ch_idx] != CAN_NOUSE)
            {
                for (trfifo_idx = 0; trfifo_idx < CAN_MAX_TRFIFO_NUM;
                                         trfifo_idx++)
                {
                    /* ---- enable Tx/Rx FIFO (Rx mode) ---- */
                    if (*(p_use_value) == CAN_USE_RX_MODE)
                    {
                        *(p_CFCCk) |= CAN_TRFIFO_EN_BIT_ON;
                    }
                    p_use_value++;
                    p_CFCCk++;
                }
            }
            else
            {
                p_CFCCk += CAN_MAX_TRFIFO_NUM;
            }
        }
    }

    return CAN_RTN_OK;
}

/****************************************************************************** 
* Function Name: R_CAN_ChStart 
* Description  : Start channel operation
* Arguments    : ch_idx - 
*                    channel index
* Return Value : CAN_RTN_OK -
*                    normal completion
*                CAN_RTN_MODE_WAIT -
*                    wait to change channel mode
*                CAN_RTN_ARG_ERROR -
*                    invalid argument specification
******************************************************************************/
Can_RtnType R_CAN_ChStart(can_ch_t ch_idx)
{
    uint8_t use_ch_idx;

#if defined(__CHECK__)
    /* ----  Check can channel index ---- */
    if ((ch_idx >= MAX_CH_NUM) ||
        (g_ch_use_table[ch_idx] == CAN_NOUSE))
    {
        return CAN_RTN_ARG_ERROR;
    }
#endif

    /* ---- switch to channel operation mode ---- */
    {
        volatile can_ch_sfr1_t * ptr;

        ptr = (volatile can_ch_sfr1_t *)&RSCFDnCFDCmNCFG(ch_idx);
        if ((ptr->CFDCmSTS & CAN_RST_STS_BIT_ON) != 0U)
        {
            ptr->CFDCmCTR = (ptr->CFDCmCTR & (uint32_t)~CAN_MODE_BITS_ON) |
                                         CAN_MODE_CH_COMM_MODE;
            while((ptr->CFDCmSTS & CAN_RST_STS_BIT_ON) != 0U);
        }
    }

    use_ch_idx = (uint8_t)(g_ch_use_table[ch_idx] & CAN_USE_CH_MASK);

    /* ---- enable Tx/Rx FIFO (Tx mode or gateway mode) ---- */
    {
        volatile uint32_t * p_CFCCk;
        uint32_t trfifo_idx;
        const uint8_t * p_use_value;

        p_CFCCk = &RSCFDnCFDCFCCk(ch_idx, 0);
        p_use_value = &g_trfifo_use_table[use_ch_idx][0];
        for (trfifo_idx = 0; trfifo_idx < CAN_MAX_TRFIFO_NUM; trfifo_idx++)
        {
            if ((*(p_use_value) == CAN_USE_TX_MODE) || 
                (*(p_use_value) == CAN_USE_GW_MODE))
            {
                *(p_CFCCk) |= CAN_TRFIFO_EN_BIT_ON;
            }
            p_use_value++;
            p_CFCCk++;
        }
    }

    /* ---- enable Tx queue ---- */
    if (g_txqueue_use_table[use_ch_idx] != CAN_NOUSE)
    {
        RSCFDnCFDTXQCC0m(ch_idx) |= CAN_TXQUEUE_EN_BIT_ON;
    }

    return CAN_RTN_OK;
}

/****************************************************************************** 
* Function Name: R_CAN_TrmByTxBuf
* Description  : Transmit a frame by Tx buffer
* Arguments    : ch_idx -
*                    channel index
*                txbuf_idx -
*                    Tx buffer index
*                pFrame -
*                    pointer to frame to be transmitted
* Return Value : CAN_RTN_OK -
*                    normal completion
*                CAN_RTN_STS_ERROR -
*                    failure to clear Tx buffer status
*                CAN_RTN_ARG_ERROR -
*                    invalid argument specification
******************************************************************************/
Can_RtnType R_CAN_TrmByTxBuf(can_ch_t ch_idx, can_txbuf_t txbuf_idx,
                             const can_frame_t * pFrame)
{
#if defined(__CHECK__)
    /* ----  Check can channel index ---- */
    if ((ch_idx >= MAX_CH_NUM) ||
        (g_ch_use_table[ch_idx] == CAN_NOUSE))
    {
        return CAN_RTN_ARG_ERROR;
    }

    /* ----  Check Tx buffer index ---- */
    if (txbuf_idx >= CAN_MAX_TXBUF_NUM)
    {
        return CAN_RTN_ARG_ERROR;
    }
#endif

    /* ---- Clear Tx buffer status ---- */
    {
        volatile uint8_t  * p_TMSTSp;

        p_TMSTSp = &(RSCFDnCFDTMSTSp(ch_idx, txbuf_idx));
        *p_TMSTSp = 0x0U;
        if (*p_TMSTSp != 0x0U)
        {
            return CAN_RTN_STS_ERROR;
        }
    }

    /* ---- Store message to tx buffer ---- */
    {
        volatile uint32_t * p_CiTBp;
        uint32_t *p_data;
        uint32_t i, loop_cnt;

    	p_CiTBp = &(RSCFDnCFDTMID(ch_idx, txbuf_idx));
        p_data = (uint32_t *)pFrame;
		loop_cnt = rcan_tr_data_cnt((uint32_t)pFrame->DLC);
        *(p_CiTBp++) = *(p_data++);
        *(p_CiTBp++) = *(p_data++);
        *(p_CiTBp++) = *(p_data++);
    	for (i = 0; i < loop_cnt; i++)
    	{
	    	*(p_CiTBp++) = *(p_data++);
    	}
    }

    /* ---- Set transmission request ---- */
    RSCFDnCFDTMCp(ch_idx, txbuf_idx) = CAN_TXBUF_TRM_BIT_ON;
    
    return CAN_RTN_OK;
}

/****************************************************************************** 
* Function Name: R_CAN_AbortTrm
* Description  : Abort a CAN transmission
* Arguments    : ch_idx -
*                    channel index
*                txbuf_idx -
*                    Tx buffer index
* Return Value : CAN_RTN_OK -
*                    normal completion
*                CAN_RTN_ARG_ERROR -
*                    invalid argument specification
******************************************************************************/
Can_RtnType R_CAN_AbortTrm(can_ch_t ch_idx, can_txbuf_t txbuf_idx)
{
#if defined(__CHECK__)
    /* ----  Check can channel index ---- */
    if ((ch_idx >= MAX_CH_NUM) ||
        (g_ch_use_table[ch_idx] == CAN_NOUSE))
    {
        return CAN_RTN_ARG_ERROR;
    }

    /* ----  Check Tx buffer index ---- */
    if (txbuf_idx >= CAN_MAX_TXBUF_NUM)
    {
        return CAN_RTN_ARG_ERROR;
    }
#endif

    /* ---- Set transmission abort request ---- */
    RSCFDnCFDTMCp(ch_idx, txbuf_idx) |= CAN_TXBUF_ABT_BIT_ON;

    return CAN_RTN_OK;
}

/****************************************************************************** 
* Function Name: R_CAN_CheckTxBufResult
* Description  : Read the result of transmission from Tx buffer
* Arguments    : ch_idx -
*                    channel index
*                txbuf_idx -
*                    Tx buffer index
* Return Value : CAN_RTN_TRANSMITTING -
*                    Transmission is in progress
*                    or no transmit request is present.
*                CAN_RTN_TX_ABORT_OVER -
*                    Transmit abort has been completed.
*                CAN_RTN_TX_END -
*                    Transmission has been completed
*                    (without transmit abortrequest).
*                CAN_RTN_TX_END_WITH_ABORT_REQ -
*                    Transmission has been completed
*                    (with transmit abort request).
*                CAN_RTN_ARG_ERROR -
*                    invalid argument specification
******************************************************************************/
Can_RtnType R_CAN_CheckTxBufResult(can_ch_t ch_idx, can_txbuf_t txbuf_idx)
{
    Can_RtnType rtn_value;

    volatile uint8_t * p_TMSTSp;

#if defined(__CHECK__)
    /* ----  Check can channel index ---- */
    if ((ch_idx >= MAX_CH_NUM) ||
        (g_ch_use_table[ch_idx] == CAN_NOUSE))
    {
        return CAN_RTN_ARG_ERROR;
    }

    /* ----  Check Tx buffer index ---- */
    if (txbuf_idx >= CAN_MAX_TXBUF_NUM)
    {
        return CAN_RTN_ARG_ERROR;
    }
#endif

    p_TMSTSp = &(RSCFDnCFDTMSTSp(ch_idx, txbuf_idx));

    rtn_value = (Can_RtnType)((*p_TMSTSp & CAN_TXBUF_RSLT_BITS_ON)
                              >> CAN_TXBUF_RSLT_BITS_POS);

    /* ---- Tx transmission completed/abort? ---- */
    if (rtn_value != CAN_RTN_TRANSMITTING)
    {
        /* Clear Tx buffer status */
        *p_TMSTSp = 0x0U;
    }

    return rtn_value;
}

/****************************************************************************** 
* Function Name: R_CAN_TrmByTRFIFO
* Description  : Transmit a frame by common (Tx/Rx) FIFO
* Arguments    : ch_idx -
*                    channel index
*                trfifo_idx -
*                    Tx/Rx FIFO index
*                pFrame -
*                    pointer to frame to be transmitted
* Return Value : CAN_RTN_OK -
*                    Frame is successfully pushed into FIFO.
*                CAN_RTN_FIFO_FULL -
*                    Specified FIFO is full.
*                CAN_RTN_ARG_ERROR -
*                    invalid argument specification
******************************************************************************/
Can_RtnType R_CAN_TrmByTRFIFO(can_ch_t ch_idx, can_trfifo_t trfifo_idx,
                              const can_frame_t * pFrame)
{
#if defined(__CHECK__)
    /* ----  Check can channel index ---- */
    if ((ch_idx >= MAX_CH_NUM) ||
        (g_ch_use_table[ch_idx] == CAN_NOUSE))
    {
        return CAN_RTN_ARG_ERROR;
    }

    /* ----  Check Tx/Rx FIFO index ---- */
    {
        uint8_t  use_ch_idx;
        use_ch_idx = (uint8_t)(g_ch_use_table[ch_idx] & CAN_USE_CH_MASK);
        if ((trfifo_idx >= CAN_MAX_TRFIFO_NUM) ||
            (g_trfifo_use_table[use_ch_idx][trfifo_idx] != CAN_USE_TX_MODE))
        {
            return CAN_RTN_ARG_ERROR;
        }
    }
#endif

    /* ---- Return if Tx/Rx FIFO is full ---- */
    if ((RSCFDnCFDCFSTSk(ch_idx, trfifo_idx) & CAN_TRFIFO_FULL_BIT_ON) != 0)
    {
        return CAN_RTN_FIFO_FULL;
    }

    /* ---- Send message into Tx/Rx FIFO if it is not full ---- */
    {
        volatile uint32_t *p_CiTRFAk;
        uint32_t *p_data;
        uint32_t i, loop_cnt;

        p_CiTRFAk = &(RSCFDnCFDCFID(ch_idx, trfifo_idx));
		loop_cnt = rcan_tr_data_cnt((uint32_t)pFrame->DLC);
        p_data = (uint32_t *)pFrame;
        *(p_CiTRFAk++) = *(p_data++);
        *(p_CiTRFAk++) = *(p_data++);
        *(p_CiTRFAk++) = *(p_data++);
    	for (i = 0; i < loop_cnt; i++)
    	{
	    	*(p_CiTRFAk++) = *(p_data++);
    	}
    }

    /* ---- Increment Tx/Rx FIFO buffer pointer ---- */
    RSCFDnCFDCFPCTRk(ch_idx, trfifo_idx) = CAN_FIFO_PTR_INC;

	return CAN_RTN_OK;
}

/****************************************************************************** 
* Function Name: R_CAN_TrmByTxQueue
* Description  : Transmit a frame by Tx queue
* Arguments    : ch_idx -
*                    channel index
*                pFrame -
*                    pointer to frame to be transmitted
* Return Value : CAN_RTN_OK -
*                    Frame is successfully pushed into queue.
*                CAN_RTN_FIFO_FULL -
*                    Specified queue is full.
*                CAN_RTN_ARG_ERROR -
*                    invalid argument specification
******************************************************************************/
Can_RtnType R_CAN_TrmByTxQueue(can_ch_t ch_idx, const can_frame_t * pFrame)
{
#if defined(__CHECK__)
    /* ----  Check can channel index ---- */
    if ((ch_idx >= MAX_CH_NUM) ||
        (g_ch_use_table[ch_idx] == CAN_NOUSE))
    {
        return CAN_RTN_ARG_ERROR;
    }

    /* ----  Check Tx queue index ---- */
    {
        uint8_t  use_ch_idx;
        use_ch_idx = (uint8_t)(g_ch_use_table[ch_idx] & CAN_USE_CH_MASK);
        if (g_txqueue_use_table[use_ch_idx] == CAN_NOUSE)
        {
            return CAN_RTN_ARG_ERROR;
        }
    }

#endif

    /* ---- Return if Tx queue is full ---- */
    if ((RSCFDnCFDTXQSTS0m(ch_idx) & CAN_TXQUEUE_FULL_BIT_ON) != 0)
    {
        return CAN_RTN_FIFO_FULL;
    }

    /* ---- Send message into Tx queue if it is not full ---- */
    {
        volatile uint32_t *p_CiTB15;
        uint32_t *p_data;
        uint32_t i, loop_cnt;

        p_CiTB15 = &RSCFDnCFDTMID15(ch_idx);
        p_data = (uint32_t *)pFrame;
		loop_cnt = rcan_tr_data_cnt((uint32_t)pFrame->DLC);
        *(p_CiTB15++) = *(p_data++);
        *(p_CiTB15++) = *(p_data++);
        *(p_CiTB15++) = *(p_data++);
    	for (i = 0; i < loop_cnt; i++)
    	{
	    	*(p_CiTB15++) = *(p_data++);
    	}
    }

    /* ---- Increment transmission queue pointer ---- */
    RSCFDnCFDTXQPCTR0m(ch_idx) = CAN_FIFO_PTR_INC;

    return CAN_RTN_OK;
}

/****************************************************************************** 
* Function Name: R_CAN_ReadRxBuffer
* Description  : Read message from Rx buffer
* Arguments    : p_rxbuf_idx -
*                    pointer to Rx buffer that receives frame
*                pFrame -
*                    pointer to stored frame position
* Return Value : CAN_RTN_OK -
*                    A frame is successfully read out.
*                CAN_RTN_BUFFER_EMPTY -
*                    No frame is read out.
*                CAN_RTN_STS_ERROR -
*                    failure to clear Rx complete flag
*                CAN_RTN_OVERWRITE -
*                    A frame is overwritten.
******************************************************************************/
Can_RtnType R_CAN_ReadRxBuffer(uint8_t * p_rxbuf_idx, can_frame_t * pFrame)
{
    uint8_t  buf_idx;
    uint8_t  rb_idx;
    uint8_t  ch_idx;
    uint16_t temp_rbrcf;
    uint16_t pattern;

    volatile uint16_t * p_RMND;

    /* ---- Judge if new messages are available ---- */
    rb_idx = 0xFF;
    p_RMND = &RSCFDnCFDRMNDy(0);
    for (ch_idx = 0U; ch_idx < MAX_CH_NUM; ch_idx++)
    {
        temp_rbrcf = *(p_RMND);
        if (temp_rbrcf != 0U)
        {
            rb_idx = ch_idx;
            break;
        }
        p_RMND++;
    }

    if (temp_rbrcf == 0)
    {
        return CAN_RTN_BUFFER_EMPTY;
    }

    /* ---- Get Rx buffer that has new message ---- */
    if (temp_rbrcf != 0)
    {
        pattern = 1;
        for (buf_idx = 0U; buf_idx < 16U; ++buf_idx)
        {
            if ((temp_rbrcf & pattern) != 0)
            {
                *p_rxbuf_idx = buf_idx + (rb_idx * 16);
                break;
            }
            pattern <<= 1;
        }
    }

    /* ---- Clear Rx complete flag of corresponding Rx buffer ---- */
    *p_RMND &= (uint16_t)~pattern;
    if ((*p_RMND & pattern) != 0)
    {
        return CAN_RTN_STS_ERROR;
    }

    /* ---- Read out message from Rx buffer ---- */
    {
        volatile uint32_t *p_CRBn;
        uint32_t *p_data;
        uint32_t i, loop_cnt;

        p_CRBn = &(RSCFDnCFDRMID((*p_rxbuf_idx)));
        p_data = (uint32_t *)pFrame;
        *(p_data++) = *(p_CRBn++);
        *(p_data++) = *(p_CRBn++);
        *(p_data++) = *(p_CRBn++);
    	loop_cnt = rcan_tr_data_cnt((uint32_t)pFrame->DLC);
    	for (i = 0; i < loop_cnt; i++)
    	{
	        *(p_data++) = *(p_CRBn++);
    	}
    }

    /* ---- Judge if current message is overwritten ---- */
    if ((*p_RMND & pattern) != 0)
    {
        return CAN_RTN_OVERWRITE;
    }

    return CAN_RTN_OK;
}

/****************************************************************************** 
* Function Name: R_CAN_ReadRxFIFO
* Description  : Read message from Rx FIFO
* Arguments    : rxfifo_idx -
*                    Rx FIFO index
*                pFrame -
*                    pointer to stored frame position
* Return Value : CAN_RTN_OK -
*                    A frame is successfully read out.
*                CAN_RTN_OK_WITH_LOST -
*                    A frame is successfully read out (with message lost).
*                CAN_RTN_BUFFER_EMPTY -
*                    No frame is read out.
*                CAN_RTN_ARG_ERROR -
*                    invalid argument specification
******************************************************************************/
Can_RtnType R_CAN_ReadRxFIFO(can_rxfifo_t rxfifo_idx, can_frame_t * pFrame)
{
    uint32_t    temp_status;
    Can_RtnType rtn_value;

    volatile uint32_t * ptr_reg;

#if defined(__CHECK__)
    /* ----  Check Rx FIFO index ---- */
    if ((rxfifo_idx >= CAN_MAX_RXFIFO_NUM) ||
        (g_rxfifo_use_table[rxfifo_idx] == CAN_NOUSE))
    {
        return CAN_RTN_ARG_ERROR;
    }
#endif

    /* ----  Check if any unread message is available in Rx FIFO ---- */
    temp_status = RSCFDnCFDRFSTSx(rxfifo_idx);
    if ((temp_status & CAN_RFIFO_EMPTY_BIT_ON) != 0)
    {
        return CAN_RTN_BUFFER_EMPTY;
    }

    /* ----  Set return value ---- */
    rtn_value = CAN_RTN_OK;

    /* ---- Check if Rx FIFO has message lost ---- */
    if ((temp_status & CAN_RFIFO_MSGLST_BIT_ON) != 0)
    {
        /* ---- Clear message lost flag ---- */
        RSCFDnCFDRFSTSx(rxfifo_idx) = CAN_CLR_WITHOUT_RX_INT;

        /* ----  Set return value ---- */
        rtn_value = CAN_RTN_OK_WITH_LOST;
    }

    /* ---- Read out message from Rx FIFO ---- */
    {
        uint32_t *p_data;
        uint32_t i, loop_cnt;

        ptr_reg = &(RSCFDnCFDRFID(rxfifo_idx));
        p_data = (uint32_t *)pFrame;
        *(p_data++) = *(ptr_reg++);
        *(p_data++) = *(ptr_reg++);
        *(p_data++) = *(ptr_reg++);
    	loop_cnt = rcan_tr_data_cnt((uint32_t)pFrame->DLC);
    	for (i = 0; i < loop_cnt; i++)
    	{
	        *(p_data++) = *(ptr_reg++);
    	}
    }

    /* ---- Increment Rx FIFO buffer pointer ---- */
    RSCFDnCFDRFPCTRx(rxfifo_idx) = CAN_FIFO_PTR_INC;

    return rtn_value;
}

/****************************************************************************** 
* Function Name: R_CAN_ReadTRFIFO
* Description  : Read message from common (Tx/Rx) FIFO
* Arguments    : ch_idx -
*                    channel index
*                trfifo_idx -
*                    common (Tx/Rx) FIFO index
*                pFrame -
*                    pointer to stored frame position
* Return Value : CAN_RTN_OK -
*                    A frame is successfully read out.
*                CAN_RTN_OK_WITH_LOST -
*                    A frame is successfully read out (with message lost).
*                CAN_RTN_BUFFER_EMPTY -
*                    No frame is read out.
*                CAN_RTN_ARG_ERROR -
*                    invalid argument specification
******************************************************************************/
Can_RtnType R_CAN_ReadTRFIFO(can_ch_t ch_idx, can_trfifo_t trfifo_idx,
                             can_frame_t * pFrame)
{
    uint32_t    temp_ctrfsr;
    Can_RtnType rtn_value;

    volatile uint32_t * ptr_reg;

#if defined(__CHECK__)
    /* ----  Check can channel index ---- */
    if ((ch_idx >= MAX_CH_NUM) ||
        (g_ch_use_table[ch_idx] == CAN_NOUSE))
    {
        return CAN_RTN_ARG_ERROR;
    }

    /* ----  Check common (Tx/Rx) FIFO index ---- */
    {
        uint8_t  use_ch_idx;
        use_ch_idx = (uint8_t)(g_ch_use_table[ch_idx] & CAN_USE_CH_MASK);
        if ((trfifo_idx >= CAN_MAX_TRFIFO_NUM) ||
            (g_trfifo_use_table[use_ch_idx][trfifo_idx] != CAN_USE_RX_MODE))
        {
            return CAN_RTN_ARG_ERROR;
        }
    }
#endif

    /* ----  Check if any unread message is available in common (Tx/Rx) FIFO ---- */
    temp_ctrfsr = RSCFDnCFDCFSTSk(ch_idx, trfifo_idx);
    if ((temp_ctrfsr & CAN_TRFIFO_EMPTY_BIT_ON) != 0)
    {
        return CAN_RTN_BUFFER_EMPTY;
    }

    /* ----  Set return value ---- */
    rtn_value = CAN_RTN_OK;

    /* ---- Check if common (Tx/Rx) FIFO has message lost ---- */
    if ((temp_ctrfsr & CAN_TRFIFO_MSGLST_BIT_ON) != 0)
    {
        /* ---- Clear message lost flag ---- */
        RSCFDnCFDCFSTSk(ch_idx, trfifo_idx) = CAN_CLR_WITHOUT_TX_RX_INT;

        /* ----  Set return value ---- */
        rtn_value = CAN_RTN_OK_WITH_LOST;
    }

    /* ---- Read out message from common (Tx/Rx) FIFO ---- */
    {
        uint32_t *p_data;
        uint32_t i, loop_cnt;

    	ptr_reg = &(RSCFDnCFDCFID(ch_idx, trfifo_idx));
        p_data = (uint32_t *)pFrame;
        *(p_data++) = *(ptr_reg++);
        *(p_data++) = *(ptr_reg++);
        *(p_data++) = *(ptr_reg++);
    	loop_cnt = rcan_tr_data_cnt((uint32_t)pFrame->DLC);
    	for (i = 0; i < loop_cnt; i++)
    	{
	        *(p_data++) = *(ptr_reg++);
    	}
    }

    /* ---- Increment common (Tx/Rx) FIFO buffer pointer ---- */
    RSCFDnCFDCFPCTRk(ch_idx, trfifo_idx) = CAN_FIFO_PTR_INC;

    return rtn_value;
}

/****************************************************************************** 
* Function Name: R_CAN_ReadChStatus
* Description  : Read channel status
* Arguments    : ch_idx -
*                    channel index
* Return Value : channel status (<= 0xFF) -
*                    normal completion
*                CAN_RTN_ARG_ERROR -
*                    invalid argument specification
******************************************************************************/
Can_RtnType R_CAN_ReadChStatus(can_ch_t ch_idx)
{
    volatile can_ch_sfr1_t * ptr_sfr1;

#if defined(__CHECK__)
    /* ----  Check can channel index ---- */
    if ((ch_idx >= MAX_CH_NUM) ||
        (g_ch_use_table[ch_idx] == CAN_NOUSE))
    {
        return CAN_RTN_ARG_ERROR;
    }
#endif

    ptr_sfr1 = (volatile can_ch_sfr1_t *)&RSCFDnCFDCmNCFG(ch_idx);

    return (Can_RtnType)(ptr_sfr1->CFDCmSTS & CAN_8_BITS_MASK);
}

/****************************************************************************** 
* Function Name: rcan_tr_data_cnt
* Description  : Get Tx/Rx data count
* Arguments    : dlc_data -
*                    DLC value
* Return Value : data Read/Write loop count
******************************************************************************/
int rcan_tr_data_cnt(int dlc_data)
{
	int		loop_cnt;

	switch (dlc_data) {
	case 0x00:
		loop_cnt = 0;
		break;
	case 0x01: case 0x02: case 0x03: case 0x04:
		loop_cnt = 1;
		break;
	case 0x05: case 0x06: case 0x07: case 0x08:
		loop_cnt = 2;
		break;
	case 0x09:
		loop_cnt = 3;
		break;
	case 0x0A:
		loop_cnt = 4;
		break;
	case 0x0B:
		loop_cnt = 5;
		break;
	case 0x0C:
		loop_cnt = 6;
		break;
	case 0x0D:
		loop_cnt = 8;
		break;
	case 0x0E:
		loop_cnt = 12;
		break;
	case 0x0F:
		loop_cnt = 16;
		break;
	}
	return (loop_cnt);
}
