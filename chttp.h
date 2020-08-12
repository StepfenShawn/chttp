#ifndef _CHTTP_H_
#define _CHTTP_H_

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>

#ifdef LINUX
#include <sys/socket.h>
#else

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32")
#pragma comment(lib, "Mswsock")

/* GET request */
int 
GET(const char* host, int port, const char* path)
{
    int i;
    SOCKET fd;
    SOCKADDR_IN addr;
    WSADATA wsadata;

    /* WIN32 version */
    i = WSAStartup(0x0202, &wsadata);
    /* Create and init a socket */
    fd = socket(PF_INET, SOCK_STREAM, 0);
    addr.sin_addr.S_un.S_addr = 0;
    addr.sin_family = AF_INET;
    addr.sin_port = 0;

    i = bind(fd, (sockaddr*)&addr, sizeof(SOCKADDR_IN));

    struct hostent *ip = gethostbyname(host);
    addr.sin_addr.S_un.S_addr = inet_addr(inet_ntoa(*(struct in_addr*)ip->h_addr_list[0])); 
    addr.sin_port = ntohs(port);

    i = connect(fd, (sockaddr*)&addr, sizeof(SOCKADDR_IN));

    if(i != NOERROR)
    {
        puts("Can not connect to..\r\n");
        exit(1);
    }
    char* buffer = (char*)malloc(sizeof(char) * 1023);
    i = sprintf(buffer, "GET /%s HTTP/1.1\r\n"
                        "Host: %s\r\n"
                        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64)\r\n"
                        "content-type: text/css; charset=utf-8\r\n"
                        "Connection:close\r\n"
                        "X-Power:XXX\r\n\r\n"
                        ,path,host
    );

    int n = send(fd, buffer, i, 0);
    if(n == i)
    {
        while(1)
        {
            i = recv(fd, buffer, 1024, 0);
            if(i <= 0)
            {
                break;
            }
            buffer[i] = '\0';
            printf("%s\r\n", buffer);
        }
    }
    free(buffer);

    /* Close the socket */
    i = closesocket(fd);
    i = WSACleanup();
    system("pause");

    return 0;
}

/* Post request */
int
POST(const char* host, int port, const char* path)
{
        int i;
    SOCKET fd;
    SOCKADDR_IN addr;
    WSADATA wsadata;

    /* WIN32 version */
    i = WSAStartup(0x0202, &wsadata);
    /* Create and init a socket */
    fd = socket(PF_INET, SOCK_STREAM, 0);
    addr.sin_addr.S_un.S_addr = 0;
    addr.sin_family = AF_INET;
    addr.sin_port = 0;

    i = bind(fd, (sockaddr*)&addr, sizeof(SOCKADDR_IN));

    struct hostent *ip = gethostbyname(host);
    addr.sin_addr.S_un.S_addr = inet_addr(inet_ntoa(*(struct in_addr*)ip->h_addr_list[0])); 
    addr.sin_port = ntohs(port);

    i = connect(fd, (sockaddr*)&addr, sizeof(SOCKADDR_IN));

    if(i != NOERROR)
    {
        puts("Can not connect to..\r\n");
        exit(1);
    }
    char* buffer = (char*)malloc(sizeof(char) * 1023);
    i = sprintf(buffer, "POST /%s HTTP/1.1\r\n"
                        "Host: %s\r\n"
                        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64)\r\n"
                        "Connection:close\r\n\r\n"
                        ,path,host
    );

    int n = send(fd, buffer, i, 0);
    if(n == i)
    {
        while(1)
        {
            i = recv(fd, buffer, 1024, 0);
            if(i <= 0)
            {
                break;
            }
            buffer[i] = '\0';
            printf("%s\r\n", buffer);
        }
    }
    free(buffer);

    /* Close the socket */
    i = closesocket(fd);
    i = WSACleanup();
    system("pause");

    return 0;
}
#endif /* LINUX */

#endif /* _CHTTP_H_ */