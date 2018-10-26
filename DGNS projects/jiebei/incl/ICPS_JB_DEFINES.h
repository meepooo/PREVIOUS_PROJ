



#define  ICPS_COMPSTATUS_SQL_FAIL       -1        /*数据库操作-失败*/
#define  ICPS_COMPSTATUS_SQL_NORECORD    0        /*数据库操作-无符合条件记录*/
#define  ICPS_COMPSTATUS_SQL_SUCC        1        /*数据库操作-成功*/





/************************************************************************
宏定义功能:
  组件辅助宏  获取组件可解析参数
输入参数:
  parasn      参数序号
  parabuf     参数缓冲区
  paraarray   参数存储变量
  paraname    参数名称
限    制:
  parabuf  必须为字符串变量，不可为字符串指针
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
宏定义功能:
  组件辅助宏  获取组件可解析参数
输入参数:
  parasn      参数序号
  parabuf     参数缓冲区
  paraarray   参数存储变量
  paraname    参数名称
限    制:
  parabuf  必须为字符串变量，不可为字符串指针
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
宏定义功能:
  组件辅助宏  获取总账文件里的金额字段，并赋值到对应变量
输入参数:
  sFrom      源字符串
  iListno    位置序号
  sTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据分隔符获取指定位置的子字符串
输入参数:
  sFrom      源字符串
  iListno    位置序号
  sTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据分隔符获取指定位置的时间子字符串，并转换格式
  源格式YYYY-MM-DD HH:MM:SS 目标格式YYYYMMDDHHMMSS
输入参数:
  sFrom      源字符串
  iListno    位置序号
  sTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据分隔符获取指定位置的日期子字符串，并转换格式
  源格式YYYY-MM-DD 目标格式YYYYMMDD
输入参数:
  sFrom      源字符串
  iListno    位置序号
  sTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据分隔符获取指定位置的金额子字符串，并转换成以元为单位的double类型
  源单位 分 目标单位 元
输入参数:
  sFrom      源字符串
  iListno    位置序号
  dTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据分隔符获取指定位置的数值子字符串，并转换成整数类型
输入参数:
  sFrom      源字符串
  iListno    位置序号
  iTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据分隔符获取指定位置的子字符串，并转换成double类型
输入参数:
  sFrom      源字符串
  iListno    位置序号
  dTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据分隔符获取指定位置的子字符串
输入参数:
  sFrom      源字符串
  iListno    位置序号
  sTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据分隔符获取指定位置的时间子字符串，并转换格式
  源格式YYYY-MM-DD HH:MM:SS 目标格式YYYYMMDDHHMMSS
输入参数:
  sFrom      源字符串
  iListno    位置序号
  sTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据分隔符获取指定位置的日期子字符串，并转换格式
  源格式YYYY-MM-DD 目标格式YYYYMMDD
输入参数:
  sFrom      源字符串
  iListno    位置序号
  sTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据分隔符获取指定位置的金额子字符串，并转换成以元为单位的double类型
  源单位 分 目标单位 元
输入参数:
  sFrom      源字符串
  iListno    位置序号
  dTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据分隔符获取指定位置的数值子字符串，并转换成整数类型
输入参数:
  sFrom      源字符串
  iListno    位置序号
  iTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据分隔符获取指定位置的子字符串，并转换成double类型
输入参数:
  sFrom      源字符串
  iListno    位置序号
  dTo        存储变量
  cDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据多字符分隔符获取指定位置的子字符串
输入参数:
  sTo        存储变量
  sFrom      源字符串
  sSymbol    分割来源
  sDiv       分割字符
  sName      子字符串名称
限    制:
************************************************************************/
#ifdef ICPS_GET_STRING_BY_MULTDIV
#undef ICPS_GET_STRING_BY_MULTDIV
#endif
#define ICPS_GET_STRING_BY_MULTDIV(sFrom, sTo, sDiv, sName) {             \
    getsubstr(sFrom, sDiv, sTo, sizeof(sTo));                             \
    trim(sTo);                                                            \
}

/************************************************************************
宏定义功能:
  组件辅助宏  根据多字符分隔符获取指定位置的子字符串，并转换成double类型
输入参数:
  dTo        存储变量
  sFrom      源字符串
  sSymbol    分割来源
  sDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据多字符分隔符获取指定位置的子字符串，并转换成int类型
输入参数:
  iTo        存储变量
  sFrom      源字符串
  sSymbol    分割来源
  sDiv       分割字符
  sName      子字符串名称
限    制:
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
宏定义功能:
  组件辅助宏  根据多字符分隔符获取指定位置的子字符串，并转换成日期格式
输入参数:
  iTo        存储变量
  sFrom      源字符串
  sSymbol    分割来源
  sDiv       分割字符
  sName      子字符串名称
限    制:
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
    LOG(LM_DEBUG,Fmtmsg("节点[%s]值为[%s]", xmlNode, sElementValue), "DEBUG");             \
}



