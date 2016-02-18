#include "stdafx.h"
#include "parser.h"


bool InitParser(ParserBase *pParserBase);


bool InitNewParserBase( 
	bool (*ProcessFrame)(  char* buf, int len, int count ),
	bool (*InvalidFrame)(  char* buf, int len ),
	bool (*IsFrameHeader)( char* buf ),
	bool (*IsValidFrame)( char* buf, int len ),
	PARSE_PARAM *pParam,
	ParserBase *pParserBase)
{
	pParserBase->ProcessFrame = ProcessFrame;
	pParserBase->InvalidFrame = InvalidFrame;
	
	pParserBase->IsFrameHeader = IsFrameHeader;
	pParserBase->IsValidFrame = IsValidFrame;

	pParserBase->m_bInited = false;
	pParserBase->m_magicCode = pParam->magic_code;
	
	pParserBase->m_pTempBuf = NULL;
	pParserBase->m_tempBufLen = pParam->temp_buf_len;
	pParserBase->m_pTempDataEnd = NULL;
	
	pParserBase->m_pHeaderBuf = NULL;
	pParserBase->m_minHeaderSize = pParam->frame_header_max_len;
	pParserBase->m_pHeaderDataEnd = NULL;

	pParserBase->m_count = pParam->m_count;

	return InitParser(pParserBase);
}

bool InitParser(ParserBase *pParserBase)
{
	if (pParserBase->m_bInited) {
		return true;
	}
	if (pParserBase->m_tempBufLen <= pParserBase->m_minHeaderSize)
		return false;

	if( pParserBase->m_pTempBuf )
	{
		free(pParserBase->m_pTempBuf);
		pParserBase->m_pTempBuf = NULL;
	}
	
	if( pParserBase->m_pHeaderBuf )
	{
		free(pParserBase->m_pHeaderBuf);
		pParserBase->m_pHeaderBuf = NULL;
	}

	pParserBase->m_pTempBuf = (char*)malloc(pParserBase->m_tempBufLen);//new char[pParserBase->m_tempBufLen];
	if( !pParserBase->m_pTempBuf )
		return false;

	pParserBase->m_pHeaderBuf = (char*)malloc(pParserBase->m_minHeaderSize);//new char[pParserBase->m_minHeaderSize];
	if( !pParserBase->m_pHeaderBuf )
	{
		free(pParserBase->m_pTempBuf);
		pParserBase->m_pTempBuf = NULL;
		return false;
	}

	pParserBase->m_pTempDataEnd = pParserBase->m_pTempBuf;
	pParserBase->m_pHeaderDataEnd = pParserBase->m_pHeaderBuf;	

	pParserBase->m_bInited = true;
	return true;

}

bool DeInitParser(ParserBase*pParserBase)
{
	if (!pParserBase->m_bInited) {
		return true;
	}

	pParserBase->m_magicCode = 0;

	if( pParserBase->m_pTempBuf )
	{
		free(pParserBase->m_pTempBuf);
		pParserBase->m_pTempBuf = NULL;
	}
	pParserBase->m_tempBufLen = 0;
	pParserBase->m_pTempDataEnd = NULL;
	
	if( pParserBase->m_pHeaderBuf )
	{
		free(pParserBase->m_pHeaderBuf);
		pParserBase->m_pHeaderBuf = NULL;
	}
	pParserBase->m_minHeaderSize = 0;
	pParserBase->m_pHeaderDataEnd = NULL;

	pParserBase->m_bInited = false;
	return true;
}

bool ResetParser(ParserBase*pParserBase)
{
	if( !pParserBase->m_bInited )
		return true;

	EmptyTempDataBuf(pParserBase);
	EmptyHeaderBuf(pParserBase);

	return true;	
}


char* SearchForMagicCode( char* buf, int len ,ParserBase*pParserBase)
{
//		// assert 4 bytes aligned
//		assert( (len&0x3) == 0);

	unsigned int* pCurScan = (unsigned int*)buf;
	unsigned int* pStopScan = (unsigned int*)(buf+len);

	while ( pCurScan < pStopScan ) 
	{
		if ( *pCurScan == pParserBase->m_magicCode )
			return (char*) pCurScan;

		pCurScan++;
	}

	return (char*)pStopScan;		
}

