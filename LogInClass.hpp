#ifndef Login_hpp
#define Login_hpp

#include <iostream>
#include <string>
#include <vector>
#include "EmployeeClass.hpp"
#include "MeetingClass.hpp"
#include "ParticipantClass.hpp"

using namespace std;
int option;

class Login {
private:
	int LogInId;
	string LogInPass;
public:
	void LogIn() {

		vector <Employee> vemp;
		Employee* emp = new Employee;
		Meeting* m = new Meeting;
		Participant* p = new Participant;

		cout << "Enter Id: ";
		cin >> this->LogInId;
		cout << "Enter Password: ";
		cin >> this->LogInPass;

		fstream EmployeeFile;
		EmployeeFile.open("employees.txt", ios::in);

		while (EmployeeFile.read((char*)emp, sizeof(Employee))) {
			vemp.push_back(*emp);
		}
		EmployeeFile.close();
		for (auto e = begin(vemp); e < end(vemp); e++) {
			if (this->LogInId == e->getEmployeeId() && !this->LogInPass.compare(e->getPassword())) {
				cout << "\nWelcome " << e->getName() << ". Profile details:" << endl;
				e->show();
				do {
					cout << "\n--------------------------Calendar Menu---------------------------\n\n";
					cout << "1. Schedule Meeting" << endl;
					cout << "2. Send Notifications" << endl;
					cout << "3. Send Reply" << endl;
					cout << "4. Display Calendar" << endl;
					cout << "5. Display Meeting" << endl;
					cout << "6. Cancel Meeting" << endl;
					cout << "0. Logout" << endl;
					cout << "\nEnter choice of activity: ";

					//enter choice of action
					cin >> option;

					switch (option) {
					case 1:cout << "\nScheduling a Meeting...." << endl;p->CreateParticipant(m->CreateMeeting(this->LogInId)); break;
					case 2:cout << "\nSending Notifications...." << endl; e->SendNotification(this->LogInId);  break;
					case 3:cout << "\nSending Reply...." << endl; e->SendReply(this->LogInId); break;
					case 4:cout << "\nDisplaying Calendar...." << endl; e->DisplayCalendar(this->LogInId); break;
					case 5:cout << "\nDisplaying Meetings...." << endl; e->DisplayMeeting(this->LogInId); break;
					case 6:cout << "\nCancel Meeting..." << endl; e->CancelMeeting(this->LogInId);  break;
					case 0:cout << "\nLogging out....\n" << endl; return;
					default:cout << "\nInvalid choice. Please try again.\n" << endl; break;
					}
				} while (option != 0);

			}
			else if( e == end(vemp)) {
				cout << "Invalid Credentials. Please try again...\n\n ";
			}
		}
	}
};
#endif // !Login_hpp

