/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V4.1.00
����ϵͳ:AIX/Linux/HP-UX
�� �� ��:SSERIAL.c
�ļ�����:����ˮ/������ˮ/��ˮ������������
�� Ŀ ��:GAPS�з���
�� �� Ա:[Tianhc]
��������:2009-6-16 15:19:57
��    ��:
�޸�����:
****************************************************************************/
/*
   ˵����Ϣ��
      ��ASPKV4�����£��Ƽ�ʹ��ϵͳ�ṩ��DCIģʽ�������ݿ⣻
      ������ʹ�����ݿ��Դ���EXEC SQLǶC�Ŀ���ģʽ������ͨ���ѷ�װ��DCI�����������ݿ�
      �����뼴Ϊʹ��DCI��һ��������������
       insert(�ṹģʽ)/update(�ṹģʽ)/select(�α�ģʽ)
*/
/****************************************************************************
�޸ļ�¼
�޸�����:2009-8-1 9:06:43
�� �� ��:Tianhc
�޸�����:
   �Դ�����з���ǰ����
Tianhc 2009-9-24 14:04:28
  V4.0.01
    ԭ�汾�ڳ���ʱδ����Ӧ��/��Ӧ��Ϣ
****************************************************************************/



#include "gaps_head.h"
#include "ywty_drls.h"
#include "DCI.h"

static char SSERIAL_c[] = "{$Id: SSERIAL.c 2219 2013-01-25 07:20:11Z tianhc $}";

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "4.0.02"

int ShowSocompVersion(char *sinfo, int isize)
{
  char sversion[] = "<?xml version=\"1.0\" encoding=\"GB2312\"?>\
     <root>\
      <soname>SSERIAL.so</soname>\
      <sosrcname>SSERIAL.c</sosrcname>\
      <sonote>��ˮ������������</sonote>\
      <version>\
        <rec ver=\"4.0.00\" modify=\"2009-8-1 9:14:20\" programer=\"Tianhc Chendh\" filesize=\"81519\">ASPKV4����ǰ����</rec>\
        <rec ver=\"4.0.02\" modify=\"2012/10/17 10:34:30\" programer=\"Tianhc\" filesize=\"22539\">�޸�Updateʱ��������</rec>\
      </version>\
     </root>";
  printf("\n================��̬���������Ϣ================\n");
  printf("SOCOMPBUILDNO:%s\n", SOCOMPBUILDNO);
  printf("SOCOMPVERSION:%s\n", SOCOMPVERSION);
  printf("%s-%s\n", __PROJECTSNAME, __VERSION);
  if (strlen(sversion) >= isize)
  {
    printf(" -->ȡ��ϸ��Ϣʧ��...\n");
    return -2;
  }
  strcpy(sinfo, sversion);
  printf(" -->��鿴��ϸ��Ϣ...\n");
  return 0;
}

