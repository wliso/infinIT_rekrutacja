#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include "Column.cpp"
class Row {
public:
	vector<Column*> columns;
	Row() {}
	Row(const vector<Column*> &column) {
		columns = column;
	}

	string displayRow() {
		string st;
		for (int i = 0; i < columns.size(); i++) {
			st += columns[i]->display();
			//cout << " ";
			st += " ";
		}
		return st;
	}
	vector<int> findColumn(vector<string> column) {
		vector<int> ind;
		for (int i = 0; i < columns.size(); i++) 
		for(int j=0;j < column.size();j++)
		{
			if (columns[i]->returnSt().compare(column[j]) == 0) ind.push_back(i);
		}
		
		return ind;
	}	
};
