#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "ws2_32.lib")

#include <mysql.h>
#include <iostream>



int main()
{
	// MYSQL ����
	MYSQL* MySql = NULL, mysql;

	// ������ ���� ��, ��� ��� ����ü
	MYSQL_RES* SqlResult;

	// ����� �� ����
	MYSQL_ROW SqlRow;

	// ������ ���� ����
	bool SqlStat;

	// MYSQL �ʱ�ȭ
	mysql_init(&mysql);

	// Database ����
	MySql = mysql_real_connect(&mysql, "localhost", "root", "0000", "UE4SocketDB", 3306, NULL, 0);

	// ���� or ���� ó��
	if (!MySql)
	{
		std::cout << "Connect Failed : Error" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Connect Success\n" << std::endl;
	}





	// Winsock �ε�
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		std::cout << "Winsock Error : " << GetLastError() << std::endl;
		exit(-1);
	}

	// Socket ����
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == INVALID_SOCKET)
	{
		std::cout << "fail create Socket : " << GetLastError() << std::endl;
		exit(-1);
	}

	// Socket ���� ���
	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN));
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerSockAddr.sin_port = htons(3307);

	// Socket ���ε�
	int BindServerSock = bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));
	if (BindServerSock == SOCKET_ERROR)
	{
		std::cout << "fail bind : " << GetLastError() << std::endl;
		exit(-1);
	}

	// Socket ���Ŵ��
	BindServerSock = listen(ServerSocket, 0);
	if (BindServerSock == SOCKET_ERROR)
	{
		std::cout << "fail listen : " << GetLastError() << std::endl;
		exit(-1);
	}

	// Client socket ����
	// Ŭ���̾�Ʈ ���� ��û ��, ������ �ִ� ����
	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(SOCKADDR_IN));
	int ClientSockAddrLength = sizeof(ClientSockAddr);

	// Client ���� ����
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
	if (ClientSocket == SOCKET_ERROR)
	{
		std::cout << "fail accept : " << GetLastError() << std::endl;
		exit(-1);
	}





	// Query ��û
	SqlStat = mysql_query(MySql, "SELECT * FROM DATATABLE");

	// Query ���� ��
	if (SqlStat)
	{
		fprintf(stderr, "Query Error : %s", mysql_error(&mysql));
		return 1;
	}

	// Query ��û ��� ����
	SqlResult = mysql_store_result(MySql);

	// Query ��� ���
	while ((SqlRow = mysql_fetch_row(SqlResult)) != NULL)
	{
		for (int i = 0; i < mysql_num_fields(SqlResult); ++i)
		{
			std::cout << SqlRow[i] << "  ";
		}
		std::cout << std::endl;
	}

	// Query ��� �ʱ�ȭ
	mysql_free_result(SqlResult);





	// Socket ����
	closesocket(ServerSocket);
	closesocket(ClientSocket);
	WSACleanup();

	// Database ����
	mysql_close(MySql);
	return 0;
}