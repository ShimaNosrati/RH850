/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018, 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Pin.c
* Version          : 1.0.0.0
* Device(s)        : R7F702301
* Description      : This file implements SMC pin code generation.
***********************************************************************************************************************/
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Pins_Create
* Description  : This function initializes Smart Configurator pins
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Pins_Create(void)
{
    /* Set CAN0RX(P6_13) pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(7U);
    PORT0.PCR6_13.UINT32 = (PORT0.PCR6_13.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR6_13.UINT32 |= _PCR_ALT_IN7;
    PORT0.PCR6_13.UINT32 |= _PCR_SET_PMC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set CAN0TX(P6_14) pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(7U);
    PORT0.PCR6_14.UINT32 = (PORT0.PCR6_14.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR6_14.UINT32 |= _PCR_ALT_OUT4;
    PORT0.PCR6_14.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR6_14.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR6_14.UINT32 &= _PCR_ALT_OUT_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set CAN1RX(P6_7) pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(7U);
    PORT0.PCR6_7.UINT32 = (PORT0.PCR6_7.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR6_7.UINT32 |= _PCR_ALT_IN7;
    PORT0.PCR6_7.UINT32 |= _PCR_SET_PMC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set CAN1TX(P6_8) pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(7U);
    PORT0.PCR6_8.UINT32 = (PORT0.PCR6_8.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR6_8.UINT32 |= _PCR_ALT_OUT2;
    PORT0.PCR6_8.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR6_8.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR6_8.UINT32 &= _PCR_ALT_OUT_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set CAN8RX(P22_3) pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(18U);
    PORT0.PCR22_3.UINT32 = (PORT0.PCR22_3.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR22_3.UINT32 |= _PCR_ALT_IN8;
    PORT0.PCR22_3.UINT32 |= _PCR_SET_PMC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set CAN8TX(P22_4) pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(18U);
    PORT0.PCR22_4.UINT32 = (PORT0.PCR22_4.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR22_4.UINT32 |= _PCR_ALT_OUT8;
    PORT0.PCR22_4.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR22_4.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR22_4.UINT32 &= _PCR_ALT_OUT_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

}