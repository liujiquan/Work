//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   AsfInfo.h
//* Author   :   liujiquan
//* DateTime :   11/6/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __ASFINFO_H_2459134951B94A1895E650CFD52F4215__
#define __ASFINFO_H_2459134951B94A1895E650CFD52F4215__
#pragma once

#include "SuperGridCtrl/MySuperGrid.h"
/************************************************************************/
/* Define                                                               */
/************************************************************************/
#define ASFFILENAME _T("amano.asf")
#define ITEMVALUENULL(p)	if(p == NULL){	vt = _NULL;		return;	}
// Stream Properties Object Stream Type GUIDs
#define			ASF_Audio_Media				"F8699E40-5B4D-11CF-A8FD-00805F5C442B"	//"2B445C5F8000FDA811CF5B4DF8699E40"	 	
#define			ASF_Video_Media				"BC19EFC0-5B4D-11CF-A8FD-00805F5C442B"	//"2B445C5F8000FDA811CF5B4DBC19EFC0"	 
#define			ASF_Command_Media			"59DACFC0-59E6-11D0-A3AC-00A0C90348F6"	//"F64803C9A000ACA311D059E659DACFC0"	 	
#define			ASF_JFIF_Media				"B61BE100-5B4E-11CF-A8FD-00805F5C442B"	//"2B445C5F8000FDA811CF5B4EB61BE100"	 
#define			ASF_Degradable_JPEG_Media	"35907DE0-E415-11CF-A917-00805F5C442B"	//"2B445C5F800017A911CFE41535907DE0"	 
#define			ASF_File_Transfer_Media		"91BD222C-F21C-497A-8B6D-5AA86BFC0185"	//"8501FC6BA85A6D8B497AF21C91BD222C"	 
#define			ASF_Binary_Media			"3AFB65E2-47EF-40F2-AC2C-70A90D71D343"	//"43D3710DA9702CAC40F247EF3AFB65E2"	 

// 10.5	Stream Properties Object Error Correction Type GUIDs 
#define			ASF_No_Error_Correction		"20FB5700-5B55-11CF-A8FD-00805F5C442B"
#define			ASF_Audio_Spread			"BFC3CD50-618F-11CF-8BB2-00AA00B4E220"

/************************************************************************/
/* Struct                                                               */
/************************************************************************/
#ifdef DWORD64
#undef DWORD64
// UINT64
struct DWORD64
{
	DWORD dwValueLow;
	DWORD dwValueHi;
}DWORD64;
#endif
#define HIDWORD(dwwValue)	(DWORD)(dwwValue>>32)	
#define LODWORD(dwwValue)	(DWORD)(dwwValue)
// UINT128

struct DWORD128
{
	DWORD64 dwwValueLow;
	DWORD64 dwwValueHi;
	bool operator ==(const DWORD128& value)
	{
		return this->dwwValueLow == value.dwwValueLow && this->dwwValueHi == value.dwwValueHi;
	}
	bool operator ==(const CString& value)
	{
		CString strTemp;
//		strTemp.Format("%08X%08X%08X%08X",	HIDWORD(dwwValueHi), LODWORD(dwwValueHi),HIDWORD(dwwValueLow),LODWORD(dwwValueLow));
		DWORD d1 = LODWORD(dwwValueLow);
		WORD  w1 = (WORD)(dwwValueLow>>32);
		WORD  w2 = (WORD)(dwwValueLow>>48);
		WORD  w3 = (WORD)(dwwValueHi);
		DWORD64 d2 = dwwValueHi>>16;
		BYTE b1 = (BYTE)(d2);
		BYTE b2 = (BYTE)(d2>>8);
		BYTE b3 = (BYTE)(d2>>16);
		BYTE b4 = (BYTE)(d2>>24);
		BYTE b5 = (BYTE)(d2>>32);
		BYTE b6 = (BYTE)(d2>>40);
		
		strTemp.Format("%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",	d1, w1, w2, (BYTE)w3, (BYTE)(w3>>8), 
																			b1, b2, b3, b4, b5, b6);

		
		return strTemp == value;
	}
};

