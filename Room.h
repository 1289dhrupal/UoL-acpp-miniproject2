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
    Room(const string& id, const string& description);

    Room* getExit(const string& direction);
    void setExit(const string& direction, Room* room);

    Object* getObject(const string& objectId);
    void addObject(Object* object);
    bool hasObjects() const;
    void removeObject(Object* object);
    map<string, Object*> getObjects() const;

    Enemy* getEnemy(const string& enemyId);
    void addEnemy(Enemy* enemy);
    bool hasEnemy() const;
    void removeEnemy(Enemy* enemy);
    map<string, Enemy*> getEnemies() const;

    string getDescription() const;

    string look();
    string lookAround();

private:
    string id_;
    string description_;
    map<string, Room*> exits_;
    map<string, Object*> objects_;
    map<string, Enemy*> enemies_;
};

#endif // ROOM_H
