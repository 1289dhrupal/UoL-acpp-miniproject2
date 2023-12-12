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
public:
    Objective(const string& type, const string& roomName);

private:
    string _type;
    string _roomName;
};

#endif // OBJECTIVE_H
