/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:�м�ҵ��ƽ̨��Ŀ
��    ��:V2.1.0.2
����ϵͳ:AIX+DB2
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iconv.h>
#include "gaps_head.h"
#include "DCI.h"

/************************************************************************
��̬�����������
    ���ü��ܻ�  ����ת����PIN 
�������:
    ���ܻ�IP   
    ���ܻ�Port 
    ϵͳID     
    �ⲿID
    ԴPIN����
    ԴZpk��Կ����
    Ŀ��Zpk��Կ����
    Ŀ��PIN���Ľ���ڵ���     
************************************************************************/
IRESULT PABYBH_CHENGESEC(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int handle = 0;
       
    char sPinData2[256 + 1];
    
    char szBuf[255];
    char respcode[10];
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"");   
 
/*
����:  ת����PIN
����:  appHandle[in]            Ӧ�ýӿھ��
        pinBlock1[in]           PIN����
        accNo1[in]              Դ�˺�
        accNo2[in]              Ŀ���˺�
        keyName1[in]            Դ��Կ����
        keyName2[in]            Ŀ����Կ����
        format1[in]             ԴPIN��ʽ
        format2[in]             Ŀ��PIN��ʽ
        checkFlag[in]           �����ʶ ��ѡ,Ĭ��Ϊ0
                                        0��ϵͳ�趨
                                        1���û�����
                                        2��ϵͳ�������
        checkData1[in]          PINУ������ checkFlagΪ1ʱ���ڣ� ����ʮ�������ַ����ַ���N��������
        decimalFlag[in]         ʮ����ת�����ʶ,��ѡ,
                                        0��ϵͳ�趨
                                        1���û�����
                                        2��ϵͳ�������
        decimalTable1[in]       ʮ����ת�������� decimalFlag?ʱ��

        pinBlock2[out]          PIN����,keyName2Ϊtpk\zpkʱ����
        pinOffset[out]          PIN Offset,keyName2Ϊpvkʱ����
        checkData2[out]         PINУ������,keyName2Ϊpvkʱ����
        decimalTable2[out]      PINʮ����ת��������,keyName2Ϊpvkʱ����
����ֵ:
        >=0     �ɹ�
        <0      ������

EXPORTDLL int UnionAPIServiceE142(int appHandle, const char *pinBlock1, const char *keyName1, const char *keyName2, const char *accNo1, const char *accNo2, const char *format1, const char *format2, int checkFlag, const char *checkData1, int decimalFlag, const char *decimalTable1, char *pinBlock2, char *pinOffset, char *checkData2, char *decimalTable2);
*/     
       memset(sPinData2,0x00,sizeof(sPinData2));
       COMP_SOFTSETXML("/pabybh/req/secopera", "0");   /*ת����*/
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
		        LOG(LM_DEBUG, Fmtmsg("���ü���ƽ̨����ʧ��"), "INFO");
		        fpub_SetMsg( lXmlhandle, 999999, "���ü���ƽ̨����ʧ��" );
		        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		        return -1;
        }
    COMP_SOFTGETXML("/pabybh/req/capitalpwd", sPinData2);
    LOG(LM_DEBUG, Fmtmsg("PIN����ֵ:[%s]", sPinData2), "INFO");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}
/************************************************************************
��̬�����������
    ���ü��ܻ� E150 ����MACֵ������У�� 
�������:
    ���ܻ�IP   
    ���ܻ�Port 
    ϵͳID     
    �ⲿID     
    Zak��Կ����
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
    LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "" )
#endif
 
    memset(sZakName, 0, sizeof(sZakName));
    memset(sMacType, 0, sizeof(sMacType));
    memset(sMacFlag, 0, sizeof(sMacFlag));
    COMP_GETPARSEPARAS(1, sZakName, "Zak��Կ����");
    COMP_GETPARSEPARAS(2, sMacType, "MAC����(1.����MAC 2.У��MAC)");
    COMP_GETPARSEPARAS(3, sMacFlag, "�Ƿ���ҪMAC(1.��Ҫ 0.����Ҫ)"); 
    COMP_SOFTSETXML("/pabybh/req/secopera", "1");   /*MAC���ɣ�У�飩*/
    trim(sZakName);
    trim(sMacFlag);
    trim(sMacType);    

    LOG(LM_DEBUG, Fmtmsg("Zak��Կ����                       :[%s]", sZakName), "INFO");
    LOG(LM_DEBUG, Fmtmsg("MAC����(1.����MAC 2.У��MAC)      :[%s]", sMacType), "INFO");
    LOG(LM_DEBUG, Fmtmsg("�Ƿ���ҪMAC(1.��Ҫ 0.����Ҫ)      :[%s]", sMacFlag), "INFO");
