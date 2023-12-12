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

    // Constructor to initialize an enemy with ID, description, aggressiveness, and location.
    Enemy(const string& id, const string& description = DEFAULT_DESCRIPTION, 
        int aggressiveness = DEFAULT_AGGRESSIVENESS);
    
    // Destructor for the Enemy class.
    ~Enemy();

    // Returns the unique ID of the enemy.
    string getId() const;
    
    // Returns the description of the enemy.
    string getDescription() const;
    
    // Returns the aggressiveness level of the enemy.
    int getAggressiveness() const;
    
    // Sets the aggressiveness level of the enemy.
    void setAggressiveness(int aggressiveness);

private:
    const string id_;
    const string description_;
    int aggressiveness_;
};

#endif // ENEMY_H
