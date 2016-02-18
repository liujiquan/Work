//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ASFdefine.cpp
//* Author   :   liujiquan
//* DateTime :   11/7/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "StdAfx.h"
#include "AsfInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//	g_szHeaderObjFiled
TCHAR g_szHeaderObjField[][MAX_PATH] = {
		_T("Object ID"),
		_T("Object Size"),
		_T("Number of Header Objects"),
		_T("Reserved1"),
		_T("Reserved2")
};
TCHAR g_szHeaderObjDesc[][MAX_PATH] = {
		_T("Specifies the GUID for the Header Object. This field shall be set to ASF_Header_Object."),
		_T("Specifies the size of the Header Object. This includes the sum of 24 bytes plus the size of the objects contained in the Header Object. Valid values are at least 30 bytes."),
		_T("Number of Header Objects "),
		_T("This field must be set to the value 0x01"),
		_T("This field must be set to the value 0x02.")
};
// 	g_szPropertiesObjFiled
TCHAR g_szPropertiesObjField [][MAX_PATH] = {
		_T("Object ID"),
		_T("Object Size"),
		_T("File ID"),
		_T("File Size"),
		_T("Creation Date"),
		_T("Data Packets Count"),
		_T("Play Duration"),
		_T("Send Duration"),
		_T("Preroll"),
		_T("Flags"),
			_T("Broadcast Flag (bit 0)"),
			_T("Seekable Flag (bit 1)"),
			_T("Reserved (bits 2 每 31)"),
		_T("Minimum Data Packet Size "),
		_T("Maximum Data Packet Size "),
		_T("Maximum Bitrate "),
};
TCHAR g_szPropertiesObjDesc[][MAX_PATH*10] = {
	//Object ID 
	_T("Specifies the GUID for the File Properties Object. This field shall be set to ASF_File_Properties_Object."),
	//Object Size 
	_T("Specifies the size, in bytes, of the File Properties Object. Valid values are at least 104 bytes."),
	//File ID 
	_T("Specifies the unique identifier for this file. The value of this field shall be regenerated every time the file is modified in any way. The value of this field shall be identical to the value of the File ID field of the Data Object."),
	//File Size
	_T("Specifies the size, in bytes, of the entire file. The value of this field is invalid if the Broadcast Flag bit in the Flags field is set to 1."),
	//Creation Date 
	_T("Specifies the date and time of the initial creation of the file. The value is given as the number of 100-nanosecond intervals since January 1, 1601, according to Coordinated Universal Time (Greenwich Mean Time). The value of this field may be invalid if the Broadcast Flag bit in the Flags field is set to 1."),
	//Data Packets Count
	_T("Specifies the number of Data Packet entries that exist within the Data Object. The value of this field is invalid if the Broadcast Flag bit in the Flags field is set to 1."),
	//Play Duration 
	_T("Specifies the time needed to play the file in 100-nanosecond units. This value should include the duration (estimated, if an exact value is unavailable) of the the last media object in the presentation. The value of this field is invalid if the Broadcast Flag bit in the Flags field is set to 1."),
	//Send Duration 
	_T("Specifies the time needed to send the file in 100-nanosecond units. This value should include the duration of the last packet in the content. The value of this field is invalid if the Broadcast Flag bit in the Flags field is set to 1. Players can ignore this value."),
	//Preroll 
	_T("Specifies the amount of time to buffer data before starting to play the file, in millisecond units. If this value is nonzero, the Play Duration field and all of the payload Presentation Time fields have been offset by this amount. Therefore, player software must subtract the value in the preroll field from the play duration and presentation times to calculate their actual values.\
	It follows that all payload Presentation Time fields need to be at least this value."),

	//Flags
	_T("The flags are stored in Least Significant Byte (LSB) order./Broadcast Flag (bit 0)/Seekable Flag (bit 1)/Reserved (bits 2 每 31)" ) ,
		//Broadcast Flag (bit 0)
		_T("Specifies, if set, that a file is in the process of being created (for example, for recording applications), and thus that various values stored in the header objects are invalid. It is highly recommended that post-processing be performed to remove this condition at the earliest opportunity."),
		//Seekable Flag (bit 1)
		_T("Specifies, if set, that a file is seekable. Note that for files containing a single audio stream and a Minimum Data Packet Size field equal to the Maximum Data Packet Size field, this flag shall always be set to 1. For files containing a single audio stream and a video stream or mutually exclusive video streams, this flag is only set to 1 if the file contains a matching Simple Index Object for each regular video stream (that is, video streams that are not hidden according to the method described in section 8.2.2)."),
		//Reserved (bits 2 每 31)
		_T("Remaining 30 reserved flags shall be set to 0."),

	//Minimum Data Packet Size 
	_T("Specifies the minimum Data Packet size in bytes. In general, the value of this field is invalid if the Broadcast Flag bit in the Flags field is set to 1. However, for the purposes of this specification, the values for the Minimum Data Packet Size and Maximum Data Packet Size fields shall be set to the same value, and this value should be set to the packet size, even when the Broadcast Flag in the Flags field is set to 1."),
	//Maximum Data Packet Size 
	_T("Specifies the maximum Data Packet size in bytes. In general, the value of this field is invalid if the Broadcast Flag bit in the Flags field is set to 1. However, for the purposes of this specification, the values of the Minimum Data Packet Size and Maximum Data Packet Size fields shall be set to the same value, and this value should be set to the packet size, even when the Broadcast Flag field is set to 1."),
	//Maximum Bitrate 
	_T("Specifies the maximum instantaneous bit rate in bits per second for the entire file. This shall equal the sum of the bit rates of the individual digital media streams. It shall be noted that the digital media stream includes ASF data packetization overhead as well as digital media data in payloads. Only those streams that have a free-standing Stream Properties Object in the header shall have their bit rates included in the sum; streams whose Stream ")
};

