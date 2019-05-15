#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <fstream>
#include "Table.cpp"
using namespace std;



class ListTable {
public:
	vector<Table> tables;

	int findName(string name) {
		for (int i = 0; i < tables.size(); i++) 
			if (tables[i].tableName.compare(name) == 0) return i;
			cout << "There is no list with such name" << endl;
			return -1;
	}

	void whichProcedure(vector<string> proc) {
		if (proc[0].compare("CREATE") == 0) {
			cout << " create" << endl;
			this->create(proc);
		}
		else if (proc[0].compare("INSERT") == 0) { 
			cout << "insert" << endl; 
			this->insert(proc);
		}
		else if (proc[0].compare("SELECT") == 0) { 
			cout << "select" << endl; 
			this->select(proc);
		}
		else if (proc[0].compare("DROP") == 0) { cout << "srop" << endl; }
		else if (proc[0].compare("DELETE") == 0) { cout << "delete" << endl; }
		else cout << "there isnt such an option" << endl;
	}

	void create(vector<string> proc) {
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
			cout << " W CREATEEEE" << endl;
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
			Table *newtable = new Table();
			newtable->tableName = proc[2];
			newtable->rows = rowss;
			tables.push_back(*newtable);
		}
	}
	void printNames() {
		for (Table const& i : tables) {
			cout << "1. "<<i.tableName<< endl;
		}
	}

	Column* whatType(string type) {
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

	bool ifvarchar(string word) {
		string::iterator first = word.begin();
		string::iterator last = word.end() - 1;
		char f = *first;
		char l = *last;
		if (f == '\"' and l == '\"') return true;
		else return false;
	}

	bool ifint(string word) {
		for (int i = 0; i < word.length(); i++) if (word[i] > '9' || word[i] < '0') return false;

		return true;
	}

	bool iffloat(string word) {
		try {
			float num = stof(word);
		}
		catch (const std::exception& e) {
			cout << "Invalid input: " << e.what() << '\n';
			return 0;
		}
		return 1;
	}

	bool ifbool(string word) {
		if (word.compare("true") == 0 or word.compare("false") == 0)
			return true;
		else return false;
	}

	bool allCorrect(vector<bool> correct) {
		for (int i = 0; i < correct.size(); i++) {
			if (correct[i] == false) {
				cout << "sprawdz poprawnosc wpisanych danych." << endl;
				return false;
			}
		}
		
		return true;
	}

	void insert(vector<string> proc) {
		int ind = findName(proc[2]);
		if (ind != -1) {
			vector<bool> correct;
			for (int i = 0; i < tables[ind].rows[0].columns.size(); i++)
			{
				Column* col = whatType(tables[ind].rows[1].columns[i]->returnSt());
				Type typ = col->GetType();
				switch (typ)
				{
				case TintT:
					correct.push_back(ifint(proc[i + 4]));
					break;
				case TfloatT:
					correct.push_back(iffloat(proc[i + 4]));
					break;
				case TboolT:
					correct.push_back(ifbool(proc[i + 4]));
					break;
				case TstringT:
					correct.push_back(ifvarchar(proc[i + 4]));
						break;
				}
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
					int n;
					float f;
					bool b;
				
					switch (typ)
					{
					case TintT:
						n = stoi(names[no]);
						columns.push_back(new Tint(n));
						break;
					case TfloatT:
						f = stof(names[no]);
						columns.push_back(new Tfloat(f));
						break;
					case TboolT:
						istringstream(names[no]) >> b;
						columns.push_back(new Tbool(b));
						break;
					case TstringT:
						columns.push_back(new Tstring(names[no]));
						break;
					}
					no++;
				}
				Row *row = new Row(columns);
				tables[ind].rows.push_back(*row);
				tables[ind].displayTable();
			}
		}
	}

	void select(vector<string> proc) {
		int tmp = 0;
		for (int i = 0; i < tables.size(); i++) {
			if (tables[i].tableName.compare(proc[3]) == 0)
			{
				tmp = 1;
				tables[i].displayTable();
			}
		}
		if (tmp == 0) cout << "There is no table with that name." << endl;
	}


	vector<string> readProcedure(string name, int & position)
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
				if (let != ';' and !isspace(let) and let != ',' and let != ':') {
					tmp.push_back(let);
				}
			} while (!isspace(let) and let != ';' and let != ',' and let != ':');
			if (tmp.size() != 0) word.push_back(tmp);
		} while (let != ';');
		for (int i = 0; i < word.size(); i++)
			cout << " " << i << " " << word[i];
		return word;
	}

	void readFromFile(string name,int& positionRead) {
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
};