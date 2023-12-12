#pragma once
#include <string>

using namespace std;

// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    Enemy(const string& id, const string& description, int aggressiveness, const string& location);
    ~Enemy();

    string getId() const;
    string getDescription() const;
    int getAggressiveness() const;
    void setAggressiveness(int aggressiveness);
    string getLocation() const;
    void setLocation(const string& location);

private:
    string id_;
    string description_;
    int aggressiveness_;
    string location_;
};

#endif // ENEMY_H
