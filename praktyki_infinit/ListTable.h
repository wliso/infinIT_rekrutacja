#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <fstream>
#include "Table.h"
using namespace std;

class ListTable {
public:
	vector<Table> tables;

	int findName(string name);

	void whichProcedure(vector<string> proc);

	vector<string> readProcedure(string name, int & position);

	void readFromFile(string name, int& positionRead);

	Table createNewTable(vector<string> proc);

	void create(vector<string> proc);

	void printNames();

	Column* whatType(string type);

	bool ifvarchar(string word);

	bool ifint(string word);

	bool iffloat(string word);

	bool ifbool(string word);

	bool allCorrect(vector<bool> correct);

	vector<Column*> addTypeColumn(string word, Type typ, vector<Column*> &columns);

	void insert(vector<string> proc);

	vector<bool> ifTypeSwitch(string word, int ind, int i, vector<bool> &correct);

	void select(vector<string> proc);

	void selectWhere(vector<string> proc);

	void selectOrderBy(vector<string> proc);

	void drop(vector<string> proc);

	void deleteFrom(vector<string> proc);

	void deleteWhere(vector<string> proc);


};