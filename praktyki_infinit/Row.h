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
	void displayRow() {
		for (int i = 0; i < columns.size(); i++) {
			columns[i]->display();
			cout << " ";
		}
		cout << endl;
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
