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
public:
    Room(const string& name, const string& description);

    Room* getExit(const string& direction);
    void setExit(const string& direction, Room* room);

    Object* getObject(const string& object);
    void addObject(const Object& object);
    bool hasObjects() const;
    void removeObject(const Object& object);

    Enemy* getEnemy(const string& enemy);
    void addEnemy(const Enemy& enemy);
    bool hasEnemy() const;
    void removeEnemy(const Enemy& enemy);

    string getDescription() const;

    void look();
    void lookAround();

private:
    string _name;
    string _description;
    map<string, Room*> _exits;
    map<string, Object> _objects;
    map<string, Enemy> _enemies;
};

#endif // ROOM_H
