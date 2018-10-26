



#define  ICPS_COMPSTATUS_SQL_FAIL       -1        /*���ݿ����-ʧ��*/
#define  ICPS_COMPSTATUS_SQL_NORECORD    0        /*���ݿ����-�޷���������¼*/
#define  ICPS_COMPSTATUS_SQL_SUCC        1        /*���ݿ����-�ɹ�*/





/************************************************************************
�궨�幦��:
  ���������  ��ȡ����ɽ�������
�������:
  parasn      �������
  parabuf     ����������
  paraarray   �����洢����
  paraname    ��������
��    ��:
  parabuf  ����Ϊ�ַ�������������Ϊ�ַ���ָ��
************************************************************************/
#ifdef ICPS_GETPARSEPARAS_STRING
#undef ICPS_GETPARSEPARAS_STRING
#endif
#define ICPS_GETPARSEPARAS_STRING(parasn, parabuf, paraarray, paraname) {         \
    memset(parabuf, 0, sizeof(parabuf));                                  \
    memset(paraarray, 0, sizeof(paraarray));                              \
    COMP_GETPARSEPARAS(parasn, parabuf, paraname);                        \
    trim(parabuf);                                                        \
    pstrcopy(paraarray, parabuf, sizeof(paraarray));                      \
}

/************************************************************************
�궨�幦��:
  ���������  ��ȡ����ɽ�������
�������:
  parasn      �������
  parabuf     ����������
  paraarray   �����洢����
  paraname    ��������
��    ��:
  parabuf  ����Ϊ�ַ�������������Ϊ�ַ���ָ��
************************************************************************/
#ifdef ICPS_GETPARSEPARAS_STRING_NOTNULL
#undef ICPS_GETPARSEPARAS_STRING_NOTNULL
#endif
#define ICPS_GETPARSEPARAS_STRING_NOTNULL(parasn, parabuf, paraarray, paraname) { \
    memset(paraarray, 0, sizeof(paraarray));                              \
    COMP_GETPARSEPARAS(parasn, parabuf, paraname);                        \
    trim(parabuf);                                                        \
    if('\0' == parabuf[0])                                                \
    {                                                                     \
        fpub_SetMsg(lXmlhandle, MID_SYS_COMPEXEC,                         \
            Fmtmsg(MSG_SYS_COMPEXEC, fpub_GetCompname(lXmlhandle)));      \
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);                  \
        LOGRET(COMPRET_FAIL, LM_STD,                                      \
           Fmtmsg(MSG_SYS_COMPGETPARAS, fpub_GetCompname(lXmlhandle),     \
               paraname, parasn), fpub_GetCompname(lXmlhandle))           \
    }                                                                     \
    pstrcopy(paraarray, parabuf, sizeof(paraarray));                      \
}

