/********************************************************************
  ��Ȩ����:�������ӹɷ����޹�˾
  ��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
  ��    ��:V1.0.00
  ����ϵͳ:LIUNX64
  �ļ�����:JZDSF_PUBLIC.c
  �ļ�����:���д��ո��������
  �� Ŀ ��:
  �� �� Ա:liurj
  ��������:20180910
  ��    ��:
  �޸�����:  
 *********************************************************************/

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.00"


#include "gaps_head.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/********************************************************************
**
**	local variable declaration
**
*********************************************************************/
/*
**	Return Code
*/
#define API_RETCD_SUC		"000"	/* SUCCESS ���� */
#define API_RETCD_FAL		"102"	/* FAILURE ʧ�� */

/*
**	Actions Code
*/
#define API_ACTCD_ENC		0	/* ENCRYPT ���ܼ�ѹ */
#define API_ACTCD_DEC		1	/* DECRYPT ���ܽ�ѹ */

/*
**	Constant Length
*/
#define API_MAX_MSG_LEN		9999
#define API_FILE_NAME_LEN	150

#define API_MAC_LEN		64
#define API_KEY_LEN		24
#define API_RETCD_LEN		3
#define DEBUG_STATUS  0    /* 0-API�����������־����0-API�����������Ϣ */

/*
   ע��������Ϊ����⹫������,�����ڷ���״̬����ʾ�ڲ��汾��Ϣ
       �����������£�ÿ�θ��¾�Ӧ�޸İ汾�š�������Ӧ��Ϣ
*/
int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>"
     "<root>"
             "<soname>CUSTOM_PUBLIC_DRC.so</soname>"
             "<sosrcname>CUSTOM_PUBLIC_DRC.c</sosrcname>"
             "<sonote>���д��ո��������</sonote>"
             "<version>"
               "<rec ver=\"1.0.00\" modify=\"2018-09-10 17:18:33\" programer=\"[�����]\" filesize=\"FILE\">��ʼ������</rec>"
             "</version>"
     "</root>";
  printf("\n================��̬���������Ϣ================\n");
  printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
  printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
  printf("%s-%s\n",__PROJECTSNAME,__VERSION);
  if (strlen(sversion) >= isize)
  {
        printf(" -->ȡ��ϸ��Ϣʧ��...\n");
        return -2;
  }
        strcpy(sinfo,sversion);
        printf(" -->��鿴��ϸ��Ϣ...\n");
  return 0;
}


/************************************************************************
  ��̬�����������
  �����������: JZDSF_TxnEec
  �������: ���д��ո�-���ʽ�����Ϣ��MAC�����ܡ����ܡ�У��MAC

  �������: 
  ��ʵʱ���ʽ�����Ϣ��MAC�����ܡ����ܡ�У��MAC
  �������: 
  ��� ��������              ��Դ���       ȱʡֵ          �Ƿ�ɿ�  ����˵��
  1    Դ���Ľڵ�            XML���ݽڵ�    /commbuf       ����Ϊ��  Դ���ģ�����ʱ������Ϣ�壬����ʱ������Ϣ��+У����
  2    �ӽ������õ�KEYֵ     XML�����ַ���                 ����Ϊ��  �ӽ������õ�KEYֵ
  3    Ŀ�걨�Ľڵ�          XML���ݽڵ�    /commbuf       ����Ϊ��  Ŀ�걨�Ľڵ�
  4    ������ʶ              XML�����ַ���   0             ����Ϊ��  0-��MAC���ܣ�1-���ܲ�У��MAC

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����
  ��

  �� Ŀ ��: 
  �� �� Ա: liurj
  ��������: 2018��09��10��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: /commbuf 123456 /commbuf 0
 ************************************************************************/
