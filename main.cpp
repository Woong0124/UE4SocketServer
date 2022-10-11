#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "ws2_32.lib")

#include <mysql.h>
#include <iostream>



int main()
{
	// MYSQL Create
	MYSQL* MySql = NULL, mysql;

	// Structure containing the result when the query is successful
	MYSQL_RES* SqlResult;

	// When the query succeeds, row information of the result structure
	MYSQL_ROW SqlRow;

	// Check query is successful
	bool SqlStat;

	// MYSQL initialization
	mysql_init(&mysql);

	// Connect database
	MySql = mysql_real_connect(&mysql, "localhost", "root", "0000", "UE4SocketDB", 3306, NULL, 0);

	// success or failure messege
	if (!MySql)
	{
		std::cout << "Connect Failed : Error" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Connect Success\n" << std::endl;
	}





	// Load Winsock
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		std::cout << "Winsock Error : " << GetLastError() << std::endl;
		exit(-1);
	}

	// Create socket
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == INVALID_SOCKET)
	{
		std::cout << "fail create Socket : " << GetLastError() << std::endl;
		exit(-1);
	}

	// Socket element
	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN));
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerSockAddr.sin_port = htons(3307);

	// Bind socket
	int BindServerSock = bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));
	if (BindServerSock == SOCKET_ERROR)
	{
		std::cout << "fail bind : " << GetLastError() << std::endl;
		exit(-1);
	}

	// Listening
	BindServerSock = listen(ServerSocket, 0);
	if (BindServerSock == SOCKET_ERROR)
	{
		std::cout << "fail listen : " << GetLastError() << std::endl;
		exit(-1);
	}

	// Create client socket
	// Client request connect >> Accept role
	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(SOCKADDR_IN));
	int ClientSockAddrLength = sizeof(ClientSockAddr);

	// Accept client
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
	if (ClientSocket == SOCKET_ERROR)
	{
		std::cout << "fail accept : " << GetLastError() << std::endl;
		exit(-1);
	}





	// Query request
	SqlStat = mysql_query(MySql, "SELECT * FROM DATATABLE");

	// On query failure messege
	if (SqlStat)
	{
		fprintf(stderr, "Query Error : %s", mysql_error(&mysql));
		return 1;
	}

	// Save result
	SqlResult = mysql_store_result(MySql);

	// Result output
	while ((SqlRow = mysql_fetch_row(SqlResult)) != NULL)
	{
		std::cout << SqlRow[0] << ", " << SqlRow[1] << ", " << SqlRow[2] << ", " << SqlRow[3] << ", " << SqlRow[4] << std::endl;
	}

	// Clear result
	mysql_free_result(SqlResult);





	// Close sockets
	closesocket(ServerSocket);
	closesocket(ClientSocket);
	WSACleanup();

	// Disconnect database
	mysql_close(MySql);
	return 0;
}