// g_szClockObjFiled
TCHAR g_szClockObjectField [][MAX_PATH] = {
	_T("Object ID"),
	_T("Object Size"),
	_T("Clock Type"),
	_T("Clock Size	"),
	_T("Clock-Specific Data Length")
};

TCHAR g_szClockObjectDesc [][MAX_PATH] = {
	_T("Object ID"),
	_T("Object Size"),
	_T("Clock Type"),
	_T("Clock Size	"),
	_T("Clock-Specific Data Length")
};

// 	g_szPropertiesObjFiled
TCHAR g_szStreamPropertiesObjectField [][MAX_PATH] = {
	_T("Object ID "),	
	_T("Object Size "),
	_T("Stream Type "),
	_T("Error Correction Type "),
	_T("Time Offset "),
	_T("Type-Specific Data Length "),
	_T("Error Correction Data Length "),
	_T("Flags[Stream Number 7(LSB)/Reserved 8/Encrypted Content Flag1]"),
		_T("Stream Number (bits 0-6)"),
		_T("Reserved (bits 7-14)"),
		_T("Encrypted Content Flag (bit 15)"),
	_T("Reserved "),
	_T("Type-Specific Data "),
	_T("Error Correction Data ")
};
// g_szStreamPropertiesObjectDesc
TCHAR g_szStreamPropertiesObjectDesc [][MAX_PATH*10] = {
	_T("pecifies the GUID for the Stream Properties Object. The value of this field shall be set to ASF_Stream_Properties_Object."),
	//Object Size 
	_T("Specifies the size, in bytes, of the Stream Properties Object. Valid values are at least 78 bytes."),
	//Stream Type 
	_T("Specifies the type of the stream (for example, audio, video, and so on). Use one of the GUIDs defined in section 10.4. Any streams with unrecognized Stream Type values should be ignored."),
	//Error Correction Type 
	_T("Specifies the error correction type used by this digital media stream. For streams other than audio, this value should be set to ASF_No_Error_Correction. For audio streams, this value should be set to ASF_Audio_Spread. The possible GUIDs are defined in section 10.5, and the standard error correction schemes are described in section 9.1."),
	//Time Offset
	_T("Specifies the presentation time offset of the stream in 100-nanosecond units. The value of this field is added to all of the timestamps of the samples in the stream. This value shall be equal to the send time of the first interleaved packet in the data section. The value of this field is typically 0. It is non-zero in the case when an ASF file is edited and it is not possible for the editor to change the presentation times and send times of ASF packets. Note that if more than one stream is present in an ASF file the offset values of all stream properties objects must be equal."),
	//Type-Specific Data Length 
	_T("Specifies the number of bytes in the Type-Specific Data field."),
	//Error Correction Data Length 
	_T("Specifies the number of bytes in the Error Correction Data field."),
	//Flags
	_T("The flags are stored in LSB order."),
		//Stream Number (bits 0-6)
		_T("Specifies the number of this stream. 0 is an invalid stream. Valid values are between 1 and 127. The numbers assigned to streams in an ASF presentation may be any combination of unique values; parsing logic must not assume that streams are numbered sequentially."),
		//Reserved (bits 7-14)
		_T("These bits are reserved and should be set to 0."),
		//Encrypted Content Flag (bit 15)
		_T("Specifies, if set, that the data contained in this stream is encrypted and will be unreadable unless there is a way to decrypt the stream."),
	//Reserved
	_T("This field is reserved and should be set to 0."),
	//Type-Specific Data 
	_T("Specifies type-specific format data. The structure for the Type-Specific Data field is determined by the value stored in the Stream Type field. The structure for the Type-Specific Data field for standard ASF media types is detailed in section 9."),
	//Error Correction Data 
	_T("Specifies data specific to the error correction type. The structure for the Error Correction Data field is determined by the value stored in the Error Correction Type field. For example, an audio data stream might need to know how codec chunks were redistributed, or it might need a sample of encoded silence. ")
};

