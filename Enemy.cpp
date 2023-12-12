#include "Enemy.h"

Enemy::Enemy(const string& id, const string& description, int aggressiveness, const string& location)
    : id_(id), description_(description), aggressiveness_(aggressiveness), location_(location) {}

Enemy::~Enemy() { /* No cleanup needed */ }

string Enemy::getId() const { return id_; }

string Enemy::getDescription() const { return description_; }

int Enemy::getAggressiveness() const { return aggressiveness_; }
void Enemy::setAggressiveness(int aggressiveness) { aggressiveness_ = aggressiveness; }

string Enemy::getLocation() const { return location_; }
void Enemy::setLocation(const string& location) { location_ = location; }
