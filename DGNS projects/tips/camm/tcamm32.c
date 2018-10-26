#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
    char scamm2[256];
    char scamm[256];
    int iret;
    
    if ( argc < 2)
    {
        printf("tcamm string\n");
        return -1;
    }
        
    memset(scamm, 0x00, sizeof(scamm));
    snprintf(scamm, sizeof(scamm),"%s", argv[1]);
    memset(scamm2, 0x00, sizeof(scamm2));
    iret=gaps_encode(0, scamm ,scamm2,sizeof(scamm2));
    if(iret!=0)
    {
        printf("--解密失败[%d][%s]--\n",iret,scamm);
        return -9;        
    }    
    printf("--加密成功[%s]-->[%s]--\n",scamm,scamm2);
    
    memset(scamm, 0x00, sizeof(scamm));
    iret=gaps_encode(1, scamm2 ,scamm,sizeof(scamm2));
    if(iret!=0)
    {
        printf("--解密失败[%d][%s]--\n",iret,scamm2);
        return -9;        
    }
    printf("--解密成功[%s]-->[%s]--\n",scamm2, scamm);
    return 0; 
}
