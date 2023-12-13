#pragma once
#include <string>
#include <vector>

using namespace std;

// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

// The Enemy class represents an enemy with unique attributes in the game.
class Enemy {
public:
    Enemy(const string& id, const string& description, const vector<string> canBeKilledBy, int aggressiveness);

    ~Enemy();

    string getId() const;

    string getDescription() const;

    bool canBeKilledBy(const string &objectId) const;

    int getAggressiveness() const;

    string look() const;

private:
    // Member variables to store enemy attributes
    const string id_; // Unique identifier for the enemy
    const string description_; // Description of the enemy
    int aggressiveness_; // Aggressiveness level of the enemy
    const vector<string> canBeKilledBy_; // Specifies what can kill the enemy
};

#endif // ENEMY_H
