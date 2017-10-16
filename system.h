#pragma once
#include"lesson.h"
#include"People.h"
#include<Windows.h>


void loginface(map<int, Student> &stu, map<int, Teacher> &tea, map<int, Lesson> &les); //登陆界面
void adminface(map<int, Student> &stu, map<int, Teacher> &tea);                        //教务员界面
void stuinfor(map<int, Student> &stu, map<int, Teacher> &tea);                         //教务员对学生操作
void teainfor(map<int, Student> &stu, map<int, Teacher> &tea);                         //教务员对老师操作
void displaystu(map<int, Student> &stu);                                               //展示现有学生信息
void displaytea(map<int, Teacher> &tea);                                               //展示现有老师信息
void studentface(Student &stu, map<int, Lesson> &les);                                 //学生界面
void teacherface(Teacher &tea, map<int, Lesson> &les);                                 //老师界面
bool verifyinput(string input);                                                        //判断id输入是否合法
bool verifystudentid(const int &keyName, map<int, Student> &stu);                      //判断学生id是否存在
bool verifyteacherid(const int &keyName, map<int, Teacher> &tea);                      //判断老师id是否存在
void addteacher(map<int, Teacher> &tea);                                               //增加老师
void deleteteacher(map<int, Teacher> &tea);                                            //删除老师
void addstudent(map<int, Student> &stu);                                               //增加学生
void deletestudent(map<int, Student> &stu);                                            //删除学生
void createlesson(Teacher &tea, map<int, Lesson> &les);                                //开课
bool verifyidinput(string input);                                                      //确认课程id是否存在
bool verifycapinput(string input);                                                     //确认课程容量是否输入正确
void deletelesson(Teacher &tea, map<int, Lesson> &les);                                //删除课程
void displaylesson(Teacher &tea, map<int, Lesson> &les);                               //展示老师已开课程
void stuclesson(Student &stu, map<int, Lesson> &les);                                  //选课
void stunoclesson(Student &stu, map<int, Lesson> &les);                                //退课
void studisplaylesson(Student &stu, map<int, Lesson> &les);                            //展示学生已选课程
void studisplayalllesson(Student &stu, map<int, Lesson> &les);                         //展示所有课程




void loginface(map<int, Student> &stu, map<int, Teacher> &tea, map<int, Lesson> &les) {
	string id;
	Type t;
	cout << "欢迎来到kiddion的选课系统,请按下列提示输入：" << endl;
	do {
		cout << "请输入id" << endl;
		cin >> id;
		system("cls");
		if (verifyinput(id) == false) {
			cout << "输入id不合法" << endl;
			continue;
		}
		else {
			if (id == "10000") {
				break;
			}
			if (id.size() == 5) {
				int idnum = std::stoi(id);
				if (verifyteacherid(idnum, tea) == false) {
					cout << "输入id不存在" << endl;
					continue;
				}
				else {
					break;
				}					
			}
			else {
				int idnum = std::stoi(id);
				if (verifystudentid(idnum, stu) == false) {
					cout << "输入id不存在" << endl;
					continue;
				}
				else {
					break;
				}
			}
		}
	} while (1);
	system("cls");
	int idnum = std::stoi(id);
	string password;
	string nu = "null";
	do {
		cout << "请输入密码,除管理员以外输入null可更改密码（新密码不能为null）" << endl;
		cin >> password;
		system("cls");
		if (idnum == 10000) {
			if (password != "null") {
				cout << "输入密码错误" << endl;
				continue;
			}
			else {
				t = ADMIN;
				break;
			}
		}
		else {
			if (password == nu) {
				do {
					cout << "请更改密码,请输入旧的密码" << endl;
					string opassword;
					cin >> opassword;
					system("cls");
					if (id.size() == 5) {
						if (tea[idnum].getpassword() == opassword) {
							break;
						}
						else {
							cout << "输入错误请重新输入" << endl;
						}
					}
					else {
						if (stu[idnum].getpassword() == opassword) {
							break;
						}
						else {
							cout << "输入错误请重新输入" << endl;
						}
					}
				} while (1);
				cout << "请输入新密码" << endl;
				string npassword;
				cin >> npassword;
				if (id.size() == 5) {
					tea[idnum].setpassword(npassword);
					cout << "密码修改成功" << endl;
					t = TEACHER;
					break;
				}
				else {
					stu[idnum].setpassword(npassword);
					cout << "密码修改成功" << endl;
					t = STUDENT;
					break;
				}
				
			}
			if (id.size() == 5) {
				if (tea[idnum].getpassword() == password) {
					t = TEACHER;
					break;
				}
				else {
					cout << "输入密码错误" << endl;
					continue;
				}
			}
			else {
				if (stu[idnum].getpassword() == password) {
					t = STUDENT;
					break;
				}
				else {
					cout << "输入密码错误" << endl;
					continue;
				}
			}
		}
	} while (1);
	system("cls");
	if (t == 1) {
		studentface(stu[idnum],les);
	}
	else if (t == 2) {
		adminface(stu,tea);
	}
	else {
		teacherface(tea[idnum],les);
	}
	
	
}

