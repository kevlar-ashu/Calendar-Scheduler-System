#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "EmployeeClass.hpp"
#include "MeetingClass.hpp"
#include "NotificationClass.hpp"
#include "DateStruct.hpp"
#include "LogInClass.hpp"

using namespace std;

void displaymeetings(); void displayemployees(); void displayparti(); void displaynotif();

int main(){
	int choice;
	Employee* emp = new Employee;
	Login* l = new Login;
	LastEmployeeId();
	cout << "-------------MyCalendar-------------\n\n";

	do {
		cout << "1. Sign up\n2. Log in\n0. Exit\nEnter choice: ";
		cin >> choice;
		switch (choice) {
		case 1:emp->SignUp(); break;
		case 2:l->LogIn(); break;
		case 3:displayemployees(); break;
		case 4:displaymeetings(); break;
		case 5:displayparti(); break;
		case 6:displaynotif(); break;
		case 0:cout << "Please visit again !!!" << endl; exit(0);
		default:cout << "Invalid option. Retry please.\n\n";
		}
	} while (1);
	return 0;
}


//convenience functions
void displaymeetings() {
	fstream mfile;
	Meeting* m = new Meeting;
	mfile.open("meetings.txt", ios::in);
	while (mfile.read((char*)m, sizeof(Meeting))) {
		cout << m->getDesc() << " - " << m->getMeetingId() << " - ";
		m->showdate();
	}
	mfile.close();
}
void displayemployees() {
	fstream mfile;
	Employee* m = new Employee;
	mfile.open("employees.txt", ios::in);
	while (mfile.read((char*)m, sizeof(Employee))) {
		cout << m->getName() << " - " << m->getEmployeeId() << endl;
	}
	mfile.close();
}
void displayparti() {
	fstream mfile;
	Participant* m = new Participant;
	mfile.open("participants.txt", ios::in);
	while (mfile.read((char*)m, sizeof(Participant))) {
		cout << m->getPEmpId() << " - " << m->getDesc() << " - " << m->getMeetingId() << endl;
	}
	mfile.close();
}
void displaynotif() {
	fstream mfile;
	Notification* m = new Notification;
	mfile.open("notifications.txt", ios::in);
	while (mfile.read((char*)m, sizeof(Notification))) {
		cout << m->getPEmpId() << " - " << m->getDesc() << " - " << m->getMeetingId() << endl;
	}
	mfile.close();
}