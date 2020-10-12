#ifndef Meeting_hpp
#define Meeting_hpp
#include <string>
#include <iostream>
#include "DateStruct.hpp"
using namespace std;

int meetidies;
void LastMeetingId();

class Meeting{
private:
	int meetingID;
	int OrganiserID;
	string desc;
	int Duration;
	char status;
	int location;
	int partiNo;
protected:
	DATE date;
public:

	//create a meeting here
	Meeting * CreateMeeting(int LogInId) {
		//auto-incremented id
		LastMeetingId();
		meetingID = meetidies + 1;
		//i am organiser id
		OrganiserID = LogInId;

		//rest of the details
		cout << "Enter description: ";
		cin >> desc;
		cout << "enter date (DD/MM/YYYY): ";
		cin >> this->date.dd >> this->date.sep >> this->date.mm >> this->date.sep >> this->date.yyyy;
		cout << "Enter duration: ";
		cin >> Duration;
		cout << "Enter Location: ";
		cin >> location;
		status = 'S';
		cout << "Enter no of participants to the meet: ";
		cin >> partiNo;
		WriteMeeting(*this);
		return this;
	}

	void WriteMeeting(Meeting &meet) {
		fstream MeetFile;
		MeetFile.open("meetings.txt", ios::app);
		MeetFile.write((char*)&meet, sizeof(Meeting));
		MeetFile.close();
	}

	//function to display date
	void showdate() {
		cout << this->date.dd << this->date.sep << this->date.mm << this->date.sep << this->date.yyyy << endl;
	}

	//functions to return date values
	DATE getdate() {
		return this->date;
	}

	int getMonth() {
		return this->date.mm;
	}

	int getDay() {
		return this->date.dd;
	}

	int getYear() {
		return this->date.yyyy;
	}

	//other getters and setters
	const string& getDesc() const {
		return desc;
	}

	void setDesc(const string& desc) {
		this->desc = desc;
	}
	int getDuration() const {
		return Duration;
	}
	void setDuration(int duration) {
		Duration = duration;
	}
	int getLocation() const {
		return location;
	}
	void setLocation(int location) {
		this->location = location;
	}
	int getMeetingId() const {
		return meetingID;
	}
	void setMeetingId(int meetingId) {
		meetingID = meetingId;
	}
	int getOrganiserId() const {
		return OrganiserID;
	}
	void setOrganiserId(int organiserId) {
		OrganiserID = organiserId;
	}
	int getPartiNo() const {
		return partiNo;
	}
	void setPartiNo(int partiNo) {
		this->partiNo = partiNo;
	}
	char getStatus() const {
		return status;
	}
	void setStatus(char status) {
		this->status = status;
	}
};


void LastMeetingId() {
	fstream MeetingFile;
	vector <Meeting> vmeet;
	Meeting* meet = new Meeting;
	MeetingFile.open("Meetings.txt", ios::in);
	while (MeetingFile.read((char*)meet, sizeof(Meeting))) {
		vmeet.push_back(*meet);
	}

	if (!vmeet.empty()) {
		for (auto m = begin(vmeet); m < end(vmeet); m++) {
			meetidies = m->getMeetingId();
		}
	}
	else {
		meetidies = 999;
	}
}

#endif