// g_szAudiomediatypeField
TCHAR g_szAudiomediatypeField [][MAX_PATH] = {
	_T("CodecID / FormatTag"),		
	_T("NumberofChannels"),			
	_T("SamplesPerSecond"),			
	_T("AverageNumberofBytesPerSecond"),
	_T("BlockAlignment"),				
	_T("BitsPerSample"),				
	_T("CodecSpecific Data Size"),	
	_T("CodecSpecific Data")
};	
TCHAR g_szAudiomediatypeDesc [][MAX_PATH] = {
	//Codec ID / Format Tag
	_T("Specifies the unique ID of the codec used to encode the audio data. There is a registration procedure for new codecs. Defined as the wFormatTag field of a WAVEFORMATEX structure."),
	//Number of Channels
	_T("Specifies the number of audio channels. Monaural data uses one channel and stereo data uses two channels. 5.1 audio uses six channels. Defined as the nChannels field of a WAVEFORMATEX structure."),
	//Samples Per Second
	_T("Specifies a value in Hertz (cycles per second) that represents the sampling rate of the audio stream. Defined as the nSamplesPerSec field of a WAVEFORMATEX structure."),
	//Average Number of Bytes Per Second
	_T("Specifies the average number of bytes per second of the audio stream. Defined as the nAvgBytesPerSec field of a WAVEFORMATEX structure."),
	//Block Alignment
	_T("Specifies the block alignment, or block size, in bytes of the audio codec. Defined as the nBlockAlign field of a WAVEFORMATEX structure."),
	//Bits per Sample
	_T("Specifies the number of bits per sample of monaural data. Defined as the wBitsPerSample field of a WAVEFORMATEX structure."),
	//Codec Specific Data Size
	_T("Specifies the size, in bytes, of the Codec Specific Data buffer. Defined as the cbSize field of a WAVEFORMATEX structure. This value should be 0 when Codec ID is 1 (WAVE_FORMAT_PCM)."),
	//Codec Specific Data
	_T("Specifies an array of codec-specific data bytes.")
};
// g_szVideomediatypeField
TCHAR g_szVideomediatypeField [][MAX_PATH] = {
	_T("Encoded Image Width"),
	_T("Encoded Image Height"),
	_T("Reserved Flags"),
	_T("Format Data Size"),
	
	_T("BITMAPINFO"),// BITMAPINFO
	_T("Format Data Size"),
	_T("Image Width	"),
	_T("Image Height"),
	_T("Reserved"),
	_T("Bits Per Pixel Count"),
	_T("Compression ID"),
	_T("Image Size"),
	_T("Horizontal Pixels Per Meter"),
	_T("Vertical Pixels Per Meter"),
	_T("Colors Used Count"),
	_T("Important Colors Count"),
	_T(" Specific Data")
};
TCHAR g_szVideomediatypeDesc [][MAX_PATH*2] = {
	//Encoded Image Width
	_T("Specifies the width of the encoded image in pixels."),
	//Encoded Image Height
	_T("Specifies the height of the encoded image in pixels."),
	//Reserved Flags
	_T("Specifies reserved flags, and shall be set to 2."),
	// Format Data Size
	_T("Specifies the size of the Format Data field in bytes."),
// BITMAPINFO
	_T("Specifies the details of the format of the image data. This format is structured as follows (the BITMAPINFOHEADER structure):"),
	//Format Data Size 
	_T("Specifies the number of bytes stored in the Format Data field. Defined as the biSize field of a BITMAPINFOHEADER structure."),
	//Image Width 
	_T("Specifies the width of the encoded image in pixels. Defined as the biWidth field of a BITMAPINFOHEADER structure. This should be equal to the Encoded Image Width field defined previously."),
	//Image Height 
	_T("Specifies the height of the encoded image in pixels. Defined as the biHeight field of a BITMAPINFOHEADER structure. This should be equal to the Encoded Image Height field defined previously."),
	//Reserved 
	_T("Reserved. Shall be set to 1. Defined as the biPlanes field of a BITMAPINFOHEADER structure."),
	//Bits Per Pixel Count 
	_T("Specifies the number of bits per pixel. Defined as the biBitCount field of a BITMAPINFOHEADER structure."),
	//Compression ID
	_T("Specifies the type of the compression, using a four-character code. For ISO MPEG-4 video, this contains MP4S, mp4s, M4S2, or m4s2. In the Compression ID, the first character of the four-character code appears as the least-significant byte; for instance MP4S uses the Compression ID 0x5334504D. Defined as the biCompression field of a BITMAPINFOHEADER structure."),
	//Image Size 
	_T("Specifies the size of the image in bytes. Defined as the biSizeImage field of a BITMAPINFOHEADER structure."),
	//Horizontal Pixels Per Meter 
	_T("Specifies the horizontal resolution of the target device for the bitmap in pixels per meter. Defined as the biXPelsPerMeter field of a BITMAPINFOHEADER structure."),
	//Vertical Pixels Per Meter 
	_T("Specifies the vertical resolution of the target device for the bitmap in pixels per meter. Defined as the biYPelsPerMeter field of a BITMAPINFOHEADER structure."),
	//Colors Used Count 
	_T("Specifies the number of color indexes in the color table that are actually used by the bitmap. Defined as the biClrUsed field of a BITMAPINFOHEADER structure."),
	//Important Colors Count 
	_T("Specifies the number of color indexes that are required for displaying the bitmap. If this value is zero, all colors are required. Defined as the biClrImportant field of a BITMAPINFOHEADER structure."),
	//Codec Specific Data
	_T("Specifies an array of codec specific data bytes. The size of this array is equal to the Format Data Size field minus the size of the Format Data fields listed previously."),

};
// g_szVideomediatypeField
TCHAR g_szJFIF_JPEGmediatypeField [][MAX_PATH] = {
	_T("Image width"),
	_T("Image height"),	
	_T("Reserved")
};
TCHAR g_szJFIF_JPEGmediatypeDesc [][MAX_PATH] = {
	//Image width
	_T("Specifies the width of the encoded image in pixels. "),
	//Image height
	_T("Specifies the height of the encoded image in pixels."),
	//Reserved
	_T("Reserved, must be 0.")
};
// g_szVideomediatypeField
TCHAR g_szDegradableJPEGmediatypeField [][MAX_PATH] = {
	_T("Image width"),
	_T("Image height"),	
	_T("Reserved1"),
	_T("Reserved2"),
	_T("Reserved3"),
	_T("Interchange data length")
};
TCHAR g_szDegradableJPEGmediatypeDesc [][MAX_PATH] = {
	//Image width
	_T("Specifies the width of the encoded image in pixels. "),
	//Image height
	_T("Specifies the height of the encoded image in pixels."),
	//Reserved
	_T("These three fields must be, respectively, 0, 2, and 4."),
	_T("These three fields must be, respectively, 0, 2, and 4."),
	_T("These three fields must be, respectively, 0, 2, and 4."),
	//Interchange data length
	_T("Specifies the number of bytes in the Interchange data field. If this value is 0, then Interchange data field shall consist of the single byte value 0x00."),
	//Interchange data
	_T("Specifies the interchange data for this stream. If Interchange data length is set to 0, then this field shall still be present and shall consist of the single byte 0x00.")
};
// g_szFiletransferandbinarymediatypesField
TCHAR g_szFiletransferandbinarymediatypesField [][MAX_PATH] = {
	_T("media type"),
	_T("Media subtype"),
	_T("Fixed-size samples"),
	_T("Temporal compression"),
	_T("Sample size"),
	_T("Format type"),
	_T("Format data size")
};
// g_szWebstreamField
TCHAR g_szWebstreamField [][MAX_PATH] = {
	_T("Web stream format data size"),
	_T("Fixed sample header size"),	
	_T("Version number"),			
	_T("Reserved")
};	
TCHAR g_szmediaobjectsForWebstreamField [][MAX_PATH] = {
	_T("Total header len"),
	_T("Part number"),		
	_T("Total part count"),
	_T("Sample type"),		
	_T("URL string")
};
TCHAR g_szWebstreamDesc [][MAX_PATH] = {				
	//Web stream format data size
	_T("This shall be set to 8."),	
		//Fixed sample header size
		_T("This shall be set to 10. See below for a description of the Web stream header."),	
		//Version number
		_T("This shall be set to 1. "),	
		//Reserved
		_T("Reserved, must be 0."),
};
TCHAR g_szmediaobjectsForWebstreamDesc [][MAX_PATH] = {
	//Total header length
	_T("This is the total size of the media object header. This value should be set to 10 plus the length (not including the nul-terminating character) of the URL string field."),
	//Part number
	_T("Current part of the file (0-based). Valid values are from 0 to Total number of parts 每 1."),
	//Total part count
	_T("Number of parts in the file."),
	//Sample type
	_T("Valid values for this field are 1, which indicates the sample type is \"file\", and 2, which indicates the sample type is \"render\" (which is essentially a command to render the data)."),
	//URL string
	_T("This is a nul-terminated string containing the URL for the file being transferred.")
};


