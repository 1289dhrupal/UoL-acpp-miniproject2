#pragma once
#include <string>

using namespace std;

// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
    // Represents an enemy with unique attributes in the game.
public:
    static const string DEFAULT_DESCRIPTION;
    static const int DEFAULT_AGGRESSIVENESS;
    static const string DEFAULT_KILLED_BY;

    // Constructor to initialize an enemy with ID, description, aggressiveness, and location.
    Enemy(const string& id, const string& description, const string& canBeKilledBy, int aggressiveness);

    // Destructor for the Enemy class.
    ~Enemy();

    // Returns the unique ID of the enemy.
    string getId() const;

    // Returns the description of the enemy.
    string getDescription() const;

    // Returns the object that can kill the enemy.
    string getCanBeKilledBy() const;

    // Returns the aggressiveness level of the enemy.
    int getAggressiveness() const;

    // Sets the aggressiveness level of the enemy.
    void setAggressiveness(int aggressiveness);

    // Provides a detailed description of the enemy.
    string look() const;

private:
    const string id_;
    const string description_;
    int aggressiveness_;
    const string canBeKilledBy_;
};

#endif // ENEMY_H
