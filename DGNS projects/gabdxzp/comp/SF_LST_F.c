#include "gaps_head.h"
#include "gabdxzp_head.h"
#include "sfxt_lstqry.h"

/************************************************************************
动态组件函数定义
组件函数名称:ffunc_sfxt_listQry_getFileName
函数名称:获取回写文件名
参数:

组件结果状态:
  结果状态码        结果说明
  < 0               数据准备失败
  = 0               成功
  
项 目 组: 
程 序 员:屠秋龙 
发布日期:20160226
修改日期:
参数使用示例:
************************************************************************/
int ffunc_sfxt_listQry_getFileName(HXMLTREE lXmlhandle, char* psFileName)
{
    char sPltDate[8+1];
    char sPltNum[8+1];
    char sJyjg[16+1];
    char sJygy[16+1];
    char sFilePath[256];
    int  iRet = -1;
    
    memset(sPltDate, 0x00, sizeof(sPltDate));
    memset(sPltNum, 0x00, sizeof(sPltNum));
    memset(sJyjg, 0x00, sizeof(sJyjg));
    memset(sJygy, 0x00, sizeof(sJygy));
    GAB_DXZP_GETXMLSTR_NOTNULL( "/sfxt/jyjg", sJyjg, "交易机构" )
    GAB_DXZP_GETXMLSTR_NOTNULL( "/sfxt/jygy", sJygy, "交易柜员" )
    GAB_DXZP_GETXMLSTR_NOTNULL( XMLNM_SYSDATE, sPltDate, "平台日期" )
    GAB_DXZP_GETXMLSTR_NOTNULL( XMLNM_ZHQZLSH, sPltNum, "平台流水号" )
    
    memset(sFilePath, 0x00, sizeof(sFilePath));
    /* XMLNM_SYS_LISTQRYFP */
    GAB_DXZP_GETXMLSTR_NULL( "/sfxt/listqryfp", sFilePath, "列表查询路径" )
    if (sFilePath[0] == '\0')
    {
        snprintf(sFilePath, sizeof(sFilePath),"%s/file", getenv("HOME"));
    }
    sprintf(psFileName, "%s/sfxtlist_%s%s_%s_%s", 
        sFilePath, sJyjg, sJygy, sPltDate, sPltNum);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:ffunc_sfxt_listQry_getCntNum
函数名称:获取总笔数
参数:

组件结果状态:
  结果状态码        结果说明
  < 0               数据准备失败
  = 0               成功
  
项 目 组: 
程 序 员:屠秋龙 
发布日期:20160226
修改日期:
参数使用示例:
************************************************************************/
int ffunc_sfxt_listQry_getCntNum(HXMLTREE lXmlhandle, char* psSql, int iSqlLen, int* piCntNum)
{
    char sSql[8192];   /*保存传入sql语句*/
    char sSql1[4076];  /*条件串*/
    char sSql2[4096];  /*count统计串*/
    char* pStr1 = NULL;
    char* pStr2 = NULL;
    int iSql1 = 0;
    int iRet = -1;
    int iLen = 0;
    int iRelPos = 0;  /*sql条件相对偏移位置*/

    if (iSqlLen > sizeof (sSql) - 1)
    {
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("列表查询SQL语句有误,len:psSql[%d],size:sSql[%d]", iSqlLen, sizeof (sSql)), fpub_GetCompname(lXmlhandle));
    }

    memset(sSql, 0x00, sizeof (sSql));
    pstrcopy(sSql, psSql, sizeof (sSql) - 1);
    strtoupper(sSql);
    pStr1 = (char *)strstr(sSql, "SELECT ");
    pStr2 = (char *)strstr(sSql, " FROM ");
    if ( pStr2 == NULL )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("列表查询SQL语句有误,[%s]", psSql), fpub_GetCompname(lXmlhandle));
    }
    /*条件串的相对偏移*/
    iRelPos = pStr2 - sSql;
    /*SELECT列表串长度*/
    iLen = (int)(pStr2 - pStr1);
    /*ORDER BY串的位置*/
    pStr2 = strstr(sSql, "ORDER BY");
    if (pStr2 != NULL)
    {
        iLen += (iSqlLen - (int)(pStr2 - sSql));
    }
    memset(sSql1, 0x00, sizeof(sSql1));
    /*取出条件串*/
    pstrcopy(sSql1, psSql + iRelPos, iSqlLen-iLen+1);
    LOG(LM_DEBUG, Fmtmsg("sSql1[%s]\npSql[%s]", sSql1, psSql), fpub_GetCompname(lXmlhandle));
    COMP_SOFTSETXML("/sfxt/qrywhere", sSql1);
    memset(sSql2, 0x00, sizeof(sSql2));
    snprintf(sSql2, sizeof(sSql2), "select count(*) %s", sSql1);

    if ( (iRet = sql_CountSql( sSql2 )) == -1 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("列表查询获取总记录数失败,[%d]", iRet), fpub_GetCompname(lXmlhandle));
    }
    *piCntNum = iRet;
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:ffunc_sfxt_listQry_wrtRndFile
函数名称:列表查询写文件方式
参数:

