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
/******************************************************************************* 
* File Name    : r_rh850_can_int.c 
* Version	    : 1.10
* Device(s) 	: RH850/U2A
* Description  : This is source file for CAN interrupt registers..
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
* : 31.10.2020 	1.00 	First Release
* : 30.06.2022 	1.10 	Modified for RH850/U2A6
******************************************************************************/
#include "iodefine.h"
#include "can_drv.h"
/****************************************************************************** 
* Function Name: R_CAN_Tx_IRQ_init
* Description  : Tx Interrupt initialize
* Arguments    : none 
* Return Value : none -
******************************************************************************/
void R_CAN_Tx_IRQ_init(void)
{

	INTC2.EIBD300.UINT32	= 0x00000000;	// Interrupt is bound to PE0
//	INTC2.EIBD300.UINT32	= 0x00000001;	// Interrupt is bound to PE1
//	INTC2.EIBD300.UINT32	= 0x00000002;	// Interrupt is bound to PE2
//	INTC2.EIBD300.UINT32	= 0x00000003;	// Interrupt is bound to PE3
	INTC2.EIC300.UINT16	= 0x004F;

}
/****************************************************************************** 
* Function Name: R_CAN_RxFIFO_IRQ_init
* Description  : RxFIFO Interrupt initialize
* Arguments    : none 
* Return Value : none -
******************************************************************************/
void R_CAN_RxFIFO_IRQ_init(void)
{

	INTC2.EIBD297.UINT32	= 0x00000000;	// Interrupt is bound to PE0
//	INTC2.EIBD297.UINT32	= 0x00000001;	// Interrupt is bound to PE1
//	INTC2.EIBD297.UINT32	= 0x00000002;	// Interrupt is bound to PE2
//	INTC2.EIBD297.UINT32	= 0x00000003;	// Interrupt is bound to PE3
	INTC2.EIC297.UINT16	= 0x004F;

}

/****************************************************************************** 
* Function Name: R_CAN_TxRxFIFO_IRQ_init
* Description  : TxRxFIFO Interrupt initialize
* Arguments    : none 
* Return Value : none -
******************************************************************************/
void R_CAN_TxRxFIFO_IRQ_init(void)
{

	INTC2.EIBD302.UINT32	= 0x00000000;	// Interrupt is bound to PE0
//	INTC2.EIBD302.UINT32	= 0x00000001;	// Interrupt is bound to PE1
//	INTC2.EIBD302.UINT32	= 0x00000002;	// Interrupt is bound to PE2
//	INTC2.EIBD302.UINT32	= 0x00000003;	// Interrupt is bound to PE3
	INTC2.EIC302.UINT16	= 0x004F;

}