/*
int UnionAPIServiceE150(int appHandle,int mode,const char *keyName,const char *keyValue,int algorithmID,int fillMode,int dataType,char *data,int lenOfData,char *mac)
    
    iRet = UnionAPIServiceE150(handle, 1, sZakName, "", 2, 0, 1, sData, iLen, sMacData);
    ����:
        appHandle[in]   Ӧ�ýӿھ��
        mode[in]    ģʽ����ѡ��Ĭ��Ϊ1
            1��ָ����Կ����
            2��ָ����Կ����
        keyName [in]  ��Կ����
            modeΪ1ʱ��Ϊzak��Կ����
            modeΪ2ʱ��Ϊzmk��Կ����     
        keyValue[in]    ��Կ���ģ���ѡ��modeΪ2�Ǵ��ڣ���ZMK����  
        algorithmID[in] �㷨��ʶ����ѡ��Ĭ��Ϊ1
            1��ANSIX9.19
            2���й�������׼
            3������POS��׼
        fillMode    ������� (0: 1: 2:)
        dataType[in]    �������� ��ѡ��Ĭ��Ϊ2
            1��asc�ַ�
            2��ʮ��������
        data[in]         ����
        lenOfData[in]    ���ݳ���
    ����
        mac[out]         macУ��ֵ
        ����ֵ: >=0 �ɹ�   <0 ������
*/
    
    if (sMacType[0] == '1')   // MAC����(1.����MAC 2.У��MAC) 
    {
        memset( szClearText, 0, sizeof( szClearText ) );
        iComBuf = 0;
        if ((iComBuf = xml_RelGetBinElement( lXmlhandle, "/pabybh/commbuf", szClearText, sizeof( szClearText ) ) ) == FAIL )
        {
            LOG( LM_STD, Fmtmsg( "��ȡͨѶ������ʧ��"), "ERR" );
		        fpub_SetMsg( lXmlhandle, 99999, "��ȡͨѶ������ʧ��" );
		        fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		        LOGRET( COMPRET_FAIL, LM_STD, "��ȡͨѶ������ʧ��", "" );   
		    }
		    LOG(LM_DEBUG, Fmtmsg("����:[%d]-[%s]", iComBuf, szClearText), "INFO");
        /*�����в�����MAC�򣬽����ɵ�MAC��ֱ����ӵ�����ĩβ*/
        if(sMacFlag[0] == '0')
        		iCommLen = iComBuf - 4;
        else  iCommLen = iComBuf - 4 + 8;
        
        memset(szCommLen, 0, sizeof(szCommLen));
        sprintf(szCommLen, "%04d", iCommLen);
        /*----------------------------------����ͷ����------------------------------------------*/
        /*ѭ��������ͷǰ4���ֽڸ�ֵ*/
        for( j = 0; j <= 3; j++ )
        {
             szClearText[j] = szCommLen[j];
        }
        iTotalPackLen = iCommLen + 4;
        LOG( LM_DEBUG, Fmtmsg( "��ӳ��Ⱥ���[%s]", szClearText ), "Info" );
        
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
		            LOG(LM_DEBUG, Fmtmsg("���ü���ƽ̨����MACֵ������У��ʧ��"), "INFO");
		            fpub_SetMsg( lXmlhandle, 99999, "���ü���ƽ̨����MACֵ������У��ʧ��" );
		            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		            return -1;
		        }
		        COMP_SOFTGETXML("/pabybh/req/mac",sMacData);
		        LOG(LM_DEBUG, Fmtmsg("Mac:[%s]", sMacData), "INFO");
		    
		        /*��ȡǰ��λתΪHEX����MAC��*/
		        memset(szHexMac, 0, sizeof(szHexMac));
		        memcpy(szHexMac, sMacData, 8);
		        szHexMac[8] = 0;
		        LOG( LM_DEBUG, Fmtmsg("MACУ��ֵ[%s]", szHexMac), "INFO");
		        memcpy( szClearText + ( iTotalPackLen - 8 ), szHexMac, 8 );
		        LOG( LM_DEBUG, Fmtmsg( "���MAC����:[%s]", szClearText ), "INFO" );
        	 
        }
        /*��ASCתΪHEX�洢��/commbuf*/
        if(( iLen = xml_RelSetBinElement( lXmlhandle, "/pabybh/commbuf", szClearText, iTotalPackLen ) ) == FAIL )
        {
             LOG( LM_DEBUG, Fmtmsg( "����ͨѶ������ʧ��!" ), "ERROR" );
             fpub_SetMsg( lXmlhandle, 99999, "����ͨѶ������ʧ��!" );
             fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
             LOGRET( COMPRET_FAIL, LM_STD, "����ͨѶ������ʧ��!", "" );  
        }
    }
    else if (sMacType[0] == '2')   // MAC����(1.����MAC 2.У��MAC)   
    {
    		if(sMacFlag[0] == '0')
        {
        	 LOG( LM_DEBUG, "���Ĵ���ɹ�", "Info" );
					#ifdef DEBUG
					    LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
					#endif
					    fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
					    return COMPRET_SUCC;
        }
    		
        /*��ȥ���ձ��ĵĺ�8λ--����У��MAC*/
        memset( szClearText, 0, sizeof( szClearText ) );
        iComBuf = 0;
        if ((iComBuf = xml_RelGetBinElement( lXmlhandle, "/commbuf", szClearText, sizeof( szClearText ) ) ) == FAIL )
        {
            LOG( LM_STD, Fmtmsg( "��ȡͨѶ������ʧ��"), "ERR" );
		        fpub_SetMsg( lXmlhandle, 99999, "��ȡͨѶ������ʧ��" );
		        fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		        LOGRET( COMPRET_FAIL, LM_STD, "��ȡͨѶ������ʧ��", "" );   
		    }
		    LOG(LM_DEBUG, Fmtmsg("����:[%s][%d]", szClearText, iComBuf), "INFO");
        memset(szCommLen, 0, sizeof(szCommLen));
        memcpy( szCommLen, szClearText, 4 );
        iCommLen = atoi( szCommLen ); // ʵ�ʱ����峤�ȣ���MAC
 
        iTotalPackLen = iCommLen + 4; // �ܳ���
        LOG( LM_DEBUG, Fmtmsg( "ͨѶ���ܳ�[%d]", iTotalPackLen ), "INFO" );
        
        /*��ȡԭMAC*/
        memset(szOriMac, 0, sizeof( szOriMac ) );
        memcpy(szOriMac, ( szClearText + 4 + iCommLen - 8 ) , 8);
        LOG( LM_DEBUG, Fmtmsg("ԭMAC:[%s]", szOriMac), "INFO");
        if (strlen(szOriMac) < 8) {
            LOG(LM_DEBUG, Fmtmsg("MACУ��ʧ��,ԭMAC��ʽ����"), "INFO");
            fpub_SetMsg(lXmlhandle, 99999, "MACУ��ʧ��,ԭMAC��ʽ����!" );
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
            LOG(LM_DEBUG, Fmtmsg("���ü���ƽ̨����MACֵ������У��ʧ��"), "INFO");
            fpub_SetMsg( lXmlhandle, 99999, "���ü���ƽ̨����MACֵ������У��ʧ��" );
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return -1;
        }
        COMP_SOFTGETXML("/pabybh/req/mac",sMacData);
        LOG( LM_DEBUG, Fmtmsg( "MAC:[%s]", sMacData ), "INFO" );
    
        /*��������MAC��ȡǰ��λ*/
        memset(szHexMac, 0, sizeof(szHexMac));
        memcpy(szHexMac, sMacData, 8);
        szHexMac[8] = 0;
        LOG( LM_DEBUG, Fmtmsg("MACУ��ֵ:[%s]", szHexMac), "INFO");
    
        if ( 0 != memcmp(szOriMac, szHexMac, 8) )
        {
             LOG( LM_DEBUG, Fmtmsg( "MACУ��ʧ��;ԭMAC[%s],У��MAC[%s]",szOriMac, szHexMac), "ERROR" );
             fpub_SetMsg( lXmlhandle, 999999, "MACУ��ʧ��!" );
             fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
             LOGRET( COMPRET_FAIL, LM_STD, "MACУ��ʧ��!", "" );
        }
    }
 
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
    fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
    return COMPRET_SUCC;
}



