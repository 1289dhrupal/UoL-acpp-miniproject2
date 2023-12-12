#pragma once
#include <string>
#include <map>
#include "Room.h"
#include "Object.h"

using namespace std;

// Player.h
#ifndef PLAYER_H
#define PLAYER_H

class Player {
    // Represents a player in the game with health, location, and objects.
public:

    // Constructor to initialize a player at a specific location.
    Player(const string& location);

    // Destructor for the Player class.
    ~Player();

    // Returns the health of the player.
    int getHealth() const;
    
    // Sets the health of the player.
    void setHealth(int health);

    // Returns the current location of the player.
    string getLocation() const;
    
    // Sets the current location of the player.
    void setLocation(const string& location);

    // Retrieves an object based on its ID from the player's inventory.
    Object* getObject(const string& objectId);
    
    // Returns a map of all objects in the player's inventory.
    map<string, Object*> getObjects() const;
    
    // Adds an object to the player's inventory.
    void addObject(Object* object);
    
    // Checks if the player has any objects in their inventory.
    bool hasObjects() const;

    // Performs a check to return a status summary of the player.
    string check() const;

private:
    int health_;
    string location_; // Currently used for initial location of the player.
    map<string, Object*> objects_;
};

#endif // PLAYER_H