char* SearchForValidHeader( char* buf, int len, bool* partial ,ParserBase *pParserBase)
{
	char* pBufStart = buf;
	char* pBufEnd = buf + len;
	char* pCurPos = pBufStart;

	while( pCurPos < pBufEnd )
	{
		char* pMagicCode = SearchForMagicCode( pCurPos, pBufEnd - pCurPos ,pParserBase);
		if (pBufEnd-pMagicCode >= pParserBase->m_minHeaderSize)
		{
			// found magic number
			if ( pParserBase->IsFrameHeader( pMagicCode ) )
			{
				*partial = false;
				return pMagicCode;
			}
			else
			{
				// !!!
				// alignment consideration
				pCurPos = pMagicCode + sizeof(unsigned int);
				continue;
			}
		}
		else if ( pMagicCode < pBufEnd )
		{
			// found magic number, but not enough data
			// to form a entire header
			*partial = true;
			return pMagicCode;
		}
		else
		{
			assert( pMagicCode == pBufEnd );

			// no magic code found
			*partial = false;
			return pBufEnd;
		}
	}	

	*partial = false;
	return pBufEnd;
}


char* ParseHelper_ParseNewBuffer( char* buf, int len ,ParserBase*pParserBase)
{


	char*   pBufStart = buf;
	char*	pBufEnd = buf + len;
	char*	pCurPos = pBufStart;

	bool	IsPartial;
	char*	pLastHeader;
	char*	pCurrHeader;

	assert( !HasTempData(pParserBase) );
	assert( !HasHeaderData(pParserBase) );	
		
	pCurrHeader = SearchForValidHeader( pCurPos, pBufEnd-pCurPos, &IsPartial ,pParserBase);
	
	if ( pCurrHeader != pBufEnd )
	{
		// found header
		if (IsPartial)
		{
			// partial header
			assert( pBufEnd-pCurrHeader < HeaderBufRemainLen(pParserBase) );
			AppendDataToHeaderBuf( pCurrHeader, pBufEnd-pCurrHeader ,pParserBase);
			return pBufEnd;
		}
		else
		{
			// entire header
			// do nothing, fall through
			pCurPos = pCurrHeader + pParserBase->m_minHeaderSize;
		}

	}
	else
	{
		// header not found
		return pBufEnd;
	}

	// now we've got first frame header

	while ( pCurPos < pBufEnd ) 
	{
		pLastHeader = pCurrHeader;
		pCurrHeader = SearchForValidHeader( pCurPos, pBufEnd-pCurPos, &IsPartial ,pParserBase);
		
		if ( pCurrHeader != pBufEnd )
		{
			// found header
			if (IsPartial)
			{
				// partial header
				if ( pCurrHeader-pLastHeader <= TempBufRemainLen(pParserBase) )
				{
					AppendDataToTempBuf( pLastHeader, pCurrHeader-pLastHeader ,pParserBase);
				}

				assert( pBufEnd-pCurrHeader < HeaderBufRemainLen(pParserBase) );
				AppendDataToHeaderBuf( pCurrHeader, pBufEnd-pCurrHeader ,pParserBase);

				return pBufEnd;
			}
			else
			{
				// entire header
				if ( pParserBase->IsValidFrame( pLastHeader, pCurrHeader-pLastHeader ) )
				{
					pParserBase->ProcessFrame (  pLastHeader, pCurrHeader-pLastHeader, pParserBase->m_count );
				}
				else
				{
					pParserBase->InvalidFrame (  pLastHeader, pCurrHeader-pLastHeader );
				}
				
				pCurPos = pCurrHeader + pParserBase->m_minHeaderSize;
				continue;
			}	
		}
		else
		{
			// header not found
			// copy the packet from last header till end (not entire)
			// to temp buffer
			if( pBufEnd-pLastHeader <= TempBufRemainLen(pParserBase) )
				AppendDataToTempBuf( pLastHeader, pBufEnd-pLastHeader ,pParserBase);

			return pBufEnd;
		}		
	}

	assert( pCurPos == pBufEnd );
	assert( pCurrHeader != pBufEnd && (pBufEnd-pCurrHeader==pParserBase->m_minHeaderSize ) );

	AppendDataToTempBuf( pCurrHeader, pParserBase->m_minHeaderSize ,pParserBase);

	return pBufEnd;
}