// HeaderObject
typedef  struct ASF_HeaderObject
{
	DWORD128		ObjectID;				// GUID
	DWORD64			ObjectSize;				// Object Size
	DWORD			dwHeaderObjectCount;	// Number of Header Objects
	BYTE			Reserved1;				// Alignment
	BYTE			Reserved2;				// architecture
}ASF_HeaderObject, *PASF_HeaderObject;

// Properties Object
#define BroadcastFlag(Flags)					(BYTE)(Flags&0x0001)
#define SeekableFlag(Flags)						(BYTE)(Flags&0x0002)
#define Reserved_PropertiesFlags(Flags)			(DWORD)(Flags&0xFFC)
typedef  struct ASF_PropertiesObject
{
	DWORD128		ObjectID;				// Object ID
	DWORD64			ObjectSize;				// Object Size
	DWORD128		FileIDGUID;				// File ID	GUID
	DWORD64			FileSize;				// File Size
	union 
	{		
		FILETIME	FileTime;				
		DWORD64		ddword64Value;			
	}CreationDate;							// Creation Date
	
	DWORD64			DataPacketsCount;		// Data Packets Count
	DWORD64			PlayDuration;			// Play Duration
	DWORD64			SendDuration;			// Send Duration
	DWORD64			Preroll;				// Preroll
	DWORD			Flags;					// Flags
//	BIT				BroadcastFlag;			// Broadcast Flag (bit 0)"),
//	BIT				SeekableFlag;			// Seekable Flag (bit 1)"),
//	BIT				Reserved[30];			// Reserved (bits 2 ¨C 31)"
	DWORD			MinDataPacketSize;		// Minimum Data Packet Size
	DWORD			MaxDataPacketSize;		// Maximum Data Packet Size
	DWORD			MaxBitrate;				// Maximum Bitrate
}ASF_PropertiesObject, *PASF_PropertiesObject;
// Clock Object
typedef  struct ASF_ClockObject
{
	DWORD128		ObjectID;					// Object ID
	DWORD64			ObjectSize;					// Object Size
	DWORD128		ClockType;					// Clock Type
	WORD			ClockSize;					// Clock Size	
	DWORD			ClockSpecificDataLength;	// Clock-Specific Data Length
}ASF_ClockObject;
// Stream Properties Object
#define StreamNumber_Flags(Flags)		(WORD)(Flags&0xFF7F)
#define Reserved_Flags(Flags)			(WORD)(Flags&0x7F80)
#define EncryptedContentFlag(Flags)		(BYTE)(Flags>>15)
typedef  struct ASF_StreamPropertiesObject
{
	DWORD128		ObjectID;					// Object ID
	DWORD64			ObjectSize;					// Object Size
	DWORD128		StreamType;					// Stream Type
	DWORD128		ErrorCorrectionType;		// Error Correction Type
	DWORD64			TimeOffset;					// Time Offset
	DWORD			TypeSpecificDataLength;		// Type-Specific Data Length
	DWORD			ErrorCorrectionDataLength;	// Error Correction Data Length
	WORD			Flags;						// Flags
//	BIT 			StreamNumber[7];			// Stream Number:Flags
//	BIT				Reserved;					// Reserved:Flags
//	BIT				EncryptedContentFlag;		// Encrypted Content Flag:Flags
	DWORD			Reserved;					// Reserved		
//	BYTE			TypeSpecificData;			// Type-Specific Data [varies]
//	BYTE			ErrorCorrectionData;		// Error Correction Data [varies]
}ASF_StreamPropertiesObject, *PASF_StreamPropertiesObject;

