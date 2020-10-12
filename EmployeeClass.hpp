#ifndef Employee_hpp
#define Employee_hpp
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "MeetingClass.hpp"
#include "ParticipantClass.hpp"
#include "NotificationClass.hpp"

using namespace std;

int empidies;
int notifidies;

class Employee {
private:
	int EmployeeID;
	string Password;
	string Name;
	string Dept;
	long long int MobNo;
	string Email;
	int SkypeID;
public:
	//--------------------------------------------------------------------------------------------------------------------------
	void SignUp() {								//enter details of employee
		cout << "\nWelcome. Please enter details to sign-up as new user:-";
		EmployeeID = empidies + 1;
		empidies += 1;
		cout << "\n\nEnter name: ";
		cin >> Name;
		cout << "Enter password: ";
		cin >> Password;
		cout << "Enter department: ";
		cin >> Dept;
		cout << "Enter MobNo (10 digit): ";
		cin >> MobNo;
		cout << "Enter Email: ";
		cin >> Email;
		SkypeID = EmployeeID;
		cout << "\nYour log-in id is: " << this->getEmployeeId() << endl;
		WriteEmployee(*this);
	}

	void WriteEmployee(Employee &emp) {
		fstream EmpFile;
		EmpFile.open("employees.txt", ios::app);
		EmpFile.write((char*)&emp,sizeof(Employee));
		EmpFile.close();
	}
	//--------------------------------------------------2. Send Notification-------------------------------------------
	void SendNotification(int LogInId) {

		int meetID; bool allow = 1;

		//create vectors for meeting and participant
		vector <Meeting> vmeet;
		vector <Participant> vpart;
		vector <Notification> vnot;

		//object pointers
		Meeting* meet = new Meeting;
		Participant* part = new Participant;
		Notification* notif = new Notification;

		//file objects
		fstream MeetingFile; fstream ParticipantFile; fstream NotificationFile;

		//open notification file in read mode
		NotificationFile.open("notifications.txt", ios::in);
		while (NotificationFile.read((char*)notif, sizeof(Notification))) {
			vnot.push_back(*notif);
		}

		//push data into vector
		if (!vnot.empty()) {
			for (auto n = begin(vnot); n < end(vnot); n++) {
				notifidies = n->getNotifId();
			}
		}
		else {
			notifidies = 0;
		}

		//close notification file
		NotificationFile.close();

		//open meetings file
		MeetingFile.open("meetings.txt", ios::in);

		//push data into meeting vector
		while (MeetingFile.read((char*)meet, sizeof(Meeting))) {
			vmeet.push_back(*meet);
		}

		//close file
		MeetingFile.close();

		//open participants file in read mode
		ParticipantFile.open("participants.txt", ios::in);

		//push all elements into participant vector
		while (ParticipantFile.read((char*)part, sizeof(Participant))) {
			vpart.push_back(*part);
		}


		//close participants file
		ParticipantFile.close();

		//display meetings organised be the logged in employee
		for (auto m = begin(vmeet); m < end(vmeet); m++) {
			if (m->getOrganiserId() == LogInId) {
				allow = 0;
				cout << "You have organised: \n";
				cout << "Meeting ID: " << m->getMeetingId() << "| Description: " << m->getDesc() << "| Duration: " << m->getDuration() << "| Location: " << m->getLocation() << "| Date: ";
				m->showdate();
				cout << "-------------------------------------------------------------------------------------------" << endl;
				continue;
			}
			else {}
		}

		if (allow == 0) {
			cout << "Enter meeting Id of meeting to send notification: ";
			cin >> meetID;
			meetidies = meetID;
		}
		else {
			cout << "No meetings organised." << endl;
			return;
		}

		NotificationFile.open("notifications.txt", ios::out | ios::app);

		if (!vpart.empty()) {
			//check meetings where log-in employee is a participant
			for (auto p = begin(vpart); p < end(vpart); p++) {

				//condition - meeting participant id (p->getPEmpId()) matches log-in employee id (organiser id)
				if (p->getOrganiserId() == LogInId && p->getMeetingId() == meetID && p->getNotiSent() == 'N') {

					//Noification sent is yes
					notif->setNotifId(notifidies + 1);
					notif->setDate(p->getdate());
					notif->setDesc(p->getDesc());
					notif->setDuration(p->getDuration());
					notif->setLocation(p->getLocation());
					notif->setMeetingId(p->getMeetingId());
					notif->setNotiSent('Y');
					notif->setOrganiserId(p->getOrganiserId());
					notif->setPartiNo(p->getPartiNo());
					notif->setRespRec(p->getRespRec());
					notif->setRespTyp(p->getRespTyp());
					notif->setPEmpId(p->getPEmpId());

					//write to notification file
					NotificationFile.write((char*)notif, sizeof(Notification));
					continue;
				}
			}

			//close notification file
			NotificationFile.close();
		}
		else {
			cout << "No meetings to participated in....\n\n";
		}

		//displaynotif();
	}

