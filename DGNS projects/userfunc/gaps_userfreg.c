/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V4.1.00
操作系统:AIX/Linux/HP-UX
文件名称:gaps_userfreg.c
文件描述:用户扩充函数注册结构定义文件
项 目 组:GAPS研发组
程 序 员:Tianhc
发布日期:
修    订:Tianhc
修改日期:2006-3-22 20:38
*********************************************************************/
/*
修改记录
修改日期:
修改内容:
修改人:
*/
#include <stdio.h>
#include "gaps_head.h"
#include "gaps_func.h"

/********************************************************************
本文档用于用于扩充用户自定义静态函数资源
请谨慎修改
非可编辑区域部分不得修改！！！

*********************************************************************/

/************************可编辑区域开始*************************/


/************************可编辑区域结束*************************/
/**/
IRESULT SAMP_Func1(HXMLTREE, char*);
IRESULT func_SubStr(HXMLTREE, char*, int*, int, char*, int*, int*, char*, void*, void*);
IRESULT func_ConvertLLVAR(HXMLTREE, char*, int*, int, char*, int*, int*, char*, void*, void*);
IRESULT func_ConvertsHEX2sINT(HXMLTREE, char*, int*, int, char*, int*, int*, char*, void*, void*);
IRESULT func_Char2Int(HXMLTREE, char*, int*, int, char*, int*, int*, char*, void*, void*);
IRESULT func_Int2Char(HXMLTREE, char*, int*, int, char*, int*, int*, char*, void*, void*);
IRESULT func_AddHead(HXMLTREE, char*, int*, int, char*, int*, int*, char*, void*, void*);
IRESULT func_reverse(HXMLTREE, char*, int , char *);
IRESULT gaps32_checkfldrule(char*, char *);

/*用户扩充函数注册结构*/
FUNCREG gFregSfuncuser[] =
{
  /************************可编辑区域开始*************************/
  /*样例函数*/
  {"SAMP_Func1", SAMP_Func1},
  /*取子字符串函数*/
  {"func_SubStr", func_SubStr},
  /*变长LLVAR字段组包*/
  {"func_ConvertLLVAR", func_ConvertLLVAR},
  /*变长LLVAR字段解包时取长度*/
  {"func_ConvertsHEX2sINT", func_ConvertsHEX2sINT},
  {"func_Char2Int", func_Char2Int},
  {"func_Int2Char", func_Int2Char},
  {"func_AddHead", func_AddHead},
  {"func_reverse", func_reverse},
  {"gaps32_checkfldrule", gaps32_checkfldrule},

  /************************可编辑区域结束*************************/
  {"", NULL}
};
