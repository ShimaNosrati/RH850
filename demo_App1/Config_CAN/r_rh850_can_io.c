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
* File Name    : r_rh850_can_io.c 
* Version	    : 1.10
* Device(s) 	: RH850/U2A
* Description  : This is source file for CAN I/O registers..
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
* : 31.10.2020 	1.00 	First Release
* : 30.06.2022 	1.10 	Modified for RH850/U2A6
******************************************************************************/
#include "can_drv.h"
#include "r_rh850_can_sfr.h"
#include "base_macrodef.h"
#include "iodefine.h"

#define PORT_PKCPROT				(* (volatile unsigned int *) 0xFFD92F40)
#define PORT_PWE				(* (volatile unsigned int *) 0xFFD92F44)
#define PORT_PCR4_9				(* (volatile unsigned int *) 0xFFD92124)
#define PORT_PCR4_10				(* (volatile unsigned int *) 0xFFD92140)
#define PORT_PCR6_7				(* (volatile unsigned int *) 0xFFD9219C)
#define PORT_PCR6_8				(* (volatile unsigned int *) 0xFFD921A0)
#define PORT_PCR6_13				(* (volatile unsigned int *) 0xFFD921B4)
#define PORT_PCR6_14				(* (volatile unsigned int *) 0xFFD921B8)


/****************************************************************************** 
* Function Name: PORT_Init
* Description  : IO Port init
* Arguments    : none 
* Return Value : none -
******************************************************************************/
void PORT_Init(void)
{

	PORT_PKCPROT = 0xA5A5A501;
	PORT_PWE     = 0x0ffffffe;

		if ((g_ch_use_table[0] & CAN_USE) == CAN_USE) {
		PORT_PCR6_13 = 0x00000053;			/* CAN0RX(P6_13/ALT4 IN)	*/
		PORT_PCR6_14 = 0x00000043;			/* CAN0TX(P6_14/ALT4 OUT)	*/
		}

		if ((g_ch_use_table[1] & CAN_USE) == CAN_USE) {
		#if defined(__QFP_144__) 
  			PORT_PCR4_10 = 0x00000052; /* CAN1RX(P4_10/ALT3 IN)	*/
  			PORT_PCR4_9 = 0x00000042; /* CAN1TX(P4_9/ALT3 OUT)	*/
		#else
  			PORT_PCR6_7 = 0x00000051; /* CAN1RX(P6_7/ALT2 IN)	*/
  			PORT_PCR6_8 = 0x00000041; /* CAN1TX(P6_8/ALT2 OUT)	*/
		#endif
 		}
}

