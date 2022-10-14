#pragma once

#include <mysql.h>

class MySocket
{
public:
	MySocket();
	~MySocket();

	// ���ε� ����
	SOCKET ServerSocket;

	// ���� ����
	SOCKET ClientSocket;

	// Winsock �ε�, Socket ����
	bool CreateSocket();

	// Bind, Listen
	bool BindListenSocket();

	// ���� ����
	bool AcceptSocket();

	// Send
	void SendSocket();

	// Recv
	void RecvSocket();
};