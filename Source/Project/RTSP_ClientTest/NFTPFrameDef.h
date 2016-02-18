/************************************************************************
*
*	Copyrite (c) 北京诺德世讯科技开发有限公司研发部
*	All rights reserved.
*
*	NFTPFrameDef.h
*	各种NFTP帧定义
*
*	v0.1
*	Wen Ming, Li Yongbin
*	2005-6-28
*
************************************************************************/

#ifndef __NFTP_FRAME_DEF_H__
#define __NFTP_FRAME_DEF_H__

#define NFTP_STARTCODE 0x4E465450

/********************************************************************************************
*
* 注意：
*
*	1. 由于编译器的不同有可能造成定义的数据结构和对应的描述图不对应，这时候以描述图的结构为准。
*
*	2. 所有结构体定义字段全为网络序(大头序)。
*
*********************************************************************************************/


/******************************************************************
*
*   通用命令帧格式      客户端 －> 服务端
*
*                      32 bit
*   ____________|____________|_____________|____________|
*  |		    	start code (NFTP)                   |
*  |____________________________________________________|
*  |			reserve		  |        frame length     |
*  |__________________________|_________________________|
*  |			    	  command						|
*  |____________________________________________________|
*
*	不带参数命令帧按照通用命令帧格式
*	fram length = 12
*
*****************************************************************/

typedef struct tagNFTPGenCommFrame  
{
	unsigned int 	startCode;
	unsigned short	reserve;
	unsigned short  frameLen;
	char			comm[4];
} NFTP_GEN_COMM, *pNFTP_GEN_COMM;


/******************************************************************
*
*   带参数命令帧格式       客户端 －> 服务端
*
*                      32 bit
*   ____________|____________|_____________|____________|
*  |		    	start code (NFTP)                   |
*  |____________________________________________________|
*  |			type		  |        frame length     |
*  |__________________________|_________________________|
*  |			    	  command						|
*  |____________________________________________________|
*  |                      parameter                     |
*  |____________________________________________________|
*
*	frame length 为实际帧长度，包括“start code”
*
*****************************************************************/
typedef struct tagNFTPDiskPara  
{
	unsigned int 	dev_id;
	unsigned int 	partition_id;
	char			filename[64];
	unsigned int  	offset;
	unsigned int  	len;
	char 			dir[64];	
}NFTPDiskPara,*pNFTPDiskPara;


typedef struct tagNFTPUserFrame  
{
	unsigned int 	startCode;
	unsigned short	reserve;
	unsigned short  frameLen;
	char			comm[4];
	char			username[64];
} NFTP_USER_COMM, *pNFTP_USER_COMM;

typedef struct tagNFTPPassFrame  
{
	unsigned int 	startCode;
	unsigned short	reserve;
	unsigned short  frameLen;
	char			comm[4];
	char			password[64];
} NFTP_PASS_COMM, *pNFTP_PASS_COMM; 

typedef struct tagNFTPDownFrame  
{
	unsigned int 	startCode;
	unsigned short	reserve;
	unsigned short  frameLen;
	char			comm[4];
	NFTPDiskPara    para;
} NFTP_PARA_COMM, *pNFTP_PARA_COMM;

/******************************************************************
*
*   回复帧通用格式		服务端 -> 客户端
*
*							32 bit
*   ____________|_____________|_____________|___________|
*  |		    	start code (NFTP)                   |
*  |____________________________________________________|
*  | reply code |frm len high |    frame length low     |
*  |__________________________|_________________________|
*  |                       data                         |
*  |____________________________________________________|
*
*
*
*
*****************************************************************/

//普通回复
//frmLenH = 0, frmLenL = 8
typedef struct  tagNFTPCommonReply
{
	unsigned int 	startCode;
	unsigned char   replyCode;
	unsigned char	frmLenH;
	unsigned short	frmLenL;
} NFTP_COMMON_REPLY, *pNFTP_COMMON_REPLY;


//数据回复
typedef struct  tagNFTPDataReply
{
	unsigned int 	startCode;
	unsigned char   replyCode;
	unsigned char	frmLenH;
	unsigned short	frmLenL;
	unsigned char	data[4];
} NFTP_DATA_REPLY, *pNFTP_DATA_REPLY;

//回复代码定义 (reply code):
#define COMMAND_OK				60 
#define COMMAND_FAIL			61		
#define INVALID_COMMAND			62
#define INVALID_PARAMETER		63
#define SERVICE_READY			64	
#define SERVICE_NOOP			65	
#define SERVICE_ABORT			66	
#define SERVICE_CLOSE			67	
#define SERVICE_FULL			68	
#define SERVICE_BUSY			69
#define SERVICE_OVERTIME		70	
#define INVALID_ABORT			71


#define DLOG_FILE_READY			80
#define PLOG_FILE_READY			81
#define DOWN_FILE_READY			82
#define DLOG_FILE				83
#define PLOG_FILE				84
#define DOWN_FILE				85
#define DLOG_FILE_OVER			86
#define PLOG_FILE_OVER			87
#define DOWN_FILE_OVER			88
#define FILE_ERROR				89
#define ALL_FILE_OVER			90


#endif