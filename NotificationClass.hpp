#ifndef Notification_hpp
#define Notification_hpp
#include <string>
#include <iostream>
#include "ParticipantClass.hpp"
using namespace std;

class Notification : public Participant {
private:
	int NotifId;
public:
	void setNotifId(int nid) {
		NotifId = nid;
	}

	int getNotifId() {
		return NotifId;
	}
};
#endif // !Notification_hpp

