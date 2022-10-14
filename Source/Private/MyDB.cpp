#include "MyDB.h"
#include <iostream>



#define Host "localhost"
#define User "root"
#define PW "0000"
#define DB "UE4SocketDB"
#define Port 3306



MyDB::MyDB()
{
	MySql = NULL;
	mysql_init(&mysql);
	SqlResult = NULL;
	SqlRow = NULL;
	SqlStat = true;
}

MyDB::~MyDB()
{
	mysql_close(MySql);
}

bool MyDB::ConnectDataBase()
{
	// Database ����
	MySql = mysql_real_connect(&mysql, Host, User, PW, DB, Port, NULL, 0);

	// ���� or ���� ó��
	if (!MySql)
	{
		std::cout << "Connect Failed : Error" << std::endl;
		return false;
	}
	else
	{
		std::cout << "Connect Success\n" << std::endl;
		return true;
	}
}

bool MyDB::QueryTransmission(const char* Value)
{
	// Query ��û
	SqlStat = mysql_query(MySql, Value);

	// Query ���� ��
	if (SqlStat)
	{
		fprintf(stderr, "Query Error : %s", mysql_error(MySql));
		return false;
	}

	return true;
}

bool MyDB::QueryOutput()
{
	// Query ��û ��� ����
	SqlResult = mysql_store_result(MySql);

	// Query ��� ���
	while ((SqlRow = mysql_fetch_row(SqlResult)) != NULL)
	{
		for (unsigned int i = 0; i < mysql_num_fields(SqlResult); ++i)
		{
			std::cout << SqlRow[i] << "  ";
		}
		std::cout << std::endl;
	}

	return true;
}

void MyDB::QueryInit()
{
	mysql_free_result(SqlResult);
}
