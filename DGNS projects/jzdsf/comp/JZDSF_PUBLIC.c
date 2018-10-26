/********************************************************************
  版权所有:恒生电子股份有限公司
  项目名称:综合应用平台（GAPS）项目
  版    本:V1.0.00
  操作系统:LIUNX64
  文件名称:JZDSF_PUBLIC.c
  文件描述:集中代收付公共组件
  项 目 组:
  程 序 员:liurj
  发布日期:20180910
  修    订:
  修改日期:  
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
#define API_RETCD_SUC		"000"	/* SUCCESS 正常 */
#define API_RETCD_FAL		"102"	/* FAILURE 失败 */

/*
**	Actions Code
*/
#define API_ACTCD_ENC		0	/* ENCRYPT 加密加压 */
#define API_ACTCD_DEC		1	/* DECRYPT 解密解压 */

/*
**	Constant Length
*/
#define API_MAX_MSG_LEN		9999
#define API_FILE_NAME_LEN	150

#define API_MAC_LEN		64
#define API_KEY_LEN		24
#define API_RETCD_LEN		3
#define DEBUG_STATUS  0    /* 0-API不输出调试日志，非0-API会输出调试信息 */

/*
   注：本函数为组件库公共函数,用于在发布状态下显示内部版本信息
       在生产环境下，每次更新均应修改版本号、填入相应信息
*/
int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>"
     "<root>"
             "<soname>CUSTOM_PUBLIC_DRC.so</soname>"
             "<sosrcname>CUSTOM_PUBLIC_DRC.c</sosrcname>"
             "<sonote>集中代收付公共组件</sonote>"
             "<version>"
               "<rec ver=\"1.0.00\" modify=\"2018-09-10 17:18:33\" programer=\"[刘如杰]\" filesize=\"FILE\">初始发布版</rec>"
             "</version>"
     "</root>";
  printf("\n================动态组件基本信息================\n");
  printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
  printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
  printf("%s-%s\n",__PROJECTSNAME,__VERSION);
  if (strlen(sversion) >= isize)
  {
        printf(" -->取详细信息失败...\n");
        return -2;
  }
        strcpy(sinfo,sversion);
        printf(" -->请查看详细信息...\n");
  return 0;
}


/************************************************************************
  动态组件函数定义
  组件函数名称: JZDSF_TxnEec
  组件名称: 集中代收付-单笔交易信息加MAC、加密、解密、校验MAC

  组件功能: 
  对实时单笔交易信息加MAC、加密、解密、校验MAC
  组件参数: 
  序号 参数名称              资源类别       缺省值          是否可空  参数说明
  1    源报文节点            XML数据节点    /commbuf       不可为空  源报文，加密时传入信息体，解密时传入信息体+校验码
  2    加解密所用的KEY值     XML解析字符串                 不可为空  加解密所用的KEY值
  3    目标报文节点          XML数据节点    /commbuf       不可为空  目标报文节点
  4    操作标识              XML解析字符串   0             不可为空  0-加MAC加密，1-解密并校验MAC

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作
  无

  项 目 组: 
  程 序 员: liurj
  发布日期: 2018年09月10日
  修改日期: 
  修改日期: 
  参数使用示例: /commbuf 123456 /commbuf 0
 ************************************************************************/