组件结果状态:
  结果状态码        结果说明
  < 0               数据准备失败
  = 0               成功
  
项 目 组: 
程 序 员:屠秋龙 
发布日期:20160226
修改日期:
参数使用示例:
************************************************************************/
int ffunc_sfxt_listQry_wrtRndFile(HXMLTREE lXmlhandle, char* psSql, int iStartNum, int iEndNum, int* piRealNum)
{
    char sFileName[256];
    FILE* fp;
    int iRet = -1;
    /* 获取文件名 */
    memset(sFileName, 0x00, sizeof(sFileName));
    iRet = ffunc_sfxt_listQry_getFileName(lXmlhandle, sFileName);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "获取列表文件名");
    COMP_SOFTSETXML(XMLNM_RESP_FILENAME, sFileName)
    /* 打开文件 */
    LOG(LM_DEBUG, Fmtmsg("列表查询->文件名[%s]", sFileName), fpub_GetCompname(lXmlhandle)); 
    fp = fopen(sFileName, "w+");
    if ( fp == NULL )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_FILEOP, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)));
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)), fpub_GetCompname(lXmlhandle)); 
    }
    /* 打开数据库连接 
    iRet = fbasc_db_openDB(lXmlhandle);
    GAB_DXZP_FUNCCHK_NOTSUCC_CLSFP(lXmlhandle, iRet, "打开数据库连接");
    */
    /* 处理 */
    iRet = ffunc_sfxt_listQry_fetAndWrtRndFile(lXmlhandle, psSql, fp, iStartNum, iEndNum, piRealNum);
    /* 关闭数据库连接、文件句柄 
    fclose(fp);
    fbasc_db_closeDB(lXmlhandle);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "处理列表查询");
    */
    COMP_SOFTSETXML(XMLNM_RESP_FILEFLAG, "1")
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:ffunc_sfxt_listQry_fetAndWrtRndFile
函数名称:文件方式获取并回写记录
参数:

组件结果状态:
  结果状态码        结果说明
  < 0               数据准备失败
  = 0               成功
  
