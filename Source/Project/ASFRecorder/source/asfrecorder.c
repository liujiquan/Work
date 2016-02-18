/******************************************************************************\

  asfrecorder.c - by an unknown author, so no one is to blame.
                  Well, blame it on Microsoft.

                  Version 1.1 - Platinum Edition

                  new features:
                  -proxy and password support,
                  -a randomized client identifier (GUID),
                  -fixed problems with some asf files using partitioned headers,
                  -enhanced resume functionality to avoid broken ASF files.
                  -timecode correction for live recordings (enables seeking)

                  And that's it! This is my last ASFRecorder update!

------------------------------- How to Compile ---------------------------------

  Compile console-version on Linux (tested on SUSE)

     gcc asfrecorder.c -o asfrecorder

  Compile console-version on SUN OS:

     gcc -lsocket -lnsl asfrecorder.c -o asfrecorder

  Compile console-version with GCC 2.95.2 using CygWin B20.1 / MINGW32

     gcc -mno-cygwin -Wl,-s source/asfrecorder.c -o asfrecorder.exe -lws2_32 

  Compile GUI version with GCC 2.95.2 using CygWin B20.1 / MINGW32

     make GUI

  Compile console-version with VisualC++

     nmake /F NMAKEFILE

  Compile GUI version with VisualC++ (DirectShow SDK might be needed)

     nmake /F NMAKEFILE GUI=wingui

 ------------------------------------------------------------------------------

  Episode I
  
  The starship Voyager -- millions and millions of lightyears away from home --
  has encountered a quantum anomaly which completely wiped out the information
  stored on all of Voyager's secondary computer cores. This included the
  entire audio, video, fine arts and literature database and most of the
  holodeck programs. Fortunately, the Emergency Medical Hologram (the Holo Doc)
  has taken no damage.

  Months later, the Voyager and its crew -- desperately lingering for enter-
  tainment -- approached a planet which owned a rich selection of cultural,
  music and video programmes, but refused to offer this excellent material for
  downloading to the Voyager's computer core. "We only permit streaming access!",
  they kept responding. "And we are using one of the Universe's most advanced
  Active Stream Formats, which we are very proud of! It allows us to protect
  the rights we claim on this content."

  Janeway: "Tuvok, tactical analysis."

  Tuvok:   "The adversary has no defense systems. His protocols are
            simple and vulnerable. An attack will have a high probability
            of success."

  Janeway: "I had expected at least a minimal barrier against intrusion. Is
            there no kind of encryption? Not even an authorization procedure?"

  Tuvok:   "The computer reports that no security measures have been taken."

  Janeway: "Are they just too damn stupid or are they trying to trick us?
            Well, let's take our chance. On my command, download streaming
            content to our computer core. Begin transport now!"

------------------------------------------------------------------------------

  Episode II

  The Voyager orbited the planet for three days and secretly captured about
  seven million gigaquads of most exciting multimedia data.

  Kim:     "Captain, the planet's hailing us!"

  Janeway: "On screen."

  Prime    "Ha! You Bastards! You tricked us! You stole our most valuable
  Minister: goods! Our culture, our spirit, our souls! How dare you! Devils!"

  Janeway: (smiling) "No, we didn't steal it. Actually, we only replicated it.
            Didn't you find the switch to enable Digital Rights Management?"
           (laughing) Our pleasure."

  [Prime Minister gasps for air and ends the transmission.]

  Janeway: "Fire quantum torpedoes! Destroy all evidence! We don't want to let
            anybody know we just violated the prime directive, do we?"
  
  Neelix:  (whispering to Tom Paris): "This script really sucks. Why is she
            firing at those poor people?"

  Paris:   "Yeah, you are absolutely right. This idiot of a scriptwriter
            should be programming cool stuff instead of writing such hideous
            crap."

  7 of 9:  "Yes, even the Borg would refuse to act in such a cheap play."

  Tuvok:   "I totally agree. This script is illogical and most disturbing."


  Argh! Mutiny! The Voyager crew doesn't like my scriptwriting skills! So I
  better get going to add some cool stuff. Have a look at the fix_timecode()
  function to find some pure, compressed coolness.

  Fortunately there will be no Episode III... ;-)


\******************************************************************************/

/* Standard ANSI-C headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdarg.h>
#include <time.h>

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN
/* networking headers for Windows platform */
#include <winsock2.h>
/* networking compatibility for Windows platform */
#define errno WSAGetLastError()

#else /* WIN32 */

#ifdef  __MINGW32__

#ifdef GUI
/* we need to rename the main() function for MINGW32 */
/* because otherwise WinMain() will never be called */
#define main(argc,argv) renamed_main(argc,argv)
#endif

#ifdef OLD_WINDOWS_HEADERS

/* networking headers for CygWin/EGCS 1.1 and old windows headers */
#include <Windows32/Base.h>
#include <Windows32/Sockets.h>
typedef int caddr_t;

#else /* OLD_WINDOWS_HEADERS */

/* networking headers for GCC 2.95.2 */
#include <winsock2.h>
#undef errno

#endif /* OLD_WINDOWS_HEADERS */

/* networking compatibility for CygWin/MINGW32 */
#define errno WSAGetLastError()
/* define the WIN32 constant now */
#define WIN32

#else /* __MINGW32__ */

/* networking headers for Unix platform */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
/* networking compatibility for Unix platform */
#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
typedef struct sockaddr_in SOCKADDR_IN;
#define closesocket close
/* string compatbilitiy for Unix platform */
#define stricmp strcasecmp
#define strnicmp strncasecmp

#endif /* __MINGW32__ */

#endif /* WIN32 */


/* Prototypes for this source code module */
int main_function(int argc, char **argv);


/* largest chunk size this program can handle */
#define MAX_CHUNK_SIZE 65536


/* maximum number of URLs to handle at a time */
#define MAXURLS 100


/* The header ID to look for, all offsets relative to this ID */

unsigned char HDR_ID[16] = {0xa1,0xdc,0xab,0x8c,0x47,0xa9,0xcf,0x11,
                            0x8e,0xe4,0x00,0xc0,0x0c,0x20,0x53,0x65};

/* Offsets of some critical information in ASF header */

#define HDR_TOTAL_SIZE_8               0x28
#define HDR_NUM_PACKETS_8              0x38
#define HDR_FINE_TOTALTIME_8           0x40
#define HDR_FINE_PLAYTIME_8            0x48
#define HDR_PLAYTIME_OFFSET_4          0x50
#define HDR_FLAGS_4                    0x58
#define HDR_ASF_CHUNKLENGTH_4          0x5c
#define HDR_ASF_CHUNKLENGTH_CONFIRM_4  0x60

#define DATSEG_HDR_SIZE 0x32
#define DATSEG_NUMCHUNKS_4 0x28


/* Chunk types */

#define HEADER_CHUNK (('H' << 8) + '$')
#define DATA_CHUNK   (('D' << 8) + '$')
#define END_CHUNK    (('E' << 8) + '$')


/* The type of content on the server */
typedef enum
{
    connect_failed = 0,
    server_error,
    password_required,
    unknown_content,
    live_content,
    prerecorded_content,
    redirector_content,
} ContentType;


/* a custom structure be filled with some important */
/* information about the ASF file */
struct HeaderInfo
{
    ContentType contenttype;
    unsigned int redirsize;

    unsigned int header_offs;
    unsigned int totalsize_hi, totalsize_lo;
    unsigned int totaltime_hi, totaltime_lo;
    unsigned int offset;
    unsigned int chunklength;
    unsigned int chunklength2;
    unsigned int flags;
    unsigned int endofheader_offs;

    unsigned int time;
};



#ifndef GUI

/* Stub routines for non-existent GUI code. */

int gui_initialize()
{
    return 1;
}

void gui_uninitialize()
{
}

void gui_setbatchmode(int flag)
{
}

int gui_startedfromdesktop()
{
    return 0;
}


int gui_start_transmission(char *url, char *filename, int filenamesize, unsigned int totaltime, unsigned int maxtime)
{
    return 1;
}

void gui_progressinfo(int bytes, char *timecode, int progress, int seqno, int currenttime)
{
//    printf("%5d kB (%2d%%), tc: %s, seq: %d\n", bytes/1024, progress/100, timecode, seqno);
}

void gui_modify_duration(unsigned int totaltime)
{
}

void gui_finished_transmission()
{
}

void gui_not_idle(int flag)
{
}

void gui_prepareasyncsocket(SOCKET s)
{
}

void gui_restoresyncsocket(SOCKET s)
{
}

void gui_return_on_network_activity()
{
}

void gui_return_on_network_connect(int *retval)
{
}

int gui_nonblocking_socket_check(int num)
{
    return 0;
}

void gui_waitforuseraction(void)
{
}


void gui_showtext(char *text, ...)
{
    va_list args;
    va_start(args, text);
    vprintf(text, args);
    va_end(args);
}

void gui_setstatus(char *statustext, ...)
{
    va_list args;
    va_start(args, statustext);
    vprintf(statustext, args);
    va_end(args);
}

void gui_seterror(char *errortext, ...)
{
    va_list args;
    va_start(args, errortext);
    vprintf(errortext, args);
    va_end(args);
}

void gui_criticalerror(char *errortext, ...)
{
    va_list args;
    va_start(args, errortext);
    vprintf(errortext, args);
    va_end(args);
}

void gui_logtext(char *text, ...)
{
    va_list args;
    va_start(args, text);
    vprintf(text, args);
    va_end(args);
}

char *gui_translate_errorcode(int error)
{
    static char errorstring[32];
    sprintf(errorstring, "%d", error);
    return errorstring;
}

int gui_getpassword(char **username, char **password)
{
    return 0;
}

int gui_getproxy(char **proxy)
{
    return 0;
}

#else

/* Prototypes for GUI code in external module */

extern int  gui_initialize(void);
extern void gui_uninitialize(void);
extern void gui_setbatchmode(int flag);
extern int  gui_startedfromdesktop(void);

extern int  gui_start_transmission(char *url, char *filename, int filenamesize, unsigned int totaltime, unsigned int maxtime);
extern void gui_finished_transmission();
extern void gui_progressinfo(int bytes, char *timecode, int progress, int seqno, int currenttime);
extern void gui_modify_duration(unsigned int totaltime);
extern void gui_not_idle(int flag);

extern void gui_prepareasyncsocket(SOCKET s);
extern void gui_restoresyncsocket(SOCKET s);
extern void gui_return_on_network_activity();
extern void gui_return_on_network_connect(int *retval);
extern int  gui_nonblocking_socket_check(int num);
extern void gui_waitforuseraction(void);

extern void gui_showtext(char *text, ...);
extern void gui_setstatus(char *statustext, ...);
extern void gui_seterror(char *errortext, ...);
extern void gui_criticalerror(char *errortext, ...);
extern void gui_logtext(char *text, ...);
extern char *gui_translate_errorcode(int error);

extern int gui_getpassword(char **username, char **password);
extern int gui_getproxy(char **proxy);

#endif


/* protocol stuff */
#define DEFAULT_PORT 80


/* global flag for exiting the download */
int abortflag = 0;



/* helper functions */

/* get 64bit integer (Little endian) */

void get_quad(unsigned char *pos, unsigned int *hi, unsigned int *lo)
{
    unsigned char c1 = *pos++, c2 = *pos++, c3 = *pos++, c4 = *pos++;
    unsigned char c5 = *pos++, c6 = *pos++, c7 = *pos++, c8 = *pos++;
    (*hi) = (c8<<24) + (c7<<16) + (c6<<8) + c5;
    (*lo) = (c4<<24) + (c3<<16) + (c2<<8) + c1;
}

/* write 64bit integer to stream (Little endian) */

