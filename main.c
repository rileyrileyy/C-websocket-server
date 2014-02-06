#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <process.h>
#include "websocket.h"

struct sockaddr_in server, client;
WSADATA wsa;
SOCKET sock, new_socket;

void listenForClients();

int main(int argc , char *argv[]){
	
    server.sin_port = htons(23415);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

	WSAStartup(MAKEWORD(2,2),&wsa);
    sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    bind(sock,(struct sockaddr *)&server, sizeof(server));

    listen(sock,3);

    listenForClients();

    closesocket(sock);
 	WSACleanup();
    return 0;
}

void listenForClients(SOCKET *serv){

    char read[1024];
    int len;

    while((new_socket = accept((SOCKET)serv,(struct sockaddr*)&client,NULL))){
        len = recv(new_socket,read,1024,0);
        read[len] = '\0';
        puts(read);
        WShandshake(read,len,&new_socket);
        closesocket(new_socket);
    }    
}