/************************************************************************
��̬�����������
�����������: SERIAL_InsertCurrent
�������: SERIAL_InsertCurrent
�������:
     ����DCI�ӿڣ���ywty_drls�����һ����¼
�������:
  ��� ��������   ��Դ���     ȱʡֵ   �Ƿ�ɿ�  ����˵��


������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: Turandot@ASPKV4
�� �� Ա:
��������: 2009-8-1 9:15:25
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SERIAL_InsertCurrent(HXMLTREE lXmlhandle)
{

  int iParas;
  int ret;
  YWTY_DRLS Sywty_drls;
  char sBuf[300];
  char errmsg[512];

  fpub_InitSoComp(lXmlhandle);

  LOG(LM_STD, Fmtmsg("���뵱����ˮ...."), "INFO")
  memset(&Sywty_drls, 0, sizeof(Sywty_drls));
  /*��������*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_HARDGETXML("/pub/zwrq", sBuf)
  trim(sBuf);
  pstrcopy(Sywty_drls.zwrq, sBuf, sizeof(Sywty_drls.zwrq));
  /*�ۺ�ǰ����ˮ��*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_HARDGETXML("/pub/zhqzlsh", sBuf)
  Sywty_drls.zhqzlsh = atoi(sBuf);
  /*������ˮ��*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/zxlsh", sBuf)
  pstrcopy(Sywty_drls.zxlsh, sBuf, sizeof(Sywty_drls.zxlsh));
  /*��������������*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/dsfzwrq", sBuf)
  pstrcopy(Sywty_drls.dsfzwrq, sBuf, sizeof(Sywty_drls.dsfzwrq));
  /*��������ˮ��*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/dsflsh", sBuf)
  pstrcopy(Sywty_drls.dsflsh, sBuf, sizeof(Sywty_drls.dsflsh));
  /*���׸��ٺ�*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jygzh", sBuf)
  pstrcopy(Sywty_drls.jygzh, sBuf, sizeof(Sywty_drls.jygzh));
  /*�ۺ�ǰ����ˮ��2*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/zhqzlsh2", sBuf)
  Sywty_drls.zhqzlsh2 = atoi(sBuf);
  /*��Ȩ��*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/sqm", sBuf)
  pstrcopy(Sywty_drls.sqm, sBuf, sizeof(Sywty_drls.sqm));
  /*��Ȩ����Ա*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/sqczy", sBuf)
  pstrcopy(Sywty_drls.sqczy, sBuf, sizeof(Sywty_drls.sqczy));
  /*�ϼ�����*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/sjjgbh", sBuf)
  pstrcopy(Sywty_drls.sjjgbh, sBuf, sizeof(Sywty_drls.sjjgbh));
  /*�������*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jgbh", sBuf)
  pstrcopy(Sywty_drls.jgbh, sBuf, sizeof(Sywty_drls.jgbh));
  /*�ڲ�������ʶ*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/nbjgbs", sBuf)
  pstrcopy(Sywty_drls.nbjgbs, sBuf, sizeof(Sywty_drls.nbjgbs));
  /*ί�л������*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/wtjgbh", sBuf)
  pstrcopy(Sywty_drls.wtjgbh, sBuf, sizeof(Sywty_drls.wtjgbh));
  /*ί���ڲ�������ʶ*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/wtnbjgbs", sBuf)
  pstrcopy(Sywty_drls.wtnbjgbs, sBuf, sizeof(Sywty_drls.wtnbjgbs));
  /*����Ա��*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/czyh", sBuf)
  pstrcopy(Sywty_drls.czyh, sBuf, sizeof(Sywty_drls.czyh));
  /*�ڵ���*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jdbh", sBuf)
  pstrcopy(Sywty_drls.jdbh, sBuf, sizeof(Sywty_drls.jdbh));
  /*��������*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/sys/apps|1/appcode", sBuf); /*Tian 2003-9-10 19:30*/
  pstrcopy(Sywty_drls.jyqd, sBuf, sizeof(Sywty_drls.jyqd));
  /*��������*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/sys/sysdate", sBuf)
  pstrcopy(Sywty_drls.jyrq, sBuf, sizeof(Sywty_drls.jyrq));
  /*����ʱ��*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/sys/systime", sBuf)
  pstrcopy(Sywty_drls.jysj, sBuf, sizeof(Sywty_drls.jysj));
  /*���״���*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jydm", sBuf)
  pstrcopy(Sywty_drls.jydm, sBuf, sizeof(Sywty_drls.jydm));
  /*��������*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jymc", sBuf)
  pstrcopy(Sywty_drls.jymc, sBuf, sizeof(Sywty_drls.jymc));
  /*ҵ�����*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/ywdm", sBuf)
  pstrcopy(Sywty_drls.ywdm, sBuf, sizeof(Sywty_drls.ywdm));
  /*��Ŀ����*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/xmdh", sBuf)
  pstrcopy(Sywty_drls.xmdh, sBuf, sizeof(Sywty_drls.xmdh));
  /*�ͻ�����*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/khmc", sBuf)
  pstrcopy(Sywty_drls.khmc, sBuf, sizeof(Sywty_drls.khmc));
  /*�����˺�*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jyzh", sBuf)
  pstrcopy(Sywty_drls.jyzh, sBuf, sizeof(Sywty_drls.jyzh));
  /*�ʻ�����*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/zhzl", sBuf)
  pstrcopy(Sywty_drls.zhzl, sBuf, sizeof(Sywty_drls.zhzl));
  /*�����˺�2*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jyzh2", sBuf)
  pstrcopy(Sywty_drls.jyzh2, sBuf, sizeof(Sywty_drls.jyzh2));
  /*�ʻ�����2*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/zhzl2", sBuf)
  pstrcopy(Sywty_drls.zhzl2, sBuf, sizeof(Sywty_drls.zhzl2));
  /*�ʻ�����2*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/zhjg2", sBuf)
  pstrcopy(Sywty_drls.zhjg2, sBuf, sizeof(Sywty_drls.zhjg2));
  /*�ͻ���*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/khh", sBuf)
  pstrcopy(Sywty_drls.khh, sBuf, sizeof(Sywty_drls.khh));
  /*�û���*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/yhh", sBuf)
  pstrcopy(Sywty_drls.yhh, sBuf, sizeof(Sywty_drls.yhh));
  /*���ֺ�*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/bzh", sBuf)
  pstrcopy(Sywty_drls.bzh, sBuf, sizeof(Sywty_drls.bzh));
  /*���׽��*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jyje", sBuf)
  Sywty_drls.jyje = atof(sBuf);
  /*������*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/sxf", sBuf)
  Sywty_drls.sxf = atof(sBuf);
  /*������*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/gbf", sBuf)
  Sywty_drls.gbf = atof(sBuf);
  /*���ɽ�*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/znj", sBuf)
  Sywty_drls.znj = atof(sBuf);
  /*����״̬*/
  Sywty_drls.jyzt[0] = '9' ;/*����*/
  /*��Ӧ��*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML(XMLNM_RESPCODE, sBuf)
  pstrcopy(Sywty_drls.xym, sBuf, sizeof(Sywty_drls.xym));
  /*��Ӧ��Ϣ*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML(XMLNM_RESPMSG, sBuf)
  pstrcopy(Sywty_drls.xyxx, sBuf, sizeof(Sywty_drls.xyxx));
  /*���׷�ʽ*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jyfs", sBuf)
  pstrcopy(Sywty_drls.jyfs, sBuf, sizeof(Sywty_drls.jyfs));
  /*�����־*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jdbz", sBuf)
  pstrcopy(Sywty_drls.jdbz, sBuf, sizeof(Sywty_drls.jdbz));
  /*���ʱ�־*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jzbz", sBuf)
  pstrcopy(Sywty_drls.jzbz, sBuf, sizeof(Sywty_drls.jzbz));
  /*�����־*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/qsbz", sBuf)
  pstrcopy(Sywty_drls.qsbz, sBuf, sizeof(Sywty_drls.qsbz));
  /*�鵵��־*/
  COMP_SOFTGETXML("/pub/gdbz", sBuf)
  pstrcopy(Sywty_drls.gdbz, sBuf, sizeof(Sywty_drls.gdbz));
  /*��������*/
  COMP_SOFTGETXML("/pub/jyzl", sBuf)
  pstrcopy(Sywty_drls.jyzl, sBuf, sizeof(Sywty_drls.jyzl));
  /*��չ��־*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/kzbz", sBuf)
  pstrcopy(Sywty_drls.kzbz, sBuf, sizeof(Sywty_drls.kzbz));
  /*�ⲿ�����ʶ*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/wbzwbs", sBuf)
  pstrcopy(Sywty_drls.wbzwbs, sBuf, sizeof(Sywty_drls.wbzwbs));
  /*����*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/byzd", sBuf)
  pstrcopy(Sywty_drls.byzd, sBuf, sizeof(Sywty_drls.byzd));

  ret = DBInsert("ywty_drls", SD_YWTY_DRLS, NUMELE(SD_YWTY_DRLS), &Sywty_drls, errmsg);
  if (ret < 0)
  {/*���뵱����ˮʧ��*/
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("�����쳣���������ݿ����ʧ��[%s]", errmsg),
           fpub_GetCompname(lXmlhandle))
  }

  if (DCICommit() == -1)
  {
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("�����쳣���ύ����ʧ��[%s]", DCILastError()),
           fpub_GetCompname(lXmlhandle))
  }

  LOG(LM_STD, Fmtmsg("����ɹ�"), "INFO")

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SERIAL_UpdateCurrent
�������: SERIAL_UpdateCurrent
�������:
   ���ݵ�ǰXML�����ݣ�����DCI�ӿڣ����µ�ǰ����ˮ���е�ǰ��¼
