
/******************************************************************************* 
* File Name    : can_sfr.h 
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
#ifndef CAN_SFR_H
#define CAN_SFR_H

#define BIT_ON(x)     (uint32_t)(1 << (x))
#define BITS_2_ON(x)  (uint32_t)(3 << (x))

/*
 * Address
 */
#define CAN_REG8(x)   (*((volatile uint8_t *) (CAN_START_ADDR + (x))))
#define CAN_REG16(x)  (*((volatile uint16_t *)(CAN_START_ADDR + (x))))
#define CAN_REG32(x)  (*((volatile uint32_t *)(CAN_START_ADDR + (x))))
/* ---- Channel ---- */
typedef struct {
    volatile uint32_t CFDCmNCFG;
    volatile uint32_t CFDCmCTR;
    volatile uint32_t CFDCmSTS;
    volatile uint32_t CFDCmERFL;
} can_ch_sfr1_t;

typedef struct {
    volatile uint32_t CFDCmDCFG;
    volatile uint32_t CFDCmFDCFG;
    volatile uint32_t CFDCmFDCTR;
    volatile uint32_t CFDCmFDSTS;
    volatile uint32_t CFDCmFDCRC;
    volatile uint32_t CFDCmBLCT;
    volatile uint32_t CFDCmBLSTS;
	volatile uint32_t dummy;
} can_ch_sfr2_t;

#define RSCFDnCFDCmNCFG(ch)             CAN_REG32(0x0000 + (sizeof(can_ch_sfr1_t) * (ch)))
#define RSCFDnCFDCmDCFG(ch)             CAN_REG32(0x1400 + (sizeof(can_ch_sfr2_t) * (ch)))

/* ---- Global ---- */
#define RSCFDnCFDGCFG                   CAN_REG32(0x0084)
#define RSCFDnCFDGCTR                   CAN_REG32(0x0088)
#define RSCFDnCFDGSTS                   CAN_REG32(0x008C)
#define RSCFDnCFDGERFL                  CAN_REG32(0x0090)
#define RSCFDnCFDGTSC                   CAN_REG32(0x0094)

/* ---- Rx rules ---- */
#define RSCFDnCFDGAFLECTR               CAN_REG32(0x0098)
#define RSCFDnCFDGAFLCFGw(x)            CAN_REG32(0x009C + (0x04 * (x)))

/* ---- Rx buffers ---- */
#define RSCFDnCFDRMNB                   CAN_REG32(0x00AC)
#define RSCFDnCFDRMNDy(ch)              CAN_REG16(0x00B0 + (0x04 * (ch)))

/* ---- Rx FIFO ---- */
#define RSCFDnCFDRFCCx(rxfifo)          CAN_REG32(0x00C0 + (0x04 * (rxfifo)))
#define RSCFDnCFDRFSTSx(rxfifo)         CAN_REG32(0x00E0 + (0x04 * (rxfifo)))
#define RSCFDnCFDRFPCTRx(rxfifo)        CAN_REG32(0x0100 + (0x04 * (rxfifo)))

/* ---- Common (Tx/Rx) FIFO ---- */
#define RSCFDnCFDCFCCk(ch, trfifo)      CAN_REG32(0x0120 + (0x0C * (ch)) + (0x04 * (trfifo)))
#define RSCFDnCFDCFCCEk(ch, trfifo)     CAN_REG32(0x0180 + (0x0C * (ch)) + (0x04 * (trfifo)))
#define RSCFDnCFDCFSTSk(ch, trfifo)     CAN_REG32(0x01E0 + (0x0C * (ch)) + (0x04 * (trfifo)))
#define RSCFDnCFDCFPCTRk(ch, trfifo)    CAN_REG32(0x0240 + (0x0C * (ch)) + (0x04 * (trfifo)))
#define RSCFDnCFDFESTS                  CAN_REG32(0x02A0)
#define RSCFDnCFDFFSTS                  CAN_REG32(0x02A4)
#define RSCFDnCFDFMSTS                  CAN_REG32(0x02A8)
#define RSCFDnCFDRFISTS                 CAN_REG32(0x02AC)
#define RSCFDnCFDCFRISTS                CAN_REG32(0x02B0)
#define RSCFDnCFDCFTISTS                CAN_REG32(0x02B4)
#define RSCFDnCFDCFOFRISTS              CAN_REG32(0x02B8)
#define RSCFDnCFDCFOFTISTS              CAN_REG32(0x02BC)
#define RSCFDnCFDCFMOWSTS               CAN_REG32(0x02C0)
#define RSCFDnCFDFFFSTS                 CAN_REG32(0x02C4)

/* ---- Tx buffers ---- */
#define RSCFDnCFDTMCp(ch, txbuf)        CAN_REG8 (0x02D0 + (0x10 * (ch)) + txbuf)
#define RSCFDnCFDTMSTSp(ch, txbuf)      CAN_REG8 (0x07D0 + (0x10 * (ch)) + txbuf)
#define RSCFDnCFDTMIECy(ch)             CAN_REG16(0x0F50 + (0x02 * (ch)))

/* ---- Tx queue ---- */
#define RSCFDnCFDTXQCC0m(ch)            CAN_REG32(0x1000 + (0x04 * (ch)))
#define RSCFDnCFDTXQSTS0m(ch)           CAN_REG32(0x1020 + (0x04 * (ch)))
#define RSCFDnCFDTXQPCTR0m(ch)          CAN_REG32(0x1040 + (0x04 * (ch)))
#define RSCFDnCFDTXQCC1m(ch)            CAN_REG32(0x1060 + (0x04 * (ch)))
#define RSCFDnCFDTXQSTS1m(ch)           CAN_REG32(0x1080 + (0x04 * (ch)))
#define RSCFDnCFDTXQPCTR1m(ch)          CAN_REG32(0x10A0 + (0x04 * (ch)))
#define RSCFDnCFDTXQCC2m(ch)            CAN_REG32(0x10C0 + (0x04 * (ch)))
#define RSCFDnCFDTXQSTS2m(ch)           CAN_REG32(0x10E0 + (0x04 * (ch)))
#define RSCFDnCFDTXQPCTR2m(ch)          CAN_REG32(0x1100 + (0x04 * (ch)))
#define RSCFDnCFDTXQCC3m(ch)            CAN_REG32(0x1120 + (0x04 * (ch)))
#define RSCFDnCFDTXQSTS3m(ch)           CAN_REG32(0x1130 + (0x04 * (ch)))
#define RSCFDnCFDTXQPCTR3m(ch)          CAN_REG32(0x1160 + (0x04 * (ch)))

/* ---- Test ---- */
#define RSCFDnCFDGTSTCFG                CAN_REG32(0x1308)
#define RSCFDnCFDGTSTCTR                CAN_REG32(0x130C)
#define RSCFDnCFDGLOCKK                 CAN_REG32(0x131C)

/* ---- RAM ---- */
#define RSCFDnCFDGAFLIDj(rxrule)        CAN_REG32(0x1800 + (0x10 * (rxrule)))
#define RSCFDnCFDRMID(buf)              CAN_REG32(0x2000 + (0x80 * (buf)))
#define RSCFDnCFDRFID(rxfifo)           CAN_REG32(0x6000 + (0x80 * (rxfifo)))
#define RSCFDnCFDCFID(ch, trfifo)       CAN_REG32(0x6400 + (0x180 * (ch)) + (0x80 * (trfifo)))
#define RSCFDnCFDTMID(ch, txbuf)        CAN_REG32(0x10000 + (0x2000 * (ch)) + (0x80 * (txbuf)))
#define RSCFDnCFDTMID15(ch)             CAN_REG32(0x10780 + (0x2000 * (ch)))
#define RSCFDnCFDRPGACCr(r)             CAN_REG32(0x8400 + (0x04 * (r)))

/* ==== CAN SFR register bit field position ==== */
/* ---- RSCFDnCFDCmNCFG ---- */
#define CAN_NTSEG2_BIT_POS                          25U
#define CAN_NTSEG1_BIT_POS                          17U
#define CAN_NSJW_BIT_POS                            10U
#define CAN_NBRP_BIT_POS                            0U

