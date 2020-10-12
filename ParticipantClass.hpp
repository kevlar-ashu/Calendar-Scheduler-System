#ifndef Participant_hpp
#define Participant_hpp

#include <string>
#include <iostream>
#include <fstream>

#include "MeetingClass.hpp"
#include "EmployeeClass.hpp"
#include "DateStruct.hpp"
using namespace std;
int id;

class Participant : public Meeting {
private:
	int PEmpID;
	char NotiSent;
	char RespRec;
	string RespTyp;
public:

	void CreateParticipant(Meeting* meet) {
		this->ParticipantDetails();
		this->setDate(meet->getdate());
		this->setPartiNo(meet->getPartiNo());
		this->setOrganiserId(meet->getOrganiserId());
		this->setMeetingId(meet->getMeetingId());
		this->setDesc(meet->getDesc());
		this->setDuration(meet->getDuration());
		this->setLocation(meet->getLocation());
		this->setStatus(meet->getStatus());
		int no = meet->getPartiNo();
		fstream PartFile;
		PartFile.open("participants.txt", ios::out | ios::app);
		for (int i = 1; i <= no; i++) {
			cout << "Enter ID of participant " << i << " : ";
			cin >> id;
			this->setPEmpId(id);
			PartFile.write((char*)this, sizeof(Participant));
		}
		PartFile.close();
	}

	//setting variables other than those in meeting class
	void ParticipantDetails() {
		NotiSent = 'N';
		RespRec = 'N';
		RespTyp = "None";
	}

	//set meeting date for thisicipant
	void setDate(DATE trial) {
		this->date = trial;
	}

	//other getters and setters
	char getNotiSent() const {
		return NotiSent;
	}
	void setNotiSent(char notiSent) {
		NotiSent = notiSent;
	}
	int getPEmpId() const {
		return PEmpID;
	}
	void setPEmpId(int empId) {
		PEmpID = empId;
	}
	char getRespRec() const {
		return RespRec;
	}
	void setRespRec(char respRec) {
		RespRec = respRec;
	}

	const string& getRespTyp() const {
		return RespTyp;
	}
	void setRespTyp(const string& respTyp) {
		RespTyp = respTyp;
	}
};
#endif // !

