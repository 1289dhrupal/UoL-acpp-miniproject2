#pragma once
#include <string>
#include <map>
#include "Room.h"
#include "Object.h"

using namespace std;

// Objective.h
#ifndef OBJECTIVE_H
#define OBJECTIVE_H

class Objective {
    // Represents a specific objective or goal in the game.
    // Currently the game has only one objective.
public:

    // Constructor to initialize an objective with a type and associated room ID.
    Objective(const string& type, const string& roomId);

    // Destructor for the Objective class.
    ~Objective();

    string getBossRoomId();

    bool isObjectiveAchived(Room* room);

    string check();

private:
    const string type_;
    const string roomId_;
};

#endif // OBJECTIVE_H
