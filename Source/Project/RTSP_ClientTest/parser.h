#ifndef	 __PARSER__
#define  __PARSER__

//#include "std.h"
#include <assert.h>

//#include "std_nod.h" 
//#include "inet_nod.h"


//#ifdef __cplusplus
//extern "C" {
//#endif



typedef struct 
{
	unsigned int	magic_code;
	int		temp_buf_len;
	int		frame_header_max_len;

	int		m_count;
}PARSE_PARAM;


typedef struct  {
	bool	m_bInited;
	
	char*	m_pTempBuf;
	int		m_tempBufLen;
	char*	m_pTempDataEnd;
	
	char*   m_pHeaderBuf;
	char*	m_pHeaderDataEnd;

	unsigned int 	m_magicCode;
	int		m_minHeaderSize;

	int		m_count;

	bool (*ProcessFrame)(  char* buf, int len, int count );
   	bool (*InvalidFrame)(  char* buf, int len );

	bool (*IsFrameHeader)( char* buf );
	bool (*IsValidFrame)( char* buf, int len ); 


}ParserBase;

bool InitNewParserBase( 
					   bool (*ProcessFrame)(  char* buf, int len, int count ),
					   bool (*InvalidFrame)(  char* buf, int len ),
					   bool (*IsFrameHeader)( char* buf ),
					   bool (*IsValidFrame)( char* buf, int len ),
					   PARSE_PARAM *pParam,
					   ParserBase *pParserBase);

bool DeInitParser(ParserBase*pParserBase);

void ParseBuffer( char* buf, int len ,ParserBase*pParserBase);

inline	bool HasTempData(ParserBase *pParserBase)
{
	return pParserBase->m_pTempDataEnd != pParserBase->m_pTempBuf;
}

inline	int TempDataLen(ParserBase *pParserBase)
{
	return pParserBase->m_pTempDataEnd - pParserBase->m_pTempBuf;
}


inline  int TempBufRemainLen( ParserBase * pParserBase)
{
	return pParserBase->m_tempBufLen - TempDataLen(pParserBase);
}

inline	void AppendDataToTempBuf(char* buf, int len, ParserBase * pParserBase)
{
	assert( len <= TempBufRemainLen(pParserBase) );
	memmove( pParserBase->m_pTempDataEnd, buf, len);
	pParserBase->m_pTempDataEnd += len;
}

inline  void DropDataAtTempBufEnd( int len , ParserBase * pParserBase)
{
	assert( len <= TempBufRemainLen(pParserBase) );
	pParserBase->m_pTempDataEnd -= len;		
}

inline	void EmptyTempDataBuf( ParserBase * pParserBase)
{
	pParserBase->m_pTempDataEnd = pParserBase->m_pTempBuf;
}

inline  bool HasHeaderData( ParserBase * pParserBase)
{
	return pParserBase->m_pHeaderDataEnd != pParserBase->m_pHeaderBuf;
}

inline	int HeaderBufDataLen( ParserBase * pParserBase)
{
	return pParserBase->m_pHeaderDataEnd - pParserBase->m_pHeaderBuf;
}

inline  int HeaderBufRemainLen( ParserBase * pParserBase)
{
	return pParserBase->m_minHeaderSize - HeaderBufDataLen(pParserBase);
}

inline	char* HeaderBufEnd( ParserBase * pParserBase)
{
	return pParserBase->m_pHeaderBuf + pParserBase->m_minHeaderSize; 
}

inline  void AppendDataToHeaderBuf( char* buf, int len , ParserBase * pParserBase)
{
	assert( len <= HeaderBufRemainLen(pParserBase) );
	memmove( pParserBase->m_pHeaderDataEnd, buf, len);
	pParserBase->m_pHeaderDataEnd += len;		
}

inline	void EmptyHeaderBuf( ParserBase * pParserBase)
{
	pParserBase->m_pHeaderDataEnd = pParserBase->m_pHeaderBuf;
}


//#ifdef __cplusplus
//}
//#endif /* extern "C" */


#endif /* __PARSER__ */