void write_quad(FILE *outfile, unsigned int hi, unsigned int lo)
{
    unsigned char c1 = (lo & 0xff), c2 = ((lo>>8) & 0xff), c3 = ((lo>>16) & 0xff), c4 = ((lo>>24) & 0xff);
    unsigned char c5 = (hi & 0xff), c6 = ((hi>>8) & 0xff), c7 = ((hi>>16) & 0xff), c8 = ((hi>>24) & 0xff);
    fputc(c1, outfile); fputc(c2, outfile); fputc(c3, outfile); fputc(c4, outfile);
    fputc(c5, outfile); fputc(c6, outfile); fputc(c7, outfile); fputc(c8, outfile);
}

/* get 32bit integer (Little endian) */

void get_long(unsigned char *pos, unsigned int *val)
{
    unsigned char c1 = *pos++, c2 = *pos++, c3 = *pos++, c4 = *pos++;
    (*val) = (c4<<24) + (c3<<16) + (c2<<8) + c1;
}

/* put 32 bit integer (Little endian) */

void put_long(unsigned char *pos, unsigned int val)
{
    *pos++ = (val & 0xff); *pos++ = ((val>>8) & 0xff), *pos++ = ((val>>16) & 0xff), *pos++ = ((val>>24) & 0xff);
}

/* write a 32 bit integer to stream (Little endian) */

void write_long(FILE *outfile, unsigned int val)
{
    unsigned char c1 = (val & 0xff), c2 = ((val>>8) & 0xff), c3 = ((val>>16) & 0xff), c4 = ((val>>24) & 0xff);
    fputc(c1, outfile); fputc(c2, outfile); fputc(c3, outfile); fputc(c4, outfile);
}

/* get short integer (Little endian) */

void get_short(unsigned char *pos, unsigned short *val)
{
    unsigned char c1 = *pos++, c2 = *pos++;
    (*val) = (c2<<8) + c1;
}

/* write a 32 bit integer to stream (Little endian) */

void write_short(FILE *outfile, unsigned short val)
{
    unsigned char c1 = (val & 0xff), c2 = ((val>>8) & 0xff);
    fputc(c1, outfile); fputc(c2, outfile);
}


/* 64 bit subtraction with unsigned integers */

void quad_subtraction(unsigned int *dst_hi, unsigned int *dst_lo, unsigned int hi, unsigned int lo)
{
    unsigned int tmp;

    *dst_hi -= hi;

    tmp = *dst_lo;
    *dst_lo -= lo;

    /* handle "carry bit" */
    if (*dst_lo > tmp) *dst_hi--;
}


/* timecode helper functions */

/* get position of timecode in chunk (-1 if unknown) */

int whereis_timecode(unsigned char *Buffer)
{
    int tc_start = -1;

    /* timecode position varies with type of chunk */
    switch(Buffer[3])
    {
    case 0x00: tc_start =  5; break;
    case 0x01: tc_start =  5; break;
    case 0x08: tc_start =  6; break;
    case 0x09: tc_start =  6; break;
    case 0x10: tc_start =  7; break;
    case 0x11: tc_start =  7; break;
    case 0x48: tc_start =  8; break;
    case 0x49: tc_start =  8; break;
    case 0x50: tc_start =  9; break;
    case 0x51: tc_start =  9; break;
    default:
        tc_start = -1;
        gui_logtext("unknown format type: $%02x\n", (int)Buffer[3]);
    }

    return tc_start;
}


/* Create a randomized GUID string to avoid filtering ASFRecorder's */
/* stream requests by means of detecting any hardcoded GUIDs */

void randomize_guid(unsigned char *buf)
{
    int digit, dig;
    time_t curtime;

    *buf++='{';
    time(&curtime);
    srand(curtime);
    for (digit=0; digit <32; digit++)
    {
        if (digit==8 || digit == 12 || digit == 16 || digit == 20) *buf++='-';

        dig = rand()%0xf;
        if (dig<10)
            *buf++='0'+dig;
        else
            *buf++='A'+(dig-10);
    }
    *buf++='}';
    *buf++='\0';
}


/* create a timecode string from a timecode in milliseconds */

char *createtimestring(unsigned int timecode)
{
    static char timecodestring[64];

    if (timecode/1000 >= 24*3600)
        sprintf(timecodestring, "%d:%02d:%02d:%02d.%03d", (timecode/1000)/(24*3600), ((timecode/1000)/3600)%24, ((timecode/1000)/60)%60, (timecode/1000)%60, timecode%1000);
    else
        if (timecode/1000 >= 3600)
            sprintf(timecodestring, "%d:%02d:%02d.%03d", (timecode/1000)/3600, ((timecode/1000)/60)%60, (timecode/1000)%60, timecode%1000);
        else
            if (timecode/1000 >= 60)
                sprintf(timecodestring, "%d:%02d.%03d", (timecode/1000)/60, (timecode/1000)%60, timecode%1000);
            else
                sprintf(timecodestring, "%d.%03d", (timecode/1000)%60, timecode%1000);
    return timecodestring;
}


/* subroutine for base64 encoding (used in HTTP Basic authentification) */

const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

int base64enc(char *data,char *out)
{
    int len = strlen(data);
    
    int i,index;
    int val;
    
    for (i=0, index=0; i<len; i+=3, index+=4)
    {
        int quad,trip;
        
        quad = 0;
        trip = 0;
        
        val = (0xff & data[i]);
        val <<= 8;
        if ((i+1) < len) {
            val |= (0xff & data[i+1]);
            trip = 1;
        }
        val <<= 8;
        if ((i+2) < len) {
            val |= (0xff & data[i+2]);
            quad = 1;
        }
        out[index+3] = alphabet[(quad? (val & 0x3f): 64)];
        val >>= 6;
        out[index+2] = alphabet[(trip? (val & 0x3f): 64)];
        val >>= 6;
        out[index+1] = alphabet[val & 0x3f];
        val >>= 6;
        out[index+0] = alphabet[val & 0x3f];
    }
    
    out[++index] = 0;
    
    return index;
}

    
/* helper routine for ASF header parsing */

int find_id(unsigned char *id, unsigned char *Buffer, int bufsize)
{
    int offs, i, found;
    for (offs = 0; offs < bufsize-16; offs++) {
        found=1;
        for (i=0; i<16; i++) if (Buffer[offs+i] != id[i]) {found = 0; break;}
        if (found) return(offs);
    }
    return -1;
}



/* These routines are used to parse the packet and find */
/* and modify timecodes for live streams */

unsigned int get_data(unsigned char **bp, unsigned int type)
{
    unsigned int res = 0;
    switch (type) {
        case 0: break;
        case 1: res = *(*bp+0); *bp+=1; break;
        case 2: res = *(*bp+0) + (*(*bp+1) << 8); *bp+=2; break;
        case 3: res = *(*bp+0) + (*(*bp+1) << 8) + (*(*bp+2) << 16) + (*(*bp+3) << 24); *bp+=4; break;
        default: gui_logtext("unknown format type %d\n", type); break;
    }
    return res;
}

int fix_timecodes(unsigned char *Buffer, int bodylength, unsigned int deltatime, unsigned int in_chunk_no, struct HeaderInfo *hi)
{
    /* This coding style is actually meant to confuse you. */
    /* Don't ask what I am doing here. Just don't ask!     */
    /* You are not supposed to understand this...          */
    /* But be assured that this is good for you ;-)        */
    unsigned char *ptr1,b1;
    unsigned int f1,f2,l1,l2,l3,l4,l5,l6,l7,l8,n1,n;
    unsigned int v1,v2,v3,v4,v5=0,v6,v7,v8,v9,v10;
    if (!(Buffer[0]==0x82&&Buffer[1]==0x00&&Buffer[2]==0x00)){
        gui_logtext("Illegal header bytes in chunk %d!\n",in_chunk_no);return 1;}
    ptr1=&Buffer[3];b1=*ptr1++;f1=(b1&0x80)>>7;
    if(f1==0){l1=(b1&0x60)>>5;l2=(b1&0x18)>>3;l3=(b1&0x06)>>1;f2=(b1&0x01);}
    else{gui_logtext("Chunks carrying error correction information are not supported yet!\n");return 1;}
    b1=*ptr1++;l4=(b1&0xc0)>>6;l5=(b1&0x30)>>4;l6=(b1&0x0c)>>2;l7=(b1&0x03);
    v1=get_data(&ptr1,l1);v2=get_data(&ptr1,l3);v3=get_data(&ptr1,l2);v4=get_data(&ptr1,3);
    v4=(deltatime<v4)?v4-=deltatime:0;put_long(ptr1-4,v4);
    if(l1==0)v1=hi->chunklength;if(l3==0)v2=in_chunk_no;if(v3>0)memset(Buffer+v1-v3,0,v3);
    ptr1+=2;b1=*ptr1++;l8=(b1&0x80)>>7;if(l8==0)l8=2;else l8=2; /* ;-) */
    n1=(b1&0x1f);if(f2==0){n1=1;l8=0;}for(n=0;(n<n1);n++){
    if(f2!=0)v5=get_data(&ptr1,l4);v6=get_data(&ptr1,l5);v7=get_data(&ptr1,l6);v8=get_data(&ptr1,l7);
    if(v8==8){get_long(ptr1+4,&v10);v10=(deltatime<v10)?v10-=deltatime:0;put_long(ptr1+4,v10);}
    if(v8>0)ptr1+=v8;if(f2!=0)v9=get_data(&ptr1,l8);else v9=(v1-v3)-(ptr1-Buffer);if(v9>0)ptr1+=v9;
    if((unsigned int)(ptr1-Buffer)>hi->chunklength){
        gui_logtext("WARNING! buffer pointer %d bytes after packet!\n",(unsigned int)(ptr1-Buffer)-hi->chunklength);return 1;}
    if ((unsigned int)(ptr1-Buffer)>hi->chunklength-v3){
        gui_logtext("WARNING! buffer pointer %d bytes after packet-padlen!\n",(unsigned int)(ptr1-Buffer)-(hi->chunklength-v3));return 1;}}
    if((ptr1-Buffer)<(int)hi->chunklength-(int)v3)
        gui_logtext("NOTE: %d bytes not covered by payload\n",hi->chunklength-v3-(ptr1-Buffer));
    return 0;
    /* Ha, ha! Never ever before in my life I produced such an unreadable code! ;-) */
}



/* Replace specific characters in the URL string by an escape sequence */

/* works like strcpy(), but without return argument */
void escape_url_string(char *outbuf, char *inbuf)
{
    unsigned char c;
    do
    {
        c = *inbuf++;
        
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') ||
            c=='-' || c=='_'  || c=='.' || c=='!' || c=='~'  || /* mark characters */
            c=='*' || c=='\'' || c=='(' || c==')' ||
            c=='%' ||                                           /* do not touch escape character */
            c==';' || c=='/'  || c=='?' || c==':' || c=='@'  || /* reserved characters */
            c=='&' || c=='='  || c=='+' || c=='$' || c==','  || /* see RFC 2396 */
            c=='\0' )
        {
            *outbuf++ = c;
        }
        else
        {
           /* all others will be escaped */
            unsigned char c1 = ((c & 0xf0) >> 4); 
            unsigned char c2 =  (c & 0x0f);
            if (c1 < 10) c1+='0'; else c1+='A';
            if (c2 < 10) c2+='0'; else c2+='A';
            *outbuf++ = '%';
            *outbuf++ = c1;
            *outbuf++ = c2;
        }
        
    } while (c != '\0');
}


/* Replace escape sequences in an URL (or a part of an URL) */

/* works like strcpy(), but without return argument */
void unescape_url_string(char *outbuf, char *inbuf)
{
    unsigned char c;
    do
    {
        c = *inbuf++;
        if (c == '%')
        {
            unsigned char c1 = *inbuf++;
            unsigned char c2 = *inbuf++;
            if (((c1>='0' && c1<='9') || (c1>='A' && c1<='F')) &&
                ((c2>='0' && c2<='9') || (c2>='A' && c2<='F')) )
            {
                if (c1>='0' && c1<='9') c1-='0'; else c1-='A';
                if (c2>='0' && c2<='9') c2-='0'; else c2-='A';
                c = (c1<<4) + c2;
            }
        }
        *outbuf++ = c;

    } while (c != '\0');
}



