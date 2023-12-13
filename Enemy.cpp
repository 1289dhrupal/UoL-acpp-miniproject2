#include "Enemy.h"
#include "Objective.h"
#include <sstream>

using namespace std;

// Default values for Enemy class static members
const string Enemy::DEFAULT_DESCRIPTION = "Random Enemy.";
const int Enemy::DEFAULT_AGGRESSIVENESS = 50;
const string Enemy::DEFAULT_KILLED_BY = "";

// Constructor: Initializes an Enemy with specific attributes.
// id: Unique identifier for the enemy.
// canBeKilledBy: What can be used to kill the enemy.
// description: Description of the enemy.
// aggressiveness: The aggressiveness level of the enemy.
Enemy::Enemy(const string& id, const string& canBeKilledBy, const string& description, int aggressiveness)
    : id_(id), description_(description), aggressiveness_(aggressiveness), canBeKilledBy_(canBeKilledBy) {
    // Constructor implementation
}

// Destructor: Cleans up the Enemy's resources (if any).
Enemy::~Enemy() {
    // Cleanup logic here (if needed).
}

// getId: Returns the ID of the enemy.
string Enemy::getId() const {
    return id_;
}

// getDescription: Returns the description of the enemy.
string Enemy::getDescription() const {
    return description_;
}

// getAggressiveness: Returns the aggressiveness level of the enemy.
int Enemy::getAggressiveness() const {
    return aggressiveness_;
}

// setAggressiveness: Sets the aggressiveness level of the enemy.
// aggressiveness: The new aggressiveness level.
void Enemy::setAggressiveness(int aggressiveness) {
    aggressiveness_ = aggressiveness;
}

// getCanBeKilledBy: Returns the method or object that can kill the enemy.
string Enemy::getCanBeKilledBy() const {
    return canBeKilledBy_;
}

// look: Provides a detailed description of the enemy.
string Enemy::look() const {
    stringstream ss;
    ss << "        Enemy :: " << id_ << " : " << description_ << endl;
    ss << "            Current status :: Aggressiveness (" << aggressiveness_ << ")" << endl;
    return ss.str();
}
