/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:中间业务平台项目
版    本:V2.1.0.2
操作系统:AIX+DB2
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iconv.h>
#include "gaps_head.h"
#include "DCI.h"

/************************************************************************
动态组件函数定义
    调用加密机  服务转加密PIN 
组件参数:
    加密机IP   
    加密机Port 
    系统ID     
    外部ID
    源PIN密文
    源Zpk密钥名称
    目的Zpk密钥名称
    目的PIN密文结果节点名     
************************************************************************/
IRESULT PABYBH_CHENGESEC(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int handle = 0;
       
    char sPinData2[256 + 1];
    
    char szBuf[255];
    char respcode[10];
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"");   
 
/*
描述:  转加密PIN
参数:  appHandle[in]            应用接口句柄
        pinBlock1[in]           PIN密文
        accNo1[in]              源账号
        accNo2[in]              目的账号
        keyName1[in]            源密钥名称
        keyName2[in]            目的密钥名称
        format1[in]             源PIN格式
        format2[in]             目的PIN格式
        checkFlag[in]           检验标识 可选,默认为0
                                        0：系统设定
                                        1：用户输入
                                        2：系统随机生成
        checkData1[in]          PIN校验数据 checkFlag为1时存在， 包含十六进制字符和字符“N”的数据
        decimalFlag[in]         十进制转换表标识,可选,
                                        0：系统设定
                                        1：用户输入
                                        2：系统随机生成
        decimalTable1[in]       十进制转换表数据 decimalFlag?时在

        pinBlock2[out]          PIN密文,keyName2为tpk\zpk时存在
        pinOffset[out]          PIN Offset,keyName2为pvk时存在
        checkData2[out]         PIN校验数据,keyName2为pvk时存在
        decimalTable2[out]      PIN十进制转换表数据,keyName2为pvk时存在
返回值:
        >=0     成功
        <0      错误码

EXPORTDLL int UnionAPIServiceE142(int appHandle, const char *pinBlock1, const char *keyName1, const char *keyName2, const char *accNo1, const char *accNo2, const char *format1, const char *format2, int checkFlag, const char *checkData1, int decimalFlag, const char *decimalTable1, char *pinBlock2, char *pinOffset, char *checkData2, char *decimalTable2);
*/     
       memset(sPinData2,0x00,sizeof(sPinData2));
       COMP_SOFTSETXML("/pabybh/req/secopera", "0");   /*转加密*/
       iRet=fpub_CallFlow(lXmlhandle,"flow_pabybh_secsvr");
/*    iRet = UnionAPIServiceE142(handle, sPinData1, sZpkName1, sZpkName2, "000000000000", "000000000000", "01", "01", 0, "0", 0, "0", sPinData2, "0", "0", "0");	*/
    memset(szBuf,0x00,sizeof(szBuf));
    memset(respcode,0x00,sizeof(respcode));
        COMP_SOFTGETXML("/pub/respcode", szBuf);
        trim(szBuf);
        if(strlen(szBuf) >= 6)
        	sprintf(respcode,"%.6s",szBuf);
        else sprintf(respcode,"%0*d%s",6-strlen(szBuf),0,szBuf);
        LOG(LM_DEBUG,Fmtmsg("iRet=[%d],respcode=[%s]",iRet,respcode),"INFO")
        if(strcmp(respcode,"000000") != 0 || iRet != MID_SYS_SUCC)
        {
		        LOG(LM_DEBUG, Fmtmsg("调用加密平台服务失败"), "INFO");
		        fpub_SetMsg( lXmlhandle, 999999, "调用加密平台服务失败" );
		        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		        return -1;
        }
    COMP_SOFTGETXML("/pabybh/req/capitalpwd", sPinData2);
    LOG(LM_DEBUG, Fmtmsg("PIN密文值:[%s]", sPinData2), "INFO");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}