TCHAR g_szFiletransferandbinarymediatypesDesc [][MAX_PATH*2] = {
	//Major media type
	_T("This value must be equal to the Stream Type value in the Stream Properties Object."),
	//Media subtype
	_T("Indicates the media subtype. Can be set to 0 if not relevant. ASF_Web_Stream_Media_Subtype is a possible value for file transfer streams that are Web streams."),
	//Fixed-size samples
	_T("Valid values are 0 and 1. This value shall be set to 1 if this stream has fixed-size samples."),
	//Temporal compression
	_T("Valid values are 0 and 1. This value shall be set to 1 if compression of media object N might depend on media object N-1. In general, this value should be set to 0."),
	//Sample size
	_T("If the Fixed-size samples field has a value of 1, then this value is the fixed sample size. Otherwise, the value is ignored and should be 0."),
	//Format type
	_T("If there is no additional media type information, this field, along with the value in the Format data size field, should be set to 0. For a Web stream, this can be set to ASF_Web_Stream_Format. Custom non-standard format types can also be defined, but they will not necessarily be understood across implementations."),
	//Format data size
	_T("This is the number of bytes in Format data. If there is no format data, this field, along with the value in the Format type field, should be set to 0.  ")
	//Format data
	//This is the additional format data for this media type. This shall be present only if Format data size is greater than 0. Custom format types can define how these bytes are formatted. If the Format type is equal to ASF_Web_Stream_Format, then there is a standard format for these bytes, detailed in section 9.5.1.
};

