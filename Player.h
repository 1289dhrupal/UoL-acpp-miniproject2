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
    Player(Room* location);

    ~Player();

    Room* getLocation();

    void setLocation(Room* location);

    void setObject(Object* objectId);

    Object* getObject();

    string check() const;

private:
    Room* location_; // The current location of the player in the game.
    Object* object_;
};

#endif // PLAYER_H
