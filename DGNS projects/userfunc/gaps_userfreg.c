/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V4.1.00
����ϵͳ:AIX/Linux/HP-UX
�ļ�����:gaps_userfreg.c
�ļ�����:�û����亯��ע��ṹ�����ļ�
�� Ŀ ��:GAPS�з���
�� �� Ա:Tianhc
��������:
��    ��:Tianhc
�޸�����:2006-3-22 20:38
*********************************************************************/
/*
�޸ļ�¼
�޸�����:
�޸�����:
�޸���:
*/
#include <stdio.h>
#include "gaps_head.h"
#include "gaps_func.h"

/********************************************************************
���ĵ��������������û��Զ��徲̬������Դ
������޸�
�ǿɱ༭���򲿷ֲ����޸ģ�����

*********************************************************************/

/************************�ɱ༭����ʼ*************************/


/************************�ɱ༭�������*************************/
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

/*�û����亯��ע��ṹ*/
FUNCREG gFregSfuncuser[] =
{
  /************************�ɱ༭����ʼ*************************/
  /*��������*/
  {"SAMP_Func1", SAMP_Func1},
  /*ȡ���ַ�������*/
  {"func_SubStr", func_SubStr},
  /*�䳤LLVAR�ֶ����*/
  {"func_ConvertLLVAR", func_ConvertLLVAR},
  /*�䳤LLVAR�ֶν��ʱȡ����*/
  {"func_ConvertsHEX2sINT", func_ConvertsHEX2sINT},
  {"func_Char2Int", func_Char2Int},
  {"func_Int2Char", func_Int2Char},
  {"func_AddHead", func_AddHead},
  {"func_reverse", func_reverse},
  {"gaps32_checkfldrule", gaps32_checkfldrule},

  /************************�ɱ༭�������*************************/
  {"", NULL}
};