#define CAN_CFG_N_BAUDRATE(brp, tseg1, tseg2, sjw)  \
    ( ((tseg2) << CAN_NTSEG2_BIT_POS)               \
    + ((tseg1) << CAN_NTSEG1_BIT_POS)               \
    + ((sjw)   << CAN_NSJW_BIT_POS)                 \
    + ((brp)   << CAN_NBRP_BIT_POS)                 )

/* ---- RSCFDnCFDCmDCFG ---- */
#define CAN_DSJW_BIT_POS                            24U
#define CAN_DTSEG2_BIT_POS                          16U
#define CAN_DTSEG1_BIT_POS                          8U
#define CAN_DBRP_BIT_POS                            0U

#define CAN_CFG_D_BAUDRATE(brp, tseg1, tseg2, sjw)  \
    ( ((sjw)   << CAN_DSJW_BIT_POS)                 \
    + ((tseg2) << CAN_DTSEG2_BIT_POS)               \
    + ((tseg1) << CAN_DTSEG1_BIT_POS)               \
    + ((brp)   << CAN_DBRP_BIT_POS)                 )

/* ---- RSCFDnCFDCmFDCFG ---- */
#define CAN_CLOE_BIT_POS                            30U
#define CAN_REFE_BIT_POS                            29U
#define CAN_FODE_BIT_POS                            28U
#define CAN_GWBRS_BIT_POS                           26U
#define CAN_GWFDF_BIT_POS                           25U
#define CAN_GWEN_BIT_POS                            24U
#define CAN_TDCO_BIT_POS                            16U
#define CAN_ESIC_BIT_POS                            10U
#define CAN_TDCE_BIT_POS                            9U
#define CAN_TDCOC_BIT_POS                           8U
#define CAN_EOCCFG_BIT_POS                          0U

#define CAN_CFG_FDCFG(cloe, refe, fode, gwbrs,      \
                      gwfdf, gwen, tdco, esic,      \
                      tdce, tdcoc, eoccfg)          \
    ( ((cloe)  << CAN_CLOE_BIT_POS)                 \
    + ((refe)  << CAN_REFE_BIT_POS)                 \
    + ((fode)  << CAN_FODE_BIT_POS)                 \
    + ((gwbrs) << CAN_GWBRS_BIT_POS)                \
    + ((gwfdf) << CAN_GWFDF_BIT_POS)                \
    + ((gwen)  << CAN_GWEN_BIT_POS)                 \
    + ((tdco)  << CAN_TDCO_BIT_POS)                 \
    + ((esic)  << CAN_ESIC_BIT_POS)                 \
    + ((tdce)  << CAN_TDCE_BIT_POS)                 \
    + ((tdcoc) << CAN_TDCOC_BIT_POS)                \
    + ((eoccfg) << CAN_EOCCFG_BIT_POS)              )

/* ---- RSCFDnCFDCmCTR ---- */
#define CAN_ROM_BIT_POS                             31U
#define CAN_CRCT_BIT_POS                            30U
#define CAN_CTMS_BIT_POS                            25U
#define CAN_CTME_BIT_POS                            24U
#define CAN_ERRD_BIT_POS                            23U
#define CAN_BOM_BIT_POS                             21U
#define CAN_TDCVFIE_BIT_POS                         19U
#define CAN_SOCOIE_BIT_POS                          18U
#define CAN_EOCOIE_BIT_POS                          17U
#define CAN_TAIE_BIT_POS                            16U
#define CAN_ALIE_BIT_POS                            15U
#define CAN_BLIE_BIT_POS                            14U
#define CAN_OLIE_BIT_POS                            13U
#define CAN_BORIE_BIT_POS                           12U
#define CAN_BOEIE_BIT_POS                           11U
#define CAN_EPIE_BIT_POS                            10U
#define CAN_EWIE_BIT_POS                            9U
#define CAN_BEIE_BIT_POS                            8U
#define CAN_CSLPR_BIT_POS                           2U
#define CAN_CHMDC_BIT_POS                           0U

#define CAN_CFG_FUNC(ie_bus, ie_ew, ie_ep, ie_boe,  \
                     ie_bor, ie_ol, ie_bl, ie_al,   \
                     ie_ta, ie_eo, ie_so, ie_td,    \
                     boff_mode, er_disp)            \
    ( ((ie_bus)    << CAN_BEIE_BIT_POS)             \
    + ((ie_ew)     << CAN_EWIE_BIT_POS)             \
    + ((ie_ep)     << CAN_EPIE_BIT_POS)             \
    + ((ie_boe)    << CAN_BOEIE_BIT_POS)            \
    + ((ie_bor)    << CAN_BORIE_BIT_POS)            \
    + ((ie_ol)     << CAN_OLIE_BIT_POS)             \
    + ((ie_bl)     << CAN_BLIE_BIT_POS)             \
    + ((ie_al)     << CAN_ALIE_BIT_POS)             \
    + ((ie_ta)     << CAN_TAIE_BIT_POS)             \
    + ((ie_eo)     << CAN_EOCOIE_BIT_POS)           \
    + ((ie_so)     << CAN_SOCOIE_BIT_POS)           \
    + ((ie_td)     << CAN_TDCVFIE_BIT_POS)          \
    + ((boff_mode) << CAN_BOM_BIT_POS)              \
    + ((er_disp)   << CAN_ERRD_BIT_POS)             )

#define CAN_SDTST_BIT_ON                BIT_ON(CAN_CTME_BIT_POS)
#define CAN_STP_BIT_ON                  BIT_ON(CAN_CSLPR_BIT_POS)
#define CAN_MODE_BITS_ON                BITS_2_ON(CAN_CHMDC_BIT_POS)
#define CAN_CTMS_BITS_ON                BITS_2_ON(CAN_CTMS_BIT_POS)

/* ---- RSCFDnCFDCmSTS ---- */
#define CAN_CSLPSTS_BIT_POS                         2U
#define CAN_CHLTSTS_BIT_POS                         1U
#define CAN_CRSTSTS_BIT_POS                         0U

#define CAN_STP_STS_BIT_ON              BIT_ON(CAN_CSLPSTS_BIT_POS)
#define CAN_HLT_STS_BIT_ON              BIT_ON(CAN_CHLTSTS_BIT_POS)
#define CAN_RST_STS_BIT_ON              BIT_ON(CAN_CRSTSTS_BIT_POS)

/* ---- RSCFDnCFDGCFG ---- */
#define CAN_ITRCP_BIT_POS                           16U
#define CAN_TSSS_BIT_POS                            12U
#define CAN_TSP_BIT_POS                             8U
#define CAN_CMPOC_BIT_POS                           5U
#define CAN_DCS_BIT_POS                             4U
#define CAN_MME_BIT_POS                             3U
#define CAN_DRE_BIT_POS                             2U
#define CAN_DCE_BIT_POS                             1U
#define CAN_TPRI_BIT_POS                            0U

#define CAN_CFG_GCFG(priority, dlc_check,           \
                     dlc_replace, mirror,           \
                     can_clock, ts_clock, pl_ov_md, \
                     ts_pr, it_pr)                  \
    ( ((priority)    << CAN_TPRI_BIT_POS)           \
    + ((dlc_check)   << CAN_DCE_BIT_POS)            \
    + ((dlc_replace) << CAN_DRE_BIT_POS)            \
    + ((mirror)      << CAN_MME_BIT_POS)            \
    + ((can_clock)   << CAN_DCS_BIT_POS)            \
    + ((pl_ov_md)    << CAN_CMPOC_BIT_POS)          \
    + ((ts_pr)       << CAN_TSP_BIT_POS)            \
    + ((ts_clock)    << CAN_TSSS_BIT_POS)           \
    + ((it_pr)       << CAN_ITRCP_BIT_POS)          )

/* ---- RSCFDnCFDGCTR ---- */
#define CAN_CMPOFIE_BIT_POS                         11U
#define CAN_THLEIE_BIT_POS                          10U
#define CAN_MEIE_BIT_POS                            9U
#define CAN_DEIE_BIT_POS                            8U
#define CAN_GSLPR_BIT_POS                           2U
#define CAN_GMDC_BIT_POS                            0U

#define CAN_CFG_GCTR(payload_overflow_ie,           \
                     history_overflow_ie,           \
                     msg_lost_ie, dlc_error_ie)     \
    ( ((payload_overflow_ie) << CAN_CMPOFIE_BIT_POS)\
    + ((history_overflow_ie) << CAN_THLEIE_BIT_POS) \
    + ((msg_lost_ie)  << CAN_MEIE_BIT_POS)          \
    + ((dlc_error_ie) << CAN_DEIE_BIT_POS)          )