// g_szSpreadaudioField
TCHAR g_szSpreadaudioField [][MAX_PATH] = {
	_T("Span"),
	_T("Virtual Packet Length"),
	_T("Virtual Chunk Length"),
	_T("Silence Data Length")
};
TCHAR g_szSpreadaudioDesc [][MAX_PATH] = {
	//Span
	_T("Specifies the number of packets over which audio will be spread. Typically, this value should be set to 1."),
	//Virtual Packet Length
	_T("Specifies the virtual packet length. The value of this field should be set to the size of the largest audio payload found in the audio stream."),
	//Virtual Chunk Length
	_T("Specifies the virtual chunk length. The value of this field should be set to the size of the largest audio payload found in the audio stream."),
	//Silence Data Length
	_T("Specifies the number of bytes stored in the Silence Data field. This value should be set to 1. It is also valid for this value to equal the Block Alignment value (from the Audio Media Type)."),
	//Silence Data
	_T("Specifies an array of silence data bytes. This value should be set to 0 for the length of Silence Data Length.")
};

// 	g_szHeaderExtensionObjectField
TCHAR g_szHeaderExtensionObjectField [][MAX_PATH] = {
	_T("Object ID"),				
	_T("Object Size	"),			
	_T("Reserved Field 1"),		
	_T("Reserved Field 2"),		
	_T("Header Extension Data Size")
};
TCHAR g_szHeaderExtensionObjectDesc [][MAX_PATH] = {
	//Object ID 
	_T("Specifies the GUID for the Header Extension Object. The value of this field shall be set to ASF_Header_Extension_Object."),
	//Object Size 
	_T("Specifies the size, in bytes, of the Header Extension Object. The value of this field shall be set to 46 bytes."),
	//Reserved Field 1
	_T("This value shall be set to ASF_Reserved_1 as defined in section 10.6."),
	//Reserved Field 2
	_T("This value should be set to 6."),
	//Header Extension Data Size
	_T("Specifies the number of bytes stored in the Header Extension Data field. This value may be 0 bytes or 24 bytes and larger. It should also be equal to the Object Size field minus 46 bytes."),
	//Header Extension Data
	_T("Specifies an array of bytes containing additional extended header objects. This data should be interpreted as 0 or more extended header objects stored consecutively within the array of bytes. No empty space, padding, leading, or trailing bytes are allowed.")
};

