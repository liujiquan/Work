/*
 *	================NFTPParser.c====================
 */
#include "stdafx.h"
#include "winsock2.h"
#include "NFtpParser.h"

extern bool recv_data_parser(char *buff,int len);
static ParserBase	nftpParser;
//==============================================================================================
//Paser分析出完整一帧NFtp Packet
static bool ProcessNFtpBuf(char *buf,int len, int count)
{	
	if(!buf || len > NFTP_PKT_MAX_SIZE)
	{
		return false;
	}
	
	if( recv_data_parser(buf,len))
	{
		return true;	
	}
	
	return false;
}
//==============================================================================================
//无效的NFtp数据包
static bool InvalidNFtpBuf(char *buf,int len)
{
	return false;
}
//==============================================================================================
//NFtp数据包头有效
static bool IsNFtpPacketHeader(char *buf)
{
	pNFTP_COMMON_REPLY pNFtp = (pNFTP_COMMON_REPLY)buf;
	
	return(ntohl(pNFtp->startCode) == NFTP_STARTCODE);	
}
//==============================================================================================
//确认为完整的NFtp数据包
static bool IsNFtpPacket(char *buf,int len)
{
	pNFTP_COMMON_REPLY pNFtp = (pNFTP_COMMON_REPLY)buf;	
	
	return(ntohs(pNFtp->frmLenL) == len);

}
//==============================================================================================
//初始化Parser
void InitNFtpParser()
{
	PARSE_PARAM param;
	param.temp_buf_len = 32*1024;
	param.magic_code = htonl(NFTP_STARTCODE);
	param.frame_header_max_len = 8;

	InitNewParserBase(ProcessNFtpBuf, InvalidNFtpBuf, IsNFtpPacketHeader,
		IsNFtpPacket, &param, &nftpParser);
}
//==============================================================================================
//将数据放入Paser
void ProcessNFtpData(unsigned char *buf,int len)
{
	if(len)
	{
		ParseBuffer((char *)buf, len, &nftpParser);
	}
}
