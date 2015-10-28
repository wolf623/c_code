#ifndef SENDLOG_H_
#define SENDLOG_H_
/*
	Casa Systems Inc.
	Copyright (C) 2003, 2004
	All Rights Reserved.

	This file contains proprietary trade secrets of Casa Systems, Inc. 
	No part of this file may be reproduced or transmitted in any form 
	or by any means, electronic or mechanical, including photocopying 
	and	recording, for any purpose without the expressed written 
	permission of Casa Systems, Inc.    

	Module: Casa Logging

	File Name: casalog.h
  
	Author:  Shri Iyengar
	Date:    September 23, 2004

	Revision History:
*/

#ifdef __cplusplus
extern "C" {
#endif


#define LOG_PORTNUM     0xA5AC
#define int8_t char

enum Log_msg_type_E {
	LOG_MESSAGE,
	LOG_OCTET_MAC_FILE,
	LOG_OCTET_TLV_FILE,
	LOG_OCTET_IP_FILE,	
	LOG_CONFIG_TRIGGER
} ;

#define LOG_HOST		0x7F000001
#define LOG_HOST_1200		0x7F000001

typedef enum {
    L_CLI    = 0,
    L_SNMP   = 1,
    L_QAM    = 2,
    L_IMM    = 3,
    L_RPC    = 4,
    L_SYS    = 5,
    L_CMTS   = 6,
    L_DOCSIS_OB = 7, // obsoleted, docsis-log moved to snmpd
    L_ALARM  = 8,
    L_DPI    = 9,
    L_DMM    = 10,
    L_RNG    = 11,
    L_MAC    = 12,
    L_BPI    = 13,
    L_DCTS   = 14,
    L_EAM    = 15,
    L_LC     = 16,
    L_IPDR   = 17,
    L_IPSEC  = 18,
    L_ROUTER = 19,
    L_AAA    = 20,
    L_CSM_TRA = 21,
    L_CSM_POL = 22,
    L_CSM_FFT = 23,
    L_CSM_EVT = 24,
    L_CSM_FSM = 25,
    L_CSM_HOP = 26,
    L_CSM_ERR = 27,
    L_CDB = 28,
    L_CFG = 29,
    L_LBM =30,
    L_OTHER  = 31,
    L_NUMBERS
} LOG_MODULE; 

typedef enum LogLevel {
    L_EMERGENCIES   = 0,
    L_ALERTS        = 1,
    L_CRITICAL      = 2,
    L_ERRORS        = 3,
    L_WARNINGS      = 4,
    L_NOTIFICATIONS = 5,
    L_INFORMATIONAL = 6,
    L_DEBUGGING     = 7
} LOG_LEVEL;

enum {
	 LOGGER_TEXT_LEN = 255,
	 LOGGER_TEXT_SIZE // including the trailing '\0'
} ;

typedef struct logMsgData {
	long mtype;
	int8_t smmid; // for smm only, lcs just give 0

	LOG_MODULE module; 	
	LOG_LEVEL severity;
	unsigned long  id;	    
	char text[LOGGER_TEXT_SIZE];	    // this field should be the last one
} LOGMSGDATA, *P_LOGMSGDATA;


#ifdef QUAGGA_LIB

	#define	10K_SMM6		6
	#define 10K_SMM7		7
	extern void LOGFUNC(LOG_LEVEL severity, char *proto_name, const char *format, va_list ap);
	extern int quagga_smm_id;

#else

	extern void LOGFUNC(LOG_MODULE module, LOG_LEVEL severity, unsigned long eventId, const char* text, ...);

#endif /* END OF QUAGGA_LIB */




#ifdef __cplusplus
}
#endif

#endif


