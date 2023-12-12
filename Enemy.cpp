#include "Enemy.h"

// Constructor initializing Enemy with ID, description, aggressiveness, and location.
Enemy::Enemy(const string& id, const string& description, int aggressiveness, const string& location)
    : id_(id), description_(description), aggressiveness_(aggressiveness), location_(location) {}

// Destructor for Enemy class.
Enemy::~Enemy() { /* No cleanup needed */ }

// Returns the ID of the enemy.
string Enemy::getId() const { return id_; }

// Returns the description of the enemy.
string Enemy::getDescription() const { return description_; }

// Returns the aggressiveness level of the enemy.
int Enemy::getAggressiveness() const { return aggressiveness_; }

// Sets the aggressiveness level of the enemy.
void Enemy::setAggressiveness(int aggressiveness) { aggressiveness_ = aggressiveness; }

// Returns the current location of the enemy.
string Enemy::getLocation() const { return location_; }

// Sets the current location of the enemy.
void Enemy::setLocation(const string& location) { location_ = location; }