#define CAN_GLB_STP_BIT_ON              BIT_ON(CAN_GSLPR_BIT_POS)
#define CAN_GLB_MODE_BITS_ON            BITS_2_ON(CAN_GMDC_BIT_POS)

/* ---- RSCFDnCFDGSTS ---- */
#define CAN_GRAMINIT_BIT_POS                        3U
#define CAN_GSLPSTS_BIT_POS                         2U
#define CAN_GSLTSTS_BIT_POS                         1U
#define CAN_GRSTSTS_BIT_POS                         0U

#define CAN_RAM_INIT_BIT_ON             BIT_ON(CAN_GRAMINIT_BIT_POS)
#define CAN_GLB_STP_STS_BIT_ON          BIT_ON(CAN_GSLPSTS_BIT_POS)
#define CAN_GLB_TST_STS_BIT_ON          BIT_ON(CAN_GSLTSTS_BIT_POS)
#define CAN_GLB_RST_STS_BIT_ON          BIT_ON(CAN_GRSTSTS_BIT_POS)

/* ---- RSCFDnCFDGAFLECTR ---- */
#define CAN_AFLDAE_BIT_POS                          8U

#define CAN_RX_RULE_WRT_EN_BIT_ON       BIT_ON(CAN_AFLDAE_BIT_POS)

/* ---- RSCFDnCFDGTSTCTR ----*/
#define CAN_RTME_BIT_POS                            2U
#define CAN_ICBCTME_BIT_POS                         0U

#define CAN_RAM_TST_BIT_ON              BIT_ON(CAN_RTME_BIT_POS)
#define CAN_ICBC_TST_BIT_ON             BIT_ON(CAN_ICBCTME_BIT_POS)

/* ---- RSCFDnCFDRFCCx ---- */
#define CAN_RFFIE_BIT_POS                           16U
#define CAN_RFIGCV_BIT_POS                          13U
#define CAN_RFIM_BIT_POS                            12U
#define CAN_RFDC_BIT_POS                            8U
#define CAN_RFPLS_BIT_POS                           4U
#define CAN_RFIE_BIT_POS                            1U
#define CAN_RFE_BIT_POS                             0U

#define CAN_CFG_RXFIFO(dc, i_enable, i_rfpls,       \
                       i_factor, i_timing)          \
    ( ((i_timing) << CAN_RFIGCV_BIT_POS)            \
    + ((i_factor) << CAN_RFIM_BIT_POS)              \
    + ((i_rfpls) << CAN_RFPLS_BIT_POS)              \
    + ((i_enable) << CAN_RFIE_BIT_POS)              \
    + ((dc)       << CAN_RFDC_BIT_POS)              )

#define CAN_RFIFO_EN_BIT_ON             BIT_ON(CAN_RFE_BIT_POS)

/* ---- RSCFDnCFDRFSTSx ---- */
#define CAN_RFIF_BIT_POS                            3U
#define CAN_RFMLT_BIT_POS                           2U
#define CAN_RFEMP_BIT_POS                           0U

#define CAN_RFIFO_RFIF_BIT_ON           BIT_ON(CAN_RFIF_BIT_POS)
#define CAN_RFIFO_MSGLST_BIT_ON         BIT_ON(CAN_RFMLT_BIT_POS)
#define CAN_RFIFO_EMPTY_BIT_ON          BIT_ON(CAN_RFEMP_BIT_POS)

#define CAN_CLR_WITHOUT_RX_INT          BIT_ON(CAN_RFIF_BIT_POS)

/* ---- RSCFDnCFDCFCCk ---- */
#define CAN_CFITT_BIT_POS                           24U
#define CAN_CFDC_BIT_POS                            21U
#define CAN_CFTML_BIT_POS                           16U
#define CAN_CFIGCV_BIT_POS                          13U
#define CAN_CFIM_BIT_POS                            12U
#define CAN_CFITR_BIT_POS                           11U
#define CAN_CFITSS_BIT_POS                          10U
#define CAN_CFM_BIT_POS                             8U
#define CAN_CFPLS_BIT_POS                           4U
#define CAN_CFTXIE_BIT_POS                          2U
#define CAN_CFRXIE_BIT_POS                          1U
#define CAN_CFE_BIT_POS                             0U

#define CAN_CFG_TRFIFO_TX(dc, txbuf_idx, i_enable,  \
                          i_factor, timer,          \
                          time, pls)                \
    ( ((time)               << CAN_CFITT_BIT_POS)   \
    + ((dc)                 << CAN_CFDC_BIT_POS)    \
    + ((txbuf_idx)          << CAN_CFTML_BIT_POS)   \
    + ((i_factor)           << CAN_CFIM_BIT_POS)    \
    + ((timer)              << CAN_CFITSS_BIT_POS)  \
    + ((CAN_TRFIFO_TX_MODE) << CAN_CFM_BIT_POS)     \
    + ((pls)                << CAN_CFPLS_BIT_POS)   \
    + ((i_enable)           << CAN_CFTXIE_BIT_POS)  )

#define CAN_CFG_TRFIFO_RX(dc, i_enable, i_factor,   \
                          i_timing, pls)            \
    ( ((dc)                 << CAN_CFDC_BIT_POS)    \
    + ((i_timing)           << CAN_CFIGCV_BIT_POS)  \
    + ((i_factor)           << CAN_CFIM_BIT_POS)    \
    + ((CAN_TRFIFO_RX_MODE) << CAN_CFM_BIT_POS)     \
    + ((pls)                << CAN_CFPLS_BIT_POS)   \
    + ((i_enable)           << CAN_CFRXIE_BIT_POS)  )

#define CAN_CFG_TRFIFO_GW(dc, i_factor,             \
                          txbuf_idx, tx_i_enable,   \
                          timer, time, rx_i_enable, \
                          rx_i_timing, pls)         \
    ( ((time)               << CAN_CFITT_BIT_POS)   \
    + ((dc)                 << CAN_CFDC_BIT_POS)    \
    + ((txbuf_idx)          << CAN_CFTML_BIT_POS)   \
    + ((rx_i_timing)        << CAN_CFIGCV_BIT_POS)  \
    + ((i_factor)           << CAN_CFIM_BIT_POS)    \
    + ((timer)              << CAN_CFITSS_BIT_POS)  \
    + ((CAN_TRFIFO_GW_MODE) << CAN_CFM_BIT_POS)     \
    + ((pls)                << CAN_CFPLS_BIT_POS)   \
    + ((tx_i_enable)        << CAN_CFTXIE_BIT_POS)  \
    + ((rx_i_enable)        << CAN_CFRXIE_BIT_POS)  )

#define CAN_TRFIFO_EN_BIT_ON                BIT_ON(CAN_CFE_BIT_POS)

/* ---- RSCFDnCFDCFSTSk ---- */
#define CAN_CFTXIF_BIT_POS                          4U
#define CAN_CFRXIF_BIT_POS                          3U
#define CAN_CFMLT_BIT_POS                           2U
#define CAN_CFFLL_BIT_POS                           1U
#define CAN_CFEMP_BIT_POS                           0U

#define CAN_TRFIFO_CFTXIF_BIT_ON            BIT_ON(CAN_CFTXIF_BIT_POS)
#define CAN_TRFIFO_CFRXIF_BIT_ON            BIT_ON(CAN_CFRXIF_BIT_POS)
#define CAN_TRFIFO_MSGLST_BIT_ON            BIT_ON(CAN_CFMLT_BIT_POS)
#define CAN_TRFIFO_FULL_BIT_ON              BIT_ON(CAN_CFFLL_BIT_POS)
#define CAN_TRFIFO_EMPTY_BIT_ON             BIT_ON(CAN_CFEMP_BIT_POS)

#define CAN_CLR_WITHOUT_TX_RX_INT \
    (BIT_ON(CAN_CFTXIF_BIT_POS) | BIT_ON(CAN_CFRXIF_BIT_POS))

