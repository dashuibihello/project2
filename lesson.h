#pragma once
#include<map>
#include<iostream>
#include<string>

using std::map;
using std::pair;

class Lesson {
	int cid;        //课程id
	string cname;   //课程名
	size_t cap;     //容量
	int tid;        //老师id
	string tname;   //老师名
	
public:
	map<int, Student>stu;
	Lesson(){}
	Lesson(int cid_, string cname_, int cap_, int tid_, string tname_) {
		cid = cid_;
		cname = cname_;
		cap = (size_t)cap_;
		tid = tid_;
		tname = tname_;
	}

	void setcid(int cid_){

	}

	int getcid() {
		return cid;
	}

	int gettid() {
		return tid;
	}

	int getnow() {
		return stu.size();
	}

	size_t getcap() {
		return cap;
	}

	string gettname() {
		return tname;
	}

	string getcname() {
		return cname;
	}

	bool chooselesson(int id, Student s) {
		if (stu.size() < cap) {
			stu.insert(pair<int, Student>(id,s));
			stu[id].setlessonid(cid);
			return true;
		}
		else {
			return false;
		}
	}

	void nochooselesson(int id) {
		stu[id].eraselessonid(cid);
		stu.erase(id);
	}
	void display() {
		cout << "lessonid:" << cid << "\tlessonname:" << cname << "\tnow/capacity:" << stu.size() << "/" << cap << "\tteacher:" << tname << endl;
	}
};