项 目 组: 
程 序 员:屠秋龙 
发布日期:20160226
修改日期:
参数使用示例:
************************************************************************/
int ffunc_sfxt_listQry_fetAndWrtRndFile(HXMLTREE lXmlhandle, char* psSql, FILE* fp, int iStartNum, int iEndNum, int* piRealNum)
{
    char sBuf[1024];
    char sLine[4096];
    int i = 0;
    int iCurNum = 1;
    int iRealNum = 0;
    int iQueryNum = 0;
    int iRet = -1;
    int iNumCols=0;
    int j=0;
    int iFlag=-1;
    char sColName[100];
    CURSOR cur;

    /* 声明游标 */
    if ((cur = DCIDeclareCursor(psSql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("声明C01LSTQRY游标失败,[%s]", DCILastError()), fpub_GetCompname(lXmlhandle));
    }
    if (DCIExecute(cur) == -1)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("打开C01LSTQRY游标失败,[%s]", DCILastError()), fpub_GetCompname(lXmlhandle));
    }
    /* 获取列名 */
    iNumCols = DCINumCols(cur);
    memset(sLine, 0x00, sizeof(sLine));
    for (j=0; j<iNumCols; 	j++)
    {
        memset(sColName, 0x00, sizeof(sColName));
        DCIColName(cur, j, sColName, sizeof(sColName));   /* 取字段名 */
        snprintf(sLine+strlen(sLine), sizeof(sLine), "%s,", sColName);
    }
    strcat(sLine, "\n");
    fwrite(sLine, strlen(sLine), 1, fp);
    LOG(LM_STD, Fmtmsg("COLNAME:[%s]", sLine), fpub_GetCompname(lXmlhandle));    

    /*开始循环取记录数*/
    iQueryNum = iEndNum-iStartNum;
    for ( iRealNum=0; iRealNum<iQueryNum; iRealNum++)
    {
        iCurNum = iStartNum + iRealNum ;
        iRet = DCIFetch2(cur, DCI_FETCH_ABSOLUTE, iCurNum);
	    if (iRet == -1)
        {
    	    fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
    	    LOG(LM_STD, Fmtmsg("从C01LSTQRY游标失败,[%s]", DCILastError()), fpub_GetCompname(lXmlhandle));
    	    iFlag=-1;
    	    break;
        }	  	
        if (iRet == 0)  	/*无记录*/
        {
    	    break;
    	}
        memset(sLine, 0, sizeof(sLine));
        for (j=0; j<iNumCols; j++)
        {
    	    memset(sBuf, 0x00, sizeof(sBuf));
    	    snprintf( sBuf, sizeof(sBuf), "%s", DCIFieldAsString(cur, j) );
    	    trim(sBuf);
    	    snprintf(sLine+strlen(sLine), sizeof(sLine), "%s|", sBuf );
        }
        LOG(LM_DEBUG, Fmtmsg("ROW[%d]:[%s]", i, sLine), fpub_GetCompname(lXmlhandle));
        strcat(sLine, "\n");
        fwrite(sLine, strlen(sLine), 1, fp);
        
    }
    DCIFreeCursor(cur);
    *piRealNum = iRealNum;
    if ( iFlag < 0 )
    {
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("从C01LSTQRY游标失败"),fpub_GetCompname(lXmlhandle));
    }
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:ffunc_sfxt_listQry_wrtRndXml
函数名称:列表查询写XML树方式
参数:

组件结果状态:
  结果状态码        结果说明
  < 0               数据准备失败
  = 0               成功
  
项 目 组: 
程 序 员:屠秋龙 
发布日期:20160226
修改日期:
参数使用示例:
************************************************************************/
int ffunc_sfxt_listQry_wrtRndXml(HXMLTREE lXmlhandle, char* psSql, int iStartNum, int iEndNum, int* piRealNum)
{
    int iRet = -1;
    /* 打开数据库连接 
    LOG( LM_DEBUG, Fmtmsg("司法查控通用查询->------------1-----------"), fpub_GetCompname(lXmlhandle));
    iRet = fbasc_db_openDB(lXmlhandle);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "打开数据库连接");
    LOG( LM_DEBUG, Fmtmsg("司法查控通用查询->------------2-----------"), fpub_GetCompname(lXmlhandle));
    */
    /* 处理 */
    iRet = ffunc_sfxt_listQry_fetAndWrtRndXml(lXmlhandle, psSql, iStartNum, iEndNum, piRealNum);
    /* 关闭数据库连接、文件句柄 
    fbasc_db_closeDB(lXmlhandle);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "处理列表查询");
    */
    COMP_SOFTSETXML(XMLNM_RESP_FILEFLAG, "1")
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:ffunc_sfxt_listQry_fetAndWrtRndXml
函数名称:XML方式获取并回写记录
参数:

组件结果状态:
  结果状态码        结果说明
  < 0               数据准备失败
  = 0               成功
  
项 目 组: 
程 序 员:屠秋龙 
发布日期:20160226
修改日期:
参数使用示例:
************************************************************************/
int ffunc_sfxt_listQry_fetAndWrtRndXml(HXMLTREE lXmlhandle, char* psSql, int iStartNum, int iEndNum, int* piRealNum)
{
    char sBuf[1024];
    char sLine[1024];
    int i = 0;
    int iCurNum = 1;
    int iRealNum = 0;
    int iQueryNum = 0;
    int iRet = -1;
    int iNumCols=0;
    int j=0;
    int iFlag=0;
    char sColName[100];
    char sSfxtNodePath[128];
    CURSOR cur;
    /* 声明游标 */
    if ((cur = DCIDeclareCursor(psSql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("声明C01LSTQRY游标失败,[%s]", DCILastError()), fpub_GetCompname(lXmlhandle));
    }
    if (DCIExecute(cur) == -1)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("打开C01LSTQRY游标失败,[%s]", DCILastError()), fpub_GetCompname(lXmlhandle));
    }
    /* 获取列名 */
    iNumCols = DCINumCols(cur);  
    /*开始循环取记录数*/
    iQueryNum = iEndNum-iStartNum;
    for ( iRealNum=0; iRealNum<iQueryNum; iRealNum++)
    {
        iCurNum = iStartNum + iRealNum ;
        iRet = DCIFetch2(cur, DCI_FETCH_ABSOLUTE, iCurNum);
	    if (iRet == -1)
        {
    	    fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
    	    LOG(LM_STD, Fmtmsg("从C01LSTQRY游标失败,[%s]", DCILastError()), fpub_GetCompname(lXmlhandle));
    	    iFlag=-1;
    	    break;
        }	  	
        if (iRet == 0)  	/*无记录*/
        {
    	    break;
    	}
        memset(sLine, 0, sizeof(sLine));
        for (j=0; j<iNumCols; j++)
        {
    	    memset(sColName, 0x00, sizeof(sColName));
            DCIColName(cur, j, sColName, sizeof(sColName));   /* 取字段名 */
            strtolower(sColName);
            memset(sSfxtNodePath, 0x00, sizeof(sSfxtNodePath));
            snprintf(sSfxtNodePath, sizeof(sSfxtNodePath), XMLNM_RESP_LISTQRY, iRealNum+1, sColName);
            trim(sSfxtNodePath);
    	    snprintf(sLine, sizeof(sLine), "%s", DCIFieldAsString(cur, j));
    	    trim(sLine);
    	    COMP_SOFTSETXML(sSfxtNodePath, sLine);
            LOG(LM_DEBUG, Fmtmsg("[%s]:[%s]", sSfxtNodePath, sLine), fpub_GetCompname(lXmlhandle));
        }
    }
    DCIFreeCursor(cur);
    *piRealNum = iRealNum ;
    if ( iFlag < 0 )
    {
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("从C01LSTQRY游标失败"),fpub_GetCompname(lXmlhandle));
    }
    return 0;
}