/* ---- RSCFDnCFDTXQCCXm ---- */
#define CAN_TXQOFTXIE_BIT_POS                       18U
#define CAN_TXQOFRXIE_BIT_POS                       17U
#define CAN_TXQFIE_BIT_POS                          16U
#define CAN_TXQDC_BIT_POS                           8U
#define CAN_TXQIM_BIT_POS                           7U
#define CAN_TXQTXIE_BIT_POS                         5U
#define CAN_TXQOWE_BIT_POS                          2U
#define CAN_TXQGWE_BIT_POS                          1U
#define CAN_TXQE_BIT_POS                            0U

#define CAN_CFG_TXQUEUE(dc, i_enable, i_factor)     \
    ( ((dc)       << CAN_TXQDC_BIT_POS)             \
    + ((i_factor) << CAN_TXQIM_BIT_POS)             \
    + ((i_enable) << CAN_TXQTXIE_BIT_POS) )

#define CAN_TXQUEUE_EN_BIT_ON               BIT_ON(CAN_TXQE_BIT_POS)

/* ---- RSCFDnCFDTMCp ---- */
#define CAN_TMTAR_BIT_POS                           1U
#define CAN_TMTR_BIT_POS                            0U

#define CAN_TXBUF_ABT_BIT_ON                (uint8_t)(1 << (CAN_TMTAR_BIT_POS))
#define CAN_TXBUF_TRM_BIT_ON                (uint8_t)(1 << (CAN_TMTR_BIT_POS))

/* ---- RSCFDnCFDTMSTSp ---- */
#define CAN_TMTRF_BIT_POS                           1U

#define CAN_TXBUF_RSLT_BITS_POS             CAN_TMTRF_BIT_POS
#define CAN_TXBUF_RSLT_BITS_ON              (uint8_t)(3 << (CAN_TXBUF_RSLT_BITS_POS))

/* ---- RSCFDnCFDTXQSTSXm ---- */
#define CAN_TXQIF_BIT_POS                           2U
#define CAN_TXQFLL_BIT_POS                          1U

#define CAN_TXQUEUE_IF_BIT_ON               BIT_ON(CAN_TXQIF_BIT_POS)
#define CAN_TXQUEUE_FULL_BIT_ON             BIT_ON(CAN_TXQFLL_BIT_POS)

/* ---- RSCFDnCFDRMNB ---- */
#define CAN_RMPLS_BIT_POS                           8U
#define CAN_NRXMB_BIT_POS                           0U

#define CAN_CFG_RMNB(size, buff_num)                \
    ( ((size)      << CAN_RMPLS_BIT_POS)            \
    + ((buff_num)  << CAN_NRXMB_BIT_POS))

/* ==== CAN SFR register value ==== */

