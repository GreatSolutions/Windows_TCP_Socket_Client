#include"Socket_Client.h"

void tcp_client::run()
{
	Set_Entrypoint("192.168.2.105", 1337);
	Init_WinsockData();
	Create_Socket();
	Set_hint_struct();
	Connect();
	Interactive_Loop();
}

tcp_client::tcp_client()
{

}


tcp_client::~tcp_client()
{
}

void tcp_client::Set_Entrypoint(std::string ip, int port)
{
	m_ip = ip;
	m_port = port;
}

void tcp_client::Init_WinsockData()
{
	int result = WSAStartup(m_Version, &m_WinsockData);
	if (result != 0) {
		std::cerr << "Can't Initialise WSA! Quitting\n";
		return;
	}
}

void tcp_client::Create_Socket()
{
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Socket == INVALID_SOCKET) {
		std::cerr << "Can't create a socket! Quitting\n";
		return;
	}
}

void tcp_client::Set_hint_struct()
{
	m_hint.sin_family = AF_INET;
	m_hint.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ip.c_str(), &m_hint.sin_addr);
}

void tcp_client::Connect()
{
	int result = ::connect(m_Socket, (sockaddr*)& m_hint, sizeof(m_hint));
	if (result == SOCKET_ERROR) {
		std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << '\n';
		closesocket(m_Socket);
		WSACleanup();
		return;
	}
}

void tcp_client::Interactive_Loop()
{
	char Buffer[4096];
	std::string userInput;
	do
	{
		std::cout << m_TEST << "> ";
		std::getline(std::cin, userInput);
		if (userInput.size() > 0) {
			int sendResult = send(m_Socket, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {
				ZeroMemory(Buffer, 4096);
				int bytesReceived = recv(m_Socket, Buffer, 4096, 0);
				if (bytesReceived > 0) {
					std::cout << "Server(Pi to Client)> " << std::string(Buffer, 0, bytesReceived) << '\n';
				}
			}
		}
	} while (userInput.size() > 0);
	closesocket(m_Socket);
	WSACleanup();
}