#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Exits.h"
#include "Object.h"
#include "Enemy.h"

using namespace std;

// Room.h
#ifndef ROOM_H
#define ROOM_H
class Room {
public:
    Room(const string& name, const string& description);
    Room(const string& name, const string& description, const Exits& exits,
        const vector<Object>& objects, const vector<Enemy>& enemies);

    Room* getExit(const string& direction);
    void setExit(const string& direction, Room* room);

    void addObject(const Object& object);
    bool hasObjects() const;
    void removeObject(const Object& object);

    string getDescription() const;

    void look();
    void lookAround();

private:
    string _name;
    string _description;
    Exits _exits;
    vector<Object> _objects;
    vector<Enemy> _enemies;


};

#endif // ROOM_H
