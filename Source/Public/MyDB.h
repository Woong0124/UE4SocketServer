#pragma once

#include <mysql.h>
#include "DataStruct.h"

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

	// ���� ��� ����ü�� ����
	void QueryStructInsert(DataStruct* DStruct);

	// ���� �ʱ�ȭ
	void QueryInit();
};