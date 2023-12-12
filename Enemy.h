#pragma once
#include <string>

using namespace std;

// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    Enemy(const string& name, const string& description, int aggressiveness, const string& location);
    ~Enemy();

    string getName() const;
    string getDescription() const;
    int getAggressiveness() const;
    void setAggressiveness(int aggressiveness);
    string getLocation() const;
    void setLocation(const string& location);

private:
    string _name;
    string _description;
    int _aggressiveness;
    string _location;
};

#endif // ENEMY_H
