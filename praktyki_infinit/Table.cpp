#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include "Row.h"
using namespace std;

class Table {
public:
	string tableName;
	vector<Row> rows;
	Table() {}
	//Table(string name, vector<Row> row) {
	//	tableName = name;
	//	rows = row;
	//}
	Table(const Table& table) {
		tableName = table.tableName;
		rows = table.rows;
	}
	void displayTable() {
		cout << tableName << endl;
		for (int i = 0; i < rows.size(); i++) {
			rows[i].displayRow();
			//if (i == 0) i++;
		}
	}
};