/* ---- Time segment 1(Normal Bit Rate) ---- */
#define CAN_NTSEG1_2TQ                    1U
#define CAN_NTSEG1_3TQ                    2U
#define CAN_NTSEG1_4TQ                    3U
#define CAN_NTSEG1_5TQ                    4U
#define CAN_NTSEG1_6TQ                    5U
#define CAN_NTSEG1_7TQ                    6U
#define CAN_NTSEG1_8TQ                    7U
#define CAN_NTSEG1_9TQ                    8U
#define CAN_NTSEG1_10TQ                   9U
#define CAN_NTSEG1_11TQ                  10U
#define CAN_NTSEG1_12TQ                  11U
#define CAN_NTSEG1_13TQ                  12U
#define CAN_NTSEG1_14TQ                  13U
#define CAN_NTSEG1_15TQ                  14U
#define CAN_NTSEG1_16TQ                  15U
#define CAN_NTSEG1_17TQ                  16U
#define CAN_NTSEG1_18TQ                  17U
#define CAN_NTSEG1_19TQ                  18U
#define CAN_NTSEG1_20TQ                  19U
#define CAN_NTSEG1_21TQ                  20U
#define CAN_NTSEG1_22TQ                  21U
#define CAN_NTSEG1_23TQ                  22U
#define CAN_NTSEG1_24TQ                  23U
#define CAN_NTSEG1_25TQ                  24U
#define CAN_NTSEG1_26TQ                  25U
#define CAN_NTSEG1_27TQ                  26U
#define CAN_NTSEG1_28TQ                  27U
#define CAN_NTSEG1_29TQ                  28U
#define CAN_NTSEG1_30TQ                  29U
#define CAN_NTSEG1_31TQ                  30U
#define CAN_NTSEG1_32TQ                  31U
#define CAN_NTSEG1_33TQ                  32U
#define CAN_NTSEG1_34TQ                  33U
#define CAN_NTSEG1_35TQ                  34U
#define CAN_NTSEG1_36TQ                  35U
#define CAN_NTSEG1_37TQ                  36U
#define CAN_NTSEG1_38TQ                  37U
#define CAN_NTSEG1_39TQ                  38U
#define CAN_NTSEG1_40TQ                  39U
#define CAN_NTSEG1_41TQ                  40U
#define CAN_NTSEG1_42TQ                  41U
#define CAN_NTSEG1_43TQ                  42U
#define CAN_NTSEG1_44TQ                  43U
#define CAN_NTSEG1_45TQ                  44U
#define CAN_NTSEG1_46TQ                  45U
#define CAN_NTSEG1_47TQ                  46U
#define CAN_NTSEG1_48TQ                  47U
#define CAN_NTSEG1_49TQ                  48U
#define CAN_NTSEG1_50TQ                  49U
#define CAN_NTSEG1_51TQ                  50U
#define CAN_NTSEG1_52TQ                  51U
#define CAN_NTSEG1_53TQ                  52U
#define CAN_NTSEG1_54TQ                  53U
#define CAN_NTSEG1_55TQ                  54U
#define CAN_NTSEG1_56TQ                  55U
#define CAN_NTSEG1_57TQ                  56U
#define CAN_NTSEG1_58TQ                  57U
#define CAN_NTSEG1_59TQ                  58U
#define CAN_NTSEG1_60TQ                  59U
#define CAN_NTSEG1_61TQ                  60U
#define CAN_NTSEG1_62TQ                  61U
#define CAN_NTSEG1_63TQ                  62U
#define CAN_NTSEG1_64TQ                  63U
#define CAN_NTSEG1_65TQ                  64U
#define CAN_NTSEG1_66TQ                  65U
#define CAN_NTSEG1_67TQ                  66U
#define CAN_NTSEG1_68TQ                  67U
#define CAN_NTSEG1_69TQ                  68U
#define CAN_NTSEG1_70TQ                  69U
#define CAN_NTSEG1_71TQ                  70U
#define CAN_NTSEG1_72TQ                  71U
#define CAN_NTSEG1_73TQ                  72U
#define CAN_NTSEG1_74TQ                  73U
#define CAN_NTSEG1_75TQ                  74U
#define CAN_NTSEG1_76TQ                  75U
#define CAN_NTSEG1_77TQ                  76U
#define CAN_NTSEG1_78TQ                  77U
#define CAN_NTSEG1_79TQ                  78U
#define CAN_NTSEG1_80TQ                  79U
#define CAN_NTSEG1_81TQ                  80U
#define CAN_NTSEG1_82TQ                  81U
#define CAN_NTSEG1_83TQ                  82U
#define CAN_NTSEG1_84TQ                  83U
#define CAN_NTSEG1_85TQ                  84U
#define CAN_NTSEG1_86TQ                  85U
#define CAN_NTSEG1_87TQ                  86U
#define CAN_NTSEG1_88TQ                  87U
#define CAN_NTSEG1_89TQ                  88U
#define CAN_NTSEG1_90TQ                  89U
#define CAN_NTSEG1_91TQ                  90U
#define CAN_NTSEG1_92TQ                  91U
#define CAN_NTSEG1_93TQ                  92U
#define CAN_NTSEG1_94TQ                  93U
#define CAN_NTSEG1_95TQ                  94U
#define CAN_NTSEG1_96TQ                  95U
#define CAN_NTSEG1_97TQ                  96U
#define CAN_NTSEG1_98TQ                  97U
#define CAN_NTSEG1_99TQ                  98U
#define CAN_NTSEG1_100TQ                 99U
#define CAN_NTSEG1_101TQ                100U
#define CAN_NTSEG1_102TQ                101U
#define CAN_NTSEG1_103TQ                102U
#define CAN_NTSEG1_104TQ                103U
#define CAN_NTSEG1_105TQ                104U
#define CAN_NTSEG1_106TQ                105U
#define CAN_NTSEG1_107TQ                106U
#define CAN_NTSEG1_108TQ                107U
#define CAN_NTSEG1_109TQ                108U
#define CAN_NTSEG1_110TQ                109U
#define CAN_NTSEG1_111TQ                110U
#define CAN_NTSEG1_112TQ                111U
#define CAN_NTSEG1_113TQ                112U
#define CAN_NTSEG1_114TQ                113U
#define CAN_NTSEG1_115TQ                114U
#define CAN_NTSEG1_116TQ                115U
#define CAN_NTSEG1_117TQ                116U
#define CAN_NTSEG1_118TQ                117U
#define CAN_NTSEG1_119TQ                118U
#define CAN_NTSEG1_120TQ                119U
#define CAN_NTSEG1_121TQ                120U
#define CAN_NTSEG1_122TQ                121U
#define CAN_NTSEG1_123TQ                122U
#define CAN_NTSEG1_124TQ                123U
#define CAN_NTSEG1_125TQ                124U
#define CAN_NTSEG1_126TQ                125U
#define CAN_NTSEG1_127TQ                126U
#define CAN_NTSEG1_128TQ                127U
#define CAN_NTSEG1_129TQ                128U
#define CAN_NTSEG1_130TQ                129U
#define CAN_NTSEG1_131TQ                130U
#define CAN_NTSEG1_132TQ                131U
#define CAN_NTSEG1_133TQ                132U
#define CAN_NTSEG1_134TQ                133U
#define CAN_NTSEG1_135TQ                134U
#define CAN_NTSEG1_136TQ                135U
#define CAN_NTSEG1_137TQ                136U
#define CAN_NTSEG1_138TQ                137U
#define CAN_NTSEG1_139TQ                138U
#define CAN_NTSEG1_140TQ                139U
#define CAN_NTSEG1_141TQ                140U
#define CAN_NTSEG1_142TQ                141U
#define CAN_NTSEG1_143TQ                142U
#define CAN_NTSEG1_144TQ                143U
#define CAN_NTSEG1_145TQ                144U
#define CAN_NTSEG1_146TQ                145U
#define CAN_NTSEG1_147TQ                146U
#define CAN_NTSEG1_148TQ                147U
#define CAN_NTSEG1_149TQ                148U
#define CAN_NTSEG1_150TQ                149U
#define CAN_NTSEG1_151TQ                150U
#define CAN_NTSEG1_152TQ                151U
#define CAN_NTSEG1_153TQ                152U
#define CAN_NTSEG1_154TQ                153U
#define CAN_NTSEG1_155TQ                154U
#define CAN_NTSEG1_156TQ                155U
#define CAN_NTSEG1_157TQ                156U
#define CAN_NTSEG1_158TQ                157U
#define CAN_NTSEG1_159TQ                158U
#define CAN_NTSEG1_160TQ                159U
#define CAN_NTSEG1_161TQ                160U
#define CAN_NTSEG1_162TQ                161U
#define CAN_NTSEG1_163TQ                162U
#define CAN_NTSEG1_164TQ                163U
#define CAN_NTSEG1_165TQ                164U
#define CAN_NTSEG1_166TQ                165U
#define CAN_NTSEG1_167TQ                166U
#define CAN_NTSEG1_168TQ                167U
#define CAN_NTSEG1_169TQ                168U
#define CAN_NTSEG1_170TQ                169U
#define CAN_NTSEG1_171TQ                170U
#define CAN_NTSEG1_172TQ                171U
#define CAN_NTSEG1_173TQ                172U
#define CAN_NTSEG1_174TQ                173U
#define CAN_NTSEG1_175TQ                174U
#define CAN_NTSEG1_176TQ                175U
#define CAN_NTSEG1_177TQ                176U
#define CAN_NTSEG1_178TQ                177U
#define CAN_NTSEG1_179TQ                178U
#define CAN_NTSEG1_180TQ                179U
#define CAN_NTSEG1_181TQ                180U
#define CAN_NTSEG1_182TQ                181U
#define CAN_NTSEG1_183TQ                182U
#define CAN_NTSEG1_184TQ                183U
#define CAN_NTSEG1_185TQ                184U
#define CAN_NTSEG1_186TQ                185U
#define CAN_NTSEG1_187TQ                186U
#define CAN_NTSEG1_188TQ                187U
#define CAN_NTSEG1_189TQ                188U
#define CAN_NTSEG1_190TQ                189U
#define CAN_NTSEG1_191TQ                190U
#define CAN_NTSEG1_192TQ                191U
#define CAN_NTSEG1_193TQ                192U
#define CAN_NTSEG1_194TQ                193U
#define CAN_NTSEG1_195TQ                194U
#define CAN_NTSEG1_196TQ                195U
#define CAN_NTSEG1_197TQ                196U
#define CAN_NTSEG1_198TQ                197U
#define CAN_NTSEG1_199TQ                198U
#define CAN_NTSEG1_200TQ                199U
#define CAN_NTSEG1_201TQ                200U
#define CAN_NTSEG1_202TQ                201U
#define CAN_NTSEG1_203TQ                202U
#define CAN_NTSEG1_204TQ                203U
#define CAN_NTSEG1_205TQ                204U
#define CAN_NTSEG1_206TQ                205U
#define CAN_NTSEG1_207TQ                206U
#define CAN_NTSEG1_208TQ                207U
#define CAN_NTSEG1_209TQ                208U
#define CAN_NTSEG1_210TQ                209U
#define CAN_NTSEG1_211TQ                210U
#define CAN_NTSEG1_212TQ                211U
#define CAN_NTSEG1_213TQ                212U
#define CAN_NTSEG1_214TQ                213U
#define CAN_NTSEG1_215TQ                214U
#define CAN_NTSEG1_216TQ                215U
#define CAN_NTSEG1_217TQ                216U
#define CAN_NTSEG1_218TQ                217U
#define CAN_NTSEG1_219TQ                218U
#define CAN_NTSEG1_220TQ                219U
#define CAN_NTSEG1_221TQ                220U
#define CAN_NTSEG1_222TQ                221U
#define CAN_NTSEG1_223TQ                222U
#define CAN_NTSEG1_224TQ                223U
#define CAN_NTSEG1_225TQ                224U
#define CAN_NTSEG1_226TQ                225U
#define CAN_NTSEG1_227TQ                226U
#define CAN_NTSEG1_228TQ                227U
#define CAN_NTSEG1_229TQ                228U
#define CAN_NTSEG1_230TQ                229U
#define CAN_NTSEG1_231TQ                230U
#define CAN_NTSEG1_232TQ                231U
#define CAN_NTSEG1_233TQ                232U
#define CAN_NTSEG1_234TQ                233U
#define CAN_NTSEG1_235TQ                234U
#define CAN_NTSEG1_236TQ                235U
#define CAN_NTSEG1_237TQ                236U
#define CAN_NTSEG1_238TQ                237U
#define CAN_NTSEG1_239TQ                238U
#define CAN_NTSEG1_240TQ                239U
#define CAN_NTSEG1_241TQ                240U
#define CAN_NTSEG1_242TQ                241U
#define CAN_NTSEG1_243TQ                242U
#define CAN_NTSEG1_244TQ                243U
#define CAN_NTSEG1_245TQ                244U
#define CAN_NTSEG1_246TQ                245U
#define CAN_NTSEG1_247TQ                246U
#define CAN_NTSEG1_248TQ                247U
#define CAN_NTSEG1_249TQ                248U
#define CAN_NTSEG1_250TQ                249U
#define CAN_NTSEG1_251TQ                250U
#define CAN_NTSEG1_252TQ                251U
#define CAN_NTSEG1_253TQ                252U
#define CAN_NTSEG1_254TQ                253U
#define CAN_NTSEG1_255TQ                254U
#define CAN_NTSEG1_256TQ                255U

