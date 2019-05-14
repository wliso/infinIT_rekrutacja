#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Table.cpp"
using namespace std;
vector<string> readProcedure(string name)
{
	ifstream file(name);
	vector<string> word;
	char let;	
	do
	{
		string tmp;	
		do
		{
			file >> noskipws >> let;
			if (let != ';' and !isspace(let) and let != ',' and let != ':') {
				tmp.push_back(let);
				//cout << "jestem tu" << endl;
			}
		} while (!isspace(let) and let != ';' and let != ',' and let != ':');
		if(tmp.size()!=0) word.push_back(tmp);
	} while (let != ';');
	for (int i = 0; i < word.size(); i++)
		cout << " " << i << " " << word[i];
	return word;
}

Table& create(vector<string> proc) {
	string tmp,tmp2;
	vector<Column*> columns;
	vector<Column*> columns2;
	vector<Tstring> name,name2;
	int i = 4;
	int j = 5;
	int n = 0;
	do {	
		tmp = proc[i];
		name.push_back(proc[i]);
		i = i + 2;
		tmp = proc[i];

		tmp2 = proc[j];
		name2.push_back(proc[j]);		
		j = j + 2;
		n = n + 1;
	} while (tmp.compare(")"));
	for (int i = 0; i < name.size(); i++) {
		columns.push_back(&name[i]);
		columns2.push_back(&name2[i]);
	}
	Row *row = new Row(columns);
	//Row row(columns);
	vector<Row> rowss;
	rowss.push_back(*row);
	Row *row2 = new Row(columns2);
	//row2->columns = columns2;
	rowss.push_back(*row2);
	Table *newtable = new Table();
	//Table newTable(proc[2], rowss);
	newtable->tableName = proc[2];
	newtable->rows = rowss;
	newtable->displayTable();
	return *newtable;
}

Table& whichProcedure(vector<string> proc) {
	if (proc[0].compare("CREATE")==0) { 
		cout << " create" << endl; 
		//Table table;
		//table.create(proc);
		return create(proc);
	}
	else if (proc[0].compare("INSERT") == 0) { cout << "insert" << endl; }
	else if (proc[0].compare("SELECT") == 0) { cout << "select" << endl; }
	else if (proc[0].compare("DROP") == 0) { cout << "srop" << endl; }
	else if (proc[0].compare("DELETE") == 0) { cout << "delete" << endl; }
	else cout << "there isnt such an option" << endl;
}

int main()
{
	vector<string> strings{ "mama","tata","babcia" };
	string name = "imie";
	vector<Tstring> tstrings;
	vector<Column*> columns;
	tstrings.push_back(strings[0]);	
	tstrings.push_back(strings[1]);	
	tstrings.push_back(strings[2]);
	columns.push_back(&tstrings[0]);
	columns.push_back(&tstrings[1]);	
	columns.push_back(&tstrings[2]);
	//Tstring cl1(name);
	//Tstring cl2("nazwisko");
	//Tstring cl3("wiek");
	//vector<Column*> columns;
	//columns.push_back(&cl1);
	//columns.push_back(&cl2);
	//columns.push_back(&cl3);
	Row row1(columns);

	Tstring cl21("weronika");
	Tstring cl22("lisowska");
	Tint cl23(22);
	vector<Column*> columns2;
	columns2.push_back(&cl21);
	columns2.push_back(&cl22);
	columns2.push_back(&cl23);
	Row row2(columns2);
	vector<Row> rows;
	rows.push_back(row1);
	rows.push_back(row2);
	//Table table("users",rows);
	//table.displayTable();
	//string st = whichProcedure(readProcedure("test.txt")).tableName;
	//vector<Row> ro = whichProcedure(readProcedure("test.txt")).rows;
	//Table table2 = table;
	Table table2(whichProcedure(readProcedure("test.txt")));
	table2.displayTable();
}