	//------------------------------------------3 - SEND REPLY--------------------------------------------------------------------------------
	void SendReply(int LogInId) {
		//initialise vectors
		vector <Meeting> vmeet;
		vector <Participant> vpart;

		int respId; char respTyp;

		//initialise object pointers
		Meeting* meet = new Meeting;
		Participant* part = new Participant;

		//file objects
		fstream MeetingFile; fstream ParticipantFile; fstream testfile2;

		//open meetings file and push into vector
		MeetingFile.open("meetings.txt", ios::in);
		while (MeetingFile.read((char*)meet, sizeof(Meeting))) {
			vmeet.push_back(*meet);
		}

		//close file
		MeetingFile.close();

		//open participants file and puch data into vector
		ParticipantFile.open("participants.txt", ios::in);
		while (ParticipantFile.read((char*)part, sizeof(Participant))) {
			vpart.push_back(*part);
		}

		//close participant file
		ParticipantFile.close();

		//check meetings where log-in employee is a participant
		for (auto p = begin(vpart); p < end(vpart); p++) {

			//condition - meeting participant id (p->getPEmpId()) matches log-in employee id (organiser id)
			if (p->getPEmpId() == LogInId) {

				//display details of meetings participated in
				cout << "You are participating in:";
				cout << "Meeting ID: " << p->getMeetingId() << "| Description: " << p->getDesc() << "| Duration: " << p->getDuration() << "| Location: " << p->getLocation() << "|Response Type: " << p->getRespTyp() << "| Date: ";
				p->showdate();
				cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
				continue;
			}
			else {}
		}

		//enter meeting to which response needs to be changed
		cout << "Enter id of meeting to respond to: ";
		cin >> respId;

		//open temporary file in read and original file in write mode
		ParticipantFile.open("participants.txt", ios::in);
		testfile2.open("test2.txt", ios::out);

		//read details from original participant file
		while (ParticipantFile.read((char*)part, sizeof(Participant))) {

			//meet ids match and also the participant id matches logged-in employee id
			if (part->getMeetingId() == respId && part->getPEmpId() == LogInId) {

				//choose response type A or R or M
				cout << "Choose response type: (A)ccept \t (R)eject \t (M)aybe: ";
				cin >> respTyp;
				
				//set response type according to choice
				switch (respTyp) {
				case 'A':part->setRespTyp("Accept"); part->setRespRec('Y'); break;
				case 'R':part->setRespTyp("Reject"); part->setRespRec('Y'); break;
				case 'M':part->setRespTyp("Maybe");  part->setRespRec('Y'); break;
				default:cout << "Invalid response\n"; break;
				}
				if (part->getRespTyp().compare("None")) {
					cout << "Response Changed.\n" << endl;
				}
				//enter details after changed response
				testfile2.write((char*)part, sizeof(Participant));
			}
			else {
				//write all the other entries as they are
				testfile2.write((char*)part, sizeof(Participant));
			}
		}
		ParticipantFile.close(); testfile2.close();

		//delete original participants file
		remove("participants.txt");
		//rename temporary file to the original file
		rename("test2.txt", "participants.txt");
		deletenotifs(LogInId);
	}

	void deletenotifs(int x) {
		Notification* n1 = new Notification;
		Notification* n2 = new Notification;
		Participant* p = new Participant;

		fstream nfile, n2file, pfile;
		pfile.open("participants.txt", ios::in);
		nfile.open("notifications.txt", ios::in); n2file.open("test.txt", ios::out);
		while (pfile.read((char*)p, sizeof(Participant))) {
			while (nfile.read((char*)n1, sizeof(Notification))) {
				if (p->getRespRec() != n1->getRespRec() && n1->getPEmpId() == x) {
					//don't copy into required file
				}
				else {
					n2file.write((char*)n1, sizeof(Notification));
				}
			}
		}

		nfile.close(); n2file.close();
		remove("notifications.txt");
		rename("test.txt", "notifications.txt");
	}

