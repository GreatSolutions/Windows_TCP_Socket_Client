#pragma once
#include<WS2tcpip.h>
#include<iostream>
#include<sstream>
class tcp_client
{
	
private:
	std::string m_ip;
	int			m_port;
	WSADATA		m_WinsockData;
	WORD		m_Version = MAKEWORD(2, 2);
	SOCKET		m_Socket;
	sockaddr_in m_hint;
	std::string m_TEST;
public:
	tcp_client();
	~tcp_client();
	void Set_Entrypoint(std::string ip, int port);
	void Init_WinsockData();
	void Create_Socket();
	void Set_hint_struct();
	void Connect();
	void Interactive_Loop();
	void run();
};

