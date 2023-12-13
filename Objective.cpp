#include "Objective.h"
#include <sstream>

using namespace std;

// Constructor initializing Objective with a type and room ID.
Objective::Objective(const string& type, const string& roomId) : type_(type), roomId_(roomId) {}

// Destructor for Objective class.
Objective::~Objective() { /* No cleanup needed */ }

bool Objective::isObjectiveAchived(Room* room) {
	return room->getId() == roomId_;
}

string Objective::getBossRoomId(){
    return roomId_;
}

string Objective::check() {
    std::stringstream ss;
    ss << "----------------------------------------------" << endl;
    ss << "Objective :: Reach rooom \"" << roomId_ << "\"." << endl;
    ss << "----------------------------------------------" << endl;
    return ss.str();

}