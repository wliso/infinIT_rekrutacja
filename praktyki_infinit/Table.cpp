#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Table.h"
using namespace std;


string Table:: displayTable() {
		string st;
		//cout << tableName << endl;
		st += tableName;
		st += "\n";
		for (int i = 0; i < rows.size(); i++) {
			st += rows[i].displayRow();
			//cout << endl;
			st += "\n";
			if (i == 0) i++;
		}
		return st;
	}

	void Table::displayTableOrder(vector<string> columnOrder, vector<string> column) {
		vector<int> ind = rows[0].findColumn(column);
		cout << tableName << endl;
		cout << rows[0].displayRow();
		if (ind.size() == column.size()) {
			for (int i = 0; i < columnOrder.size(); i++) {
				vector<int> order;
				order = whichRow(columnOrder[i], ind[0]);
				for (int s = 0; s < order.size(); s++)
				{
					cout << rows[order[s]].displayRow();
					cout << endl;
					if (s > 0) i++;
				}
			}			
		}
	}
	void Table::displayColumnOrder(vector<string> columnOrder, vector<string> column, vector<string> columns) {
		vector<int> ind = rows[0].findColumn(columns);
		vector<int> ind2 = rows[0].findColumn(column);
		if (ind.size() == columns.size()) {
			cout << tableName << endl;
			for (int j = 0; j < columnOrder.size(); j++) {
				vector<int> order;
				order = whichRow(columnOrder[j], ind2[0]);
				for (int o = 0; o < order.size(); o++) {
					for (int i = 0; i < ind.size(); i++)
					{
						if (i == 0 && j==0 && o == 0) {
							for (int i = 0; i < ind.size(); i++)
							cout << rows[0].columns[ind[i]]->display() << " ";
							cout << endl;
						}
						cout << rows[order[o]].columns[ind[i]]->display();
						cout << " ";
					}
					if (o > 0) j++;
					cout << endl;
				}
			}
		}
		else cout << "There is no column with such name in this table" << endl;
	}

	vector<string> Table::sortColumn(vector<string> column,bool isReverse) {
		vector<string> strings;
		vector<int> ind = rows[0].findColumn(column);
		if (ind.size() == column.size()) {
			Type typ = rows[1].columns[ind[0]]->GetType();
			vector<int> ints;
			vector<float> floats;
			vector<bool> bools;
			for (int j = 2; j < rows.size(); j++) {
				strings.push_back(rows[j].columns[ind[0]]->dataToString());
			}
			int n;
			float f;
			bool b;
			switch (typ)
			{
			case TintT:
				for (int i = 0; i < strings.size(); i++) {
					n = stoi(strings[i]);
					ints.push_back(n);
				}
				sort(ints.begin(), ints.end() + ints.size());
				strings.clear();
				for (int i = 0; i < strings.size(); i++) {
					strings.push_back(to_string(ints[i]));

				}
				break;
			case TfloatT:
				for (int i = 0; i < strings.size(); i++) {
					f = stof(strings[i]);
					floats.push_back(f);
				}
				sort(floats.begin(), floats.end() + floats.size());
				strings.clear();
				for (int i = 0; i < strings.size(); i++) {
					strings.push_back(to_string(floats[i]));

				}
				break;
			case TboolT:
				for (int i = 0; i < strings.size(); i++) {
					istringstream(strings[i]) >> b;
					bools.push_back(b);
				}
				sort(bools.begin(), bools.end() + bools.size());
				strings.clear();
				for (int i = 0; i < strings.size(); i++) {
					strings.push_back(to_string(bools[i]));

				}
				break;
			case TstringT:
				sort(strings.begin(), strings.end());
				break;
			}
			if (isReverse == true) sort(strings.begin(), strings.end(), greater<string>());
		}
		else cout << "There is no column with such name in this table" << endl;
		
		return strings;
	}

	void Table::displayTableColumn(vector<string> column) {
		vector<int> ind = rows[0].findColumn(column);
		if(ind.size()==column.size()){
			cout << tableName << endl;
			for (int j = 0; j < rows.size(); j++) {

				for (int i = 0; i < ind.size(); i++)
				{
					cout << rows[j].columns[ind[i]]->display();
					cout << " ";
				}
				cout << endl;
				if (j == 0) j++;
			}
		}
		else cout << "There is no column with such name in this table" << endl;
	}
	vector<int> Table::whichRow(string word, int column) {
		vector<int> roww;
		for (int i = 2; i < rows.size(); i++) {
			if (rows[i].columns[column]->dataToString().compare(word) == 0)
				roww.push_back(i);
		}
		return roww;
	}
	void Table::deleteRow(vector<int> numRow) {
		for (int i = numRow.size()-1; i >=0 ; i--) {
			rows.erase(rows.begin() + numRow[i]);
		}
	}
	void Table::deleteData() {
		int size = rows.size();
		for (int i = 2; i < size; i++)
			rows.pop_back();
	}
	void Table::writeTableToFile() {
		string name = tableName + ".txt";
		ofstream file(name);

		if (file)
		{
			string st;
			st += tableName;
			for (int i = 0; i < rows.size(); i++) {
				st += rows[i].displayRow();
				st += "\n";
				if (i == 0) i++;
			}
			file << displayTable() << endl;
		}
		else
		{
			cout << "Error in opening file." << endl;
		}
	}



