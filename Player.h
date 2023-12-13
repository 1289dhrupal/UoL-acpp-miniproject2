#pragma once

#include <string>
#include <map>
#include "Room.h"
#include "Object.h"

using namespace std;

// Player.h
#ifndef PLAYER_H
#define PLAYER_H

// The Player class represents a player in the game.
// It maintains the player's health, current location, and a collection of objects.
class Player {
public:
    // Constructor: Initializes a new player at a specified location.
    // location: The initial location of the player in the game.
    Player(const string& location);

    // Destructor: Cleans up the player's allocated resources.
    ~Player();

    // getHealth: Returns the current health of the player.
    int getHealth() const;

    // setHealth: Sets the health of the player.
    // health: The new health value to set for the player.
    void setHealth(int health);

    // getLocation: Returns the current location of the player in the game.
    string getLocation() const;

    // setLocation: Sets the current location of the player.
    // location: The new location to move the player to.
    void setLocation(const string& location);

    // getObject: Retrieves an object from the player's inventory by its ID.
    // objectId: The ID of the object to retrieve.
    Object* getObject(const string& objectId);

    // getObjects: Returns a map of all objects currently in the player's inventory.
    map<string, Object*> getObjects() const;

    // addObject: Adds a new object to the player's inventory.
    // object: Pointer to the object to be added.
    void addObject(Object* object);

    // removeObject: Removes an object from the player's inventory.
    // object: Pointer to the object to be removed.
    void removeObject(Object* object);

    // hasObjects: Checks if the player has any objects in their inventory.
    bool hasObjects() const;

    // check: Performs a check to return a status summary of the player.
    string check() const;

private:
    int health_; // The health of the player.
    string location_; // The current location of the player in the game.
    map<string, Object*> objects_; // Map of objects that the player has.
};

#endif // PLAYER_H
