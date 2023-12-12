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
public:
    Player(const string& location);
    ~Player();

    int getHealth() const;
    void setHealth(int health);

    string getLocation() const;
    void setLocation(const string& location);

    Object* getObject(const string& objectId);
    map<string, Object*> getObjects() const;
    void addObject(Object* object);
    bool hasObjects() const;

    string check() const;

private:
    int health_;
    string location_;
    map<string, Object*> objects_;
};

#endif // PLAYER_H
