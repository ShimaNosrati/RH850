/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/******************************************************************************
* File Name	    : interrupt0.c
* Version	    : 1.10
* Device(s) 	: RH850/U2A
* Description	: This is the main tutorial code.
******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
* : 31.10.2020 	1.00 	First Release
* : 30.06.2022 	1.10 	Modified for RH850/U2A6
******************************************************************************/

/******************************************************************************
header include
******************************************************************************/
#include "base_macrodef.h"			// Basic macro definitions
#include "can_drv.h"
#include "can_sfr.h"
#include "iodefine.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/
/* Functions */

/* Variables */
extern can_frame_t tx_buf_table[2];
/******************************************************************************
Private global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name: Can_Tx_IRQ
* Description  : Interrupt function
* Arguments    : none
* Return Value : none
*******************************************************************************/
#pragma interrupt Can_Tx_IRQ( enable=true, channel=300 ,callt=true, fpu=false)
void Can_Tx_IRQ(void)
{
	RSCFDnCFDTMSTSp(0, 0) = RSCFDnCFDTMSTSp(0, 0) & ~CAN_TXBUF_RSLT_BITS_ON;
	R_CAN_TrmByTxBuf(0,1,&tx_buf_table[1]);	/* Tx Buffer 1 transmission */
}
