#pragma comment (lib, "libmysql.lib")

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

	// Disconnect database
	mysql_close(MySql);
	return 0;
}