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
* File Name        : Config_PORT.c
* Component Version: 1.6.0
* Device(s)        : R7F702301EABG
* Description      : This file implements device driver for Config_PORT.
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
#include "Config_PORT.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_PORT_Create
* Description  : This function initializes the PORT
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_PORT_Create(void)
{
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = _PORT_PWEP02_WRITE_ENABLE | _PORT_PWEP06_WRITE_ENABLE;
    PORT0.PIBC2.UINT16 = _PORT_PIBC_INIT;
    PORT0.PIBC6.UINT16 = _PORT_PIBC_INIT;
    PORT0.PBDC2.UINT16 = _PORT_PBDC_INIT;
    PORT0.PBDC6.UINT16 = _PORT_PBDC_INIT;
    PORT0.PM2.UINT16 = _PORT_PM_INIT;
    PORT0.PM6.UINT16 = _PORT_PM_INIT;
    PORT0.PMC2.UINT16 = _PORT_PMC_INIT;
    PORT0.PMC6.UINT16 = _PORT_PMC_INIT;
    PORT0.PIPC2.UINT16 = _PORT_PIPC_INIT;
    PORT0.PIPC6.UINT16 = _PORT_PIPC_INIT;
    /* PORT2 setting */
    PORT0.PDSC2.UINT16 = _PORT_PDSCn1_DRIVE_STRENGTH_0 | _PORT_PDSCn6_DRIVE_STRENGTH_0 | _PORT_PDSCn7_DRIVE_STRENGTH_0;
    PORT0.PUCC2.UINT16 = _PORT_PUCCn1_DRIVE_STRENGTH_0 | _PORT_PUCCn6_DRIVE_STRENGTH_0 | _PORT_PUCCn7_DRIVE_STRENGTH_0;
    PORT0.PODC2.UINT16 = _PORT_PODCn1_PUSH_PULL | _PORT_PODCn6_PUSH_PULL | _PORT_PODCn7_PUSH_PULL;
    PORT0.PINV2.UINT16 = _PORT_PINVn1_OUTPUTINVERTED_OFF | _PORT_PINVn6_OUTPUTINVERTED_OFF | 
                         _PORT_PINVn7_OUTPUTINVERTED_OFF;
    PORT0.PBDC2.UINT16 = _PORT_PBDCn1_MODE_DISABLED | _PORT_PBDCn6_MODE_DISABLED | _PORT_PBDCn7_MODE_DISABLED;
    PORT0.PU2.UINT16 = _PORT_PUn0_PULLUP_OFF | _PORT_PUn2_PULLUP_OFF | _PORT_PUn3_PULLUP_OFF | _PORT_PUn4_PULLUP_OFF | 
                       _PORT_PUn5_PULLUP_OFF | _PORT_PUn8_PULLUP_OFF | _PORT_PUn9_PULLUP_OFF | 
                       _PORT_PUn10_PULLUP_OFF | _PORT_PUn11_PULLUP_OFF | _PORT_PUn12_PULLUP_OFF | 
                       _PORT_PUn13_PULLUP_OFF | _PORT_PUn14_PULLUP_OFF | _PORT_PUn15_PULLUP_OFF;
    PORT0.PD2.UINT16 = _PORT_PDn0_PULLDOWN_OFF | _PORT_PDn2_PULLDOWN_OFF | _PORT_PDn3_PULLDOWN_OFF | 
                       _PORT_PDn4_PULLDOWN_OFF | _PORT_PDn5_PULLDOWN_OFF | _PORT_PDn8_PULLDOWN_OFF | 
                       _PORT_PDn9_PULLDOWN_OFF | _PORT_PDn10_PULLDOWN_OFF | _PORT_PDn11_PULLDOWN_OFF | 
                       _PORT_PDn12_PULLDOWN_OFF | _PORT_PDn13_PULLDOWN_OFF | _PORT_PDn14_PULLDOWN_OFF | 
                       _PORT_PDn15_PULLDOWN_OFF;
    PORT0.PIS2.UINT16 = _PORT_PISn0_TYPE_SHMT1 | _PORT_PISn2_TYPE_SHMT1 | _PORT_PISn3_TYPE_SHMT1 | 
                        _PORT_PISn4_TYPE_SHMT1 | _PORT_PISn5_TYPE_SHMT1 | _PORT_PISn8_TYPE_SHMT1 | 
                        _PORT_PISn9_TYPE_SHMT1 | _PORT_PISn10_TYPE_SHMT1 | _PORT_PISn11_TYPE_SHMT1 | 
                        _PORT_PISn12_TYPE_SHMT1 | _PORT_PISn13_TYPE_SHMT1 | _PORT_PISn14_TYPE_SHMT1 | 
                        _PORT_PISn15_TYPE_SHMT1;
    PORT0.PISA2.UINT16 = _PORT_PISAn2_TYPE_SHMT1_OR_SHMT4 | _PORT_PISAn3_TYPE_SHMT1_OR_SHMT4 | 
                         _PORT_PISAn4_TYPE_SHMT1_OR_SHMT4 | _PORT_PISAn8_TYPE_SHMT1_OR_SHMT4 | 
                         _PORT_PISAn9_TYPE_SHMT1_OR_SHMT4 | _PORT_PISAn10_TYPE_SHMT1_OR_SHMT4 | 
                         _PORT_PISAn11_TYPE_SHMT1_OR_SHMT4 | _PORT_PISAn12_TYPE_SHMT1_OR_SHMT4 | 
                         _PORT_PISAn13_TYPE_SHMT1_OR_SHMT4 | _PORT_PISAn14_TYPE_SHMT1_OR_SHMT4 | 
                         _PORT_PISAn15_TYPE_SHMT1_OR_SHMT4;
    PORT0.P2.UINT16 = _PORT_Pn1_OUTPUT_LOW | _PORT_Pn6_OUTPUT_LOW | _PORT_Pn7_OUTPUT_LOW;
    PORT0.PM2.UINT16 = _PORT_PMn0_MODE_UNUSED | _PORT_PMn1_MODE_OUTPUT | _PORT_PMn2_MODE_UNUSED | 
                       _PORT_PMn3_MODE_UNUSED | _PORT_PMn4_MODE_UNUSED | _PORT_PMn5_MODE_UNUSED | 
                       _PORT_PMn6_MODE_OUTPUT | _PORT_PMn7_MODE_OUTPUT | _PORT_PMn8_MODE_INPUT | 
                       _PORT_PMn9_MODE_UNUSED | _PORT_PMn10_MODE_UNUSED | _PORT_PMn11_MODE_UNUSED | 
                       _PORT_PMn12_MODE_UNUSED | _PORT_PMn13_MODE_UNUSED | _PORT_PMn14_MODE_UNUSED | 
                       _PORT_PMn15_MODE_UNUSED;
    PORT0.PIBC2.UINT16 = _PORT_PIBCn8_INPUT_BUFFER_ENABLE;
    PORT0.PSFC2.UINT16 = _PORT_PSFCn1_SAFE_DISABLE | _PORT_PSFCn6_SAFE_DISABLE | _PORT_PSFCn7_SAFE_DISABLE;
    /* PORT6 setting */
    PORT0.PDSC6.UINT16 = _PORT_PDSC6_DEFAULT_VALUE | _PORT_PDSCn6_DRIVE_STRENGTH_0 | _PORT_PDSCn12_DRIVE_STRENGTH_0;
    PORT0.PUCC6.UINT16 = _PORT_PUCC6_DEFAULT_VALUE | _PORT_PUCCn6_DRIVE_STRENGTH_0 | _PORT_PUCCn12_DRIVE_STRENGTH_0;
    PORT0.PODC6.UINT16 = _PORT_PODCn6_PUSH_PULL | _PORT_PODCn12_PUSH_PULL;
    PORT0.PINV6.UINT16 = _PORT_PINVn6_OUTPUTINVERTED_OFF | _PORT_PINVn12_OUTPUTINVERTED_OFF;
    PORT0.PBDC6.UINT16 = _PORT_PBDCn6_MODE_DISABLED | _PORT_PBDCn12_MODE_DISABLED;
    PORT0.P6.UINT16 = _PORT_Pn6_OUTPUT_LOW | _PORT_Pn12_OUTPUT_LOW;
    PORT0.PM6.UINT16 = _PORT_PM6_DEFAULT_VALUE | _PORT_PMn0_MODE_UNUSED | _PORT_PMn2_MODE_UNUSED | 
                       _PORT_PMn3_MODE_UNUSED | _PORT_PMn4_MODE_UNUSED | _PORT_PMn5_MODE_UNUSED | 
                       _PORT_PMn6_MODE_OUTPUT | _PORT_PMn7_MODE_UNUSED | _PORT_PMn8_MODE_UNUSED | 
                       _PORT_PMn9_MODE_UNUSED | _PORT_PMn10_ALTERNATIVE_MODE_UNUSED | _PORT_PMn11_MODE_UNUSED | 
                       _PORT_PMn12_MODE_OUTPUT | _PORT_PMn13_MODE_UNUSED | _PORT_PMn14_MODE_UNUSED | 
                       _PORT_PMn15_MODE_UNUSED;
    PORT0.PSFC6.UINT16 = _PORT_PSFCn6_SAFE_DISABLE | _PORT_PSFCn12_SAFE_DISABLE;
    PORT0.PWE = _PORT_PWEP02_WRITE_DISABLE | _PORT_PWEP06_WRITE_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;
    /* Synchronization processing */
    g_cg_sync_read = PORT0.PM2.UINT16;
    __syncp();

    R_Config_PORT_Create_UserInit();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
