#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <fstream>
#include "ListTable.h"
using namespace std;

	int ListTable::findName(string name) {
		for (int i = 0; i < tables.size(); i++) 
			if (tables[i].tableName.compare(name) == 0) return i;
			cout << "There is no table with such name" << endl;
			return -1;
	}

	void ListTable::whichProcedure(vector<string> proc) {
		if (proc.size() != 0) {
			if (proc[0].compare("CREATE") == 0) {
				create(proc);
			}
			else if (proc[0].compare("INSERT") == 0) {
				insert(proc);
			}
			else if (proc[0].compare("SELECT") == 0) {
				if (proc[proc.size() - 4].compare("WHERE") == 0) {
					selectWhere(proc);
				}
				else if (proc[proc.size() - 3].compare("ORDER") == 0 || proc[proc.size() - 3].compare("BY") == 0) {
					selectOrderBy(proc);
				}
				else {
					select(proc);
				}
				cout << endl;
			}
			else if (proc[0].compare("DROP") == 0) { 
				drop(proc);
			}
			else if (proc[0].compare("DELETE") == 0) { 
				if (proc.size() > 3) {

					deleteWhere(proc);
				}
				else
					deleteFrom(proc);
			}
		}
	}

	vector<string> ListTable::readProcedure(string name, int & position)
	{
		ifstream file(name);
		file.seekg(position, ios::beg);
		vector<string> word;
		char let;
		do
		{
			string tmp;
			do
			{
				file >> noskipws >> let;
				position++;
				if (let == '\"') {
					do {
						tmp.push_back(let);
						file >> noskipws >> let;
						position++;
					} while (let != '\"');	
				} 
				if (let != ';' and !isspace(let) and let != ',' and let != ':') {
					tmp.push_back(let);
				}
			} while (!isspace(let) and let != ';' and let != ',' and let != ':');
			if (tmp.size() != 0) word.push_back(tmp);
		} while (let != ';');
		return word;
	}

	void ListTable::readFromFile(string name, int& positionRead) {
		ifstream file(name);
		char tmp;
		file >> tmp;
		while (!file.eof())
		{
			whichProcedure(readProcedure(name, positionRead));
			file.seekg(positionRead, ios::beg);
			positionRead++;
			file >> tmp;
		}
	}

	Table ListTable::createNewTable(vector<string> proc) {
		string tmp, tmp2;
		vector<Column*> columns;
		vector<Column*> columns2;
		vector<Tstring> name, name2;
		int i = 4;
		int j = 5;
		do {
			name.push_back(proc[i]);
			i = i + 2;
			tmp = proc[i];

			name2.push_back(proc[j]);
			j = j + 2;
		} while (tmp.compare(")"));
		for (int i = 0; i < name.size(); i++) {
			columns.push_back(new Tstring(name[i]));
			columns2.push_back(new Tstring(name2[i]));
		}
		Row *row = new Row(columns);
		vector<Row> rowss;
		rowss.push_back(*row);
		Row *row2 = new Row(columns2);
		rowss.push_back(*row2);
		Table *newTable = new Table();
		newTable->tableName = proc[2];
		newTable->rows = rowss;
		newTable->writeTableToFile();
		return *newTable;
	}
	void ListTable::create(vector<string> proc) {
		bool iftableAlreadyExist = false;
		for (int i = 0; i < tables.size(); i++) {
			if (tables[i].tableName.compare(proc[2]) == 0)
			{
				iftableAlreadyExist = true;
				cout << "Table with that name already exists." << endl;
			}
		}
		if (!iftableAlreadyExist)
		{			
			tables.push_back(createNewTable(proc));
		}
	}

	void ListTable::printNames() {
		for (Table const& i : tables) {
			cout << "1. "<<i.tableName<< endl;
		}
	}

	Column* ListTable::whatType(string type) {
		if (type.compare("Boolean") == 0) {
			return new Tbool();
		}
		else if(type.compare("Integer")==0){
			return new Tint();
		}
		else if(type.compare("Float")==0){
			return new Tfloat();
		}
		else if(type.compare("Varchar")==0){
			return new Tstring();
		}
	}

	bool ListTable::ifvarchar(string word) {
		string::iterator first = word.begin();
		string::iterator last = word.end() - 1;
		char f = *first;
		char l = *last;
		if (f == '\"' and l == '\"') return true;
		else return false;
	}

	bool ListTable::ifint(string word) {
		for (int i = 0; i < word.length(); i++) if (word[i] > '9' || word[i] < '0') return false;

		return true;
	}

	bool ListTable::iffloat(string word) {
		try {
			float num = stof(word);
		}
		catch (const std::exception& e) {
			cout << "Invalid input: " << e.what() << '\n';
			return 0;
		}
		return 1;
	}

	bool ListTable::ifbool(string word) {
		if (word.compare("true") == 0 or word.compare("false") == 0)
			return true;
		else return false;
	}

	bool ListTable::allCorrect(vector<bool> correct) {
		for (int i = 0; i < correct.size(); i++) {
			if (correct[i] == false) {
				cout << "sprawdz poprawnosc wpisanych danych." << endl;
				return false;
			}
		}		
		return true;
	}

	vector<Column*> ListTable::addTypeColumn(string word,Type typ, vector<Column*> &columns) {
		int n;
		float f;
		bool b;
		switch (typ)
		{
		case TintT:
			n = stoi(word);
			columns.push_back(new Tint(n));
			break;
		case TfloatT:
			f = stof(word);
			columns.push_back(new Tfloat(f));
			break;
		case TboolT:
			istringstream(word) >> b;
			columns.push_back(new Tbool(b));
			break;
		case TstringT:
			columns.push_back(new Tstring(word));
			break;
		}
		return columns;
	}

	void ListTable::insert(vector<string> proc) {
		int ind = findName(proc[2]);
		if (ind != -1) {
			vector<bool> correct;
			for (int i = 0; i < tables[ind].rows[0].columns.size(); i++)
			{
				ifTypeSwitch(proc[i + 4], ind, i, correct);
			}
			bool cor = allCorrect(correct);
			int tmp = tables[ind].rows[0].columns.size();
			if (tmp != proc.size() - 5) { 
				cor = false; 
				cout << "too many or to little arguments."<<endl;
			}

			if (cor) {
				vector<Column*> columns;
				vector<string> names;
				int no = 0;
				for (int i = 0; i < tables[ind].rows[0].columns.size(); i++) {
					Column* col = whatType(tables[ind].rows[1].columns[i]->returnSt());
					Type typ = col->GetType();
					names.push_back(proc[i + 4]);
					addTypeColumn(names[no], typ, columns);
					no++;
				}
				Row *row = new Row(columns);
				tables[ind].rows.push_back(*row);
				tables[ind].writeTableToFile();
			}
		}
	}

	vector<bool> ListTable::ifTypeSwitch(string word,int ind,int i, vector<bool> &correct) {
		Column* col = whatType(tables[ind].rows[1].columns[i]->returnSt());
		Type typ = col->GetType();
		switch (typ)
		{
		case TintT:
			correct.push_back(ifint(word));
			break;
		case TfloatT:
			correct.push_back(iffloat(word));
			break;
		case TboolT:
			correct.push_back(ifbool(word));
			break;
		case TstringT:
			correct.push_back(ifvarchar(word));
			break;
		}
		return correct;
	}

	void ListTable::select(vector<string> proc) {
		int tmp = 0;
		int j = 1;
		vector<string> columnNames;
		for (int i = 0; i < tables.size(); i++) {
			if (tables[i].tableName.compare(proc[proc.size()-1]) == 0)
			{
				tmp = 1;
				if (proc[1].compare("*") == 0) {
					
					cout << tables[i].displayTable();
				}
				else {
					while (j<proc.size()-2) {
						columnNames.push_back(proc[j]);
						j++;
					}
					tables[i].displayTableColumn(columnNames);
				}					
			}
		}
		if (tmp == 0) cout << "There is no table with that name." << endl;
	}

	void ListTable::selectWhere(vector<string> proc) {
		vector<string>::iterator it = find(proc.begin(), proc.end(), "WHERE");
		int ind = distance(proc.begin(), it);
		int tmp = 0;
		int j = 1;
		vector<string> columnNames;
		int i = findName(proc[ind - 1]);
		if (i != -1)
		{
			vector<string> st;
			st.push_back(proc[ind + 1]);
			vector<int> numb;
			numb = tables[i].rows[0].findColumn(st);
			if (numb.size() != 0)
			{
				vector<bool> correct;
				ifTypeSwitch(proc[ind + 3], i, numb[0], correct);
				tmp = 1;
				if (correct.size()!=0) {
					vector<int> row = tables[i].whichRow(proc[ind + 3], numb[0]);
					if (row.size() != 0) {
						if (proc[1].compare("*") == 0) {
							cout << tables[i].tableName << endl;
							 cout << tables[i].rows[0].displayRow();
							for (int j = 0; j < row.size(); j++) {
								cout << tables[i].rows[row[j]].displayRow();
								cout << endl;
							}
						}
						else {
							while (j < ind - 2) {
								columnNames.push_back(proc[j]);
								j++;
							}
							tables[i].rows[row[j]].columns[numb[0]]->display();
								cout << tables[i].tableName << endl;
								for (int j = 0; j < row.size(); j++) {
									cout << tables[i].rows[row[j]].columns[numb[0]]->display();
									cout << endl;
								}
						}
					}
					else cout << "There isnt such data in this table" << endl;
				}
				else cout << "invalid argument after function WHERE" << endl;
			}
			else cout << "there isnt column with such name" << endl;
		}
		if (tmp == 0) cout << "There is no table with that name." << endl;
	}

	void ListTable::selectOrderBy(vector<string> proc) {
		int tmp = 0;
		int j = 1;
		int ros = 0;
		bool isReverse=false;
		if (proc[proc.size() - 1].compare("DESC") == 0) {
			isReverse = true;
			ros = 1;
		}
		vector<string> columnNames;
		vector<string> columnOrder;
		vector<string> strings;
		columnOrder.push_back(proc[proc.size() - 1-ros]);
		
		int i = findName(proc[proc.size() - 4 -ros]);
		if (i != -1){
			strings = tables[i].sortColumn(columnOrder,isReverse);
				tmp = 1;
				if (proc[1].compare("*") == 0) {

					tables[i].displayTableOrder(strings,columnOrder);
				}
				else {
					while (j < proc.size() - 5-ros) {
						columnNames.push_back(proc[j]);
						j++;
					}
					tables[i].displayColumnOrder(strings,columnOrder,columnNames);
				}
		}
		if (tmp == 0) cout << "There is no table with that name." << endl;
	}

	void ListTable::drop(vector<string> proc) {
		int ind = findName(proc[1]);
		if (ind == -1)
			cout << "There is no table with such name." << endl;
		else
		{
			tables.erase(tables.begin() + ind);
			string st = tables[ind].tableName + ".txt";
			const char* ch = st.c_str();
			remove(ch);

		}
	}

	void ListTable::deleteFrom(vector<string> proc) {
		int ind = findName(proc[2]);
		if (ind == -1)
			cout << "There is no table with such name." << endl;
		else {
			tables[ind].deleteData();
			tables[ind].writeTableToFile();
		}
	}

	void ListTable::deleteWhere(vector<string> proc) {
		int ind = 3;
		int tmp = 0;
		int j = 1;
		vector<string> columnNames;
		int nam = findName(proc[ind - 1]);
		if (nam != -1)
		{
			vector<string> st;
			st.push_back(proc[ind + 1]);
			vector<int> numb;
			numb = tables[nam].rows[0].findColumn(st);
			if (numb.size() != 0)
			{
				vector<bool> correct;
				ifTypeSwitch(proc[ind + 3], nam, numb[0], correct);
				tmp = 1;
				if (correct.size() != 0) {
					vector<int> row = tables[nam].whichRow(proc[ind + 3], numb[0]);
					if (row.size() != 0) {
						tables[nam].deleteRow(row);
						tables[nam].writeTableToFile();
					}
					else cout << "There isnt such data in this table" << endl;
				}
				else cout << "invalid argument after function WHERE" << endl;
			}
			else cout << "there isnt column with such name" << endl;
		}
		if (tmp == 0) cout << "There is no table with that name." << endl;
	}