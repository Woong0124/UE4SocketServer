#pragma once

#include <mysql.h>

class MyDB
{
public:
	MyDB();
	~MyDB();

	// MYSQL ����
	MYSQL* MySql;

	// MYSQL ���� �ڵ�
	MYSQL mysql;

	// ������ ���� ��, ��� ��� ����ü
	MYSQL_RES* SqlResult;

	// ����� �� ����
	MYSQL_ROW SqlRow;

	// ������ ���� ����
	bool SqlStat;

	// DB����
	bool ConnectDataBase();

	// ������ ����
	bool QueryTransmission(const char* Value);

	// ���� ��� ���
	bool QueryOutput();

	// ���� �ʱ�ȭ
	void QueryInit();
};