/* generate a valid filename */

/* NOTE: this currently implements proper rules for Windows only */

void generate_valid_filename(char *buffer)
{
    char *inbuf = buffer, *outbuf = buffer;
    unsigned char c;
    int length = 0;
    do
    {
        c = *inbuf++;
        if (
#ifdef WIN32
        /* Windows does not allow the following characters in file names */
        /* and filename length (including '\0') is restricted to 255 characters */

        (c!='/' && c!='\\' && c!=':' && c!='*' && c!='?' &&
         c!='"' && c!='<'  && c!='>' && c!='|' && length < 254) || c=='\0'
#else
        /* Unix */
        /* disallow forward slash (directory separator)... anything else?!?! */

         c!='/'
#endif
        )
        {
            *outbuf++ = c;
            length++;
        }

    } while (c != '\0');
}



/* this routine can be called from the GUI to signal an abort */

void gui_abort()
{
    abortflag = 1;
}



/* ctrl-c handler */
/* WIN32: Beware! The ctrl-c handler is called in a different thread. */

void ctrlc(int sig)
{
    gui_seterror("\n***CTRL-C\n");
    abortflag = 1;
    signal(SIGINT, ctrlc);
}



/* The following (blocking) socket calls are encapsulated in an event loop */
/* that allows the GUI code to handle user input during a blocking network */
/* operation */

/* The GUI code must set the socket to non-blocking mode, install an event */
/* notification mechanism on the socket and return on detection of a network */
/* event. */

SOCKET my_socket(int af, int type, int protocol)
{
    SOCKET s;
    s = socket(af, type, protocol);

    if (s != INVALID_SOCKET)
    {
        gui_prepareasyncsocket(s);
    }
    return s;
}

int my_closesocket(SOCKET s)
{
    gui_restoresyncsocket(s);

    return closesocket(s);
}

int my_recv(SOCKET s, char *buf, int len, int flags)
{
    int returnval=0;
    while (!abortflag)
    {
        returnval = recv(s, buf, len, flags);
        if (returnval == SOCKET_ERROR && gui_nonblocking_socket_check(errno))
            gui_return_on_network_activity();
        else
            break;
    }

    return returnval;
}

int my_send(SOCKET s, const char *buf, int len, int flags)
{
    int returnval=0;
    while (!abortflag)
    {
        returnval = send(s, buf, len, flags);
        if (returnval == SOCKET_ERROR && gui_nonblocking_socket_check(errno))
            gui_return_on_network_activity();
        else
            break;
    }

    return returnval;
}


int my_connect(SOCKET s, const struct sockaddr *name, int namelen)
{
    int returnval=0;
    while (!abortflag)
    {
        returnval = connect(s, name, namelen);
        if (returnval == SOCKET_ERROR && gui_nonblocking_socket_check(errno))
            gui_return_on_network_connect(&returnval);
        break;
    }

    return returnval;
}


/* Stream input routines. This code uses a simple, circular buffer */

/* the circular stream buffer. */
#define STREAMBUFSIZE 4096
char StreamBuffer[STREAMBUFSIZE];
int sb_inpos = 0;
int sb_outpos = 0;
int networkeof;
int streameof;


/* reset circular stream buffer */
void flushstream()
{
    sb_inpos = 0;
    sb_outpos = 0;

    networkeof = 0;
    streameof = 0;
}


/* check end of stream status */
int eos()
{
    return streameof;
}


/* read one or more bytes from the stream. */
int readfromstream(SOCKET conn_socket, char *dest, int length, FILE *rawfile)
{
    int got = 0;
    int totalread = 0;

    while ((!streameof) && (length >0))
    {
        int lag;

        lag = (STREAMBUFSIZE + sb_outpos - sb_inpos) % STREAMBUFSIZE;
        if (lag == 0) lag = STREAMBUFSIZE;

        /* refill circular buffer only when at least half of it is empty */
        if ((!networkeof) && (lag > STREAMBUFSIZE/2))
        {
            int retval;
            int toend = sb_outpos - sb_inpos - 1;
            if (toend < 0) toend = STREAMBUFSIZE - sb_inpos;
            if (toend > 0)
            {
                retval = my_recv(conn_socket, &StreamBuffer[sb_inpos], toend, 0 );
                if (retval == SOCKET_ERROR)
                {
                    gui_seterror("recv() failed: %s\n",gui_translate_errorcode(errno));
                    networkeof = 1;
                }

                if (retval == 0)
                {
                    networkeof = 1;
                }

                if (retval > 0)
                {
                    if (rawfile != NULL)
                    {
                        fwrite(&StreamBuffer[sb_inpos], 1, retval, rawfile);
                    }
                    sb_inpos += retval;
                }
            }
        }

        /* check if circular buffer contains data */
        if (sb_outpos != sb_inpos)
        {
            /* report EOF only when circular buffer is empty */

            sb_inpos = sb_inpos % STREAMBUFSIZE;

            while (length > 0)
            {
                *dest++ = StreamBuffer[sb_outpos++];
                sb_outpos = sb_outpos % STREAMBUFSIZE;
                length--;
                totalread++;

                if (sb_outpos == sb_inpos) break;
            }
        }
        else
        {
            if (networkeof)
            {
                streameof = 1;
                break;
            }
        }

    }
    return totalread;
}


/* The core routine for ASF download/extraction. */