/************************************************************************/
/* ASF_StreamPropertiesObject.TypeSpecificData                                                                     */
/************************************************************************/
// ASF_Audio_Media								ASF_Audio_Media
typedef struct Audiomediatype	// WAVEFORMATEX[¼Ì³Ð²ÎÕÕ]
{	
	union	
	{	
		WORD	CodecID;						// CodecID
		WORD	FormatTag;						// Format Tag;
	};//CodecID_FormatTag
	WORD		NumberofChannels;				// NumberofChannels;			
	DWORD		SamplesPerSecond;				// SamplesPerSecond;			
	DWORD		AverageNumberofBytesPerSecond;	// AverageNumberofBytesPerSecon
	WORD		BlockAlignment;					// BlockAlignment;				
	WORD		BitsPerSample;					// BitsPerSample;				
	WORD		CodecSpecificDataSize;			// CodecSpecific Data Size;	
	BYTE		CodecSpecificData;				// CodecSpecific Data;			
}Audiomediatype;
// Video media type								ASF_Video_Media
typedef struct Videomediatype				
{	
	DWORD		EncodedImageWidth;			// Encoded Image Width;
	DWORD		EncodedImageHeight;			// Encoded Image Height
	BYTE		ReservedFlags;				// Reserved Flags;		
	WORD		FormatDataSize;				// Format Data Size;	
//	BITMAPINFOHEADER bitmapHeader;			// Format Data
	DWORD      	_FormatDataSize;			// Format Data Size;			
	LONG       	ImageWidth	;				// Image Width	;				
	LONG       	ImageHeight;				// Image Height;				
	WORD       	Reserved;					// Reserved;					
	WORD       	BitsPerPixelCount;			// Bits Per Pixel Count;		
	DWORD      	CompressionID;				// Compression ID;				
	DWORD      	ImageSize;					// Image Size;					
	LONG       	HorizontalPixelsPerMeter;	// Horizontal Pixels Per Meter;	
	LONG       	VerticalPixelsPerMeter;		// Vertical Pixels Per Meter;	
	DWORD      	ColorsUsedCount;			// Colors Used Count;			
	DWORD      	ImportantColorsCount;		// Important Colors Count;		
//	BYTE		CodecSpecificData;			// [varies]
}Videomediatype;
///Image media type
// JFIF/JPEG media type
typedef struct JFIF_JPEGmediatype				// ASF_JFIF_Media	
{	
	DWORD	Imagewidth;						// Image width
	DWORD	Imageheight;					// Image height	
	DWORD	Reserved;						// Reserved
}JFIF_JPEGmediatype;
// Degradable JPEG media type
typedef struct 	DegradableJPEGmediatype				// ASF_Degradable_JPEG_Media	
{	
	DWORD	Imagewidth;						// Image width
	DWORD	Imageheight;					// Image height	
	WORD	Reserved1;						// Reserved1
	WORD	Reserved2;						// Reserved2
	WORD	Reserved3;						// Reserved3
	WORD	Interchangedatalength;			// Interchange data length
//	BYTE	Interchange data		[varies]
}DegradableJPEGmediatype;
// File transfer and binary media types
typedef struct 	Filetransferandbinarymediatypes// ASF_File_Transfer_Media/	ASF_Binary_Media
{
	DWORD128	mediatype;					// media type;
	DWORD128	Mediasubtype;				// Media subtype;
	DWORD		Fixedsizesamples;			// Fixed-size samples;
	DWORD		Temporalcompression;		// Temporal compression;
	DWORD		Samplesize;					// Sample size;
	DWORD128	Formattype;					// Format type;
	DWORD		Formatdatasize;				// Format data size;
//	BYTE		Format data	See below	varies
}Filetransferandbinarymediatypes;
// Web streams/File transfer
typedef struct  mediaobjectsforWebstream {	
	WORD	Totalheaderlength;				// Total header len
	WORD	Partnumber;						// Part number			 
	WORD	Totalpartcount;					// Total part count
	WORD	Sampletype;						// Sample type		
	WCHAR*	URLstring;						// URL string[Varies]
}mediaobjectsforWebstream;
typedef struct Webstreams{
	WORD	Webstreamformatdatasize;		// Web stream format data size	
	WORD	Fixedsampleheadersize;			// Fixed sample header size	
	WORD	Versionnumber;					// Version number				
	WORD	Reserved;						// Reserved	
	mediaobjectsforWebstream	mediaobjects;// mediaobjectsforWebstream			
}Webstreams;

