#include "stdafx.h"
#include "Connection.h"
#define PORT 30000
int main()
{
  char policy[256] = "\r<?xml version=\"1.0\"?>\r\n <!DOCTYPE cross-domain-policy SYSTEM \'/xml/dtds/cross-domain-policy.dtd\'>\r\n <cross-domain-policy>\r\n <allow-access-from domain=\"*\" to-ports=\"1-65535\" />\r\n </cross-domain-policy>\0";
	std::cout << "[Info] Dentro de main..." << std::endl;
	Connection mCon(PORT);
	std::cout << "[Info] Dentro de main..." << std::endl;
	std::cout << "[Info] Dentro de main, last return: " << mCon.recvMessage() << std::endl;
	mCon.sendMessage(policy);
	std::cout << "[Info] Dentro de main..." << std::endl;
	
	char p;
	std::cin >> p;
	return 0;
}