	//----------------------------------------------------4. DISPLAY CALENDAR----------------------------------------------------
	void DisplayCalendar(int LogInId) {
		//initialise variables for start and end date
		DATE start, endate;

		//take start date from user
		cout << "Enter start date (DD/MM/YYYY): ";
		cin >> start.dd >> start.sep >> start.mm >> start.sep >> start.yyyy;

		//take end date from user
		cout << "Enter end date (DD/MM/YYYY): ";
		cin >> endate.dd >> endate.sep >> endate.mm >> endate.sep >> endate.yyyy;

		//initialise vectors
		vector <Meeting> vmeet;
		vector <Participant> vpart;

		//initialise object pointers
		Meeting* meet = new Meeting;
		Participant* part = new Participant;

		//file objects
		fstream MeetingFile; fstream ParticipantFile;

		//open meetings file and push into vector
		MeetingFile.open("meetings.txt", ios::in);
		while (MeetingFile.read((char*)meet, sizeof(Meeting))) {
			vmeet.push_back(*meet);
		}

		//close file
		MeetingFile.close();


		//open participants file and puch data into vector
		ParticipantFile.open("participants.txt", ios::in);
		while (ParticipantFile.read((char*)part, sizeof(Participant))) {
			vpart.push_back(*part);
		}

		//close participant file
		ParticipantFile.close();

		cout << "\nOrganised:" << endl;
		for (auto m = begin(vmeet); m < end(vmeet); m++) {

			//check if meeting date lies between start and end date and the meeting organiser id matches logged-in id
			/*Date checking logic:-
			 * condition 1 - ((meeting year > start year) OR
			 * (meeting year = start year AND meeting month > start month) OR
			 * (meeting year = start year AND meeting month = start month AND meeting day > start day)) - condition 1
			 * condition 2 - ((meeting year < end year) OR
			 * (meeting year = end year AND meeting month < end year) OR
			 * (meeting year = end year AND meeting month = start month AND meeting day < end day  )) - condition 2
			 * */
			if ((m->getOrganiserId() == LogInId) && 
				((start.yyyy < m->getYear()) || (start.yyyy == m->getYear() && start.mm < m->getMonth()) || (start.yyyy == m->getYear() && start.mm == m->getMonth() && start.dd < m->getDay())) && 
				((endate.yyyy > m->getYear()) || (endate.yyyy == m->getYear() && endate.mm > m->getMonth()) || (endate.yyyy == m->getYear() && endate.mm == m->getMonth() && endate.dd > m->getDay()))) {
				cout << "You have organised: ";
				cout << "Meeting ID: " << m->getMeetingId() << "| Description: " << m->getDesc() << "| Duration: " << m->getDuration() << "| Location: " << m->getLocation() << "| Date: ";
				m->showdate();
				cout << "------------------------------------------------------------------------------------------------------" << endl;
				continue;
			}
			else {}
		}
		cout << "\nParticipant in:" << endl;
		for (auto p = begin(vpart); p < end(vpart); p++) {

			//check if meeting date lies between start and end date and the meeting participant-id matches logged-in id
			/*Date checking logic:-
			 * condition 1 - ((meeting year > start year) OR
			 * (meeting year = start year AND meeting month > start month) OR
			 * (meeting year = start year AND meeting month = start month AND meeting day > start day)) - condition 1
			 * condition 2 - ((meeting year < end year) OR
			 * (meeting year = end year AND meeting month < end year) OR
			 * (meeting year = end year AND meeting month = start month AND meeting day < end day  )) - condition 2
			 * */
			if ((p->getPEmpId() == LogInId) && 
				((start.yyyy < p->getYear()) || (start.yyyy == p->getYear() && start.mm < p->getMonth()) || (start.yyyy == p->getYear() && start.mm == p->getMonth() && start.dd < p->getDay())) && 
				((endate.yyyy > p->getYear()) || (endate.yyyy == p->getYear() && endate.mm > p->getMonth()) || (endate.yyyy == p->getYear() && endate.mm == p->getMonth() && endate.dd > p->getDay()))) {
				cout << "You are participating in: ";
				cout << "Meeting ID: " << p->getMeetingId() << "| Description: " << p->getDesc() << "| Duration: " << p->getDuration() << "| Location: " << p->getLocation() << "| Response: " << p->getRespTyp() << "| Date: ";
				p->showdate();
				cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
				continue;
			}
			else {}
		}
	}