/************************************************************************
动态组件函数定义
    调用加密机 E150 服务MAC值生成与校验 
组件参数:
    加密机IP   
    加密机Port 
    系统ID     
    外部ID     
    Zak密钥名称
************************************************************************/
IRESULT PABYBH_MAC(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iLen = 0;
    int iPort = 0;
    int handle = 0;
    
    char sBuf[4096]={0};
    char sZakName[256 + 1];
    char sData[8096 + 1];
    char sMacFlag[256 + 1];
    char sMacType[256 + 1];
    char sMacData[256 + 1];
    char szOriMac[256 + 1];
    
    unsigned char szClearText[8096], szHexMac[8+1];
    char szCommLen[255];
    char szBuf[255];
    int  iCommLen = 0, iTotalPackLen = 0;
    int  iParas = 0;
    int  iComBuf = 0;
    int  j = 0;
 		
 		char respcode[10];
 
    fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "" )
#endif
 
    memset(sZakName, 0, sizeof(sZakName));
    memset(sMacType, 0, sizeof(sMacType));
    memset(sMacFlag, 0, sizeof(sMacFlag));
    COMP_GETPARSEPARAS(1, sZakName, "Zak密钥名称");
    COMP_GETPARSEPARAS(2, sMacType, "MAC类型(1.生成MAC 2.校验MAC)");
    COMP_GETPARSEPARAS(3, sMacFlag, "是否需要MAC(1.需要 0.不需要)"); 
    COMP_SOFTSETXML("/pabybh/req/secopera", "1");   /*MAC生成（校验）*/
    trim(sZakName);
    trim(sMacFlag);
    trim(sMacType);    

    LOG(LM_DEBUG, Fmtmsg("Zak密钥名称                       :[%s]", sZakName), "INFO");
    LOG(LM_DEBUG, Fmtmsg("MAC类型(1.生成MAC 2.校验MAC)      :[%s]", sMacType), "INFO");
    LOG(LM_DEBUG, Fmtmsg("是否需要MAC(1.需要 0.不需要)      :[%s]", sMacFlag), "INFO");
