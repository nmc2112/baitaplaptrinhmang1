#include<iostream>
#include<stdio.h>
#include<string.h> 
#include<stdlib.h> 
#include<string>
#include<WinSock2.h>
using namespace std;

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main(){
	
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);


    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(1234);


    bind(listener, (SOCKADDR*)&addr, sizeof(addr));


    listen(listener, 5);


    SOCKET client = accept(listener, NULL, NULL);

    char buf[256];

    while (1){
        int ret = recv(client, buf, sizeof(buf), 0);

        if (ret <= 0){
            if (ret == -1)
                ret = WSAGetLastError();
            break;
        }

        if (ret < sizeof(buf))
            buf[ret] = 0;
        cout << buf << endl;
    }


    closesocket(client);
    closesocket(listener);
    WSACleanup();
}
