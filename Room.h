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
    void addObject(Object* object);
    bool hasObjects() const;
    void removeObject(Object* object);

    Enemy* getEnemy(const string& enemy);
    void addEnemy(Enemy* enemy);
    bool hasEnemy() const;
    void removeEnemy(Enemy* enemy);

    string getDescription() const;

    string look();
    string lookAround();

private:
    string _name;
    string _description;
    map<string, Room*> _exits;
    map<string, Object*> _objects;
    map<string, Enemy*> _enemies;
};

#endif // ROOM_H