int collectdata(int headeronly,
                int dumpheaders,
                FILE *rawfile,
                FILE *outfile,
                int bytesread,
                unsigned char *Buffer,
                int bufsize,
                int sendlen,
                struct hostent *hp,
                char *server_name,
                unsigned int addr,
                unsigned short port,
                int socket_type,
                char *file,
                struct HeaderInfo *hi,
                int maxtime)
{
    SOCKET  conn_socket;
    int retval;

    SOCKADDR_IN server;

    int eol;
    int hdrpos;
    int linepos;
    int linenum;
    char HTTPHeader[1024];
    int resume = 0;

    char HTTPLine[512];
    char HTTPMessage[128];
    char *hdrptr;
    int errorcode;

    memset(hi, 0, sizeof(*hi));
    hi->contenttype = connect_failed;

    /* Dump the outgoing HTTP request */
    if (dumpheaders)
    {
        gui_logtext("\nHTTP-Request:\n%s", Buffer);
    }

    if (bytesread > 0) resume = 1;

    /* Copy the resolved information into the sockaddr_in structure */
    memset(&server,0,sizeof(server));
    if (hp!=NULL)
    {
        memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
        server.sin_family = hp->h_addrtype;
        strcpy(server_name, hp->h_name);
    }
    else
    {
        memcpy(&(server.sin_addr), &addr, 4);
        server.sin_family = AF_INET;
    }
    server.sin_port = htons(port);

    conn_socket = my_socket(AF_INET,socket_type,0); /* Open a socket */
    if (conn_socket < 0)
    {
        gui_seterror("socket() failed: %s\n", gui_translate_errorcode(errno));
    }
    else
    {
        gui_setstatus("connecting to: %s\n",server_name);

        if (my_connect(conn_socket,(struct sockaddr*)&server,sizeof(server))
            == SOCKET_ERROR)
        {
            gui_seterror("connect() failed: %s\n",gui_translate_errorcode(errno));
        }
        else
        {
            gui_setstatus("sending request [%d bytes]\n",sendlen);

            retval = my_send(conn_socket,Buffer,sendlen,0);
            if (retval == SOCKET_ERROR)
            {
                gui_seterror("send() failed: %s\n",gui_translate_errorcode(errno));
            }
            else
            {
                unsigned char Features[256];
                unsigned char ContentType[256];

                gui_setstatus("waiting for reply...\n");

                flushstream();

                errorcode = 0;
                strcpy(HTTPMessage, "<none>");

                strcpy(ContentType, "");
                strcpy(Features, "");

                eol = 0;
                hdrpos = 0;
                linepos = 0;
                linenum = 0;
                for (;;)
                {
                    char c;

                    if (readfromstream(conn_socket, &c, 1, rawfile) == 1)
                    {
                        if ((c != '\r') && (c != '\n'))
                        {
                            eol = 0;
                            HTTPLine[linepos++] = c;
                        }
                        else
                            HTTPLine[linepos++] = 0;

                        if (c == '\n')
                        {
                            if (eol == 0)
                            {
                                linepos = 0;
                                eol = 1;
                                linenum++;

                                hdrptr = HTTPLine;

                                /* Parse first line of HTTP reply */
                                if (linenum == 1)
                                {
                                    if ((!strnicmp(hdrptr, "HTTP/1.0 ", 9)) ||
                                        (!strnicmp(hdrptr, "HTTP/1.1 ", 9))   )
                                    {
                                        hdrptr+=9;
                                        sscanf(hdrptr, "%d", &errorcode);
                                        hdrptr+=4;
                                        strcpy(HTTPMessage, hdrptr);
                                    }
                                    else
                                    {
                                        gui_seterror("Illegal server reply! Expected HTTP/1.0 or HTTP/1.1\n");
                                        hi->contenttype = unknown_content;
                                    }
                                }
                                else
                                {
                                    /* Parse all other lines of HTTP reply */
                                    if (!strnicmp(hdrptr, "Content-Type: ", 14))
                                    {
                                        hdrptr+=14;
                                        strncpy(ContentType, hdrptr, sizeof(ContentType));
                                    }

                                    /* Parse all other lines of HTTP reply */
                                    if (!strnicmp(hdrptr, "Pragma: ", 8))
                                    {
                                        hdrptr+=8;
                                        if (!strnicmp(hdrptr, "features=", 9))
                                        {
                                            hdrptr+=9;
                                            strncpy(Features, hdrptr, sizeof(Features));
                                        }
                                    }
                                }
                            }
                            else
                            {
                                HTTPHeader[hdrpos++] = 0;
                                break;
                            }
                        }

                        HTTPHeader[hdrpos++] = c;
                    }
                    else
                    {
                        gui_seterror("readfromstream() returned other than 1!\n");
                        if (eos()) break;
                    }
                }

                hi->contenttype = unknown_content;

                /* Determine whether this is live content or not */
                if (!stricmp(ContentType, "application/octet-stream"))
                {
                    if (strstr(Features, "broadcast"))
                    {
                        hi->contenttype = live_content;
                    }
                    else
                    {
                        hi->contenttype = prerecorded_content;
                    }
                }
                else
                {
                    if ((!stricmp(ContentType, "audio/x-ms-wax")) ||
                        (!stricmp(ContentType, "audio/x-ms-wma")) ||
                        (!stricmp(ContentType, "video/x-ms-asf")) ||
                        (!stricmp(ContentType, "video/x-ms-afs")) ||
                        (!stricmp(ContentType, "video/x-ms-wvx")) ||
                        (!stricmp(ContentType, "video/x-ms-wmv")) ||
                        (!stricmp(ContentType, "video/x-ms-wma"))   )
                    {
                        hi->contenttype = redirector_content;
                        /* try to read as much data as fits into the buffer */
                        /* bufsize should be enough for any redirector files */
                        if (!eos()) hi->redirsize = readfromstream(conn_socket, Buffer, bufsize, rawfile);
                    }
                    else
                    {
                        if ( (!stricmp(ContentType, "text/html")) ||
                             (!stricmp(ContentType, "text/plain"))  )
                        {
                            /* well, maybe we are lucky and this HTML or plaintext */
                            /* file inexpectedly contains some redirector content  */
                            /* (due to a badly configured webserver!) */
                            if (!eos()) hi->redirsize = readfromstream(conn_socket, Buffer, bufsize, rawfile);
                            hdrptr = Buffer;
                            /* eat whitespaces */
                            while( (*hdrptr == ' ')  || (*hdrptr == '\t') ||
                                   (*hdrptr == '\r') || (*hdrptr == '\n')   ) hdrptr++;
                            if ((!strnicmp(hdrptr, "<ASX",   4)) ||
                                (!strnicmp(hdrptr, "< ASX",  5)) ||
                                (!strnicmp(hdrptr, "ASF ",   4)) ||
                                (!strnicmp(hdrptr, "ASF\t",  4)) ||
                                (!strnicmp(hdrptr, "http://",7)) ||
                                (!strnicmp(hdrptr, "mms://", 6)) ||
                                (!strnicmp(hdrptr, "mmst://",7)) ||
                                (!strnicmp(hdrptr, "mmsu://",7)) ||
                                (!strnicmp(hdrptr, "[Reference]", 11)) )
                            {
                                hi->contenttype = redirector_content;
                            }
                        }
                        else
                        {
                            gui_logtext("unknown content-type: %s\n", ContentType);
                        }
                    }
                }

                if (errorcode == 200 || errorcode == 401)
                    gui_setstatus("reply: %d - %s\n", errorcode, HTTPMessage);
                else
                    gui_seterror("reply: %d - %s\n", errorcode, HTTPMessage);

                /* Dump the incoming HTTP reply */
                if (dumpheaders)
                {
                    gui_logtext("\nHTTP-Reply:\n%s\n", HTTPHeader);
                }

                if (errorcode == 200)
                {
                }
                else
                {
                    if (errorcode == 401)
                    {
                        hi->contenttype = password_required;
                    }
                    else
                    {
                        hi->contenttype = server_error;
                    }
                }

                /* handle live or prerecorded content */
                if ((!eos()) && ((hi->contenttype == live_content) || (hi->contenttype == prerecorded_content)) )
                {
                    unsigned int starttime_hi = 0xffffffff;
                    unsigned int starttime    = 0xffffffff;
                    unsigned int startseqno   = 0xffffffff;
                    unsigned int maxtimecode  = 0;
                    int          endofheaderposition = 0;
                    int          numdatachunks       = 0;
                    int          sizeofdatachunks    = 0;

                    int          header_length = 0;
                    int          header_offset = 0;

                    /* The main loop for chunk extraction/ASF generation */
                    for (;;)
                    {
                        unsigned char c1;
                        unsigned char c2;

                        unsigned short type;

                        unsigned char l1;
                        unsigned char l2;
                        int length;
                        int length2;
                        int bodylength;

                        unsigned char s1;
                        unsigned char s2;
                        unsigned char s3;
                        unsigned char s4;
                        unsigned int seqno;

                        unsigned char u1;
                        unsigned char u2;
                        unsigned short partflag;

                        unsigned int timecode;

                        int progress; /* scaled from 0 to 10000 */

                        char timecodestring[100];
                        int got;

                        /* Check for EOF and extract chunk header */
                        /* bytes are read one by one so this code */
                        /* remains portable to non-INTEL platforms */

                        if (eos()) { gui_setstatus("Connection reset\n"); break; }

                        /* read basic chunk type */
                        readfromstream(conn_socket, &c1, 1, rawfile);
                        readfromstream(conn_socket, &c2, 1, rawfile);
                        type = (c2<<8) + c1;

                        /* These header types correspond to "H$", "D$" and "E$" */
                        /* (Header, Data and End) */
                        if ((type != HEADER_CHUNK) && (type != DATA_CHUNK) && (type != END_CHUNK))
                        {
                            gui_logtext("Unknown header type: $%04x\n", type);
                        }

                        if (type == END_CHUNK)
                        {
                            gui_setstatus("Transfer complete.\n");
                            break;
                        }

                        if (eos()) { gui_setstatus("Connection reset\n"); break; }

                        /* read chunk length (max 64k) */
                        readfromstream(conn_socket, &l1, 1, rawfile);
                        readfromstream(conn_socket, &l2, 1, rawfile);
                        length = (l2<<8) + l1;

                        if (eos()) { gui_setstatus("Connection reset\n"); break; }

                        /* read chunk sequence number */
                        readfromstream(conn_socket, &s1, 1, rawfile);
                        readfromstream(conn_socket, &s2, 1, rawfile);
                        readfromstream(conn_socket, &s3, 1, rawfile);
                        readfromstream(conn_socket, &s4, 1, rawfile);
                        seqno   = (s4<<24) + (s3<<16) + (s2<<8) + s1;

                        if (eos()) { gui_setstatus("Connection reset\n"); break; }

                        /* read two unknown bytes */
                        readfromstream(conn_socket, &u1, 1, rawfile);
                        readfromstream(conn_socket, &u2, 1, rawfile);
                        partflag = (u2<<8) + u1;

                        if (eos()) { gui_setstatus("Connection reset\n"); break; }

                        /* read second length entry (length confirmation) */
                        readfromstream(conn_socket, &l1, 1, rawfile);
                        readfromstream(conn_socket, &l2, 1, rawfile);
                        length2 = (l2<<8) + l1;

                        if (eos()) { gui_setstatus("Connection reset\n"); break; }

                        /* Sanity check on chunk header. Second length entry must match the first. */
                        if (length2 != length)
                        {
                            gui_logtext("Length confirmation doesn't match!\n");
                            break;
                        }

                        /* calculate length of chunk body. */
                        bodylength = length-8;

                        /* check if the body length exceeds our buffer size */
                        if (bodylength > bufsize)
                        {
                            gui_logtext("Buffer too small. Chunk is %d bytes!\n", length);
                            break;
                        }

                        /* check length of chunk body */
                        if (bodylength <= 0)
                        {
                            gui_logtext("Chunk has no body!\n");
                            break;
                        }

                        /* Read chunk's body data */
                        if (type != HEADER_CHUNK) header_offset = 0;
                        got = readfromstream(conn_socket, Buffer + header_offset, bodylength, rawfile);
                        bodylength = header_offset + bodylength;
                        got        = header_offset + got;

                        /* Try to extract a timecode from all known chunk/content types */
                        strcpy(timecodestring, "???");
                        timecode = 0;

                        /* this only applies to data chunks */
                        if (type == DATA_CHUNK)
                        {
                            int tc_start;

                            if (headeronly) break;

                            /* save the first seqno available as a reference */
                            if (startseqno == 0xffffffff)
                            {
                                startseqno = seqno;
                            }

                            /* fix the seqno for live recordings only */
                            if (hi->time == 0)
                            {
                                /* refer seqno to the point we "zapped in" (for live streams) */
                                if (startseqno != 0xffffffff)
                                    seqno -= startseqno;
                            }

                            /* find the location of the time code */
                            if ((tc_start = whereis_timecode(Buffer)) > 0)
                            {
                                /* The timecode is an integer value defining milliseconds */
                                /* enough range for about 50 days! */
                                get_long(&Buffer[tc_start], &timecode);

                                /* save the first timecode available as a reference */
                                if (starttime == 0xffffffff)
                                    starttime = timecode;

                                /* fix timecode for live recordings only */
                                if (hi->time == 0)
                                {
                                    /* refer timecode to the point we "zapped in" (live streams) */
                                    timecode -= starttime;

                                    /* this fixes the timecodes in the memory buffer */
                                    fix_timecodes(Buffer, bodylength, starttime, seqno, hi);
                                }

                                /* save max. timecode value */
                                if (timecode > maxtimecode)
                                    maxtimecode = timecode;

                                /* create a string with a human-readable form of the timecode */
                                strcpy(timecodestring, createtimestring(timecode));
                            }
                        }

                        /* calculate progress indicator (scale: 0....10000) */
                        if (hi->time == 0)
                             /* live streams */
                            if (maxtime == 0)   /* unlimited recording */
                                progress = 0;
                            else                /* limited time recording */
                                progress = (int)((double)timecode*10000/(maxtime*60*1000));
                        else
                            /* prerecorded content */
                            progress = (int)((double)timecode*10000/hi->time);

                        /* Print current position in stream download */
                        gui_logtext("%5d kB (%2d%%), HDR: $%04x, part: $%04x, %4d bytes, seq $%08x, tc: %s\n", bytesread/1024, progress/100, (int)type, (int)partflag, length, seqno, timecodestring);

                        /* Extract the block size from the ASF header. */
                        /* This block size is essential in the ASF file */
                        /* format. All data chunks in the ASF file must */
                        /* have this length, even if network transmission */
                        /* sent us smaller chunks! */
                        if (type == HEADER_CHUNK)
                        {
                            int offs;
                            
                            /* Headers may be split into several parts with */
                            /* a rising sequence number. This case occurs in */
                            /* audio books on broadcast.com, for example. */

                            /* This indicates the first header part */
                            if (partflag & 0x0400)
                            {
                                header_offset = 0;
                                get_long(&Buffer[16], &header_length);
                                header_length += 50;
                            }

                            /* header progress indicator */
                            if (bodylength < header_length)
                                gui_setstatus("receiving ASF header (%d/%d)!\n", bodylength, header_length);

                            /* Skip parsing the header if it hasn't been received completely */
                            if (!(partflag & 0x0800))
                            {
                                /* next header partition will be appended */
                                header_offset = bodylength;

                                /* this prevents saving a partial header to the output file */
                                bodylength = header_length;
                            }
                            else
                            {
                                /* finally got the header */
                                gui_setstatus("received ASF header!\n");

                                /* find a specific object in this header */
                                offs = find_id(HDR_ID,Buffer, got);
                                if (offs == -1)
                                {
                                    gui_criticalerror("Unable to parse this ASF header!\n");
                                    break;
                                }
                                else
                                {
                                    /* extract required information */
                                    hi->header_offs = offs;
                                    get_quad(&Buffer[offs+HDR_TOTAL_SIZE_8], &hi->totalsize_hi, &hi->totalsize_lo);
                                    get_quad(&Buffer[offs+HDR_FINE_TOTALTIME_8], &hi->totaltime_hi, &hi->totaltime_lo);
                                    get_long(&Buffer[offs+HDR_PLAYTIME_OFFSET_4], &hi->offset);
                                    get_long(&Buffer[offs+HDR_FLAGS_4], &hi->flags);
                                    get_long(&Buffer[offs+HDR_ASF_CHUNKLENGTH_4], &hi->chunklength);
                                    get_long(&Buffer[offs+HDR_ASF_CHUNKLENGTH_CONFIRM_4], &hi->chunklength2);
                                    
                                    /* check if the extracted chunk length looks good */
                                    if (!(hi->chunklength < MAX_CHUNK_SIZE && (hi->chunklength == hi->chunklength2)))
                                    {
                                        gui_criticalerror(
                                            "Unable to capture this stream!\n"
                                            "This one uses variable chunk sizes,\n"
                                            "which is not supported. Sorry! ;-)\n");
                                        
                                        hi->contenttype = unknown_content;
                                        break;
                                    }
                                    
                                    /* calculate playtime in milliseconds (0 for live streams) */
                                    if (hi->totaltime_hi == 0 && hi->totaltime_lo == 0)
                                    {
                                        hi->time = 0; /* live streams */
                                    }
                                    else
                                        hi->time = (int)((double)429496.7296 * hi->totaltime_hi) + (hi->totaltime_lo / 10000) - hi->offset;

                                    /* store position where the ASF header segment ends */
                                    /* and the chunk data segment starts */
                                    hi->endofheader_offs = bodylength - DATSEG_HDR_SIZE;
                                    
                                    if (!headeronly)
                                        gui_setstatus("receiving stream...\n");
                                    else
                                        break;
                                }
                            }
                        }

                        /* check chunk body for completeness */
                        if (got < bodylength)
                        {
                            if (outfile != NULL && type == DATA_CHUNK)
                                gui_logtext("Received incomplete chunk... (Chunk is NOT saved)\n");
                        }
                        else
                        {
                            /* Ignore media type header if the download */
                            /* resumes a previous transmission */
                            if (type == HEADER_CHUNK && resume)
                            {
                                gui_logtext("Not saving header since this is a RESUME.\n");
                            }
                            else
                            {
                                /* count how many bytes we accepted from server */
                                bytesread += got;

                                /* some statistics for data chunks only */
                                if (type == DATA_CHUNK)
                                {
                                    /* count number of chunks */
                                    numdatachunks++;

                                    /* count total size of chunks */
                                    sizeofdatachunks += hi->chunklength;
                                }

                                if (outfile != NULL)
                                {
                                    if (type == DATA_CHUNK)
                                    {
                                        /* When saving data chunks, seek to appropriate position */
                                        /* in file. This should prevent problems when resuming to */
                                        /* download files containing a truncated last chunk */
                                        fseek(outfile, hi->endofheader_offs + DATSEG_HDR_SIZE + seqno * hi->chunklength, SEEK_SET);
                                    }

                                    /* Save chunk body to ASF file */
                                    fwrite(Buffer, 1, got, outfile);

                                    /* Fill up unused bytes in this chunk. */
                                    /* ASF requires equally sized chunks for */
                                    /* the main stream content */
                                    if (type == DATA_CHUNK && got < (int)hi->chunklength)
                                    {
                                        int i;
                                        for (i=0; i < (int)hi->chunklength-got; i++) fputc(0, outfile);
                                    }
                                }

                                /* send progress information to main GUI */
                                gui_progressinfo(bytesread, timecodestring, progress, seqno, timecode);

                                /* set a new total time for the stream */
                                /* (important for preview and slider functionality) */
                                if (hi->time == 0)
                                {
                                    if (maxtime == 0)
                                        gui_modify_duration(timecode);
                                    else
                                        gui_modify_duration(maxtime*60*1000);
                                }
                            }
                        }

                        /* use recording time limit, if specified */
                        if (maxtime != 0)
                        {
                            if ((int)timecode >= (maxtime*60*1000))
                            {
                                gui_setstatus("maxtime reached.\n");
                                break;
                            }
                        }

                        /* check for end request */
                        if (abortflag) break;

                    } /* for (;;) */

                    /* fix total file size and for live streams the header information as well */
                    if (outfile != NULL)
                    {
                        unsigned int filesize_lo;
                        unsigned int filesize_hi;

                        /* Determine file size of .ASF file */
                        fseek(outfile, 0, SEEK_END);
                        filesize_hi = 0;
                        filesize_lo = ftell(outfile);

                        /* write this file size to the ASF header */
                        fseek(outfile, hi->header_offs + HDR_TOTAL_SIZE_8, SEEK_SET);
                        write_quad(outfile, filesize_hi, filesize_lo);

                        /* Correct some details for live streams */
                        if (hi->time == 0)
                        {
                            double totaltime;
                            unsigned int totaltime_hi;
                            unsigned int totaltime_lo;

                            double playtime;
                            unsigned int playtime_hi;
                            unsigned int playtime_lo;

                            unsigned int num_chunks_hi;
                            unsigned int num_chunks_lo;

                            unsigned int segmentsize_hi;
                            unsigned int segmentsize_lo;

                            /* bugfixed calculations, these were broken in V 1.0 */
                            totaltime = (double)(maxtimecode) * 10000;
                            totaltime_hi = (int)(totaltime / 4294967296.0);
                            totaltime_lo = (int)(totaltime - ((double)totaltime_hi * 4294967296.0));

                            playtime = (double)(maxtimecode - hi->offset) * 10000;
                            playtime_hi = (int)(playtime / 4294967296.0);
                            playtime_lo = (int)(playtime - ((double)playtime_hi * 4294967296.0));

                            num_chunks_hi = 0;
                            num_chunks_lo = numdatachunks;

                            /* write correct number of packets for stream */
                            fseek(outfile, hi->header_offs + HDR_NUM_PACKETS_8, SEEK_SET);
                            write_quad(outfile, num_chunks_hi, num_chunks_lo);

                            /* write correct totaltime for stream */
                            fseek(outfile, hi->header_offs + HDR_FINE_TOTALTIME_8, SEEK_SET);
                            write_quad(outfile, totaltime_hi, totaltime_lo);

                            /* write correct playtime for stream */
                            fseek(outfile, hi->header_offs + HDR_FINE_PLAYTIME_8, SEEK_SET);
                            write_quad(outfile, playtime_hi, playtime_lo);

                            /* enable seeking in file */
                            fseek(outfile, hi->header_offs + HDR_FLAGS_4, SEEK_SET);
                            write_long(outfile, 0x00000002);

                            /* write total size of data chunk segment */
                            segmentsize_hi = 0;
                            segmentsize_lo = DATSEG_HDR_SIZE + sizeofdatachunks;
                            fseek(outfile, hi->endofheader_offs + 0x10, SEEK_SET);
                            write_quad(outfile, segmentsize_hi, segmentsize_lo);

                            /* write total number of chunks */
                            fseek(outfile, hi->endofheader_offs + DATSEG_NUMCHUNKS_4, SEEK_SET);
                            write_long(outfile, numdatachunks);
                        }
                    }

                    if (abortflag)
                    {
                        gui_seterror("Transfer aborted!\n");
                    }
                }
            }
        }
        my_closesocket(conn_socket);
    }

    return abortflag;
}


