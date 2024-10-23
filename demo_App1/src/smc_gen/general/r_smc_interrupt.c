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
* File Name        : r_smc_interrupt.c
* Version          : 1.4.0
* Device(s)        : R7F702301EABG
* Description      : None
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
#include "r_smc_interrupt.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
void R_Interrupt_Create(void)
{

}

void eiint297_enable_interrupt(void)
{
    /* Clear INTRCANGRECC0 request and enable operation */
    INTC2.EIC297.BIT.EIRF297 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC297.BIT.EIMK297 = _INT_PROCESSING_ENABLED;
}

void eiint297_disable_interrupt(void)
{
    /* Disable INTRCANGRECC0 operation and clear request */
    INTC2.EIC297.BIT.EIMK297 = _INT_PROCESSING_DISABLED;
    INTC2.EIC297.BIT.EIRF297 = _INT_REQUEST_NOT_OCCUR;
}

void eiint302_enable_interrupt(void)
{
    /* Clear INTRCAN1REC request and enable operation */
    INTC2.EIC302.BIT.EIRF302 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC302.BIT.EIMK302 = _INT_PROCESSING_ENABLED;
}

void eiint302_disable_interrupt(void)
{
    /* Disable INTRCAN1REC operation and clear request */
    INTC2.EIC302.BIT.EIMK302 = _INT_PROCESSING_DISABLED;
    INTC2.EIC302.BIT.EIRF302 = _INT_REQUEST_NOT_OCCUR;
}

void eiint303_enable_interrupt(void)
{
    /* Clear INTRCAN1TRX request and enable operation */
    INTC2.EIC303.BIT.EIRF303 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC303.BIT.EIMK303 = _INT_PROCESSING_ENABLED;
}

void eiint303_disable_interrupt(void)
{
    /* Disable INTRCAN1TRX operation and clear request */
    INTC2.EIC303.BIT.EIMK303 = _INT_PROCESSING_DISABLED;
    INTC2.EIC303.BIT.EIRF303 = _INT_REQUEST_NOT_OCCUR;
}

void eiint308_enable_interrupt(void)
{
    /* Clear INTRCAN3REC request and enable operation */
    INTC2.EIC308.BIT.EIRF308 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC308.BIT.EIMK308 = _INT_PROCESSING_ENABLED;
}

void eiint308_disable_interrupt(void)
{
    /* Disable INTRCAN3REC operation and clear request */
    INTC2.EIC308.BIT.EIMK308 = _INT_PROCESSING_DISABLED;
    INTC2.EIC308.BIT.EIRF308 = _INT_REQUEST_NOT_OCCUR;
}

void eiint309_enable_interrupt(void)
{
    /* Clear INTRCAN3TRX request and enable operation */
    INTC2.EIC309.BIT.EIRF309 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC309.BIT.EIMK309 = _INT_PROCESSING_ENABLED;
}

void eiint309_disable_interrupt(void)
{
    /* Disable INTRCAN3TRX operation and clear request */
    INTC2.EIC309.BIT.EIMK309 = _INT_PROCESSING_DISABLED;
    INTC2.EIC309.BIT.EIRF309 = _INT_REQUEST_NOT_OCCUR;
}

void eiint311_enable_interrupt(void)
{
    /* Clear INTRCAN4REC request and enable operation */
    INTC2.EIC311.BIT.EIRF311 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC311.BIT.EIMK311 = _INT_PROCESSING_ENABLED;
}

void eiint311_disable_interrupt(void)
{
    /* Disable INTRCAN4REC operation and clear request */
    INTC2.EIC311.BIT.EIMK311 = _INT_PROCESSING_DISABLED;
    INTC2.EIC311.BIT.EIRF311 = _INT_REQUEST_NOT_OCCUR;
}

void eiint312_enable_interrupt(void)
{
    /* Clear INTRCAN4TRX request and enable operation */
    INTC2.EIC312.BIT.EIRF312 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC312.BIT.EIMK312 = _INT_PROCESSING_ENABLED;
}

void eiint312_disable_interrupt(void)
{
    /* Disable INTRCAN4TRX operation and clear request */
    INTC2.EIC312.BIT.EIMK312 = _INT_PROCESSING_DISABLED;
    INTC2.EIC312.BIT.EIRF312 = _INT_REQUEST_NOT_OCCUR;
}

void eiint320_enable_interrupt(void)
{
    /* Clear INTRCAN7REC request and enable operation */
    INTC2.EIC320.BIT.EIRF320 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC320.BIT.EIMK320 = _INT_PROCESSING_ENABLED;
}

void eiint320_disable_interrupt(void)
{
    /* Disable INTRCAN7REC operation and clear request */
    INTC2.EIC320.BIT.EIMK320 = _INT_PROCESSING_DISABLED;
    INTC2.EIC320.BIT.EIRF320 = _INT_REQUEST_NOT_OCCUR;
}

void eiint321_enable_interrupt(void)
{
    /* Clear INTRCAN7TRX request and enable operation */
    INTC2.EIC321.BIT.EIRF321 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC321.BIT.EIMK321 = _INT_PROCESSING_ENABLED;
}

void eiint321_disable_interrupt(void)
{
    /* Disable INTRCAN7TRX operation and clear request */
    INTC2.EIC321.BIT.EIMK321 = _INT_PROCESSING_DISABLED;
    INTC2.EIC321.BIT.EIRF321 = _INT_REQUEST_NOT_OCCUR;
}
