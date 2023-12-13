#pragma once
#include <string>
#include "Enemy.h"

using namespace std;

// Object.h
#ifndef OBJECT_H
#define OBJECT_H

class Object {
    // Represents an object within the game environment.
public:
    static const string DEFAULT_DESCRIPTION;
    static const string DEFAULT_LOCATION;
    static const int DEFAULT_DURABILITY;

    // Constructor to initialize an object with ID, description, location, and durability.
    Object(const string& id, const string& description = DEFAULT_DESCRIPTION,
        const string& location = DEFAULT_LOCATION, int durability = DEFAULT_DURABILITY);

    // Destructor for the Object class.
    ~Object();

    // Returns the unique ID of the object.
    string getId() const;

    // Returns the description of the object.
    string getDescription() const;

    // Returns the durability of the object.
    int getDurability() const;

    // Sets the current durability of the object.
    void setDurability(int durability);

    // Returns the current location of the object.
    string getLocation() const;
    
    // Sets the current location of the object.
    void setLocation(const string& location);

    // Provides a detailed description of the object.
    string look() const;

private:
    const string id_;
    const string description_;
    string location_;  // Currently used for initial location of the object or is it with player.
    int durability_;
};

#endif // OBJECT_H
