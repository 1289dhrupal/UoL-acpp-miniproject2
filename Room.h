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

class Room {
    // Represents a room in the game environment.
public:
    
    // Constructor to initialize a room with an ID and description.
    Room(const string& id, const string& description);

    // Destructor for the Objective class.
    ~Room();

    // Returns the room ID.
    string getId();

    // Returns a pointer to an exit room based on the given direction.
    Room* getExit(const string& direction);
    
    // Sets an exit for the room in a specified direction.
    void setExit(const string& direction, Room* room);

    // Checks if the room has any exits.
    bool hasExits();

    // Retrieves an object from the room based on its ID.
    Object* getObject(const string& objectId);
    
    // Adds an object to the room.
    void addObject(Object* object);
    
    // Checks if the room contains objects.
    bool hasObjects() const;
    
    // Removes an object from the room.
    void removeObject(Object* object);
    
    // Returns a map of all objects in the room.
    map<string, Object*> getObjects() const;

    // Retrieves an enemy from the room based on its ID.
    Enemy* getEnemy(const string& enemyId);
    
    // Adds an enemy to the room.
    void addEnemy(Enemy* enemy);
    
    // Checks if the room contains an enemy.
    bool hasEnemy() const;
    
    // Removes an enemy from the room.
    void removeEnemy(Enemy* enemy);
    
    // Returns a map of all enemies in the room.
    map<string, Enemy*> getEnemies() const;

    // Returns the description of the room.
    string getDescription() const;

    // Provides a detailed description of the room and its contents.
    string look();
    
    // Provides a brief overview of the room's surroundings.
    string lookAround();

private:
    const string id_;
    const string description_;
    map<string, Room*> exits_;
    map<string, Object*> objects_;
    map<string, Enemy*> enemies_;
};

#endif // ROOM_H
