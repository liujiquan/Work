//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   CyberxEncrypt.cpp
//* Author   :   liujiquan
//* DateTime :   12/10/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "CyberxEncrypt.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const unsigned short	g_nMaxLen = 2048;		//
const unsigned short	g_nMask = 0x07FF;		//
unsigned char g_szKeyData[] = 
{
	0x83,0x04,0x89,0x44,0x56,0x66,0xDF,0x24,0xE6,0x54,0x9A,0x3B,0x16,0x36,0x08,0x42,
	0x6B,0x56,0x4A,0x31,0x88,0x56,0x6B,0x0B,0x5C,0x6C,0x6A,0x42,0x8E,0x2E,0x6F,0x54,
	0x54,0x44,0xBD,0x2E,0x27,0x65,0x24,0x35,0xF0,0x2E,0xF5,0x79,0x96,0x4E,0xD6,0x52,
	0x1E,0x16,0xDE,0x18,0xC1,0x34,0xE2,0x16,0x98,0x28,0xDA,0x7E,0xD7,0x7E,0xC8,0x47,
	0xAB,0x5E,0x8D,0x1F,0x35,0x7C,0x82,0x38,0x3D,0x3C,0xD9,0x38,0x8B,0x56,0x14,0x02,
	0x0E,0x74,0x0D,0x79,0x3A,0x6F,0x65,0x7B,0x3E,0x50,0x59,0x55,0x01,0x2C,0x4D,0x63,
	0x10,0x04,0x86,0x24,0xD9,0x76,0xEF,0x70,0xED,0x4A,0xE3,0x51,0x1D,0x75,0x49,0x3E,
	0xAC,0x78,
};
/////////////////////////////////////////////////////////
// バイナリ テキスト変換

DWORD MfxMemToSting(CString& strString, LPCTSTR lpszMem, DWORD dwSize)
{
	LPTSTR pszT = strString.GetBuffer(dwSize * 2);

	for (DWORD i = 0; i < dwSize; i++)
	{
		sprintf(pszT, "%02X", (BYTE)*lpszMem);
		pszT += 2;
		lpszMem++;
	}
	*pszT = 0;
	strString.ReleaseBuffer();

	return dwSize * 2;
}

void MfxAddString(CString& strString,  LPCTSTR lpvSrc, DWORD dwSize)
{
	CString strT;
	MfxMemToSting(strT, lpvSrc, dwSize);
	strString += strT;
}

/////////////////////////////////////////////////////////
// テキスト バイナリ変換

void MfxStingToMem(LPTSTR lpszMem, LPCTSTR lpszString)
{
	LPCTSTR pszT = lpszString;

	while (*pszT != NULL)
	{
		*lpszMem = 0;
		for (int j = 1; j >= 0; j--)
		{
			*lpszMem += (*pszT <= '9') ? (*pszT - '0') << (4 * j) : (*pszT - 'A' + 10) << (4 * j);
			pszT++;
		}
		lpszMem++;
	}
}

///////////////////////////////////////////////////////////////////////////////////
// 暗号文の生成