�������:
  ��� ��������   ��Դ���     ȱʡֵ   �Ƿ�ɿ�  ����˵��
  1    ����״̬   �����ַ���   0         N        ����ywty_drls��ṹ�еĶ���

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: Turandot@ASPKV4
�� �� Ա:
��������: 2009-8-1 9:15:25
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SERIAL_UpdateCurrent(HXMLTREE lXmlhandle)
{
  int  iParas;
  int  ret;
  char sJyzt[50];
  char sBuf[254];
  char sCondition[128];
  char errmsg[512];
  YWTY_DRLS Sywty_drls;

  fpub_InitSoComp(lXmlhandle);
  COMP_PARACOUNTCHK(1)
  COMP_GETPARSEPARAS(1, sJyzt, "����״̬")

  LOG(LM_STD, Fmtmsg("  -->���µ�����ˮ,״̬[%s]...", sJyzt), "INFO")


  /*��ȡ�������  --S*/

  /*��ȡ�������  --E*/
  /*��ɹ���  --S*/
  memset(&Sywty_drls, 0, sizeof(Sywty_drls));

  /*��������*/
  COMP_HARDGETXML("/pub/zwrq", sBuf)
  pstrcopy(Sywty_drls.zwrq, sBuf, sizeof(Sywty_drls.zwrq));
  /*�ۺ�ǰ����ˮ��*/
  COMP_HARDGETXML("/pub/zhqzlsh", sBuf)
  Sywty_drls.zhqzlsh = atoi(sBuf);
  /*������ˮ��*/
  COMP_SOFTGETXML("/pub/zxlsh", sBuf)
  pstrcopy(Sywty_drls.zxlsh, sBuf, sizeof(Sywty_drls.zxlsh));
  /*��������������*/
  COMP_SOFTGETXML("/pub/dsfzwrq", sBuf)
  pstrcopy(Sywty_drls.dsfzwrq, sBuf, sizeof(Sywty_drls.dsfzwrq));
  /*��������ˮ��*/
  COMP_SOFTGETXML("/pub/dsflsh", sBuf)
  pstrcopy(Sywty_drls.dsflsh, sBuf, sizeof(Sywty_drls.dsflsh));
  /*���׸��ٺ�*/
  COMP_SOFTGETXML("/pub/jygzh", sBuf)
  pstrcopy(Sywty_drls.jygzh, sBuf, sizeof(Sywty_drls.jygzh));
  /*�ۺ�ǰ����ˮ��2*/
  COMP_SOFTGETXML("/pub/zhqzlsh2", sBuf)
  Sywty_drls.zhqzlsh2 = atoi(sBuf);
  /*��Ȩ��*/
  COMP_SOFTGETXML("/pub/sqm", sBuf)
  pstrcopy(Sywty_drls.sqm, sBuf, sizeof(Sywty_drls.sqm));
  /*��Ȩ����Ա*/
  COMP_SOFTGETXML("/pub/sqczy", sBuf)
  pstrcopy(Sywty_drls.sqczy, sBuf, sizeof(Sywty_drls.sqczy));
  /*�ϼ�����*/
  COMP_SOFTGETXML("/pub/sjjgbh", sBuf)
  pstrcopy(Sywty_drls.sjjgbh, sBuf, sizeof(Sywty_drls.sjjgbh));
  /*�������*/
  COMP_SOFTGETXML("/pub/jgbh", sBuf)
  pstrcopy(Sywty_drls.jgbh, sBuf, sizeof(Sywty_drls.jgbh));
  /*�ڲ�������ʶ*/
  COMP_SOFTGETXML("/pub/nbjgbs", sBuf)
  pstrcopy(Sywty_drls.nbjgbs, sBuf, sizeof(Sywty_drls.nbjgbs));
  /*ί�л������*/
  COMP_SOFTGETXML("/pub/wtjgbh", sBuf)
  pstrcopy(Sywty_drls.wtjgbh, sBuf, sizeof(Sywty_drls.wtjgbh));
  /*ί���ڲ�������ʶ*/
  COMP_SOFTGETXML("/pub/wtnbjgbs", sBuf)
  pstrcopy(Sywty_drls.wtnbjgbs, sBuf, sizeof(Sywty_drls.wtnbjgbs));
  /*����Ա��*/
  COMP_SOFTGETXML("/pub/czyh", sBuf)
  pstrcopy(Sywty_drls.czyh, sBuf, sizeof(Sywty_drls.czyh));
  /*�ڵ���*/
  COMP_SOFTGETXML("/pub/jdbh", sBuf)
  pstrcopy(Sywty_drls.jdbh, sBuf, sizeof(Sywty_drls.jdbh));
  /*��������*/
  COMP_SOFTGETXML("/sys/apps|1/appcode", sBuf); /*Tian 2003-9-10 19:30*/
  pstrcopy(Sywty_drls.jyqd, strtolower(sBuf), sizeof(Sywty_drls.jyqd));
  /*��������*/
  COMP_SOFTGETXML("/sys/sysdate", sBuf)
  pstrcopy(Sywty_drls.jyrq, sBuf, sizeof(Sywty_drls.jyrq));
  /*����ʱ��*/
  COMP_SOFTGETXML("/sys/systime", sBuf)
  pstrcopy(Sywty_drls.jysj, sBuf, sizeof(Sywty_drls.jysj));
  /*���״���*/
  COMP_SOFTGETXML("/pub/jydm", sBuf)
  pstrcopy(Sywty_drls.jydm, sBuf, sizeof(Sywty_drls.jydm));
  /*��������*/
  COMP_SOFTGETXML("/pub/jymc", sBuf)
  pstrcopy(Sywty_drls.jymc, sBuf, sizeof(Sywty_drls.jymc));
  /*ҵ�����*/
  COMP_SOFTGETXML("/pub/ywdm", sBuf)
  pstrcopy(Sywty_drls.ywdm, sBuf, sizeof(Sywty_drls.ywdm));
  /*��Ŀ����*/
  COMP_SOFTGETXML("/pub/xmdh", sBuf)
  pstrcopy(Sywty_drls.xmdh, sBuf, sizeof(Sywty_drls.xmdh));
  /*�ͻ�����*/
  COMP_SOFTGETXML("/pub/khmc", sBuf)
  pstrcopy(Sywty_drls.khmc, sBuf, sizeof(Sywty_drls.khmc));
  /*�����˺�*/
  COMP_SOFTGETXML("/pub/jyzh", sBuf)
  pstrcopy(Sywty_drls.jyzh, sBuf, sizeof(Sywty_drls.jyzh));
  /*�ʻ�����*/
  COMP_SOFTGETXML("/pub/zhzl", sBuf)
  pstrcopy(Sywty_drls.zhzl, sBuf, sizeof(Sywty_drls.zhzl));
  /*�����˺�2*/
  COMP_SOFTGETXML("/pub/jyzh2", sBuf)
  pstrcopy(Sywty_drls.jyzh2, sBuf, sizeof(Sywty_drls.jyzh2));
  /*�ʻ�����2*/
  COMP_SOFTGETXML("/pub/zhzl2", sBuf)
  pstrcopy(Sywty_drls.zhzl2, sBuf, sizeof(Sywty_drls.zhzl2));
  /*�ʻ�����2*/
  COMP_SOFTGETXML("/pub/zhjg2", sBuf)
  pstrcopy(Sywty_drls.zhjg2, sBuf, sizeof(Sywty_drls.zhjg2));
  /*�ͻ���*/
  COMP_SOFTGETXML("/pub/khh", sBuf)
  pstrcopy(Sywty_drls.khh, sBuf, sizeof(Sywty_drls.khh));
  /*�û���*/
  COMP_SOFTGETXML("/pub/yhh", sBuf)
  pstrcopy(Sywty_drls.yhh, sBuf, sizeof(Sywty_drls.yhh));
  /*���ֺ�*/
  COMP_SOFTGETXML("/pub/bzh", sBuf)
  pstrcopy(Sywty_drls.bzh, sBuf, sizeof(Sywty_drls.bzh));
  /*���׽��*/
  COMP_SOFTGETXML("/pub/jyje", sBuf)
  Sywty_drls.jyje = atof(sBuf);
  /*������*/
  COMP_SOFTGETXML("/pub/sxf", sBuf)
  Sywty_drls.sxf = atof(sBuf);
  /*������*/
  COMP_SOFTGETXML("/pub/gbf", sBuf)
  Sywty_drls.gbf = atof(sBuf);
  /*���ɽ�*/
  COMP_SOFTGETXML("/pub/znj", sBuf)
  Sywty_drls.znj = atof(sBuf);

  /*����״̬*/
  pstrcopy(Sywty_drls.jyzt, sJyzt, sizeof(Sywty_drls.jyzt));

  /*��Ӧ��*/
  COMP_SOFTGETXML(XMLNM_RESPCODE, sBuf)
  pstrcopy(Sywty_drls.xym, sBuf, sizeof(Sywty_drls.xym));
  /*��Ӧ��Ϣ*/
  COMP_SOFTGETXML(XMLNM_RESPMSG, sBuf)
  pstrcopy(Sywty_drls.xyxx, sBuf, sizeof(Sywty_drls.xyxx));
  /*���׷�ʽ*/
  COMP_SOFTGETXML("/pub/jyfs", sBuf)
  pstrcopy(Sywty_drls.jyfs, sBuf, sizeof(Sywty_drls.jyfs));
  /*�����־*/
  COMP_SOFTGETXML("/pub/jdbz", sBuf)
  pstrcopy(Sywty_drls.jdbz, sBuf, sizeof(Sywty_drls.jdbz));
  /*�鵵��־*/
  COMP_SOFTGETXML("/pub/gdbz", sBuf)
  pstrcopy(Sywty_drls.gdbz, sBuf, sizeof(Sywty_drls.gdbz));
  /*��������*/
  COMP_SOFTGETXML("/pub/jyzl", sBuf)
  pstrcopy(Sywty_drls.jyzl, sBuf, sizeof(Sywty_drls.jyzl));
  /*���ʱ�־*/
  COMP_SOFTGETXML("/pub/jzbz", sBuf)
  pstrcopy(Sywty_drls.jzbz, sBuf, sizeof(Sywty_drls.jzbz));
  /*�����־*/
  COMP_SOFTGETXML("/pub/qsbz", sBuf)
  pstrcopy(Sywty_drls.qsbz, sBuf, sizeof(Sywty_drls.qsbz));
  /*��չ��־*/
  COMP_SOFTGETXML("/pub/kzbz", sBuf)
  pstrcopy(Sywty_drls.kzbz, sBuf, sizeof(Sywty_drls.kzbz));
  /*�ⲿ�����ʶ*/
  COMP_SOFTGETXML("/pub/wbzwbs", sBuf)
  pstrcopy(Sywty_drls.wbzwbs, sBuf, sizeof(Sywty_drls.wbzwbs));
  /*����*/
  COMP_SOFTGETXML("/pub/byzd", sBuf)
  pstrcopy(Sywty_drls.byzd, sBuf, sizeof(Sywty_drls.byzd));

  /*DEMO����zhqzlsh��int�Ͷ���string��!*/
  sprintf(sCondition, "zwrq = '%s' and zhqzlsh = %d", Sywty_drls.zwrq, Sywty_drls.zhqzlsh);

  ret =  DBUpdate("ywty_drls", SD_YWTY_DRLS, NUMELE(SD_YWTY_DRLS), &Sywty_drls, sCondition, errmsg);
  if (ret < 0)
  {/*���뵱����ˮʧ��*/
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("�����쳣���������ݿ����ʧ��[%s]", errmsg),
           fpub_GetCompname(lXmlhandle))
  }

  if (DCICommit() == -1)
  {
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("�����쳣���ύ����ʧ��[%s]", DCILastError()),
           fpub_GetCompname(lXmlhandle))
  }

  LOG(LM_STD, Fmtmsg("���³ɹ�"), "INFO")
  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

  return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SERIAL_ReportToFile
