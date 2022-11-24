#include <Winsock2.h>  
#include <ws2tcpip.h>  
#include <iostream>  
using namespace std;  
#pragma comment(lib, "Ws2_32.lib")   

int main()  
{  
    //ʹ��Ws2_32.dll�ĳ�ʼ��  
    WORD wVersionRequested = 0;  
    WSADATA wsaData = {};  
    int err = 0;  
    wVersionRequested = MAKEWORD( 2, 2 );  
    err = WSAStartup( wVersionRequested, &wsaData );  
    if ( err != 0 )   
    {                         
        return -1;  
    }                                    

    if ( LOBYTE( wsaData.wVersion ) != 2 ||  
        HIBYTE( wsaData.wVersion ) != 2 )   
    {  

        WSACleanup( );  
        return -1;   
    }   
    char** pptr = NULL;  
    char szHostName[256] = {};  
    cout << "--------------------------------------" << endl;  
    cout << "����������";  
    while( cin.getline( szHostName, sizeof(szHostName) ) )  
    {  
        HOSTENT* pHostEntry = gethostbyname( szHostName );  
        if( NULL != pHostEntry && szHostName[0] != '\0' )  
        {  
            //��������淶�� 
            cout << "�����淶����" << pHostEntry->h_name << endl;   //�����Խ������淶����Ϊ��������������������

            //�����������
            int i = 0;  
            for ( i = 1, pptr = pHostEntry->h_aliases; *pptr != NULL; ++pptr )  
            {  
                cout << "��������" << i++ << "��" << *pptr << endl;  
            }  

            //���������ַ�б�
            char szIpBuff[32] = {0};  
            for ( i = 1, pptr = pHostEntry->h_addr_list; *pptr != NULL; ++pptr )  
            {  
                memset( szIpBuff, 0, sizeof(szIpBuff) );  
                //inet_ntop�ķ���ֵΪNULL�����ʾʧ�ܣ����򷵻���Ӧ��IP��ַ����ʱszIpRetָ�����szIpBuff�� 
                const char* szIpRet = inet_ntop( pHostEntry->h_addrtype, *pptr, szIpBuff, sizeof(szIpBuff) );  
                if ( szIpBuff != NULL )  
                {  
                    cout << "����IP��ַ" << i++ << "��" << szIpRet << endl;  
                }  

            }  

        }  
        else  
        {  
            cout << "����ʧ�ܣ�" << endl;  
        }  
        memset( szHostName, 0, sizeof(szHostName) );  
        cout << "--------------------------------------" << endl;  
        cout << "����������";  
    }  
    WSACleanup();  
    return 0;  
}  