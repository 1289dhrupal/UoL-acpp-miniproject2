#pragma once
#include <string>
#include "Enemy.h"

using namespace std;

// Object.h
#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
    static const string DEFAULT_DESCRIPTION;
    static const string DEFAULT_LOCATION;
    static const int DEFAULT_DURABILITY;

    Object(const string& id, const string& description = DEFAULT_DESCRIPTION,
        const string& location = DEFAULT_LOCATION, int durability = DEFAULT_DURABILITY);

    ~Object();

    string getId() const;

    string getDescription() const;

    int getDurability() const;

    string getLocation() const;
    void setLocation(const string& location);

private:
    string id_;
    string description_;
    string location_;
    int durability_;
};

#endif // OBJECT_H
