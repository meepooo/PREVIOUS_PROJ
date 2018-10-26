#include "../incl/ICPS_JB_HEAD.h"

void chomp_CRLF(char *str)
{
    int iLen;
    trim(str);
    iLen = strlen(str);
    if (str[iLen - 1] == '\n' || str[iLen - 1] == '\r')
        str[iLen - 1] = '\0';
    if (str[iLen - 2] == '\n' || str[iLen - 2] == '\r')
        str[iLen - 2] = '\0';
}

void transform_date_time(char* sFrom, char* sTo)
{
    char sBuf[20];
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%c%c%c%c%c%c%c%c%c%c%c%c%c%c", sFrom[0], sFrom[1], sFrom[2], sFrom[3], sFrom[5], sFrom[6],
            sFrom[8], sFrom[9], sFrom[11], sFrom[12], sFrom[14], sFrom[15], sFrom[17], sFrom[18]);
    pstrcopy(sTo, sBuf, 15);
}

void transform_date(char* sFrom, char* sTo)
{
    char sBuf[20];
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%c%c%c%c%c%c%c%c", sFrom[0], sFrom[1], sFrom[2], sFrom[3], sFrom[5], sFrom[6], sFrom[8],
            sFrom[9]);
    pstrcopy(sTo, sBuf, 9);
}

char* date_getNow()
{
    struct timeb tp;
    struct tm *tm;
    static char sTime_Stamp[64];

    ftime(&tp);
    tm = localtime(&tp.time);
    memset(sTime_Stamp, 0x00, sizeof(sTime_Stamp));
    snprintf(sTime_Stamp, sizeof(sTime_Stamp), "%4d%02d%02d%02d%02d%02d%.3d",
            1900+ tm->tm_year,
            1 + tm->tm_mon,
            tm->tm_mday,
            tm->tm_hour,
            tm->tm_min,
            tm->tm_sec,
            tp.millitm
            );
    return sTime_Stamp;
}

int code_convert(char *src, char *dest, char *input, size_t ilen, char *output, size_t olen)
{
    char *pin = input;
    char *pout = output;

    iconv_t cd = iconv_open(dest, src);

    if ((iconv_t) -1 == cd)
    {
        return -1;
    }

    if (iconv(cd, &pin, &ilen, &pout, &olen))
    {
        LOG(LM_STD, Fmtmsg("----------------->[%s]",strerror(errno)), "Convert");
        iconv_close(cd);
        return -2;
    }
    iconv_close(cd);
    return 0;
}

void Execle_Shell(char* script, char* para1, char* para2, char* para3)
{
    char sCmd[200];
	int iRet;

    memset(sCmd, 0x00, sizeof(sCmd));
    snprintf(sCmd, sizeof(sCmd), "sh %s/tools/icps/%s %s %s %s", getenv("HOME"), script, para1, para2, para3);
    LOG(LM_DEBUG, Fmtmsg("命令[%s]", sCmd), "DEBUG");
    iRet=system(sCmd);
	LOG(LM_DEBUG, Fmtmsg("脚本执行状态[%d]", iRet), "DEBUG");
}

int getsubstr(char** src, char* split, char* substr, int size)
{
    char *p = NULL;
    int iLenSplit = strlen(split);
    int i;


    if (NULL == *src)
    {
        return -1;
    }
    if (iLenSplit <= 0)
    {
        return -1;
    }

    p = strstr(*src, split);
    if (NULL == p)
    {
        pstrcopy(substr, *src, size);
        *src = *src + strlen(src);
    }
    else
    {
        for (i = 0; i < iLenSplit; i++)
        {
            p[0 + i] = '\0';
        }
        pstrcopy(substr, *src, size);
        *src = *src + strlen(*src) + iLenSplit;
    }

    return strlen(substr);
}

int fprv_SelToStruct( const char* sSql, APP_FLD_DESC desc_arr[], int desc_num, void* pdes)
{
    CURSOR cur;
    char szErrMsg[512];

    if( sSql == NULL || pdes == NULL || desc_arr == NULL || desc_num <= 0)
    {
        LOG(LM_STD, Fmtmsg("传入参数空"), "WARNING");
        return -1;
    }
    cur = DCIDeclareCursor( sSql, DCI_DEFAULT);
    if (cur == INVALID_CURSOR)
    {
        LOG(LM_STD, Fmtmsg("游标定义失败[%s]-[%s]",  DCILastError(), sSql), "ERROR");
        return -1;
    }
    if(DCIExecute(cur) == -1)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败[%s]", DCILastError() ), "ERROR");
        DCIFreeCursor(cur);
        return -1;
    }

    int rs = 0;
    if( 0 > ( rs = APP_DBFetch( cur, desc_arr, desc_num, pdes, szErrMsg ) ) )
    {
        LOG(LM_STD, Fmtmsg("游标获取记录错误[%s]",  szErrMsg ), "ERROR");
        return -1;
    }
    DCIFreeCursor(cur);  /*被遗漏过*/
    return rs;
}