/************************************************************************
�궨�幦��:
  ���������  ��ȡ�����ļ���Ľ���ֶΣ�����ֵ����Ӧ����
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  sTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_GET_MONEY_FROM_TOTALFILE_JB
#undef ICPS_GET_MONEY_FROM_TOTALFILE_JB
#endif
#define ICPS_GET_MONEY_FROM_TOTALFILE_JB(sFile, dTo, sColName, sName) {             \
    memset(sFileLineGBK, 0, sizeof(sFileLineGBK));                        \
	pBuf = strstr(sFileBufGBK, sColName) ;						  		  \
    GetListbyDiv(pBuf, 2, sBuf, ',', '\\');                				  \
    trim(sBuf);                                                           \
    dTo = atoi(sBuf) / 100.0;                                             \
}



/************************************************************************
�궨�幦��:
  ���������  ���ݷָ�����ȡָ��λ�õ����ַ���
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  sTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_GET_STRING_BY_DIV
#undef ICPS_GET_STRING_BY_DIV
#endif
#define ICPS_GET_STRING_BY_DIV(sFrom, iListno, sTo, cDiv, sName) {        \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    GetListbyDiv(sFrom, iListno, sBuf, cDiv, '\\');                       \
    trim(sBuf);                                                           \
    pstrcopy(sTo, sBuf, sizeof(sTo));                                     \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݷָ�����ȡָ��λ�õ�ʱ�����ַ�������ת����ʽ
  Դ��ʽYYYY-MM-DD HH:MM:SS Ŀ���ʽYYYYMMDDHHMMSS
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  sTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_GET_DATE_TIME_BY_DIV
#undef ICPS_GET_DATE_TIME_BY_DIV
#endif
#define ICPS_GET_DATE_TIME_BY_DIV(sFrom, iListno, sTo, cDiv, sName) {     \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    GetListbyDiv(sFrom, iListno, sBuf, cDiv, '\\');                       \
    trim(sBuf);                                                           \
    transform_date_time(sBuf, sTo);                                       \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݷָ�����ȡָ��λ�õ��������ַ�������ת����ʽ
  Դ��ʽYYYY-MM-DD Ŀ���ʽYYYYMMDD
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  sTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_GET_DATE_BY_DIV
#undef ICPS_GET_DATE_BY_DIV
#endif
#define ICPS_GET_DATE_BY_DIV(sFrom, iListno, sTo, cDiv, sName) {          \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    GetListbyDiv(sFrom, iListno, sBuf, cDiv, '\\');                       \
    trim(sBuf);                                                           \
    transform_date(sBuf, sTo);                                            \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݷָ�����ȡָ��λ�õĽ�����ַ�������ת������ԪΪ��λ��double����
  Դ��λ �� Ŀ�굥λ Ԫ
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  dTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_GET_MONEY_BY_DIV
#undef ICPS_GET_MONEY_BY_DIV
#endif
#define ICPS_GET_MONEY_BY_DIV(sFrom, iListno, dTo, cDiv, sName) {         \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    GetListbyDiv(sFrom, iListno, sBuf, cDiv, '\\');                       \
    trim(sBuf);                                                           \
    dTo = atoi(sBuf) / 100.0;                                             \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݷָ�����ȡָ��λ�õ���ֵ���ַ�������ת������������
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  iTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_GET_INTEGER_BY_DIV
#undef ICPS_GET_INTEGER_BY_DIV
#endif
#define ICPS_GET_INTEGER_BY_DIV(sFrom, iListno, iTo, cDiv, sName) {       \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    GetListbyDiv(sFrom, iListno, sBuf, cDiv, '\\');                       \
    trim(sBuf);                                                           \
    iTo = atoi(sBuf);                                                     \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݷָ�����ȡָ��λ�õ����ַ�������ת����double����
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  dTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_GET_DOUBLE_BY_DIV
#undef ICPS_GET_DOUBLE_BY_DIV
#endif
#define ICPS_GET_DOUBLE_BY_DIV(sFrom, iListno, dTo, cDiv, sName) {        \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    GetListbyDiv(sFrom, iListno, sBuf, cDiv, '\\');                       \
    trim(sBuf);                                                           \
    dTo = atof(sBuf);                                                     \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݷָ�����ȡָ��λ�õ����ַ���
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  sTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_WB_GET_STRING_BY_DIV
#undef ICPS_WB_GET_STRING_BY_DIV
#endif
#define ICPS_WB_GET_STRING_BY_DIV(sFrom, iListno, sTo, cDiv, sName) {     \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    GetListbyDiv(sFrom, iListno, sBuf, cDiv, '\\');                       \
    trim(sBuf);                                                           \
    if (0 == strcmp(sBuf, "\\N"))                                         \
        sTo[0] = 0;                                                       \
    else                                                                  \
        pstrcopy(sTo, sBuf, sizeof(sTo));                                 \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݷָ�����ȡָ��λ�õ�ʱ�����ַ�������ת����ʽ
  Դ��ʽYYYY-MM-DD HH:MM:SS Ŀ���ʽYYYYMMDDHHMMSS
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  sTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_WB_GET_DATE_TIME_BY_DIV
#undef ICPS_WB_GET_DATE_TIME_BY_DIV
#endif
#define ICPS_WB_GET_DATE_TIME_BY_DIV(sFrom, iListno, sTo, cDiv, sName) {     \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    GetListbyDiv(sFrom, iListno, sBuf, cDiv, '\\');                       \
    trim(sBuf);                                                           \
    if (0 == strcmp(sBuf, "\\N"))                                         \
        sTo[0] = 0;                                                       \
    else                                                                  \
    transform_date_time(sBuf, sTo);                                       \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݷָ�����ȡָ��λ�õ��������ַ�������ת����ʽ
  Դ��ʽYYYY-MM-DD Ŀ���ʽYYYYMMDD
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  sTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_WB_GET_DATE_BY_DIV
#undef ICPS_WB_GET_DATE_BY_DIV
#endif
#define ICPS_WB_GET_DATE_BY_DIV(sFrom, iListno, sTo, cDiv, sName) {       \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    GetListbyDiv(sFrom, iListno, sBuf, cDiv, '\\');                       \
    trim(sBuf);                                                           \
    if (0 == strcmp(sBuf, "\\N"))                                         \
        sTo[0] = 0;                                                       \
    else                                                                  \
        transform_date(sBuf, sTo);                                        \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݷָ�����ȡָ��λ�õĽ�����ַ�������ת������ԪΪ��λ��double����
  Դ��λ �� Ŀ�굥λ Ԫ
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  dTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_WB_GET_MONEY_BY_DIV
#undef ICPS_WB_GET_MONEY_BY_DIV
#endif
#define ICPS_WB_GET_MONEY_BY_DIV(sFrom, iListno, dTo, cDiv, sName) {         \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    GetListbyDiv(sFrom, iListno, sBuf, cDiv, '\\');                       \
    trim(sBuf);                                                           \
    if (0 == strcmp(sBuf, "\\N"))                                         \
        dTo = 0.00;                                                       \
    else                                                                  \
    dTo = atoi(sBuf) / 100.0;                                             \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݷָ�����ȡָ��λ�õ���ֵ���ַ�������ת������������
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  iTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_WB_GET_INTEGER_BY_DIV
#undef ICPS_WB_GET_INTEGER_BY_DIV
#endif
#define ICPS_WB_GET_INTEGER_BY_DIV(sFrom, iListno, iTo, cDiv, sName) {       \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    GetListbyDiv(sFrom, iListno, sBuf, cDiv, '\\');                       \
    trim(sBuf);                                                           \
    if (0 == strcmp(sBuf, "\\N"))                                         \
        iTo = 0;                                                          \
    else                                                                  \
    iTo = atoi(sBuf);                                                     \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݷָ�����ȡָ��λ�õ����ַ�������ת����double����
�������:
  sFrom      Դ�ַ���
  iListno    λ�����
  dTo        �洢����
  cDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_WB_GET_DOUBLE_BY_DIV
#undef ICPS_WB_GET_DOUBLE_BY_DIV
#endif
#define ICPS_WB_GET_DOUBLE_BY_DIV(sFrom, iListno, dTo, cDiv, sName) {        \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    GetListbyDiv(sFrom, iListno, sBuf, cDiv, '\\');                       \
    trim(sBuf);                                                           \
    if (0 == strcmp(sBuf, "\\N"))                                         \
        dTo = 0.00;                                                       \
    else                                                                  \
    dTo = atof(sBuf);                                                     \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݶ��ַ��ָ�����ȡָ��λ�õ����ַ���
�������:
  sTo        �洢����
  sFrom      Դ�ַ���
  sSymbol    �ָ���Դ
  sDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_GET_STRING_BY_MULTDIV
#undef ICPS_GET_STRING_BY_MULTDIV
#endif
#define ICPS_GET_STRING_BY_MULTDIV(sFrom, sTo, sDiv, sName) {             \
    getsubstr(sFrom, sDiv, sTo, sizeof(sTo));                             \
    trim(sTo);                                                            \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݶ��ַ��ָ�����ȡָ��λ�õ����ַ�������ת����double����
�������:
  dTo        �洢����
  sFrom      Դ�ַ���
  sSymbol    �ָ���Դ
  sDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_GET_DOUBLE_BY_MULTDIV
#undef ICPS_GET_DOUBLE_BY_MULTDIV
#endif
#define ICPS_GET_DOUBLE_BY_MULTDIV(sFrom, dTo, sDiv, sName) {             \
    memset(sBuf, 0x00, sizeof(sBuf));                                     \
    getsubstr(sFrom, sDiv, sBuf, sizeof(sBuf));                           \
    trim(sBuf);                                                           \
    dTo = atof(sBuf);                                                     \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݶ��ַ��ָ�����ȡָ��λ�õ����ַ�������ת����int����
�������:
  iTo        �洢����
  sFrom      Դ�ַ���
  sSymbol    �ָ���Դ
  sDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_GET_INTEGER_BY_MULTDIV
#undef ICPS_GET_INTEGER_BY_MULTDIV
#endif
#define ICPS_GET_INTEGER_BY_MULTDIV(sFrom, iTo, sDiv, sName) {            \
    memset(sBuf, 0x00, sizeof(sBuf));                                     \
    getsubstr(sFrom, sDiv, sBuf, sizeof(sBuf));                           \
    trim(sBuf);                                                           \
    iTo = atoi(sBuf);                                                     \
}

/************************************************************************
�궨�幦��:
  ���������  ���ݶ��ַ��ָ�����ȡָ��λ�õ����ַ�������ת�������ڸ�ʽ
�������:
  iTo        �洢����
  sFrom      Դ�ַ���
  sSymbol    �ָ���Դ
  sDiv       �ָ��ַ�
  sName      ���ַ�������
��    ��:
************************************************************************/
#ifdef ICPS_GET_DATE_BY_MULTDIV
#undef ICPS_GET_DATE_BY_MULTDIV
#endif
#define ICPS_GET_DATE_BY_MULTDIV(sFrom, sTo, sDiv, sName) {               \
    memset(sBuf, 0x00, sizeof(sBuf));                                     \
    getsubstr(sFrom, sDiv, sBuf, sizeof(sBuf));                           \
    trim(sBuf);                                                           \
    snprintf(sTo, sizeof(sTo), "%c%c%c%c%c%c%c%c",                        \
      sBuf[0], sBuf[1], sBuf[2], sBuf[3], sBuf[5], sBuf[6], sBuf[8], sBuf[9]); \
}

