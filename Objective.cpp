#include "Objective.h"
#include "Room.h"

// Constructor initializing Objective with a type and room ID.
Objective::Objective(const string& type, const string& roomId) : type_(type), roomId_(roomId) {}

// Destructor for Objective class.
Objective::~Objective() { /* No cleanup needed */ }

bool Objective::isObjectiveAchived(Room* room) {
	return room->getId() == roomId_;
}