/*****************************************************
   函数名称:  int ffunc_xml_getNodeValue(HXMLTREE lXmlhandle, const char* szPath, const char* nodeAttr, char* szValue, unsigned int size, int iFlag)
   函数功能:  获取XML节点值,若字符串节点为空则赋'-';若金额数字型节点为空则赋0
   函数参数:  lXmlhandle  XML树操作句柄
              Path  节点路径
              nodeAttr 节点属性 0-字符串, 1-金额，数字等
              szValue 节点值存放字符串
              size  存放值的空间大小
              iFlag 节点是否必须存在 GAB_DXZP_XML_NULL GAB_DXZP_XML_NOTNULL
             
   函数返回:  >0: 节点值的实际长度
              -1:输入参数为空或输出变量为NULL
              -2:不为空的XML节点不存在
              -3:其他原因失败

   函数说明:  
            
   修改说明:  
*****************************************************/
int ffunc_xml_getNodeValue(HXMLTREE lXmlhandle, char* psPath, char* psNodeAttr, char* psValue, unsigned int size, int iFlag)
{
    int  iRet = 0;
    char sBuf[1024];
    int  iNodeValueLen = 0;
    char* psNodeValue = NULL;
    
    if ( psValue == NULL )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_XMLOP, Fmtmsg(MSG_GAB_DXZP_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!节点[%s]的目标变量为NULL!", MSG_GAB_DXZP_XMLOP, psPath),"")
        return -1;
    }
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iNodeValueLen = sizeof(sBuf);
    if ( iNodeValueLen > size )
    {
        psNodeValue = sBuf;
        iRet = xml_GetElement(lXmlhandle, psPath, psNodeValue, iNodeValueLen);
        pstrcopy(psValue, psNodeValue, size);
    }else
    {
        iNodeValueLen = size;
        psNodeValue = psValue ;
        iRet = xml_GetElement(lXmlhandle, psPath, psNodeValue, iNodeValueLen);
    }
    psNodeValue = NULL;
    if( iRet == FAIL && XML_NODE_NOTNULL == iFlag )
    {        
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_XMLOP, Fmtmsg(MSG_GAB_DXZP_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!节点[%s]不存在[%d]!", MSG_GAB_DXZP_XMLOP, psPath, iRet),"") 
        return -2;
    }
    
    if( (psValue[0] == '\0') && (XML_NODE_NOTNULL == iFlag) )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_XMLOP, Fmtmsg(MSG_GAB_DXZP_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!节点[%s]值为空!", MSG_GAB_DXZP_XMLOP, psPath),"")
        return -2;
    }    
    trim(psValue);       
    return strlen(psValue);
}
