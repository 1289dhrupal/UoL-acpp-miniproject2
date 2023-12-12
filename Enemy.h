#pragma once
#include <string>

using namespace std;

// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
    // Represents an enemy with unique attributes in the game.
public:
    
    // Constructor to initialize an enemy with ID, description, aggressiveness, and location.
    Enemy(const string& id, const string& description, int aggressiveness, const string& location);
    
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
    
    // Returns the initial location of the enemy.
    string getLocation() const;
    
    // Sets the initial location of the enemy.
    void setLocation(const string& location);

private:
    string id_;
    string description_;
    int aggressiveness_;
    string location_; // Currently used for initial location of the enemy.
};

#endif // ENEMY_H