/* ---- Time segment 2(Normal Bit Rate) ---- */
#define CAN_NTSEG2_2TQ                    1U
#define CAN_NTSEG2_3TQ                    2U
#define CAN_NTSEG2_4TQ                    3U
#define CAN_NTSEG2_5TQ                    4U
#define CAN_NTSEG2_6TQ                    5U
#define CAN_NTSEG2_7TQ                    6U
#define CAN_NTSEG2_8TQ                    7U
#define CAN_NTSEG2_9TQ                    8U
#define CAN_NTSEG2_10TQ                   9U
#define CAN_NTSEG2_11TQ                  10U
#define CAN_NTSEG2_12TQ                  11U
#define CAN_NTSEG2_13TQ                  12U
#define CAN_NTSEG2_14TQ                  13U
#define CAN_NTSEG2_15TQ                  14U
#define CAN_NTSEG2_16TQ                  15U
#define CAN_NTSEG2_17TQ                  16U
#define CAN_NTSEG2_18TQ                  17U
#define CAN_NTSEG2_19TQ                  18U
#define CAN_NTSEG2_20TQ                  19U
#define CAN_NTSEG2_21TQ                  20U
#define CAN_NTSEG2_22TQ                  21U
#define CAN_NTSEG2_23TQ                  22U
#define CAN_NTSEG2_24TQ                  23U
#define CAN_NTSEG2_25TQ                  24U
#define CAN_NTSEG2_26TQ                  25U
#define CAN_NTSEG2_27TQ                  26U
#define CAN_NTSEG2_28TQ                  27U
#define CAN_NTSEG2_29TQ                  28U
#define CAN_NTSEG2_30TQ                  29U
#define CAN_NTSEG2_31TQ                  30U
#define CAN_NTSEG2_32TQ                  31U
#define CAN_NTSEG2_33TQ                  32U
#define CAN_NTSEG2_34TQ                  33U
#define CAN_NTSEG2_35TQ                  34U
#define CAN_NTSEG2_36TQ                  35U
#define CAN_NTSEG2_37TQ                  36U
#define CAN_NTSEG2_38TQ                  37U
#define CAN_NTSEG2_39TQ                  38U
#define CAN_NTSEG2_40TQ                  39U
#define CAN_NTSEG2_41TQ                  40U
#define CAN_NTSEG2_42TQ                  41U
#define CAN_NTSEG2_43TQ                  42U
#define CAN_NTSEG2_44TQ                  43U
#define CAN_NTSEG2_45TQ                  44U
#define CAN_NTSEG2_46TQ                  45U
#define CAN_NTSEG2_47TQ                  46U
#define CAN_NTSEG2_48TQ                  47U
#define CAN_NTSEG2_49TQ                  48U
#define CAN_NTSEG2_50TQ                  49U
#define CAN_NTSEG2_51TQ                  50U
#define CAN_NTSEG2_52TQ                  51U
#define CAN_NTSEG2_53TQ                  52U
#define CAN_NTSEG2_54TQ                  53U
#define CAN_NTSEG2_55TQ                  54U
#define CAN_NTSEG2_56TQ                  55U
#define CAN_NTSEG2_57TQ                  56U
#define CAN_NTSEG2_58TQ                  57U
#define CAN_NTSEG2_59TQ                  58U
#define CAN_NTSEG2_60TQ                  59U
#define CAN_NTSEG2_61TQ                  60U
#define CAN_NTSEG2_62TQ                  61U
#define CAN_NTSEG2_63TQ                  62U
#define CAN_NTSEG2_64TQ                  63U
#define CAN_NTSEG2_65TQ                  64U
#define CAN_NTSEG2_66TQ                  65U
#define CAN_NTSEG2_67TQ                  66U
#define CAN_NTSEG2_68TQ                  67U
#define CAN_NTSEG2_69TQ                  68U
#define CAN_NTSEG2_70TQ                  69U
#define CAN_NTSEG2_71TQ                  70U
#define CAN_NTSEG2_72TQ                  71U
#define CAN_NTSEG2_73TQ                  72U
#define CAN_NTSEG2_74TQ                  73U
#define CAN_NTSEG2_75TQ                  74U
#define CAN_NTSEG2_76TQ                  75U
#define CAN_NTSEG2_77TQ                  76U
#define CAN_NTSEG2_78TQ                  77U
#define CAN_NTSEG2_79TQ                  78U
#define CAN_NTSEG2_80TQ                  79U
#define CAN_NTSEG2_81TQ                  80U
#define CAN_NTSEG2_82TQ                  81U
#define CAN_NTSEG2_83TQ                  82U
#define CAN_NTSEG2_84TQ                  83U
#define CAN_NTSEG2_85TQ                  84U
#define CAN_NTSEG2_86TQ                  85U
#define CAN_NTSEG2_87TQ                  86U
#define CAN_NTSEG2_88TQ                  87U
#define CAN_NTSEG2_89TQ                  88U
#define CAN_NTSEG2_90TQ                  89U
#define CAN_NTSEG2_91TQ                  90U
#define CAN_NTSEG2_92TQ                  91U
#define CAN_NTSEG2_93TQ                  92U
#define CAN_NTSEG2_94TQ                  93U
#define CAN_NTSEG2_95TQ                  94U
#define CAN_NTSEG2_96TQ                  95U
#define CAN_NTSEG2_97TQ                  96U
#define CAN_NTSEG2_98TQ                  97U
#define CAN_NTSEG2_99TQ                  98U
#define CAN_NTSEG2_100TQ                 99U
#define CAN_NTSEG2_101TQ                100U
#define CAN_NTSEG2_102TQ                101U
#define CAN_NTSEG2_103TQ                102U
#define CAN_NTSEG2_104TQ                103U
#define CAN_NTSEG2_105TQ                104U
#define CAN_NTSEG2_106TQ                105U
#define CAN_NTSEG2_107TQ                106U
#define CAN_NTSEG2_108TQ                107U
#define CAN_NTSEG2_109TQ                108U
#define CAN_NTSEG2_110TQ                109U
#define CAN_NTSEG2_111TQ                110U
#define CAN_NTSEG2_112TQ                111U
#define CAN_NTSEG2_113TQ                112U
#define CAN_NTSEG2_114TQ                113U
#define CAN_NTSEG2_115TQ                114U
#define CAN_NTSEG2_116TQ                115U
#define CAN_NTSEG2_117TQ                116U
#define CAN_NTSEG2_118TQ                117U
#define CAN_NTSEG2_119TQ                118U
#define CAN_NTSEG2_120TQ                119U
#define CAN_NTSEG2_121TQ                120U
#define CAN_NTSEG2_122TQ                121U
#define CAN_NTSEG2_123TQ                122U
#define CAN_NTSEG2_124TQ                123U
#define CAN_NTSEG2_125TQ                124U
#define CAN_NTSEG2_126TQ                125U
#define CAN_NTSEG2_127TQ                126U
#define CAN_NTSEG2_128TQ                127U

