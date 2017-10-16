#pragma once
#include<iostream>
#include<map>
#include<string>

using std::string;
using std::cout;
using std::cin;
using std::map;
using std::pair;
using std::endl;

enum Type {
	TEACHER,
	STUDENT,
	ADMIN
};

class People {
private:
	int id;
	string name;
	string password;
	map<int, int> less;
public:
	People(){}
	People(int id_, string name_) {
		id = id_;
		name = name_;
		password = "null";
	}
	void setid(int id_) {
		id = id_;
	}
	void setname(string name_) {
		name = name_;
	}
	void setpassword(string password_) {
		password = password_;
	}
	string getpassword() {
		return password;
	}
	string getname() {
		return name;
	}
	void display() {
		cout << "id: " << id << "\t" <<"name:" << name;
	}
	void setlessonid(int lid_) {
		less.insert(pair<int, int>(lid_, lid_));
	}
	void eraselessonid(int lid_) {
		less.erase(lid_);
	}
	int getlessonidfirst() {
		if (less.size() == 0) {
			return 0;
		}
		map<int, int>::iterator it = less.begin();
		return it->first;
	}
	int getlessonidsecond() {
		if (less.size() < 2) {
			return 0;
		}
		map<int, int>::iterator it = less.begin();
		it++;
		return it->first;
	}
	int getid() {
		return id;
	}
	int now() {
		return less.size();
	}
	virtual Type getType() const = 0;
};


class Student : public People {
public:
	Student(){}
	Student(int id_, string name_):People(id_,name_) {}
	virtual Type getType() const {
		return STUDENT;
	}
};

class Teacher : public People {
public:
	Teacher(int id_, string name_) :People(id_, name_) {}
	Teacher(){}
	virtual Type getType() const {
		return TEACHER;
	}
};

class Admin : public People {
private:
public:
	Admin() :People(10000, "Admin") {
		
	}
	virtual Type getType() const {
		return ADMIN;
	}
};
