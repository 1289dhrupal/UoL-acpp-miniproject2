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

    Object(const string& name, const string& description = DEFAULT_DESCRIPTION,
        const string& location = DEFAULT_LOCATION, int durability = DEFAULT_DURABILITY);

    ~Object();

    string getName() const;

    string getDescription() const;

    int getDurability() const;

    string getLocation() const;
    void setLocation(const string& location);

private:
    string _name;
    string _description;
    string _location;
    int _durability;
};

#endif // OBJECT_H