char* ParseHelper_ParseTempBuffer( char* buf, int len ,ParserBase*pParserBase)
{


	char*   pBufStart = buf;
	char*	pBufEnd = buf + len;
	char*	pCurPos = pBufStart;
	
	bool	IsPartial;
	char*	pFrameHeader;

	assert( HasTempData(pParserBase) );
	assert( !HasHeaderData(pParserBase) );	
		
	pFrameHeader = SearchForValidHeader( pCurPos, pBufEnd-pCurPos, &IsPartial ,pParserBase);
	if ( pFrameHeader != pBufEnd )
	{
		if (IsPartial)
		{
			if ( pFrameHeader-pBufStart <= TempBufRemainLen(pParserBase) )
			{
				AppendDataToTempBuf( pBufStart, pFrameHeader-pBufStart ,pParserBase);
			}
			else
			{
				// "large frame", drop
				EmptyTempDataBuf(pParserBase);
			}

			assert( pBufEnd-pFrameHeader < HeaderBufRemainLen(pParserBase) );
			AppendDataToHeaderBuf( pFrameHeader, pBufEnd-pFrameHeader ,pParserBase);
			return pBufEnd;
		}
		else
		{
			if ( pFrameHeader-pBufStart <= TempBufRemainLen(pParserBase) )
			{
				AppendDataToTempBuf( pBufStart, pFrameHeader-pBufStart ,pParserBase);
			
				if ( pParserBase->IsValidFrame(pParserBase->m_pTempBuf, TempDataLen(pParserBase)) )
					pParserBase->ProcessFrame(  pParserBase->m_pTempBuf, TempDataLen(pParserBase), pParserBase->m_count );
				else
					pParserBase->InvalidFrame(  pParserBase->m_pTempBuf, TempDataLen(pParserBase) );

				EmptyTempDataBuf(pParserBase);
			}
			else
			{
				EmptyTempDataBuf(pParserBase);
			}

			return pFrameHeader;
		}

	}
	else
	{
		if ( len <= TempBufRemainLen(pParserBase) )
		{
			AppendDataToTempBuf( buf, len ,pParserBase);
			return pBufEnd;
		}
		else
		{
			// "large frame"
			// drop it
			EmptyTempDataBuf(pParserBase);
			return pBufEnd;
		}
	}

}

char* ParseHelper_ParseTempHeader( char* buf, int len ,ParserBase*pParserBase)
{

	char*   pBufStart = buf;
	char*	pBufEnd = buf + len;
	char*	pCurPos = pBufStart;
	int	remain_len = HeaderBufRemainLen(pParserBase);
	
	assert( !HasTempData(pParserBase) );
	assert( HasHeaderData(pParserBase) );
		
	if ( len >= remain_len )
	{
		AppendDataToHeaderBuf( pCurPos, remain_len ,pParserBase);
		pCurPos += remain_len;

		if ( pParserBase->IsFrameHeader( pParserBase->m_pHeaderBuf) )
		{
			assert( pParserBase->m_minHeaderSize <= TempBufRemainLen(pParserBase) );
			AppendDataToTempBuf( pParserBase->m_pHeaderBuf, pParserBase->m_minHeaderSize ,pParserBase);
			EmptyHeaderBuf(pParserBase);
			return pCurPos;
		}
		else
		{
			bool	IsPartial;
			char*	pFrameHeader;
			
			pFrameHeader = SearchForValidHeader( pParserBase->m_pHeaderBuf + sizeof(int), pParserBase->m_minHeaderSize - sizeof(int), &IsPartial ,pParserBase);
			if ( pFrameHeader != HeaderBufEnd(pParserBase) )
			{
				assert( IsPartial );

				// move the partial header ahead to the start of the
				// temp header buffer		
				memmove( pParserBase->m_pHeaderBuf, pFrameHeader, HeaderBufEnd(pParserBase)-pFrameHeader );
				pParserBase->m_pHeaderDataEnd = pParserBase->m_pHeaderBuf + (HeaderBufEnd(pParserBase)-pFrameHeader);
				
				return pCurPos;
			}
			else
			{
				EmptyHeaderBuf(pParserBase);
				return pCurPos;
			}
		}
	}
	else
	{
		AppendDataToHeaderBuf( pBufStart, len ,pParserBase);
		return pBufEnd;
	}
}

