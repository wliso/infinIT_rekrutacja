#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Row.h"
using namespace std;

class Table {
public:
	string tableName;
	vector<Row> rows;

	Table() {}
	Table(const Table& table) {
		tableName = table.tableName;
		rows = table.rows;
	}
	string displayTable();

	void displayTableOrder(vector<string> columnOrder, vector<string> column);

	void displayColumnOrder(vector<string> columnOrder, vector<string> column, vector<string> columns);

	vector<string> sortColumn(vector<string> column, bool isReverse);

	void displayTableColumn(vector<string> column);

	vector<int> whichRow(string word, int column);

	void deleteRow(vector<int> numRow);

	void deleteData();

	void writeTableToFile();
};