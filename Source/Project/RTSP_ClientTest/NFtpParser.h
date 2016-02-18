#include "parser.h"
#include "NFTPFrameDef.h"

#define NFTP_PKT_MAX_SIZE 32*1024

void InitNFtpParser();
void ProcessNFtpData(unsigned char *buf,int len);