bool verifyinput(string input) {
	if (input.size() != 5 && input.size() != 8) {
		return false;
	}
	for (size_t a = 0; a < input.size(); a++) {
		if (input[a] < 48 || input[a]>57) {
			return false;
		}
	}
	return true;
}

bool verifystudentid(const int &keyName, map<int, Student> &goods) {
	return (goods.find(keyName) != goods.end());
}

bool verifyteacherid(const int &keyName, map<int, Teacher> &goods) {
	return (goods.find(keyName) != goods.end());
}

bool verifylessonid(const int &keyName, map<int, Lesson> &goods) {
	return (goods.find(keyName) != goods.end());
}

void adminface(map<int, Student> &stu, map<int, Teacher> &tea) {
	string command;
	cout << "1.增减、修改、查看老师信息\n2.增减、修改、查看学生信息\n3.退出系统" << endl;
	cin >> command;
	system("cls");
	if (command == "1") {
		teainfor(stu, tea);
	}
	else if (command == "2") {
		stuinfor(stu, tea);
	}
	else if (command == "3") {}
	else {
		cout << "输入错误，请重新输入" << endl;
		adminface(stu, tea);
	}	
}

void stuinfor(map<int, Student> &stu, map<int, Teacher> &tea) {
	string command;
	do {
		cout << "1.添加学生\n2.删除学生\n3.查看学生信息\n4.返回上一级" << endl;
		cin >> command;
		system("cls");
		if (command == "1") {
			addstudent(stu);
		}
		else if (command == "2") {
			deletestudent(stu);
		}
		else if (command == "3") {
			displaystu(stu);
		}
		else if (command == "4") {
			break;
		}
		else {
			cout << "输入错误，请重新输入" << endl;
		}
	} while (1);
	adminface(stu, tea);
}

void teainfor(map<int, Student> &stu, map<int, Teacher> &tea) {
	string command;
	do {
		cout << "1.添加老师\n2.删除老师\n3.查看老师信息\n4.返回上一级" << endl;
		cin >> command;
		system("cls");
		if (command == "1") {
			addteacher(tea);
		}
		else if (command == "2") {
			deleteteacher(tea);
		}
		else if (command == "3") {
			displaytea(tea);
		}
		else if (command == "4") {
			break;
		}
		else {
			cout << "输入错误，请重新输入" << endl;
		}
	} while (1);
	adminface(stu, tea);
}

void displaystu(map<int, Student> &stu) {
	map<int, Student> ::iterator it = stu.begin();
	if (it == stu.end()) {
		cout << "不存在学生" << endl;
		Sleep(500);
		system("cls");
	}
	else {
		cout << "Student:" << endl;
	}
	for (; it != stu.end() ; it++) {
		cout << "id:" << it->first << "\tname:" << it->second.getname() << endl;
	}
	cout << "请按除回车键以外任意键返回上一步" << endl;
	system("pause");
	system("cls");
	
}

void displaytea(map<int, Teacher> &tea) {
	map<int, Teacher> ::iterator it = tea.begin();
	if (it == tea.end()) {
		cout << "不存在老师" << endl;
		Sleep(500);
		system("cls");
	}
	else {
		cout << "Teacher:" << endl;
	}
	for (; it != tea.end(); it++) {
		cout << "id:" << it->first << "\tname:" << it->second.getname() << endl;
	}
	cout << "请按除回车键以外任意键返回上一步" << endl;
	system("pause");
	system("cls");
}

void addstudent(map<int, Student> &stu) {
	string name, id;
	int idnum;
		cout << "请输入新学生姓名" << endl;
		cin >> name;
		system("cls");
		do {
			cout << "请输入新学生id（第一位不为0的8位整数）" << endl;
			cin >> id;
			system("cls");
			if (verifyinput(id) == true && id.size() != 5) {
				idnum = std::stoi(id);
				if (verifystudentid(idnum,stu) == false) {
					Student temp(idnum, name);
					stu.insert(pair<int, Student>(idnum, temp));
					break;
				}
				else {
					cout << "该id存在，请重新输入" << endl;
				}
			}
			else {
				cout << "输入不合法，请重新输入" << endl;
			}
		} while (1);	
}

