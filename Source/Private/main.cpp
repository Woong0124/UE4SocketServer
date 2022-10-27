#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "ws2_32.lib")

#include <mysql.h>
#include <iostream>
#include "MyDB.h"
#include "MySocket.h"



int main()
{
	// DB ���� ����
	MyDB* MyDataBase = new(MyDB);

	// DB ���� üũ
	bool DBCheck;

	// DB ����
	DBCheck = MyDataBase->ConnectDataBase();
	if (DBCheck == false)
	{
		return 1;
	}





	// ���� ���� ����
	MySocket* MySock = new(MySocket);

	// ���� ���� üũ
	bool SocketCheck;

	// Socket
	SocketCheck = MySock->CreateSocket();
	if (SocketCheck == false)
	{
		exit(-1);
	}

	// Bind, Listen
	SocketCheck = MySock->BindListenSocket();
	if (SocketCheck == false)
	{
		exit(-1);
	}

	// Accept
	SocketCheck = MySock->AcceptSocket();
	if (SocketCheck == false)
	{
		exit(-1);
	}





	DataStruct* DStruct = new DataStruct;

	while (true)
	{
		MyDataBase->QueryTransmission("SELECT * FROM DATATABLE");

		DStruct->AInfo = SpawnActor;
		while ((MyDataBase->SqlRow = mysql_fetch_row(MyDataBase->SqlResult)) != NULL)
		{
			MyDataBase->QueryStructInsert(DStruct);
			MySock->SendStructSocket(DStruct);
		}

		DStruct->Key = 9;
		DStruct->AInfo = MoveActor;
		DStruct->LocX = 1;
		DStruct->LocY = 0;
		DStruct->LocZ = 0;

		MySock->SendStructSocket(DStruct);
	}

	delete DStruct;



	// ���� ����
	delete MySock;

	// DB ����
	delete MyDataBase;

	return 0;
}