/************************************************************************/
/* ASF_StreamPropertiesObject.ErrorCorrectionData                                                                     */
/************************************************************************/
// Spread audio 
typedef struct Spreadaudio
{
	BYTE	Span;							// Span
	WORD	VirtualPacketLength;			// Virtual Packet Length
	WORD	VirtualChunkLength;				// Virtual Chunk Length
	WORD	SilenceDataLength;				// Silence Data Length
//	BYTE	Silence Data		;varies
}Spreadaudio;

/************************************************************************/
/*  Header Extension Object                                             */
/************************************************************************/
typedef struct ASF_HeaderExtensionObject
{
	DWORD128	ObjectID;					// Object ID				
	DWORD64		ObjectSize	;				// Object Size				
	DWORD128	ReservedField1;				// Reserved Field 1		
	WORD		ReservedField2;				// Reserved Field 2		
	DWORD		HeaderExtensionDataSize;	// Header Extension Data Size
//	BYTE		Header Extension Data[varies];		
}ASF_HeaderExtensionObject;
/************************************************************************/
/*   Codec List Object                                                  */
/************************************************************************/
typedef struct ASF_CodecListObject  
{
	DWORD128	ObjectID;					// Object ID		
	DWORD64		ObjectSize;					// Object Size		
	DWORD128	Reserved;					// Reserved		
	DWORD		CodecEntriesCount;			// Codec Entries Count
//	BYTE		Codec Entries	See below	varies
}ASF_CodecListObject;
typedef struct CodecEntries{
	WORD		Type;
	WORD		CodecNameLength;
	WCHAR*		wszCodecName;
	WORD		CodecDescriptionLength;
	WCHAR*		wszCodecDescription;
	WORD		CodecInformationLength;
	BYTE*		bszCodecInformation;
	CodecEntries(FILE* pFile)
	{
		CodecNameLength = 0;
		CodecDescriptionLength = 0;
		CodecInformationLength = 0;
		wszCodecName = NULL;
		wszCodecDescription = NULL;
		bszCodecInformation = NULL;
		ASSERT(pFile);
		// Type
		DWORD dwReadCount = fread(&Type, 1, sizeof(Type), pFile);										ASSERT(dwReadCount > 0);
		// CodecNameLength
		dwReadCount = fread(&CodecNameLength, 1, sizeof(CodecNameLength), pFile);						ASSERT(dwReadCount > 0);
		if(CodecNameLength != 0)
		{
			wszCodecName = (WCHAR*)malloc(CodecNameLength*sizeof(WCHAR));
			dwReadCount = fread(wszCodecName, 1, CodecNameLength*sizeof(WCHAR), pFile);					ASSERT(dwReadCount > 0);	
		}
		// CodecDescriptionLength
		dwReadCount = fread(&CodecDescriptionLength, 1, sizeof(CodecDescriptionLength), pFile);			ASSERT(dwReadCount > 0);
		if(CodecDescriptionLength != 0)
		{
			wszCodecDescription = (WCHAR*)malloc(CodecDescriptionLength*sizeof(WCHAR));
			dwReadCount = fread(wszCodecDescription, 1, CodecDescriptionLength*sizeof(WCHAR), pFile);	ASSERT(dwReadCount > 0);	
		}
		// CodecInformationLength
		dwReadCount = fread(&CodecInformationLength, 1, sizeof(CodecInformationLength), pFile);			ASSERT(dwReadCount > 0);
		if(CodecInformationLength != 0)
		{
			bszCodecInformation = (BYTE*)malloc(CodecInformationLength + 1);
			dwReadCount = fread(bszCodecInformation, 1, CodecInformationLength, pFile);					ASSERT(dwReadCount > 0);
			bszCodecInformation[dwReadCount] = '\0';
		}
	}
	~CodecEntries()
	{
		if(wszCodecName)
		{
			free(wszCodecName);
			wszCodecName = NULL;
		}
		if(wszCodecDescription)
		{
			free(wszCodecDescription);
			wszCodecDescription = NULL;
		}
		if(bszCodecInformation)
		{
			free(bszCodecInformation);
			bszCodecInformation = NULL;
		}
	}
}CodecEntries;
/************************************************************************/
/*Script Command Object                                                 */
/************************************************************************/
struct CommandTypesstruct
{	
	DWORD		PresentationTime;
	WORD		TypeIndex;   
	WORD		CommandNameLength; 
	WCHAR		*wszCommandName;			// varies
	CommandTypesstruct(){}
	CommandTypesstruct(FILE* pFile)
	{
		InitData(pFile);	
	}
	void InitData(FILE* pFile)
	{
		CommandNameLength = 0;
		wszCommandName = NULL;
		ASSERT(pFile);
		DWORD dwReadCount = fread(&PresentationTime, 1, sizeof(PresentationTime), pFile);			
		ASSERT(dwReadCount > 0);
		dwReadCount = fread(&TypeIndex, 1, sizeof(TypeIndex), pFile);			
		ASSERT(dwReadCount > 0);
		dwReadCount = fread(&CommandNameLength, 1, sizeof(CommandNameLength), pFile);			
		ASSERT(dwReadCount > 0);
		if(CommandNameLength != 0)
		{
			wszCommandName = (WCHAR*)malloc(CommandNameLength*sizeof(WCHAR));
			dwReadCount = fread(wszCommandName, 1, CommandNameLength*sizeof(WCHAR), pFile);			
			ASSERT(dwReadCount > 0);	
		}
	}
	~CommandTypesstruct()
	{
		if(wszCommandName)
		{
			free(wszCommandName);
			wszCommandName = NULL;
		}
	}	
};
typedef struct Commandstruct
{
	WORD		CommandTypeNameLength;			   
	WCHAR		*wszCommandTypeName;		//[varies] 
	Commandstruct(){}
	Commandstruct(FILE* pFile)
	{
		InitData(pFile);
	}
	void InitData(FILE* pFile)
	{
		wszCommandTypeName = NULL;
		CommandTypeNameLength = 0;
		ASSERT(pFile);
		DWORD dwReadCount = fread(&CommandTypeNameLength, 1, sizeof(CommandTypeNameLength), pFile);			
//		ASSERT(dwReadCount > 0);
		if(CommandTypeNameLength != 0)
		{
			wszCommandTypeName = (WCHAR*)malloc(CommandTypeNameLength*sizeof(WCHAR));
			dwReadCount = fread(wszCommandTypeName, 1, CommandTypeNameLength*sizeof(WCHAR), pFile);			
//			ASSERT(dwReadCount > 0);	
		}	
	}
	~Commandstruct()
	{
		if(wszCommandTypeName)
		{
			TRACE2("%d-%08X\n", CommandTypeNameLength, wszCommandTypeName);
			free(wszCommandTypeName);
			wszCommandTypeName = NULL;
		}
	}
}Commandstruct, *PCommandstruct;
typedef struct ASF_ScriptCommandObject  
{
	DWORD128	ObjectID;							// ObjectID
	DWORD64		ObjectSize;							// ObjectSize
	DWORD128	Reserved;							// Reserved
	WORD		CommandsCount;						// CommandsCount
	WORD		CommandTypesCount;					// CommandTypesCount
//	BYTE		Types[varies];						// See below	
//	BYTE		Commands[varies];					// See below	varies
	Commandstruct		*pCommandstruct;			//
	CommandTypesstruct	*pCommandTypesstruct;		//
	ASF_ScriptCommandObject();
	ASF_ScriptCommandObject(FILE* pFile)
	{
		CommandTypesCount = 0;
		CommandsCount = 0;
		pCommandTypesstruct = NULL;
		pCommandstruct = NULL;
		ASSERT(pFile);
		// Type
		DWORD dwReadCount;
		dwReadCount = fread(&ObjectID, 1, sizeof(ObjectID), pFile);						ASSERT(dwReadCount > 0);
		dwReadCount = fread(&ObjectSize, 1, sizeof(ObjectSize), pFile);					ASSERT(dwReadCount > 0);
		dwReadCount = fread(&Reserved, 1, sizeof(Reserved), pFile);						ASSERT(dwReadCount > 0);
		dwReadCount = fread(&CommandsCount, 1, sizeof(CommandsCount), pFile);			ASSERT(dwReadCount > 0);
		dwReadCount = fread(&CommandTypesCount, 1, sizeof(CommandTypesCount), pFile);	ASSERT(dwReadCount > 0);
		// CommandTypesstruct
		if(CommandsCount > 0)
		{
			pCommandstruct = new Commandstruct[CommandsCount]();
			for(WORD i = 0; i < CommandsCount; i++)
			{
				pCommandstruct[i].InitData(pFile);
			}
		}
		if(CommandTypesCount > 0)
		{
			pCommandTypesstruct = new CommandTypesstruct[CommandTypesCount]();
			for(WORD i = 0; i < CommandTypesCount; i++)
			{
				pCommandTypesstruct[i].InitData(pFile);
			}
		}	
	}
	~ASF_ScriptCommandObject()
	{
		if(pCommandstruct)
		{
			delete []pCommandstruct;
			pCommandstruct = NULL;
		}
		if(pCommandTypesstruct)
		{
			delete []pCommandTypesstruct;
			pCommandTypesstruct = NULL;
		}
	}
}ASF_ScriptCommandObject;
/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct ASF_DataObject    
{
	DWORD128	ObjectID; 
	DWORD64		ObjectSize;  
	DWORD128	FileID;
	DWORD64		TotalDataPackets;
	WORD		Reserved;
//	Data Packets	See section 5.2	varies
	ASF_DataObject(FILE* pFile)
	{
		TotalDataPackets = NULL;
		ASSERT(pFile);
		// Type
		DWORD dwReadCount;
		dwReadCount = fread(this, 1,sizeof(ObjectID)+sizeof(ObjectSize)+
			sizeof(FileID)+sizeof(TotalDataPackets)+
			sizeof(Reserved), pFile);						
		ASSERT(dwReadCount > 0);
		if(TotalDataPackets > 0)
		{
//			pIndexEntries = new IndexEntries[IndexEntriesCount];
//			dwReadCount = fread(pIndexEntries, 1, sizeof(IndexEntries) * IndexEntriesCount, pFile);
		}	
	};
	~ASF_DataObject()
	{
//		if(pIndexEntries)
//		{
//			delete []pIndexEntries;
//			pIndexEntries = NULL;
//		}
	}
}ASF_DataObject;
//ASF data packet definition
//Error correction data
#define ErrorCorrectionDataLength(x)	(BYTE)(x&0x0F)
#define OpaqueDataPresent(x)			(BYTE)((x&0x10) >> 4)
#define ErrorCorrectionLengthType(x)	(BYTE)((x&0x30) >> 5)
#define ErrorCorrectionPresent(x)		(BYTE)((x&0x80) >> 7)
struct Errorcorrectiondata
{
	BYTE	ErrorCorrectionFlags;
//	Error Correction Data Length		4 (LSB)	   
//	Opaque Data Present					1	   
//	Error Correction Length Type		2	   
//	Error Correction Present			1	   
	BYTE* pErrorCorrectionData;		// varies
	Errorcorrectiondata(FILE* pFile)
	{
		ErrorCorrectionFlags = NULL;
		pErrorCorrectionData = NULL;
		ASSERT(pFile);
		// Type
		DWORD dwReadCount;
		dwReadCount = fread(&ErrorCorrectionFlags, 1, sizeof(ErrorCorrectionFlags), pFile);						
		ASSERT(dwReadCount > 0);
		BYTE dwLen = ErrorCorrectionDataLength(ErrorCorrectionFlags);
		if(dwLen > 0)
		{
			pErrorCorrectionData = (BYTE*)malloc(dwLen);
			dwReadCount = fread(pErrorCorrectionData, 1, dwLen, pFile);
		}	
	};
	~Errorcorrectiondata()
	{
		if(pErrorCorrectionData)
		{
			free(pErrorCorrectionData);
			pErrorCorrectionData = NULL;
		}
	}
};
//
struct Payloadparsing  
{
	BYTE		LengthTypeFlags;
//	Multiple Payloads Present		1 (LSB)	   
//	Sequence Type					2	   
//	Padding Length Type				2	   
//	Packet Length Type				2	   
//	Error Correction Present		1	   
	BYTE		PropertyFlags;	   
//	Replicated Data Length Type		2 (LSB)	   
//	Offset Into Media Object Length Type		2	   
//	Media Object Number Length Type		2	   
//	Stream Number Length Type		2
	   
//	Packet Length	BYTE, WORD or DWORD	0, 8, 16, 32	   
//	Sequence	BYTE, WORD or DWORD	0, 8, 16, 32	   
//	Padding Length	BYTE, WORD or DWORD	0, 8, 16, 32	   
//	Send Time	DWORD	32	   
//	Duration	WORD	16	 
};




