#pragma once

#include <mysql.h>
#include "DataStruct.h"

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

	// Send Struct
	void SendStructSocket(DataStruct* SpawnDataStruct);

	// Recv Struct
	DataStruct RecvStructSocket(DataStruct* SpawnDataStruct);
};