/* ---- Resynchronization jump width(Normal Bit Rate) ---- */
#define CAN_NSJW_1TQ                      0U
#define CAN_NSJW_2TQ                      1U
#define CAN_NSJW_3TQ                      2U
#define CAN_NSJW_4TQ                      3U
#define CAN_NSJW_5TQ                      4U
#define CAN_NSJW_6TQ                      5U
#define CAN_NSJW_7TQ                      6U
#define CAN_NSJW_8TQ                      7U
#define CAN_NSJW_9TQ                      8U
#define CAN_NSJW_10TQ                     9U
#define CAN_NSJW_11TQ                    10U
#define CAN_NSJW_12TQ                    11U
#define CAN_NSJW_13TQ                    12U
#define CAN_NSJW_14TQ                    13U
#define CAN_NSJW_15TQ                    14U
#define CAN_NSJW_16TQ                    15U
#define CAN_NSJW_17TQ                    16U
#define CAN_NSJW_18TQ                    17U
#define CAN_NSJW_19TQ                    18U
#define CAN_NSJW_20TQ                    19U
#define CAN_NSJW_21TQ                    20U
#define CAN_NSJW_22TQ                    21U
#define CAN_NSJW_23TQ                    22U
#define CAN_NSJW_24TQ                    23U
#define CAN_NSJW_25TQ                    24U
#define CAN_NSJW_26TQ                    25U
#define CAN_NSJW_27TQ                    26U
#define CAN_NSJW_28TQ                    27U
#define CAN_NSJW_29TQ                    28U
#define CAN_NSJW_30TQ                    29U
#define CAN_NSJW_31TQ                    30U
#define CAN_NSJW_32TQ                    31U
#define CAN_NSJW_33TQ                    32U
#define CAN_NSJW_34TQ                    33U
#define CAN_NSJW_35TQ                    34U
#define CAN_NSJW_36TQ                    35U
#define CAN_NSJW_37TQ                    36U
#define CAN_NSJW_38TQ                    37U
#define CAN_NSJW_39TQ                    38U
#define CAN_NSJW_40TQ                    39U
#define CAN_NSJW_41TQ                    40U
#define CAN_NSJW_42TQ                    41U
#define CAN_NSJW_43TQ                    42U
#define CAN_NSJW_44TQ                    43U
#define CAN_NSJW_45TQ                    44U
#define CAN_NSJW_46TQ                    45U
#define CAN_NSJW_47TQ                    46U
#define CAN_NSJW_48TQ                    47U
#define CAN_NSJW_49TQ                    48U
#define CAN_NSJW_50TQ                    49U
#define CAN_NSJW_51TQ                    50U
#define CAN_NSJW_52TQ                    51U
#define CAN_NSJW_53TQ                    52U
#define CAN_NSJW_54TQ                    53U
#define CAN_NSJW_55TQ                    54U
#define CAN_NSJW_56TQ                    55U
#define CAN_NSJW_57TQ                    56U
#define CAN_NSJW_58TQ                    57U
#define CAN_NSJW_59TQ                    58U
#define CAN_NSJW_60TQ                    59U
#define CAN_NSJW_61TQ                    60U
#define CAN_NSJW_62TQ                    61U
#define CAN_NSJW_63TQ                    62U
#define CAN_NSJW_64TQ                    63U
#define CAN_NSJW_65TQ                    64U
#define CAN_NSJW_66TQ                    65U
#define CAN_NSJW_67TQ                    66U
#define CAN_NSJW_68TQ                    67U
#define CAN_NSJW_69TQ                    68U
#define CAN_NSJW_70TQ                    69U
#define CAN_NSJW_71TQ                    70U
#define CAN_NSJW_72TQ                    71U
#define CAN_NSJW_73TQ                    72U
#define CAN_NSJW_74TQ                    73U
#define CAN_NSJW_75TQ                    74U
#define CAN_NSJW_76TQ                    75U
#define CAN_NSJW_77TQ                    76U
#define CAN_NSJW_78TQ                    77U
#define CAN_NSJW_79TQ                    78U
#define CAN_NSJW_80TQ                    79U
#define CAN_NSJW_81TQ                    80U
#define CAN_NSJW_82TQ                    81U
#define CAN_NSJW_83TQ                    82U
#define CAN_NSJW_84TQ                    83U
#define CAN_NSJW_85TQ                    84U
#define CAN_NSJW_86TQ                    85U
#define CAN_NSJW_87TQ                    86U
#define CAN_NSJW_88TQ                    87U
#define CAN_NSJW_89TQ                    88U
#define CAN_NSJW_90TQ                    89U
#define CAN_NSJW_91TQ                    90U
#define CAN_NSJW_92TQ                    91U
#define CAN_NSJW_93TQ                    92U
#define CAN_NSJW_94TQ                    93U
#define CAN_NSJW_95TQ                    94U
#define CAN_NSJW_96TQ                    95U
#define CAN_NSJW_97TQ                    96U
#define CAN_NSJW_98TQ                    97U
#define CAN_NSJW_99TQ                    98U
#define CAN_NSJW_100TQ                   99U
#define CAN_NSJW_101TQ                  100U
#define CAN_NSJW_102TQ                  101U
#define CAN_NSJW_103TQ                  102U
#define CAN_NSJW_104TQ                  103U
#define CAN_NSJW_105TQ                  104U
#define CAN_NSJW_106TQ                  105U
#define CAN_NSJW_107TQ                  106U
#define CAN_NSJW_108TQ                  107U
#define CAN_NSJW_109TQ                  108U
#define CAN_NSJW_110TQ                  109U
#define CAN_NSJW_111TQ                  110U
#define CAN_NSJW_112TQ                  111U
#define CAN_NSJW_113TQ                  112U
#define CAN_NSJW_114TQ                  113U
#define CAN_NSJW_115TQ                  114U
#define CAN_NSJW_116TQ                  115U
#define CAN_NSJW_117TQ                  116U
#define CAN_NSJW_118TQ                  117U
#define CAN_NSJW_119TQ                  118U
#define CAN_NSJW_120TQ                  119U
#define CAN_NSJW_121TQ                  120U
#define CAN_NSJW_122TQ                  121U
#define CAN_NSJW_123TQ                  122U
#define CAN_NSJW_124TQ                  123U
#define CAN_NSJW_125TQ                  124U
#define CAN_NSJW_126TQ                  125U
#define CAN_NSJW_127TQ                  126U
#define CAN_NSJW_128TQ                  127U

/* ---- Time segment 1(Data Bit Rate) ---- */
#define CAN_DTSEG1_2TQ                    1U
#define CAN_DTSEG1_3TQ                    2U
#define CAN_DTSEG1_4TQ                    3U
#define CAN_DTSEG1_5TQ                    4U
#define CAN_DTSEG1_6TQ                    5U
#define CAN_DTSEG1_7TQ                    6U
#define CAN_DTSEG1_8TQ                    7U
#define CAN_DTSEG1_9TQ                    8U
#define CAN_DTSEG1_10TQ                   9U
#define CAN_DTSEG1_11TQ                  10U
#define CAN_DTSEG1_12TQ                  11U
#define CAN_DTSEG1_13TQ                  12U
#define CAN_DTSEG1_14TQ                  13U
#define CAN_DTSEG1_15TQ                  14U
#define CAN_DTSEG1_16TQ                  15U
#define CAN_DTSEG1_17TQ                  16U
#define CAN_DTSEG1_18TQ                  17U
#define CAN_DTSEG1_19TQ                  18U
#define CAN_DTSEG1_20TQ                  19U
#define CAN_DTSEG1_21TQ                  20U
#define CAN_DTSEG1_22TQ                  21U
#define CAN_DTSEG1_23TQ                  22U
#define CAN_DTSEG1_24TQ                  23U
#define CAN_DTSEG1_25TQ                  24U
#define CAN_DTSEG1_26TQ                  25U
#define CAN_DTSEG1_27TQ                  26U
#define CAN_DTSEG1_28TQ                  27U
#define CAN_DTSEG1_29TQ                  28U
#define CAN_DTSEG1_30TQ                  29U
#define CAN_DTSEG1_31TQ                  30U
#define CAN_DTSEG1_32TQ                  31U

/* ---- Time segment 2(Data Bit Rate) ---- */
#define CAN_DTSEG2_2TQ                    1U
#define CAN_DTSEG2_3TQ                    2U
#define CAN_DTSEG2_4TQ                    3U
#define CAN_DTSEG2_5TQ                    4U
#define CAN_DTSEG2_6TQ                    5U
#define CAN_DTSEG2_7TQ                    6U
#define CAN_DTSEG2_8TQ                    7U
#define CAN_DTSEG2_9TQ                    8U
#define CAN_DTSEG2_10TQ                   9U
#define CAN_DTSEG2_11TQ                  10U
#define CAN_DTSEG2_12TQ                  11U
#define CAN_DTSEG2_13TQ                  12U
#define CAN_DTSEG2_14TQ                  13U
#define CAN_DTSEG2_15TQ                  14U
#define CAN_DTSEG2_16TQ                  15U

/* ---- Resynchronization jump width(Data Bit Rate) ---- */
#define CAN_DSJW_1TQ                      0U
#define CAN_DSJW_2TQ                      1U
#define CAN_DSJW_3TQ                      2U
#define CAN_DSJW_4TQ                      3U
#define CAN_DSJW_5TQ                      4U
#define CAN_DSJW_6TQ                      5U
#define CAN_DSJW_7TQ                      6U
#define CAN_DSJW_8TQ                      7U
#define CAN_DSJW_9TQ                      8U
#define CAN_DSJW_10TQ                     9U
#define CAN_DSJW_11TQ                    10U
#define CAN_DSJW_12TQ                    11U
#define CAN_DSJW_13TQ                    12U
#define CAN_DSJW_14TQ                    13U
#define CAN_DSJW_15TQ                    14U
#define CAN_DSJW_16TQ                    15U

/* ---- Error display mode ---- */
#define CAN_ERRDISP_FIRST_ERR_ONLY       0U
#define CAN_ERRDISP_ALL_ERR              1U