// g_szCodecListObjectField
TCHAR g_szCodecListObjectField [][MAX_PATH] = {
	_T("Object ID	"),	
	_T("Object Size	"),	
	_T("Reserved"),		
	_T("Codec Entries Count")
};
TCHAR g_szCodecListObjectDesc [][MAX_PATH] = {
	//Object ID 
	_T("Specifies the GUID for the Codec List Object. The value of this field shall be set to ASF_Codec_List_Object."),	
	//Object Size 
	_T("Specifies the size, in bytes, of the Codec List Object. Valid values are at least 44 bytes."),	
	//Reserved 
	_T("Reserved. This field shall be set to ASF_Reserved_2 as defined in section 10.8."),	
	//Codec Entries Count 
	_T("Specifies the number of entries listed in the Codec Entries field.")
};
TCHAR g_szCodecEntriesField [][MAX_PATH] = {
	_T("Type "),
	_T("Codec Name Length "),
	_T("Codec Name "),
	_T("Codec Description Length "),
	_T("Codec Description "),
	_T("Codec Information Length "),
	_T("Codec Information ")
};
TCHAR g_szCodecEntriesDesc [][MAX_PATH] = {
	//Type 
	_T("Specifies the type of the codec used. Use one of the values in the following table."),	
	//Values	Meaning
	//0x0001	Video codec
	//0x0002	Audio codec
	//0xFFFF	Unknown codec
	//Codec Name Length 
	_T("Specifies the number of Unicode characters stored in the Codec Name field."),	
	//Codec Name 
	_T("Specifies an array of Unicode characters that contains the name of the codec used to create the content."),	
	//Codec Description Length 
	_T("Specifies the number of Unicode characters stored in the Codec Description field."),	
	//Codec Description 
	_T("Specifies an array of Unicode characters that contains the description of the format used to create the content."),	
	//Codec Information Length 
	_T("Specifies the number of bytes stored in the Codec Information field."),	
	//Codec Information 
	_T("Specifies an opaque array of information bytes about the codec used to create the content. The meaning of these bytes is determined by the codec.")
};

