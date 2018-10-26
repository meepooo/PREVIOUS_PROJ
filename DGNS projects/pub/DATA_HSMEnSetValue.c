#include "gaps_head.h"

/*************************************************************************
 * 函数名称: set_xml
 * 函数功能: 设置xml结点的值, 从s总截取len长度作为xml结点的值(len=0, 取到'\0')
 * 输入参数: lXmlhandle - xml树句柄
 *           xmlnode - xml结点名
 *           s - 字符串
 *           len - 长度
 *           type - 方式(0: ascii, 1: bin)
 * 输出参数: 无
 * 返回值: -99 内存不足
 *         -1  设置值失败
 *         0   成功
 * 发布日期: 2009-07-08
 * 修改日期: 2009-07-08
 * 程序员: renyh
 *
*************************************************************************/
int set_xml(HXMLTREE lXmlhandle, const char *xmlnode1, const char *xmlnode2)
{
   int len;
    int mult1 = 0, mult2 = 0;
    int attr1 = 0, attr2 = 0;
    long count, i;
    char xml1[256], xml2[256];
    char value[8192];
    char *s;
    char *xmlattr1 = NULL, *xmlattr2 = NULL;
    char *x1_1, *x1_2, *x2_1, *x2_2;
    
    LOG(LM_DEBUG, Fmtmsg("xmlnode2:[%s]", xmlnode2), "");
    s = strrchr(xmlnode1, '@');
    if (s)
    {
        attr1 = 1;
        *s = '\0';
        xmlattr1 = s+1;
    }
    s = strrchr(xmlnode2, '@');
    if (s)
    {
        attr2 = 1;
        *s = '\0';
        xmlattr2 = s+1;
    }

    s = strstr(xmlnode1, "|n");
    if (s)
    {
        *s = '\0';
        x1_1 = xmlnode1;
        x1_2 = s+2;
        mult1 = 1;
    }
    s = strstr(xmlnode2, "|n");
    if (s)
    {
        *s = '\0';
        x2_1 = xmlnode2;
        x2_2 = s+2;
        mult2 = 1;
    }

    if (mult1 != mult2)
        return -1;

    if (mult1 == 1)
    {
        LOG(LM_DEBUG, Fmtmsg("x2_1:[%s]", x2_1), "");
        count = xml_ElementCount(lXmlhandle, x2_1);
        LOG(LM_DEBUG, Fmtmsg("count:[%d]", count), "");
        if (count < 0)
            return -1;
        for (i = 1; i <= count; i++)
        {
            memset(xml1, 0, sizeof(xml1));
            snprintf(xml1, sizeof(xml1), "%s|%d%s", x1_1, i, x1_2);
            memset(xml2, 0, sizeof(xml2));
            snprintf(xml2, sizeof(xml2), "%s|%d%s", x2_1, i, x2_2);
            LOG(LM_DEBUG, Fmtmsg("xml2:[%s]", xml2), "");
            memset(value, 0, sizeof(value));
            if (attr2 == 1)
            {
                if (xml_GetElementAttr(lXmlhandle, xml2, xmlattr2, value, sizeof(value)) == -1)
                {
                    LOG(LM_DEBUG, Fmtmsg("get xml attribute value failed, node:[%s], attr:[%s]", xml2, xmlattr2), "DEBUG");
                }
            }
            else
            {
                if (xml_GetElement(lXmlhandle, xml2, value, sizeof(value)) == -1)
                {
                    LOG(LM_DEBUG, Fmtmsg("get xml node value failed, node:[%s]", xml2), "DEBUG");
                }
            }
            if (attr1 == 1)
            {
                if (xml_ElementExist(lXmlhandle, xml1) == 0)
                {
                    if (xml_SetElement(lXmlhandle, xml1, "") == -1)
                    {
                        LOG(LM_DEBUG, Fmtmsg("xml_SetElement failed, xmlnode:[%s]", xml1), "DEBUG");
                        return -1;
                    }
                }
                if (xml_SetElementAttr(lXmlhandle, xml1, xmlattr1, value) == -1)
                {
                    LOG(LM_DEBUG, Fmtmsg("set xml attribute value failed, node:[%s], attr:[%s]", xml1, xmlattr1), "DEBUG");
                    return -1;
                }
                LOG(LM_DEBUG, Fmtmsg("%s@%s=[%s]", xml1, xmlattr1, value), "DEBUG");
            }
            else
            {
                if (xml_SetElement(lXmlhandle, xml1, value) == -1)
                {
                    LOG(LM_DEBUG, Fmtmsg("set xml node value failed, node:[%s]", xml1), "DEBUG");
                    return -1;
                }
                LOG(LM_DEBUG, Fmtmsg("%s=[%s]", xml1, value), "DEBUG");
            }
        }
    }
    else
    {
       
        memset(value, 0, sizeof(value));
        if (attr2 == 1)
        {
            if (xml_GetElementAttr(lXmlhandle, xmlnode2, xmlattr2, value, sizeof(value)) == -1)
            {
                LOG(LM_DEBUG, Fmtmsg("get xml attribute value failed, node:[%s], attr:[%s]", xmlnode2, xmlattr2), "DEBUG");
            }
        }
        else
        {
            if(mult2 == 0 && attr1 == 0  )
            {
                if (xml_SetElement(lXmlhandle, xmlnode1, xmlnode2) == -1)
                {
                    LOG(LM_DEBUG, Fmtmsg("set xml node value failed, node:[%s]", xmlnode1), "DEBUG");
                    return -1;
                }
             }
             else
             {
                if (xml_GetElement(lXmlhandle, xmlnode2, value, sizeof(value)) == -1)
                {
                   LOG(LM_DEBUG, Fmtmsg("get xml node value failed, node:[%s]", xmlnode2), "DEBUG");
                }
             }
        }

        if (attr1 == 1)
        {  
            if(mult2 == 0 && attr2 == 0)
            {
               if (xml_ElementExist(lXmlhandle, xmlnode1) == 0)
               {
                  if (xml_SetElement(lXmlhandle, xmlnode1, "") == -1)
                  {
                      LOG(LM_DEBUG, Fmtmsg("xml_SetElement failed, xmlnode:[%s]", xmlnode1), "DEBUG");
                      return -1;
                  }
               }
                if (xml_SetElementAttr(lXmlhandle, xmlnode1, xmlattr1, xmlnode2) == -1)
               {
                   LOG(LM_DEBUG, Fmtmsg("set xml attribute value failed, node:[%s], attr:[%s]", xmlnode1, xmlattr1), "DEBUG");
                   return -1;
               }
               LOG(LM_DEBUG, Fmtmsg("%s@%s=[%s]", xmlnode1, xmlattr1, xmlnode2), "DEBUG");
            }
            else
            {
            
               if (xml_ElementExist(lXmlhandle, xmlnode1) == 0)
               {
                  if (xml_SetElement(lXmlhandle, xmlnode1, "") == -1)
                  {
                      LOG(LM_DEBUG, Fmtmsg("xml_SetElement failed, xmlnode:[%s]", xmlnode1), "DEBUG");
                      return -1;
                  }
               }
               if (xml_SetElementAttr(lXmlhandle, xmlnode1, xmlattr1, value) == -1)
               {
                   LOG(LM_DEBUG, Fmtmsg("set xml attribute value failed, node:[%s], attr:[%s]", xmlnode1, xmlattr1), "DEBUG");
                   return -1;
               }
             LOG(LM_DEBUG, Fmtmsg("%s@%s=[%s]", xmlnode1, xmlattr1, value), "DEBUG");
            }
        }
        else
        {
            if(mult2 == 0 && attr2 == 0)
            {
                if (xml_SetElement(lXmlhandle, xmlnode1, xmlnode2) == -1)
                {
                    LOG(LM_DEBUG, Fmtmsg("set xml node value failed, node:[%s]", xmlnode1), "DEBUG");
                    return -1;
                }
                LOG(LM_DEBUG, Fmtmsg("%s=[%s]", xmlnode1, xmlnode2), "DEBUG");
            }
            else
            {
                if (xml_SetElement(lXmlhandle, xmlnode1, value) == -1)
                {
                LOG(LM_DEBUG, Fmtmsg("set xml node value failed, node:[%s]", xmlnode1), "DEBUG");
                return -1;
                }
                LOG(LM_DEBUG, Fmtmsg("%s=[%s]", xmlnode1, xmlnode2), "DEBUG");
            }
        }
    }
    return 0;
}

