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
    Objective(const string& type, const string& roomId);

private:
    string type_;
    string roomId_;
};

#endif // OBJECTIVE_H