// Script Command Object 
TCHAR g_szScriptCommandObjectField [][MAX_PATH] = {
	_T("Object ID"),
	_T("Object Size "),
	_T("Reserved "),
	_T("Commands Count "),
	_T("Command Types Count"),
	_T("Command Type Name Length"),
	_T("Command Type Name"),
	_T("Presentation Time"),
	_T("Type Index"),
	_T("Command Name Length"),
	_T("Command Name")
};

TCHAR g_szScriptCommandObjectDesc [][MAX_PATH] = {
	// Object ID 
	_T("Specifies the GUID for the Script Command Object. The value of this field shall be set to ASF_Script_Command_Object."),
	// Object Size 
	_T("Specifies the size, in bytes, of the Script Command Object. Valid values are at least 44 bytes."),
	// Reserved 
	_T("Reserved. This field shall be set to ASF_Reserved_3 as defined in section 10.9."),
	// Commands Count 
	_T("Specifies the number of Command structures in the Script Command Object."),
	// Command Types Count
	_T("Specifies the number of Command Type structures in the Script Command Object."),
	//Command Type Name Length
	_T("Specifies the number of Unicode characters that are found within the Command Type Name field."),
	//Command Type Name
	_T("Specifies the name of a type of command. Whereas it is highly recommended that this string include a nul-terminator, the nul-terminator may not be present."),
	//Presentation Time
	_T("Specifies the presentation time of the command, in milliseconds."),
	//Type Index
	_T("Specifies the type of this command, as a zero-based index into the array of Command Types of this object."),
	//Command Name Length
	_T("Specifies the number of Unicode characters that are found within the Command Name field."),
	//Command Name
	_T("Specifies the name of this command. Whereas it is highly recommended that this string include a nul-terminator, the nul-terminator may not be present.")
};
// Simple Index Object 
TCHAR g_szIndexObjectField [][MAX_PATH] = {
	_T("ObjectID"),				
	_T("Object Size"),
	_T("File ID"),
	_T("Index Entry Time Interval"),
	_T("Maximum Packet Count"),
	_T("Index Entries Count"),
	_T("Packet Number "),  
	_T("Packet Count")
};
TCHAR g_szIndexObjectDesc [][MAX_PATH*2] = {
	//Object ID 
	_T("Specifies the GUID for the Simple Index Object. The value of this field shall be set to ASF_Simple_Index_Object."),
	//Object Size 
	_T("Specifies the size, in bytes, of the Simple Index Object. Valid values are at least 56 bytes."),
	//File ID 
	_T("Specifies the unique identifier for this ASF file. The value of this field should be changed every time the file is modified in any way. The value of this field may be set to 0 or set to be identical to the value of the File ID field of the Data Object and the Header Object. ASF parsers may safely ignore this value."),
	//Index Entry Time Interval 
	_T("Specifies the time interval between each index entry in 100-nanosecond units. The most common value is 10000000, to indicate that the index entries are in 1-second intervals, though other values can be used as well."),
	//Maximum Packet Count 
	_T("Specifies the maximum Packet Count value of all Index Entries."),
	//Index Entries Count 
	_T("Specifies the number of Index Entries structures contained in the next field."),
	//Packet Number 
	_T("Specifies the number of the Data Packet associated with this index entry. Note that for video streams that contain both key frames and non-key frames, this field will always point to the closest key frame prior to the time interval."),
	//Packet Count 
	_T("Specifies the number of Data Packets to send at this index entry. If a video key frame has been fragmented into two Data Packets, the value of this field will be equal to 2.")
};
// Data Object
TCHAR g_szDataObjectField [][MAX_PATH] = {
	_T("Object ID "),
	_T("Object Size "),
	_T("File ID "),  
	_T("Total Data Packets"),	   
	_T("Reserved  "),
	_T("Data Packets")	 
};

