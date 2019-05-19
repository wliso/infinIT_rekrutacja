#pragma once
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
	virtual string returnSt() { return "kk"; }
	virtual string dataToString() { return "sth"; }
	virtual string display() {
		cout << " ";
		string tmp = " ";
		return tmp;
	}

};

class Tint : public Column {
public:
	Type GetType() { return TintT; }

	int data;
	Tint(){}
	Tint(int tmp) {
		data = tmp;
	}
	string dataToString() {
		return to_string(data);
	}
	string display() {
		cout << data;
		string tmp = to_string(data);
		return tmp;
	}
	string returnSt() {
		return "Integer";
	}
};

class Tbool : public Column {
public:
	Type GetType() { return TboolT; }

	bool data;
	string dataToString() {
		return data ? "true" : "false";
	}
	Tbool(){}
	Tbool(bool tmp) {
		data = tmp;
	}
	string returnSt() {
		return "Bool";
	}
	string display() {
		cout << data;
		string tmp = to_string(data);
		return tmp;
	}
};
class Tfloat : public Column {
public:
	Type GetType() { return TfloatT; }

	float data;
	Tfloat(){}
	string dataToString() {
		return to_string(data);
	}
	string returnSt() {
		return "Float";
	}
	Tfloat(float tmp) {
		data = tmp;
	}
	string display() {
		cout << data;
		string tmp = to_string(data);
		return tmp;
	}
};

class Tstring : public Column {
public:
	Type GetType() { return TstringT; }
	Tstring() {}
	string data;
	string dataToString() {
		return data;
	}
	string returnSt() {
		return data;
	}
	Tstring(string tmp) {
		data = tmp;
	}
	Tstring(const Tstring &tmp) {
		data = tmp.data;
	}
	string display() {
		cout << data;
		return data;
	}
};