IRESULT JZDSF_TxnEec_Dec(HXMLTREE lXmlhandle)
{
    int iParas;
    char sSrcEleNode[ 128 + 1 ];   //Դ�������ݽڵ�
    char sDesEleNode[ 128 + 1 ];   //Ŀ�걨�����ݽڵ�
    char sKey[ API_KEY_LEN	+ 1 ];          //KEYֵ
    char sFlag[ 2 ];                        //������ʶ
    char sMsg[ API_MAX_MSG_LEN	+ 1 ];      //���ڴ汨��
    char sBuf[256];    
    
	  char	s_in_msg	[ API_MAX_MSG_LEN	+ 1 ];
		char	s_out_msg	[ API_MAX_MSG_LEN	+ 1 ];
		char	s_rcv_msg	[ API_MAX_MSG_LEN	+ 1 ];
		//char	s_snd_msg	[ API_MAX_MSG_LEN	+ 1 ];
		char	s_mac		[ API_MAC_LEN		+ 1 ];
		char	s_retcd		[ API_RETCD_LEN		+ 1 ];
		char	s_key		[ API_KEY_LEN		+ 1 ];
	
		long	l_in_len = 0L;
		long	l_out_len = 0L;
		//long	l_snd_len = 0L;
		long	l_rcv_len = 0L;
		
	
		memset( s_in_msg, 0x00, sizeof( s_in_msg ) );
		memset( s_out_msg, 0x00, sizeof( s_out_msg ) );
		memset( s_rcv_msg, 0x00, sizeof( s_rcv_msg ) );
		//memset( s_snd_msg, 0x00, sizeof( s_snd_msg ) );
		memset( s_mac, 0x00, sizeof( s_mac ) );
		memset( s_retcd, 0x00, sizeof( s_retcd ) );
		memset( s_key, 0x00, sizeof( s_key ) );    
      
    fpub_InitSoComp(lXmlhandle); 
    
#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif
  

    COMP_PARACOUNTCHKMIN(4);
    memset(sSrcEleNode, 0x00, sizeof(sSrcEleNode));
    memset(sDesEleNode, 0x00, sizeof(sDesEleNode));
    memset(sKey, 0x00, sizeof(sKey));  
    memset(sFlag, 0x00, sizeof(sFlag));  
    memset(sMsg, 0x00, sizeof(sMsg));
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "Դ���Ľڵ�");
    pstrcopy(sSrcEleNode, sBuf, sizeof(sSrcEleNode));  
    trim(sSrcEleNode);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "KEYֵ");
    pstrcopy(sKey, sBuf, sizeof(sKey));  
    trim(sKey);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "Ŀ�걨�����ݽڵ�");
    pstrcopy(sDesEleNode, sBuf, sizeof(sDesEleNode));  
    trim(sDesEleNode);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(4, sBuf, "������ʶ");
    pstrcopy(sFlag, sBuf, sizeof(sFlag));  
    trim(sFlag);
    
    COMP_SOFTGETXML(sSrcEleNode,sMsg);//ȡԴ����
    LOG(LM_DEBUG, Fmtmsg("Դ����Ϊ[%s]", sMsg), "��ӡԴ����")
    
    	/*
			 **	����debug��ʶ
	     **	����ԭ�ͣ�void ORG_DEBUG( int i_api_debug )
	     **	(1) �������øú�������Ĭ��Ϊ0�������������Ϣ
	     **	(2) ����Ϊ��0ֵ�����������Ϣ
	    */
	  ORG_DEBUG( DEBUG_STATUS );
	
    if (sFlag[0] == '0')  //���ʽ�����Ϣ��MAC������
    {
    		strncat(sMsg, "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC", API_MAC_LEN);
    		
    		/*
				**	1������ԭʼ���ױ���(δ����ǰ�����ͨѶͷ,ֻ����Ϣ��+У����)
				*/
				strcpy( s_in_msg, sMsg );
	  		
				l_in_len = strlen( s_in_msg );
	  		
	  		
				/*
				**	2������MAC����������Ϣ��MACУ��λ
				*/
				ORG_MAC( s_in_msg, &l_in_len, s_mac, s_retcd );
	  		
				if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
				{
					/* ����MACʧ�ܣ������ڲ����� ... */
				  fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10001, Fmtmsg("����MACʧ��"));
    		  LOG(LM_STD,Fmtmsg("����MACʧ��"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
				}
	  		
	  		
				/* ������Ϣ��MACУ��λ */
				memcpy( s_in_msg + l_in_len - API_MAC_LEN, s_mac, API_MAC_LEN );
	  		LOG(LM_DEBUG, Fmtmsg("[��������У����ɹ�][MAC|%s]",s_mac), "[INFO]")
	  		
				/*
				**	3�����ܣ���������Ϣ����
				*/
				strcpy( s_key, sKey );
	  		
				ORG_TXN_CRYPT(	s_key, API_ACTCD_ENC, s_in_msg, &l_in_len, s_out_msg, &l_out_len, s_retcd );
	  		
				if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
				{
					/* ������Ϣ��ʧ�ܣ������ڲ����� ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("��������Ϣ��ʧ��"));
    		  LOG(LM_STD,Fmtmsg("������Ϣ��ʧ��"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
				}
	  		
				/* ���ܺ�����Ϣ�����򣬹�������ͨѶ���� *//*�ò�������GXP����*/
				/*sprintf( s_snd_msg, "%c%cC%08d%s%c",
				 * 0xef, 0x14, l_out_len + 9, s_out_msg, 0x00 );
	 			 *		
				 * l_snd_len = strlen( s_snd_msg );
				 */
	
				/*
				**	4��ͨ��socket/�м�����������ո�����,�ò�������GXP�����˴�����ʵ��
				*/
				/* ����ǰ���� 0xef0x14+ͨѶͷ+��Ϣ��+У���� ... */  
				
				COMP_SOFTSETXML(sDesEleNode, s_out_msg);  //�����Ĵ���Ŀ��ڵ�
				LOG(LM_DEBUG, Fmtmsg("���ļ��ܳɹ�[%s]", s_out_msg), "��ӡ���ܺ�ı���")  
					
    }/* end of ���ʽ�����Ϣ��MAC������ */
    else if (sFlag[0] == '1') //���ʽ�����Ϣ���ܡ�У��MAC
    {
				/*
				**	1��ͨ��socket/�м���Ӵ��ո����Ļ�ȡ����Ϣ
				*/
				strcpy( s_rcv_msg,  sMsg);
				
				l_rcv_len = strlen( s_rcv_msg );
				
				
				/*
				**	2������
				*/
				strcpy( s_key, sKey );
				/*l_tmp_len = l_rcv_len - 2 - 9;*/
				
				ORG_TXN_CRYPT(	s_key, API_ACTCD_DEC, s_rcv_msg, &l_rcv_len,
						s_out_msg, &l_out_len, s_retcd );
				
				if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
				{
					/* ������Ϣ��ʧ�ܣ������ڲ����� ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10001, Fmtmsg("������Ϣ��ʧ��"));
    		  LOG(LM_STD,Fmtmsg("������Ϣ��ʧ��"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
				}
				
				LOG(LM_DEBUG, Fmtmsg("[�����ѽ��ܳɹ�����������MAC��У��MAC"), "[INFO]")
				/*
				**	3������MAC����У��MAC
				*/
				ORG_MAC( s_out_msg, &l_out_len, s_mac, s_retcd );
				
				if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
				{
					/* ����MACʧ�ܣ������ڲ����� ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10001, Fmtmsg("����MACʧ��"));
    		  LOG(LM_STD,Fmtmsg("����MACʧ��"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
				}
				
				LOG(LM_DEBUG, Fmtmsg("[����MAC�ɹ�������У��MAC"), "[INFO]")
				
				if( strcmp( s_out_msg + l_out_len - API_MAC_LEN, s_mac ) != 0 )
				{
					/* MACУ��ʧ�ܣ������ڲ����� ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10001, Fmtmsg("MACУ��ʧ��"));
    		  LOG(LM_STD,Fmtmsg("MACУ�鲻ͨ��"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
				}
				
				s_out_msg[ l_out_len - API_MAC_LEN ] = '\0'; //ֻȡ��Ϣ��
				COMP_SOFTSETXML(sDesEleNode, s_out_msg);  //�ѽ��ܺ�ı��Ĵ���Ŀ��ڵ㣬ֻ����Ϣ��
				LOG(LM_DEBUG, Fmtmsg("���Ľ��ܲ���MAC�ɹ�[%s]", s_out_msg), "��ӡ���ܺ�ı���") 
				
				/*
				**	4��MACУ��ɹ������ĺϷ�����ҵ�����ڲ�ҵ���߼�����
				*/
				/* �ڲ�ҵ���߼��������̣������ⱨ�ģ��Ǽ����ݿ�� ... */    	
    }/* end of ���ʽ�����Ϣ���ܡ�У��MAC */
    else
    {
    			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10001, Fmtmsg("�޷�ʶ��Ĳ�����ʶ"));
    		  LOG(LM_STD,Fmtmsg("������ʶ����"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
    }
    
    #ifdef DEBUG
  		LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
		#endif

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
	
}/* end of JZDSF_TxnEec_Dec() */

/************************************************************************
  ��̬�����������
  �����������: JZDSF_FileEec_Dec
  �������: ���д��ո�-�ļ�������Ϣ��MAC�����ܡ����ܡ�У��MAC

  �������: 
  ���ļ�������Ϣ��MAC�����ܡ����ܡ�У��MAC
  �������: 
  ��� ��������              ��Դ���       ȱʡֵ          �Ƿ�ɿ�  ����˵��
  1    Դ�ļ�·�����ļ���    XML�����ַ���                  ����Ϊ��  Դ�ļ�������ʱ�ļ�ͷ���ļ����������MAC���ļ��������·������ѹʱԴ�ļ������/home/gapsv4/file/jzdsf/batch/Ŀ¼��
  2    �ӽ������õ�KEYֵ     XML�����ַ���                  ����Ϊ��  �ӽ������õ�KEYֵ
  3    Ŀ���ļ��ڵ�          XML���ݽڵ�                    ����Ϊ��  Ŀ���ļ��ڵ� �����ص��ļ�������·���������Դ�ļ���ͬ��Ŀ¼�£�
  4    ������ʶ              XML�����ַ���   0              ����Ϊ��  0-��MAC���ܼ�ѹ��1-��ѹ���ܲ�У��MAC

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����
  ��

  �� Ŀ ��: 
  �� �� Ա: liurj
  ��������: 2018��09��10��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: [/req/srcfile] 123456 /desfile 0
 ************************************************************************/
IRESULT JZDSF_FileEec_Dec(HXMLTREE lXmlhandle)
{
    int iParas;
    char sSrcFile[ API_FILE_NAME_LEN + 1 ];       //Դ�ļ�
    char sDesEleNode[ 128 + 1 ];   //Ŀ���ļ����ݽڵ�
    char sKey[ API_KEY_LEN	+ 1 ];          //KEYֵ
    char sFlag[ 2 ];                        //������ʶ   
    char sBuf[256];    
    
  	char	s_line		[ API_MAX_MSG_LEN	+ 1 ];
  	char	s_mac		[ API_MAC_LEN		+ 1 ];
  	char	s_retcd		[ API_RETCD_LEN		+ 1 ];
  	char	s_key		[ API_KEY_LEN		+ 1 ];
  	char	s_file_path	[ API_FILE_NAME_LEN	+ 1 ];
  	char	s_in_file	[ API_FILE_NAME_LEN	+ 1 ];
  	char	s_tmp_file	[ API_FILE_NAME_LEN	+ 1 ];
  	char	s_out_file	[ API_FILE_NAME_LEN	+ 1 ];
  	
  	long	l_line_len = 0L;
  	
  	FILE	*fp_r = NULL;
  	FILE	*fp_w = NULL;
  	FILE	*fp = NULL;
  	
  	memset( s_line, 0x00, sizeof( s_line ) );
  	memset( s_mac, 0x00, sizeof( s_mac ) );
  	memset( s_retcd, 0x00, sizeof( s_retcd ) );
  	memset( s_key, 0x00, sizeof( s_key ) );
  	memset( s_file_path, 0x00, sizeof( s_file_path ) );
  	memset( s_in_file, 0x00, sizeof( s_in_file ) );
  	memset( s_tmp_file, 0x00, sizeof( s_tmp_file ) );
  	memset( s_out_file, 0x00, sizeof( s_out_file ) );    
 
      
    fpub_InitSoComp(lXmlhandle); 
    
#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif
  

    COMP_PARACOUNTCHKMIN(4);
    memset(sSrcFile, 0x00, sizeof(sSrcFile));
    memset(sDesEleNode, 0x00, sizeof(sDesEleNode));
    memset(sKey, 0x00, sizeof(sKey));  
    memset(sFlag, 0x00, sizeof(sFlag));  
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "Դ�ļ�");
    pstrcopy(sSrcFile, sBuf, sizeof(sSrcFile));  
    trim(sSrcFile);
    LOG(LM_DEBUG, Fmtmsg("Դ�ļ�Ϊ[%s]", sSrcFile), "��ӡԴ�ļ�λ��")	
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "KEYֵ");
    pstrcopy(sKey, sBuf, sizeof(sKey));  
    trim(sKey);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "Ŀ���ļ����ݽڵ�");
    pstrcopy(sDesEleNode, sBuf, sizeof(sDesEleNode));  
    trim(sDesEleNode);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(4, sBuf, "������ʶ");
    pstrcopy(sFlag, sBuf, sizeof(sFlag));  
    trim(sFlag);
 
    	/*
			 **	����debug��ʶ
	     **	����ԭ�ͣ�void ORG_DEBUG( int i_api_debug )
	     **	(1) �������øú�������Ĭ��Ϊ0�������������Ϣ
	     **	(2) ����Ϊ��0ֵ�����������Ϣ
	    */
	  ORG_DEBUG( DEBUG_STATUS ); 
    
    if (sFlag[0] == '0')  //�ļ�������Ϣ��MAC�����ܡ���ѹ
    {
				/*
				**	1�����콻���ļ�
				*/
				strcpy( s_file_path, "/home/gapsv4/file/jzdsf/batch/" );
				strcpy( s_in_file, sSrcFile );
				
				strncpy( s_tmp_file, s_in_file, strlen( s_in_file ) - 8 );
				strcat( s_tmp_file, "0000temp" );
				
				
				/*
				**	2��ѭ����ȡ�ļ�����MAC����
				*/
				if( ( fp_r = fopen( s_in_file, "r" ) ) == NULL )
				{
					/* ���ļ�ʧ�ܣ������ڲ����� ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("��Դ�ļ�ʧ��"));
    		  LOG(LM_STD,Fmtmsg("��Դ�ļ�ʧ��[%s]",s_in_file), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
				}
				
				if( ( fp_w = fopen( s_tmp_file, "w+" ) ) == NULL )
				{
					/* ���ļ�ʧ�ܣ������ڲ����� ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("����ʱ�ļ�ʧ��"));
    		  LOG(LM_STD,Fmtmsg("����ʱ�ļ�ʧ��[%s]",s_tmp_file), fpub_GetCompname(lXmlhandle) )     		  
					fclose( fp_r );
					return COMPRET_FAIL;
				}
				
				while( !feof( fp_r ) )
				{
					/* ��ʼ�� */
					memset( s_line, 0x00, sizeof( s_line ) );
					memset( s_mac, 0x00, sizeof( s_mac ) );
					memset( s_retcd, 0x00, sizeof( s_retcd ) );
					l_line_len = 0;
					
					/* ���ļ��ж�ȡһ����Ϣ */
					fgets( s_line, API_MAX_MSG_LEN, fp_r );
					
					l_line_len = strlen( s_line );
					
					if( l_line_len == 0 )
					{
						continue;
					}
					
					/* �ļ����� DOS ���з�(0x0d0x0a)��β */
					if(		( s_line[ l_line_len - 1 ] == 0x0a )
						&& 	( s_line[ l_line_len - 2 ] == 0x0d )
						&&	( l_line_len > 1 )			)
					{
						s_line[ l_line_len - 1 ] = 0x00;
						s_line[ l_line_len - 2 ] = 0x00;
					}
					/* �ļ����� UNIX ���з�("\n")��β */
					else if ( s_line[ l_line_len - 1 ] == '\n' )
					{
						s_line[ l_line_len - 1 ] = 0x00;
					}
					
					strncat( s_line, "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC", API_MAC_LEN ); //ƴMAC
					l_line_len = strlen( s_line );
					
					/* ����MAC */
					ORG_MAC( s_line, &l_line_len, s_mac, s_retcd );
					
					if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
					{
						/* ����MACʧ�ܣ������ڲ����� ... */
						fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  	fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("����MACʧ��"));
    		  	LOG(LM_STD,Fmtmsg("����MACʧ��[%s]",s_tmp_file), fpub_GetCompname(lXmlhandle) )
						fclose( fp_r );
						fclose( fp_w );
						remove( s_tmp_file );
						return COMPRET_FAIL;
					}
					
					/* ����MACУ��λ */
					memcpy( s_line + l_line_len - API_MAC_LEN, s_mac, API_MAC_LEN );
					
					/* д����ʱ�ļ��� */
					fprintf( fp_w, "%s%c%c", s_line, 0x0d, 0x0a );
					fflush( fp_w );
				}
				
				fclose( fp_r );
				fclose( fp_w );
				
				
				/*
				**	3���ļ����ܼ�ѹ
				*/
				strcpy( s_key, sKey );
				
				ORG_FILE_CRYPT(	s_key, API_ACTCD_ENC, s_tmp_file, s_out_file, s_retcd );
				
				if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
				{
					/* �ļ����ܼ�ѹʧ�ܣ������ڲ����� ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("�ļ����ܼ�ѹʧ��"));
    		  LOG(LM_STD,Fmtmsg("�ļ����ܼ�ѹʧ��[%s]",s_tmp_file), fpub_GetCompname(lXmlhandle) )
					remove( s_tmp_file );
					return COMPRET_FAIL;
				}
				
				/* ɾ����ʱ�ļ� */
				remove( s_tmp_file );
				COMP_SOFTSETXML(sDesEleNode, s_out_file);
				LOG(LM_DEBUG, Fmtmsg("�ļ���MAC���ܼ�ѹ�ɹ������ļ�Ϊ[%s]", s_out_file), "�����ļ���")	
				   	
    }/* end of �ļ�������Ϣ��MAC�����ܡ���ѹ */
    else if (sFlag[0] == '1') //�ļ�������Ϣ��ѹ�����ܡ�У��MAC
    {
				/*
				**	1�����մ��ո����Ļ�Ӧ�ļ��������ļ�
				*/
				strcpy( s_file_path, "/home/gapsv4/file/jzdsf/batch/" );
				strcpy( s_in_file, sSrcFile );
				
				
				/*
				**	2���ļ���ѹ����
				*/
				strcpy( s_key, sKey );
				
				ORG_FILE_CRYPT(	s_key, API_ACTCD_DEC, s_in_file, s_out_file, s_retcd );
				
				if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
				{
					/* �ļ���ѹ����ʧ�ܣ������ڲ����� ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("�ļ���ѹ����ʧ��"));
    		  LOG(LM_STD,Fmtmsg("�ļ���ѹ����ʧ��[%s]",s_in_file), fpub_GetCompname(lXmlhandle))
					return COMPRET_FAIL;
				}
				
				LOG(LM_DEBUG, Fmtmsg("�ļ���ѹ���ܳɹ�����������MAC[%s]", s_out_file), "[INFO]")	
				
				/*
				**	3��ѭ����ȡ�ļ���У��MAC��������MAC��д�����ļ�
				*/
				strcat( s_file_path, s_out_file );
				
				strcpy( s_tmp_file, s_file_path );
				strcat( s_tmp_file, "_NoMac" );    //������MAC���ļ�
				
				if( ( fp = fopen( s_file_path, "r" ) ) == NULL )
				{
					/* ���ļ�ʧ�ܣ������ڲ����� ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("���ļ�ʧ��"));
    		  LOG(LM_STD,Fmtmsg("���ļ�ʧ��[%s]",s_file_path), fpub_GetCompname(lXmlhandle))
					return COMPRET_FAIL;
				}
				
				if( ( fp_w = fopen( s_tmp_file, "w+" ) ) == NULL )
				{
					/* ���ļ�ʧ�ܣ������ڲ����� ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("���ļ�ʧ��"));
    		  LOG(LM_STD,Fmtmsg("���ļ�ʧ��[%s]",s_tmp_file), fpub_GetCompname(lXmlhandle))				
					fclose( fp );
					return COMPRET_FAIL;
				}
				
				while( !feof( fp ) )
				{
					/* ��ʼ�� */
					memset( s_line, 0x00, sizeof( s_line ) );
					memset( s_mac, 0x00, sizeof( s_mac ) );
					memset( s_retcd, 0x00, sizeof( s_retcd ) );
					l_line_len = 0;
					
					/* ���ļ��ж�ȡһ����Ϣ */
					fgets( s_line, API_MAX_MSG_LEN, fp );
					
					l_line_len = strlen( s_line );
					
					if( l_line_len == 0 )
					{
						continue;
					}
					
					/* �ļ����� DOS ���з�(0x0d0x0a)��β */
					if(		( s_line[ l_line_len - 1 ] == 0x0a )
						&& 	( s_line[ l_line_len - 2 ] == 0x0d )
						&&	( l_line_len > 1 )			)
					{
						s_line[ l_line_len - 1 ] = 0x00;
						s_line[ l_line_len - 2 ] = 0x00;
					}
					/* �ļ����� UNIX ���з�("\n")��β */
					else if ( s_line[ l_line_len - 1 ] == '\n' )
					{
						s_line[ l_line_len - 1 ] = 0x00;
					}
					
					l_line_len = strlen( s_line );
					
					/* ����MAC */
					ORG_MAC( s_line, &l_line_len, s_mac, s_retcd );
					
					if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
					{
						/* ����MACʧ�ܣ������ڲ����� ... */
						fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  	fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("����MACʧ��"));
    		  	LOG(LM_STD,Fmtmsg("����MACʧ��[%s]"), fpub_GetCompname(lXmlhandle))
						fclose( fp );
						fclose( fp_w );
						remove( s_tmp_file );
						return COMPRET_FAIL;
					}
					
					/* У��MAC */
					if( strcmp( s_line + l_line_len - API_MAC_LEN, s_mac ) != 0 )
					{
						/* MACУ��ʧ�ܣ������ڲ����� ... */
						fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  	fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("MACУ��ʧ��"));
    		  	LOG(LM_STD,Fmtmsg("MACУ�鲻ͨ��"), fpub_GetCompname(lXmlhandle))
						fclose( fp );
						fclose( fp_w );
						remove( s_tmp_file );
						return COMPRET_FAIL;
					}
					
					/* ����MACУ��λ */
					s_line[ l_line_len - API_MAC_LEN ] = '\0';
					
					/* д����ʱ�ļ��� */
					fprintf( fp_w, "%s\n", s_line);
					fflush( fp_w );
				}
				
				fclose( fp );
				fclose( fp_w );
				
				/* ɾ������MACУ����Ľ��ܺ���ļ� */
				remove( s_file_path );
				
				/* �Ѷ���MACУ������ļ������� */
				strcat( s_out_file, "_NoMac" );
				COMP_SOFTSETXML(sDesEleNode, s_out_file);
				LOG(LM_DEBUG, Fmtmsg("�ļ���ѹ���ܲ�У��MAC�ɹ������Ѷ���У���룬���ļ�Ϊ[%s]", s_out_file), "�����ļ���")
					    	
    }/* end of �ļ�������Ϣ��ѹ�����ܡ�У��MAC */
    else
    {
    			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10001, Fmtmsg("�޷�ʶ��Ĳ�����ʶ"));
    		  LOG(LM_STD,Fmtmsg("������ʶ����"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
    }
            
    #ifdef DEBUG
  		LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
		#endif

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;    
    
}/* end of JZDSF_FileEec_Dec() */
    


