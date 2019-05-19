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

	ostream &displayRow() {
		ostream & os = cout;
		for (int i = 0; i < columns.size(); i++) {
			os = columns[i]->display();
			os << " ";
		}
		return os;
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
