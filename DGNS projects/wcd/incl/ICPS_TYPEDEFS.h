/*组件参数：初始化文件管理信息*/
typedef struct TPARA_FILEINFOINIT
{
    char busi_date[8 + 1]; /*业务日期*/
    char busi_no[10 + 1]; /*业务编号*/
} PARA_FILEINFOINIT;

/*组件参数：对账明细文件入库*/
typedef struct TPARA_CHKFILEINS
{
    char busi_date[8 + 1]; /*业务日期*/
    char busi_no[10 + 1]; /*业务编号*/
    char file_type[31 + 1]; /*文件类型*/
    char file_path[255 + 1]; /*文件路径*/
} PARA_CHKFILEINS;
/*组件参数：对账明细文件入库*/
typedef struct WPARA_CHKFILEINS
{
	char busi_date[8 + 1]; /*业务日期*/
	char busi_no[10 + 1]; /*业务编号*/
	char file_type[46 + 1]; /*文件类型*/
	char file_path[255 + 1]; /*文件路径*/
} WBC_PARA_CHKFILEINS;
/*组件参数：生成第三方报文标示号*/
typedef struct TPARA_GENMSGID
{
    char busi_no[10 + 1]; /*业务编号*/
    char plt_date[8 + 1]; /*平台日期*/
    char plt_serial[16 + 1]; /*平台流水号*/
    char msg_id_path[255 + 1]; /*报文标示号存放路径*/
} PARA_GENMSGID;

/*组件参数：文件预处理*/
typedef struct TPARA_FILEPRECHK
{
    char date[10 + 1]; /*文件所在文件夹日期*/
    char busi_no[10 + 1]; /*业务编号*/
    char bank_id[10 + 1]; /*本行代码*/
    char path[255 + 1]; /*本地存储目录*/
} PARA_FILEPRECHK;
/*微车贷文件预处理组件参数*/
typedef struct WPARA_FILEPRECHK
{
	char date[10 + 1]; /*文件所在文件夹日期*/
	char busi_no[10 + 1]; /*业务编号*/
	char bank_id[10 + 1]; /*本行代码*/
	char path[255 + 1]; /*本地存储目录*/
	char gcdcpbh[10+1];/*购车贷产品编号*/
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
