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
* File Name    : base_macrodef.h 
* Version	    : 1.10
* Device(s) 	: RH850/U2A
* Description  : This is source file for basic macro definition.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
* : 31.10.2020 	1.00 	First Release
* : 30.06.2022 	1.10 	Modified for RH850/U2A6
******************************************************************************/

/*******************************************************************************
Macro definitions
*******************************************************************************/
/* Basic data types	*/
typedef   signed int        SI;     /*RH850:4byte*/
typedef unsigned int        UI;     /*RH850:4byte*/
typedef   signed char       SB;
typedef unsigned char       UB;
typedef   signed short      SW;
typedef unsigned short      UW;
typedef   signed long       SL;
typedef unsigned long       UL;
typedef   signed long long  SWL;
typedef unsigned long long  UWL;

/* Obtain number of array elements	*/
#define elementsof( a )		( sizeof(a) / sizeof(a[0]) )
/*-----<End of Macro definitions>-------------------------------------------------------*/