/************************************************************************/
/* index objects                                                                     */
/************************************************************************/
typedef struct IndexEntries
{
	DWORD	PacketNumber;
	WORD	PacketCount;
}IndexEntries, PIndexEntries;
typedef struct ASF_IndexObject    
{	
	DWORD128	ObjectID;						
	DWORD64		ObjectSize;
	DWORD128	FileID;
	DWORD64		IndexEntryTimeInterval;   
	DWORD		MaximumPacketCount;
	DWORD		IndexEntriesCount;
	IndexEntries*	pIndexEntries;
//	Index Entries	See below	varies
	ASF_IndexObject(FILE* pFile)
	{
		pIndexEntries = NULL;
		IndexEntriesCount = 0;
		ASSERT(pFile);
		// Type
		DWORD dwReadCount;
		dwReadCount = fread(this, 1,	sizeof(ObjectID)+sizeof(ObjectSize)+
										sizeof(FileID)+sizeof(IndexEntryTimeInterval)+
										sizeof(MaximumPacketCount)+sizeof(IndexEntriesCount)
										, pFile);						
		ASSERT(dwReadCount > 0);
		if(IndexEntriesCount > 0)
		{
			pIndexEntries = new IndexEntries[IndexEntriesCount];
			dwReadCount = fread(pIndexEntries, 1, sizeof(IndexEntries) * IndexEntriesCount, pFile);
		}	
	};
	~ASF_IndexObject()
	{
		if(pIndexEntries)
		{
			delete []pIndexEntries;
			pIndexEntries = NULL;
		}
	}
}ASF_IndexObject;
// ITEMTYPE
enum VALUETYPE
{
	_NULL		= 0,
	_BYTE		= 1,
	_WORD		= 2,
	_DWORD		= 3,
	_DWORD64	= 8,
	_DWORD128	= 9,
	_BYTE_STR	= 10,
	_CHAR_STR	= 11,
	_WCHAR_STR	= 20,
};
// ITEMVALUE
struct ITEMVALUE 
{
	VALUETYPE vt;
	union 
	{
		DWORD128	dw128Value;
		DWORD64		dw64Value;
		DWORD		dwValue;
		WORD		wValue;
		BYTE		bValue;
		BYTE*		bszValue;
		CHAR*		szValue;
		WCHAR*		wszValue;
	}value;
	ITEMVALUE(){	vt = _NULL;}
	ITEMVALUE(BYTE bValue)			{ vt = _BYTE;		this->value.bValue = bValue;	}
	ITEMVALUE(WORD wValue)			{ vt = _WORD;		this->value.wValue = wValue;	}
	ITEMVALUE(LONG lValue)			{ vt = _DWORD;		this->value.dwValue = lValue;	}
	ITEMVALUE(DWORD dwValue)		{ vt = _DWORD;		this->value.dwValue = dwValue;	}
	ITEMVALUE(DWORD64 dw64Value)	{ vt = _DWORD64;	this->value.dw64Value = dw64Value;	}
	ITEMVALUE(DWORD128 dw128Value)	{ vt = _DWORD128;	this->value.dw128Value = dw128Value;	}
	ITEMVALUE(BYTE* bszValue_)		{ ITEMVALUENULL(bszValue_);	vt = _BYTE_STR;	int len = strlen((CHAR*)bszValue_)+1;	this->value.bszValue = (BYTE* )malloc(len);		memcpy(this->value.bszValue, bszValue_, len);}
	ITEMVALUE(CHAR* szValue_)		{ ITEMVALUENULL(szValue_);	vt = _CHAR_STR; int len = strlen(szValue_)+1;			this->value.szValue = (CHAR* )malloc(len);		memcpy(this->value.szValue, szValue_, len);}
	ITEMVALUE(WCHAR* wszValue_)		{ ITEMVALUENULL(wszValue_);	vt = _WCHAR_STR;int len = wcslen(wszValue_)+4;			this->value.wszValue = (WCHAR* )malloc(len*sizeof(WCHAR));	memcpy(this->value.wszValue, wszValue_, len*sizeof(WCHAR));}
	~ITEMVALUE(){	
		switch(vt){
		case _BYTE_STR:		if(value.bszValue) free(value.bszValue); value.bszValue = NULL;	break;
		case _CHAR_STR:		if(value.szValue)  free(value.szValue);  value.szValue = NULL;	break;
		case _WCHAR_STR:	if(value.wszValue) free(value.wszValue); value.wszValue = NULL;	break;
		}
	}
};
/************************************************************************/
/* Function                                                             */
/************************************************************************/
#define CTreeItem_ CSuperGridCtrl::CTreeItem
CTreeItem_*  AddMainItem(LPCTSTR pszName, DWORD dwAddress, CMySuperGrid& m_ListGrid);
CTreeItem_*  AddSubMainItem(LPCTSTR pszName, LPCTSTR pszDesc, DWORD dwAddress, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid);
CTreeItem_*  AddSubItem(LPCTSTR strTitle, DWORD& dwAddress,  ITEMVALUE& itemvalue, LPCTSTR pszSpec, LPCTSTR pszDesc, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid);
CString DWTOSTR(DWORD dwValue);					// DWORD -> CString
CString FILETIMETOSTRING(FILETIME fileTime);	// fileTime->Cstring
CString DWORD128TOGUID(DWORD128 value);			// DWORD128 -> GUID STR
CString	INDEX(DWORD dwIndex);					// INDEX
BOOL ASCIITOUNICODE(TCHAR* pszAsciiData, WCHAR* wszUTFData, DWORD dwLen = 0);
BOOL UNICODETOASCII(WCHAR* wszUTFData,TCHAR* pszAsciiData, DWORD dwLen = 0);


#endif//__ASFINFO_H_2459134951B94A1895E650CFD52F4215__