void deletestudent(map<int, Student> &stu) {
	if (stu.size() == 0) {
		cout << "不存在学生" << endl;
		return;
	}
	string id;
	int idnum;
	do {
		cout << "请输入学生id（第一位不为0的8位整数）" << endl;
		cin >> id;
		system("cls");
		if (verifyinput(id) == true && id.size() != 5) {
			idnum = std::stoi(id);
			if (verifystudentid(idnum, stu) == true) {
				stu.erase(idnum);
				break;
			}
			else {
				cout << "该id不存在，请重新输入" << endl;
			}
		}
		else {
			cout << "输入不合法，请重新输入" << endl;
		}
	} while (1);
}

void addteacher(map<int, Teacher> &tea) {
	string name, id;
	int idnum;
	cout << "请输入新老师姓名" << endl;
	cin >> name;
	system("cls");
	do {
		cout << "请输入新老师id（第一位不为0且不为10000的5位整数）" << endl;
		cin >> id;
		system("cls");
		if (verifyinput(id) == true && id.size() != 8&& id != "10000") {
			idnum = std::stoi(id);
			if (verifyteacherid(idnum, tea) == false) {
				Teacher temp(idnum, name);
				tea.insert(pair<int, Teacher>(idnum, temp));
				break;
			}
			else {
				cout << "该id存在，请重新输入" << endl;
			}
		}
		else {
			cout << "输入不合法，请重新输入" << endl;
		}
	} while (1);
}

void deleteteacher(map<int, Teacher> &tea) {
	if (tea.size() == 0) {
		cout << "不存在老师" << endl;
		return;
	}
	string id;
	int idnum;
	do {
		cout << "请输入学生id（第一位不为0的8位整数）" << endl;
		cin >> id;
		system("cls");
		if (verifyinput(id) == true && id.size() != 8) {
			idnum = std::stoi(id);
			if (verifyteacherid(idnum, tea) == true) {
				tea.erase(idnum);
				break;
			}
			else {
				cout << "该id不存在，请重新输入" << endl;
			}
		}
		else {
			cout << "输入不合法，请重新输入" << endl;
		}
	} while (1);
}

void teacherface(Teacher &tea, map<int, Lesson> &les) {
	string command;
	cout << "1.开课\n2.删除已开课程\n3.查看已开课程\n4.退出系统" << endl;
	cin >> command;
	system("cls");
	if (command == "1") {
		createlesson(tea, les);
	}	
	else if (command == "2") {
		deletelesson(tea, les);
	}
	else if (command == "3") {
		displaylesson(tea,les);
	}
	else if (command == "4") {
		
	}
	else {
		cout << "输入错误，请重新输入" << endl;
		teacherface(tea,les);
	}
}

void createlesson(Teacher &tea, map<int, Lesson> &les) {
	if (tea.now() == 2) {
		cout << "开设课程达到上限，不允许开设课程" << endl;
	}
	else {
		string cname, cid, cap;
		int idnum, capnum;
		do {
			cout << "请输入课程id（七位整数，其中第一位不为0）" << endl;
			cin >> cid;
			system("cls");
			if (verifyidinput(cid) == true) {
				idnum = std::stoi(cid);
				if (verifylessonid(idnum, les) == false) {
					break;
				}
				else {
					cout << "该id存在，请重新输入" << endl;
				}
			}
			else {
				cout << "输入不合法，请重新输入" << endl;
			}
		} while (1);
		cout << "请输入课程名" << endl;
		cin >> cname;
		system("cls");
		do {
			cout << "请输入1-200内的整数（包括1和200）作为课程容量" << endl;
			cin >> cap;
			system("cls");
			if (verifycapinput(cap) == false) {
				cout << "输入错误，请重新输入" << endl;
			}
			else {
				capnum = std::stoi(cap);
				break;
			}
		} while (1);
		Lesson temp(idnum, cname, capnum, tea.getid(), tea.getname());
		les.insert(pair<int, Lesson>(idnum, temp));
		tea.setlessonid(idnum);
	}
	teacherface(tea, les);
}

bool verifyidinput(string input) {
	if (input.size() != 7) {
		return false;
	}
	for (size_t a = 0; a < input.size(); a++) {
		if (input[a] < 48 || input[a]>57) {
			return false;
		}
	}
	return true;
}

bool verifycapinput(string input) {
	int num;
	if (input.size() > 3) {
		return false;
	}
	for (size_t a = 0; a < input.size(); a++) {
		if (input[a] < 48 || input[a]>57) {
			return false;
		}
	}
	num = std::stoi(input);
	if (num > 200 || num < 1) {
		return false;
	}
	return true;
}

