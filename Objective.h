#pragma once
#include <string>
#include <map>
#include "Room.h"
#include "Enemy.h"
#include "Object.h"

using namespace std;

// Objective.h
#ifndef OBJECTIVE_H
#define OBJECTIVE_H

// The Objective class represents a specific objective or goal in the game.
// Currently, the game has only one type of objective.
class Objective {
public:
    // Constructor: Initializes an objective with a type and associated room ID.
    // type: The type of the objective (room, enemy, collect, survival).
    // targetId: The ID of the targetId associated with the objective.
    Objective(const string& type, const vector<string> targetIds);

    // Destructor: Cleans up the Objective's resources (if any).
    ~Objective();

    // getTargetId: Retrieves the ID of the target associated with the objective.
    bool isTargetId(const string& targetId);

    // check: Returns a status summary or description of the objective.
    string check();

private:
    // Type of the objective.
    const string type_;

    // ID of the target room or item associated with the objective.
    const vector<string> targetIds_;
};

#endif // OBJECTIVE_H