int handle_express(HXMLTREE lXmlhandle, const char *sexp, int type)
{
	int ret = 0;
	char sStart[10], sLen[10];
	char *sXmlNode, *sValue;
	const char *s;
    char *sTmp;
	int flag = 0x00;
	int node_len, len = strlen(sexp);
	int iStart = 1, iLen = 0;
	int i;

	s = strchr(sexp, '=');
	if (s == NULL)
		return ret;
	node_len = (int)(s - sexp);

	sXmlNode = (char *)malloc(node_len+1);
	if (sXmlNode == NULL)
		return -99;
	sValue = (char *)malloc(len-node_len+1);
	if (sValue == NULL)
	{
		free(sXmlNode);
		return -99;
	}
	memset(sXmlNode, 0, node_len+1);
	memset(sValue, 0, len-node_len+1);
	memset(sStart, 0, sizeof(sStart));
	memset(sLen, 0, sizeof(sLen));
	i = 0;
	for (s = sexp; *s != '\0'; s++)
	{
		switch(flag)
		{
		case 0x00:
			if (*s == '=')
			{
				flag = 0x10;
				i = 0;
			}
			else
				*(sXmlNode+i++) = *s;
			break;
		case 0x10:
			if (*s == '#')
			{
				flag = 0x11;
				i = 0;
			}
			else
				*(sValue+i++) = *s;
			break;
		case 0x11:
			if (*s == ',')
			{
				flag = 0x12;
				i = 0;
			}
			else if (i < sizeof(sStart)-1)
				*(sStart+i++) = *s;
			break;
		case 0x12:
			if (i < sizeof(sLen)-1)
				*(sLen+i++) = *s;
			break;
		default:
			break;
		}
	}

	iStart = atoi(sStart);
	iLen = atoi(sLen);

	if (iStart == 0)
		iStart = 1;

	LOG(LM_STD, Fmtmsg("xml node: [%s]", sXmlNode), "");
	LOG(LM_STD, Fmtmsg("xml value: [%s]", sValue), "");
	LOG(LM_STD, Fmtmsg("start: [%d]", iStart), "");
	LOG(LM_STD, Fmtmsg("len: [%d]", iLen), "");

	ret = set_xml(lXmlhandle, sXmlNode, sValue+iStart-1);
	free(sXmlNode);
	free(sValue);
	return ret;
}

