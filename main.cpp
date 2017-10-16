#include"People.h"
#include"system.h"
#include"lesson.h"
#include<fstream>

using std::ifstream;
using std::ofstream;

void getuser(map<int, Student> &stu, map<int, Teacher> &tea);
void outuser(map<int, Student> &stu, map<int, Teacher> &tea);
void getlesson(map<int, Lesson> &les);
void outlesson(map<int, Lesson> &les);

int main() {
	map<int, Student> stu;
	map<int, Teacher> tea;
	map<int, Lesson> les;
	getuser(stu, tea);
	getlesson(les);
	loginface(stu,tea,les);
	outuser(stu, tea);
	outlesson(les);
	return 0;
}

void getuser(map<int, Student> &stu, map<int, Teacher> &tea) {
	ifstream fin("user.txt");
	int num1,num2;
	fin >> num1;
	for (int a = 0; a < num1; a++) {
		string name, password;
		int id, lid1, lid2;
		fin >> id >> password >> name >> lid1 >> lid2;
		Teacher temp(id, name);
		if (lid1 != 0) {
			temp.setlessonid(lid1);
		}
		if (lid2 != 0) {
			temp.setlessonid(lid2);
		}
		
		temp.setpassword(password);
		tea.insert(pair<int, Teacher>(id, temp));
	}
	fin >> num2;
	for (int a = 0; a < num2; a++) {
		string name, password;
		int id, lid1, lid2;
		fin >> id >> password >> name >> lid1 >> lid2;
		Student temp(id, name);
		if (lid1 != 0) {
			temp.setlessonid(lid1);
		}
		if (lid2 != 0) {
			temp.setlessonid(lid2);
		}
		temp.setpassword(password);
		stu.insert(pair<int, Student>(id, temp));
	}
	fin.close();
}

void outuser(map<int, Student>& stu, map<int, Teacher>& tea) {
	ofstream fout("user.txt");
	fout << tea.size() << endl;
	map<int, Teacher> ::iterator iter;
	if (!tea.empty()) {
		for (iter = tea.begin(); iter != tea.end(); ++iter) {
			fout << iter->first << " " << iter->second.getpassword() << " " << iter->second.getname() << " "
				<< iter->second.getlessonidfirst() << " " << iter->second.getlessonidsecond() << endl;
		}
	}
	fout << stu.size() << endl;
	map<int, Student> ::iterator it;
	if (!stu.empty()) {
		for (it = stu.begin(); it != stu.end(); ++it) {
			fout << it->first << " " << it->second.getpassword() << " " << it->second.getname() << " "
				<< it->second.getlessonidfirst() << " " << it->second.getlessonidsecond() << endl;
		}
	}
	fout.close();
}

void getlesson(map<int, Lesson> &les) {
	ifstream fin("lesson.txt");
	int num1;
	fin >> num1;
	for (int a = 0; a < num1; a++) {
		string cname,tname;
		int tid, cid, cap;
		fin >> cid >> cname >> tid >> tname >> cap;
		Lesson ltemp(cid, cname, cap, tid, tname);
		int f2;
		fin >> f2;
		for (int a = 0; a < f2; a++) {
			string name, password;
			int id, lid1, lid2;
			fin >> id >> password >> name >> lid1 >> lid2;
			Student temp(id, name);
			if (lid1 != 0) {
				temp.setlessonid(lid1);
			}
			if (lid2 != 0) {
				temp.setlessonid(lid2);
			}
			temp.setpassword(password);
			ltemp.chooselesson(id, temp);
		}
		les.insert(pair<int, Lesson>(cid, ltemp));
	}
	fin.close();
}

void outlesson(map<int, Lesson> &les) {
	ofstream fout("lesson.txt");
	fout << les.size() << endl;
	map<int, Lesson> ::iterator iter;
	if (!les.empty()) {
		for (iter = les.begin(); iter != les.end(); ++iter) {
			fout << iter->first << " "  << iter->second.getcname() << " " << iter->second.gettid()
				<< " " << iter->second.gettname() << " " << iter->second.getcap() << endl;
			fout << iter->second.getnow() << endl;
			map<int, Student> ::iterator it;
			if(!iter->second.stu.empty())
			for (it = iter->second.stu.begin(); it != iter->second.stu.end(); ++it) {
				fout << it->first << " " << it->second.getpassword() << " " << it->second.getname() << " "
					<< it->second.getlessonidfirst() << " " << it->second.getlessonidsecond() << endl;
			}
		}
	}
	fout.close();
}