TCHAR g_szDataObjectDesc [][MAX_PATH*2] = {
	//Object ID 
	_T("Specifies the GUID for the Data Object. The value of this field shall be set to ASF_Data_Object."),
	//Object Size 
	_T("Specifies the size of the Data Object. Valid values are at least 50 bytes. Note that if the Broadcast Flag bit of the Flags field is set on the File Properties Object, then the Object Size field may be 0. This is a special case that indicates the size of the Data Object is unknown. It is not valid to have a value of 0 for the Object Size field if the Broadcast Flag is not set."),
	//File ID 
	_T("Specifies the unique identifier for this ASF file. The value of this field shall be changed every time the file is modified in any way. The value of this field shall be identical to the value of the File ID field of the Header Object."),
	//Total Data Packets
	_T("Specifies the number of ASF Data Packet entries that exist within the Data Object. It must be equal to the Data Packet Count field in the File Properties Object (section 3.2). The value of this field is invalid if the Broadcast Flag field of the File Properties Object is set to 1. "),
	//Reserved 
	_T("Specifies a reserved field. The value of this field shall set to 0x0101."),
	//Data Packets
	_T("Specifies a list of Data Packets, as defined in section 5.2.")
};

// g_szErrorcorrectiondataField
TCHAR g_szErrorcorrectiondataField [][MAX_PATH] = {
	_T("Error Correction Flags"),
	_T("Error Correction Data Length (bits 0-3)"),
	_T("Opaque Data Present (bit 4)"),
	_T("Error Correction Length Type (bits 5-6)"),
	_T("Error Correction Present (bit 7)"),
	_T("Error Correction Data ")
};

TCHAR g_szErrorcorrectiondataDesc [][MAX_PATH*2] = {
	_T("Error Correction Flags"),
	//Error Correction Data Length (bits 0-3)
	_T("The value of this field is valid only if the value of the Error Correction Length Type field is 00. If the Error Correction Length Type field is 00, this field represents the size of the Error Correction Data field, in bytes.  The value of this field should be set to 0010. If the Error Correction Length Type field is different than 00, this field shall be set to 0000."),
	//Opaque Data Present (bit 4)
	_T("Specifies, if set, that the Error Correction Data field is followed by opaque data. The value of this field should be set to 0."),
	//Error Correction Length Type (bits 5-6)
	_T("Specifies the number of bits used to code the size of the error correction data. The value of this field should be set to 00, indicating that the size of the error correction data is stored in the Error Correction Data Length field.  Values other than 00 are reserved for future use."),
	//Error Correction Present (bit 7)
	_T("Specifies, if set, that this Data Packet starts with error correction information. If set, the structure of the Data Packet is as described above. If it is not set, the Data Packet starts with the payload structure, as shown in section 5.2.2."),
	_T("Error Correction Data ")
};
