#pragma once
#include <iostream>
#include <string>
#include <map>
#include "Object.h"
#include "Enemy.h"

using namespace std;

// Room.h
#ifndef ROOM_H
#define ROOM_H

// The Room class represents a room in the game environment.
class Room {
public:
    // Constructor: Initializes a room with an ID and description.
    // id: Unique identifier for the room.
    // description: Description of the room.
    Room(const string& id, const string& description);

    // Destructor: Cleans up the Room's resources.
    ~Room();

    // getId: Returns the room ID.
    string getId();

    // getExit: Returns a pointer to an exit room based on the given direction.
    // direction: The direction in which to find an exit.
    Room* getExit(const string& direction);

    // setExit: Sets an exit for the room in a specified direction.
    // direction: The direction where the exit will be set.
    // room: Pointer to the room that will be set as an exit.
    void setExit(const string& direction, Room* room);

    // hasExits: Checks if the room has any exits.
    bool hasExits();

    // getObject: Retrieves an object from the room based on its ID.
    // objectId: The ID of the object to retrieve.
    Object* getObject(const string& objectId);

    // addObject: Adds an object to the room.
    // object: Pointer to the object to be added.
    void addObject(Object* object);

    // hasObjects: Checks if the room contains objects.
    bool hasObjects() const;

    // removeObject: Removes an object from the room.
    // object: Pointer to the object to be removed.
    void removeObject(Object* object);

    // getObjects: Returns a map of all objects in the room.
    map<string, Object*> getObjects() const;

    // getEnemy: Retrieves an enemy from the room based on its ID.
    // enemyId: The ID of the enemy to retrieve.
    Enemy* getEnemy(const string& enemyId);

    // addEnemy: Adds an enemy to the room.
    // enemy: Pointer to the enemy to be added.
    void addEnemy(Enemy* enemy);

    // hasEnemy: Checks if the room contains an enemy.
    bool hasEnemy() const;

    // removeEnemy: Removes an enemy from the room.
    // enemy: Pointer to the enemy to be removed.
    void removeEnemy(Enemy* enemy);

    // getEnemies: Returns a map of all enemies in the room.
    map<string, Enemy*> getEnemies() const;

    // getDescription: Returns the description of the room.
    string getDescription() const;

    // look: Provides a detailed description of the room and its contents.
    string look();

    // lookAround: Provides a brief overview of the room's surroundings.
    string lookAround();

private:
    // Member variables to store room attributes and connections
    const string id_; // Unique identifier for the room
    const string description_; // Description of the room
    map<string, Room*> exits_; // Exits from the room
    map<string, Object*> objects_; // Objects present in the room
    map<string, Enemy*> enemies_; // Enemies present in the room
};

#endif // ROOM_H
