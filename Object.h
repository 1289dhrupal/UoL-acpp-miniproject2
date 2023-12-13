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
    // Static constants for default object attributes
    static const string DEFAULT_DESCRIPTION;
    static const string DEFAULT_LOCATION;
    static const int DEFAULT_DURABILITY;

    // Constructor: Initializes an object with an ID, description, location, and durability.
    // id: Unique identifier for the object.
    // description: Description of the object, defaulted to DEFAULT_DESCRIPTION.
    // location: Initial location of the object, defaulted to DEFAULT_LOCATION.
    // durability: Durability of the object, defaulted to DEFAULT_DURABILITY.
    Object(const string& id, const string& description = DEFAULT_DESCRIPTION,
           const string& location = DEFAULT_LOCATION, int durability = DEFAULT_DURABILITY);

    // Destructor: Cleans up the Object's resources.
    ~Object();

    // getId: Returns the unique ID of the object.
    string getId() const;

    // getDescription: Returns the description of the object.
    string getDescription() const;

    // getDurability: Returns the durability of the object.
    int getDurability() const;

    // setDurability: Sets the current durability of the object.
    // durability: The new durability value.
    void setDurability(int durability);

    // getLocation: Returns the current location of the object.
    string getLocation() const;
    
    // setLocation: Sets the current location of the object.
    // location: The new location for the object.
    void setLocation(const string& location);

    // look: Provides a detailed description of the object.
    string look() const;

private:
    // Member variables to store object attributes
    const string id_; // Unique identifier for the object
    const string description_; // Description of the object
    string location_; // Location of the object
    int durability_; // Durability of the object
};

#endif // OBJECT_H