/*
int UnionAPIServiceE150(int appHandle,int mode,const char *keyName,const char *keyValue,int algorithmID,int fillMode,int dataType,char *data,int lenOfData,char *mac)
    
    iRet = UnionAPIServiceE150(handle, 1, sZakName, "", 2, 0, 1, sData, iLen, sMacData);
    参数:
        appHandle[in]   应用接口句柄
        mode[in]    模式，可选，默认为1
            1：指定密钥名称
            2：指定密钥密文
        keyName [in]  密钥名称
            mode为1时，为zak密钥名称
            mode为2时，为zmk密钥名称     
        keyValue[in]    密钥密文，可选，mode为2是存在，由ZMK保护  
        algorithmID[in] 算法标识，可选，默认为1
            1：ANSIX9.19
            2：中国银联标准
            3：银联POS标准
        fillMode    填充类型 (0: 1: 2:)
        dataType[in]    数据类型 可选，默认为2
            1：asc字符
            2：十六进制数
        data[in]         数据
        lenOfData[in]    数据长度
    返回
        mac[out]         mac校验值
        返回值: >=0 成功   <0 错误码
*/
    
    if (sMacType[0] == '1')   // MAC类型(1.生成MAC 2.校验MAC) 
    {
        memset( szClearText, 0, sizeof( szClearText ) );
        iComBuf = 0;
        if ((iComBuf = xml_RelGetBinElement( lXmlhandle, "/pabybh/commbuf", szClearText, sizeof( szClearText ) ) ) == FAIL )
        {
            LOG( LM_STD, Fmtmsg( "获取通讯域内容失败"), "ERR" );
		        fpub_SetMsg( lXmlhandle, 99999, "获取通讯域内容失败" );
		        fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		        LOGRET( COMPRET_FAIL, LM_STD, "获取通讯域内容失败", "" );   
		    }
		    LOG(LM_DEBUG, Fmtmsg("报文:[%d]-[%s]", iComBuf, szClearText), "INFO");
        /*报文中不包含MAC域，将生成的MAC域直接添加到报文末尾*/
        if(sMacFlag[0] == '0')
        		iCommLen = iComBuf - 4;
        else  iCommLen = iComBuf - 4 + 8;
        
        memset(szCommLen, 0, sizeof(szCommLen));
        sprintf(szCommLen, "%04d", iCommLen);
        /*----------------------------------报文头处理------------------------------------------*/
        /*循环给报文头前4个字节赋值*/
        for( j = 0; j <= 3; j++ )
        {
             szClearText[j] = szCommLen[j];
        }
        iTotalPackLen = iCommLen + 4;
        LOG( LM_DEBUG, Fmtmsg( "添加长度后报文[%s]", szClearText ), "Info" );
        
        if(sMacFlag[0] == '1')
        {
		        iLen = iComBuf;
		        memset(sMacData, 0, sizeof(sMacData));
		        
		        /* test
		        strcpy(szClearText, "0353900017                                                                                                          2013101809:44:1513101800734465      201310181118                                E   0001120112013101820131018_13101800734458_1118                                                    00000000000000000         0000000000000000          7F65F8F3");
		        
		        memset(szClearText, 0, sizeof(szClearText));
		        strcpy(szClearText, "0353900017                                                                                                          2013101809:44:1513101800734465      201310181118                                E   0001120112013101820131018_13101800734458_1118                                                    00000000000000000         0000000000000000          ");
		        iLen=strlen(szClearText);
		        */
		        xml_SetElementE(lXmlhandle,"/agent/req/PLAIN_DATA",szClearText);
		        iRet=fpub_CallFlow(lXmlhandle,"flow_pabybh_secsvr");
		        memset(szBuf,0x00,sizeof(szBuf));
		        memset(respcode,0x00,sizeof(respcode));
		        COMP_SOFTGETXML("/pub/respcode", szBuf);
		        trim(szBuf);
		        if(strlen(szBuf) >= 6)
		        	sprintf(respcode,"%.6s",szBuf);
		        else sprintf(respcode,"%0*d%s",6-strlen(szBuf),0,szBuf);
		   /*     iRet = UnionAPIServiceE150(handle, 1, sZakName, "", 1, 1, 1, szClearText, iLen, sMacData);*/
		        LOG(LM_DEBUG,Fmtmsg("iRet=[%d],respcode=[%s]",iRet,respcode),"INFO")
		        if(strcmp(respcode,"000000") != 0 || iRet != MID_SYS_SUCC)
		        {
		            LOG(LM_DEBUG, Fmtmsg("调用加密平台服务MAC值生成与校验失败"), "INFO");
		            fpub_SetMsg( lXmlhandle, 99999, "调用加密平台服务MAC值生成与校验失败" );
		            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		            return -1;
		        }
		        COMP_SOFTGETXML("/pabybh/req/mac",sMacData);
		        LOG(LM_DEBUG, Fmtmsg("Mac:[%s]", sMacData), "INFO");
		    
		        /*截取前四位转为HEX存入MAC域*/
		        memset(szHexMac, 0, sizeof(szHexMac));
		        memcpy(szHexMac, sMacData, 8);
		        szHexMac[8] = 0;
		        LOG( LM_DEBUG, Fmtmsg("MAC校验值[%s]", szHexMac), "INFO");
		        memcpy( szClearText + ( iTotalPackLen - 8 ), szHexMac, 8 );
		        LOG( LM_DEBUG, Fmtmsg( "添加MAC后报文:[%s]", szClearText ), "INFO" );
        	 
        }
        /*将ASC转为HEX存储于/commbuf*/
        if(( iLen = xml_RelSetBinElement( lXmlhandle, "/pabybh/commbuf", szClearText, iTotalPackLen ) ) == FAIL )
        {
             LOG( LM_DEBUG, Fmtmsg( "设置通讯域内容失败!" ), "ERROR" );
             fpub_SetMsg( lXmlhandle, 99999, "设置通讯域内容失败!" );
             fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
             LOGRET( COMPRET_FAIL, LM_STD, "设置通讯域内容失败!", "" );  
        }
    }
    else if (sMacType[0] == '2')   // MAC类型(1.生成MAC 2.校验MAC)   
    {
    		if(sMacFlag[0] == '0')
        {
        	 LOG( LM_DEBUG, "报文处理成功", "Info" );
					#ifdef DEBUG
					    LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
					#endif
					    fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
					    return COMPRET_SUCC;
        }
    		
        /*除去接收报文的后8位--生成校验MAC*/
        memset( szClearText, 0, sizeof( szClearText ) );
        iComBuf = 0;
        if ((iComBuf = xml_RelGetBinElement( lXmlhandle, "/commbuf", szClearText, sizeof( szClearText ) ) ) == FAIL )
        {
            LOG( LM_STD, Fmtmsg( "获取通讯域内容失败"), "ERR" );
		        fpub_SetMsg( lXmlhandle, 99999, "获取通讯域内容失败" );
		        fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		        LOGRET( COMPRET_FAIL, LM_STD, "获取通讯域内容失败", "" );   
		    }
		    LOG(LM_DEBUG, Fmtmsg("报文:[%s][%d]", szClearText, iComBuf), "INFO");
        memset(szCommLen, 0, sizeof(szCommLen));
        memcpy( szCommLen, szClearText, 4 );
        iCommLen = atoi( szCommLen ); // 实际报文体长度，含MAC
 
        iTotalPackLen = iCommLen + 4; // 总长度
        LOG( LM_DEBUG, Fmtmsg( "通讯包总长[%d]", iTotalPackLen ), "INFO" );
        
        /*截取原MAC*/
        memset(szOriMac, 0, sizeof( szOriMac ) );
        memcpy(szOriMac, ( szClearText + 4 + iCommLen - 8 ) , 8);
        LOG( LM_DEBUG, Fmtmsg("原MAC:[%s]", szOriMac), "INFO");
        if (strlen(szOriMac) < 8) {
            LOG(LM_DEBUG, Fmtmsg("MAC校验失败,原MAC格式错误！"), "INFO");
            fpub_SetMsg(lXmlhandle, 99999, "MAC校验失败,原MAC格式错误!" );
            fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
            return -1;
        }
 
        memset(sData, 0, sizeof(sData)); 
        memcpy(sData, szClearText, iCommLen +4 - 8);
        iLen = strlen(sData);
        memset(sMacData, 0, sizeof(sMacData));
        /*iRet = UnionAPIServiceE150(handle, 1, sZakName, "", 1, 1, 1, sData, iLen, sMacData);*/
        xml_SetElementE(lXmlhandle,"/agent/req/PLAIN_DATA",sData);
        iRet=fpub_CallFlow(lXmlhandle,"flow_pabybh_secsvr");
        memset(szBuf,0x00,sizeof(szBuf));
        memset(respcode,0x00,sizeof(respcode));
        COMP_SOFTGETXML("/pub/respcode", szBuf);
        trim(szBuf);
        if(strlen(szBuf) >= 6)
        	sprintf(respcode,"%.6s",szBuf);
        else sprintf(respcode,"%0*d%s",6-strlen(szBuf),0,szBuf);
        LOG(LM_DEBUG,Fmtmsg("iRet=[%d],respcode=[%s]",iRet,respcode),"INFO")
        if(strcmp(respcode,"000000") != 0 || iRet != MID_SYS_SUCC)
        {    	
            LOG(LM_DEBUG, Fmtmsg("调用加密平台服务MAC值生成与校验失败"), "INFO");
            fpub_SetMsg( lXmlhandle, 99999, "调用加密平台服务MAC值生成与校验失败" );
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return -1;
        }
        COMP_SOFTGETXML("/pabybh/req/mac",sMacData);
        LOG( LM_DEBUG, Fmtmsg( "MAC:[%s]", sMacData ), "INFO" );
    
        /*本方生成MAC截取前四位*/
        memset(szHexMac, 0, sizeof(szHexMac));
        memcpy(szHexMac, sMacData, 8);
        szHexMac[8] = 0;
        LOG( LM_DEBUG, Fmtmsg("MAC校验值:[%s]", szHexMac), "INFO");
    
        if ( 0 != memcmp(szOriMac, szHexMac, 8) )
        {
             LOG( LM_DEBUG, Fmtmsg( "MAC校验失败;原MAC[%s],校验MAC[%s]",szOriMac, szHexMac), "ERROR" );
             fpub_SetMsg( lXmlhandle, 999999, "MAC校验失败!" );
             fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
             LOGRET( COMPRET_FAIL, LM_STD, "MAC校验失败!", "" );
        }
    }
 
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
    fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
    return COMPRET_SUCC;
}



