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
	
};
