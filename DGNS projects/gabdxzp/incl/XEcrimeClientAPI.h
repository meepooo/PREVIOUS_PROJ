#ifndef _XECRIME_CLIENT_API_H__
#define _XECRIME_CLIENT_API_H__

#ifndef WIN32
#define _stdcall
#endif

#define HASTR  "ChinaFinancialCertificationAuthority_"

#define CFCA_ERROR                  -1
#define CFCA_OK                      0

typedef struct  
{
    char szServerIP[16];
    int  nPort;
}SERVER;

#define MAX_TEST_XML_LINE_LEN   4096
#define MAX_DATA_LEN            1024
#define MAX_SERVICE_ID          128

typedef struct _TEST_DATA
{
    char szRequest[MAX_TEST_XML_LINE_LEN];
    unsigned char bySrcData[MAX_DATA_LEN];
    int           nSrcDataSize;

    SERVER stServerAarry[2];
    int    nCountServer;

} TEST_DATA, *PTEST_DATA;

extern TEST_DATA g_stTestData;

#ifdef __cplusplus
extern "C" {
#endif 

// WARNING: CFCA_Initialize() / CFCA_Uninitialize() can only be invoked once in a process.
//          Invoke CFCA_Initialize() before creat child-threads.
int _stdcall CFCA_Initialize( SERVER* pServerArray,
                              int     nServerCount,
                              char*   pszLogConfigFilePath );

int _stdcall CFCA_Uninitialize( );

int _stdcall CFCA_Connect( void** ppSession );

int _stdcall CFCA_Disconnect( void** ppSession );

int _stdcall SendandReceiveMsg ( void*  pSession,
                                 char*  pszRequest,
                                 char** ppszResponse );

int _stdcall SM3HashData( unsigned char*  pbySrcData,
                          int             nSrcDataSize,
                          bool            bWithZValue,
                          char*           pszBase64Cert,
                          char**          ppszHash );

void _stdcall FreeMemory( void* pBuf );

#ifdef __cplusplus
}
#endif


#endif // _XECRIME_CLIENT_API_H__
