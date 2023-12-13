#pragma once
#include <string>

using namespace std;

// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

// The Enemy class represents an enemy with unique attributes in the game.
class Enemy {
public:
    // Static constants for default enemy attributes
    static const string DEFAULT_DESCRIPTION;
    static const int DEFAULT_AGGRESSIVENESS;
    static const string DEFAULT_KILLED_BY;

    // Constructor: Initializes an enemy with specific attributes.
    // id: Unique identifier for the enemy.
    // description: Description of the enemy.
    // canBeKilledBy: Specifies what can be used to kill the enemy.
    // aggressiveness: Aggressiveness level of the enemy.
    Enemy(const string& id, const string& description, const string& canBeKilledBy, int aggressiveness);

    // Destructor: Cleans up the Enemy's resources.
    ~Enemy();

    // getId: Returns the unique ID of the enemy.
    string getId() const;

    // getDescription: Returns the description of the enemy.
    string getDescription() const;

    // getCanBeKilledBy: Returns the object that can kill the enemy.
    string getCanBeKilledBy() const;

    // getAggressiveness: Returns the aggressiveness level of the enemy.
    int getAggressiveness() const;

    // setAggressiveness: Sets the aggressiveness level of the enemy.
    void setAggressiveness(int aggressiveness);

    // look: Provides a detailed description of the enemy.
    string look() const;

private:
    // Member variables to store enemy attributes
    const string id_; // Unique identifier for the enemy
    const string description_; // Description of the enemy
    int aggressiveness_; // Aggressiveness level of the enemy
    const string canBeKilledBy_; // Specifies what can kill the enemy
};

#endif // ENEMY_H