char* ParseHelper_ParseTempHeaderAndBuffer( char* buf, int len ,ParserBase*pParserBase)
{

	
	char*   pBufStart = buf;
	char*	pBufEnd = buf + len;
	char*	pCurPos = pBufStart;
	
	int	remain_len = HeaderBufRemainLen(pParserBase);	
	
	assert( HasTempData(pParserBase) );
	assert( HasHeaderData(pParserBase) );
	

	if ( len >= remain_len )
	{
		AppendDataToHeaderBuf( pCurPos, remain_len ,pParserBase);
		pCurPos += remain_len;
		
		if ( pParserBase->IsFrameHeader(pParserBase->m_pHeaderBuf) )
		{
			// data in temp buffer is an entire frame
			// process it

			if ( pParserBase->IsValidFrame(pParserBase->m_pTempBuf, TempDataLen(pParserBase)) )
				pParserBase->ProcessFrame(  pParserBase->m_pTempBuf, TempDataLen(pParserBase), pParserBase->m_count );
			else
				pParserBase->InvalidFrame(  pParserBase->m_pTempBuf, TempDataLen(pParserBase) );
			
			EmptyTempDataBuf(pParserBase);
			
			AppendDataToTempBuf( pParserBase->m_pHeaderBuf, pParserBase->m_minHeaderSize ,pParserBase);
			EmptyHeaderBuf(pParserBase);

			return pCurPos;
		}
		else
		{
			bool	IsPartial;
			char*	pFrameHeader;
			
			pFrameHeader = SearchForValidHeader( pParserBase->m_pHeaderBuf + sizeof(int), pParserBase->m_minHeaderSize - sizeof(int), &IsPartial ,pParserBase);
			if ( pFrameHeader != HeaderBufEnd(pParserBase) )
			{
				assert( IsPartial );
				
				if( pFrameHeader-pParserBase->m_pHeaderBuf <= TempBufRemainLen(pParserBase) )
				{
					AppendDataToTempBuf( pParserBase->m_pHeaderBuf, pFrameHeader-pParserBase->m_pHeaderBuf ,pParserBase);
				}
				else
				{
					EmptyTempDataBuf(pParserBase);
				}
				
				// move the partial header ahead to the start of the
				// temp header buffer		
				memmove( pParserBase->m_pHeaderBuf, pFrameHeader, HeaderBufEnd(pParserBase)-pFrameHeader );
				pParserBase->m_pHeaderDataEnd = pParserBase->m_pHeaderBuf + (HeaderBufEnd(pParserBase)-pFrameHeader);
				
				return pCurPos;
			}
			else
			{
				if ( pParserBase->m_minHeaderSize <= TempBufRemainLen(pParserBase) )
				{
					AppendDataToTempBuf( pFrameHeader, pParserBase->m_minHeaderSize ,pParserBase);
				}
				else
				{
					EmptyTempDataBuf(pParserBase);
				}

				EmptyHeaderBuf(pParserBase);
				
				return pCurPos;
			}
		}
	}
	else
	{
		AppendDataToHeaderBuf( pBufStart, len ,pParserBase);
		return pBufEnd;
	}
}

void ParseBuffer( char* buf, int len ,ParserBase*pParserBase)
{
	char*	pBufStart = buf;
	char*   pBufEnd = buf+len;
	char*	pCurPos = pBufStart;
	
	if (!pParserBase->m_bInited) 
	{
		if(!InitParser(pParserBase))
			return;
	}

	while ( pCurPos < pBufEnd )
	{
		if( HasTempData(pParserBase) )
		{
			if( HasHeaderData(pParserBase) )
			{
				pCurPos = ParseHelper_ParseTempHeaderAndBuffer( pCurPos, pBufEnd-pCurPos, pParserBase  );
			}
			else
			{
				pCurPos = ParseHelper_ParseTempBuffer( pCurPos, pBufEnd-pCurPos, pParserBase  );					
			}
		}
		else
		{
			if( HasHeaderData(pParserBase) )
			{
				pCurPos = ParseHelper_ParseTempHeader( pCurPos, pBufEnd-pCurPos, pParserBase  );
			}
			else
			{
				pCurPos = ParseHelper_ParseNewBuffer( pCurPos, pBufEnd-pCurPos, pParserBase );
				
			}
		}		
	}

	if( HasTempData(pParserBase) )
	{
		if( pParserBase->IsValidFrame( pParserBase->m_pTempBuf, TempDataLen(pParserBase) ) )
		{
			pParserBase->ProcessFrame(  pParserBase->m_pTempBuf, TempDataLen(pParserBase), pParserBase->m_count );
			EmptyTempDataBuf(pParserBase);
		}
		else if ( HasHeaderData(pParserBase) )
		{
			AppendDataToTempBuf( pParserBase->m_pHeaderBuf, HeaderBufDataLen(pParserBase),pParserBase );
			if( pParserBase->IsValidFrame( pParserBase->m_pTempBuf, TempDataLen(pParserBase) ) )
			{
				pParserBase->ProcessFrame(  pParserBase->m_pTempBuf, TempDataLen(pParserBase), pParserBase->m_count );
				EmptyTempDataBuf(pParserBase);
				EmptyHeaderBuf(pParserBase);
			}
			else
			{
				DropDataAtTempBufEnd( HeaderBufDataLen(pParserBase),pParserBase );
			}
		}
	}
	return ;
}