/*�����������ʼ���ļ�������Ϣ*/
typedef struct TPARA_FILEINFOINIT
{
    char busi_date[8 + 1]; /*ҵ������*/
    char busi_no[10 + 1]; /*ҵ����*/
} PARA_FILEINFOINIT;

/*���������������ϸ�ļ����*/
typedef struct TPARA_CHKFILEINS
{
    char busi_date[8 + 1]; /*ҵ������*/
    char busi_no[10 + 1]; /*ҵ����*/
    char file_type[31 + 1]; /*�ļ�����*/
    char file_path[255 + 1]; /*�ļ�·��*/
} PARA_CHKFILEINS;
/*���������������ϸ�ļ����*/
typedef struct WPARA_CHKFILEINS
{
	char busi_date[8 + 1]; /*ҵ������*/
	char busi_no[10 + 1]; /*ҵ����*/
	char file_type[46 + 1]; /*�ļ�����*/
	char file_path[255 + 1]; /*�ļ�·��*/
} WBC_PARA_CHKFILEINS;
/*������������ɵ��������ı�ʾ��*/
typedef struct TPARA_GENMSGID
{
    char busi_no[10 + 1]; /*ҵ����*/
    char plt_date[8 + 1]; /*ƽ̨����*/
    char plt_serial[16 + 1]; /*ƽ̨��ˮ��*/
    char msg_id_path[255 + 1]; /*���ı�ʾ�Ŵ��·��*/
} PARA_GENMSGID;

/*����������ļ�Ԥ����*/
typedef struct TPARA_FILEPRECHK
{
    char date[10 + 1]; /*�ļ������ļ�������*/
    char busi_no[10 + 1]; /*ҵ����*/
    char bank_id[10 + 1]; /*���д���*/
    char path[255 + 1]; /*���ش洢Ŀ¼*/
} PARA_FILEPRECHK;
/*΢�����ļ�Ԥ�����������*/
typedef struct WPARA_FILEPRECHK
{
	char date[10 + 1]; /*�ļ������ļ�������*/
	char busi_no[10 + 1]; /*ҵ����*/
	char bank_id[10 + 1]; /*���д���*/
	char path[255 + 1]; /*���ش洢Ŀ¼*/
	char gcdcpbh[10+1];/*��������Ʒ���*/
} WBC_PARA_FILEPRECHK;

typedef struct TCreditScore
{
    int success;
    char biz_no[32];
    char zm_score;
}CreditScore;

typedef struct  TVARS
{
    char key[32];
    char value[32];
}VARS;

typedef struct TDAS
{
    int success;
    char biz_no[32];
    VARS vars[15];
}DAS;

typedef struct TIVS
{
    int success;
    char biz_no[32];
    char hit[2];
}IVS;

typedef struct TWatchListii
{
    int success;
    char biz_no[32];
    int is_matched;
}WatchListii;