	//----------------------------------------------5. DISPLAY MEETINGS--------------------------------------------------------------------------
	void DisplayMeeting(int LogInId) {
		//create vectors for meeting and participant
		vector <Meeting> vmeet;
		vector <Participant> vpart;

		//object pointers
		Meeting* meet = new Meeting;
		Participant* part = new Participant;

		//file objects
		fstream MeetingFile; fstream ParticipantFile;

		//open meetings file
		MeetingFile.open("meetings.txt", ios::in);

		//push data into meeting vector
		while (MeetingFile.read((char*)meet, sizeof(Meeting))) {
			vmeet.push_back(*meet);
		}

		//close file
		MeetingFile.close();

		//open participants file in read mode
		ParticipantFile.open("participants.txt", ios::in);

		//push all elements into participant vector
		while (ParticipantFile.read((char*)part, sizeof(Participant))) {
			vpart.push_back(*part);
		}

		//close participants file
		ParticipantFile.close();

		
		//check meetings organised by log-in employee
		if (!vmeet.empty()) {
			for (auto m = begin(vmeet); m < end(vmeet); m++) {

				//condition - meeting organiser id (m->getOrganiserId()) should match log-in employee (organiserid)
				if (m->getOrganiserId() == LogInId) {

					//display details of organised meetings
					cout << "\nOrganised: " << endl;
					cout << "Meeting ID: " << m->getMeetingId() << "| Description: " << m->getDesc() << "| Duration: " << m->getDuration() << "| Location: " << m->getLocation() << "| Date: ";
					m->showdate();

					//display all participants needed in the meeting and their response types
					cout << "\nPaticipants are:\n";
					for (auto p = begin(vpart); p < end(vpart); p++) {
						if (p->getOrganiserId() == LogInId && m->getMeetingId() == p->getMeetingId()) {
							cout << "Participant-id: " << p->getPEmpId() << " | Responded: " << p->getRespRec() << " | Response: " << p->getRespTyp() << endl;
						}
					}
					cout << "-------------------------------------------------------------" << endl;
					continue;
				}
				else {}
			}
		}
		else {
			cout << "No meets schedule....\n\n";
		}

		cout << "\nParticipated in:" << endl;
		if (!vpart.empty()) {
			//check meetings where log-in employee is a participant
			for (auto p = begin(vpart); p < end(vpart); p++) {

				//condition - meeting participant id (p->getPEmpId()) matches log-in employee id (organiser id)
				if (p->getPEmpId() == LogInId) {

					//display details of meetings participated in
					cout << "You are participating in: ";
					cout << "Meeting ID: " << p->getMeetingId() << "| Description: " << p->getDesc() << "| Duration: " << p->getDuration() << "| Location: " << p->getLocation() << "| Response: " << p->getRespTyp() << "| Date: ";
					p->showdate();
					cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
					continue;
				}
				else {}
			}
		}
		else {
			cout << "No meetings participated in....\n\n";
		}
	
	}

