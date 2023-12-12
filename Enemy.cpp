#include "Enemy.h"

Enemy::Enemy(const string& name, const string& description, int aggressiveness, const string& location)
    : _name(name), _description(description), _aggressiveness(aggressiveness), _location(location) {}

string Enemy::getName() const { return _name; }

string Enemy::getDescription() const { return _description; }

int Enemy::getAggressiveness() const { return _aggressiveness; }
void Enemy::setAggressiveness(int aggressiveness) { _aggressiveness = aggressiveness; }

string Enemy::getLocation() const { return _location; }
void Enemy::setLocation(const string& location) { _location = location; }
