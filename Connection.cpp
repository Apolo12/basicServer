#include "StdAfx.h"
#include "Connection.h"

Connection::Connection(int mPort){
  std::cout << "[Info] Dentro de Connection..." << std::endl;
   resp=WSAStartup(MAKEWORD(1,0),&wsaData);
  if(resp){
    std::cout << "[Error] Problemas al inicializar socket" << std::endl;
	std::cout << "[resp]" << resp << std::endl;}

  hp=(struct hostent *)gethostbyname("localhost");
  if(!hp){
    std::cout << "[Error] Problemas al acceder al host (gethostbyname)" << std::endl;
	WSACleanup();
	std::cout << "[WSAGetLastError]" << WSAGetLastError() << std::endl; }
  conn_socket=socket(AF_INET,SOCK_STREAM, 0);
  if(conn_socket==INVALID_SOCKET) {
    std::cout << "[Error] Problemas al crear socket" << std::endl;
	WSACleanup();
	std::cout << "[WSAGetLastError]" << WSAGetLastError() << std::endl; }

  memset(&server, 0, sizeof(server)) ;
  memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
  server.sin_family = hp->h_addrtype;
  server.sin_port = htons(mPort);

  resp=bind(conn_socket, (struct sockaddr *)&server, sizeof(server));
  if(resp==SOCKET_ERROR){
    std::cout <<"[Error] Problemas al asociar puerto e ip al socket" << std::endl;
	closesocket(conn_socket);
	WSACleanup();
	std::cout << "[WSAGetLastError]" << WSAGetLastError() << std::endl; }

  if(listen(conn_socket, 1)==SOCKET_ERROR){
	  std::cout << "[Error] Problemas al habilitar conexiones entrantes"<< std::endl;
      closesocket(conn_socket);
	  WSACleanup();
	  std::cout << "[WSAGetLastError]" << WSAGetLastError() << std::endl; }
  if(this->rConnection()){
	  std::cout << "[Servidor] Servidor y cliente operativos..." << std::endl;
	}
}
bool Connection::rConnection(){
	std::cout << "[Info] Dentro de rConnection..." << std::endl;
	std::cout << "[Servidor] Esperando un cliente..." << std::endl;
    stsize=sizeof(struct sockaddr);
    comm_socket=accept(conn_socket,(struct sockaddr *)&client,&stsize);
    if(comm_socket==INVALID_SOCKET){
    std::cout << "[Error] Problemas al aceptar al cliente entrante" << std::endl;
    closesocket(conn_socket);
	WSACleanup();
    std::cout << "[WSAGetLastError]" << WSAGetLastError() << std::endl; 
	return false; }
	std::cout << "[Servidor] Cliente se conecta desde: " << inet_ntoa(client.sin_addr) << std::endl;
	closesocket(conn_socket);
	
	return true;
}

Connection::~Connection(void){
	std::cout << "[Info] Dentro de ~Connection..." << std::endl;
	closesocket(comm_socket);
	WSACleanup();
}

bool Connection::sendMessage(char message[]){
	std::cout << "[Info] Dentro de sendMessage..." << std::endl;
	strcpy_s(SendBuff, message);
    send (comm_socket, SendBuff, sizeof(SendBuff), 0);
	std::cout << "[Servidor] Datos enviados: "<< std::endl <<  SendBuff << std::endl;
	return true;
}