�������: SERIAL_ReportToFile
�������:
   ����һ���򵥱��������
   ָ�������µļ�¼��ȫ����¼���ļ��У�����unload����

�������:
  ��� ��������   ��Դ���     ȱʡֵ   �Ƿ�ɿ�  ����˵��


������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: Turandot@ASPKV4
�� �� Ա:
��������: 2009-8-1 9:15:25
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SERIAL_ReportToFile(HXMLTREE lXmlhandle)
{
  int  iParas;
  int  rowcount = 0;
  int rc;
  char sDeli[256];
  char sFile[256];
  char sCondition[512];
  char sSql[1024];
  char errmsg[512];
  FILE* fp;
  CURSOR cur;
  YWTY_DRLS Sywty_drls;

  fpub_InitSoComp(lXmlhandle);
  COMP_PARACOUNTCHK(3)
  COMP_GETPARSEPARAS(1, sFile,      "�ļ���")
  COMP_GETPARSEPARAS(2, sCondition, "����")
  COMP_GETPARSEPARAS(3, sDeli,      "�ָ���")

  LOG(LM_STD, Fmtmsg("  -->�������ļ�[%s],����[%s]�ָ���[%s]...", sFile, sCondition, sDeli), "INFO")


  /*��ȡ�������  --S*/

  /*��ȡ�������  --E*/
  /*��ɹ���  --S*/
  memset(&Sywty_drls, 0, sizeof(Sywty_drls));

  trim(sCondition);
  if (strlen(sCondition) > 0)
    sprintf(sSql, "select * from ywty_drls where %s", sCondition);
  else
    strcpy(sSql, "select * from ywty_drls");

  if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
  {
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("�����쳣��׼�����ݿ����ʧ��[%s]", DCILastError()),
           fpub_GetCompname(lXmlhandle))
  }


  if (DCIExecute(cur) == -1)
  {
    DCIFreeCursor(cur);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("�����쳣��ִ�����ݿ����ʧ��[%s]", DCILastError()),
           fpub_GetCompname(lXmlhandle))
  }

  fp = fopen(sFile, "w");
  if (fp == NULL)
  {
    DCIFreeCursor(cur);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("���ļ�ʧ��[%s]", sFile),
           fpub_GetCompname(lXmlhandle))
  }

  while ((rc = DBFetch(cur, SD_YWTY_DRLS, NUMELE(SD_YWTY_DRLS), &Sywty_drls, errmsg)) > 0)
  {
    int i;
    FLD_DESC *pdesc;
    int desc_num = NUMELE(SD_YWTY_DRLS);

    rowcount++;
    for (i = 0, pdesc = SD_YWTY_DRLS; i < desc_num; i++, pdesc++)
    {
      char *pval = (char *) & Sywty_drls + pdesc->offset;
      switch (pdesc->type)
      {
      case TT_CHAR:
      case TT_STRING:
        fprintf(fp, "%s%s", pval, sDeli);
        break;

      case TT_SHORT:
        fprintf(fp, "%d%s", *(int *) pval, sDeli);
        break;
      case TT_LONG:
        fprintf(fp, "%ld%s", *(long *) pval, sDeli);
        break;

      case TT_DOUBLE:
        fprintf(fp, "%lf%s", *(double *) pval, sDeli);
        break;
      default:
        LOG(LM_STD, Fmtmsg("  -->δ֪���ֶ�����[%d]...", pdesc->type), "INFO")
        break;
      }
    }
    fprintf(fp, "\n");
  }

  LOG(LM_STD, Fmtmsg(" ������¼��=%d", rowcount), __func__)
  
  if (rc < 0)
  {
    fclose(fp);
    DCIFreeCursor(cur);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("�����쳣����ȡ���ݿ�����ʧ��[%s]", errmsg),
           fpub_GetCompname(lXmlhandle))
  }
  fclose(fp);
  DCIFreeCursor(cur);
  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

  return COMPRET_SUCC;
}

int main()
{
  return 0;
}