#ifdef ICPS_GETXMLNODE_STRING
#undef ICPS_GETXMLNODE_STRING
#endif
#define ICPS_GETXMLNODE_STRING(nodepath, nodearray, nodename) {           \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    COMP_SOFTGETXML(nodepath, sBuf);                                      \
    trim(sBuf);                                                           \
    pstrcopy(nodearray, sBuf, sizeof(nodearray));                         \
}

#ifdef ICPS_GETXMLNODE_DOUBLE
#undef ICPS_GETXMLNODE_DOUBLE
#endif
#define ICPS_GETXMLNODE_DOUBLE(nodepath, nodearray, nodename) {           \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    COMP_SOFTGETXML(nodepath, sBuf);                                      \
    trim(sBuf);                                                           \
    nodearray = atof(sBuf);                                               \
}

#ifdef ICPS_GETXMLNODE_MONEY
#undef ICPS_GETXMLNODE_MONEY
#endif
#define ICPS_GETXMLNODE_MONEY(nodepath, nodearray, nodename) {            \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    COMP_SOFTGETXML(nodepath, sBuf);                                      \
    trim(sBuf);                                                           \
    nodearray = atof(sBuf)/100.0;                                         \
}

#ifdef ICPS_GETXMLNODE_INTEGER
#undef ICPS_GETXMLNODE_INTEGER
#endif
#define ICPS_GETXMLNODE_INTEGER(nodepath, nodearray, nodename) {          \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    COMP_SOFTGETXML(nodepath, sBuf);                                      \
    trim(sBuf);                                                           \
    nodearray = atoi(sBuf);                                               \
}

