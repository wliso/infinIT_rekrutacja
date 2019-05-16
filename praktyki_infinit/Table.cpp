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
	void displayTableColumn(vector<string> column) {
		vector<int> ind = rows[0].findColumn(column);
		if(ind.size()==column.size()){
			cout << tableName << endl;
			for (int j = 0; j < rows.size(); j++) {

				for (int i = 0; i < ind.size(); i++)
				{
					rows[j].columns[ind[i]]->display();
					cout << " ";
				}
				cout << endl;
			}
		}
		else cout << "There is no column with such name in this table" << endl;
	}
	vector<int> whichRow(string word, int column) {
		vector<int> roww;
		for (int i = 2; i < rows.size(); i++) {
			if (rows[i].columns[column]->dataToString().compare(word) == 0)
				roww.push_back(i);
		}
		return roww;
	}
};



