#pragma once
#include <string>
#include "Enemy.h"

using namespace std;

// Object.h
#ifndef OBJECT_H
#define OBJECT_H

// The Object class represents an object within the game environment.
class Object {
public:

    Object(const string& id, const string& description, const string& location);

    ~Object();

    string getId() const;

    string getDescription() const;

    string getLocation() const;

    void setLocation(const string& location);

    string look() const;

private:

    const string id_;
    const string description_;
    string location_;
};

#endif // OBJECT_H