CString Encryption(LPCTSTR lpszPlaintext, LPCTSTR lpvKeyData)
{
	unsigned short nRandomNo; 				//	任意の乱数値
	unsigned short nTableLen; 				//	種のテーブルの大きさ
	unsigned short nSeed;
	//	バッファ
	unsigned short* pD = new unsigned short[g_nMaxLen];
	unsigned short* pX = new unsigned short[g_nMaxLen];
	unsigned short* pY = new unsigned short[g_nMaxLen];
	unsigned short* pZ = new unsigned short[g_nMaxLen];
	unsigned long	m, n;
	short 			dsize;
	unsigned short	c, i, j, k, l, p, tmp;
	CString strCiphertext;

	int nRet = TRUE;


	//	バッファの取得

	if (pD && pX && pY && pZ && lpvKeyData)
	{
		nTableLen = *(WORD*)lpvKeyData;			// テーブル長
		nRandomNo = *(WORD*)(lpvKeyData + 2);	// 乱数値
		memcpy(pZ, lpvKeyData + 4, 110);		// 乱数表をコピー

		srand((UINT)time(NULL));				//	乱数の初期化

		//	種のテーブル展開

		m = ((unsigned long)rand()) << 16;
		m |= (unsigned long)rand();
		n = ((unsigned long)rand()) << 16;
		n |= (unsigned long)rand();
		i = (short)(m % (unsigned long)nTableLen);		//	種のテーブルオフセット
		j = (short)(n % (unsigned long)nTableLen);		//	種のテーブルオフセット

		if ( i > j )
			k = i;
		else
			k = j;										//	k に大きい方を入れる

		if (k >= 55)
		{
			for (c = 55; c <= k; c++)
				pZ[c] = pZ[c-24] - pZ[c-55];			//	種のテーブルを展開
		}

		//	乱数列の初期化

		nSeed = pZ[i];									//	種を取り出す
		pX[55] = nSeed;
		tmp = 1;
		for ( i = 1; i < 55; i++ )						//	種を刻んでばらまく
		{
			p = ( i * 21 ) % 55;
			pX[p] = tmp;
			tmp = nSeed - tmp;
			nSeed = pX[p];
		}
		for (i = 56; i < 256; i++) 						//	少しかきまぜておく
			pX[i] = pX[i - 24] - pX[i - 55];
		for (i = 0; i < 55; i++ )						//	値を５５個先頭へコピー
			pX[i] = pX[i + 200];

		nSeed = pZ[j];									//	種を取り出す
		pY[55] = nSeed;
		tmp = 1;
		for (i = 1; i < 55; i++)						//	種を刻んでばらまく
		{
			p = ( i * 21 ) % 55;
			pY[p] = tmp;
			tmp = nSeed - tmp;
			nSeed = pY[p];
		}
		for (i = 56; i < 256; i++) 						//	少しかきまぜておく
			pY[i] = pY[i - 24] - pY[i - 55];
		for (i = 0; i < 55; i++)						//	値を５５個先頭へコピー
			pY[i] = pY[i + 200];

		//	暗号化前の初期化
		i = 55;
		j = 55;
		l = 0;
		k = 1;
		pD[0] = nRandomNo;

		//	暗号化

		MfxAddString(strCiphertext, (char*)&m, sizeof(DWORD));		//	m の出力
		MfxAddString(strCiphertext, (char*)&n, sizeof(DWORD));		//	n の出力

		WORD nLen = g_nMaxLen * 2 - 2;
		while (*lpszPlaintext != NULL)
		{												//	平文を読み込む
			dsize = min(strlen(lpszPlaintext), nLen);
			strncpy(((char*)pD) + 2, lpszPlaintext, nLen);
			lpszPlaintext += dsize;

			dsize = (dsize + 1) / 2;					//	バイトの半端は切り上げておく
			dsize += 1; 								//	先頭に入れるパターン分
			for (k = 1; k < dsize; i++, j++, l++, k++)
			{											//	バッファをラウンドするようにマスク
				pX[i & g_nMask] = pX[(i - 24) & g_nMask] - pX[(i - 55) & g_nMask] - pD[k - 1];
				pY[j & g_nMask] = pY[(j - 24) & g_nMask] - pY[(j - 55) & g_nMask];
				while ((pX[i & g_nMask] + pY[j & g_nMask]) == 0)
				{										// 平文が丸出しにならないよう
					j++;
					pY[j & g_nMask] = pY[(j - 24) & g_nMask] - pY[(j - 55) & g_nMask];
				}
				pZ[l] = (pX[i & g_nMask] + pY[j & g_nMask]) ^ pD[k];
			}
			MfxAddString(strCiphertext, (char*)pZ, (dsize - 1) * 2);	//	暗号文の出力

			pD[0] = pD[dsize - 1];						//	出力した末尾をバッファ先頭へ
			k = 1;										//	次の平文開始位置
			l = 0;										//	暗号化バッファ先頭へセット
		}
	}

	if (pD)
		delete pD;
	if (pX)
		delete pX;
	if (pY)
		delete pY;
	if (pZ)
		delete pZ;

	return strCiphertext;
}


///////////////////////////////////////////////////////////////////////////////////
// 平文の生成