/* ---- Bus off recovery mode ---- */
#define CAN_BOFF_RECOVERY_ISO11898       0U
#define CAN_BOFF_RECOVERY_START_ENTRY    1U
#define CAN_BOFF_RECOVERY_END_ENTRY      2U
#define CAN_BOFF_RECOVERY_MANUAL_ENTRY   3U

/* ---- Channel mode ---- */
#define CAN_MODE_CH_COMM_MODE            0U
#define CAN_MODE_CH_RESET_MODE           1U
#define CAN_MODE_CH_HALT_MODE            2U

/* ---- Time stamp clock source ---- */
#define CAN_TS_PCLOCK                    0U
#define CAN_TS_CAN0_BT_CLOCK             1U
#define CAN_TS_CAN1_BT_CLOCK             3U
#define CAN_TS_CAN2_BT_CLOCK             5U
#define CAN_TS_CAN3_BT_CLOCK             7U
#define CAN_TS_CAN4_BT_CLOCK             9U
#define CAN_TS_CAN5_BT_CLOCK            11U

/* ---- Time stamp clock source division ---- */
#define CAN_TS_NO_DIV                    0U
#define CAN_TS_2_DIV                     1U
#define CAN_TS_4_DIV                     2U
#define CAN_TS_8_DIV                     3U
#define CAN_TS_16_DIV                    4U
#define CAN_TS_32_DIV                    5U
#define CAN_TS_64_DIV                    6U
#define CAN_TS_128_DIV                   7U
#define CAN_TS_256_DIV                   8U
#define CAN_TS_512_DIV                   9U
#define CAN_TS_1024_DIV                 10U
#define CAN_TS_2048_DIV                 11U
#define CAN_TS_4096_DIV                 12U
#define CAN_TS_8192_DIV                 13U
#define CAN_TS_16384_DIV                14U
#define CAN_TS_32768_DIV                15U

/* ---- Payload overflow mode ---- */
#define CAN_PL_NO_STORED                 0U
#define CAN_PL_STORED                    1U

/* ---- CAN clock source ---- */
#define CAN_SOURCE_PCLOCK_PLL2           0U
#define CAN_SOURCE_MAIN_CLOCK_X_DIV      1U

/* ---- transmission priority ---- */
#define CAN_TX_ID_FIRST                  0U
#define CAN_TX_BUF_IDX_FIRST             1U

/* ---- global mode ---- */
#define CAN_GLB_OPERATION_MODE           0U
#define CAN_GLB_RESET_MODE               1U
#define CAN_GLB_TEST_MODE                2U

/* ---- channel canfd config ---- */
#define BRS_BIT_SET                      1U
#define BRS_BIT_CLEAR                    0U
#define CLASSICAL_FRAME                  0U
#define CANFD_FRAME                      1U
#define CH_ERROR_STATE                   0U
#define BUFF_ESI_BIT                     1U
#define MEASURE_AND_OFFSET               0U
#define OFFSET_ONLY                      1U
#define ALL_TX_RX_MESSAGE                0U
#define ALL_TX_MESSAGE                   1U
#define ALL_RX_MESSAGE                   2U
#define ONLY_TX_RX_DATA_PHASE            4U
#define ONLY_TX_DATA_PHASE               5U
#define ONLY_RX_DATA_PHASE               6U

/* ---- Rx buffer ---- */
#define CAN_RBSIZE_8BYTE                 0U
#define CAN_RBSIZE_12BYTE                1U
#define CAN_RBSIZE_16BYTE                2U
#define CAN_RBSIZE_20BYTE                3U

/* ---- FIFO (Rx, Common) interrupt generation timing ---- */
#define CAN_FIFO_THRESHOLD_1_8           0U
#define CAN_FIFO_THRESHOLD_2_8           1U
#define CAN_FIFO_THRESHOLD_3_8           2U
#define CAN_FIFO_THRESHOLD_4_8           3U
#define CAN_FIFO_THRESHOLD_5_8           4U
#define CAN_FIFO_THRESHOLD_6_8           5U
#define CAN_FIFO_THRESHOLD_7_8           6U
#define CAN_FIFO_THRESHOLD_FULL          7U

/* ---- FIFO (Rx, Common) interrupt factor ---- */
#define CAN_FIFO_INT_THRESHOLD           0U
#define CAN_FIFO_INT_EACH_MSG            1U

/* ---- FIFO (Rx, Common) depth define ---- */
#define CAN_FIFO_DEPTH_0                 0U
#define CAN_FIFO_DEPTH_4                 1U
#define CAN_FIFO_DEPTH_8                 2U
#define CAN_FIFO_DEPTH_16                3U
#define CAN_FIFO_DEPTH_32                4U
#define CAN_FIFO_DEPTH_48                5U
#define CAN_FIFO_DEPTH_64                6U
#define CAN_FIFO_DEPTH_128               7U

/* ---- FIFO (Rx, Common) RFPLS define ---- */
#define CAN_FIFO_RFPLS_8                 0U
#define CAN_FIFO_RFPLS_12                1U
#define CAN_FIFO_RFPLS_16                2U
#define CAN_FIFO_RFPLS_20                3U
#define CAN_FIFO_RFPLS_24                4U
#define CAN_FIFO_RFPLS_32                5U
#define CAN_FIFO_RFPLS_48                6U
#define CAN_FIFO_RFPLS_64                7U

/* ---- FIFO (TX/Rx, Common) CFPLS define ---- */
#define CAN_FIFO_CFPLS_8                 0U
#define CAN_FIFO_CFPLS_12                1U
#define CAN_FIFO_CFPLS_16                2U
#define CAN_FIFO_CFPLS_20                3U
#define CAN_FIFO_CFPLS_24                4U
#define CAN_FIFO_CFPLS_32                5U
#define CAN_FIFO_CFPLS_48                6U
#define CAN_FIFO_CFPLS_64                7U

/* ---- Tx buffer ---- */
#define CAN_TX_BUFFER_0                  0U
#define CAN_TX_BUFFER_1                  1U
#define CAN_TX_BUFFER_2                  2U
#define CAN_TX_BUFFER_3                  3U
#define CAN_TX_BUFFER_4                  4U
#define CAN_TX_BUFFER_5                  5U
#define CAN_TX_BUFFER_6                  6U
#define CAN_TX_BUFFER_7                  7U
#define CAN_TX_BUFFER_8                  8U
#define CAN_TX_BUFFER_9                  9U
#define CAN_TX_BUFFER_10                10U
#define CAN_TX_BUFFER_11                11U
#define CAN_TX_BUFFER_12                12U
#define CAN_TX_BUFFER_13                13U
#define CAN_TX_BUFFER_14                14U
#define CAN_TX_BUFFER_15                15U

/* ---- Common FIFO interval time counter source ---- */
#define CAN_IT_PCLOCK                    0U
#define CAN_IT_CAN_BIT_CLK               1U
#define CAN_IT_PCLOCK_10                 2U

/* ---- Common FIFO mode ---- */
#define CAN_TRFIFO_RX_MODE               0U
#define CAN_TRFIFO_TX_MODE               1U
#define CAN_TRFIFO_GW_MODE               2U

/* ---- TX queue interrupt factor ---- */
#define CAN_TX_QUEUE_INT_EMPTY           0U
#define CAN_TX_QUEUE_INT_EACH_MSG        1U

/* ---- TX queue depth define ---- */
#define CAN_TX_QUEUE_DEPTH_0             0U
#define CAN_TX_QUEUE_DEPTH_3             2U
#define CAN_TX_QUEUE_DEPTH_4             3U
#define CAN_TX_QUEUE_DEPTH_5             4U
#define CAN_TX_QUEUE_DEPTH_6             5U
#define CAN_TX_QUEUE_DEPTH_7             6U
#define CAN_TX_QUEUE_DEPTH_8             7U
#define CAN_TX_QUEUE_DEPTH_9             8U
#define CAN_TX_QUEUE_DEPTH_10            9U
#define CAN_TX_QUEUE_DEPTH_11           10U
#define CAN_TX_QUEUE_DEPTH_12           11U
#define CAN_TX_QUEUE_DEPTH_13           12U
#define CAN_TX_QUEUE_DEPTH_14           13U
#define CAN_TX_QUEUE_DEPTH_15           14U
#define CAN_TX_QUEUE_DEPTH_16           15U

#endif /* CAN_SFR_H */