enum
{
    mode_determinefiletype,
    mode_searchforbracket,
    mode_expectkeyword,
    mode_readkeyword,
    mode_expectoption,
    mode_readoption,
    mode_expectargumentoroption,
    mode_argumentstart,
    mode_argument,
    mode_argumentquotes,
    mode_expectclosingbrackets,
};

enum
{
    submode_none,
    submode_eatwhite
};

typedef enum
{
    unknownfile = 0,
    xmlfile,
    inifile,
    plainfile,

} ASXFileType;


/* parse a redirection file (either from disk or from memory) */
/* builds a list of stream references (URLs) */

int parse_redirection( unsigned char *filename, unsigned char *buffer, unsigned int redir_size, unsigned int maxtime, unsigned short portnum )
{
    int result = 0;

    FILE *infile;

    ASXFileType filetype;
    int error = 0;

    unsigned char *pos;
    int c;
    int iswhite;
    int isalpha;

    int mode;
    int submode;

    unsigned char *urlptr;
    char URLBuffer[4096];
    int my_argc;
    int urlcounter;
    unsigned char *(my_argv[MAXURLS]);

    unsigned char Keyword[128];
    unsigned char *keywordptr = NULL;

    unsigned char OptionBuffer[512];
    unsigned char *optionptr = NULL;
    int optionc = 0;
    unsigned char *(optionnamev[256]);
    unsigned char *(optionargv[256]);

    int keywordfinished;
    int termination;

    unsigned char TextLine[512];
    unsigned char *lineptr;
    unsigned char CurrentScope[128];

    my_argc = 0;
    urlcounter = 0;
    urlptr = URLBuffer;

    /* read file, if filename given and fill buffer */
    if (filename != NULL && buffer == NULL)
    {
        /* if filename starts with http:// or mms://, it is not a filename */
        /* in this case, parse_redirection() returns with result 0 */
        if (strnicmp("http://",  filename, 7) &&
            strnicmp("mms://",   filename, 6) &&
            strnicmp("mmsu://",  filename, 7) &&
            strnicmp("mmst://",  filename, 7)   )
        {
            infile = fopen( filename, "rb" );
            if (infile != NULL)
            {
                fseek(infile, 0, SEEK_END);
                redir_size = ftell(infile);

                fseek(infile, 0, SEEK_SET);
                if ((buffer = malloc(redir_size)) != NULL)
                {
                    fread(buffer, 1, redir_size, infile);
                }
                fclose(infile);
            }
        }
    }

    if (buffer != NULL && redir_size > 0)
    {
        pos = buffer;
        filetype = unknownfile;
        mode = mode_determinefiletype;
        submode = submode_eatwhite;
        keywordptr = Keyword;

        /* the first argument passed to main_function must be the program name */
        my_argv[my_argc++] = urlptr;
        urlptr += (sprintf(urlptr, "ASFRecorder")+1);

        /* explicity specify recording time, if different from 0 */
        if (maxtime != 0)
        {
            my_argv[my_argc++] = urlptr;
            urlptr += (sprintf(urlptr, "-m")+1);
            my_argv[my_argc++] = urlptr;
            urlptr += (sprintf(urlptr, "%d", maxtime)+1);
        }

        /* explicity specify port number, if different from default */
        if (portnum != DEFAULT_PORT)
        {
            my_argv[my_argc++] = urlptr;
            urlptr += (sprintf(urlptr, "-p")+1);
            my_argv[my_argc++] = urlptr;
            urlptr += (sprintf(urlptr, "%d", portnum)+1);
        }

        /* The following code is an XML parser with a very forgiving syntax check   */
        /* It doesn't comply to any "official" XML syntax rules, but it works fine. */

        /* It extracts keywords, options and arguments and can determine opening    */
        /* and closing of the scope of a keyword (<ASX>, </ASX>, <ASX OPTION />)    */
        /* example of syntax: <KEYWORD OPTION1=ARGUMENT OPTION2="ARGUMENT">         */

        /* character loop */
        while ( (!error) && (pos <= (buffer+redir_size)) && (filetype == unknownfile || filetype == xmlfile) )
        {
            if (pos == buffer+redir_size) {
                c = EOF;
                pos++;
            } else
                c = *pos++;

            if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == EOF )
                iswhite = 1;
            else
                iswhite = 0;

            if ((c >= 'a' && c <= 'z') || c >= 'A' && c <= 'Z')
                isalpha = 1;
            else
                isalpha = 0;

            if (submode == submode_eatwhite && iswhite) continue;

            keywordfinished = 0;

            switch(mode)
            {
            case mode_determinefiletype:
                if (c == '<') {
                    /* fall through */
                }
                else {
                    if (c == '[') {
                        /* file is probably an INI file */
                        filetype = inifile;
                    }
                    else {
                        if (isalpha) {
                            /* collect first plaintext keyword */
                            *keywordptr++ = c;
                            submode = submode_none;
                        }
                        else {
                            *keywordptr++ = '\0';
                            /* check if keyword matches "ASF" or any know protocol extension */
                            if (!stricmp(Keyword, "ASF")   ||
                                 stricmp(Keyword, "http")  ||
                                 stricmp(Keyword, "mms")   ||
                                 stricmp(Keyword, "mmst")  ||
                                 stricmp(Keyword, "mmsu") ) {
                                /* file type is probably a plain ASX file */
                                filetype = plainfile;
                            }
                            else {
                                gui_logtext("ASF syntax error 1!\n"); error = 1;
                            }
                        }
                    }
                    break;
                }
                /* fall through */

            case mode_searchforbracket:
                if (c == '<') {
                    termination=0; keywordptr = Keyword; optionptr = OptionBuffer;
                    optionc = 0;
                    mode = mode_expectkeyword; submode = submode_eatwhite;
                }
                break;

            case mode_expectkeyword:
            {
                if (c == '/') {
                    termination = 1;
                    break;
                }
                else {
                    if (isalpha) {
                        mode = mode_readkeyword; submode = submode_none;
                        /* fall through */
                    }
                    else {
                        gui_logtext("ASF syntax error 2!\n"); error = 1;
                        break;
                    }
                }
            }
            /* fall through */

            case mode_readkeyword:
                if (!iswhite) {
                    if (isalpha) {
                        *keywordptr++ = c;
                    }
                    else {
                        if (c == '/') {
                            *keywordptr++ = '\0';
                            termination = 1;
                            mode = mode_expectclosingbrackets; submode = submode_eatwhite;
                        }
                        else {
                            if (c == '>') {
                                *keywordptr++ = '\0';
                                keywordfinished = 1;
                            }
                            else {
                                gui_logtext("ASF syntax error 3!\n"); error = 1;
                            }
                        }
                    }
                }
                else {
                    *keywordptr++ = '\0';
                    mode = mode_expectoption; submode = submode_eatwhite;
                }
                break;

            case mode_expectoption:
                {
                    if (isalpha)
                    {
                        optionnamev[optionc] = optionptr; optionargv[optionc] = NULL;
                        optionc++;
                        mode = mode_readoption; submode = submode_none;
                        /* fall through */
                    }
                    else {
                        if (c == '/') {
                            termination = 1;
                            mode = mode_expectclosingbrackets; submode = submode_eatwhite;
                            break;
                        }
                        else {
                            if (c == '>') {
                                keywordfinished = 1;
                                break;
                            }
                            else {
                                gui_logtext("ASF syntax error 4!\n"); error = 1;
                                break;
                            }
                        }
                    }
                }
                /* fall through */

            case mode_readoption:
                {
                    if (isalpha) {
                        *optionptr++ = c;
                        break;
                    }
                    else {
                        *optionptr++ = '\0';
                         mode = mode_expectargumentoroption; submode = submode_eatwhite;

                         if (iswhite) break;

                         /* fall through */
                    }
                }
                /* fall through */

            case mode_expectargumentoroption:
                {
                    if (c == '/') {
                        termination = 1;
                        mode = mode_expectclosingbrackets; submode = submode_eatwhite;
                    }
                    else {
                        if (c == '>') {
                            keywordfinished = 1;
                        }
                        else {
                            if (c == '=') {
                                optionargv[optionc-1] = optionptr;
                                mode = mode_argumentstart; submode = submode_eatwhite;
                            }
                            else {
                                gui_logtext("ASF syntax error 5!\n"); error = 1;
                            }
                        }
                    }
                }
                break;

            case mode_argumentstart:
                {
                    if (c == '"') {
                        mode = mode_argumentquotes; submode = submode_none;
                        break;
                    }
                    else {
                        if (c == '/') {
                            gui_logtext("ASF syntax error 6!\n"); error = 1;
                            break;
                        }
                        else {
                            mode = mode_argument; submode = submode_eatwhite;
                            if (iswhite) break;
                            /* fall through */
                        }
                    }
                }
                /* fall through */

            case mode_argument:
                {
                    if (c == '"' || c == '=') {
                        gui_logtext("ASF syntax error 7!\n"); error = 1;
                    }
                    else {
                        if (iswhite)
                        {
                            *optionptr++ = '\0';
                            mode = mode_expectoption; submode = submode_eatwhite;
                        }
                        else {
                            if (c == '/') {
                                *optionptr++ = '\0';
                                termination = 1;
                                mode = mode_expectclosingbrackets; submode = submode_eatwhite;
                            }
                            else {
                                if (c == '>') {
                                    *optionptr++ = '\0';
                                    keywordfinished = 1;
                                }
                                else {
                                    *optionptr++ = c;
                                    submode = submode_none;
                                }
                            }
                        }
                    }
                }
                break;

            case mode_argumentquotes:
                {
                    if (c != '"') {
                        *optionptr++ = c;
                    }
                    else {
                        *optionptr++ = '\0';

                        mode = mode_expectoption; submode = submode_eatwhite;
                    }
                }
                break;

            case mode_expectclosingbrackets:
                {
                    if (c == '>') {
                        keywordfinished = 1;
                    }
                    else {
                        gui_logtext("ASF syntax error 8!\n"); error = 1;
                    }
                }
                break;
            }

            if (keywordfinished)
            {
                /* begin to search for next keyword starting with a "<" */
                mode = mode_searchforbracket; submode = submode_eatwhite;

#if 0 /* just for debugging */
                int i;

                if (termination)
                    gui_logtext("Keyword: /%s\n", Keyword);
                else
                    gui_logtext("Keyword %s\n", Keyword);
                for (i=0; i<optionc; i++)
                {
                    if (optionargv[i] == NULL)
                        gui_logtext("option #%d %s\n", i+1, optionnamev[i]);
                    else
                        gui_logtext("option #%d %s = %s\n", i+1, optionnamev[i], optionargv[i]);
                }
#endif

                if (!stricmp(Keyword, "ASX"))
                {
                    /* signal the calling main_function that we parsed this ASX file */
                    result = 1;
                }

                if (!stricmp(Keyword, "Entry") && (!termination))
                {
                    /* set a marker for every new entry */

                    /* this is because one entry can have multiple references */
                    /* pointing to the same stream on different servers       */
                    /* (or lower-bitrate streams) for redundancy              */

                    /* this marker allows us to download only one stream of   */
                    /* these multiple references                              */

                    my_argv[my_argc++] = urlptr;
                    urlptr += (sprintf(urlptr, "-e")+1);
                }

                if ((!stricmp(Keyword, "Ref")) || (!stricmp(Keyword, "EntryRef")))
                {
                    if (optionc > 0)
                    {
                        if ( (!stricmp("href", optionnamev[0])) && (optionargv[0] != NULL) )
                        {
                            /* store this URL for later download */
                            my_argv[my_argc++] = urlptr;
                            urlptr += (sprintf(urlptr, "%s", optionargv[0])+1);
                            urlcounter++;
                        }
                    }
                }
            }

            if (error)
            {
                /* try to recover after an error */
                mode = mode_searchforbracket; submode = submode_eatwhite;
                error = 0;
            }
        }

        if (filetype == inifile)
        {
            /* signal the calling main_function that we parsed this INI file */
            result = 1;

            pos = buffer;
            lineptr = TextLine;
            strcpy(CurrentScope, "");

            /* character loop */
            while ( (!error) && ( pos <= (buffer+redir_size) ) )
            {
                int linecomplete = 0;

                if (pos == buffer+redir_size) {
                    c = EOF;
                    pos++;
                }   else
                    c = *pos++;


                if ((c != '\r') && (c != '\n') && (c != EOF))
                    *lineptr++ = c;
                else
                    *lineptr++ = 0;

                if (c == '\n' || c == EOF)
                {
                    lineptr = TextLine;
                    linecomplete = 1;
                }

                if (linecomplete)
                {
                    if (TextLine[0] == '[')
                    {
                        strcpy(CurrentScope, TextLine);

                        if (!stricmp(CurrentScope, "[Reference]"))
                        {
                            /* set new entry marker (-e option) */
                            my_argv[my_argc++] = urlptr;
                            urlptr += (sprintf(urlptr, "-e")+1);
                            /* all following URLs belong to this single entry */
                        }
                    }
                    else
                    {
                        if (!stricmp(CurrentScope, "[Reference]"))
                        {
                            /* URLs begin with with REFxx= where xx is any number */
                            if (!strnicmp(TextLine, "REF", 3))
                            {
                                unsigned char *ptr = TextLine+3;
                                /* skip numbers */
                                while ((*ptr) >= '0' && (*ptr) <= '9') ptr++;
                                if ((*ptr) == '=')
                                {
                                    ptr++;

                                    /* save the resulting URL string */
                                    my_argv[my_argc++] = urlptr;
                                    urlptr += (sprintf(urlptr, "%s",ptr)+1);
                                    urlcounter++;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (filetype == plainfile)
        {
            /* signal the calling main_function that we parsed this INI file */
            result = 1;

            pos = buffer;
            lineptr = TextLine;

            /* set new entry marker (-e option) */
            my_argv[my_argc++] = urlptr;
            urlptr += (sprintf(urlptr, "-e")+1);
            /* all following URLs belong to this single entry */

            /* character loop */
            while ( (!error) && ( pos <= (buffer+redir_size) ) )
            {
                int linecomplete = 0;

                if (pos == buffer+redir_size) {
                    c = EOF;
                    pos++;
                } else
                    c = *pos++;

                if ((c != '\r') && (c != '\n') && (c != EOF))
                    *lineptr++ = c;
                else
                    *lineptr++ = 0;

                if (c == '\n' || c == EOF)
                {
                    lineptr = TextLine;
                    linecomplete = 1;
                }

                if (linecomplete)
                {
                    unsigned char *ptr = TextLine;

                    /* eat whitespaces */
                    while( (*ptr == ' ') || (*ptr == '\t') ) ptr++;

                    /* don't know if multiple lines are allowed in this */
                    /* plain ASX file format but who cares */
                    if ((!strnicmp(ptr, "ASF ",  4)) ||
                        (!strnicmp(ptr, "ASF\t", 4))   )
                    {
                        ptr += 4;

                        /* eat whitespaces */
                        while( (*ptr == ' ') || (*ptr == '\t') ) ptr++;

                        /* save the resulting URL string */
                        my_argv[my_argc++] = urlptr;
                        urlptr += (sprintf(urlptr, "%s",ptr)+1);
                        urlcounter++;
                    }
                    else
                    {
                        /* some providers use ASX files that contain the URL only */
                        if ((!strnicmp(ptr, "http://",  7)) ||
                            (!strnicmp(ptr, "mms://",   6)) ||
                            (!strnicmp(ptr, "mmsu://",  7)) ||
                            (!strnicmp(ptr, "mmst://",  7)) )
                        {
                            /* save the resulting URL string */
                            my_argv[my_argc++] = urlptr;
                            urlptr += (sprintf(urlptr, "%s",ptr)+1);
                            urlcounter++;
                        }
                    }
                }
            }
        }

#if 0 /* just for debugging */
        if (my_argc > 1)
        {
            int url;

            gui_logtext("List of arguments for main_function()\n");

            for (url = 0; url < my_argc; url++)
            {
                gui_criticalerror("arg #%d: %s\n", url, my_argv[url]);
            }
        }
#endif
        /* recursively call main_function() with the extracted URLs */
        if (urlcounter > 0)
            main_function(my_argc, (char**)my_argv);
    }

    return result;
}


typedef enum 
{
    ShowUsage,
    NoArguments,
    BadOption,
} UsageMode;

/* Program usage information */

void Usage(char *progname, UsageMode mode)
{
    char Buffer[1024];

    char *bufptr;
    char *nameptr, *tmpptr;

    if (mode == NoArguments) {
        if (gui_startedfromdesktop()) {
            return;
        }
    }

    for (nameptr = progname, tmpptr = progname; (tmpptr = strchr(tmpptr, '\\')) != NULL ; nameptr = ++tmpptr);
    
    bufptr = Buffer;
    
    if (mode != BadOption)
    {
        if (gui_startedfromdesktop())
            bufptr+=sprintf(bufptr,"\nPROGRAM ARGUMENTS INFORMATION:\n\n");
        else
            bufptr+=sprintf(bufptr,"\nPROGRAM USAGE FROM CONSOLE:\n\n");

        bufptr+=sprintf(bufptr,"%s [-a <user:passwd>] [-p <port>] [-P <proxy:port>]\n", nameptr);
        bufptr+=sprintf(bufptr,"[-m <minutes>] [-e] <one or more stream references> [-b] [-r] [-d]\n");
        bufptr+=sprintf(bufptr,"\nDownload and store Windows Media Player .ASF streams!\n\n");
        bufptr+=sprintf(bufptr,"<stream references> must point to mms:// or http:// streams\n");
        bufptr+=sprintf(bufptr,"or to an .asx redirection URL/file referencing such a stream.\n");
        bufptr+=sprintf(bufptr,"Partial downloads will be resumed.\n");
        bufptr+=sprintf(bufptr,"\nOnly HTTP streaming is supported (no UDP or TCP).\n\n");
    }
    if (mode == BadOption)
    {
        bufptr+=sprintf(bufptr,"\nYOU SPECIFIED AN INVALID OPTION!:\n\n");
        bufptr+=sprintf(bufptr,"List of options: [-a <username:password>] [-p <portnum>] [-m <minutes>] [-e] [-b] [-r] [-d]\n\n");
    }
    bufptr+=sprintf(bufptr,"-a authorization with username and password\n");
    bufptr+=sprintf(bufptr,"-p specifies the port number to connect to\n");
    bufptr+=sprintf(bufptr,"-P specifies a proxy (e.g. http://proxy:8080)\n");
    bufptr+=sprintf(bufptr,"-r enables generation of a raw streaming file.\n");
    bufptr+=sprintf(bufptr,"-d dumps HTTP headers (for your information).\n");
    bufptr+=sprintf(bufptr,"-b enables batch mode (non-blocking GUI operation)\n");
    bufptr+=sprintf(bufptr,"-m specifies max. recording time in minutes.\n");
    bufptr+=sprintf(bufptr,"-e downloads only the first stream available\n");
    bufptr+=sprintf(bufptr,"   from the following list of references.\n\n");
    
    if (mode != BadOption)
    {
        if (!gui_startedfromdesktop())
            bufptr+=sprintf(bufptr,"Hit Ctrl-C to terminate the download.\n\n");
    }
    gui_showtext(Buffer);
}


/* A simple main() code that works for both console and GUI application */

int main(int argc, char **argv)
{
#ifdef WIN32
    WSADATA wsaData;
#endif

    if (gui_initialize())
    {

#ifdef WIN32

#define WS_MAJOR 2
#define WS_MINOR 0

        /* Open Winsock */
        if (WSAStartup(((WS_MINOR<<8)+WS_MAJOR),&wsaData) != 0)
        {
            gui_criticalerror("WSAStartup failed: %s\n",gui_translate_errorcode(errno));
            WSACleanup();
            gui_uninitialize();
            return -1;
        }
        else
        {
            /* Confirm that the WinSock DLL supports 2.2.*/
            /* Note that if the DLL supports versions greater    */
            /* than 2.2 in addition to 2.2, it will still return */
            /* 2.2 in wVersion since that is the version we      */
            /* requested.                                        */
            
            if ( (LOBYTE( wsaData.wVersion ) <  WS_MAJOR ) || 
                ((LOBYTE( wsaData.wVersion ) == WS_MAJOR ) && (HIBYTE( wsaData.wVersion ) < WS_MINOR )) )
            {
                /* Tell the user that we could not find a usable */
                /* WinSock DLL.                                  */
                gui_criticalerror("Your WinSock version is too old!\n"
                                  "Required is version %d.%d\n"
                                  "Your DLL is version %d.%d\n",
                                  WS_MAJOR, WS_MINOR,
                                  (int)LOBYTE( wsaData.wVersion ),
                                  (int)HIBYTE( wsaData.wVersion ));
                WSACleanup( );
                gui_uninitialize();
                return -1;
            }
        }
#endif 
        main_function(argc, argv);

        gui_waitforuseraction();    /* gui_waitforuseraction may call main_function again */

#ifdef WIN32
        WSACleanup();
#endif
    }

    gui_uninitialize();

    return 0;
}


/* Parameter and URL parsing, HTTP request generation, opening output files */

int main_function(int argc, char **argv)
{
    /* these static flags/pointers are supposed to remain set */
    /* (even for multiple invocations of the main_function)   */
    static int createrawfile = 0;
    static int dumpheaders   = 0;
    static int batchmode     = 0;

    static char *username = NULL;
    static char *password = NULL;
    static char *proxy = NULL;

    unsigned char Buffer[MAX_CHUNK_SIZE];
    int i;
    unsigned int addr;
    struct hostent *hp = NULL;

    char *bufptr;
    char *urlptr;
    char *dashptr;
    char *colonptr;

    unsigned char *(URL[MAXURLS]);
    unsigned short portnum;
    unsigned short portnum_url[MAXURLS];
    unsigned short portnum_proxy;
    unsigned int maxtime;
    unsigned int maxtime_url[MAXURLS];
    int entry;
    int entry_url[MAXURLS];
    int urlc;
    int url;

    unsigned char file[512];
    unsigned char full_path[512];
    unsigned char server_name[512];

    char *tmpptr;
    char *fileptr;
    char *dotptr;

    unsigned char filename[512];

    unsigned char rawfilename[512];
    FILE *outfile, *rawfile;
    int oldsize;

    unsigned int offset_hi; /* the start position in the ASF file */
    unsigned int offset_lo; /* (64 bit large integer) */

    struct HeaderInfo hdrinfo;

    /* tell the GUI that this process is working */
    gui_not_idle(1);

    /* clear arrays & local structures */
    memset(&hdrinfo, 0, sizeof(hdrinfo));
    memset(URL, 0, sizeof(URL));

    /* Setup CTRL-C handler */
    signal(SIGINT, &ctrlc);

    /* set some defaults */
    urlc = 0;
    strcpy(file, "");
    strcpy(server_name, "");
    portnum = DEFAULT_PORT;
    abortflag = 0;
    maxtime = 0;
    entry = -1;

    /* Argument parsing */
    if (argc > 1)
    {
        int err = 0;

        for( i=1 ; (!err) && (i < argc) ; i++)
        {
#ifdef WIN32
            if ( (argv[i][0] == '-') || (argv[i][0] == '/') )
#else
            if ( (argv[i][0] == '-') )
#endif
            {
                switch(argv[i][1])
                {
                case 'a':
                    if (argc > i+1)
                    {
                        colonptr = strchr(argv[++i],':');
                        if (colonptr == NULL) {
                            gui_seterror("Invalid syntax for username:password! Forgot colon?\n"); err=1;}
                        else
                        {
                            *colonptr = 0;
                            username = argv[i];
                            password = colonptr+1;
                        }
                    }
                    else {
                        gui_seterror("insufficient args\n"); err=1;}
                    break;
                case 'p':
                    if (argc > i+1)
                        portnum = atoi(argv[++i]);
                    else {
                        gui_seterror("insufficient args\n"); err=1;}
                    break;
                case 'P':
                    if (argc > i+1)
                        proxy = argv[++i];
                    else {
                        gui_seterror("insufficient args\n"); err=1;}
                    break;
                case 'r':
                    createrawfile = 1;
                    break;
                case 'd':
                    dumpheaders = 1;
                    break;
                case 'm':
                    if (argc > i+1)
                        maxtime = atoi(argv[++i]);
                    else {
                        gui_seterror("insufficient args\n"); err=1;}
                    break;
                case 'b':
                    batchmode = 1;
                    break;
                case 'e':
                    entry++;
                    break;
                case '?':
                    Usage(argv[0], ShowUsage);
                    gui_not_idle(0);
                    return 0;
                    break;
                default:
                    Usage(argv[0], BadOption);
                    gui_not_idle(0);
                    return 0;
                    break;
                }
            }
            else
            {
                if (urlc < MAXURLS-1)
                {
                    (URL[urlc]) = argv[i];
                    portnum_url[urlc] = portnum;
                    maxtime_url[urlc] = maxtime;
                    entry_url[urlc] = entry;
                    urlc++;
                }
            }
        }
        if (err)
        {
            gui_not_idle(0);
            return 0;
        }
    }


    /* Print program usage */
    if (urlc == 0)
    {
        Usage(argv[0], NoArguments);
        gui_not_idle(0);
        return 0;
    }

    gui_getproxy(&proxy);
    if (proxy != NULL) if (!strcmp(proxy, "")) proxy = NULL;

    gui_setbatchmode(batchmode);

    /* Loop thorugh all specified <stream references> */
    for (url = 0; ( ((!abortflag) || batchmode) && (url < urlc)) ; url++)
    {
        /* try to interpret the stream reference as an on-disk redirection file first.    */
        /* subroutine will return TRUE if this was successful. We need to pass on maxtime */
        /* and portnum specifications because these can be different for any URL given    */
        if ( !parse_redirection( URL[url], NULL, 0, maxtime_url[url], portnum_url[url] ) )
        {
            unsigned char escaped_url[512];

            /* else try to parse string as an URL stream reference */
            /* Extract server name and path to stream */
            gui_setstatus("Parsing URL: '%s'\n", URL[url]);

            /* replace unescaped characters (e.g. spaces) by escape sequences */
            escape_url_string(escaped_url, URL[url]);

            urlptr = escaped_url;
            if (!strnicmp("http://", urlptr, 7)) urlptr+=7;
            if (!strnicmp("mms://",  urlptr, 6)) urlptr+=6;
            if (!strnicmp("mmsu://", urlptr, 7)) urlptr+=7;
            if (!strnicmp("mmst://", urlptr, 7)) urlptr+=7;
            dashptr = strchr(urlptr, '/');
            if (dashptr == NULL)
            {
                dashptr = urlptr+strlen(urlptr);
                gui_criticalerror("Invalid URL format!\n");
            }
            else
            {
                strncpy(server_name, urlptr, dashptr-urlptr);
                server_name[dashptr-urlptr] = 0;
                strcpy(file, dashptr);

                colonptr = strchr(server_name, ':');
                if (colonptr != NULL)
                {
                    portnum_url[url] = (unsigned short)atol(colonptr+1);
                    *colonptr = '\0';
                    if (portnum_url[url] == 0)
                    {
                        gui_criticalerror("Invalid URL format!\n");
                        strcpy(server_name, "");
                        strcpy(file, "");
                    }
                }
            }

            /* parse proxy URL */
            if (proxy != NULL)
            {
                if (portnum_url[url] == DEFAULT_PORT)
                    sprintf(full_path, "http://%s%s", server_name, file);
                else
                    sprintf(full_path, "http://%s:%d%s", server_name, portnum_url[url], file);
                urlptr = proxy;
                if (!strnicmp("http://", urlptr, 7)) urlptr+=7;

                dashptr = strchr(urlptr, '/');
                if (dashptr != NULL)
                {
                    gui_criticalerror("Invalid proxy URL format!\n");
                }
                else
                {
                    colonptr = strchr(urlptr, ':');
                    if (colonptr != NULL)
                    {
                        portnum_proxy = (unsigned short)atol(colonptr+1);
                        if (portnum_proxy == 0)
                        {
                            gui_criticalerror("Invalid proxy URL format!\n");
                            strcpy(server_name, "");
                            strcpy(file, "");
                        }
                        else
                        {
                            portnum_url[url] = portnum_proxy;
                        }
                    }
                    else
                        colonptr = urlptr+strlen(urlptr);

                    strncpy(server_name, urlptr, colonptr-urlptr);
                    server_name[colonptr-urlptr] = 0;
                }
            }

            if (strcmp(server_name,""))
            {
                /* Attempt to detect if we should call gethostbyname() or gethostbyaddr() */
                gui_setstatus("Resolving host: '%s'\n", server_name);

                addr = 0;

                if (isalpha(server_name[0]))
                {
                    /* Server address is a name */
                    hp = gethostbyname(server_name);
                    if (hp == NULL)
                    {
                        gui_seterror("Unable to resolve host '%s'!\n", server_name);
                    }
                }
                else
                {
                    /* Convert nnn.nnn address to a usable one */
                    addr = inet_addr(server_name);
                    if ((hp = gethostbyaddr((char *)&addr,4,AF_INET))!=NULL)
                    {
                        strcpy(server_name, hp->h_name);
                    }
                }

                if ( ((!abortflag) || batchmode) && (hp != NULL || addr != 0) )
                {
                    unsigned char randomized_guid[80];
                    char passwordcombo[512];
                    char base64buf[1000];

                    randomize_guid(randomized_guid);

                    strcpy(filename, "");

                    /* loop until we got a valid password */
                    while (!abortflag)
                    {
                        gui_start_transmission(URL[url], filename, sizeof(filename), 0, 0);
                        
                        /* cook up first HTTP request to send */
                        
                        /* This is the initial HTTP request of media player.
                        It is used to query for the media type header of
                        the stream (needed for checking if the codecs are
                        installed at the client and for obtaining the type
                        of stream (live stream, pre-recorded content etc..)
                        
                        Note that the request-context changes with every
                        new HTTP request. */
                        
                        bufptr = Buffer;
                        bufptr+=sprintf(bufptr,"GET %s HTTP/1.0\r\n", proxy == NULL ? file:full_path);
                        if (username != NULL || password != NULL)
                        {
                            sprintf(passwordcombo, "%s:%s", username!=NULL?username:"", password!=NULL?password:"");
                            base64enc(passwordcombo,base64buf);
                            bufptr += sprintf(bufptr,"Authorization: Basic %s\r\n",base64buf);
                        }
                        bufptr+=sprintf(bufptr,"Accept: */*\r\n");
                        bufptr+=sprintf(bufptr,"User-Agent: NSPlayer/4.1.0.3856\r\n");
                        if (proxy == NULL) bufptr+=sprintf(bufptr,"Host: %s\r\n", server_name);
                        bufptr+=sprintf(bufptr,"Pragma: no-cache,rate=1.000000,stream-time=0,stream-offset=0:0,request-context=1,max-duration=0\r\n");
                        bufptr+=sprintf(bufptr,"Pragma: xClientGUID=%s\r\n", randomized_guid);
                        bufptr+=sprintf(bufptr,"Connection: Close\r\n\r\n");
                        
                        /* Call the subroutine that does all the work */
                        
                        abortflag = 0;  /* reset global abort flag */
                        
                        collectdata(1, dumpheaders,
                            NULL,                       /* file for raw output or NULL */
                            NULL,                       /* output file (NULL, header only!) */
                            0,                          /* previous size of output file */
                            Buffer,                     /* adress of data buffer */
                            sizeof(Buffer),             /* size of data buffer */
                            ((int)bufptr-(int)Buffer),  /* size of HTTP request */
                            hp,                         /* hostent structure or NULL */
                            server_name,                /* server name string */
                            addr,                       /* IP address in network byte order */
                            portnum_url[url],           /* port number (80 in most cases) */
                            SOCK_STREAM,                /* type of socket (SOCK_STREAM) */
                            file,                       /* path to ASF stream on server */
                            &hdrinfo,                   /* adress of hdr info structure */
                            maxtime_url[url]);          /* maximum time for recording */
                        
                        gui_finished_transmission();

                        if (hdrinfo.contenttype != password_required)
                        {
                            /* leave loop if anything else than "401 - unauthorized" returned */
                            break;
                        }
                        else
                        {
                            if (batchmode && (username != NULL || password != NULL))
                            {
                                gui_seterror("Authorization failed!\n");
                                break;
                            }
                            if (!gui_getpassword(&username, &password))
                            {
                                gui_seterror("Authorization cancelled!\n");
                                break;
                            }
                        }
                    }

                    if (!abortflag)
                    {

                        if ( hdrinfo.contenttype == redirector_content )
                        {
                            /* redirection file now resides in Buffer, so call the parser */
                            /* the parser itself will call the main_function recursively */
                            parse_redirection(NULL, Buffer, hdrinfo.redirsize, maxtime_url[url], portnum_url[url] );
                        }

                        if ((hdrinfo.contenttype == prerecorded_content || hdrinfo.contenttype == live_content) )
                        {
                            /* Cut away leading sub directories from the URL and extract the file name */
                            for (fileptr = file, tmpptr = file; (tmpptr = strchr(tmpptr, '/')) != NULL ; fileptr = ++tmpptr);

                            /* replace escape characters in filename */
                            unescape_url_string(filename, fileptr);

                            /* remove any disallowed characters (OS-specific!) */
                            generate_valid_filename(filename);

                            /* the GUI is allowed to modify the filename (target file selection) */
                            /* GUI can also cancel the download at this point */
                            if (!gui_start_transmission(URL[url], filename, sizeof(filename), hdrinfo.time, (maxtime*60*1000)))
                            {
                                gui_seterror("transfer cancelled.\n");
                            }
                            else
                            {
                                /* Open output ASF file */
                                gui_logtext("Opening file '%s' for output\n", filename);

                                /* open either an existing or a new output file */

                                /* try to open existing file for binary reading and writing */
                                /* (but not for live content) */
                                outfile = NULL;
                                if (hdrinfo.contenttype != live_content)
                                    outfile = fopen(filename, "rb+");

                                /* second option: create a new file for binary writing */
                                if (outfile == NULL)
                                    outfile = fopen(filename, "wb");

                                if (outfile == NULL)
                                {
                                    gui_seterror("Failed to open '%s'.\n", filename);
                                }
                                else
                                {
                                    /* If desired, open raw file. It will contain */
                                    /* the raw streaming data for further analysis */

                                    /* This file cannot be played in Media Player */

                                    /* Note the raw file will contain the HTTP reply */
                                    /* and additional chunk headers */

                                    if (createrawfile)
                                    {
                                        for (dotptr = fileptr+strlen(fileptr), tmpptr = fileptr; (tmpptr = strchr(tmpptr, '.')) != NULL ; dotptr = tmpptr++);
                                        strncpy(rawfilename, fileptr, (dotptr-fileptr));
                                        rawfilename[(dotptr-fileptr)] = 0;
                                        strcat(rawfilename, "_raw");
                                        strcat(rawfilename, dotptr);

                                        gui_logtext("Opening raw file '%s' for output\n", rawfilename);
                                        rawfile = fopen(rawfilename, "ab");
                                        if (rawfile == NULL)
                                        {
                                            gui_seterror("Failed to open %s'.\n", rawfilename);
                                        }
                                        else
                                            fseek(rawfile, 0, SEEK_END);
                                    } else rawfile = NULL;

                                    /* Appending is not possible for live content! */
                                    oldsize = 0;
                                    if (hdrinfo.contenttype != live_content)
                                    {
                                        /* Determine file size of existing .ASF file */
                                        fseek(outfile, 0, SEEK_END);
                                        oldsize = ftell(outfile);
                                    }

                                    /* Check if this download requires a resume */
                                    if (oldsize > 0)
                                    {
                                        /* Enable resuming the download */
                                        /* ANSI-C does not support file operations >4GB */
                                        /* but who wants to stream 4 GIG files anyway? */
                                        gui_logtext("Appending to existing file!\n");
                                        offset_hi = 0;
                                        offset_lo = oldsize;
                                    }
                                    else
                                    {
                                        /* Otherwise tell the server to send from the beginning */
                                        offset_hi = 0xffffffff;
                                        offset_lo = 0xffffffff;
                                    }

                                    /* cook up second HTTP request to send */

                                    if (hdrinfo.contenttype == prerecorded_content)
                                    {
                                    /* This is the HTTP request that enables downloading
                                    prerecorded (=seekable) content.

                                      The stream-offset parameter defines the start offset
                                      in the ASF file on the server,

                                        The stream-time is the timecode (milliseconds) for
                                        seeking within the stream. This parameter is not used
                                        by this program. */

                                        bufptr = Buffer;
                                        bufptr+=sprintf(bufptr,"GET %s HTTP/1.0\r\n", proxy == NULL ? file:full_path);
                                        if (username != NULL || password != NULL)
                                            bufptr += sprintf(bufptr,"Authorization: Basic %s\r\n",base64buf);
                                        bufptr+=sprintf(bufptr,"Accept: */*\r\n");
                                        bufptr+=sprintf(bufptr,"User-Agent: NSPlayer/4.1.0.3856\r\n");
                                        if (proxy == NULL) bufptr+=sprintf(bufptr,"Host: %s\r\n", server_name);
                                        bufptr+=sprintf(bufptr,"Pragma: no-cache,rate=1.000000,stream-time=0,stream-offset=%u:%u,request-context=2,max-duration=%u\r\n",offset_hi, offset_lo, hdrinfo.time);
                                        bufptr+=sprintf(bufptr,"Pragma: xPlayStrm=1\r\n");
                                        bufptr+=sprintf(bufptr,"Pragma: xClientGUID=%s\r\n", randomized_guid);
                                        bufptr+=sprintf(bufptr,"Pragma: stream-switch-count=1\r\n");
                                        bufptr+=sprintf(bufptr,"Pragma: stream-switch-entry=ffff:1:0\r\n");
                                        bufptr+=sprintf(bufptr,"Connection: Close\r\n\r\n");
                                    }

                                    if (hdrinfo.contenttype == live_content)
                                    {
                                    /* This is the HTTP request that enables downloading
                                    live (=broadcast) content.

                                        The offset-stuff is not used here. */

                                        bufptr = Buffer;
                                        bufptr+=sprintf(bufptr,"GET %s HTTP/1.0\r\n", proxy == NULL ? file:full_path);
                                        if (username != NULL || password != NULL)
                                            bufptr += sprintf(bufptr,"Authorization: Basic %s\r\n",base64buf);
                                        bufptr+=sprintf(bufptr,"Accept: */*\r\n");
                                        bufptr+=sprintf(bufptr,"User-Agent: NSPlayer/4.1.0.3856\r\n");
                                        if (proxy == NULL) bufptr+=sprintf(bufptr,"Host: %s\r\n", server_name);
                                        bufptr+=sprintf(bufptr,"Pragma: no-cache,rate=1.000000,request-context=2\r\n",offset_hi, offset_lo);
                                        bufptr+=sprintf(bufptr,"Pragma: xPlayStrm=1\r\n");
                                        bufptr+=sprintf(bufptr,"Pragma: xClientGUID=%s\r\n", randomized_guid);
                                        bufptr+=sprintf(bufptr,"Pragma: stream-switch-count=1\r\n");
                                        bufptr+=sprintf(bufptr,"Pragma: stream-switch-entry=ffff:1:0\r\n");
                                        bufptr+=sprintf(bufptr,"Connection: Close\r\n\r\n");
                                    }

                                    /* Call the subroutine that does all the work */

                                    abortflag = 0;  /* reset global abort flag */

                                    collectdata(0, dumpheaders,
                                        rawfile,                    /* file for raw output or NULL */
                                        outfile,                    /* output file */
                                        oldsize,                    /* previous size of output file */
                                        Buffer,                     /* adress of data buffer */
                                        sizeof(Buffer),             /* size of data buffer */
                                        ((int)bufptr-(int)Buffer),  /* size of HTTP request */
                                        hp,                         /* hostent structure or NULL */
                                        server_name,                /* server name string */
                                        addr,                       /* IP address in network byte order */
                                        portnum_url[url],           /* port number (80 in most cases) */
                                        SOCK_STREAM,                /* type of socket (SOCK_STREAM) */
                                        file,                       /* path to ASF stream on server */
                                        &hdrinfo,                   /* adress of hdr info structure */
                                        maxtime_url[url]);          /* maximum time for recording */

                                    /* TODO: */

                                    /* Tranmission is not yet checked for success!          */
                                    /* For prerecorded content, a transfer interrupted by   */
                                    /* technical problems should be automatically retried   */
                                    /* (at least when in batch mode)                        */
                                    /* Resuming of live content could be implemented rather */
                                    /* easily now                                           */

                                    /* now handle the -e option */
                                    /* useful when several alternative URL references point */
                                    /* to the same content. This method is often used by    */
                                    /* content providers to allow server reduncandy.        */
                                    if (entry_url[url] != -1)
                                    {
                                        int entry = entry_url[url];
                                        for (;;)
                                        {
                                            /* skip following URLs with same entry number */
                                            if ((url+1) < urlc)
                                            {
                                                if (entry_url[url+1] == entry) url++;
                                                else break;
                                            }
                                            else break;
                                            /* the outer for (;;) loop will add 1 more to url */
                                        }
                                    }

                                    /* Close files, cleanup and exit */
                                    if (rawfile != NULL)
                                    {
                                        fclose(rawfile); rawfile = NULL;
                                    }
                                    fclose(outfile);
                                }
                                gui_finished_transmission();
                            }
                        }
                    }
                }
            }
        }
    }
    /* tell the GUI that this process is no longer working */
    gui_not_idle(0);
    return 0;
}