CString Decryption(LPCTSTR lpszCiphertext, LPCTSTR lpvKeyData)
{
	unsigned short	nRandomNo; 				//	任意の乱数値
	unsigned short	nTableLen; 				//	種のテーブルの大きさ
	unsigned short	nSeed;
	unsigned long	m, n;
	short 			dsize;
	unsigned short	c, i, j, k, l, p, tmp;
	CString strPlaintext = _T("");
	short nCiphertextLen = strlen(lpszCiphertext) / 2;

	if (nCiphertextLen < 8)
		return strPlaintext;

	//	バッファの取得
	unsigned short* pD = new unsigned short[g_nMaxLen];
	unsigned short* pX = new unsigned short[g_nMaxLen];
	unsigned short* pY = new unsigned short[g_nMaxLen];
	unsigned short* pZ = new unsigned short[g_nMaxLen];
	unsigned char* pC = new unsigned char[nCiphertextLen];

	if (pD && pX && pY && pZ && pC && lpvKeyData)
	{
		nTableLen = *(WORD*)lpvKeyData;			// テーブル長
		nRandomNo = *(WORD*)(lpvKeyData + 2);	// 乱数値
		memcpy(pZ, lpvKeyData + 4, 110);		// 乱数表をコピー

		MfxStingToMem((LPTSTR)pC, lpszCiphertext);

		m = *(DWORD*)pC; 		//	m の読みとり
		n = *(DWORD*)(pC + 4); 	//	n の読みとり

		//	種のテーブル展開

		i = (short)(m % (unsigned long)nTableLen);			//	種のテーブルオフセット
		j = (short)(n % (unsigned long)nTableLen);			//	種のテーブルオフセット

		k = (i > j) ? i : j;								//	k に大きい方を入れる
		if (k >= 55)
		{
			for (c = 55; c <= k; c++)
				pZ[c] = pZ[c - 24] - pZ[c - 55];			//	種のテーブルを展開
		}

		//	乱数列の初期化

		nSeed = pZ[i];										//	種を取り出す
		pX[55] = nSeed;
		tmp = 1;
		for (i = 1; i < 55; i++)							//	種を刻んでばらまく
		{
			p = ( i * 21 ) % 55;
			pX[p] = tmp;
			tmp = nSeed - tmp;
			nSeed = pX[p];
		}
		for (i = 56; i < 256; i++) 							//	少しかきまぜておく
			pX[i] = pX[i - 24] - pX[i - 55];
		for (i = 0; i < 55; i++)							//	値を５５個先頭へコピー
			pX[i] = pX[i + 200];

		nSeed = pZ[j];										//	種を取り出す
		pY[55] = nSeed;
		tmp = 1;
		for (i = 1; i < 55; i++)							//	種を刻んでばらまく
		{
			p = ( i * 21 ) % 55;
			pY[p] = tmp;
			tmp = nSeed - tmp;
			nSeed = pY[p];
		}
		for (i = 56; i < 256; i++) 							//	少しかきまぜておく
			pY[i] = pY[i - 24] - pY[i - 55];
		for (i = 0; i < 55; i++)							//	値を５５個先頭へコピー
			pY[i] = pY[i + 200];

		//	復号化前の初期化

		i = 55;
		j = 55;
		l = 0;
		k = 1;
		pD[0] = nRandomNo;

		//	復号化

		nCiphertextLen -= 8;
		int nRead = 8;

		while ((dsize = min(g_nMaxLen * 2 - 2, nCiphertextLen)) != 0)
		{													//	暗号を読み込む
			memcpy(pZ, pC + nRead, dsize);
			nRead += dsize;
			nCiphertextLen -= dsize;

			dsize /= 2; 									//	ワードサイズに直す
			dsize += 1; 									//	先頭に入れるパターン分
			for (k = 1; k < dsize; i++, j++, l++, k++)
			{												//	バッファをラウンドするようにマスク
				pX[i & g_nMask] = pX[(i - 24) & g_nMask] - pX[(i - 55) & g_nMask] - pD[k - 1];
				pY[j & g_nMask] = pY[(j - 24) & g_nMask] - pY[(j - 55) & g_nMask];
				short ss1 = pX[i & g_nMask];
				short ss2 = pY[j & g_nMask];
				short ss3;
				while ((pX[i & g_nMask] + pY[j & g_nMask]) == 0)
				{											// 平文が丸出しにならないよう
					j++;
					pY[j & g_nMask] = pY[(j - 24) & g_nMask] - pY[(j - 55) & g_nMask];
					ss3 = pY[j & g_nMask];
				}
				unsigned short  u1 = pX[i & g_nMask];
				unsigned short u2 = pY[j & g_nMask];
				unsigned short u3 = u1 + u2;
				unsigned short u4 = pZ[l];
				unsigned short u5 = u3 ^ u4;
				pD[k] = (pX[i & g_nMask] + pY[j & g_nMask]) ^ pZ[l];
			}
			*((char*)pD + (dsize - 1) * 2 + 2) = 0;
			strPlaintext += ((char*)pD) + 2;				//	平文の出力

			pD[0] = pD[dsize - 1];							//	出力した末尾をバッファ先頭へ
			k = 1;											//	次の平文開始位置
			l = 0;											//	暗号化バッファ先頭へセット
		}
	}

	if (pD)
		delete pD;
	if (pX)
		delete pX;
	if (pY)
		delete pY;
	if (pZ)
		delete pZ;
	if (pC)
		delete pC;

	return strPlaintext;
}