IRESULT JZDSF_TxnEec_Dec(HXMLTREE lXmlhandle)
{
    int iParas;
    char sSrcEleNode[ 128 + 1 ];   //源报文数据节点
    char sDesEleNode[ 128 + 1 ];   //目标报文数据节点
    char sKey[ API_KEY_LEN	+ 1 ];          //KEY值
    char sFlag[ 2 ];                        //操作标识
    char sMsg[ API_MAX_MSG_LEN	+ 1 ];      //用于存报文
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
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif
  

    COMP_PARACOUNTCHKMIN(4);
    memset(sSrcEleNode, 0x00, sizeof(sSrcEleNode));
    memset(sDesEleNode, 0x00, sizeof(sDesEleNode));
    memset(sKey, 0x00, sizeof(sKey));  
    memset(sFlag, 0x00, sizeof(sFlag));  
    memset(sMsg, 0x00, sizeof(sMsg));
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "源报文节点");
    pstrcopy(sSrcEleNode, sBuf, sizeof(sSrcEleNode));  
    trim(sSrcEleNode);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "KEY值");
    pstrcopy(sKey, sBuf, sizeof(sKey));  
    trim(sKey);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "目标报文数据节点");
    pstrcopy(sDesEleNode, sBuf, sizeof(sDesEleNode));  
    trim(sDesEleNode);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(4, sBuf, "操作标识");
    pstrcopy(sFlag, sBuf, sizeof(sFlag));  
    trim(sFlag);
    
    COMP_SOFTGETXML(sSrcEleNode,sMsg);//取源报文
    LOG(LM_DEBUG, Fmtmsg("源报文为[%s]", sMsg), "打印源报文")
    
    	/*
			 **	设置debug标识
	     **	函数原型：void ORG_DEBUG( int i_api_debug )
	     **	(1) 若不调用该函数，则默认为0，不输出调试信息
	     **	(2) 设置为非0值，输出调试信息
	    */
	  ORG_DEBUG( DEBUG_STATUS );
	
    if (sFlag[0] == '0')  //单笔交易信息加MAC、加密
    {
    		strncat(sMsg, "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC", API_MAC_LEN);
    		
    		/*
				**	1、构造原始交易报文(未包括前导码和通讯头,只有信息体+校验码)
				*/
				strcpy( s_in_msg, sMsg );
	  		
				l_in_len = strlen( s_in_msg );
	  		
	  		
				/*
				**	2、生成MAC，并附在信息串MAC校验位
				*/
				ORG_MAC( s_in_msg, &l_in_len, s_mac, s_retcd );
	  		
				if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
				{
					/* 生成MAC失败，进行内部处理 ... */
				  fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10001, Fmtmsg("生成MAC失败"));
    		  LOG(LM_STD,Fmtmsg("生成MAC失败"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
				}
	  		
	  		
				/* 重置信息串MAC校验位 */
				memcpy( s_in_msg + l_in_len - API_MAC_LEN, s_mac, API_MAC_LEN );
	  		LOG(LM_DEBUG, Fmtmsg("[报文增加校验码成功][MAC|%s]",s_mac), "[INFO]")
	  		
				/*
				**	3、加密，并重置信息长度
				*/
				strcpy( s_key, sKey );
	  		
				ORG_TXN_CRYPT(	s_key, API_ACTCD_ENC, s_in_msg, &l_in_len, s_out_msg, &l_out_len, s_retcd );
	  		
				if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
				{
					/* 加密信息串失败，进行内部处理 ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("生加密信息串失败"));
    		  LOG(LM_STD,Fmtmsg("加密信息串失败"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
				}
	  		
				/* 加密后，置信息长度域，构造完整通讯报文 *//*该部分已在GXP处理*/
				/*sprintf( s_snd_msg, "%c%cC%08d%s%c",
				 * 0xef, 0x14, l_out_len + 9, s_out_msg, 0x00 );
	 			 *		
				 * l_snd_len = strlen( s_snd_msg );
				 */
	
				/*
				**	4、通过socket/中间件发送至代收付中心,该部分已在GXP处理，此处无需实现
				*/
				/* 发送前导码 0xef0x14+通讯头+信息体+校验码 ... */  
				
				COMP_SOFTSETXML(sDesEleNode, s_out_msg);  //把密文存至目标节点
				LOG(LM_DEBUG, Fmtmsg("报文加密成功[%s]", s_out_msg), "打印加密后的报文")  
					
    }/* end of 单笔交易信息加MAC、加密 */
    else if (sFlag[0] == '1') //单笔交易信息解密、校验MAC
    {
				/*
				**	1、通过socket/中间件从代收付中心获取到信息
				*/
				strcpy( s_rcv_msg,  sMsg);
				
				l_rcv_len = strlen( s_rcv_msg );
				
				
				/*
				**	2、解密
				*/
				strcpy( s_key, sKey );
				/*l_tmp_len = l_rcv_len - 2 - 9;*/
				
				ORG_TXN_CRYPT(	s_key, API_ACTCD_DEC, s_rcv_msg, &l_rcv_len,
						s_out_msg, &l_out_len, s_retcd );
				
				if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
				{
					/* 解密信息串失败，进行内部处理 ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10001, Fmtmsg("解密信息串失败"));
    		  LOG(LM_STD,Fmtmsg("解密信息串失败"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
				}
				
				LOG(LM_DEBUG, Fmtmsg("[报文已解密成功，即将生成MAC并校验MAC"), "[INFO]")
				/*
				**	3、生成MAC，并校验MAC
				*/
				ORG_MAC( s_out_msg, &l_out_len, s_mac, s_retcd );
				
				if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
				{
					/* 生成MAC失败，进行内部处理 ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10001, Fmtmsg("生成MAC失败"));
    		  LOG(LM_STD,Fmtmsg("生成MAC失败"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
				}
				
				LOG(LM_DEBUG, Fmtmsg("[生成MAC成功，即将校验MAC"), "[INFO]")
				
				if( strcmp( s_out_msg + l_out_len - API_MAC_LEN, s_mac ) != 0 )
				{
					/* MAC校验失败，进行内部处理 ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10001, Fmtmsg("MAC校验失败"));
    		  LOG(LM_STD,Fmtmsg("MAC校验不通过"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
				}
				
				s_out_msg[ l_out_len - API_MAC_LEN ] = '\0'; //只取信息体
				COMP_SOFTSETXML(sDesEleNode, s_out_msg);  //把解密后的报文存至目标节点，只有信息体
				LOG(LM_DEBUG, Fmtmsg("报文解密并验MAC成功[%s]", s_out_msg), "打印解密后的报文") 
				
				/*
				**	4、MAC校验成功，报文合法，企业进行内部业务逻辑处理
				*/
				/* 内部业务逻辑处理流程，例如拆解报文，登记数据库等 ... */    	
    }/* end of 单笔交易信息解密、校验MAC */
    else
    {
    			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10001, Fmtmsg("无法识别的操作标识"));
    		  LOG(LM_STD,Fmtmsg("操作标识错误"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
    }
    
    #ifdef DEBUG
  		LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
		#endif

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
	
}/* end of JZDSF_TxnEec_Dec() */

/************************************************************************
  动态组件函数定义
  组件函数名称: JZDSF_FileEec_Dec
  组件名称: 集中代收付-文件交易信息加MAC、加密、解密、校验MAC

  组件功能: 
  对文件交易信息加MAC、加密、解密、校验MAC
  组件参数: 
  序号 参数名称              资源类别       缺省值          是否可空  参数说明
  1    源文件路径及文件名    XML解析字符串                  不可为空  源文件，加密时文件头、文件体无需包含MAC，文件名需绝对路径，解压时源文件需放在/home/gapsv4/file/jzdsf/batch/目录下
  2    加解密所用的KEY值     XML解析字符串                  不可为空  加解密所用的KEY值
  3    目标文件节点          XML数据节点                    不可为空  目标文件节点 （返回的文件名不带路径，存放在源文件相同的目录下）
  4    操作标识              XML解析字符串   0              不可为空  0-加MAC加密加压，1-解压解密并校验MAC

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作
  无

  项 目 组: 
  程 序 员: liurj
  发布日期: 2018年09月10日
  修改日期: 
  修改日期: 
  参数使用示例: [/req/srcfile] 123456 /desfile 0
 ************************************************************************/
IRESULT JZDSF_FileEec_Dec(HXMLTREE lXmlhandle)
{
    int iParas;
    char sSrcFile[ API_FILE_NAME_LEN + 1 ];       //源文件
    char sDesEleNode[ 128 + 1 ];   //目标文件数据节点
    char sKey[ API_KEY_LEN	+ 1 ];          //KEY值
    char sFlag[ 2 ];                        //操作标识   
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
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif
  

    COMP_PARACOUNTCHKMIN(4);
    memset(sSrcFile, 0x00, sizeof(sSrcFile));
    memset(sDesEleNode, 0x00, sizeof(sDesEleNode));
    memset(sKey, 0x00, sizeof(sKey));  
    memset(sFlag, 0x00, sizeof(sFlag));  
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "源文件");
    pstrcopy(sSrcFile, sBuf, sizeof(sSrcFile));  
    trim(sSrcFile);
    LOG(LM_DEBUG, Fmtmsg("源文件为[%s]", sSrcFile), "打印源文件位置")	
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "KEY值");
    pstrcopy(sKey, sBuf, sizeof(sKey));  
    trim(sKey);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "目标文件数据节点");
    pstrcopy(sDesEleNode, sBuf, sizeof(sDesEleNode));  
    trim(sDesEleNode);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(4, sBuf, "操作标识");
    pstrcopy(sFlag, sBuf, sizeof(sFlag));  
    trim(sFlag);
 
    	/*
			 **	设置debug标识
	     **	函数原型：void ORG_DEBUG( int i_api_debug )
	     **	(1) 若不调用该函数，则默认为0，不输出调试信息
	     **	(2) 设置为非0值，输出调试信息
	    */
	  ORG_DEBUG( DEBUG_STATUS ); 
    
    if (sFlag[0] == '0')  //文件交易信息加MAC、加密、加压
    {
				/*
				**	1、构造交易文件
				*/
				strcpy( s_file_path, "/home/gapsv4/file/jzdsf/batch/" );
				strcpy( s_in_file, sSrcFile );
				
				strncpy( s_tmp_file, s_in_file, strlen( s_in_file ) - 8 );
				strcat( s_tmp_file, "0000temp" );
				
				
				/*
				**	2、循环读取文件，加MAC处理
				*/
				if( ( fp_r = fopen( s_in_file, "r" ) ) == NULL )
				{
					/* 打开文件失败，进行内部处理 ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("打开源文件失败"));
    		  LOG(LM_STD,Fmtmsg("打开源文件失败[%s]",s_in_file), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
				}
				
				if( ( fp_w = fopen( s_tmp_file, "w+" ) ) == NULL )
				{
					/* 打开文件失败，进行内部处理 ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("打开临时文件失败"));
    		  LOG(LM_STD,Fmtmsg("打开临时文件失败[%s]",s_tmp_file), fpub_GetCompname(lXmlhandle) )     		  
					fclose( fp_r );
					return COMPRET_FAIL;
				}
				
				while( !feof( fp_r ) )
				{
					/* 初始化 */
					memset( s_line, 0x00, sizeof( s_line ) );
					memset( s_mac, 0x00, sizeof( s_mac ) );
					memset( s_retcd, 0x00, sizeof( s_retcd ) );
					l_line_len = 0;
					
					/* 从文件中读取一行信息 */
					fgets( s_line, API_MAX_MSG_LEN, fp_r );
					
					l_line_len = strlen( s_line );
					
					if( l_line_len == 0 )
					{
						continue;
					}
					
					/* 文件行以 DOS 换行符(0x0d0x0a)结尾 */
					if(		( s_line[ l_line_len - 1 ] == 0x0a )
						&& 	( s_line[ l_line_len - 2 ] == 0x0d )
						&&	( l_line_len > 1 )			)
					{
						s_line[ l_line_len - 1 ] = 0x00;
						s_line[ l_line_len - 2 ] = 0x00;
					}
					/* 文件行以 UNIX 换行符("\n")结尾 */
					else if ( s_line[ l_line_len - 1 ] == '\n' )
					{
						s_line[ l_line_len - 1 ] = 0x00;
					}
					
					strncat( s_line, "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC", API_MAC_LEN ); //拼MAC
					l_line_len = strlen( s_line );
					
					/* 生成MAC */
					ORG_MAC( s_line, &l_line_len, s_mac, s_retcd );
					
					if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
					{
						/* 生成MAC失败，进行内部处理 ... */
						fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  	fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("生成MAC失败"));
    		  	LOG(LM_STD,Fmtmsg("生成MAC失败[%s]",s_tmp_file), fpub_GetCompname(lXmlhandle) )
						fclose( fp_r );
						fclose( fp_w );
						remove( s_tmp_file );
						return COMPRET_FAIL;
					}
					
					/* 重置MAC校验位 */
					memcpy( s_line + l_line_len - API_MAC_LEN, s_mac, API_MAC_LEN );
					
					/* 写入临时文件中 */
					fprintf( fp_w, "%s%c%c", s_line, 0x0d, 0x0a );
					fflush( fp_w );
				}
				
				fclose( fp_r );
				fclose( fp_w );
				
				
				/*
				**	3、文件加密加压
				*/
				strcpy( s_key, sKey );
				
				ORG_FILE_CRYPT(	s_key, API_ACTCD_ENC, s_tmp_file, s_out_file, s_retcd );
				
				if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
				{
					/* 文件加密加压失败，进行内部处理 ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("文件加密加压失败"));
    		  LOG(LM_STD,Fmtmsg("文件加密加压失败[%s]",s_tmp_file), fpub_GetCompname(lXmlhandle) )
					remove( s_tmp_file );
					return COMPRET_FAIL;
				}
				
				/* 删除临时文件 */
				remove( s_tmp_file );
				COMP_SOFTSETXML(sDesEleNode, s_out_file);
				LOG(LM_DEBUG, Fmtmsg("文件加MAC加密加压成功，新文件为[%s]", s_out_file), "打结果文件名")	
				   	
    }/* end of 文件交易信息加MAC、加密、加压 */
    else if (sFlag[0] == '1') //文件交易信息解压、解密、校验MAC
    {
				/*
				**	1、接收代收付中心回应文件或其它文件
				*/
				strcpy( s_file_path, "/home/gapsv4/file/jzdsf/batch/" );
				strcpy( s_in_file, sSrcFile );
				
				
				/*
				**	2、文件解压解密
				*/
				strcpy( s_key, sKey );
				
				ORG_FILE_CRYPT(	s_key, API_ACTCD_DEC, s_in_file, s_out_file, s_retcd );
				
				if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
				{
					/* 文件解压解密失败，进行内部处理 ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("文件解压解密失败"));
    		  LOG(LM_STD,Fmtmsg("文件解压解密失败[%s]",s_in_file), fpub_GetCompname(lXmlhandle))
					return COMPRET_FAIL;
				}
				
				LOG(LM_DEBUG, Fmtmsg("文件解压解密成功，即将检验MAC[%s]", s_out_file), "[INFO]")	
				
				/*
				**	3、循环读取文件，校验MAC，并丢弃MAC，写入新文件
				*/
				strcat( s_file_path, s_out_file );
				
				strcpy( s_tmp_file, s_file_path );
				strcat( s_tmp_file, "_NoMac" );    //丢弃了MAC的文件
				
				if( ( fp = fopen( s_file_path, "r" ) ) == NULL )
				{
					/* 打开文件失败，进行内部处理 ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("打开文件失败"));
    		  LOG(LM_STD,Fmtmsg("打开文件失败[%s]",s_file_path), fpub_GetCompname(lXmlhandle))
					return COMPRET_FAIL;
				}
				
				if( ( fp_w = fopen( s_tmp_file, "w+" ) ) == NULL )
				{
					/* 打开文件失败，进行内部处理 ... */
					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("打开文件失败"));
    		  LOG(LM_STD,Fmtmsg("打开文件失败[%s]",s_tmp_file), fpub_GetCompname(lXmlhandle))				
					fclose( fp );
					return COMPRET_FAIL;
				}
				
				while( !feof( fp ) )
				{
					/* 初始化 */
					memset( s_line, 0x00, sizeof( s_line ) );
					memset( s_mac, 0x00, sizeof( s_mac ) );
					memset( s_retcd, 0x00, sizeof( s_retcd ) );
					l_line_len = 0;
					
					/* 从文件中读取一行信息 */
					fgets( s_line, API_MAX_MSG_LEN, fp );
					
					l_line_len = strlen( s_line );
					
					if( l_line_len == 0 )
					{
						continue;
					}
					
					/* 文件行以 DOS 换行符(0x0d0x0a)结尾 */
					if(		( s_line[ l_line_len - 1 ] == 0x0a )
						&& 	( s_line[ l_line_len - 2 ] == 0x0d )
						&&	( l_line_len > 1 )			)
					{
						s_line[ l_line_len - 1 ] = 0x00;
						s_line[ l_line_len - 2 ] = 0x00;
					}
					/* 文件行以 UNIX 换行符("\n")结尾 */
					else if ( s_line[ l_line_len - 1 ] == '\n' )
					{
						s_line[ l_line_len - 1 ] = 0x00;
					}
					
					l_line_len = strlen( s_line );
					
					/* 生成MAC */
					ORG_MAC( s_line, &l_line_len, s_mac, s_retcd );
					
					if( strcmp( s_retcd, API_RETCD_SUC ) != 0 )
					{
						/* 生成MAC失败，进行内部处理 ... */
						fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  	fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("生成MAC失败"));
    		  	LOG(LM_STD,Fmtmsg("生成MAC失败[%s]"), fpub_GetCompname(lXmlhandle))
						fclose( fp );
						fclose( fp_w );
						remove( s_tmp_file );
						return COMPRET_FAIL;
					}
					
					/* 校验MAC */
					if( strcmp( s_line + l_line_len - API_MAC_LEN, s_mac ) != 0 )
					{
						/* MAC校验失败，进行内部处理 ... */
						fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  	fpub_SetMsg(lXmlhandle, 10002, Fmtmsg("MAC校验失败"));
    		  	LOG(LM_STD,Fmtmsg("MAC校验不通过"), fpub_GetCompname(lXmlhandle))
						fclose( fp );
						fclose( fp_w );
						remove( s_tmp_file );
						return COMPRET_FAIL;
					}
					
					/* 丢弃MAC校验位 */
					s_line[ l_line_len - API_MAC_LEN ] = '\0';
					
					/* 写入临时文件中 */
					fprintf( fp_w, "%s\n", s_line);
					fflush( fp_w );
				}
				
				fclose( fp );
				fclose( fp_w );
				
				/* 删除带有MAC校验码的解密后的文件 */
				remove( s_file_path );
				
				/* 把丢弃MAC校验码的文件名返回 */
				strcat( s_out_file, "_NoMac" );
				COMP_SOFTSETXML(sDesEleNode, s_out_file);
				LOG(LM_DEBUG, Fmtmsg("文件解压解密并校验MAC成功，并已丢弃校验码，新文件为[%s]", s_out_file), "打结果文件名")
					    	
    }/* end of 文件交易信息解压、解密、校验MAC */
    else
    {
    			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    		  fpub_SetMsg(lXmlhandle, 10001, Fmtmsg("无法识别的操作标识"));
    		  LOG(LM_STD,Fmtmsg("操作标识错误"), fpub_GetCompname(lXmlhandle) ) 
    		  return COMPRET_FAIL;
    }
            
    #ifdef DEBUG
  		LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
		#endif

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;    
    
}/* end of JZDSF_FileEec_Dec() */
    