/**********************************************************************
动态组件函数定义
组件函数名称:DATA_HSMEnSetValue
组件名称: DATA_HSMEnSetValue, 增强型设置xml结点值
组件功能: 增强型设置xml结点值
组件参数:
序号 参数名称   资源类别     缺省值   是否可空  参数说明


组件结果状态:
  结果状态码         结果说明
项 目 组: 中间业务产品研发组
程 序 员: 中间业务产品发展部研发组 
发布日期: 2009年07月20日 
修改日期: 2009年07月20日
参数使用示例:
************************************************************************/
IRESULT DATA_HSMEnSetValue(HXMLTREE lXmlhandle)
{
    char sBuf[81920];
    int iFlag;           /* 0-ascii, 1-bin  */
    int iParaCount,i;

    int iRet=0; 
    int iStatus= COMPSTATUS_SUCC;
    int iResult = COMPRET_SUCC;


    fpub_InitSoComp(lXmlhandle);

#ifdef _DEBUG
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"");
#endif

    iParaCount = fpub_GetPARAcount(lXmlhandle);
 
    memset(sBuf,'\0',sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "赋值方式");
    iFlag = atoi(sBuf);
   
    for ( i = 1; i < iParaCount; i++ )
    { 
        memset(sBuf,'\0',sizeof(sBuf));
        COMP_GETPARSEPARAS(i+1, sBuf, "赋值解析式");
        trim(sBuf);
		LOG(LM_STD, Fmtmsg("表达式[%s]赋值", sBuf), "");
		iRet = handle_express(lXmlhandle, sBuf, iFlag);
		
		if (iRet == -99)
		{
			LOG(LM_STD, Fmtmsg("表达式[%s]赋值失败, 内存不足!", sBuf), "");
		}
		else if (iRet == -1)
		{
			LOG(LM_STD, Fmtmsg("表达式[%s]赋值失败", sBuf), "");
		}
		
    }

#ifdef _DEBUG
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"");
#endif

    fpub_SetCompStatus(lXmlhandle, iStatus);
    return iResult;
}
