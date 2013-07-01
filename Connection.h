#include "stdafx.h"

#pragma once

class Connection
{
public:
  Connection(int mPort);
	~Connection(void);
	bool sendMessage(char message[]);
	char *recvMessage(void){
	char *pointer = RecvBuff;
	std::cout << "[Info] Dentro de recvMessage..." << std::endl;
	recv (comm_socket, RecvBuff, sizeof(RecvBuff), 0);
	std::cout << "[Servidor] Datos recibidos: " << RecvBuff << std::endl;
	return pointer;
	};
private:
	bool rConnection();
	WSADATA wsaData;
	SOCKET conn_socket,comm_socket;
	SOCKET comunicacion;
	struct sockaddr_in server;
	struct sockaddr_in client;
	struct hostent *hp;
	int resp,stsize;
	char RecvBuff[512];
	char SendBuff[512];
};