void deletelesson(Teacher &tea, map<int, Lesson> &les) {
	if (tea.now() == 0) {
		cout << "不存在课程" << endl;
		Sleep(500);
		system("cls");
		teacherface(tea, les);	
	}
	else {
		string input;
		int idnum;
		do {
			cout << "请输入课程id,输入0返回上一界面" << endl;
			cin >> input;
			system("cls");
			if (input == "0") {
				break;
			}
			if (verifyidinput(input) == true) {
				idnum = std::stoi(input);
				if (tea.getid() != les[idnum].gettid()) {
					cout << "此课程不属于您,请重新输入" << endl;
				}
				else {
					les.erase(idnum);
					tea.eraselessonid(idnum);
					cout << "删除成功，即将返回上一界面" << endl;
					break;
				}
			}
		} while (1);
		Sleep(500);
		system("cls");
		teacherface(tea, les);
	}
	
}

void displaylesson(Teacher &tea, map<int, Lesson> &les) {
	if (tea.now() == 0) {
		cout << "不存在课程" << endl;
		Sleep(500);
		system("cls");
		teacherface(tea, les);
	}
	else {
		cout << "Lesson:" << endl;
		les[tea.getlessonidfirst()].display();
		if (tea.now() == 2) {
			les[tea.getlessonidsecond()].display();
		}
		cout << "请按除回车键以外任意键返回上一步" << endl;
		system("pause");
		system("cls");
		teacherface(tea, les);
	}
}
	
void studentface(Student &stu, map<int, Lesson> &les) {
	string command;
	cout << "1.选课\n2.退选\n3.查看已选课程\n4.查看所有课程\n5.退出系统" << endl;
	cin >> command;
	system("cls");
	if (command == "1") {
		stuclesson(stu, les);
	}
	else if (command == "2") {
		stunoclesson(stu, les);
	}
	else if (command == "3") {
		studisplaylesson(stu, les);
	}
	else if (command == "4") {
		studisplayalllesson(stu, les);
	}
	else if (command == "5") {

	}
	else {
		cout << "输入错误，请重新输入" << endl;
		studentface(stu, les);
	}
}

void stuclesson(Student &stu, map<int, Lesson> &les) {
	if (stu.now() == 2) {
		cout << "选择课程达到上限，不允许开设课程" << endl;
		Sleep(500);
		system("cls");
	}
	else {
		string cid;
		int idnum;
		do {
			cout << "请输入课程id（七位整数，其中第一位不为0）" << endl;
			cin >> cid;
			system("cls");
			if (verifyidinput(cid) == true) {
				idnum = std::stoi(cid);
				if (verifylessonid(idnum, les) == true) {
					break;
				}
				else {
					cout << "该id不存在，请重新输入" << endl;
				}
			}
			else {
				cout << "输入不合法，请重新输入" << endl;
			}
		} while (1);
		if (les[idnum].chooselesson(stu.getid(), stu) == true) {
			stu.setlessonid(idnum);
			cout << "选课成功" << endl;
		}
		else {
			cout << "该课程人数达到上限，选课失败" << endl;
		}
	}
	studentface(stu, les);
}

void stunoclesson(Student &stu, map<int, Lesson> &les) {
	if (stu.now() == 0) {
		cout << "没有选择课程" << endl;
		Sleep(500);
		system("cls");
		studentface(stu, les);
	}
	else {
		string input;
		int idnum;
		do {
			cout << "请输入课程id,输入0返回上一界面" << endl;
			cin >> input;
			system("cls");
			if (input == "0") {
				break;
			}
			if (verifyidinput(input) == true) {
				idnum = std::stoi(input);
				if (idnum != stu.getlessonidfirst() && idnum != stu.getlessonidsecond()) {
					cout << "此课程不属于您,请重新输入" << endl;
				}
				else {
					stu.eraselessonid(idnum);
					les[idnum].nochooselesson(stu.getid());
					cout << "退选成功，即将返回上一界面" << endl;
					break;
				}
			}
		} while (1);
		Sleep(500);
		system("cls");
		studentface(stu, les);
	}
}

void studisplaylesson(Student &stu, map<int, Lesson> &les) {
	if (stu.now() == 0) {
		cout << "不存在选择课程" << endl;
		Sleep(500);
		system("cls");
		studentface(stu, les);
	}
	else {
		cout << "Lesson:" << endl;
		les[stu.getlessonidfirst()].display();
		if (stu.now() == 2) {
			les[stu.getlessonidsecond()].display();
		}
		cout << "请按除回车键以外任意键返回上一步" << endl;
		system("pause");
		system("cls");
		studentface(stu, les);
	}
}

void studisplayalllesson(Student &stu, map<int, Lesson> &les) {
	if (les.size() == 0) {
		cout << "不存在课程" << endl;
		Sleep(500);
		system("cls");
		studentface(stu, les);
	}
	else {
		map<int, Lesson>::iterator it = les.begin();
		for (; it != les.end(); ++it) {
			it->second.display();
		}
		cout << "请按除回车键以外任意键返回上一步" << endl;
		system("pause");
		system("cls");
		studentface(stu, les);
	}
}
