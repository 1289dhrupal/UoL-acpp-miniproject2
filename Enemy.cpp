#include "Enemy.h"
#include "Objective.h"
#include <sstream>

using namespace std;

Enemy::Enemy(const string& id, const string& description, const vector<string> canBeKilledBy, int aggressiveness)
    : id_(id), description_(description), aggressiveness_(aggressiveness), canBeKilledBy_(canBeKilledBy) {
}

Enemy::~Enemy() {}

string Enemy::getId() const {
    return id_;
}

string Enemy::getDescription() const {
    return description_;
}

int Enemy::getAggressiveness() const {
    return aggressiveness_;
}

bool Enemy::canBeKilledBy(const string& objectId) const {
    return find(canBeKilledBy_.begin(), canBeKilledBy_.end(), objectId) != canBeKilledBy_.end();
}

string Enemy::look() const {
    stringstream ss;
    ss << "        Enemy :: " << id_ << " : " << description_ << endl;
    ss << "            Current status :: Aggressiveness (" << aggressiveness_ << ")" << endl;
    return ss.str();
}
