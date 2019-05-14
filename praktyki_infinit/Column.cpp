#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Type {
	TintT = 1,
	TboolT = 2,
	TfloatT = 3,
	TstringT = 4
};


class Column {
public:
	virtual Type GetType() = 0;
	//virtual ~Column() {}
	virtual void display() {
		cout << " ";
	}
};

class Tint : public Column {
public:
	Type GetType() { return TintT; }

	int data;
	Tint(int tmp) {
		data = tmp;
	}
	void display() {
		cout << data;
	}
};

class Tbool : public Column {
public:
	Type GetType() { return TboolT; }

	bool data;
	Tbool(bool tmp) {
		data = tmp;
	}
	void display() {
		cout << data;
	}
};
class Tfloat : public Column {
public:
	Type GetType() { return TfloatT; }

	float data;
	Tfloat(float tmp) {
		data = tmp;
	}
	void display() {
		cout << data;
	}
};

class Tstring : public Column {
public:
	Type GetType() { return TstringT; }
	Tstring() {}
	string data;
	Tstring(string tmp) {
		data = tmp;
	}
	Tstring(const Tstring &tmp) {
		data = tmp.data;
	}
	void display() {
		cout << data<< ".";
	}
};