	//------------------------------------------------------6. CANCEL MEETINGS-----------------------------------------------------------------------
	void CancelMeeting(int LogInId) {
		int meetID; bool allow = 1;

		//initialise vectors
		vector <Meeting> vmeet;
		vector <Participant> vpart;

		//initialise object pointers
		Meeting* meet = new Meeting;
		Participant* part = new Participant;
		Notification* notif = new Notification;

		//file objects
		fstream MeetingFile;
		fstream ParticipantFile;
		fstream NotificationFile;

		//temporary file objects
		fstream testfile, testfile2, testfile3;

		//push data into meeting vector
		MeetingFile.open("meetings.txt", ios::in);
		while (MeetingFile.read((char*)meet, sizeof(Meeting))) {
			vmeet.push_back(*meet);
		}
		MeetingFile.close();

		//push data into participant vector
		ParticipantFile.open("participants.txt", ios::in);
		while (ParticipantFile.read((char*)part, sizeof(Participant))) {
			vpart.push_back(*part);
		}
		ParticipantFile.close();

		//display meetings organised be the logged in employee
		for (auto m = begin(vmeet); m < end(vmeet); m++) {
			if (m->getOrganiserId() == LogInId) {
				allow = 0;
				cout << "You have organised: ";
				cout << "Meeting ID: " << m->getMeetingId() << "| Description: " << m->getDesc() << "| Duration: " << m->getDuration() << "| Location: " << m->getLocation() << "| Date: ";
				m->showdate();
				cout << "-------------------------------------------------------------------------------------------" << endl;
				continue;
			}
			else {}
		}


		//based on displayed organised meetings, enter id of meeting to be cancelled
		if (allow == 0) {
			cout << "Enter meeting Id of meeting to be cancelled: ";
			cin >> meetID;
			meetidies = meetID;
		}
		else {
			cout << "No meetings organised that can be cancelled." << endl;
			return;
		}
		//open temporary and the original meetings file
		testfile.open("test.txt", ios::out);
		MeetingFile.open("meetings.txt", ios::in);

		//copy all meetings from original to temporary except for the meeting whose meeting-id was entered
		while (MeetingFile.read((char*)meet, sizeof(Meeting))) {

			//meet-id matches entered meet id and also meeting organiser id metches logged in employee id
			if (meet->getMeetingId() == meetidies && meet->getOrganiserId() == LogInId) {
				//do not write to the file if condition is true
				cout << "Meeting cancelled." << endl;
			}
			else {
				testfile.write((char*)meet, sizeof(Meeting));
			}
		}

		//close temporary and original files
		MeetingFile.close(); testfile.close();

		//open temporary and original participants file
		testfile2.open("test2.txt", ios::out);
		ParticipantFile.open("participants.txt", ios::in);

		//re-write all except cancelled meeting to the participant file
		while (ParticipantFile.read((char*)part, sizeof(Participant))) {

			//meet ids match and also the organiser id of meeting in which a participant has participated matches logged-in employee id
			if (part->getMeetingId() == meetidies && part->getOrganiserId() == LogInId) {}
			else {
				//copy details to temporary participants file
				testfile2.write((char*)part, sizeof(Participant));
			}
		}
		
		//close all open files
		ParticipantFile.close(); testfile2.close();
		
		//open temporary and original participants file
		testfile3.open("test3.txt", ios::out);
		NotificationFile.open("notifications.txt", ios::in);

		//re-write all except cancelled meeting to the participant file
		while (NotificationFile.read((char*)notif, sizeof(Notification))) {

			//meet ids match and also the organiser id of meeting in which a participant has participated matches logged-in employee id
			if (notif->getMeetingId() == meetidies && notif->getOrganiserId() == LogInId) {}
			else {
				//copy details to temporary participants file
				testfile3.write((char*)notif, sizeof(Notification));
			}
		}
		
		//close all open files
		NotificationFile.close(); testfile3.close();

		//delete original meetings file
		remove("meetings.txt");

		//rename the temporary file to the original one file
		rename("test.txt", "meetings.txt");

		//delete original participants file
		remove("participants.txt");

		//rename temporary file to the original file
		rename("test2.txt", "participants.txt");
		
		//delete original notification file
		remove("notifications.txt");

		//rename the temporary file to the original one file
		rename("test3.txt", "notifications.txt");
	}

	

	//display details of employee
	void show() {
		cout << "Name: " << Name << "\nEmployee ID: " << EmployeeID << "\nDept: " << Dept << "\nEmail ID: " << Email << "\nMobNo: " << MobNo << "\nSkype ID: " << SkypeID << endl << endl;
	}

	int getEmployeeId() const {
		return EmployeeID;
	}

	double getMobNo() const {
		return MobNo;
	}

	const string& getPassword() const {
		return Password;
	}

	const string& getName() const {
		return Name;
	}
};

void LastEmployeeId() {
	
	vector <Employee> vemp;

	Employee* emp = new Employee;

	fstream EmployeeFile;
	EmployeeFile.open("employees.txt", ios::in);
	
	while (EmployeeFile.read((char*)emp, sizeof(Employee))) {
		vemp.push_back(*emp);
	}
	EmployeeFile.close();

	if (!vemp.empty()) {
		for (auto e = begin(vemp); e < end(vemp); e++) {
			empidies = e->getEmployeeId();
		}
	}
	else {
		empidies = 999;
	}
}


#endif // !1