#ifdef ICPS_SQLSETVALUE_STRING
#undef ICPS_SQLSETVALUE_STRING
#endif
#define ICPS_SQLSETVALUE_STRING(nodepath, statstr, desstr, valuename, nodename) {  \
    memset(sBuf, 0, sizeof(sBuf));                                        \
    COMP_SOFTGETXML(nodepath, sBuf);                                      \
    trim(sBuf);                                                           \
    if(0 != sBuf[0])                                                      \
    {                                                                     \
        snprintf(desstr,sizeof(desstr),"%s='%s',", valuename, sBuf);      \
        strcat(statstr, desstr);                                          \
    }                                                                     \
}










#ifdef XML2JSON
#undef XML2JSON
#endif
#define XML2JSON(path, xmlNode) {                                                         \
    memset(sElementPath, 0, sizeof(sElementPath));                                        \
    memset(sElementValue, 0, sizeof(sElementValue));                                      \
    sprintf(sElementPath, "%s/%s", path, xmlNode);                                        \
    xml_GetElement(lXmlhandle, sElementPath, sElementValue, sizeof(sElementValue));       \
    LOG(LM_DEBUG,Fmtmsg("�ڵ�[%s]ֵΪ[%s]", xmlNode, sElementValue), "DEBUG");             \
}



