#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "ListTable.h"
using namespace std;





int main()
{
	ListTable ListOfTables;
	//ListOfTables.whichProcedure(readProcedure("test.txt"));
	int positionRead = 0;
	ListOfTables.readFromFile("test.txt",positionRead);
	//ListOfTables.tables[0].displayTable();
	//ListOfTables.printNames();
	//ListOfTables.whichProcedure(readProcedure("select.txt"));
	//ListOfTables.printNames();

}
